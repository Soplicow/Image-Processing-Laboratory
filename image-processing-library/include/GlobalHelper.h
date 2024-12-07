#ifndef GLOBALHELPER_H
#define GLOBALHELPER_H

#define forXYnoBorders(img, x, y, buffer) for (int y = buffer; y < img.height() - buffer; y++) for (int x = buffer; x < img.width() - buffer; x++)

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

    static CImg<unsigned char> createEmptyBinaryImage(int width, int height) {
        return CImg<unsigned char>(width, height, 1, 1, 0); // depth 1, 1 channel (binary), initialized to 0
    }

    static boolean isEqual(const CImg<unsigned char>& imageA, const CImg<unsigned char>& imageB) {
        if (imageA.width() != imageB.width() || imageA.height() != imageB.height()) {
            return false;
        }

        cimg_forXY(imageA, x, y) {
            if (imageA(x, y) != imageB(x, y)) {
                return false;
            }
        }

        return true;
    }
};

#endif // GLOBALHELPER_H