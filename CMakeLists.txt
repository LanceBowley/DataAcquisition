cmake_minimum_required(VERSION 3.6)
project(Serial)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Initializer.h Initializer.cpp Port.h Port.cpp BinaryIO.h BinaryIO.cpp Serial.h Serial.cpp)
add_executable(Serial ${SOURCE_FILES})