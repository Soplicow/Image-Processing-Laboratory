#include "Histogram.h"
#include "GlobalHelper.h"

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
    unsigned int totalPixels = image.width() * image.height();

    CImg<unsigned char> fpdfImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    for (int c = 0; c < image.spectrum(); ++c) {
        std::map<uint8_t, uint32_t> histogramData = computeHistogram(image, c);

        std::map<uint8_t, uint32_t> cumulativeHistogram;
        for (int x = 0; x < 256; ++x) {
            for (int y = 0; y <= x; ++y) {
                cumulativeHistogram[x] += histogramData[y];
            }
        }

        cimg_forXY(image, x, y) {
            uint8_t pixelValue = image(x, y, 0, c);
            float cumulativeSum = cumulativeHistogram[pixelValue];

            float newPixelValue = minBrightness - (1.0f / alpha) * std::log(1 - (1.0f / totalPixels) * cumulativeSum);
            fpdfImage(x, y, 0, c) = static_cast<uint8_t>(std::clamp(newPixelValue, static_cast<float>(minBrightness), static_cast<float>(maxBrightness)));
        }
    }

    return fpdfImage;
}