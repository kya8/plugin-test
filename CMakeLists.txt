cmake_minimum_required(VERSION 3.10.0)
project(plugin-test VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_EXTENSIONS OFF)

# Do not export symbols by default
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_VISIBILITY_PRESET hidden)

add_compile_options("$<IF:$<CXX_COMPILER_ID:MSVC>,/W4,-Wall;-Wextra;-pedantic>")

add_library(plugin-common INTERFACE plugin_common.h export.h)
target_include_directories(plugin-common INTERFACE .)

add_executable(plugin-test dso.hpp dso.cpp main.cpp)
target_link_libraries(plugin-test PRIVATE ${CMAKE_DL_LIBS} plugin-common)

file(GLOB PLUGIN_SOURCES
"plugins/*.c"
"plugins/*.cpp"
)

foreach(src_file IN LISTS PLUGIN_SOURCES)
    get_filename_component(plugin_name ${src_file} NAME_WE)
    add_library(${plugin_name} MODULE ${src_file})
    target_compile_definitions(${plugin_name} PRIVATE PLUGIN_SOURCE)
    target_link_libraries(${plugin_name} PRIVATE plugin-common)
    set_target_properties(${plugin_name}
        PROPERTIES PREFIX ""
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/plugins"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/plugins")
endforeach()
