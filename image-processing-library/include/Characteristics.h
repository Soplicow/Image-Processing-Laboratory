#include "CImg.h"
#ifndef CHARACTERISTICS_H
#define CHARACTERISTICS_H

using namespace cimg_library;

class Characteristics {
public:
    // Constructor
    Characteristics();

    // Destructor
    ~Characteristics();

    float mean(CImg<unsigned char> image);

    float variance(CImg<unsigned char> image);

    float standardDeviation(CImg<unsigned char> image);

    float variationCoefficient_1(CImg<unsigned char> image);

    float variationCoefficient_2(CImg<unsigned char> image);

    float assymetryCoefficient(CImg<unsigned char> image);

    float flatteningCoefficient(CImg<unsigned char> image);

    float entropy(CImg<unsigned char> image);

private:

};

#endif // CHARACTERISTICS_H