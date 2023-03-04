#include "EngineModule.h"
#include <memory>

EngineModuleLoader* EngineModuleLoader::Get()
{
    static std::unique_ptr<EngineModuleLoader> _loader = std::make_unique<EngineModuleLoader>();
    return _loader.get();
}

EngineModule* EngineModuleLoader::GetOrCreateModule(std::string const& Path)
{
    {
        std::scoped_lock<std::mutex> Lock(_moduleMutex);
        if (auto it = _libraries.find(Path); it != _libraries.end())
        {
            return it->second.second;
        }
    }

    HMODULE Lib = LoadLibraryA(Path.c_str());
    if (!Lib)
    {
        return nullptr;
    }


    typedef EngineModule* (*CreateModulePred)(void);
    CreateModulePred pred = (CreateModulePred)GetProcAddress(Lib, "CreateSizzleEngineModule");
    EngineModule* module = pred();

    echeck(module, "Could not find module %s function: CreateSizzleEngineModule!", Path.c_str());

    {
        std::scoped_lock<std::mutex> Lock(_moduleMutex);
        _libraries[Path] = std::make_pair(Lib, module);
    }
    module->Load();

    return module;
}

void EngineModuleLoader::UnloadAll()
{
    std::scoped_lock<std::mutex> Lock(_moduleMutex);
    for (auto& lib_mod : _libraries)
    {
        std::pair<HMODULE, EngineModule*>& p = lib_mod.second;
        check(FreeLibrary(p.first) == TRUE);
        p.second->Destroy();
        delete p.second;
    }
    _libraries.clear();
}
