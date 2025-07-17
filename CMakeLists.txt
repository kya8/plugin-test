cmake_minimum_required(VERSION 3.10.0)
project(plugin-test VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

# Do not export symbols by default
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_VISIBILITY_PRESET hidden)

add_compile_options("$<IF:$<CXX_COMPILER_ID:MSVC>,/W4,-Wall;-Wextra;-pedantic>")

add_executable(plugin-test dso.hpp dso.cpp main.cpp)
target_link_libraries(plugin-test PRIVATE ${CMAKE_DL_LIBS})

add_library(plugin SHARED plugin.cpp)
target_compile_definitions(plugin PRIVATE PLUGIN_SOURCE)
set_target_properties(plugin PROPERTIES PREFIX "")
