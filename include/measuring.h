#ifndef MEASURING_H
#define MEASURING_H

#include "../include/CImg.h"

using namespace cimg_library;
class Measuring {
public:

    static float signalToNoiseRatio(CImg<unsigned char> originalImage, CImg<unsigned char> modifiedImage);

private:
    // Add private members if needed
};

#endif // MEASURING_H