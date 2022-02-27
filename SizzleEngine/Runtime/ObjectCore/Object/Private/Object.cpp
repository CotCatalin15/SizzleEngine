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
		field->SerializeField(ar, this);
	}

}

void Object::Destroy()
{
	delete this;
}
