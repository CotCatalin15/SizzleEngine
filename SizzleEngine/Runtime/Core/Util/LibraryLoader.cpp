#include "LibraryLoader.h"
#include <memory>
#include <windows.h>

LibraryLoader::LibraryLoader()
{

}

LibraryLoader::~LibraryLoader()
{
    
}

LibraryLoader* LibraryLoader::Get()
{
    static std::unique_ptr<LibraryLoader> _manager = std::make_unique<LibraryLoader>();
    return _manager.get();
}



SLibraryRef LibraryLoader::TryLoadOrGetLibrary(std::string const& LibName)
{

    {
        std::shared_lock<std::shared_mutex> Lock(_libMutex);
        if (auto it = _libraries.find(LibName); it != _libraries.end())
        {
            return it->second;
        }
    }

    HMODULE libHandle = LoadLibraryA(LibName.c_str());

    if (!libHandle)
    {
        return SLibraryRef();
    }

    SLibrary* Library = new SLibrary(LibName, (void*)libHandle);
    check(Library);

    {
        std::shared_lock<std::shared_mutex> Lock(_libMutex);
        _libraries.emplace(LibName, Library);
    }

    return Library;
}

void LibraryLoader::UnloadLibrary(SLibrary* Library)
{
    std::scoped_lock<std::shared_mutex> Lock(_libMutex);
    _libraries.erase(Library->GetLibName());
}

void* SLibrary::GetProcAdress(const char* FuncName)
{
    HMODULE libModule = (HMODULE)this->_libModule;

    return GetProcAddress(libModule, FuncName);
}

SLibrary::SLibrary(std::string const& Name, void* Module) :
    _libName{ Name },
    _libModule{ Module }
{
    check(_libModule);
}

SLibrary::~SLibrary()
{
    HMODULE libModule = (HMODULE)_libModule;
    FreeLibrary(libModule);

    LibraryLoader::Get()->UnloadLibrary(this);
    libModule = nullptr;
}
