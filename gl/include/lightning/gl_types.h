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
    int width = 0;
    int height = 0;

    bool operator==(const gl_size &other) const
    {
        return this->width == other.width
            && this->height == other.height;
    }
};

struct gl_pos
{
    int x = 0;
    int y = 0;

    bool operator==(const gl_pos &other) const
    {
        return this->x == other.x
            && this->y == other.y;
    }
};

struct gl_rect
{
    gl_pos pos;
    gl_size size;

    bool operator==(const gl_rect &other) const
    {
        return this->pos == other.pos
            && this->size == other.size;
    }
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