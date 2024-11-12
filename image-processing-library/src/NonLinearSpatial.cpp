#include "NonLinearSpatial.h"
#include <algorithm>
#include <cstdint>

NonLinearSpatial::NonLinearSpatial() {
}

NonLinearSpatial::~NonLinearSpatial() {
}

/**
 * @brief Applies the Rosenfeld operator to the given image.
 *
 * The Rosenfeld operator is a non-linear spatial filter that processes each pixel
 * by averaging the values of its neighboring pixels within a specified power range.
 *
 * @param image The input image to be processed.
 * @param power The power value that determines the range of neighboring pixels to consider.
 *              The range is calculated as 2^power.
 * @return A new image with the Rosenfeld operator applied.
 */
CImg<unsigned char> NonLinearSpatial::rosenfeldOperator(CImg<unsigned char> image, unsigned int power) {
    CImg<unsigned char> newImage = image;
    int P = pow(2, power);
    
    cimg_forXYC(image, x, y, c) {
        int leftP = std::min(x, P);
        int rightP = std::min(image.width() - x - 1, P);

        float sum = 0;

        for (int i = -leftP; i < 0; i++) {
            sum -= image(x + i, y, c);
        }

        for (int j = 0; j < rightP; j++) {
            sum += image(x + j, y, c);
        }

        newImage(x, y, c) = static_cast<uint8_t>(std::clamp(sum / (leftP + rightP + 1), 0.0f, 255.0f));
    }

    return newImage;
}