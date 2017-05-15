cmake_minimum_required(VERSION 3.6)
project(RTTI)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp TypeInfo.cpp RTTI.cpp Globals.cpp)
add_executable(RTTI ${SOURCE_FILES})