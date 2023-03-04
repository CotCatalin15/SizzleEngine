#include "../Public/RenderTaskContext.h"
#include <thread>
#include <algorithm>

RenderTaskContext::RenderTaskContext() : 
    _suspendCount{ 0 },
    _taskCount{ 0 },
    _bStop{ false }
{
    uint32_t maxWorkers = std::max(1U, std::thread::hardware_concurrency() / 2 );

    for (uint32_t i = 0; i < maxWorkers; ++i)
    {
        _workers.emplace_back(&RenderTaskContext::WorkerRoutine, this);
    }

}

RenderTaskContext::~RenderTaskContext()
{
    {
        std::unique_lock<std::mutex> Lock(_renderMutex);
        _tasks.clear();
        _bStop = true;
    }
    _cVar.notify_all();

    //wait all the threads to join
    for (auto& th : _workers)
        if(th.joinable())
            th.join();
    
    {
        std::scoped_lock<std::mutex> Lock(_renderMutex);
        _taskCount = 0;
    }

    _waitVar.notify_all();
}

void RenderTaskContext::EnqueueTask(RenderTaskRef Task, uint32_t Priority /*= 0 */)
{
    {
        std::scoped_lock<std::mutex> Lock(_renderMutex);
        if (!_suspendCount)
        {
            _tasks.emplace_back(Task, Priority);

            std::make_heap(_tasks.begin(), _tasks.end(), [](auto const& lhs, auto const& rhs) {
                return lhs.second > rhs.second;
                });
            ++_taskCount;
        }
        else
        {
            _suspendedTasks.emplace_back(Task, Priority);

            std::make_heap(_suspendedTasks.begin(), _suspendedTasks.end(), [](auto const& lhs, auto const& rhs) {
                return lhs.second > rhs.second;
                });
        }
    }

    _cVar.notify_one();
}

void RenderTaskContext::Wait()
{
    std::unique_lock<std::mutex> Lock(_renderMutex);
    if (_taskCount == 0 || _bStop)
        return;

    _waitVar.wait(Lock, [this] { return _bStop || _taskCount == 0; });
}

void RenderTaskContext::Suspend()
{
    {
        std::scoped_lock<std::mutex> Lock(_renderMutex);
        ++_suspendCount;
    }
    Wait();
}

void RenderTaskContext::Continue()
{
    {
        std::scoped_lock<std::mutex> Lock(_renderMutex);
        --_suspendCount;
        if (_suspendCount == 0)
        {
            _tasks = std::move(_suspendedTasks);
            _taskCount = _tasks.size();
        }
    }
    _cVar.notify_all();
}

void RenderTaskContext::WorkerRoutine()
{
    RenderTaskRef task;
    while (true)
    {
        {
            std::unique_lock<std::mutex> Lock(_renderMutex);
            
            _cVar.wait(Lock, [this] { return _bStop || !_tasks.empty(); });


            if (_bStop)
            {
                break;
            }

            task = PopTaskNoLock();
        }

        task->DoWork(nullptr);
        task.Release();

        --_taskCount;
        if (_taskCount == 0)
        {
            _waitVar.notify_all();
        }
    }
}

RenderTaskRef RenderTaskContext::PopTaskNoLock()
{
    RenderTaskRef task = _tasks.front().first;
    std::pop_heap(_tasks.begin(), _tasks.end(), [](auto const& lhs, auto const& rhs) {
        return lhs.second > rhs.second;
        });
    _tasks.pop_back();
    return task;
}
