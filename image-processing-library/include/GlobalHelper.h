#ifndef GLOBALHELPER_H
#define GLOBALHELPER_H

#define forXYnoBorders(img, x, y, buffer) for (int y = buffer; y < img.height() - buffer; y++) for (int x = buffer; x < img.width() - buffer; x++)

#include "CImg.h"
#include <vector>
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

    static CImg<unsigned char> mergeChannels(std::vector<CImg<unsigned char>>& channels) {
        CImg<unsigned char> result(channels[0].width(), channels[0].height(), 1, channels.size(), 0);
        for (int i = 0; i < channels.size(); i++) {
            result.get_shared_channel(i) = channels[i];
        }
        return result;
    }

    // Method to merge multiple images into a single image (including depth)
    static CImg<double> mergeImages(std::vector<CImg<double>>& images) {
        CImg<double> result(images[0].width(), images[0].height(), images[0].depth(), images.size(), 0);
        for (int i = 0; i < images.size(); i++) {
            result.get_shared_channel(i) = images[i];
        }
        return result;
    }

    static CImg<unsigned char> doubleToUnsignedChar(const CImg<double>& image) {
        CImg<unsigned char> result(image.width(), image.height(), 1, 3, 0);
        if (image.spectrum() == 1) {
            cimg_forXY(image, x, y) {
                result(x, y, 0) = std::clamp((int)image(x, y), 0, 255);
                result(x, y, 1) = std::clamp((int)image(x, y), 0, 255);
                result(x, y, 2) = std::clamp((int)image(x, y), 0, 255);
            }
            return result;
        }
        cimg_forXYC(image, x, y, c) {
            result(x, y, c) = std::clamp((int)image(x, y, c), 0, 255);
        }
        return result;
    }
};

#endif // GLOBALHELPER_H