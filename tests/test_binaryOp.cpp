#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <BinaryOp.h>

using namespace cimg_library;

TEST_CASE("BinaryOp::dilation - customimage", "[dilation]") {
    CImg<unsigned char> image(21, 21, 1, 1, 0); // Initialize a 21x21 image with all pixels set to 0 (black)
    for (int y = 0; y < 21; ++y) {
        image(10, y) = 255; // Set the middle column to 255 (white)
    }
    image.save_bmp("task3/image.bmp");
    
    std::array<std::array<bool, 3>, 3> kernel = {{{0, 0, 0}, {1, 0, 1}, {0, 0, 0}}}; 
    CImg<unsigned char> result = BinaryOp::dilation(image, kernel);
    result.save_bmp("result.bmp");

    REQUIRE(result(10, 1) != image(10, 1)); // The result should not be the same as the input
}

TEST_CASE("BinaryOp::dilation - lenabw", "[dilation]") {
    CImg<unsigned char> image("lenabw.bmp");
    std::array<std::array<bool, 3>, 3> kernel = {{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}};
    CImg<unsigned char> result = BinaryOp::dilation(image, kernel);
    result.save_bmp("task3/lenabw_dilated.bmp");

    REQUIRE(result != image); // The result should not be the same as the input
}

TEST_CASE("BinaryOp::erosion - customimage", "[erosion]") {
    CImg<unsigned char> image(21, 21, 1, 1, 0); // Initialize a 21x21 image with all pixels set to 0 (black)
    for (int y = 0; y < 21; ++y) {
        image(9, y) = 255; // Set the middle column to 255 (white)
        image(10, y) = 255; // Set the middle column to 255 (white)
        image(11, y) = 255; // Set the middle column to 255 (white)
    }

    std::array<std::array<bool, 3>, 3> kernel = {{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}};
    CImg<unsigned char> result = BinaryOp::erosion(image, kernel);

    result.save_bmp("task3/result_erosion.bmp");

    REQUIRE(result(10, 1) == image(10, 1)); // Middlemost column stays the same
    REQUIRE(result(9, 1) != image(9, 1)); // The result should not be the same as the input
}

TEST_CASE("BinaryOp::erosion - Lenabw", "[erosion]") {
    CImg<unsigned char> image("lenabw.bmp");
    std::array<std::array<bool, 3>, 3> kernel = {{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}};
    CImg<unsigned char> result = BinaryOp::erosion(image, kernel);
    result.save_bmp("task3/lenabw_eroded.bmp");

    REQUIRE(result != image); // The result should not be the same as the input
}

TEST_CASE("BinaryOp::M7 - lenabw", "[M7]") {
    CImg<unsigned char> image("lenabw.bmp");
    std::array<std::array<bool, 3>, 3> kernel = {{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}};
    CImg<unsigned char> result = BinaryOp::M7(image, kernel, 1);
    result.save_bmp("task3/lenabw_M7.bmp");

    REQUIRE(image != result); // The result should not be the same as the input
}

TEST_CASE("BinaryOp::M7 - customimage", "[M7]") {
    CImg<unsigned char> image(21, 21, 1, 1, 0); // Initialize a 21x21 image with all pixels set to 0 (black)
    for (int y = 0; y < 21; ++y) {
        image(9, y) = 255; // Set the middle column to 255 (white)
        image(10, y) = 255; // Set the middle column to 255 (white)
        image(11, y) = 255; // Set the middle column to 255 (white)
    }
    std::array<std::array<bool, 3>, 3> kernel = {{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}};
    CImg<unsigned char> result = BinaryOp::M7(image, kernel, 1);
    result.save_bmp("task3/binary_M7.bmp");

    REQUIRE(image != result); // The result should not be the same as the input
}

TEST_CASE("BinaryOp::M7 - mandrilbw", "[M7]") {
    CImg<unsigned char> image("mandrilbw.bmp");
    std::array<std::array<bool, 3>, 3> kernel = {{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}};
    CImg<unsigned char> result = BinaryOp::M7(image, kernel, 1);
    CImg<unsigned char> result1 = BinaryOp::M7(image, kernel, 4);
    CImg<unsigned char> result2 = BinaryOp::M7(image, kernel, 7);
    result.save_bmp("task3/mandrilbw_M7_1.bmp");
    result1.save_bmp("task3/mandrilbw_M7_4.bmp");
    result2.save_bmp("task3/mandrilbw_M7_7.bmp");

    REQUIRE(image != result); // The result should not be the same as the input
    REQUIRE(image != result1); // The result should not be the same as the input
    REQUIRE(image != result2); // The result should not be the same as the input
}

TEST_CASE("BinaryOp::regionGrowing - lenabw", "[regionGrowing]") {
    CImg<unsigned char> image("lenabw.bmp");
    CImg<unsigned char> result1 = BinaryOp::regionGrowing(image, 250, 140, 0); // White region
    CImg<unsigned char> result2 = BinaryOp::regionGrowing(image, 2, 300, 0); // Black region
    
    result1.save_bmp("task3/lenabw_region1.bmp");
    result2.save_bmp("task3/lenabw_region2.bmp");

    REQUIRE(image != result1); // The result should not be the same as the input
    REQUIRE(image != result2); // The result should not be the same as the input
}

TEST_CASE("BinaryOp::HMT - lenabw", "[HMT]") {
    CImg<unsigned char> image("lenabw.bmp");
    std::array<std::array<bool, 3>, 3> kernelA = {{{1, 0, 0}, {1, 1, 0}, {1, 0, 0}}};
    std::array<std::array<bool, 3>, 3> kernelB = {{{0, 0, 1}, {0, 0, 1}, {0, 0, 1}}};
    CImg<unsigned char> result = BinaryOp::HMT(image, kernelA, kernelB);
    result.save_bmp("task3/lenabw_HMT.bmp");

    std::array<std::array<bool, 3>, 3> kernelA2 = {{{1, 0, 0}, {1, 0, 0}, {1, 0, 0}}};
    std::array<std::array<bool, 3>, 3> kernelB2 = {{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}};
    CImg<unsigned char> result2 = BinaryOp::HMT(image, kernelA2, kernelB2);
    result2.save_bmp("task3/lenabw_HMT2.bmp");

    REQUIRE(image != result); // The result should not be the same as the input
    REQUIRE(image != result2); // The result should not be the same as the input
}