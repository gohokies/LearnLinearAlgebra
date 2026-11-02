find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(gl3w CONFIG REQUIRED)

add_executable(glComputeDemo main.cpp)

target_include_directories(glComputeDemo PRIVATE OpenGL::GL glfw unofficial::gl3w::gl3w)
target_link_libraries(glComputeDemo PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(glComputeDemo PRIVATE glfw)
target_link_libraries(glComputeDemo PRIVATE unofficial::gl3w::gl3w)