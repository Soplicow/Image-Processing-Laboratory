#include "Elementary.h"
#include "GlobalHelper.h"
#include <algorithm>
#include <map>


CImg<unsigned char> Elementary::brightnessMod(CImg<unsigned char> image, int brightness) {
    CImg<unsigned char> modifiedImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    std::map<int, int> lookupTable;
    for (int i = 0; i < 256; ++i) {
        lookupTable[i] = std::clamp(i + brightness, 0, 255);
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
        lookupTable[i] = std::clamp(static_cast<int>(contrast * (i - 128) + 128), 0, 255);
    }

    cimg_forXYC(image, x, y, c) {
        modifiedImage(x, y, c) = lookupTable[image(x, y, c)];
    }
    return modifiedImage;
}

CImg<unsigned char> Elementary::negative(CImg<unsigned char> image) {
    CImg<unsigned char> modifiedImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    std::map<int, int> lookupTable;
    for (int i = 0; i < 256; ++i) {
        lookupTable[i] = 255 - i;
    }

    cimg_forXYC(image, x, y, c) {
        modifiedImage(x, y, c) = lookupTable[image(x, y, c)];
    }
    return modifiedImage;
}

