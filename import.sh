#!/bin/bash

SRC=$1
ARCH=$(uname -m)
DIST=$(cat ~/DIST)

mkdir -p $ARCH/$DIST/lib/
mkdir -p $ARCH/$DIST/bin/

cp $SRC/VERSION VERSION

rsync -av --delete $SRC/generated/include/vnx/ generated/include/vnx/
rsync -av --delete $SRC/include/vnx/ include/vnx/
rsync -av --delete $SRC/interface/ interface/vnx/
rsync -av --delete $SRC/modules/ modules/

cp $SRC/doxygen.cfg ./
cp $SRC/build/libvnx_base* $ARCH/$DIST/lib/
cp $SRC/build/tools/vnxclose $ARCH/$DIST/bin/
cp $SRC/build/tools/vnxdump $ARCH/$DIST/bin/
cp $SRC/build/tools/vnxread $ARCH/$DIST/bin/
cp $SRC/build/tools/vnxrouter $ARCH/$DIST/bin/
cp $SRC/build/tools/vnxtimeserver $ARCH/$DIST/bin/
cp $SRC/build/tools/vnxtopic $ARCH/$DIST/bin/

