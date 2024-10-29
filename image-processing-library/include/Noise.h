#ifndef NOISE_H
#define NOISE_H

#include "../include/CImg.h"

using namespace cimg_library;

namespace ImageProcessing {
class Noise {
public:

    static CImg<unsigned char> minFilter(CImg<unsigned char> image, int windowSize);

    static CImg<unsigned char> maxFilter(CImg<unsigned char> image, int windowSize);

    static CImg<unsigned char> adaptiveMedianFilter(CImg<unsigned char> image, int windowSize, int maxWindowSize);

private:

};

} // namespace ImageProcessing

#endif // NOISE_H