FROM dankersw/zephyr_builder:0.1.1

ARG DEBIAN_FRONTEND=noninteractive

WORKDIR /work

COPY ncs /work/ncs

RUN cd /work/ncs && \
    pip3 install -r zephyr/scripts/requirements.txt && \
    pip3 install -r nrf/scripts/requirements.txt && \
    pip3 install -r bootloader/mcuboot/scripts/requirements.txt && \
    cd .. && \
    rm -fr ncs
