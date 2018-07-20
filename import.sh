#!/bin/bash

SRC=$1

rsync -av --delete $SRC/generated/include/vnx/ generated/include/vnx/
rsync -av --delete $SRC/include/vnx/ include/vnx/
rsync -av --delete $SRC/interface/ interface/vnx/
rsync -av --delete $SRC/modules/ modules/

