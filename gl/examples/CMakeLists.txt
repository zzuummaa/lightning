add_executable(opengl opengl.cpp)
target_link_libraries(opengl ${OPENGL_LIBRARIES})

add_executable(gtk_button gtk_button.cpp)
target_link_libraries(gtk_button ${GTK_LIBRARIES})

add_executable(view_model view_model.cpp)
target_link_libraries(view_model lightning_gl)
