#include "Histogram.h"
#include "GlobalHelper.h"

Histogram::Histogram() {
    for (int i = 0; i < 256; ++i) {
        histogramData[i] = 0;
    }
}

Histogram::~Histogram() {
    histogramData.clear();
}

void Histogram::computeHistogram(CImg<unsigned char> image, int channel) {
    histogramData.clear();
    for (uint8_t pixel : image) {
        uint8_t value = pixel >> (channel * 8); //bit shift to get the value of the channel
        histogramData[value]++;
    }
}

CImg<unsigned char> Histogram::returnHistogramImage() const {
    int width = 256;
    int height = 100;
    CImg<unsigned char> histogramImage = GlobalHelper::createEmptyImage(width, height);
    uint32_t max = 0;
    for (auto& pair : histogramData) {
        max = std::max(max, pair.second);
    }
    for (int i = 0; i < width; ++i) {
        uint32_t value = histogramData.at(i);
        int barHeight = static_cast<int>(static_cast<float>(value) / max * height);
        for (int j = 0; j < barHeight; ++j) {
            histogramImage(i, height - j - 1, 0) = 255;
            histogramImage(i, height - j - 1, 1) = 255;
            histogramImage(i, height - j - 1, 2) = 255;
        }
    }
    return histogramImage;
}