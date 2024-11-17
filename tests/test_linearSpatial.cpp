#define CATCH_CONFIG_MAIN

#include "LinearSpatial.h"
#include <catch2/catch_test_macros.hpp>

#include <chrono>
#include <iostream>

TEST_CASE("LinearSpatial::optimizedExtractionOfDetailsN", "[extractionOfDetails]") {
    CImg<unsigned char> testImage("test_image.bmp");
    LinearSpatial linearSpatial;

    auto start = std::chrono::high_resolution_clock::now();
    CImg<unsigned char> newImage = linearSpatial.extractionOfDetails(testImage, "N");
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "optimizedExtractionOfDetailsN took " << duration.count() << " seconds" << std::endl;

    REQUIRE(newImage.width() == testImage.width());
    REQUIRE(newImage.height() == testImage.height());
    REQUIRE(newImage.spectrum() == testImage.spectrum());
}

TEST_CASE("LinearSpatial::extractionOfDetailsNE", "[extractionOfDetails]") {
    CImg<unsigned char> testImage("test_image.bmp");
    LinearSpatial linearSpatial;

    auto start = std::chrono::high_resolution_clock::now();
    CImg<unsigned char> newImage = linearSpatial.extractionOfDetails(testImage, "NE");
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "extractionOfDetailsNE took " << duration.count() << " seconds" << std::endl;

    REQUIRE(newImage.width() == testImage.width());
    REQUIRE(newImage.height() == testImage.height());
    REQUIRE(newImage.spectrum() == testImage.spectrum());
}

TEST_CASE("LinearSpatical::extractionOfDetails images are different", "[extractionOfDetails]") {
    CImg<unsigned char> testImage("test_image.bmp");
    LinearSpatial linearSpatial;

    CImg<unsigned char> newImageN = linearSpatial.extractionOfDetails(testImage, "N");
    CImg<unsigned char> newImageNE = linearSpatial.extractionOfDetails(testImage, "NE");

    REQUIRE_FALSE(newImageN == newImageNE);
}