SET(GL_LIBRARIES OpenGL::GL GLUT::GLUT)

add_library(lightning_gl
    src/gl_context.cpp
    src/gl_window.cpp
    src/gl_loop.cpp
)

target_include_directories(lightning_gl PUBLIC include)
target_link_libraries(lightning_gl PUBLIC lightning_base ${GL_LIBRARIES})

add_subdirectory(examples)

UNSET(GL_LIBRARIES)