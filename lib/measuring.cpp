#include "../include/measuring.h"
#include "../include/CImg.h"
#include <cmath>

using namespace cimg_library;

float Measuring::signalToNoiseRatio(CImg<unsigned char> originalImage, CImg<unsigned char> modifiedImage) {
    float snr = 0.0;
    float originalSum = 0.0;
    float modifiedSum = 0.0;
    
    // squared sum of squares of original image
    cimg_forXY(originalImage, x, y) {
        originalSum += pow(originalImage(x, y, 0), 2);
    }

    // squared sum of squares of difference between original and modified image
    cimg_forXY(modifiedImage, x, y) {
        modifiedSum += pow(originalImage(x, y, 0) - modifiedImage(x, y, 0), 2);
    }

    snr = 10 * log10(originalSum / modifiedSum);
    
    return snr;
}