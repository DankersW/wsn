# WSN

Repository containing several WSN node projects. All nodes use Zephyr RTOS and the Nordic nrf52840 dongle MDK.

## Getting started

```sh
./scripts/sdk/bootstrap.sh
```

Building and flashing any app or sample is done with the following command. One can specify their app via the ```-p``` parameter. The script is called form the root directory which provides the added benifit of tab completion.

```sh
./scripts/build_and_flash.sh -p app/soil_moisture_meter
```


### Toolchain

Manual access to the toolchain can be provided via:

```sh
./scripts/toolchain.sh /bin/bash
```
