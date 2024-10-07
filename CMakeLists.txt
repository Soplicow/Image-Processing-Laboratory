cmake_minimum_required(VERSION 3.28)
project(ImageProcessing)

enable_testing()

# Dodaj katalogi do ścieżki include
include_directories(${CIMG_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Dodaj podprojekty
add_subdirectory(lib)
#add_subdirectory(tests)

# Dodaj plik wykonywalny
add_executable(imageProcessing src/main.cpp)

# Połącz bibliotekę z plikiem wykonywalnym
target_link_libraries(imageProcessing PRIVATE lib ${CIMG_LIBRARIES})

# Change the output directory of the build to a folder outside the build directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)