#!/bin/bash

PRJ_DIR=${PWD}

pip install mugit

echo "select mugit main file"

mugit select main

mugit pull

# select version

cd ${PRJ_DIR}/third_party/kvproto; git reset --hard 0e3ce33f29b8be60d24610eb1c4695114de367ca
cd ${PRJ_DIR}
echo "set kvproto to version 0e3ce33f29b8be60d24610eb1c4695114de367ca success"

cd ${PRJ_DIR}/third_party/googletest; git reset --hard db5f9ec567daff3beba53fd0bcd98e3f3562404c
cd ${PRJ_DIR}
echo "set googletest to version db5f9ec567daff3beba53fd0bcd98e3f3562404c success"

cd ${PRJ_DIR}/third_party/libfiu; git reset --hard 20ea5e85ec63e3dedd6904e103fb2e56b46840cf
cd ${PRJ_DIR}
echo "set libfiu to version 20ea5e85ec63e3dedd6904e103fb2e56b46840cf success"

echo "all pre download success!!!, Go to the ci dir: cd ci; make run-dev    "
