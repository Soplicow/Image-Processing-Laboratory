#include "Geometry.h"
#include "GlobalHelper.h"

using namespace cimg_library;

CImg<unsigned char> Geometry::horizontalFlip(CImg<unsigned char> image) {
    CImg<unsigned char> flippedImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    cimg_forXYC(flippedImage, x, y, c) {
        flippedImage(x, y, c) = image(image.width() - x - 1, y, c);
    }
    return flippedImage;
}

CImg<unsigned char> Geometry::verticalFlip(CImg<unsigned char> image) {
    CImg<unsigned char> flippedImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    cimg_forXYC(flippedImage, x, y, c) {
        flippedImage(x, y, c) = image(x, image.height() - y - 1, c);
    }
    return flippedImage;
}

CImg<unsigned char> Geometry::diagonalFlip(CImg<unsigned char> image) {
    CImg<unsigned char> flippedImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    cimg_forXYC(flippedImage, x, y, c) {
        flippedImage(x, y, c) = image(y, x, c);
    }
    return flippedImage;
}

CImg<unsigned char> Geometry::imageShrinking(CImg<unsigned char> image, int factor) {
    CImg<unsigned char> shrunkImage = GlobalHelper::createEmptyImage(image.width() / factor, image.height() / factor);
    cimg_forXYC(shrunkImage, x, y, c) {
        shrunkImage(x, y, c) = image(x * factor, y * factor, c);
    }
    return shrunkImage;
}

CImg<unsigned char> Geometry::imageEnlargement(CImg<unsigned char> image, int factor) {
    CImg<unsigned char> enlargedImage = GlobalHelper::createEmptyImage(image.width() * factor, image.height() * factor);

    cimg_forXYC(enlargedImage, x, y, c) {
        enlargedImage(x, y, c) = image(x / factor, y / factor, c);
    }
    return enlargedImage;
}