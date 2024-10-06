#ifndef ELEMENTARY_H
#define ELEMENTARY_H

#include "../include/CImg.h"

using namespace cimg_library;

class Elementary {
public:
    // Constructor
    Elementary();

    // Destructor
    ~Elementary();

    static CImg<unsigned char> brightnessMod(CImg<unsigned char> image, int brightness);

    static CImg<unsigned char> contrastMod(CImg<unsigned char> image, float contrast);

    static CImg<unsigned char> negative(CImg<unsigned char> image);

private:
    // Add any private members if needed
};

#endif // ELEMENTARY_H