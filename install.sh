#!/bin/bash
INSTALL_PREFIX=${1:-/usr/local}
mkdir -p build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX -B build -S . -DBUILD_EXAMPLES=OFF -DBUILD_TESTS=OFF
sudo cmake --build build --target uninstall
sudo cmake --build build --config Release --target install
echo "WeNet library installed successfully!"
