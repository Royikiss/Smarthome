#cmake_minimum_required(VERSION 3.10)

# Set the project name
#project(RoyiSmartHome)

# Add the executable
#add_executable(RoyiSmartHome tests/test.c source/common.c source/Non-blocking.c)

# Specify include directories
#target_include_directories(RoyiSmartHome PUBLIC
#                           "${PROJECT_BINARY_DIR}"
#                           "${PROJECT_SOURCE_DIR}/include"
#                           )

# 设置CMake最低版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名
project(RoyiSmartHome)

# 添加头文件路径
include_directories(include)

# 指定源文件
file(GLOB_RECURSE SOURCE_FILES 
    "test/*.cpp"
    "src/*.cpp"
)

# 指定生成目标
add_executable(RoyiSmartHome ${SOURCE_FILES})

#添加链接库
target_link_libraries(RoyiSmartHome pthread mysqlcppconn) 

# 设置编译选项
# 针对不同的编译模式（Debug/Release）设置不同的编译器选项
set(CMAKE_CXX_FLAGS_DEBUG "-g")       # Debug 模式下启用调试信息
set(CMAKE_CXX_FLAGS_RELEASE "-O3")    # Release 模式下优化代码

# 添加宏定义
# 如果是 Debug 模式，自动添加 -D_D 参数
target_compile_definitions(RoyiSmartHome
    PRIVATE
    $<$<CONFIG:Debug>:_D>  # 只有 Debug 模式会添加 _D
)

# 添加对编译类型的支持（Release, Debug等）
# 使用 -DCMAKE_BUILD_TYPE=Debug 或 -DCMAKE_BUILD_TYPE=Release 来选择不同模式
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")   # 如果没有指定编译类型，默认为Release
endif()

# 输出编译类型信息
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
