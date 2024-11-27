#include "NonLinearSpatial.h"
#include <algorithm>
#include <cstdint>
#include <GlobalHelper.h>
#include <vector>

NonLinearSpatial::NonLinearSpatial() {
}

NonLinearSpatial::~NonLinearSpatial() {
}

CImg<unsigned char> NonLinearSpatial::rosenfeldOperator(CImg<unsigned char> image, unsigned int power) {
    CImg<unsigned char> newImage = GlobalHelper::createEmptyImage(image.width(), image.height());
    int P = pow(2, power);

    cimg_forYC(image, y, c) {  // Iterate over rows (y) and channels (c)
        std::vector<int> prefixSum(image.width(), 0);
        prefixSum[0] = image(0, y, c);

        // Compute prefix sums for the current row
        for (int x = 0; x < image.width() - 1; x++) {
            prefixSum[x + 1] = prefixSum[x] + image(x, y, c);
        }

        // Compute the new pixel values using the prefix sums
        for (int x = 0; x < image.width(); x++) {
            int left = std::max(x - P, 0); // Start of the range
            int centre = x;
            int right = std::min(x + P - 1, image.width() - 1); // End of the range

            // Compute the sum for the range [x-P, x+P]
            float sum = prefixSum[right] - 2 * prefixSum[centre] + prefixSum[left];

            // Normalize and assign the new pixel value
            int totalPixels = right - left;
            newImage(x, y, c) = static_cast<uint8_t>(
                std::clamp(sum / static_cast<float>(totalPixels), 0.0f, 255.0f)
            );
        }
    }

    return newImage;
}