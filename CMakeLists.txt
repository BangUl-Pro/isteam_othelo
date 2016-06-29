cmake_minimum_required(VERSION 2.8)
project(othelo)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES main.c game.h game.c)
add_executable(othelo ${SOURCE_FILES})