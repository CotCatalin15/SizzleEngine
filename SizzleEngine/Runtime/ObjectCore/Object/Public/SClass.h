#pragma once

#include "../../ObjectCoreAPI.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <mutex>


#include "SField.h"

class Object;

enum class SClassTraits
{
	SingleInstanceClass,
	MultiInstanceClass //multi-instance
};

class OBJECTCORE_API SClass
{
public:
	SClass(SClassTraits Trait = SClassTraits::MultiInstanceClass);
	~SClass();

	virtual std::string GetName() const = 0;


	Object* InstanciateObject();
	void RemoveObjectInstance(Object* Obj);
	

	inline std::vector< SField* > const& GetFields() const { return _fields; }

protected: 
	virtual Object* CreateObject() = 0;

	SClassTraits _trait;

	std::string _name;
	std::string _derived;

	std::vector< SField* > _fields;

	std::unordered_set<Object*> _createdObjects;
};