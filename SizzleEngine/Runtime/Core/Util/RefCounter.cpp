#include "RefCounter.h"
#include "../CoreDebug/DebugMacros.h"

RefCounter::RefCounter()
{

}

RefCounter::~RefCounter() { check(_counter == 0); }

uint32_t RefCounter::AddRef()
{
    return (++_counter);
}

uint32_t RefCounter::Release()
{
    uint32_t value = (--_counter);
    if (value == 0)
        delete this;
    return value;
}

uint32_t RefCounter::NumRef()
{
    return _counter;
}
