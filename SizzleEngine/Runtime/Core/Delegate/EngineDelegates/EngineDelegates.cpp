#include "EngineDelegates.h"


//---------------ENGINE CALLS THIS FUNCTIONS
//Loading
Delegate<> OnEnginePreLoadDelegate;
Delegate<> OnEngineLoadDelegate;
Delegate<> OnEnginePostLoadDelegate;

//Destroy phase
Delegate<> OnEnginePreDestroyDelegate;
Delegate<> OnEngineDestroyDelegate;
Delegate<> OnEnginePostDestroyDelegate;


//------------OUTSIDE ENGINE FUNCTIONS CAN CALL THEM

//On error
Delegate<> ExternEngineForceDestroy;

//On fatal error where immediate shutdown is required 
Delegate<> ExternEngineForceDestroyNoCleanup;