#!/bin/bash

INSTALL_PREFIX=${1:-/usr/local}

mkdir -p build

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX -B build -S . -DBUILD_EXAMPLES=OFF
sudo cmake --build build --target uninstall

echo "WeNet library uninstalled successfully!"
