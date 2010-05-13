#!/bin/bash

PACKAGES="libcwiid1-dev libboost-thread-dev"
CMAKE_PARAMS="-C../GCCSetup.cmake -DCMAKE_INSTALL_PREFIX=/usr"
BUILD_TYPES="debug release"


if ! dpkg -l $PACKAGES >/dev/null
then
    echo "Will install packages: $PACKAGES"
    sudo apt-get install $PACKAGES
fi

for x in $BUILD_TYPES
do
    mkdir -p "$x"

    pushd "$x"
    cmake $CMAKE_PARAMS "-DCMAKE_BUILD_TYPE=$x" ..
    popd
done
