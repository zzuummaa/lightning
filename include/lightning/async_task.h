#pragma once

#include <coroutine>

namespace lightning
{

struct promise;

template<typename _promise = promise>
struct async_task
{
    using promise_type = _promise;

    explicit async_task(_promise& promise) : handle_(std::coroutine_handle<_promise>::from_promise(promise)) { }

    void resume()
    {
        handle_.resume();
    }

private:
    std::coroutine_handle<_promise> handle_;
};

struct promise
{
    auto get_return_object()
    {
        return async_task{ *this };
    }

    std::suspend_never initial_suspend() noexcept
    {
        return {};
    }

    std::suspend_always final_suspend() noexcept
    {
        return {};
    }

    void return_void()
    {

    }

    void unhandled_exception()
    {

    }
};

}
