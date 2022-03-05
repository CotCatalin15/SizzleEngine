#pragma once

enum class LogVerbosity
{
    Log,
    Warning, 
    Error
};


class ILogContext
{
public:

    ILogContext() = default;
    virtual ~ILogContext() = default;

    //Just formats the message
    bool LogMessageFormat(LogVerbosity Verbosity, const std::string& Message, ...);
    virtual bool LogMessage(LogVerbosity Verbosity, const std::string& Message);

private:
};