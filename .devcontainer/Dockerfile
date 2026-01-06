FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    software-properties-common \
    cmake \
    gdb \
    git \
    valgrind \
    vim \
    wget \
    gcc-14 \
    g++-14 \
    libgtest-dev \
    libgmock-dev \
    clang-format \
    clang-tidy \
    && rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-14 100

WORKDIR /workspaces/SharedMemBuffer