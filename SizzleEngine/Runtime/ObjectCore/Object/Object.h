#pragma once
#include "../ObjectCoreAPI.h"

#include <string>
#include "../../Core/Serialization/SArchive.h"

class SClass;

class OBJECTCORE_API Object
{
public:
	Object();
	virtual ~Object();

	virtual uint64_t GetSize() const = 0;
	virtual std::string GetName() const = 0;
	virtual SClass* GetObjectClass() const { return nullptr; }

	virtual void Serialize( SArchive& ar );

	virtual void InitObject() {}

    void Destroy();

	static Object* CreateObject(SClass* Class);

private:
};