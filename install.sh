#!/bin/bash

mkdir -p build

cd build

cmake -DARCH=$(uname -m) $@ ..

make install

cd ..

rm -rf build

