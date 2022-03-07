#pragma once
#include <string>
#include "../../CoreAPI.h"
#include <stdio.h>
#include <fstream>

enum class LogVerbosity
{
    Log,
    Warning, 
    Error, //will try to clean-up
    FatalError  //no cleanup 
};


class CORE_API ILogContext
{
public:

    ILogContext() = default;
    virtual ~ILogContext() = default;

    //Just formats the message
    template<typename ... Args>
    bool LogMessageFormat(LogVerbosity Verbosity, const std::string& Message, Args&& ... args)
    {
        std::string buffer;
        const char* const msg = Message.c_str();
        int size = snprintf(nullptr, 0, msg, std::forward<Args>(args)...);
        buffer.resize(size + 1);
        sprintf_s(buffer.data(), size + 1, Message.c_str(), std::forward<Args>(args)...);

        return LogMessage(Verbosity, buffer);
    }

    virtual bool LogMessage(LogVerbosity Verbosity, const std::string& Message) = 0;

private:
};



class CORE_API SFileLogContext : public ILogContext
{
public:
    SFileLogContext(std::string const& Path);

    bool IsClosed() const { return _writer.fail(); }

    bool LogMessage(LogVerbosity Verbosity, const std::string& Message) override;

private:

    std::ofstream _writer;

};