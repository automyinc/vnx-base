#!/bin/bash

cd $(dirname "$0")

rm -rf doc/doxygen

mkdir -p doc/doxygen

doxygen doxygen.cfg

