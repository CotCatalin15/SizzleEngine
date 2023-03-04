#pragma once
#include "../../Core/Util/RefCounter.h"
#include "../RenderCoreAPI.h"
#include "../../Core/Util/RefPointer.h"

class RenderCommand;

enum class RenderTaskExecuteThread
{
    MainRenderThread,
    WorkerRenderThread,
    Any
};

class RENDERCORE_API RenderTask : public RefCounter
{
public:
    RenderTask(RenderTaskExecuteThread PreferedThread = RenderTaskExecuteThread::WorkerRenderThread) :
        _preferedThread(PreferedThread)
        {}

    RenderTaskExecuteThread GetPreferedThread() const { return _preferedThread; }

    virtual ~RenderTask() {}

    virtual void DoWork(RenderCommand* Cmd) = 0;

private:
    RenderTaskExecuteThread _preferedThread;

    friend class RenderTaskContext;
};

using RenderTaskRef = RefPointer<RenderTask>;