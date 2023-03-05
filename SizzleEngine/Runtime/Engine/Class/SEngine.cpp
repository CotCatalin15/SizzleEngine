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
    InitializeEngineDelegates();

    //Init the engine render context
    InitializeRenderContext();

    //Now start the render thread
    StartRenderThreadAsync();
    
    GRenderThreadAcceptsTasks.Wait();

    LoadEngineModules();
}

void SEngine::LoadEngineModules()
{
    
}

void SEngine::InitializeEngineDelegates()
{
    //Called by check
    ExternEngineForceDestroy.RegisterDelegate([]() {
        static bool firstCall = true;
        if (firstCall == false)
        {
            //Check was called in this delegate
            firstCall = true;
            //Error/Fatal will call this function again
            SIZZLE_LOG(DefaultLog, LogVerbosity::Warning, "Log with verobisity Error was called inside ExternEngineForceDestroy");
            exit(-1);
        }
        firstCall = false;
    });

    ExternEngineForceDestroyNoCleanup.RegisterDelegate([]() {
        static bool firstCall = true;
        if (firstCall == false)
        {
            //Check was called in this delegate
            firstCall = true;
            //Error/Fatal will call this function again
            SIZZLE_LOG(DefaultLog, LogVerbosity::Warning, "Log with verobisity Fatal was called inside ExternEngineForceDestroyNoCleanup");
            exit(-1);
        }
        firstCall = false;
        });
}

