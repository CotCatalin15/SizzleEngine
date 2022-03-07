#pragma once

#include "../Delegate.h"
#include "../../CoreAPI.h"



//---------------ENGINE CALLS THIS FUNCTIONS
//Loading
extern CORE_API Delegate<> OnEnginePreLoadDelegate;
extern CORE_API Delegate<> OnEngineLoadDelegate;
extern CORE_API Delegate<> OnEnginePostLoadDelegate;

//Destroy phase
extern CORE_API Delegate<> OnEnginePreDestroyDelegate;
extern CORE_API Delegate<> OnEngineDestroyDelegate;
extern CORE_API Delegate<> OnEnginePostDestroyDelegate;


//------------OUTSIDE ENGINE FUNCTIONS CAN CALL THEM

//On error
extern CORE_API Delegate<> ExternEngineForceDestroy;

//On fatal error where immediate shutdown is required 
extern CORE_API Delegate<> ExternEngineForceDestroyNoCleanup;


