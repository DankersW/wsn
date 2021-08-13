cmake_minimum_required(VERSION 3.8.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND BOARD_ROOT /work)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(NONE)

include_directories(src/some_module)
add_subdirectory(src/some_module)


target_sources(app PRIVATE
	src/main.c)

target_include_directories(app PRIVATE 
	src
)