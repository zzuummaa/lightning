#pragma once

#include <lightning/awaitable.h>

#include <lightning/io_context.h>
#include <lightning/io_time.h>

namespace lightning
{

template<>
struct awaitable_selector<io_context, delay_for>
{
    using type = io_delay_awaitable<io_context>;
};


struct binary_awaitable
{

};

}
