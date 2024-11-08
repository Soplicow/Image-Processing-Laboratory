#include <CImg.h>
#ifndef NLINEARSPATIAL_H
#define NLINEARSPATIAL_H

using namespace cimg_library;

class NonLinearSpatial {
public:
    NonLinearSpatial();
    ~NonLinearSpatial();

    static CImg<unsigned char> rosenfeldOperator(CImg<unsigned char> image, unsigned int power);

private:
    
};

#endif // NLINEARSPATIAL_H