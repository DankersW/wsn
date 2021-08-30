cmake_minimum_required(VERSION 3.10...3.19)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(
	bt_gateway
	VERSION "0.0.1"
	DESCRIPTION "Thread gateway"
	LANGUAGES CXX
)

# TODO: Find out how to add subdirectories in Zephyr with CMake, cleaning up this code
target_sources(app PRIVATE 
	src/main.c
	src/cli/cli_shell.c
	src/cli/cli_definitions.c
	src/cli/handlers/misc_cmd_handlers.c
)

target_include_directories(app PRIVATE 
	src/cli
	src/cli/handlers
)
