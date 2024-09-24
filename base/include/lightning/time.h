#pragma once

#include <chrono>

namespace lightning
{

struct delay_for
{
    template<typename _rep, typename _period>
    explicit delay_for(const std::chrono::duration<_rep, _period>& rtime) : rtime_(rtime) {}

    operator std::chrono::nanoseconds()
    {
        return rtime_;
    }
private:
    std::chrono::nanoseconds rtime_;
};

}