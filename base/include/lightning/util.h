#pragma once

#include <functional>

namespace lightning
{

template<typename _t>
using hash = std::hash<_t>;

template<typename ..._args>
size_t hash_combine(_args&& ...args)
{
    return (std::hash<_args>{}(std::forward<_args>(args)) ^ ...);
}

} // namespace lightning