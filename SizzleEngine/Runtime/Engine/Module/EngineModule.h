#pragma once
#include "../EngineAPI.h"
#include "../../Core/Util/RefPointer.h"
#include "../../Core/Util/RefCounter.h"

#include <mutex>
#include <windows.h>
#include <string>
#include <unordered_map>
#include <utility>

class EngineModule
{
public:
    EngineModule() = default;
    virtual ~EngineModule() = default;

    virtual void Load() = 0;
    virtual void Destroy() = 0;
    virtual void RegisterSClasses() = 0;


private:

};

class ENGINE_API EngineModuleLoader
{
public:
    EngineModuleLoader() {}
    ~EngineModuleLoader() { UnloadAll(); }

    static EngineModuleLoader* Get();

    EngineModule* GetOrCreateModule(std::string const& Path);

    void UnloadAll();

private:

    std::mutex _moduleMutex;

    std::unordered_map<std::string, std::pair<HMODULE, EngineModule*>> _libraries;
};