#pragma once

#include <lightning/gl_types.h>

namespace lightning
{

void gl_init(int* argc, char** argv);

struct gl_window
{
    gl_window(const gl_rect& dims, const char* title);

    ~gl_window();

private:
    int handle_;
    // TODO save context or surface

    static void on_display();
};

} // namespace lightning