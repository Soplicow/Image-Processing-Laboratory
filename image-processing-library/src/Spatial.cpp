#include "Spatial.h"
#include <algorithm>
#include <GlobalHelper.h>

CImg<unsigned char> Spatial::extractionOfDetails(CImg<unsigned char> image, const char* mask) {
    CImg<unsigned char> newImage = image;
    if (strcmp(mask, "N") == 0) {
        convolve(newImage, maskN);
    } else if (strcmp(mask, "NE") == 0) {
        convolve(newImage, maskNE);
    } else if (strcmp(mask, "E") == 0) {
        convolve(newImage, maskE);
    } else if (strcmp(mask, "SE") == 0) {
        convolve(newImage, maskSE);
    }
    return newImage;    
}

CImg<unsigned char> Spatial::optimizedExtractionOfDetailsN(CImg<unsigned char> image) {
    CImg<unsigned char> newImage = image;
    int maskSize = 3;
    int halfSize = 1;

    for (int x = halfSize; x < image.width() - halfSize; ++x) {
        for (int y = halfSize; y < image.height() - halfSize; ++y) {
            for (int c = 0; c < image.spectrum(); ++c) {
                
                int sum = 0;
                sum += image(x + 1, y + 1, c);
                sum += image(x, y + 1, c);
                sum += image(x - 1, y + 1, c);
                sum += image(x + 1, y, c);
                sum -= 2 * image(x, y, c);
                sum += image(x - 1, y, c);
                sum -= image(x + 1, y - 1, c);
                sum -= image(x, y - 1, c);
                sum -= image(x - 1, y - 1, c);
                // TODO: is this even optimized? task said it should be optimized but idk what to do here xd

                newImage(x, y, c) = std::clamp(sum, 0, 255);
            }
        }
    }
    return newImage;
}

void Spatial::convolve(CImg<unsigned char>& image, const std::array<int, 9>& mask) {
    CImg<unsigned char> newImage = image;
    int maskSize = sqrt(mask.size());
    int halfSize = maskSize / 2;

    for (int x = halfSize; x < image.width() - halfSize; ++x) {
        for (int y = halfSize; y < image.height() - halfSize; ++y) {
            for (int c = 0; c < image.spectrum(); ++c) {

                int sum = 0;
                for (int i = -halfSize; i < halfSize; ++i) {
                    for (int j = -halfSize; j < halfSize; ++j) {
                        int maskValue = mask[(i + halfSize) * maskSize + j + halfSize];
                        sum += image(x - i, y - j, c) * maskValue;
                    }
                }
                newImage(x, y, c) = std::clamp(sum, 0, 255);

            }
        }
    }

    image = newImage;
}