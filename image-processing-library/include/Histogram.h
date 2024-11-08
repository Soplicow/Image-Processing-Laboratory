#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <vector>
#include <cstdint>
#include <map>
#include "CImg.h"
using namespace cimg_library;

class Histogram {
public:
    Histogram();
    ~Histogram();

    // void displayHistogram() const;
    static CImg<unsigned char> returnHistogramImage(CImg<unsigned char> image, int channel);
    static CImg<unsigned char> exponentialFPDF(CImg<unsigned char> image, int minBrightness, int maxBrightness, float alpha);
    static std::map<uint8_t, uint32_t> computeHistogram(CImg<unsigned char> image, int channel);

private:

};

#endif // HISTOGRAM_H