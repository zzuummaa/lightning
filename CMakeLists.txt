cmake_minimum_required(VERSION 3.28)
project(lightning)

set(CMAKE_CXX_STANDARD 20)

# Use graphic libraries for building UI-s
find_package(OpenGL)
find_package(GLUT)

find_package(PkgConfig)
pkg_check_modules(GTK4 IMPORTED_TARGET gtk4)

add_subdirectory(base)
add_subdirectory(io)

if (OPENGL_FOUND AND GLUT_FOUND AND GTK4_FOUND)
    add_subdirectory(gl)
endif()
