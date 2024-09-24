add_library(lightning_io
    src/io_context.cpp
    src/io_time.cpp
)

target_link_libraries(lightning_io PUBLIC lightning_base)
target_include_directories(lightning_io PUBLIC include)

add_subdirectory(examples)