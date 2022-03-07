#pragma once

#include <functional>
#include <vector>
#include <mutex>
#include <unordered_set>
#include <queue>
#include <windows.h>
#include "../../../CoreAPI.h"

class Task;
class TaskFactory;

class CORE_API Task
{
private:
    //Internal use only
    struct CORE_API __TaskArgument
    {
        TaskFactory* Factory;
        Task* _this;
        std::function<void()> _action;
    };

public:

    void Start();
    void StartAsync();

    void ContinueWith(Task*& NextTask);

    void Wait();
private:

    friend VOID CORE_API CALLBACK _factoryWorkCallback(
        _Inout_     PTP_CALLBACK_INSTANCE Instance,
        _Inout_opt_ PVOID                 Context,
        _Inout_     PTP_WORK              Work
    );

    Task(PTP_CALLBACK_ENVIRON env, TaskFactory* Factory);
    ~Task();

    __TaskArgument TaskWorkArg;
    Task* _nextTask;

    std::function<void()> _action;

    PTP_WORK _work;

    friend class TaskFactory;
};

class CORE_API TaskFactory
{
public:

    TaskFactory();
    ~TaskFactory();

    template<typename Func, typename ... Args>
    Task* CreateTaskAny(Func&& func, Args&& ... args)
    {
        return CreateTask( std::bind(func, std::forward<Args>(args)...) );
    }

    Task* CreateTask( std::function<void()>&& Action );

    static TaskFactory* Get();

private:
    friend VOID CORE_API CALLBACK _factoryWorkCallback(
        _Inout_     PTP_CALLBACK_INSTANCE Instance,
        _Inout_opt_ PVOID                 Context,
        _Inout_     PTP_WORK              Work
    );

    void NotifyTaskWorkFinished(Task* task);
    
    std::mutex _factoryMutex;

    std::vector<Task*> _usedTasks;

    std::vector<Task*> _freeTasks;

    TP_CALLBACK_ENVIRON _environmet;
    
    PTP_POOL _pool;

    HANDLE _memoryHeap;

    friend class Task;
};


