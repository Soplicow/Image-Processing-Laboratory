#include "Measuring.h"
#include <cmath>

using namespace cimg_library;

/**
 * @brief Computes the Signal-to-Noise Ratio (SNR) between an original image and a modified image.
 *
 * The SNR is calculated using the formula:
 * SNR = 10 * log10(sum(originalImage^2) / sum((originalImage - modifiedImage)^2))
 *
 * @param originalImage The original image.
 * @param modifiedImage The modified image.
 * @return The Signal-to-Noise Ratio (SNR) in decibels (dB).
 */
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

/**
 * @brief Calculates the Peak Signal-to-Noise Ratio (PSNR) between two images.
 *
 * The PSNR is a measure of the quality of the modified image compared to the original image.
 * It is expressed in decibels (dB) and is calculated using the formula:
 * 
 * \f[
 * \text{PSNR} = 20 \cdot \log_{10}(255) - 10 \cdot \log_{10}(\text{MSE})
 * \f]
 * 
 * where MSE is the Mean Square Error between the original and modified images.
 *
 * @param originalImage The original image.
 * @param modifiedImage The modified image.
 * @return The PSNR value in decibels (dB).
 */
float Measuring::peakSignalToNoiseRatio(CImg<unsigned char> originalImage, CImg<unsigned char> modifiedImage) {
    float psnr = 0.0;
    
    psnr = 20*log10(255) - 10*log10(meanSquareError(originalImage, modifiedImage));
    return psnr;
}

/**
 * @brief Computes the Mean Square Error (MSE) between two images.
 *
 * This function calculates the Mean Square Error (MSE) between the original image
 * and the modified image. The MSE is a measure of the average squared difference
 * between corresponding pixels of the two images.
 *
 * @param originalImage The original image.
 * @param modifiedImage The modified image to compare against the original image.
 * @return The Mean Square Error (MSE) value.
 */
float Measuring::meanSquareError(CImg<unsigned char> originalImage, CImg<unsigned char> modifiedImage) {
    float mse = 0.0;
    cimg_forXYZC(originalImage, x, y, z, c) {
        mse += pow(originalImage(x, y, z, c) - modifiedImage(x, y, z, c), 2);
    }
    mse /= originalImage.width() * originalImage.height() * originalImage.depth() * originalImage.spectrum();
    return mse;
}

/**
 * @brief Calculates the Peak Mean Square Error (PMSE) between the original and modified images.
 *
 * The PMSE is a normalized version of the Mean Square Error (MSE) that divides the MSE by the square of the maximum possible pixel value (255 for 8-bit images).
 *
 * @param originalImage The original image to compare.
 * @param modifiedImage The modified image to compare.
 * @return The Peak Mean Square Error (PMSE) value.
 */
float Measuring::peakMeanSquareError(CImg<unsigned char> originalImage, CImg<unsigned char> modifiedImage) {
    float pmse = 0.0;
    pmse = meanSquareError(originalImage, modifiedImage) / pow(255, 2);
    return pmse;
}

/**
 * @brief Computes the maximum difference between corresponding pixels of two images.
 *
 * This function iterates over each pixel in the original and modified images,
 * calculates the absolute difference between the corresponding pixels, and
 * returns the maximum difference found.
 *
 * @param originalImage The original image.
 * @param modifiedImage The modified image.
 * @return The maximum absolute difference between corresponding pixels of the two images.
 */
float Measuring::maximumDifference(CImg<unsigned char> originalImage, CImg<unsigned char> modifiedImage) {
    int maxDiff = 0;
    cimg_forXYZC(originalImage, x, y, z, c) {
        maxDiff = std::max(maxDiff, abs(originalImage(x, y, z, c) - modifiedImage(x, y, z, c)));
    }
    return maxDiff;
}