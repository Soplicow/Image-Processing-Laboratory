#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "Elementary.h"
#include <iostream>

using namespace cimg_library;

TEST_CASE("Elementary::brightnessMod increases brightness", "[brightnessMod]") {
    CImg<unsigned char> image(3, 3, 1, 1, 100); // Create a 3x3 image with all pixels set to 100
    int brightness = 50;
    CImg<unsigned char> result = Elementary::brightnessMod(image, brightness);

    cimg_forXY(result, x, y) {
        REQUIRE(result(x, y) == 150); // All pixels should be increased by 50
    }
}

TEST_CASE("Elementary::brightnessMod decreases brightness", "[brightnessMod]") {
    CImg<unsigned char> image(3, 3, 1, 1, 100); // Create a 3x3 image with all pixels set to 100
    int brightness = -50;
    CImg<unsigned char> result = Elementary::brightnessMod(image, brightness);

    std::cout << result(0, 0, 0) << std::endl;

    cimg_forXY(result, x, y) {
        REQUIRE(result(x, y) == 50); // All pixels should be decreased by 50
    }
}

TEST_CASE("Elementary::brightnessMod caps at 255", "[brightnessMod]") {
    CImg<unsigned char> image(3, 3, 1, 1, 230); // Create a 3x3 image with all pixels set to 230
    int brightness = 250;
    CImg<unsigned char> result = Elementary::brightnessMod(image, brightness);

    cimg_forXY(result, x, y) {
        REQUIRE(result(x, y) == 255); // All pixels should be capped at 255
    }
}

TEST_CASE("Elementary::brightnessMod caps at 0", "[brightnessMod]") {
    CImg<unsigned char> image(3, 3, 1, 1, 20); // Create a 3x3 image with all pixels set to 20
    int brightness = -50;
    CImg<unsigned char> result = Elementary::brightnessMod(image, brightness);

    cimg_forXY(result, x, y) {
        REQUIRE(result(x, y) == 0); // All pixels should be capped at 0
    }
}

TEST_CASE("Elementary::contrastMod increases contrast", "[contrastMod]") {
    CImg<unsigned char> image(3, 3, 1, 1, 100); // Create a 3x3 image with all pixels set to 100
    float contrast = 2.0;
    CImg<unsigned char> result = Elementary::contrastMod(image, contrast);

    cimg_forXY(result, x, y) {
        REQUIRE(result(x, y) == 72); // All pixels should be doubled
    }
}

TEST_CASE("Elementary::contrastMod decreases contrast", "[contrastMod]") {
    CImg<unsigned char> image(3, 3, 1, 1, 100); // Create a 3x3 image with all pixels set to 100
    float contrast = 0.5;
    CImg<unsigned char> result = Elementary::contrastMod(image, contrast);

    cimg_forXY(result, x, y) {
        REQUIRE(result(x, y) == (100-128)/2 + 128); // All pixels should be scaled
    }
}

TEST_CASE("Elementary::contrastMod caps at 255", "[contrastMod]") {
    CImg<unsigned char> image(3, 3, 1, 1, 200); // Create a 3x3 image with all pixels set to 200
    float contrast = 2.0;
    CImg<unsigned char> result = Elementary::contrastMod(image, contrast);

    cimg_forXY(result, x, y) {
        REQUIRE(result(x, y) == 255); // All pixels should be capped at 255
    }
}

TEST_CASE("Elementary::contrastMod caps at 0", "[contrastMod]") {
    CImg<unsigned char> image(3, 3, 1, 1, 50); // Create a 3x3 image with all pixels set to 50
    float contrast = 2;
    CImg<unsigned char> result = Elementary::contrastMod(image, contrast);

    cimg_forXY(result, x, y) {
        REQUIRE(result(x, y) == 0); // All pixels should be capped at 0
    }
}

TEST_CASE("Elementary::negative creates negative image", "[negative]") {
    CImg<unsigned char> image(3, 3, 1, 1, 100); // Create a 3x3 image with all pixels set to 100
    CImg<unsigned char> result = Elementary::negative(image);

    cimg_forXY(result, x, y) {
        REQUIRE(result(x, y) == 155); // All pixels should be 255 - original value
    }
}