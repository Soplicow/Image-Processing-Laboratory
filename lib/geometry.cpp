#include "Geometry.h"
#include "GlobalHelper.h"

using namespace cimg_library;

CImg<unsigned char> Geometry::horizontalFlip(CImg<unsigned char> image) {
    CImg<unsigned char> flippedImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            for (int c = 0; c < image.spectrum(); c++) {
                flippedImage(x, y, c) = image(image.width() - x - 1, y, c);
            }
        }
    }
    return flippedImage;
}

CImg<unsigned char> Geometry::verticalFlip(CImg<unsigned char> image) {
    CImg<unsigned char> flippedImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            for (int c = 0; c < image.spectrum(); c++) {
                flippedImage(x, y, c) = image(x, image.height() - y - 1, c);
            }
        }
    }
    return flippedImage;
}

CImg<unsigned char> Geometry::diagonalFlip(CImg<unsigned char> image) {
    CImg<unsigned char> flippedImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            for (int c = 0; c < image.spectrum(); c++) {
                flippedImage(x, y, c) = image(y, x, c);
            }
        }
    }
    return flippedImage;
}

CImg<unsigned char> Geometry::imageShrinking(CImg<unsigned char> image, int factor) {
    CImg<unsigned char> shrunkImage = GlobalHelper::createEmptyImage(image.width() / factor, image.height() / factor);
    for (int x = 0; x < shrunkImage.width(); x++) {
        for (int y = 0; y < shrunkImage.height(); y++) {
            for (int c = 0; c < image.spectrum(); c++) {
                shrunkImage(x, y, 0) = image(x * factor, y * factor, c);
            }
        }
    }
    return shrunkImage;
}

CImg<unsigned char> Geometry::imageEnlargement(CImg<unsigned char> image, int factor) {
    CImg<unsigned char> enlargedImage = GlobalHelper::createEmptyImage(image.width() * factor, image.height() * factor);
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            for (int i = 0; i < factor; i++) {
                for (int j = 0; j < factor; j++) {
                    for (int c = 0; c < image.spectrum(); c++) {
                        enlargedImage(x * factor + i, y * factor + j, c) = image(x, y, c);
                    }
                }
            }
        }
    }
    return enlargedImage;
}