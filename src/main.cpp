#include "../include/CImg.h" // modify the path if necessary
#include <iostream>
using namespace cimg_library;

int main(int argc, char* argv[]) {
        if (argc < 3) {
                std::cerr << "Usage: " << "<image.bmp> " << "--command " << "[-argument=value [...]]" << std::endl;
                return 0;
        }

        CImg<unsigned char> originalImage(argv[0]);
        CImg<unsigned char> modifiedImage(originalImage);


}