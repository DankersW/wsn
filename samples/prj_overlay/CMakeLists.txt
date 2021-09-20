cmake_minimum_required(VERSION 3.13.1)

set(OVERLAY_CONFIG 
    "config/usb_overlay.conf config/logging.conf"
)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})


project(prj_overlay)

target_sources(app PRIVATE src/main.c)
