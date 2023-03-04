#pragma once
#include "../CoreAPI.h"

#include <stdint.h>

class CORE_API SEvent
{
public:
    SEvent(bool Signaled = false, bool AutoReset = false );
    ~SEvent();

    void Set();
    void Reset();

    void Pulse();
    void Wait();
    void WaitFor(uint64_t Milliseconds);

private:
    typedef void* HANDLE;
    HANDLE _event;
};