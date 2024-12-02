enable_testing()

set(SOURCE_FILES
    src/Elementary.cpp
    src/Geometry.cpp
    src/Measuring.cpp
    src/Noise.cpp
    src/Histogram.cpp
    src/LinearSpatial.cpp
    src/NonLinearSpatial.cpp
    src/Characteristics.cpp
    src/BinaryOp.cpp
)

add_library(image-processing-library STATIC ${SOURCE_FILES})

target_include_directories(image-processing-library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} include)