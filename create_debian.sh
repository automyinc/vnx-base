#!/bin/bash

VERSION=$(cat VERSION)
ARCH=$(uname -m)
DST=${PWD##*/}-$VERSION-$ARCH

rm -rf $DST
mkdir -p $DST/DEBIAN
mkdir -p $DST/usr

echo "Version: $VERSION" >> $DST/DEBIAN/control
cat $ARCH/debian/control >> $DST/DEBIAN/control
cat debian/control >> $DST/DEBIAN/control

./install.sh -DCMAKE_INSTALL_PREFIX:PATH=$PWD/$DST/usr

dpkg-deb --build $DST

mv ${DST}.deb $ARCH/

rm -rf $DST

