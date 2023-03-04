#pragma once
#include <atomic>
#include "../CoreAPI.h"


class CORE_API RefCounter
{
public:
    RefCounter();

    virtual ~RefCounter();

    virtual uint32_t AddRef();

    virtual uint32_t Release();

    virtual uint32_t NumRef();

protected:

    std::atomic< unsigned int > _counter;

};