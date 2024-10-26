#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "Geometry.h"

using namespace cimg_library;

TEST_CASE("Geometry::horizontalFlip flips image horizontally", "[horizontalFlip]") {
    CImg<unsigned char> testImage("test_image.bmp");
    CImg<unsigned char> flippedImage = Geometry::horizontalFlip(testImage);

    cimg_forXYC(flippedImage, x, y, c) {
        REQUIRE(flippedImage(x, y, c) == testImage(testImage.width() - x - 1, y, c));
    }
}

TEST_CASE("Geometry::verticalFlip flips image vertically", "[verticalFlip]") {
    CImg<unsigned char> testImage("test_image.bmp");
    CImg<unsigned char> flippedImage = Geometry::verticalFlip(testImage);

    cimg_forXYC(flippedImage, x, y, c) {
        REQUIRE(flippedImage(x, y, c) == testImage(x, testImage.height() - y - 1, c));
    }
}

TEST_CASE("Geometry::diagonalFlip flips image diagonally", "[diagonalFlip]") {
    CImg<unsigned char> testImage("test_image.bmp");
    CImg<unsigned char> flippedImage = Geometry::diagonalFlip(testImage);

    cimg_forXYC(flippedImage, x, y, c) {
        REQUIRE(flippedImage(x, y, c) == testImage(y, x, c));
    }
}

TEST_CASE("Geometry::imageShrinking shrinks image by factor", "[imageShrinking]") {
    CImg<unsigned char> testImage("test_image.bmp");
    int factor = 2;
    CImg<unsigned char> shrunkImage = Geometry::imageShrinking(testImage, factor);

    cimg_forXYC(shrunkImage, x, y, c) {
        REQUIRE(shrunkImage(x, y, c) == testImage(x * factor, y * factor, c));
    }
}

TEST_CASE("Geometry::imageEnlargement enlarges image by factor", "[imageEnlargement]") {
    CImg<unsigned char> testImage("test_image.bmp");
    int factor = 2;
    CImg<unsigned char> enlargedImage = Geometry::imageEnlargement(testImage, factor);

    cimg_forXYC(enlargedImage, x, y, c) {
        REQUIRE(enlargedImage(x, y, c) == testImage(x / factor, y / factor, c));
    }
}