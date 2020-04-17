cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# suppress an annoying warning
cmake_policy(SET CMP0074 NEW)

project(tetris VERSION 0.1)

if (MSVC)
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules/msvc")
endif ()

if (APPLE)
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules/apple")
endif ()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_subdirectory(src)
