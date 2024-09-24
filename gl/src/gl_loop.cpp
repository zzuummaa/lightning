#include <lightning/gl_loop.h>
#include <lightning/opengl/glut.h>

namespace lightning
{

void gl_loop::poll()
{
    glutMainLoop();
}

void gl_loop::poll_once()
{
    glutMainLoopEvent();
}

} // namespace lightning
