cmake_minimum_required(VERSION 3.15)

project(mandelbrot_set)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(main "${SOURCES}")
target_link_libraries(main glfw glad)