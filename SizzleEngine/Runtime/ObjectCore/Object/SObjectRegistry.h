#pragma once

#include "../ObjectCoreAPI.h"

#include <shared_mutex>
#include <unordered_map>
#include <string>

class SClass;

class OBJECTCORE_API SObjectRegistry
{
public:
    static SObjectRegistry* Get();

    void RegisterSClass(std::string const& Name, SClass* Cls);

    SClass* GetSClass(std::string const& Name);


private:

    std::shared_mutex _mutex;

    std::unordered_map<std::string, SClass*> _classes;
};