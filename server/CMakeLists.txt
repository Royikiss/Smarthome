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

# 添加宏定义
add_definitions(-D_D)

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
