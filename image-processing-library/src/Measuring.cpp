#include "Measuring.h"
#include <cmath>

using namespace cimg_library;

float Measuring::signalToNoiseRatio(CImg<unsigned char> originalImage, CImg<unsigned char> modifiedImage) {
    float snr = 0.0;
    float originalSum = 0.0;
    float modifiedSum = 0.0;
    
    // squared sum of squares of original image
    cimg_forXYZC(originalImage, x, y, z, c) {
        originalSum += pow(originalImage(x, y, z, c), 2);
    }

    // squared sum of squares of difference between original and modified image
    cimg_forXYZC(modifiedImage, x, y, z, c) {
        modifiedSum += pow(originalImage(x, y, z, c) - modifiedImage(x, y, z, c), 2);
    }

    snr = 10 * log10(originalSum / modifiedSum);
    
    return snr;
}

float Measuring::peakSignalToNoiseRatio(CImg<unsigned char> originalImage, CImg<unsigned char> modifiedImage) {
    float psnr = 0.0;
    
    psnr = 20*log10(255) - 10*log10(meanSquareError(originalImage, modifiedImage));
    return psnr;
}

float Measuring::meanSquareError(CImg<unsigned char> originalImage, CImg<unsigned char> modifiedImage) {
    float mse = 0.0;
    cimg_forXYZC(originalImage, x, y, z, c) {
        mse += pow(originalImage(x, y, z, c) - modifiedImage(x, y, z, c), 2);
    }
    mse /= originalImage.width() * originalImage.height() * originalImage.depth() * originalImage.spectrum();
    return mse;
}

float Measuring::peakMeanSquareError(CImg<unsigned char> originalImage, CImg<unsigned char> modifiedImage) {
    float pmse = 0.0;
    pmse = meanSquareError(originalImage, modifiedImage) / pow(255, 2);
    return pmse;
}

float Measuring::maximumDifference(CImg<unsigned char> originalImage, CImg<unsigned char> modifiedImage) {
    int maxDiff = 0;
    cimg_forXYZC(originalImage, x, y, z, c) {
        maxDiff = std::max(maxDiff, abs(originalImage(x, y, z, c) - modifiedImage(x, y, z, c)));
    }
    return maxDiff;
}