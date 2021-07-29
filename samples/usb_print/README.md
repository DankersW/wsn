# USB CLI

CLI shell examples showcases a barebone cli shell over USB. It is developed and tested mainly for the nrf52840 dongle. The shell comes with a handfull of features as well as tab-completion.

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
