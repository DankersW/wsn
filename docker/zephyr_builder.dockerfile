FROM ubuntu:20.04

RUN apt-get -y update && \
    apt-get -y upgrade && \
    DEBIAN_FRONTEND=noninteractive \
    apt-get install -y \
	    cmake \
	    git \
	    gperf \
	    libfdt1 \
	    libncurses5 \
	    libncurses5-dev \
	    libyaml-dev \
	    ninja-build \
	    python3-pip \
	    python3-setuptools \
	    wget \
    && \
    apt-get -y remove python-cryptography python3-cryptography && \
    apt-get -y clean && apt-get -y autoremove

RUN mkdir -p /usr/local \
    && cd /usr/local \
    && wget -qO- \
    gnuarmemb_toolchain.tar.bz2 'https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2?revision=108bd959-44bd-4619-9c19-26187abf5225&la=en&hash=E788CE92E5DFD64B2A8C246BBA91A249CB8E2D2D' \
    | tar xj && \
    mkdir -p /tmp/debs && \
    cd /tmp/debs && \
    # Device Tree Compiler 1.5.1 (for Ubuntu 20.04)
    # Releases: https://git.kernel.org/pub/scm/utils/dtc/dtc.git
    wget -q http://archive.ubuntu.com/ubuntu/pool/main/d/device-tree-compiler/device-tree-compiler_1.5.1-1_amd64.deb && \
    # Nordic command line tools
    # Releases: https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Command-Line-Tools/Download
    wget -qO- https://www.nordicsemi.com/-/media/Software-and-other-downloads/Desktop-software/nRF-command-line-tools/sw/Versions-10-x-x/10-12-1/nRFCommandLineTools10121Linuxamd64.tar.gz \
    | tar xz && \
    dpkg -i *.deb && \
    cd .. && \
    rm -fr /tmp/debs


RUN pip3 install -U pip && \
    pip3 install -U setuptools && \
    pip3 install cmake wheel && \
    pip3 install -U west

ENV ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb
ENV ZEPHYR_BASE=/work/ncs/zephyr
ENV BOARD_ROOT=/work

ENV GNUARMEMB_TOOLCHAIN_PATH="/usr/local/gcc-arm-none-eabi-9-2019-q4-major"
ENV PATH="${GNUARMEMB_TOOLCHAIN_PATH}/bin:${PATH}"

ENV LC_ALL=C.UTF-8
ENV LANG=C.UTF-8
ENV XDG_CACHE_HOME=/work/.cache

WORKDIR /work
