#pragma once

#include "../../ObjectCore/Object/Object.h"
#include "../EngineAPI.h"
#include "../../ObjectCore/Object/Public/SClass.h"
#include "../../ObjectCore/Object/Macros/SClassMacros.h"

#include "SEngine.generated.h"


BUILD_EXECUTE_COMMAND(ParseClass, API = ENGINE_API, INSTANCE = SClassTraits::SingleInstanceClass)
class ENGINE_API SEngine : public Object
{
	GENERATE_SCLASS()
public: 
	
	~SEngine(); 
	
	virtual void InitObject();

	bool IsEngineRunning();
	void RunEngine();

private:

	void LoadEngineComponents();

	void LoadEngineModules();
	void UnloadEngineModules();

	bool _engineAlive = false;
};