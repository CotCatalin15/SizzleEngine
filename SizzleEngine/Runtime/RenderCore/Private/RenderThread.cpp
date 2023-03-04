#include "../Public/RenderThread.h"
#include "../Public/RenderTaskContext.h"

#include "../../RenderContext/Public/RenderContext.h"
#include "../../Core/Util/RefPointer.h"
#include "../Public/RenderTask.h"


#include <queue>
#include <mutex>
#include <atomic>
#include <windows.h>
#include "../../Vulkan/Public/VulkanRenderContext.h"
#include "../../Core/Delegate/EngineDelegates/EngineDelegates.h"

#define MIN_HEAP_ANY_TASK_COUNT 200

RENDERCORE_API RenderContext* GRenderContext;

RENDERCORE_API void InitializeRenderContext()
{
    GRenderContext = new VulkanRenderContext();
}

RENDERCORE_API void DeleteRenderContext()
{
    if (GRenderContext)
    {
        delete GRenderContext;
        GRenderContext = nullptr;
    }
}


SEvent GRenderThreadAcceptsTasks;


std::atomic<bool> GRenderThreadAlive;

std::thread _renderThread;

void StartRenderThreadAsync()
{
    //_renderThread = std::move(std::thread(RenderThreadMain));
    GRenderThreadAcceptsTasks.Set();
}

void StopRenderThread()
{
    GRenderThreadAcceptsTasks.Reset();
    GRenderThreadAlive = false;

    if (_renderThread.joinable())
    {
        _renderThread.join();
    }
}

RenderTaskContext* GRenderTaskContext;

//some tasks can only be executed on the main render thread

std::queue<RenderTaskRef> GMainRenderTasks;
std::mutex GRendererLock;
HANDLE GAnyTaskMemoryHeap;

class AnyExecuteRenderTask : public RenderTask
{
public:
    AnyExecuteRenderTask(std::function< void(RenderCommand*) >&& Func,
        RenderTaskExecuteThread ExecuteThread) :
        RenderTask{ ExecuteThread },
        _func{ Func }
    {
    }

    void DoWork(RenderCommand* Cmd) override
    {
        _func(Cmd);
    }


    uint32_t Release() final override
    {
        uint32_t value = (--_counter);
        if (value == 0)
        {
            HeapLock(GAnyTaskMemoryHeap);
            HeapFree(GAnyTaskMemoryHeap, 0, this);
            HeapUnlock(GAnyTaskMemoryHeap);
        }
        return value;
    }

private:


    std::function<void(RenderCommand*)> _func;
};


void ExecuteRenderThreadTasks()
{
    bool HasTasks = false;
    {
        std::scoped_lock<std::mutex> Lock(GRendererLock);
        HasTasks = !GMainRenderTasks.empty();
    }

    if (!HasTasks)
        return;

    GRenderTaskContext->Suspend();
    RenderTaskRef task;

    while (true)
    {
        {
            std::scoped_lock<std::mutex> Lock(GRendererLock);
            if (GMainRenderTasks.empty())
                return;
            task = std::move( GMainRenderTasks.front() );
            GMainRenderTasks.pop();
        }

        task->DoWork(nullptr);
    }
    GRenderTaskContext->Continue();
}


void RenderThreadMain()
{
    GAnyTaskMemoryHeap = HeapCreate(0, sizeof(AnyExecuteRenderTask) * MIN_HEAP_ANY_TASK_COUNT, 0);
    check(GAnyTaskMemoryHeap);

    GRenderTaskContext = new RenderTaskContext();

    GRenderThreadAlive = true;
    GRenderThreadAcceptsTasks.Set();

    RenderTaskRef task;

    while (GRenderThreadAlive.load(std::memory_order::memory_order_relaxed))
    {  
        ExecuteRenderThreadTasks();
        //do what the renderthread should do
    }

    delete GRenderTaskContext;
    HeapDestroy(GAnyTaskMemoryHeap);
}

bool IsOnRenderThread()
{
    return _renderThread.get_id() == std::this_thread::get_id();
}


void EnqueueTaskOnRenderThread(RenderTaskRef RenderTask, uint32_t Priorty /*= 0 */)
{
    if (RenderTask->GetPreferedThread() == RenderTaskExecuteThread::MainRenderThread)
    {
        std::scoped_lock<std::mutex> Lock(GRendererLock);
        GMainRenderTasks.emplace( RenderTask );
    }
    else
    {
        GRenderTaskContext->EnqueueTask(RenderTask, Priorty);
    }
}


void EnqueueAnyTaskOnRenderThread(std::function<void(RenderCommand*)>&& Func, RenderTaskExecuteThread ExecuteThread, uint32_t Priority)
{
    HeapLock(GAnyTaskMemoryHeap);
    AnyExecuteRenderTask* task = (AnyExecuteRenderTask*)HeapAlloc(GAnyTaskMemoryHeap, 0, sizeof(AnyExecuteRenderTask));
    HeapUnlock(GAnyTaskMemoryHeap);
    check(task);

    new(task)AnyExecuteRenderTask(std::move(Func), ExecuteThread);

    EnqueueTaskOnRenderThread( task, Priority);
}