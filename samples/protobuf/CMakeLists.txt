cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(protobuf)

#nanopb_generate_cpp(proto_sources proto_headers RELPATH .
#    src/simple.proto
#)

#set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../extra)
#find_package(Nanopb REQUIRED)

target_sources(app PRIVATE 
    src/main.c
    src/pb_common.c
    src/pb_decode.c
    src/pb_encode.c
    src/simple.pb.c
    #../../home-automation-ipc/generated/c/wsn.pb-c.c
   
)

target_include_directories(app PRIVATE
    src
   #../../home-automation-ipc/generated/c/
)
