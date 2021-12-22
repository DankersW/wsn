cmake_minimum_required(VERSION 3.13.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OVERLAY_CONFIG 
    "config/ot_overlay.conf config/usb_overlay.conf "
)

list(APPEND BOARD_ROOT /work)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(thread_sensor)

target_sources(app PRIVATE 
    src/main.c

    src/coap/ot_coap_utils.c
    src/coap/ot_coap.c
    src/coap/coap_message_definition.c
    
    src/sensor/die_temp.c

    src/protobuf/proto_serializer.c

    ../../home-automation-ipc/generated/nanopb/pb_common.c
    ../../home-automation-ipc/generated/nanopb/pb_decode.c
    ../../home-automation-ipc/generated/nanopb/pb_encode.c
    ../../home-automation-ipc/generated/nanopb/wsn.pb.c
)

target_include_directories(app PRIVATE
    src
    src/coap
    src/sensor
    src/protobuf

    ../../home-automation-ipc/generated/nanopb/
)
