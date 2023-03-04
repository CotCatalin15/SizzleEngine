#pragma once

template<typename Fn, typename ... Args>
class DefaultScopeGuard
{
public:
    DefaultScopeGuard(Fn&& GuardFnc, Args&& ... args) :
        _fnc{ GuardFnc },
        _arguments{ std::forward<Args>(args)... }
    { }

    ~DefaultScopeGuard()
    {
        std::apply(_fnc, _arguments);
    }

private:
    Fn& _fnc;
    std::tuple<Args...> _arguments;
};


#define GLUE(x, y) x##y
#define ON_SCOPE_EXIT(Scope, ...) DefaultScopeGuard GLUE(_random_scope_, __COUNTER__)(Scope, __VA_ARGS__);
