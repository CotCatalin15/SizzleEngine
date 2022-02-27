#pragma once

#include "../../ObjectCoreAPI.h"

#include <string>
#include <vector>
#include "SField.h"

class Object;

class OBJECTCORE_API SClass
{
public:
	SClass();
	~SClass();

	virtual std::string GetName() const = 0;
	virtual Object* CreateObject() = 0;

	inline std::vector< SField* > const& GetFields() const { return _fields; }

protected: 

	std::string _name;
	std::string _derived;

	std::vector< SField* > _fields;
};