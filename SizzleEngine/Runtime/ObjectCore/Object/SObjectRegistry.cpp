#include "SObjectRegistry.h"

#include <memory>
#include "Public/SClass.h"

SObjectRegistry* SObjectRegistry::Get()
{
    static std::unique_ptr< SObjectRegistry > registry = std::make_unique<SObjectRegistry>();
    return registry.get();
}

void SObjectRegistry::RegisterSClass(std::string const& Name, SClass* Cls)
{
    std::unique_lock<std::shared_mutex> Lock(_mutex);
    
    check(_classes.find(Name) == _classes.end());

    _classes[Name] = Cls;
}

SClass* SObjectRegistry::GetSClass(std::string const& Name)
{
    std::shared_lock<std::shared_mutex> Lock(_mutex);

    auto it = _classes.find(Name);
    if (it == _classes.end())
        return nullptr;
    return it->second;
}
