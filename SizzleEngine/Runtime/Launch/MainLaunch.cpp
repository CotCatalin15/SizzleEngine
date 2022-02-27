#include "MainLaunch.h"

#include <iostream>
#include "../Core/Debug/DebugMacros.h"
#include "../Engine/Class/SEngine.h"
#include "../ObjectCore/Object/ObjectCast.h"
#include "../Core/Serialization/Public/SDataSerializer.h"



int MainLaunch(int argc, char** argv)
{
    SEngine* engine;
    SDataSerializer ser;
    {
        engine = (SEngine*)SEngine::GetStaticClass()->CreateObject();
        engine->a = 30;
        engine->Serialize(ser);
        delete engine;
    }

    SDataSerializer wr(ser.GetData(), ser.GetSize());
    engine = (SEngine*)SEngine::GetStaticClass()->CreateObject();
    engine->Serialize(wr);
	system("pause");
	return 0;
}
