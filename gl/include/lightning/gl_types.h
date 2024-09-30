#pragma once

namespace lightning
{

struct gl_context;
struct gl_window;

using gl_object_handle = void*;

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

} // namespace lightning