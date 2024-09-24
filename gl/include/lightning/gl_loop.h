#pragma once

namespace lightning
{

struct gl_loop
{
    static void poll();

    static void poll_once();
};

} // namespace lightning