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

add_custom_command(TARGET imageProcessingTests_task1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/tests/test_image.bmp
            $<TARGET_FILE_DIR:imageProcessingTests_task1>/test_image.bmp
)

catch_discover_tests(imageProcessingTests_task1)

add_executable(imageProcessingTests_task2 
                    test_histogram.cpp
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