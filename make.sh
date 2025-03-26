#!/bin/bash
cd build
cmake .. 
make -j4 && ctest --output-on-failure
cd ..