#include "Event.h"
#include "../CoreDebug/DebugMacros.h"
#include <windows.h>


SEvent::SEvent(bool Signaled /*= false*/, bool AutoReset /*= false */)
{
    _event = CreateEvent(NULL, AutoReset, Signaled, NULL);
    check(_event);
}

SEvent::~SEvent()
{
    CloseHandle(_event);
}

void SEvent::Set()
{
    SetEvent(_event);
}

void SEvent::Reset()
{
    ResetEvent(_event);
}

void SEvent::Pulse()
{
    PulseEvent(_event);
}

void SEvent::Wait()
{   
    WaitForSingleObject(_event, INFINITE);
}

void SEvent::WaitFor(uint64_t Milliseconds)
{
    WaitForSingleObject(_event, Milliseconds);
}
