# WSN

Repository containing several WSN node projects. All nodes use Zephyr RTOS and the Nordic nrf52840 chip.

## Getting started

### Toolchain

Setting up the toolchain and the development environment is done by executing the ```sdk/bootstrap.sh``` script from the root directory.

```sh
./scripts/toolchain/bootstrap.sh
```

Executing a command in the toolchain is done by invoking the ```toolchain/run.sh``` script together with the command you want to execute from the project root.

```sh
./scripts/toolchain/run.sh echo "hello from the other side" || exit 1
```

In contrainy to executing a command it is also possible to open up a shell into the toolchain.

```sh
./scripts/toolchain/run.sh /bin/bash
```

### Building and flashing

Building and flashing any app or sample is done with the following command. One can specify their app via the ```-p PATH``` parameter. The script is called form the root directory which provides the added benifit of having tab completion.

```sh
./scripts/build_and_flash.sh -p sample/blinky
```

The default configuration for flashing is set to flash the ```NRF52840 dongle```. Inorder to flash another board (like the ```NRF52840_DK```) the ```-b BOARD``` parameter needs to be provided.

## Chips

The repo is primarly build for the ```NRF52840``` chip but due to the awesomeness of Zephyr it is easy and straight forward to addapt the samples and apps for other chips and boards.

### Supported boards

| Manufacturer | Chip     | Board  | Architecture | Zephyr board name       |
|--------------|----------|--------|--------------|-------------------------|
| Nordic       | NRF52840 | Dongle | ARM          | nrf52840dongle_nrf52840 |
| Nordic       | NRF52840 | DK     | ARM          | nrf52840dk_nrf52840     |
