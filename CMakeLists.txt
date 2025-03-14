cmake_minimum_required(VERSION 3.12)
project(Delfi VERSION 1.0.0 LANGUAGES CXX)

#-------------------------------#
#        输出目录控制           #
#-------------------------------#
# 静态库文件(.a/.lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# 动态库文件(.so/.dll)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# 可执行文件(.exe等)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#-------------------------------#
#        编译选项配置           #
#-------------------------------#
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 静态分析配置（选项形式）
option(WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)
if(WARNINGS_AS_ERRORS)
    add_compile_options(-Werror)
endif()

#-------------------------------#
#          主库构建             #
#-------------------------------#
add_library(Delfi STATIC
    src/Function.cpp
    src/Matrix.cpp
)

target_include_directories(Delfi PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

#-------------------------------#
#          测试目标             #
#-------------------------------#
# Function模块测试
add_executable(TestFunction
    test/test_function.cpp
)

# Matrix模块测试（新增）
add_executable(TestMatrix
    test/test_matrix.cpp
)

# 统一配置测试目标
foreach(test_target IN ITEMS TestFunction TestMatrix)
    # 链接主库
    target_link_libraries(${test_target} PRIVATE Delfi)
    
    # 设定测试属性
    add_test(
        NAME ${test_target}
        COMMAND ${test_target}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin  # 设置为可执行文件所在目录
    )
endforeach()

#-------------------------------#
#          安装规则             #
#-------------------------------#
install(TARGETS Delfi
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(DIRECTORY include/ DESTINATION include/delfi)
