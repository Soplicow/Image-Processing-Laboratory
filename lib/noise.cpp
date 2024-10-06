#include "noise.h"
#include <algorithm>

using namespace cimg_library;
Noise::Noise() {
    // Constructor
}

Noise::~Noise() {
    // Destructor
}

CImg<unsigned char> Noise::medianFilter(CImg<unsigned char> image, int windowHorizontal, int windowVertical) {
    CImg<unsigned char> filteredImage(image.width(), image.height(), 1, 3, 0);
    cimg_forXY(image, x, y) {
        int windowSize = windowHorizontal * windowVertical;
        int* window = new int[windowSize];
        int windowIndex = 0;
        for (int i = x - windowHorizontal / 2; i <= x + windowHorizontal / 2; i++) {
            for (int j = y - windowVertical / 2; j <= y + windowVertical / 2; j++) {
                if (i >= 0 && i < image.width() && j >= 0 && j < image.height()) {
                    window[windowIndex++] = image(i, j, 0);
                }
            }
        }
        std::sort(window, window + windowSize);
        filteredImage(x, y, 0) = window[windowSize / 2];
        filteredImage(x, y, 1) = window[windowSize / 2];
        filteredImage(x, y, 2) = window[windowSize / 2];
        delete[] window;
    }
    return filteredImage;
}

CImg<unsigned char> Noise::harmonicMeanFilter(CImg<unsigned char> image, int windowHorizontal, int windowVertical) {
    CImg<unsigned char> filteredImage(image.width(), image.height(), 1, 3, 0);
    cimg_forXY(image, x, y) {
        int windowSize = windowHorizontal * windowVertical;
        float* window = new float[windowSize];
        int windowIndex = 0;
        for (int i = x - windowHorizontal / 2; i <= x + windowHorizontal / 2; i++) {
            for (int j = y - windowVertical / 2; j <= y + windowVertical / 2; j++) {
                if (i >= 0 && i < image.width() && j >= 0 && j < image.height()) {
                    window[windowIndex++] = 1.0f / image(i, j, 0);
                }
            }
        }
        float sum = 0.0f;
        for (int i = 0; i < windowSize; i++) {
            sum += window[i];
        }
        filteredImage(x, y, 0) = 1.0f / sum;
        filteredImage(x, y, 1) = 1.0f / sum;
        filteredImage(x, y, 2) = 1.0f / sum;

        delete[] window;
    }
    return filteredImage;
}