#include "MainLaunch.h"
#include "../Engine/Class/SEngine.h"
#include "../ObjectCore/Object/Object.h"
#include "../ObjectCore/Object/ObjectCast.h"

#include <windows.h>
#include "../ObjectCore/Object/SObjectRegistry.h"


int MainLaunch(int argc, char** argv)
{
    //Process arguments

    ///

    ///

    SEngine* engine = nullptr;

    Object* engineObject = Object::CreateObject(SEngine::GetStaticClass());
    if (engineObject == nullptr)
    {
        echeck(0, "Failed to instanciate engine class!");
        return -1;
    }

    engine = ObjectCast<SEngine>(engineObject);
    if (!engine)
    {
        echeck(0, "Failed to cast to engine class!");
        return -1;
    }

    {
        struct EngineLockGuard
        {
            EngineLockGuard(SEngine*& engine)  :
                engine{ engine }
            {}

            ~EngineLockGuard() 
            {
                engine->Destroy();
                engine = nullptr;
            }

            SEngine*& engine;
        }EngineGuard(engine);

        while (engine->IsEngineRunning())
        {
            engine->RunEngine();
        }
    }
	return 0;
}
