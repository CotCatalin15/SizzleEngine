#include "../Public/SClass.h"

SClass::SClass(SClassTraits Trait) :
    _trait{Trait}
{
    
}

SClass::~SClass()
{

}

std::mutex _sclassMutex;

Object* SClass::InstanciateObject()
{
    if (_trait == SClassTraits::SingleInstanceClass)
    {
        {
            std::unique_lock<std::mutex> Lock(_sclassMutex);
            if (_createdObjects.size() == 1)
            {
                SIZZLE_LOG(DefaultLog, LogVerbosity::Error, "trying to instantiate a single instance class %s",_name.c_str());
                return nullptr;
            }
        }
    }

    Object* obj = CreateObject();
    std::unique_lock<std::mutex> Lock(_sclassMutex);
    
    if(obj)
        _createdObjects.emplace(obj);

    return obj;
}

void SClass::RemoveObjectInstance(Object* Obj)
{
    std::unique_lock<std::mutex> Lock(_sclassMutex);
    _createdObjects.erase(Obj);
}
