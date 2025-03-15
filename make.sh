#!/bin/bash
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release

# 编译项目（观察生成路径）
cmake --build . 

# 验证输出路径

cd ..