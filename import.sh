#!/bin/bash

SRC=$1

git checkout master
git pull

mkdir -p lib/
mkdir -p bin/

rsync -av --delete $SRC/doc/pages/ doc/pages/
rsync -av --delete $SRC/doc/tools/ doc/tools/
rsync -av --delete $SRC/doc/tutorials/ doc/tutorials/
rsync -av --delete $SRC/generated/include/vnx/ generated/include/vnx/
rsync -av --delete $SRC/include/vnx/ include/vnx/
rsync -av --delete $SRC/interface/ interface/vnx/
rsync -av --delete $SRC/modules/ modules/

cp $SRC/VERSION VERSION
cp $SRC/CHANGELOG.md ./
cp $SRC/doxygen.cfg ./
cp $SRC/doc/mainpage.h doc/
cp $SRC/build/libvnx_base* lib/
cp $SRC/build/tools/vnxclose bin/
cp $SRC/build/tools/vnxdump bin/
cp $SRC/build/tools/vnxread bin/
cp $SRC/build/tools/vnxrouter bin/
cp $SRC/build/tools/vnxtimeserver bin/
cp $SRC/build/tools/vnxtopic bin/
cp $SRC/build/tools/vnxrecord bin/
cp $SRC/build/tools/vnxplay bin/
cp $SRC/build/tools/vnxgraph bin/

