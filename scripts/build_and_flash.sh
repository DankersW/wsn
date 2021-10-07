#!/bin/bash

HEX_FILE="build/zephyr/zephyr.hex"
BOARD="nrf52840dongle_nrf52840"


help() {
    echo "FAIL: $@"
    echo "Usage: $0 -p path_to_app -b board[dk, dongle]" 1>&2
    exit 1
}

while getopts "p:b:" opt; do
    case "${opt}" in
        p)
            APP=$OPTARG
            ;;
        b)
            if [ $OPTARG = "dk" ]; then
                BOARD="nrf52840dk_nrf52840"
            else
                BOARD="nrf52840dongle_nrf52840"
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


echo "Building application $APP"
./scripts/toolchain/run.sh west build -p -b $BOARD $APP || exit 1

echo "Flashing hex"
if [ $BOARD = "nrf52840dongle_nrf52840" ]; then
    APP_NAME="$(cut -d'/' -f2 <<<$APP)"
    PKG_NAME="$APP_NAME.zip" 
    nrfutil pkg generate --hw-version 52 --sd-req=0x00 --application $HEX_FILE --application-version 1 $PKG_NAME
    nrfutil dfu usb-serial -pkg $PKG_NAME -p /dev/ttyACM0
    rm $PKG_NAME
elif [ $BOARD = "nrf52840dk_nrf52840" ]; then
    ./scripts/toolchain/run.sh west flash
fi

