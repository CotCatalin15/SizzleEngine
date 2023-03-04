#include "SpinLock.h"


SpinLock::SpinLock(uint32_t SpinCount)
{
    InitializeCriticalSectionAndSpinCount(&_section, SpinCount);
}

SpinLock::~SpinLock()
{
    DeleteCriticalSection(&_section);
}

void SpinLock::lock()
{
    EnterCriticalSection(&_section);
}

bool SpinLock::try_lock()
{
    return (bool)TryEnterCriticalSection(&_section);
}

void SpinLock::unlock()
{
    LeaveCriticalSection(&_section);
}
