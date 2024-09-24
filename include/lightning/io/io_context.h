#pragma once
#include <memory>
#include <chrono>
#include <coroutine>
#include <unordered_map>

namespace lightning
{

struct io_awaitable_factory;

struct io_context
{

    explicit io_context(size_t capacity);
    ~io_context();

    template<typename SystemAwaitable>
    void registerAwaitable(SystemAwaitable& awaitable)
    {
        registerHandle(awaitable.handle(), awaitable.coro_handle());
    }

    void registerHandle(int handle, std::coroutine_handle<> coro_handle);

    void poll(int timeout_ms);

private:
    struct pimpl;
    std::unique_ptr<pimpl> impl_;

    std::unordered_map<int, std::coroutine_handle<>> callbacks;
};

}
