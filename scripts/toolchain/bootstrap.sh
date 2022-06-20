#!/bin/bash

DOCKER_IMAGE="wsn_toolchain"
TOOLCHAIN_TAG=`./scripts/toolchain/version.sh`

echo "Install 3th party tools"
pip3 install -r requirements.txt

echo "INIT SDK"
mkdir -p ncs
west update || exit 1

echo "Building build docker"
docker build --tag dankersw/$DOCKER_IMAGE:$TOOLCHAIN_TAG -f docker/toolchain.dockerfile . || exit 1

echo "INIT SDK"
./scripts/toolchain/run.sh west update || exit 1

echo "Fetching protobuf messages"
git submodule init
git submodule update
