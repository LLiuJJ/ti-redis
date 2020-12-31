#!/bin/bash

set -xe


SCRIPTPATH="$( cd "$(dirname "$0")" ; pwd -P )"
SRCPATH=$(cd $SCRIPTPATH/..; pwd -P)
NPROC=$(nproc || grep -c ^processor /proc/cpuinfo)

if [ -d "$SRCPATH/third_party/kvproto" ]; then
  cd "$SRCPATH/third_party/kvproto"
  ./scripts/generate_cpp.sh
  cd -
fi

build_dir="$SRCPATH/build"
mkdir -p $build_dir && cd $build_dir
cmake "$SRCPATH" \
    -DENABLE_TESTS=on
make -j $NPROC