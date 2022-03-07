#pragma once
#include "../CoreAPI.h"

#include <functional>
#include <vector>
#include <mutex>


template<typename ... Args>
class Delegate
{
public:
    typedef void(*FunctionType)(Args&& ...);
public:
    Delegate() = default;
    ~Delegate() = default;

    void RegisterDelegate(FunctionType Function)
    {
        std::scoped_lock<std::mutex> Lock(_callMutex);
        if (std::find(_delegates.begin(), _delegates.end(), Function) == _delegates.end())
        {
            _delegates.emplace_back(Function);
        }
    }

    void UnregisterDelegatea(FunctionType Function)
    {
        std::scoped_lock<std::mutex> Lock(_callMutex);
        if (auto it = std::find(_delegates.begin(), _delegates.end(), Function); it != _delegates.end())
        {
            _delegates.erase(it);
        }
    }

    void Broadcast(Args&& ... args)
    {
        std::scoped_lock<std::mutex> Lock(_callMutex);

        for (auto del : _delegates)
        {
            del( std::forward<Args>(args)... );
        }

    }

private:

    std::mutex _callMutex;

    std::vector<FunctionType> _delegates;
};