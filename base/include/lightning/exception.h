#pragma once

#include <functional>
#include <stdexcept>
#include <optional>

namespace lightning
{

std::optional<std::string> backtrace();

template<typename T, typename R, typename TComp = std::equal_to<std::remove_reference_t<T>>>
T&& expect(T&& left, R&& right, TComp comp = {})
{
    if (comp(std::forward<T>(left), std::forward<R>(right))) return std::forward<T>(left);

    const auto bt = backtrace();
    throw std::runtime_error(bt ? *bt : "");
}

inline bool expect(bool success)
{
    return expect(success, true);
}

inline int expect_posix_ok(int res)
{
    return expect(res, -1, std::not_equal_to<int>{});
}

}