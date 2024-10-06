#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../include/CImg.h"

using namespace cimg_library;

class Geometry {
public:
    static CImg<unsigned char> horizontalFlip(CImg<unsigned char> image);

    static CImg<unsigned char> verticalFlip(CImg<unsigned char> image);

    static CImg<unsigned char> diagonalFlip(CImg<unsigned char> image);

    static CImg<unsigned char> imageShrinking(CImg<unsigned char> image, int factor);

    static CImg<unsigned char> imageEnlargement(CImg<unsigned char> image, int factor);
};

#endif // GEOMETRY_H
