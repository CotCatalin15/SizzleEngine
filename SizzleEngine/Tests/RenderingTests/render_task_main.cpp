
#include "../../Runtime/RenderCore/Public/RenderTask.h"
#include "../../Runtime/RenderCore/Public/RenderTaskContext.h"
#include "../../Runtime/Core/Util/ScopeGuard.h"
#include "../../Runtime/Vulkan/VulkanExportModule.h"


#include <iostream>
#include <thread>
#include <windows.h>
#include "../../Runtime/RenderCore/Public/RenderThread.h"

class TestRenderTask : public RenderTask
{
public:
    TestRenderTask(int prio)
    {
        pr = prio;
    }

    void DoWork(RenderCommand* Cmd) override
    {
        printf("Doing work %d\n", pr);
    }


    int pr;
};

int main()
{
    InitializeRenderContext();
    DeleteRenderContext();
    return 0;

    RenderTaskContext* Context = new RenderTaskContext();

    RenderTaskRef task = new TestRenderTask(3);
    Context->EnqueueTask(new TestRenderTask(2), 2);
    
    Context->EnqueueTask(new TestRenderTask(2), 2);
    Context->Suspend();
   
    std::this_thread::sleep_for(std::chrono::seconds(5));
    Context->Continue();
    
    Context->Wait();

    delete Context;

    task.Release();
    return 0;
}