#!/bin/bash

VERSION=$(cat VERSION)
ARCH=$(uname -m)
DIST=$(cat ~/DIST)
NAME=${PWD##*/}
DST=$NAME-$VERSION-$ARCH-$DIST

rm -rf build
mkdir build
cd build

cmake -DARCH=$(uname -m) -DDIST=$(cat ~/DIST) -DCMAKE_INSTALL_PREFIX:PATH=$PWD/usr ..

make install

fpm -t rpm -n $NAME -v $VERSION -m "automyinc@gmail.com" -s dir usr/

cd ..

mv build/$NAME*.rpm $ARCH/$DST.rpm

rm -rf build

