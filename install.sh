#!/bin/bash

mkdir -p build

cd build

cmake -DARCH=$(uname -m) -DDIST=$(cat ~/DIST) $@ ..

make install

cd ..

rm -rf build

