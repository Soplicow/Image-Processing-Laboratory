#include "elementary.h"
#include <algorithm>

Elementary::Elementary() {
    // Constructor
}

Elementary::~Elementary() {
    // Destructor
}

CImg<unsigned char> Elementary::brightnessMod(CImg<unsigned char> image, int brightness) {
    CImg<unsigned char> modifiedImage(image.width(), image.height(), 1, 3, 0);

    // cast the image values to int and cap them between 0 and 255
    // and add them to modifiedImage
    cimg_forXY(image, x, y) {
        modifiedImage(x, y, 0) = std::min(255, std::max(0, static_cast<int>(image(x, y, 0)) + brightness));
        modifiedImage(x, y, 1) = std::min(255, std::max(0, static_cast<int>(image(x, y, 1)) + brightness));
        modifiedImage(x, y, 2) = std::min(255, std::max(0, static_cast<int>(image(x, y, 2)) + brightness));
    }
    return modifiedImage;
}

CImg<unsigned char> Elementary::contrastMod(CImg<unsigned char> image, float contrast) {
    CImg<unsigned char> modifiedImage(image.width(), image.height(), 1, 3, 0);
    cimg_forXY(image, x, y) {
        modifiedImage(x, y, 0) = std::min(255.0f, std::max(0.0f, contrast * (static_cast<int>(image(x, y, 0)) - 128) + 128));
        modifiedImage(x, y, 1) = std::min(255.0f, std::max(0.0f, contrast * (static_cast<int>(image(x, y, 1)) - 128) + 128));
        modifiedImage(x, y, 2) = std::min(255.0f, std::max(0.0f, contrast * (static_cast<int>(image(x, y, 2)) - 128) + 128));
    }
    return modifiedImage;
}

CImg<unsigned char> Elementary::negative(CImg<unsigned char> image) {
    CImg<unsigned char> modifiedImage(image.width(), image.height(), 1, 3, 0);
    cimg_forXY(image, x, y) {
        modifiedImage(x, y, 0) = 255 - image(x, y, 0);
        modifiedImage(x, y, 1) = 255 - image(x, y, 1);
        modifiedImage(x, y, 2) = 255 - image(x, y, 2);
    }
    return modifiedImage;
}

