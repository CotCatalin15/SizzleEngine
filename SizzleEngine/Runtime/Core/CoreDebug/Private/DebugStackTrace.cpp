#include "DebugStackTrace.h"

#include <memory.h>
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "DbgHelp.lib")


std::vector<std::string> GetCurrentStackFunctions()
{
    std::vector<std::string> callbackFrames;

    const int max_frames = 200;
    void* callstack[max_frames];
    int frames = CaptureStackBackTrace(0, max_frames, callstack, NULL);

    // Initialize symbol handler
    SymSetOptions(SYMOPT_DEFERRED_LOADS | SYMOPT_UNDNAME);
    SymInitialize(GetCurrentProcess(), NULL, TRUE);

    try
    {
        // Resolve symbol names and create a vector of strings

        std::vector<uint8_t> symbolBuffer(sizeof(SYMBOL_INFO) + 256 * sizeof(uint8_t));
        SYMBOL_INFO* symbol = reinterpret_cast<SYMBOL_INFO*>(symbolBuffer.data());

        symbol->MaxNameLen = 255;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

        for (int i = 3; i < frames - 6; i++)
        {
            DWORD64 address = (DWORD64)(callstack[i]);
            if (symbol != nullptr)
            {
                SymFromAddr(GetCurrentProcess(), address, 0, symbol);
                callbackFrames.push_back(symbol->Name);
            }
            else
            {
                callbackFrames.push_back("Unknown frame");
            }
        }
    }
    catch (...)
    {

    }

    SymCleanup(GetCurrentProcess());

    return callbackFrames;
}