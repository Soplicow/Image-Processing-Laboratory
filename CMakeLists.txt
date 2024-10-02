cmake_minimum_required(VERSION 3.5.0)
project(Image-Processing-Laboratory VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Image-Processing-Laboratory src/main.cpp)


include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})