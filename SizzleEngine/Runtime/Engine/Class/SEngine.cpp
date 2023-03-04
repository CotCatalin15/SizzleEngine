#include "SEngine.h"
#include "../../ObjectCore/Object/SObjectRegistry.h"


#include "../../Core/CoreDebug/Public/ILogContext.h"
#include "../../Core/Delegate/EngineDelegates/EngineDelegates.h"
#include "../Module/EngineModule.h"
#include "../../RenderContext/Public/RenderContext.h"
#include "../../RenderCore/Public/RenderThread.h"

void SEngine::InitObject()
{
    _engineAlive = true;


    OnEnginePreLoadDelegate.Broadcast();
    LoadEngineComponents();

    //So engine modules can hook up to this broadcast
    OnEnginePostLoadDelegate.Broadcast();
}

SEngine::~SEngine()
{
    OnEnginePreDestroyDelegate.Broadcast();

    StopRenderThread();
    DeleteRenderContext();

    OnEngineDestroyDelegate.Broadcast();
    _engineAlive = false;
    
    OnEnginePostDestroyDelegate.Broadcast();
}


bool SEngine::IsEngineRunning()
{
    return _engineAlive && 0;
}

void SEngine::RunEngine()
{

}

void SEngine::LoadEngineComponents()
{
    //Init the engine render context
    InitializeRenderContext();
    //Now start the renderthrad
    StartRenderThreadAsync();
    
    GRenderThreadAcceptsTasks.Wait();

    LoadEngineModules();
}

void SEngine::LoadEngineModules()
{
    
}

