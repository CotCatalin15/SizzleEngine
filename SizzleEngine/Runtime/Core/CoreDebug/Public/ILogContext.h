#pragma once
#include <string>
#include "../../CoreAPI.h"
#include <stdio.h>
#include <fstream>
#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <condition_variable>

enum class LogVerbosity
{
    Log,
    Warning, 
    Error, //will try to clean-up
    FatalError  //no cleanup 
};

inline std::string LogVerbosityToString(const LogVerbosity& Verbosity)
{
    switch (Verbosity)
    {
    case LogVerbosity::Log:
        return "Log";
        break;
    case LogVerbosity::Warning:
        return "Warning";
        break;
    case LogVerbosity::Error:
        return "Error";
        break;
    case LogVerbosity::FatalError:
        return "FatalError";
        break;
    }

    return "Unknown";
}

class CORE_API LogCategory
{
public:
    LogCategory(const std::string& Category) :
        _category{ Category }
    {

    }
    
    inline std::string GetCategory() const { return _category; }
private:
    std::string _category;
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
        size_t size = snprintf(nullptr, 0, msg, std::forward<Args>(args)...);
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
    struct LogInfo
    {
        LogInfo() {}
        LogInfo(const std::string& LogTime, LogVerbosity Verbosity, const std::string& Message) :
            LogTime{ LogTime },
            Verbosity{ Verbosity },
            Message{ Message }
        {}

        std::string LogTime;
        LogVerbosity Verbosity;
        std::string Message;
    };


public:
    SFileLogContext(std::string const& Path);
    ~SFileLogContext();

    bool IsClosed() const { return _writer.fail(); }

    bool LogMessage(LogVerbosity Verbosity, const std::string& Message) override;

private:
    void LogThreadRoutine();
    std::string GetCurrentDateTimeAsString();

    bool m_stop;
    std::condition_variable m_cVar;
    std::queue<LogInfo> m_logData;
    std::mutex m_mutex;
    std::thread m_logThread;
    std::ofstream _writer;
};