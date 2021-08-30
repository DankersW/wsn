#
# Copyright (c) 2020 Nordic Semiconductor ASA
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#
cmake_minimum_required(VERSION 3.13.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
list(APPEND BOARD_ROOT /work)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(openthread_coap_client)

target_sources(app PRIVATE 
	src/main.c
	src/coap_client_utils.c
)

target_include_directories(app PUBLIC src)
