#pragma once
#include <atomic>
#include "../CoreAPI.h"
#include "../CoreDebug/DebugMacros.h"


class CORE_API RefCounter
{
public:
    RefCounter() { }

    virtual ~RefCounter() { check(_counter == 0); }

    virtual uint32_t AddRef()
    {
        return (++_counter);
    }

    virtual uint32_t Release()
    {
        uint32_t value = (--_counter);
        if (value == 0)
            delete this;
        return value;
    }

    virtual uint32_t NumRef()
    {
        return _counter;
    }

private:

    std::atomic< unsigned int > _counter;

};