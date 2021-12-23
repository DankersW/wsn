cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(protobuf)

target_sources(app PRIVATE 
    src/main.c

    ../../home-automation-ipc/generated/nanopb/pb_common.c
    ../../home-automation-ipc/generated/nanopb/pb_decode.c
    ../../home-automation-ipc/generated/nanopb/pb_encode.c
    ../../home-automation-ipc/generated/nanopb/wsn.pb.c 
)

target_include_directories(app PRIVATE
    src
   ../../home-automation-ipc/generated/nanopb/
)
