project(ImageProcessingTests)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

include(CTest)
include(Catch)

# Add the test executable
add_executable(imageProcessingTests_task1 
                    test_elementary.cpp
                    test_geometry.cpp
)

catch_discover_tests(imageProcessingTests_task1)

add_executable(imageProcessingTests_task2 
                    test_histogram.cpp
                    test_linearSpatial.cpp
                    test_nonLinearSpatial.cpp
)

catch_discover_tests(imageProcessingTests_task2)

add_executable(imageProcessingTests_task3 
                    test_binaryOp.cpp
)

catch_discover_tests(imageProcessingTests_task3)

add_custom_command(TARGET imageProcessingTests_task1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/tests/test_image.bmp
            $<TARGET_FILE_DIR:imageProcessingTests_task1>/test_image.bmp
)

add_custom_command(TARGET imageProcessingTests_task3 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/tests/test_image_binary.bmp
            $<TARGET_FILE_DIR:imageProcessingTests_task3>/test_image_binary.bmp
            
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/tests/lenabw.bmp
            $<TARGET_FILE_DIR:imageProcessingTests_task3>/lenabw.bmp

    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/tests/mandrilbw.bmp
            $<TARGET_FILE_DIR:imageProcessingTests_task3>/mandrilbw.bmp
            
    COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:imageProcessingTests_task3>/task3
)

target_link_libraries(imageProcessingTests_task1 
                        PRIVATE 
                            image-processing-library 
                            Catch2::Catch2WithMain
)

target_link_libraries(imageProcessingTests_task2 
                        PRIVATE 
                            image-processing-library 
                            Catch2::Catch2WithMain
)

target_link_libraries(imageProcessingTests_task3 
                        PRIVATE 
                            image-processing-library 
                            Catch2::Catch2WithMain
)