#include "../include/geometry.h"
#include "../include/CImg.h"

using namespace cimg_library;

CImg<unsigned char> Geometry::horizontalFlip(CImg<unsigned char> image) {
    CImg<unsigned char> flippedImage(image.width(), image.height(), 1, 3, 0);
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            flippedImage(x, y, 0) = image(image.width() - x - 1, y, 0);
            flippedImage(x, y, 1) = image(image.width() - x - 1, y, 1);
            flippedImage(x, y, 2) = image(image.width() - x - 1, y, 2);
        }
    }
    return flippedImage;
}

CImg<unsigned char> Geometry::verticalFlip(CImg<unsigned char> image) {
    CImg<unsigned char> flippedImage(image.width(), image.height(), 1, 3, 0);
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            flippedImage(x, y, 0) = image(x, image.height() - y - 1, 0);
            flippedImage(x, y, 1) = image(x, image.height() - y - 1, 1);
            flippedImage(x, y, 2) = image(x, image.height() - y - 1, 2);
        }
    }
    return flippedImage;
}

CImg<unsigned char> Geometry::diagonalFlip(CImg<unsigned char> image) {
    CImg<unsigned char> flippedImage(image.width(), image.height(), 1, 3, 0);
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            flippedImage(x, y, 0) = image(y, x, 0);
            flippedImage(x, y, 1) = image(y, x, 1);
            flippedImage(x, y, 2) = image(y, x, 2);
        }
    }
    return flippedImage;
}

CImg<unsigned char> Geometry::imageShrinking(CImg<unsigned char> image, int factor) {
    CImg<unsigned char> shrunkImage(image.width() / factor, image.height() / factor, 1, 3, 0);
    for (int x = 0; x < shrunkImage.width(); x++) {
        for (int y = 0; y < shrunkImage.height(); y++) {
            shrunkImage(x, y, 0) = image(x * factor, y * factor, 0);
            shrunkImage(x, y, 1) = image(x * factor, y * factor, 1);
            shrunkImage(x, y, 2) = image(x * factor, y * factor, 2);
        }
    }
    return shrunkImage;
}

CImg<unsigned char> Geometry::imageEnlargement(CImg<unsigned char> image, int factor) {
    CImg<unsigned char> enlargedImage(image.width() * factor, image.height() * factor, 1, 3, 0);
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            for (int i = 0; i < factor; i++) {
                for (int j = 0; j < factor; j++) {
                    enlargedImage(x * factor + i, y * factor + j, 0) = image(x, y, 0);
                    enlargedImage(x * factor + i, y * factor + j, 1) = image(x, y, 1);
                    enlargedImage(x * factor + i, y * factor + j, 2) = image(x, y, 2);
                }
            }
        }
    }
    return enlargedImage;
}