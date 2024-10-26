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

    void computeHistogram(CImg<unsigned char> image, int channel);
    // void displayHistogram() const;
    CImg<unsigned char> returnHistogramImage() const;

private:
    std::map<uint8_t, uint32_t> histogramData;
};

#endif // HISTOGRAM_H