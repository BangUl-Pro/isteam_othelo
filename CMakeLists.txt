cmake_minimum_required(VERSION 3.5)
project(isteam_othelo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    game.c
    game.h
    main.c)

add_executable(isteam_othelo ${SOURCE_FILES})