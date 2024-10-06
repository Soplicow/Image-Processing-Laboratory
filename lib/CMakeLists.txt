cmake_minimum_required(VERSION 3.28)

enable_testing()

set(SOURCE_FILES
    elementary.cpp
    geometry.cpp
    measuring.cpp
    noise.cpp
)

add_library(lib STATIC ${SOURCE_FILES})

target_include_directories(lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)