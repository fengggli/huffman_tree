cmake_minimum_required(VERSION 3.5)

project(Huffman CXX)

set(CMAKE_CXX_STANDARD 11)
add_definitions("-std=c++11")
add_executable(Huffman Huffman.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/freq.txt
            DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
