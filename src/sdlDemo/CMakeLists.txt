find_package(OpenGL REQUIRED)

find_package(SDL2 CONFIG REQUIRED)

add_executable(sdlDemo main.cpp)

target_link_libraries(sdlDemo PRIVATE OpenGL::GL OpenGL::GLU)

target_include_directories(sdlDemo
    PRIVATE
    ${OPENGL_INCLUDE_DIR} 
    ${SDL2_INCLUDE_DIR} 
    $<TARGET_PROPERTY:SDL2::SDL2,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(sdlDemo
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
