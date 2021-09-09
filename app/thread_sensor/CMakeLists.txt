cmake_minimum_required(VERSION 3.13.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND BOARD_ROOT /work)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(openthread_coap_server)

target_sources(app PRIVATE 
    src/main.c
    src/ot_coap_utils.c
)

target_include_directories(app PRIVATE
    src
)
