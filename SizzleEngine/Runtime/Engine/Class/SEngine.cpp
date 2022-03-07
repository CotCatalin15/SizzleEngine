#include "SEngine.h"
#include "../../ObjectCore/Object/SObjectRegistry.h"


#include "../../Core/CoreDebug/Public/ILogContext.h"
#include "../../Core/Delegate/EngineDelegates/EngineDelegates.h"

void SEngine::InitObject()
{
    _engineAlive = true;


    OnEnginePreLoadDelegate.Broadcast();
    LoadEngineModules();
    OnEnginePostLoadDelegate.Broadcast();
    //So engine modules can hook up to this broadcast

    OnEnginePostLoadDelegate.Broadcast();
}

SEngine::~SEngine()
{
    OnEnginePreDestroyDelegate.Broadcast();

    OnEngineDestroyDelegate.Broadcast();
    _engineAlive = false;
    
    OnEnginePostDestroyDelegate.Broadcast();
}


bool SEngine::IsEngineRunning()
{
    return _engineAlive;
}

void SEngine::RunEngine()
{
}

void SEngine::LoadEngineModules()
{

}

