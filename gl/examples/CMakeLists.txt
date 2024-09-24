add_executable(opengl opengl.cpp)
target_link_libraries(opengl ${GL_LIBRARIES})

add_executable(view_model view_model.cpp)
target_link_libraries(view_model lightning_gl)