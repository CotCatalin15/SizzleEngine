#include "EngineModule.h"
#include <memory>

EngineModule::EngineModule(std::string const& Path)
{
    _library = LoadLibrary(Path.c_str());
}

EngineModule::~EngineModule()
{
    FreeLibrary(_library);
}

void* EngineModule::LoadFunction(const char* Name)
{
    return nullptr;
}

EngineModuleLoader* EngineModuleLoader::Get()
{
    static std::unique_ptr<EngineModuleLoader> _loader = std::make_unique<EngineModuleLoader>();
    return _loader.get();
}
