#pragma once
#include <windows.h>
#include <string>
#include "../EngineAPI.h"
#include <unordered_map>
#include "../../Core/Util/RefPointer.h"
#include "../../Core/Util/RefCounter.h"

class ENGINE_API EngineModule
{
public:
    EngineModule(std::string const& Path);
    ~EngineModule();

    void* LoadFunction(const char* Name);

    inline bool Failed() const { return !_library; }
private:
    HMODULE _library;
};

class ENGINE_API EngineModuleLoader
{
public:
    EngineModuleLoader() {}
    ~EngineModuleLoader() {}

    static EngineModuleLoader* Get();

    EngineModule* CreateModule(std::string const& Path) { return nullptr; }

private:
    std::unordered_map<std::string, EngineModule*> _libraries;
};