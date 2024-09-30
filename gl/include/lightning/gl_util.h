#pragma once

#include <lightning/util.h>

#include <source_location>
#include <string_view>

namespace std
{

template<>
struct hash<std::source_location>
{
    size_t operator()(const std::source_location location) const noexcept
    {
        return lightning::hash_combine(location.file_name(), location.function_name(), location.line(), location.column());
    }
};

constexpr bool operator==(const std::source_location& lhs, const std::source_location& rhs)
{
    return std::string_view{lhs.file_name()} == rhs.file_name()
        && std::string_view{lhs.function_name()} == rhs.function_name()
        && lhs.line() == rhs.line()
        && lhs.column() == rhs.column();
}

} // namespace std