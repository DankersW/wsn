#!/bin/bash

base_dir=$(readlink -f $(dirname $0)/..)
image_name="dankersw/wsn_toolchain"
image_tag=`./scripts/toolchain/version_toolchain.sh`

fail() {
    echo "##### FAIL: $1"
    exit 1
}

docker run \
    --rm \
	--user $UID:$UID \
	--volume ${base_dir}:/work \
	-it --privileged \
    ${image_name}:${image_tag} $@ \
        || fail "running docker"
