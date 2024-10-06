#ifndef NOISE_H
#define NOISE_H

#include "../include/CImg.h"

using namespace cimg_library;
class Noise {
public:
    // Constructor
    Noise();

    // Destructor
    ~Noise();

    static CImg<unsigned char> medianFilter(CImg<unsigned char> image, int windowHorizontal, int windowVertical);

    static CImg<unsigned char> harmonicMeanFilter(CImg<unsigned char> image, int windowHorizontal, int windowVertical);

private:
    // Add any private members if needed
};

#endif // NOISE_H