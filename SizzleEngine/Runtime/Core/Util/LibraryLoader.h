#pragma once
#include "../CoreAPI.h"
#include "RefPointer.h"
#include "RefCounter.h"

#include <shared_mutex>
#include <unordered_map>

class CORE_API SLibrary : public RefCounter
{
public:

    void* GetProcAdress(const char* FuncName);

    std::string const& GetLibName() const { return _libName; }

private:

    SLibrary(std::string const& Name, void* Module);
    ~SLibrary();


    std::string _libName;

    void* _libModule;

    friend class LibraryLoader;
};

using SLibraryRef = RefPointer<SLibrary>;

class CORE_API LibraryLoader
{
public:
    LibraryLoader();
    ~LibraryLoader();

    static LibraryLoader* Get();

    SLibraryRef TryLoadOrGetLibrary(std::string const& LibName);

private:
    
    void UnloadLibrary(SLibrary* Library);

    std::unordered_map<std::string, SLibrary*> _libraries;

    std::shared_mutex _libMutex;

    
    friend class SLibrary;
};