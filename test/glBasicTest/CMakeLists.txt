find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(glBasicTest main.cpp)

target_include_directories(glBasicTest PRIVATE ${OPENGL_INCLUDE_DIR})
target_link_libraries(glBasicTest PRIVATE GTest::gtest GTest::gtest_main ${OPENGL_LIBRARIES})
target_link_libraries(glBasicTest PRIVATE glfw)

add_test(glBasicTest glBasicTest)