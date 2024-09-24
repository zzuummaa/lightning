#include <lightning/exception.h>

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sstream>

#define BT_BUF_SIZE 100

namespace lightning {

std::optional<std::string> backtrace()
{
    int nptrs;
    void *buffer[BT_BUF_SIZE];
    char **strings;

    nptrs = ::backtrace(buffer, BT_BUF_SIZE);

    if (nptrs < 1)
    {
        return std::nullopt;
    }

    strings = backtrace_symbols(buffer, nptrs);
    if (strings == NULL)
    {
        return std::nullopt;
    }

    std::stringstream bt;
    for (size_t j = 0; j < nptrs - 1; j++)
    {
        bt << strings[j] << std::endl;
    }
    bt << strings[nptrs - 1];

    free(strings);

    return bt.str();
}

}