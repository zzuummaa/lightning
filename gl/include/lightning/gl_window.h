#pragma once

#include <lightning/gl_types.h>

namespace lightning
{

void gl_init(int* argc, char** argv);

struct gl_context;

struct gl_window
{
    using surface_type = std::function<void(gl_context&)>;

    gl_window(const gl_rect& dims, const char* title, gl_context& context);

    ~gl_window();

    template<typename _surface>
    void set_surface(_surface&& surface)
    {
        surface_ = std::forward<_surface>(surface);
    }

    surface_type& get_surface()
    {
        return surface_;
    }

    int handle() const
    {
        return handle_;
    }

private:
    int handle_;
    gl_context& context_;
    surface_type surface_;

    static void on_display();
};

} // namespace lightning