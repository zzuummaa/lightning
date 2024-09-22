#include <lightning/async_task.h>
#include <lightning/async_context.h>
#include <lightning/time.h>

#include <iostream>

using namespace lightning;

async_task<> periodic_printer(async_context& context)
{
    while (true)
    {
        std::cout << "Hello, World!" << std::endl;
        co_await delay_for(context, std::chrono::seconds(1));
    }
}

int main()
{
    async_context context(2);

    // Create coroutine in resume state, do first print
    auto task = periodic_printer(context);

    // Waiting for delay timeout elapsed, do second print
    context.poll(3000);

    // Waiting for delay timeout elapsed, do third print
    context.poll(3000);

    return 0;
}
