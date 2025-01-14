project(ImageProcessingTests)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

find_package(TIFF REQUIRED)

set(CIMG_H_PATH "${PROJECT_SOURCE_DIR}/../image-processing-library/include")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${CIMG_H_PATH}")

get_filename_component(TIFF_LIB_DIRS "${TIFF_LIBRARIES}" DIRECTORY)
SET(CIMG_CFLAGS "${CIMG_CFLAGS} ${CIMG_TIFF_CCFLAGS}")
link_directories(${TIFF_LIB_DIRS})
include_directories(${TIFF_INCLUDE_DIR})
SET(SYSTEM_LIBS ${SYSTEM_LIBS} ${TIFF_LIBRARIES})

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

add_executable(imageProcessingTests_task4 
                    test_frequency.cpp
)

catch_discover_tests(imageProcessingTests_task4)

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
            ${CMAKE_SOURCE_DIR}/tests/lena.bmp
            $<TARGET_FILE_DIR:imageProcessingTests_task3>/lena.bmp

    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_SOURCE_DIR}/tests/mandrilbw.bmp
            $<TARGET_FILE_DIR:imageProcessingTests_task3>/mandrilbw.bmp
        
    COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/tests/mandril.bmp
        $<TARGET_FILE_DIR:imageProcessingTests_task3>/mandril.bmp

        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/mandrilc.bmp
                $<TARGET_FILE_DIR:imageProcessingTests_task3>/mandrilc.bmp

    COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:imageProcessingTests_task3>/task3
)

add_custom_command(TARGET imageProcessingTests_task4 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/mandril.bmp
                $<TARGET_FILE_DIR:imageProcessingTests_task1>/mandril.bmp
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/lena.bmp
                $<TARGET_FILE_DIR:imageProcessingTests_task1>/lena.bmp
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/camera.bmp
                $<TARGET_FILE_DIR:imageProcessingTests_task1>/camera.bmp
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/boat.bmp
                $<TARGET_FILE_DIR:imageProcessingTests_task1>/boat.bmp
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/F5mask1.bmp
                $<TARGET_FILE_DIR:imageProcessingTests_task1>/F5mask1.bmp
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/F5mask2.bmp
                $<TARGET_FILE_DIR:imageProcessingTests_task1>/F5mask2.bmp
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/F5test1.bmp
                $<TARGET_FILE_DIR:imageProcessingTests_task1>/F5test1.bmp
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/F5test2.bmp
                $<TARGET_FILE_DIR:imageProcessingTests_task1>/F5test2.bmp
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/tests/F5test3.bmp
                $<TARGET_FILE_DIR:imageProcessingTests_task1>/F5test3.bmp
        COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:imageProcessingTests_task4>/task4
        COMMAND ${CMAKE_COMMAND} -E make_directory
            $<TARGET_FILE_DIR:imageProcessingTests_task4>/task4/raport
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

target_link_libraries(imageProcessingTests_task4 
                        PRIVATE 
                            image-processing-library 
                            Catch2::Catch2WithMain
                                ${TIFF_LIBRARIES}
)