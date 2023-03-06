#pragma once

#include <vector>
#include <string>

class CheckException
{
public:
    CheckException(std::string Message, std::vector<std::string> StackTrace) :
        m_message{ Message },
        m_stackTrace{ StackTrace }
    {}

    inline std::string GetMessage() const { return m_message; }
    inline std::vector<std::string> GetStackTrace() const { return m_stackTrace; }

protected:
    std::string m_message;
    std::vector<std::string> m_stackTrace;
};