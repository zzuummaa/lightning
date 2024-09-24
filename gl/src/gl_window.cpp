#include <lightning/gl_window.h>
#include <lightning/exception.h>

#include <lightning/opengl/glut.h>

#include <map>
#include <mutex>

namespace lightning
{

void gl_init(int* argc, char** argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
}

static thread_local std::map<int, gl_window*> windows;

void gl_window::on_display()
{
    int handle = expect(glutGetWindow(), 0, std::greater{});
    gl_window* window = expect(windows.find(handle), std::end(windows), std::not_equal_to{})->second;

    // TODO paint surface
}

gl_window::gl_window(const gl_rect& dims, const char* title)
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

} // namespace lightning