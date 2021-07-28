#!/bin/bash

base_dir=$(readlink -f $(dirname $0)/../..)
image_name=dankersw/zephyr_builder
image_tag="0.1"

fail() {
    echo "##### FAIL: $1"
    exit 1
}

docker run \
    --rm \
	--user $UID:$UID \
	--volume ${base_dir}:/work \
	${extra_options} \
    ${image_name}:${image_tag} $@ \
        || fail "running docker"
