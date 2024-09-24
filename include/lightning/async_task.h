#pragma once

#include "lightning/awaitable.h"

#include <coroutine>
#include <utility>

namespace lightning
{

struct dummy_context {};

template<typename _context>
struct promise;

template<typename _context = dummy_context>
struct async_task
{
    using promise_type = promise<_context>;

    explicit async_task(promise_type& promise) : handle_(std::coroutine_handle<promise_type>::from_promise(promise)) { }

    void resume()
    {
        handle_.resume();
    }

private:
    std::coroutine_handle<promise_type> handle_;
};

template<typename _context>
struct promise
{
    using context_type = _context;

    // allow default constructor for promise<dummy_context>
    explicit promise(std::enable_if_t<std::is_same_v<_context, dummy_context>, dummy_context> context = dummy_context{}) : context_(context) {}

    explicit promise(context_type& context) : context_(context) {}

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

    template<typename base_awaitable_type>
    auto await_transform(base_awaitable_type&& base_awaitable)
    {
        using awaitable_type = typename awaitable_selector<context_type, base_awaitable_type>::type;
        return awaitable_type(context_, std::forward<base_awaitable_type>(base_awaitable));
    }

    std::suspend_always await_transform(std::suspend_always)
    {
        return {};
    }

    std::suspend_never await_transform(std::suspend_never)
    {
        return {};
    }

private:
    context_type& context_;
};

}
