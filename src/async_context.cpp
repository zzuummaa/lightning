#include <lightning/async_context.h>
#include <lightning/exception.h>

#include <unistd.h>
#include <sys/epoll.h>

namespace lightning
{

struct async_context::pimpl
{
    int handle_;
    std::vector<epoll_event> events_;

    pimpl(int handle, size_t capacity) : handle_(handle), events_(capacity) {}
};

async_context::async_context(size_t capacity)
    : impl_(
        std::make_unique<pimpl>(
            expect_posix_ok(::epoll_create1(EPOLL_CLOEXEC)),
            capacity
        )
    )
{

}

async_context::~async_context()
{
    ::close(impl_->handle_);
}


void async_context::registerHandle(int handle, std::coroutine_handle<> coro_handle)
{
    epoll_event ev =
    {
        .events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP,
        .data = { .fd = handle }
    };

    expect_posix_ok(::epoll_ctl(impl_->handle_, EPOLL_CTL_ADD, handle, &ev));
    expect(callbacks.try_emplace(handle, coro_handle).second);
}

 void async_context::poll(int timeout_ms)
{
    int count = expect_posix_ok(::epoll_wait(impl_->handle_, impl_->events_.data(), impl_->events_.size(), timeout_ms));
    for (int i = 0; i < count; ++i)
    {
        const auto it = callbacks.find(impl_->events_[i].data.fd);
        expect(it, std::end(callbacks), std::not_equal_to{});

        auto coro_handle = it->second;
        callbacks.erase(it);

        coro_handle.resume();
    }
}

}

