#pragma once

#include "../../ObjectCore/Object/Object.h"
#include "../EngineAPI.h"
#include "../../ObjectCore/Object/Public/SClass.h"
#include "../../ObjectCore/Object/Macros/SClassMacros.h"

#include "SEngine.generated.h"


BUILD_EXECUTE_COMMAND(ParseClass, API = ENGINE_API)
class ENGINE_API SEngine : public Object
{
	GENERATE_SCLASS()
public:
	SEngine();
	~SEngine();

	BUILD_EXECUTE_SUBCOMMAND(Reflect);
	int a;
};