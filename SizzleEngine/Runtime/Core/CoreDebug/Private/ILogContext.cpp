#include "../Public/ILogContext.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <cstdarg>
#include "../../Delegate/EngineDelegates/EngineDelegates.h"



SFileLogContext::SFileLogContext(std::string const& Path)
{
    _writer.open(Path, std::ios::app | std::ios::ate);
}

bool SFileLogContext::LogMessage(LogVerbosity Verbosity, const std::string& Message)
{
    if (_writer.fail())
    {
        return false;
    }

    switch (Verbosity)
    {
    case LogVerbosity::Log:
        _writer << "[Log] ";
        break;
    case LogVerbosity::Warning:
        _writer << "[Warning] ";
        break;
    case LogVerbosity::Error:
        _writer << "[Error] ";
        break;
    case LogVerbosity::FatalError:
        _writer << "[FatalError] ";
        break;
    }

    _writer << Message << '\n';
 
#ifdef _WRITE_DEBUG_TO_CONSOLE
    printf("LogMessage: %s\n", Message.c_str());
#endif

    _writer.flush();

    if (Verbosity == LogVerbosity::Error)
    {
        //Deal with the error
        ExternEngineForceDestroy.Broadcast();
        system("pause");
        return false;
    }
    else if (Verbosity == LogVerbosity::FatalError)
    {
        ExternEngineForceDestroyNoCleanup.Broadcast();
        system("pause");
        exit(-1);
    }


    return true;
}
