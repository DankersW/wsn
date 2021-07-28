#!/bin/bash

BUILDER_TAG="0.1"
DOCKER_IMAGE="wsn_toolchain"
TOOLCHAIN_TAG=`./scripts/toolchain/version_toolchain.sh`

echo "INIT SDK"
./scripts/sdk/run_bootstrap_docker.sh ./scripts/sdk/sdk_init.sh || exit 1

echo "Copy requirements files"
rm -fr _requirements || exit 1
mkdir -p _requirements/zephyr _requirements/nrf _requirements/bootloader || exit 1
cp ncs/zephyr/scripts/*.txt _requirements/zephyr || exit 1
cp ncs/nrf/scripts/*.txt _requirements/nrf || exit 1
cp ncs/bootloader/mcuboot/scripts/*.txt _requirements/bootloader || exit 1

echo "Building build docker"
docker build --tag dankersw/$DOCKER_IMAGE:$TOOLCHAIN_TAG -f docker/toolchain.dockerfile . || exit 1

echo "Install 3th party tools"
pip3 install -r requirements.txt

echo "Cleaning up"
rm -fr _requirements
