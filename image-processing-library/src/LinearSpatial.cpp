#include "LinearSpatial.h"
#include <algorithm>
#include <GlobalHelper.h>
#include <iostream>

LinearSpatial::LinearSpatial() {
}

LinearSpatial::~LinearSpatial() {
}

/**
 * @brief Extracts details from the given image using a specified convolution mask.
 *
 * This function applies a convolution operation to the input image using one of the predefined masks
 * based on the provided mask identifier. The resulting image highlights specific details according to
 * the chosen mask.
 *
 * @param image The input image to be processed.
 * @param mask A string identifier for the convolution mask to be used. 
 *             Possible values are:
 *             - "N"  : North mask
 *             - "NE" : North-East mask
 *             - "E"  : East mask
 *             - "SE" : South-East mask
 * @return A new image with the details extracted based on the specified mask.
 */
CImg<unsigned char> LinearSpatial::extractionOfDetails(CImg<unsigned char> image, const char* mask) {
    CImg<unsigned char> newImage = image;
    if (strcmp(mask, "N") == 0) {
        optimizedExtractionOfDetailsN(newImage);
    } else if (strcmp(mask, "NE") == 0) {
        convolve(newImage, maskNE);
    } else if (strcmp(mask, "E") == 0) {
        convolve(newImage, maskE);
    } else if (strcmp(mask, "SE") == 0) {
        convolve(newImage, maskSE);
    }
    return newImage;    
}

/**
 * @brief Optimizes the extraction of details from an image using a specific mask.
 *
 * This function processes an input image and extracts details by applying a 
 * convolution-like operation with a predefined mask. The mask used in this 
 * function emphasizes certain details by summing and subtracting pixel values 
 * in a 3x3 neighborhood around each pixel.
 *
 * @param image The input image to be processed. It is expected to be a 
 *              CImg object with unsigned char pixel values.
 * @return A new image with the extracted details, represented as a CImg object 
 *         with unsigned char pixel values.
 */
void LinearSpatial::optimizedExtractionOfDetailsN(CImg<unsigned char>& image) {
    CImg<unsigned char> newImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    int maskSize = 3;
    int halfSize = 1;

    for (int x = halfSize; x < image.width() - halfSize; ++x) {
        for (int y = halfSize; y < image.height() - halfSize; ++y) {
            for (int c = 0; c < image.spectrum(); ++c) {
                
                int sum = 0;
                sum += image(x - 1, y - 1, c);   // maskN[0]
                sum += image(x - 1, y, c);       // maskN[1]
                sum += image(x - 1, y + 1, c);   // maskN[2]

                sum += image(x, y - 1, c);       // maskN[3]
                sum -= image(x, y, c) * -2;      // maskN[4]
                sum += image(x, y + 1, c);       // maskN[5]

                sum -= image(x + 1, y - 1, c);  // maskN[6]
                sum -= image(x + 1, y, c);      // maskN[7]
                sum -= image(x + 1, y + 1, c);  // maskN[8]
                
                newImage(x, y, c) = std::min(255, abs(sum));

            }
        }
    }
    image = newImage;
}

/**
 * @brief Applies a convolution operation to the given image using the specified mask.
 *
 * This function takes an input image and a convolution mask, and applies the mask to the image
 * to produce a new convolved image. The mask is expected to be a 3x3 array of integers.
 *
 * @param image The input image to be convolved. This image will be modified in place.
 * @param mask A 3x3 array of integers representing the convolution mask.
 */
void LinearSpatial::convolve(CImg<unsigned char>& image, const std::array<int, 9>& mask) {
    CImg<unsigned char> newImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    int maskSize = static_cast<int>(sqrt(mask.size()));
    int halfSize = maskSize / 2;

    for (int x = halfSize; x < image.width() - halfSize; ++x) {
        for (int y = halfSize; y < image.height() - halfSize; ++y) {
            for (int c = 0; c < image.spectrum(); ++c) {

                int sum = 0;
                for (int maskRow = -halfSize; maskRow <= halfSize; ++maskRow) {
                    for (int maskCol = -halfSize; maskCol <= halfSize; ++maskCol) {
                        int maskValue = mask[(maskRow + halfSize) * maskSize + (maskCol + halfSize)];
                        sum += image(x + maskRow, y + maskCol, c) * maskValue;
                    }
                }
                newImage(x, y, c) = std::clamp(sum, 0, 255);
            }
        }
    }

    image = newImage;
}