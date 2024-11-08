#include "Noise.h"
#include "GlobalHelper.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

using namespace cimg_library;

/**
 * Applies a minimum filter to the given image.
 *
 * The minimum filter replaces each pixel value with the minimum value
 * within a specified window size centered around the pixel.
 *
 * @param image The input image to be filtered.
 * @param windowSize The size of the window to be used for the filter. Must be an odd number.
 * @return A new image with the minimum filter applied.
 * @throws std::invalid_argument if the window size is not an odd number.
 */
CImg<unsigned char> Noise::minFilter(CImg<unsigned char> image, int windowSize) {
    if (windowSize % 2 == 0) {
        throw std::invalid_argument("Window size must be odd");
    }

    CImg<unsigned char> filteredImage = image;
    int halfWindowSize = windowSize / 2;
    int windowArea = windowSize * windowSize;

    for (int c = 0; c < image.spectrum(); ++c) { // Iterate over each color channel
        for (int x = halfWindowSize; x < image.width() - halfWindowSize; ++x) {
            for (int y = halfWindowSize; y < image.height() - halfWindowSize; ++y) {
                int* window = new int[windowArea];
                int windowIndex = 0;

                for (int i = x - halfWindowSize; i <= x + halfWindowSize; ++i) {
                    for (int j = y - halfWindowSize; j <= y + halfWindowSize; ++j) {
                        window[windowIndex++] = image(i, j, 0, c);
                    }
                }

                std::sort(window, window + windowIndex);
                filteredImage(x, y, 0, c) = window[0]; // Minimum value

                delete[] window;
            }
        }
    }    

    return filteredImage;
}

/**
 * Applies a maximum filter to the given image.
 *
 * The maximum filter replaces each pixel value with the maximum value
 * within a specified window size centered around the pixel.
 *
 * @param image The input image to be filtered.
 * @param windowSize The size of the window to be used for the maximum filter.
 *                   Must be an odd number.
 * @return A new image with the maximum filter applied.
 * @throws std::invalid_argument if the window size is not an odd number.
 */
CImg<unsigned char> Noise::maxFilter(CImg<unsigned char> image, int windowSize) {
    if (windowSize % 2 == 0) {
        throw std::invalid_argument("Window size must be odd");
    }

    CImg<unsigned char> filteredImage = image;
    int halfWindowSize = windowSize / 2;
    int windowArea = windowSize * windowSize;

    for (int c = 0; c < image.spectrum(); ++c) { // Iterate over each color channel
        for (int x = halfWindowSize; x < image.width() - halfWindowSize; ++x) {
            for (int y = halfWindowSize; y < image.height() - halfWindowSize; ++y) {
                
                int* window = new int[windowArea];
                int windowIndex = 0;

                for (int i = x - halfWindowSize; i <= x + halfWindowSize; ++i) {
                    for (int j = y - halfWindowSize; j <= y + halfWindowSize; ++j) {
                        window[windowIndex++] = image(i, j, 0, c);
                    }
                }

                std::sort(window, window + windowIndex);
                filteredImage(x, y, 0, c) = window[windowIndex - 1]; // Maximum value

                delete[] window;
            }
        }
    }

    return filteredImage;
}

/**
 * Applies an adaptive median filter to the given image.
 *
 * The adaptive median filter is used to remove noise from an image while preserving edges.
 * It works by iteratively increasing the window size until a suitable median value is found
 * or the maximum window size is reached.
 *
 * @param image The input image to be filtered.
 * @param windowSize The initial window size for the filter. Must be an odd number.
 * @param maxWindowSize The maximum window size for the filter. Must be an odd number.
 * @return The filtered image.
 * @throws std::invalid_argument if the initial window size is not odd.
 * @throws std::invalid_argument if the maximum window size is not odd.
 */
CImg<unsigned char> Noise::adaptiveMedianFilter(CImg<unsigned char> image, int windowSize, int maxWindowSize) {
    if (windowSize % 2 == 0) {
        throw std::invalid_argument("Window size must be odd");
    }

    if (maxWindowSize % 2 == 0) {
        throw std::invalid_argument("Max window size must be odd");
    }

    CImg<unsigned char> filteredImage = image;

    for (int c = 0; c < image.spectrum(); ++c) { // Iterate over each color channel
        for (int x = maxWindowSize / 2; x < image.width() - maxWindowSize / 2; ++x) {
            for (int y = maxWindowSize / 2; y < image.height() - maxWindowSize / 2; ++y) {
                int currentWindowSize = windowSize;
                bool pixelProcessed = false;

                while (!pixelProcessed) {
                    int halfWindowSize = currentWindowSize / 2;
                    std::vector<int> window;

                    for (int i = x - halfWindowSize; i <= x + halfWindowSize; ++i) {
                        for (int j = y - halfWindowSize; j <= y + halfWindowSize; ++j) {
                            window.push_back(image(i, j, 0, c));
                        }
                    }

                    std::sort(window.begin(), window.end());
                    int zmin = window.front();
                    int zmax = window.back();
                    int zmed = window[window.size() / 2];
                    int zxy = image(x, y, 0, c);

                    // Stage A
                    int A1 = zmed - zmin;
                    int A2 = zmed - zmax;
                    if (A1 > 0 && A2 < 0) {
                        // Stage B
                        int B1 = zxy - zmin;
                        int B2 = zxy - zmax;
                        if (B1 > 0 && B2 < 0) {
                            filteredImage(x, y, 0, c) = zxy;
                        } else {
                            filteredImage(x, y, 0, c) = zmed;
                        }
                        pixelProcessed = true;
                    } else {
                        // Increase window size if possible
                        if (currentWindowSize < maxWindowSize) {
                            currentWindowSize += 2;
                        } else {
                            filteredImage(x, y, 0, c) = zxy;
                            pixelProcessed = true;
                        }
                    }
                }
            }
        }
    }
    
    return filteredImage;
}