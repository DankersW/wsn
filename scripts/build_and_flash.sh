#!/bin/bash

help() {
    echo "FAIL: $@"
    echo "Usage: $0 -t type -a app" 1>&2
    exit 1
}

while getopts "a:t:" opt; do
    case "${opt}" in
        a)
            APP=$OPTARG
            ;;
        t)
            if [ $OPTARG = "sample" ]; then TYPE="samples"
            elif [ $OPTARG = "app" ]; then TYPE="app"
            fi
            ;;
        *)
            help illegal option "$OPTARG"
            ;;
    esac
done
shift $((OPTIND -1))

if [ -z "$APP" ]; then
    help Specify sample application
fi

BOARD="nrf52840dongle_nrf52840"
HEX_FILE="build/zephyr/zephyr.hex"
SRC_LOCATION="$TYPE/$APP"

echo "Building application $APP"
./scripts/toolchain.sh west build -p -b $BOARD $SRC_LOCATION || exit 1

echo "Flashing hex"
PKG_NAME="$APP.zip" 
nrfutil pkg generate --hw-version 52 --sd-req=0x00 --application $HEX_FILE --application-version 1 $PKG_NAME
nrfutil dfu usb-serial -pkg $PKG_NAME -p /dev/ttyACM0
rm $PKG_NAME
