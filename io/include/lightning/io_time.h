#pragma once

#include <lightning/time.h>

#include <coroutine>
#include <chrono>

namespace lightning
{

int make_valid_delay_handle(std::chrono::nanoseconds delay);
void release_delay_handle(int handle);

template<typename _context>
struct io_delay_awaitable
{
    using context_type = _context;
    using clock = std::chrono::system_clock;

    explicit io_delay_awaitable(context_type& context, std::chrono::nanoseconds rtime) : context_(context)
    {
        if (rtime <= rtime.zero())
        {
            // TODO don't suspend
        }
        handle_ = make_valid_delay_handle(rtime);
    }

    ~io_delay_awaitable()
    {
        release_delay_handle(handle_);
    }

    bool await_ready() noexcept
    {
        return false;
    }

    void await_suspend(std::coroutine_handle<> h) noexcept
    {
        context_.register_handle(handle_, h);
    }

    void await_resume() noexcept
    {
    }
private:
    int handle_;
    context_type& context_;
};

}
