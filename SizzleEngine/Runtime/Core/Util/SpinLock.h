#pragma once
#include <synchapi.h>
#include "../CoreAPI.h"


class CORE_API SpinLock 
{
public:
    SpinLock(uint32_t SpinCount);
    ~SpinLock();

    void lock();
    bool try_lock();
    void unlock();

private:
    CRITICAL_SECTION _section;
};


