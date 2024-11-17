#include <CImg.h>
#include <array>
#ifndef SPATIAL_H
#define SPATIAL_H

using namespace cimg_library;

class LinearSpatial {
public:
    // Constructor
    LinearSpatial();

    // Destructor
    ~LinearSpatial();

    // Method to apply a spatial filter to an image
    CImg<unsigned char> extractionOfDetails(CImg<unsigned char> image, const char* mask);

    void optimizedExtractionOfDetailsN(CImg<unsigned char>& image);

private:
    void convolve(CImg<unsigned char>& image, const std::array<int, 9>& mask);

    const std::array<int, 9> maskN = {1, 1, 1, 1, -2, 1, -1, -1, -1};
    const std::array<int, 9> maskNE = {1, 1, 1, -1, -2, 1, -1, -1, 1};
    const std::array<int, 9> maskE = {-1, 1, 1, -1, -2, 1, -1, 1, 1};
    const std::array<int, 9> maskSE = {-1, -1, 1, -1, -2, 1, 1, 1, 1};
};

#endif // SPATIAL_H