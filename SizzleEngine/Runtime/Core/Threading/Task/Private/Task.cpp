#include "../Public/Task.h"
#include "../../../CoreDebug/DebugMacros.h"
#include <xutility>

constexpr size_t MaxFreeTaskSize = 100;

VOID _factoryWorkCallback(_Inout_ PTP_CALLBACK_INSTANCE Instance, _Inout_opt_ PVOID Context, _Inout_ PTP_WORK Work)
{
    Task::__TaskArgument* taskArg = (Task::__TaskArgument*)Context;
   
    taskArg->_action();
    taskArg->_action = nullptr;
    taskArg->Factory->NotifyTaskWorkFinished(taskArg->_this);

    if(taskArg->_this->_nextTask)
        taskArg->_this->_nextTask->Start();
}

TaskFactory::TaskFactory()
{
    _pool = CreateThreadpool(NULL);
    check(_pool);

    check(SetThreadpoolThreadMinimum(_pool, 10) == TRUE);
    SetThreadpoolThreadMaximum(_pool, 100);

    ZeroMemory(&_environmet, sizeof(_environmet));
    InitializeThreadpoolEnvironment(&_environmet);
    SetThreadpoolCallbackPool(&_environmet, _pool);
    SetThreadpoolCallbackRunsLong(&_environmet);

    _memoryHeap = HeapCreate(HEAP_NO_SERIALIZE, sizeof(Task) * 100, 0);
    check(_memoryHeap);
}

TaskFactory::~TaskFactory()
{
    if (_pool)
    {
        CloseThreadpool(_pool);
    }

    std::scoped_lock<std::mutex> Lock(_factoryMutex);
    
    for (auto& task : _usedTasks)
    {
        task->~Task();
    }
    for (auto& task : _freeTasks)
    {
        task->~Task();
    }

    _freeTasks.clear();
    _usedTasks.clear();

    if (_memoryHeap)
    {
        check(HeapDestroy(_memoryHeap) == TRUE);
    }
}

Task* TaskFactory::CreateTask(std::function<void()>&& Action)
{
    Task* task = nullptr;
    {
        std::scoped_lock<std::mutex> Lock(_factoryMutex);
        if (!_freeTasks.empty())
        {
            task = _freeTasks.back();
            task->_action = std::move(Action);
            _freeTasks.pop_back();
        }
        else
        {
            task = (Task*)HeapAlloc(_memoryHeap, 0, sizeof(Task));
            check(task);

            new(task) Task(&_environmet, this);

            task->_action = std::move(Action);
        }

        _usedTasks.emplace_back(task);
    }

    return task;
}




TaskFactory* TaskFactory::Get()
{
    static std::unique_ptr<TaskFactory> _factory = std::make_unique<TaskFactory>();
    return _factory.get();
}

void TaskFactory::NotifyTaskWorkFinished(Task* task)
{
    {
        std::scoped_lock<std::mutex> Lock(_factoryMutex);


        for (int i = _usedTasks.size() - 1; i >= 0 ; --i)
        {
            if (_usedTasks[i] == task)
            {
                _usedTasks[i] = _usedTasks.back();
                _usedTasks.pop_back();
                if (_freeTasks.size() >= MaxFreeTaskSize)
                {
                    task->~Task();
                    HeapFree(_memoryHeap, 0, (LPVOID)task);
                }
                else
                    _freeTasks.emplace_back(task);
                return;
            }
        }
    }

    check(0);
}

Task::Task(PTP_CALLBACK_ENVIRON env, TaskFactory* Factory) : 
    _nextTask{ nullptr }
{
    _work = CreateThreadpoolWork(_factoryWorkCallback, &TaskWorkArg, env);
    TaskWorkArg.Factory = Factory;
    TaskWorkArg._this = this;
    TaskWorkArg._action = nullptr;

    check(_work);
}


Task::~Task()
{
    if (_work)
    {
        CloseThreadpoolWork(_work);
    }
}

void Task::Start()
{
    check(_action);

    TaskWorkArg._action = std::move(_action);
    TaskWorkArg._action();
    TaskWorkArg._action = nullptr;

    TaskWorkArg.Factory->NotifyTaskWorkFinished(this);

    if (_nextTask)
        _nextTask->Start();
}

void Task::StartAsync()
{
    check(_action);
    TaskWorkArg._action = std::move(_action);
    SubmitThreadpoolWork(_work);
}

void Task::ContinueWith(Task*& NextTask)
{
    check(NextTask);
    _nextTask = NextTask;
    NextTask = nullptr;
}

void Task::Wait()
{
    WaitForThreadpoolWorkCallbacks(_work, FALSE);
}

