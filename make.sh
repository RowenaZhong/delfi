#!/bin/bash

cd build
cmake .. --DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel 4
cd ..