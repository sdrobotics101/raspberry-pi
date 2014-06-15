cmake_minimum_required(VERSION 2.8)
project(robosub_rpi)
set(CMAKE_CXX_FLAGS "-pthread -std=c++11 ${CMAKE_CXX_FLAGS} -g")
add_subdirectory(src)
