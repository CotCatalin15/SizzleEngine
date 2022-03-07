#include "../Object.h"
#include "../Public/SClass.h"

Object::Object()
{

}

Object::~Object()
{

}

void Object::Serialize(SArchive& ar)
{
	//Goes through each its objects class 
	SClass* ObjClass = this->GetObjectClass();

	for (auto field : ObjClass->GetFields())
	{
		//tries to serialise field
		field->SerializeField(ar, this);
	}

}

void Object::Destroy()
{
	//Remove its instance
	GetObjectClass()->RemoveObjectInstance(this);
	delete this;
}

Object* Object::CreateObject(SClass* Class)
{
	check(Class);

	Object* newObject = Class->InstanciateObject();

	if (newObject)
	{
		newObject->InitObject();
	}
   
	return newObject;
}
