#!/bin/bash

VERSION=$(cat VERSION)
ARCH=$(uname -m)
DST=vnx-base

rm -rf $DST

./install.sh -DCMAKE_INSTALL_PREFIX:PATH=$PWD/$DST

tar czf $ARCH/${DST}-$VERSION-$ARCH.tar.gz $DST

rm -rf $DST

