#ifndef GLOBALHELPER_H
#define GLOBALHELPER_H

#include "CImg.h"
using namespace cimg_library;

class GlobalHelper {
public:
    // Constructor
    GlobalHelper() = default;

    // Method to create an empty image
    static CImg<unsigned char> createEmptyImage(int width, int height) {
        return CImg<unsigned char>(width, height, 1, 3, 0); // depth 1, 3 channels (RGB), initialized to 0
    }
};

#endif // GLOBALHELPER_H