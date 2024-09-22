#include <lightning/async_task.h>

#include <iostream>

using namespace lightning;

async_task<> printer()
{
    while (true)
    {
        std::cout << "Hello, World!" << std::endl;
        co_await std::suspend_always{};
    }
}

int main()
{
    // Create coroutine in resume state, do first print
    auto task = printer();

    // Resume coroutine, do second print
    task.resume();

    // Resume coroutine, do third print
    task.resume();

    return 0;
}
