#include <lightning/time.h>
#include <lightning/exception.h>

#include <unistd.h>
#include <sys/timerfd.h>

namespace lightning
{

int make_valid_delay_handle(std::chrono::nanoseconds rtime)
{
    const auto s = std::chrono::duration_cast<std::chrono::seconds>(rtime);
    const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(rtime - s);

    itimerspec timerspec =
    {
        .it_interval = {},
        .it_value = { .tv_sec = s.count(), .tv_nsec = ns.count() }
    };

    int handle = expect_posix_ok(timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK));
    expect_posix_ok(timerfd_settime(handle, 0, &timerspec, nullptr));

    return handle;
}

void release_delay_handle(int handle)
{
    expect_posix_ok(close(handle));
}

}
