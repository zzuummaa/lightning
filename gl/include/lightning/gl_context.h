#pragma once

#include <coroutine>

namespace lightning
{

struct gl_context
{
    template<typename SystemAwaitable>
    void registerAwaitable(SystemAwaitable& awaitable)
    {
        registerHandle(awaitable.handle(), awaitable.coro_handle());
    }

    void registerHandle(int handle, std::coroutine_handle<> coro_handle);
};

} // namespace lightning