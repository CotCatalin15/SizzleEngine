#pragma once
#include <atomic>
#include "../../Core/Util/Event.h"
#include "RenderTask.h"
#include <functional>
#include "../RenderCoreAPI.h"

class RenderContext;
RENDERCORE_API extern RenderContext* GRenderContext;

RENDERCORE_API void InitializeRenderContext();
RENDERCORE_API void DeleteRenderContext();


class RenderCommand;

//Starts the renedthread async
RENDERCORE_API void StartRenderThreadAsync();
RENDERCORE_API void StopRenderThread();

//Event that is triggered when the renderthread can take tasks
extern RENDERCORE_API SEvent GRenderThreadAcceptsTasks;


RENDERCORE_API void EnqueueTaskOnRenderThread( RenderTaskRef RenderTask, uint32_t Priorty = 0 );
RENDERCORE_API void EnqueueAnyTaskOnRenderThread( std::function<void(RenderCommand*)>&& Func, 
    RenderTaskExecuteThread ExecuteThread = RenderTaskExecuteThread::WorkerRenderThread, uint32_t Priority = 0);

void RenderThreadMain();

RENDERCORE_API bool IsOnRenderThread();


#define ENQUEUE_RENDER_COMMAND( Lambda ) EnqueueAnyTaskOnRenderThread( Lambda )