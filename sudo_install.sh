#!/bin/bash

mkdir -p build

cd build

cmake -DARCH=$(uname -m) $@ ..

sudo make install

cd ..

sudo rm -rf build

