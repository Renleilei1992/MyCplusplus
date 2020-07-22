# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)

# 项目信息
project (Demo1)

option(_OPEN "option for OPEN DEFINE" OFF)
if (_OPEN)
add_definitions(-D_OPEN)
endif()

# 指定生成目标
add_executable(Demo hello.cpp)
