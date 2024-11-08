#define CATCH_CONFIG_MAIN

#include "NonLinearSpatial.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("NonLinearSpatial::rosenfeldOperator", "[rosenfeldOperator]") {
    CImg<unsigned char> testImage("test_image.bmp");

    CImg<unsigned char> newImage = NonLinearSpatial::rosenfeldOperator(testImage, 1);

    REQUIRE(newImage.width() == testImage.width());
    REQUIRE(newImage.height() == testImage.height());
    REQUIRE(newImage.spectrum() == testImage.spectrum());
}

TEST_CASE("NonLinearSpatial::rosenfeldOperator with power 0", "[rosenfeldOperator]") {
    CImg<unsigned char> testImage("test_image.bmp");

    CImg<unsigned char> newImage = NonLinearSpatial::rosenfeldOperator(testImage, 0);

    REQUIRE(newImage.width() == testImage.width());
    REQUIRE(newImage.height() == testImage.height());
    REQUIRE(newImage.spectrum() == testImage.spectrum());
}

