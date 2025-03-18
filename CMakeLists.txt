cmake_minimum_required(VERSION 3.10)
project(delfi VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 包含头文件目录
include_directories(include)

# 递归收集源文件（适用于小型项目）
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 构建主库
add_library(delfi_lib STATIC ${SOURCES})

# 构建测试可执行文件
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test)
    enable_testing()
    
    # test_function
    add_executable(test_function test/test_function.cpp)
    target_link_libraries(test_function delfi_lib)
    add_test(NAME test_function COMMAND test_function)
    
    # test_matrix
    add_executable(test_matrix test/test_matrix.cpp)
    target_link_libraries(test_matrix delfi_lib)
    add_test(NAME test_matrix COMMAND test_matrix)
endif()

# 可选：安装规则
install(DIRECTORY include/ DESTINATION include)
install(TARGETS delfi_lib
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)