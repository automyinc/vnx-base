#!/bin/bash

SRC=$1
ARCH=$(uname -m)

mkdir -p $ARCH/bin
mkdir -p $ARCH/lib

cp $SRC/VERSION VERSION

rsync -av --delete $SRC/generated/include/vnx/ generated/include/vnx/
rsync -av --delete $SRC/include/vnx/ include/vnx/
rsync -av --delete $SRC/interface/ interface/vnx/
rsync -av --delete $SRC/modules/ modules/

cp $SRC/build/libvnx_base* $ARCH/lib/
cp $SRC/build/tools/vnxclose $ARCH/bin/
cp $SRC/build/tools/vnxdump $ARCH/bin/
cp $SRC/build/tools/vnxread $ARCH/bin/
cp $SRC/build/tools/vnxrouter $ARCH/bin/
cp $SRC/build/tools/vnxtimeserver $ARCH/bin/

