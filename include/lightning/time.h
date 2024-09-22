#pragma once

#include <lightning/async_task.h>

#include <coroutine>
#include <chrono>

namespace lightning
{

int make_valid_delay_handle(std::chrono::nanoseconds delay);
void release_delay_handle(int handle);

template<typename context_type>
struct delay_awaitable
{
    using clock = std::chrono::system_clock;

    template<typename _rep, typename _period>
    explicit delay_awaitable(context_type& context, const std::chrono::duration<_rep, _period>& rtime) : context_(context)
    {
        if (rtime <= rtime.zero())
        {
            // TODO don't suspend
        }
        handle_ = make_valid_delay_handle(rtime);
    }

    ~delay_awaitable()
    {
        release_delay_handle(handle_);
    }

    bool await_ready() noexcept
    {
        return false;
    }
    void await_suspend(std::coroutine_handle<> h) noexcept
    {
        context_.registerHandle(handle_, h);
    }
    void await_resume() noexcept
    {
    }
private:
    int handle_;
    context_type& context_;
};

template<typename _context, typename _rep, typename _period>
auto delay_for(_context& context, const std::chrono::duration<_rep, _period>& rtime)
{
    delay_awaitable awaitable(context, rtime);
    return awaitable;
}

}