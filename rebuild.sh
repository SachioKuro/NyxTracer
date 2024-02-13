#! /bin/bash

# This script is used to rebuild the project
rm -rf build
mkdir build
cd build
cmake -GNinja ..
ninja -C .

# run tests
./tuple_test