cmake_minimum_required(VERSION 3.28)
project(ImageProcessing)

enable_testing()

find_package(TIFF REQUIRED)

set(CIMG_H_PATH "${PROJECT_SOURCE_DIR}/image-processing-library/include")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${CIMG_H_PATH}")

get_filename_component(TIFF_LIB_DIRS "${TIFF_LIBRARIES}" DIRECTORY)
SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_TIFF_CCFLAGS}")
link_directories(${TIFF_LIB_DIRS})
include_directories(${TIFF_INCLUDE_DIR})
SET(SYSTEM_LIBS ${SYSTEM_LIBS} ${TIFF_LIBRARIES})

# Dodaj katalogi do ścieżki include
include_directories(${CIMG_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/image-processing-library/include)

# Dodaj podprojekty
add_subdirectory(image-processing-library)
add_subdirectory(tests)

message(STATUS "TIFF_INCLUDE_DIR: ${TIFF_INCLUDE_DIR}")
message(STATUS "TIFF_LIBRARIES: ${TIFF_LIBRARIES}")

# Dodaj plik wykonywalny
add_executable(imageProcessing main.cpp)

# Połącz bibliotekę z plikiem wykonywalnym
target_link_libraries(imageProcessing PRIVATE image-processing-library ${CIMG_LIBRARIES})
target_link_libraries(imageProcessing PRIVATE image-processing-library ${TIFF_LIBRARIES})

# Change the output directory of the build to a folder outside the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)