#include <lightning/async_task.h>
#include <lightning/io/io_context.h>
#include <lightning/io/io_awaitable.h>

#include <iostream>

using namespace lightning;

async_task<io_context> periodic_printer(io_context&)
{
    while (true)
    {
        std::cout << std::chrono::system_clock::now() << ": Hello, World!" << std::endl;
        co_await delay_for(std::chrono::seconds(1));
    }
}

int main()
{
    io_context context(2);

    // Create coroutine in resume state, do first print
    auto task = periodic_printer(context);

    // Waiting for delay timeout elapsed, do second print
    context.poll(3000);

    // Waiting for delay timeout elapsed, do third print
    context.poll(3000);

    return 0;
}
