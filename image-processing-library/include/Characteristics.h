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

    static float mean(CImg<unsigned char> image);

    static float variance(CImg<unsigned char> image);

    static float standardDeviation(CImg<unsigned char> image);

    static float variationCoefficient_1(CImg<unsigned char> image);

    static float variationCoefficient_2(CImg<unsigned char> image);

    static float assymetryCoefficient(CImg<unsigned char> image);

    static float flatteningCoefficient(CImg<unsigned char> image);

    static float entropy(CImg<unsigned char> image);

private:

};

#endif // CHARACTERISTICS_H