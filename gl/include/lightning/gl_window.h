#pragma once

#include <lightning/gl_types.h>
#include <lightning/gl_object.h>

namespace lightning
{

void gl_init(int* argc, char** argv);

struct gl_window : gl_object
{
    gl_window(gl_context& context, const gl_rect& dims, const char* title);

    gl_window(const gl_window&) = delete;

    void operator()();

private:
    gl_rect dims_;
    std::string title_;
    gl_window_handle handle_;

    static void on_display();
};

} // namespace lightning