#pragma once

#include <functional>

namespace lightning
{

struct gl_context;
struct gl_window;

using gl_window_handle = void*;
using gl_app_handle = void*;

struct gl_size
{
    int width;
    int height;
};

struct gl_pos
{
    int x;
    int y;
};

struct gl_rect
{
    gl_pos pos;
    gl_size size;
};

struct gl_button
{
    template <typename _on_click>
    explicit gl_button(const gl_rect& dims, _on_click&& on_click = [] {})
        : dims_(dims), on_click_(std::forward<_on_click>(on_click))
    {
    }

private:
    gl_rect dims_;
    std::function<void()> on_click_;
};

struct gl_box
{
    explicit gl_box(const gl_rect& dims) : dims_(dims)
    {
    }

private:
    gl_rect dims_;
};

} // namespace lightning