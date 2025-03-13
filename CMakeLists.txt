cmake_minimum_required(VERSION 3.12)
project(Delfi VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 创建静态库
add_library(Delfi STATIC
    src/Function.cpp
    src/Matrix.cpp
)

# 包含路径配置（公共头文件）
target_include_directories(Delfi PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 创建测试可执行文件
add_executable(TestFunction
    test/test_function.cpp
)

# 链接测试程序与库
target_link_libraries(TestFunction
    PRIVATE Delfi
)

# 可选：安装规则（如果需要）
install(TARGETS Delfi
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include)
