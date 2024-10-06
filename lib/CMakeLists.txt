cmake_minimum_required(VERSION 3.28)
project(lib)

enable_testing()

set(SOURCE_FILES
    elementary.cpp
    elementary.h
    geometry.cpp
    geometry.h
    measuring.cpp
    measuring.h
    noise.cpp
    noise.h
)

add_library(lib STATIC ${SOURCE_FILES})

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})