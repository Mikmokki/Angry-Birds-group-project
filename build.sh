#!/usr/bin/env bash

git submodule update --init
rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
