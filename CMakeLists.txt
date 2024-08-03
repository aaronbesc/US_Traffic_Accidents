cmake_minimum_required(VERSION 3.26)
project(US_Traffic_Incidents)

set(CMAKE_CXX_STANDARD 17)

add_executable(US_Traffic_Incidents main.cpp
        Hash_table.cpp
        Hash_table.h
        TrafficAccident.h
        RedBlackTree.h
        RedBlackTree.cpp)
