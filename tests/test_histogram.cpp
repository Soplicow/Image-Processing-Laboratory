#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "Histogram.h"

TEST_CASE("Histogram::Histogram calculation", "[histogram]") {
    CImg<unsigned char> testImage("test_image.bmp");
    std::map<uint8_t, uint32_t> histogram = Histogram::computeHistogram(testImage, 0);
    REQUIRE(histogram.size() == 256);
    REQUIRE(histogram[128] == 0);
    REQUIRE(histogram[255] == 64*64*2);
    REQUIRE(histogram[0] == 64*64*2);
}

TEST_CASE("Histogram::One pixel image", "[histogram]") {
    CImg<unsigned char> testImage(1, 1, 1, 1, 0);
    std::map<uint8_t, uint32_t> histogram = Histogram::computeHistogram(testImage, 0);
    REQUIRE(histogram.size() == 256);
    for (auto& pair : histogram) {
        assert(pair.second == 0 || pair.second == 1);
    }
}

TEST_CASE("Histogram::Histogram image", "[histogram]") {
    CImg<unsigned char> testImage("test_image.bmp");
    CImg<unsigned char> histogramImage = Histogram::returnHistogramImage(testImage, 0);
    REQUIRE(histogramImage.width() == 256);
    REQUIRE(histogramImage.height() == 100);
    REQUIRE(histogramImage.spectrum() == 3);
}

TEST_CASE("Histogram::Exponential FPDF", "[histogram]") {
    CImg<unsigned char> testImage("test_image.bmp");
    CImg<unsigned char> fpdfImage = Histogram::exponentialFPDF(testImage, 60, 200, 0.5);
    REQUIRE(fpdfImage.width() == testImage.width());
    REQUIRE(fpdfImage.height() == testImage.height());
    REQUIRE(fpdfImage.spectrum() == testImage.spectrum());
    for (int i = 0; i < fpdfImage.width(); i++) {
        for (int j = 0; j < fpdfImage.height(); j++) {
            for (int c = 0; c < fpdfImage.spectrum(); c++) {
                REQUIRE(fpdfImage(i, j, c) >= 60);
                REQUIRE(fpdfImage(i, j, c) <= 200);
            }
        }
    }
}