#pragma once
#include "../CoreDebug/DebugMacros.h"

template<typename T>
class RefPointer
{
public:
    //Null pointer constructor
    RefPointer() :
        _ptr{ nullptr }
    {}

    RefPointer(T* Ptr) :
        _ptr{ Ptr }
    {
        check(_ptr);
        check(_ptr->AddRef() > 0);
    }

    RefPointer(RefPointer const& other) :
        _ptr{ other._ptr }
    {
        if (_ptr)
            check(_ptr->AddRef() >= 0);
    }

    RefPointer(RefPointer&& other) :
        _ptr{ other._ptr }
    {
        if (_ptr)
            check(_ptr->NumRef() > 0);

        other._ptr = nullptr;
    }

    RefPointer& operator=(RefPointer const& other)
    {
        _ptr = other._ptr;

        if (_ptr)
            check(_ptr->AddRef() > 0);

        return *this;
    }

    RefPointer& operator=(RefPointer&& other)
    {
        _ptr = other._ptr;

        if (_ptr)
            check(_ptr->NumRef() > 0);

        other._ptr = nullptr;
        return *this;
    }

    ~RefPointer()
    {
        Release();
    }

    void Release()
    {
        if (_ptr)
        {
            uint32_t count = _ptr->Release();
            check(count >= 0);
            _ptr = nullptr;
        }
    }

    T* Get() const { return _ptr; }

    T* operator->()
    {
        return _ptr;
    }

    bool IsNull() const
    {
        return _ptr == nullptr;
    }

private:
    T* _ptr;
};
