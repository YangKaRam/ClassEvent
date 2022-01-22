#pragma once

#ifndef _H_CLASS_EVENT
#define _H_CLASS_EVENT

#include <functional>

template<class R>
class ClassEvent;

template<class R, class ... Args>
class ClassEvent<R(Args...)>
{
private:
    void* inst = NULL;
    using ClassFunc = std::function<R(Args...)>;
    ClassFunc func = nullptr;
public:
    bool isSetEvent = false;

public:
    R operator()(Args... _args)
    {
        return func(_args ...);
    }

    ClassEvent& operator=(ClassFunc _classFunc)
    {
        this->func = _classFunc;
        return (*this);
    }

    template<class R, class C, class ... Args>
    ClassEvent& operator=(R(C::* _func)(Args...))
    {
        std::function<R(C*, Args...)> _func2 = _func;
        C* _inst = (C*)this->inst;
        this->func = [=](Args ... _args) -> R { return _func2(_inst, _args ...); };
        return (*this);
    }

    template<class C>
    ClassEvent& operator=(C* _inst)
    {
        this->inst = _inst;
        return (*this);
    }

    template<class R, class C, class ... Args>
    void SetEvent(C* _inst, R(C::* _func)(Args...))
    {
        std::function<R(C*, Args...)> _func2 = _func;
        this->func = [=](Args ... _args) -> R { return _func2(_inst, _args ...); };
        this->isSetEvent = true;
    }
};

template<class R, class ... Args>
class ClassEvent<std::function<R(Args...)>>
{
private:
    void* inst = NULL;
    using ClassFunc = std::function<R(Args...)>;
    ClassFunc func = nullptr;
public:
    R operator()(Args... _args)
    {
        return this->func(_args ...);
    }

    ClassEvent& operator=(ClassFunc _classFunc)
    {
        this->func = _classFunc;
        return (*this);
    }

    template<class R, class C, class ... Args>
    void operator=(R(C::* _func)(Args...))
    {
        std::function<R(C*, Args...)> _func2 = _func;
        C* _inst = (C*)this->inst;
        this->func = [=](Args ... _args) -> R { return _func2(_inst, _args ...); };
    }

    template<class C>
    ClassEvent& operator=(C* _inst)
    {
        this->inst = _inst;
        return (*this);
    }

    template<class R, class C, class ... Args>
    void SetEvent(C* _inst, R(C::* _func)(Args...))
    {
        std::function<R(C*, Args...)> _func2 = _func;
        this->func = [=](Args ... _args) -> R { return _func2(_inst, _args ...); };
    }
};

#endif _H_EVENT_Y