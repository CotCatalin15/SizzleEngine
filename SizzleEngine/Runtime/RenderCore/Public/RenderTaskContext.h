#pragma once


#include "RenderTask.h"
#include "../RenderCoreAPI.h"

#include <vector>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <thread>
#include <atomic>

class RenderCommand;

class RENDERCORE_API RenderTaskContext
{
public:
    RenderTaskContext();
    ~RenderTaskContext();

    void EnqueueTask( RenderTaskRef Task, uint32_t Priority = 0 );

    void Wait();

    void Suspend();
    void Continue();


private:

    void WorkerRoutine();

    RenderTaskRef PopTaskNoLock();

    uint32_t _suspendCount;

    bool _bStop;

    std::atomic<uint32_t> _taskCount;

    std::mutex _renderMutex;

    std::condition_variable _cVar;

    std::condition_variable _waitVar;

    std::vector< std::thread > _workers;

    std::vector< std::pair<RenderTaskRef, uint32_t> > _tasks;

    std::vector< std::pair<RenderTaskRef, uint32_t> > _suspendedTasks;
};