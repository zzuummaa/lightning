set(OPENGL_LIBRARIES OpenGL::GL OpenGL::GLU GLUT::GLUT)
set(GTK_LIBRARIES PkgConfig::GTK4)

add_library(lightning_gl
    src/gl_application.cpp
    src/gl_context.cpp
    src/gl_window.cpp
    src/gl_loop.cpp
)

target_include_directories(lightning_gl PUBLIC include)
target_link_libraries(lightning_gl PUBLIC lightning_base ${OPENGL_LIBRARIES} ${GTK_LIBRARIES})

add_subdirectory(examples)

unset(OPENGL_LIBRARIES)
unset(GTK_LIBRARIES)