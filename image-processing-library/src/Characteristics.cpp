#include "Characteristics.h"
#include <cstdint>
#include <map>

Characteristics::Characteristics() {
}

Characteristics::~Characteristics() {
}

float Characteristics::mean(CImg<unsigned char> image) {
    float sum = 0;
    cimg_forXYC(image, x, y, c) {
        sum += image(x, y, 0, c);
    }
    return sum / image.size();
}

float Characteristics::variance(CImg<unsigned char> image) {
    float meanValue = mean(image);
    float sum = 0;
    cimg_forXYC(image, x, y, c) {
        float pixelValue = image(x, y, 0, c);
        sum += pow(pixelValue - meanValue, 2);
    }
    return sum / image.size();
}

float Characteristics::standardDeviation(CImg<unsigned char> image) {
    return sqrt(variance(image));
}

float Characteristics::variationCoefficient_1(CImg<unsigned char> image) {
    return standardDeviation(image) / mean(image);
}

float Characteristics::variationCoefficient_2(CImg<unsigned char> image) {
    float sumOfSquares = 0;
    std::map<uint8_t, int> histogram;

    cimg_forXYC(image, x, y, c) {
        unsigned char pixelValue = image(x, y, c);
        histogram[pixelValue]++;
    }

    for (const auto& pair : histogram) {
        sumOfSquares += pow(pair.second, 2);
    }

    return sumOfSquares / (pow(image.width() * image.height(), 2) * image.spectrum());
}

float Characteristics::assymetryCoefficient(CImg<unsigned char> image) {
    float meanValue = mean(image);
    float varianceValue = variance(image);
    float sum = 0;
    cimg_forXYC(image, x, y, c) {
        float pixelValue = image(x, y, 0, c);
        sum += pow(pixelValue - meanValue, 3);
    }
    return sum / (image.size() * pow(varianceValue, 3));
}

float Characteristics::flatteningCoefficient(CImg<unsigned char> image) {
    float meanValue = mean(image);
    float varianceValue = variance(image);
    float sum = 0;
    cimg_forXYC(image, x, y, c) {
        float pixelValue = image(x, y, 0, c);
        sum += pow(pixelValue - meanValue, 4);
    }
    return sum / (image.size() * pow(varianceValue, 4));
}

float Characteristics::entropy(CImg<unsigned char> image) {
    std::map<uint8_t, int> histogram;
    cimg_forXYC(image, x, y, c) {
        unsigned char pixelValue = image(x, y, 0, c);
        histogram[pixelValue]++;
    }

    float entropyValue = 0;
    for (const auto& pair : histogram) {
        float probability = static_cast<float>(pair.second) / image.size();
        entropyValue += probability * log2(probability);
    }

    return -entropyValue;
}