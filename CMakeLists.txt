cmake_minimum_required(VERSION 3.28)
project(lightning)

set(CMAKE_CXX_STANDARD 20)

add_library(lightning
    src/lightning.cpp
    src/async_context.cpp
    src/exception.cpp
    src/io_time.cpp
)

target_include_directories(lightning PUBLIC include)

add_subdirectory(examples)