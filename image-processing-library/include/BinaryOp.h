#ifndef BINARY_H
#define BINARY_H

#include <CImg.h>
#include <array>

using namespace cimg_library;

class BinaryOp {
public:
    // Constructor
    BinaryOp();

    // Destructor
    ~BinaryOp();

    static CImg<unsigned char> binarizeImage(const CImg<unsigned char>& image, unsigned char threshold);

    static bool saveBinaryImage(const CImg<unsigned char>& image, const char* filename);

    static CImg<unsigned char> dilation(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel);

    static CImg<unsigned char> erosion(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel);

    static CImg<unsigned char> opening(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel);

    static CImg<unsigned char> closing(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel);

    static CImg<unsigned char> HMT(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernelA, const std::array<std::array<bool, 3>, 3>& kernelB);

    static CImg<unsigned char> imageSubtract(const CImg<unsigned char>& imageA, const CImg<unsigned char>& imageB);

    static CImg<unsigned char> imageSum(const CImg<unsigned char>& imageA, const CImg<unsigned char>& imageB);

    static CImg<unsigned char> imageIntersection(const CImg<unsigned char>& imageA, const CImg<unsigned char>& imageB);

    static CImg<unsigned char> M7(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel, int k);

    static CImg<unsigned char> complement(const CImg<unsigned char>& image);

    static CImg<unsigned char> regionGrowing(const CImg<unsigned char>& image, int seedX, int seedY, int threshold);

private:
    static const std::array<std::array<bool, 3>, 3> kernel_1;
    static const std::array<std::array<bool, 3>, 3> kernel_2;
    static const std::array<std::array<bool, 3>, 3> kernel_3;
    static const std::array<std::array<bool, 3>, 3> kernel_4;
    static const std::array<std::array<bool, 3>, 3> kernel_5;
    static const std::array<std::array<bool, 3>, 3> kernel_6;
    static const std::array<std::array<bool, 3>, 3> kernel_7;
    static const std::array<std::array<bool, 3>, 3> kernel_8;
    static const std::array<std::array<bool, 3>, 3> kernel_9;
    static const std::array<std::array<bool, 3>, 3> kernel_10;

    static const std::array<std::array<bool, 3>, 3> kernel_11_left;
    static const std::array<std::array<bool, 3>, 3> kernel_11_right;
    static const std::array<std::array<bool, 3>, 3> kernel_11_up;
    static const std::array<std::array<bool, 3>, 3> kernel_11_down;
    static const std::array<std::array<bool, 3>, 3> kernel_11_complement;

    static const std::array<std::array<bool, 3>, 3> kernel_12_bottom;
    static const std::array<std::array<bool, 3>, 3> kernel_12_top;
    static const std::array<std::array<bool, 3>, 3> kernel_12_left;
    static const std::array<std::array<bool, 3>, 3> kernel_12_right;
    static const std::array<std::array<bool, 3>, 3> kernel_12_bottom_right;
    static const std::array<std::array<bool, 3>, 3> kernel_12_bottom_left;
    static const std::array<std::array<bool, 3>, 3> kernel_12_top_right;
    static const std::array<std::array<bool, 3>, 3> kernel_12_top_left;

    static const std::array<std::array<bool, 3>, 3> kernel_12_bottom_complement;
    static const std::array<std::array<bool, 3>, 3> kernel_12_top_complement;
    static const std::array<std::array<bool, 3>, 3> kernel_12_left_complement;
    static const std::array<std::array<bool, 3>, 3> kernel_12_right_complement;
    static const std::array<std::array<bool, 3>, 3> kernel_12_bottom_right_complement;
    static const std::array<std::array<bool, 3>, 3> kernel_12_bottom_left_complement;
    static const std::array<std::array<bool, 3>, 3> kernel_12_top_right_complement;
    static const std::array<std::array<bool, 3>, 3> kernel_12_top_left_complement;
};

#endif // BINARY_H