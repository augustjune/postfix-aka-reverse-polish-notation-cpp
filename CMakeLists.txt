cmake_minimum_required(VERSION 3.6)
project(Postfix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp   cpps/CTree.cpp cpps/CNode.cpp)
add_executable(Postfix ${SOURCE_FILES})