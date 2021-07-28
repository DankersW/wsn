#!/bin/bash

TAG="0.1"
DOCKER_IMAGE="zephyr_builder"
DOCKER_REGISTY="zephyr_builder"

docker build --tag dankersw/$DOCKER_REGISTY:$TAG -f docker/zephyr_builder.dockerfile .
docker login -u dankersw
docker tag $DOCKER_IMAGE:$TAG dankersw/$DOCKER_REGISTY:$TAG
docker push dankersw/$DOCKER_REGISTY:$TAG
