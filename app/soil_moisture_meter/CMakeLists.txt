cmake_minimum_required(VERSION 3.8.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND BOARD_ROOT /work)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(
	moisture_sensor
	VERSION "0.0.1"
	DESCRIPTION "Wireless sensor network to detect the soil moisture level"
	LANGUAGES CXX
)

target_sources(app PRIVATE
	src/main.c

	src/bt/mesh.c

	src/bt/models/model_definitions.c
	src/bt/models/led_handlers.c
	src/bt/models/attention_handlers.c
)

target_include_directories(app PRIVATE 
	src/bt
	src/bt/models
)