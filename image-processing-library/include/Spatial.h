#include <CImg.h>
#include <array>
#ifndef SPATIAL_H
#define SPATIAL_H

using namespace cimg_library;

namespace ImageProcessing {

class Spatial {
public:
    // Constructor
    Spatial();

    // Destructor
    ~Spatial();

    // Method to apply a spatial filter to an image
    CImg<unsigned char> extractionOfDetails(CImg<unsigned char> image, const char* mask);

private:
    void convolve(CImg<unsigned char>& image, const std::array<int, 9>& mask);
};

} // namespace ImageProcessing

#endif // SPATIAL_H