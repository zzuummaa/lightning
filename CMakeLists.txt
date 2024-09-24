cmake_minimum_required(VERSION 3.28)
project(lightning)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL)
find_package(GLUT)

add_subdirectory(base)
add_subdirectory(io)

if (OPENGL_FOUND AND GLUT_FOUND)
    add_subdirectory(gl)
endif()
