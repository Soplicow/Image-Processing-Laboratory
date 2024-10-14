#include "Elementary.h"
#include "GlobalHelper.h"
#include <algorithm>
#include <map>


CImg<unsigned char> Elementary::brightnessMod(CImg<unsigned char> image, int brightness) {
    CImg<unsigned char> modifiedImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    std::map<int, int> lookupTable;
    for (int i = 0; i < 256; ++i) {
        lookupTable[i] = std::min(255, std::max(0, i + brightness));
    }
    // cast the image values to int and cap them between 0 and 255
    // and add them to modifiedImage
    cimg_forXYC(image, x, y, c) {    
        modifiedImage(x, y, c) = lookupTable[image(x, y, c)];
    }
    return modifiedImage;
}

CImg<unsigned char> Elementary::contrastMod(CImg<unsigned char> image, float contrast) {
    CImg<unsigned char> modifiedImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    std::map<int, int> lookupTable;
    for (int i = 0; i < 256; ++i) {
        lookupTable[i] = std::min(255, std::max(0, static_cast<int>(contrast * (i - 128) + 128)));
    }

    cimg_forXY(image, x, y) {
        modifiedImage(x, y, 0) = lookupTable[image(x, y, 0)];
        modifiedImage(x, y, 1) = lookupTable[image(x, y, 1)];
        modifiedImage(x, y, 2) = lookupTable[image(x, y, 2)];
    }
    return modifiedImage;
}

CImg<unsigned char> Elementary::negative(CImg<unsigned char> image) {
    CImg<unsigned char> modifiedImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    std::map<int, int> lookupTable;
    for (int i = 0; i < 256; ++i) {
        lookupTable[i] = 255 - i;
    }

    cimg_forXY(image, x, y) {
        modifiedImage(x, y, 0) = lookupTable[image(x, y, 0)];
        modifiedImage(x, y, 1) = lookupTable[image(x, y, 1)];
        modifiedImage(x, y, 2) = lookupTable[image(x, y, 2)];
    }
    return modifiedImage;
}

