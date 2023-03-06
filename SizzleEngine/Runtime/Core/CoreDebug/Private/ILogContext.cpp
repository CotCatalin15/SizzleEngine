#include "../Public/ILogContext.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <cstdarg>
#include "../../Delegate/EngineDelegates/EngineDelegates.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include "DebugStackTrace.h"
#include "../Public/CheckException.h"



SFileLogContext::SFileLogContext(std::string const& Path) : 
    m_stop{ true }
{
    _writer.open(Path);

    if (_writer.fail())
    {
        return;
    }

    m_stop = false;
    try
    {
        m_logThread = std::thread(&SFileLogContext::LogThreadRoutine, this);
    }
    catch (...)
    {
        _writer << "Failed to create log thread\n";
    }
}

SFileLogContext::~SFileLogContext()
{
    if (_writer.fail() || !m_logThread.joinable())
    {
        return;
    }

    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_stop = true;
    }
    m_cVar.notify_all();
    m_logThread.join();
    _writer.close();
}

bool SFileLogContext::LogMessage(LogVerbosity Verbosity, const std::string& Message)
{
    if (_writer.fail())
    {
        return false;
    }

    LogInfo info(std::move(GetCurrentDateTimeAsString()), Verbosity, Message);

    //Log stack
    if (Verbosity == LogVerbosity::Error || Verbosity == LogVerbosity::FatalError)
    {
        std::vector<std::string> frames = GetCurrentStackFunctions();
        std::ostringstream os;
        os << "[STACKTRACE]\n";

        for (auto& frame : frames)
        {
            os << frame << '\n';
        }

        os << Message;
        info.Message = os.str();
    }

    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if(Verbosity == LogVerbosity::Error)
        { 
            m_logData.emplace(info);
        }
        else
        {
            m_logData.emplace(std::move(info));
        }
    }
    m_cVar.notify_one();

    if (Verbosity == LogVerbosity::Error)
    {
        //Deal with the error
        ExternEngineForceDestroy.Broadcast();
        throw CheckException(info.Message, GetCurrentStackFunctions());
        return false;
    }
    else if (Verbosity == LogVerbosity::FatalError)
    {
        ExternEngineForceDestroyNoCleanup.Broadcast();
        exit(-2);
    }


    return true;
}

void SFileLogContext::LogThreadRoutine()
{
    LogInfo log;
    while (true)
    {
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cVar.wait(lock, [this] { return m_stop || !m_logData.empty(); });

            //Flush everything before returning
            if (m_stop && m_logData.empty())
            {
                _writer.flush();
                break;
            }
            log = std::move(m_logData.front());
            m_logData.pop();
        }

        
        _writer << '[' << LogVerbosityToString(log.Verbosity) << ']' 
                << '[' << log.LogTime << ']' 
                << ' ' << log.Message << '\n';

#ifdef _WRITE_DEBUG_TO_CONSOLE
        printf("LogMessage: [%s][%s] %s\n", log.LogTime.c_str(), LogVerbosityToString(log.Verbosity).c_str(), log.Message.c_str());
#endif
    }
}

std::string SFileLogContext::GetCurrentDateTimeAsString()
{
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);

    std::tm tm_now = *std::localtime(&time_t_now);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

    std::stringstream ss;
    ss << std::put_time(&tm_now, "%Y-%m-%d %H:%M:%S") << '.' << std::setfill('0') << std::setw(3) << milliseconds.count() << '.' << std::setfill('0') << std::setw(5) << microseconds.count();

    return ss.str();
}
