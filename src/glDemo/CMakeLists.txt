find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(glDemo main.cpp)

target_link_libraries(glDemo PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(glDemo PRIVATE glfw)
