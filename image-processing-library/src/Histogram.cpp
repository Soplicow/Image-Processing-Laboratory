#include "Histogram.h"
#include "GlobalHelper.h"
#include <stdexcept>

Histogram::Histogram() {
    
}

Histogram::~Histogram() {

}

std::map<uint8_t, uint32_t> Histogram::computeHistogram(CImg<unsigned char> image, int channel) {
    std::map<uint8_t, uint32_t> histogramData;
    for (size_t i = 0; i < 256; i++)
    {
        histogramData[i] = 0;
    }

    cimg_forXY(image, x, y) {
        uint8_t pixelValue = image(x, y, 0, channel);
        histogramData[pixelValue]++;
    }
    return histogramData;
}

CImg<unsigned char> Histogram::returnHistogramImage(CImg<unsigned char> image, int channel) {
    int width = 256;
    int height = 100;
    CImg<unsigned char> histogramImage = GlobalHelper::createEmptyImage(width, height);
    std::map<uint8_t, uint32_t> histogramData = computeHistogram(image, channel);
    uint32_t max = 0;
    for (auto& pair : histogramData) {
        max = std::max(max, pair.second);
    }
    for (int i = 0; i < width; ++i) {
        uint32_t value = histogramData.count(i) ? histogramData.at(i) : 0;
        int barHeight = static_cast<int>(static_cast<float>(value) / max * height);
        for (int j = 0; j < barHeight; ++j) {
            histogramImage(i, height - j - 1, 0) = 255;
            histogramImage(i, height - j - 1, 1) = 255;
            histogramImage(i, height - j - 1, 2) = 255;
        }
    }
    return histogramImage;
}

CImg<unsigned char> Histogram::exponentialFPDF(CImg<unsigned char> image, int minBrightness, int maxBrightness, float alpha) {
    if (alpha <= 0) {
        throw std::invalid_argument("Alpha must be greater than 0");
    }

    if (minBrightness < 0 || minBrightness > 255) {
        throw std::invalid_argument("Min brightness must be between 0 and 255");
    }

    if (maxBrightness < 0 || maxBrightness > 255) {
        throw std::invalid_argument("Max brightness must be between 0 and 255");
    }

    unsigned int totalPixels = image.width() * image.height();

    CImg<unsigned char> fpdfImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    for (int c = 0; c < image.spectrum(); ++c) {
        std::map<uint8_t, uint32_t> histogramData = computeHistogram(image, c);

        std::vector<float> cumulativeHistogram(256, 0.0f); //vectors are apparently faster than maps
        cumulativeHistogram[0] = histogramData[0];
        for (int i = 1; i < 256; ++i) {
            cumulativeHistogram[i] = cumulativeHistogram[i - 1] + histogramData[i];
        }

        cimg_forXY(image, x, y) {
            uint8_t pixelValue = image(x, y, c);
            float cumulativeSum = cumulativeHistogram[pixelValue];

            float newPixelValue = minBrightness - (1.0f / alpha) * std::log(1 - (1.0f / totalPixels) * cumulativeSum);
            fpdfImage(x, y, c) = static_cast<uint8_t>(std::clamp(newPixelValue, static_cast<float>(minBrightness), static_cast<float>(maxBrightness)));
        }
    }

    return fpdfImage;
}