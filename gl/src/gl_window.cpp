#include <iostream>
#include <lightning/exception.h>
#include <lightning/gl_context.h>
#include <lightning/gl_window.h>

#include <lightning/opengl/glut.h>

#include <unordered_map>
#include <mutex>

namespace lightning
{

void gl_init(int* argc, char** argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
}

static thread_local std::unordered_map<int, gl_window*> windows;

void gl_window::on_display()
{
    int handle = expect(glutGetWindow(), 0, std::greater{});
    gl_window* window = expect(windows.find(handle), std::end(windows), std::not_equal_to{})->second;

    if (window->surface_)
    {
        window->surface_(window->context_);
    }
}

gl_window::gl_window(
    const gl_rect& dims, const char* title, gl_context& context)
    : context_(context)
{
    glutInitWindowPosition(dims.pos.x, dims.pos.y);
    glutInitWindowSize(dims.size.width, dims.size.height);

    handle_ = glutCreateWindow(title);
    expect(windows.try_emplace(handle_, this).second);

    glutDisplayFunc(on_display);
}

gl_window::~gl_window()
{
    glutDestroyWindow(handle_);
    expect(windows.erase(handle_), 1);
}

void gl_window::set_surface(const surface_type& surface) { surface_ = surface; }

gl_window::surface_type& gl_window::get_surface() { return surface_; }

} // namespace lightning