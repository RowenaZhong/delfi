cmake_minimum_required(VERSION 3.10)
project(Delfi
    VERSION 0.1.0
    LANGUAGES CXX
)


# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 配置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # 静态库(.a)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # 动态库(.so/.dll)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  # 可执行文件

# 创建主库
add_library(delfi
    src/Function.cpp
    src/Matrix.cpp
    src/Vector.cpp
    src/MultiFunction.cpp
    src/VecValFunction.cpp
)

# 包含头文件目录
target_include_directories(delfi PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 安装配置
install(TARGETS delfi
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)

# 测试数据部署
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/test_data)  # 创建测试数据目录
file(COPY test/data/ DESTINATION ${CMAKE_BINARY_DIR}/test_data)  # 复制测试数据

# 启用测试
enable_testing()

# 单元测试配置
add_executable(test_function test/unit/test_function.cpp)
target_link_libraries(test_function delfi)
add_test(NAME test_function 
    COMMAND test_function
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test_data  # 设置测试工作目录
)

add_executable(test_matrix test/unit/test_matrix.cpp)
target_link_libraries(test_matrix delfi)
add_test(NAME test_matrix 
    COMMAND test_matrix
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test_data
)

add_executable(test_vector test/unit/test_vector.cpp)
target_link_libraries(test_vector delfi)
add_test(NAME test_vector 
    COMMAND test_vector
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test_data
)

add_executable(test_multifunction test/unit/test_multifunction.cpp)
target_link_libraries(test_multifunction delfi)
add_test(NAME test_multifunction 
    COMMAND test_multifunction
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test_data
)

add_executable(test_vec_val_function test/unit/test_vec_val_function.cpp)
target_link_libraries(test_vec_val_function delfi)
add_test(NAME test_vec_val_function 
    COMMAND test_vec_val_function
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/test_data
)

find_package(GTest REQUIRED)
target_link_libraries(test_vector delfi ${GTEST_LIBRARIES})
target_link_libraries(test_matrix delfi ${GTEST_LIBRARIES})
target_link_libraries(test_function delfi ${GTEST_LIBRARIES})
target_link_libraries(test_multifunction delfi ${GTEST_LIBRARIES})
target_link_libraries(test_vec_val_function delfi ${GTEST_LIBRARIES})

# 安装测试程序（可选）
install(TARGETS test_function test_matrix test_vector test_multifunction test_vec_val_function
    RUNTIME DESTINATION bin
)


if(ENABLE_COVERAGE)
    target_compile_options(delfi PRIVATE --coverage -fprofile-arcs -ftest-coverage)
    target_link_libraries(delfi PRIVATE --coverage)
endif()