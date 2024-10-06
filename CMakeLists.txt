cmake_minimum_required(VERSION 3.28)
project(ImageProcessing)

enable_testing()

# Dodaj katalogi do ścieżki include
include_directories(${CIMG_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Dodaj podprojekt z folderu lib
add_subdirectory(lib)

# Dodaj plik wykonywalny
add_executable(main src/main.cpp)

# Połącz bibliotekę z plikiem wykonywalnym
target_link_libraries(main lib ${CIMG_LIBRARIES})