# Protobuf

Example how to use protobuf to serialize and deseialize a message

## Building & Flashing

```sh
./scripts/toolchain.sh ./scripts/execute_sample.sh -s usb_cli -b dongle -f
# Press the reset button the dongle inorder to go into the "programming" mode
nrfutil dfu usb-serial -pkg samples/usb_cli/usb_cli.zip -p /dev/ttyACM0
```

## Testing/Running

```sh
screen /dev/ttyACM0
```
