#include "BinaryOp.h"
#include "GlobalHelper.h"
#include <fstream>
#include <vector>
#include <queue>


CImg<unsigned char> BinaryOp::dilation(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel) {
    CImg<unsigned char> dilatedImage = GlobalHelper::createEmptyBinaryImage(image.width(), image.height());
    
    int buffer = kernel.size() / 2;

    forXYnoBorders(image, x, y, buffer) {
        if (image(x, y) == 255) {
            for (int i = 0; i < kernel.size(); i++) {
                for (int j = 0; j < kernel[i].size(); j++) {
                    if (kernel[j][i] == 1) {
                        dilatedImage(x + i - buffer, y + j - buffer) = 255;
                    }
                }
            }   
        }
    }

    return dilatedImage;
}

CImg<unsigned char> BinaryOp::erosion(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel) {
    CImg<unsigned char> erodedImage = GlobalHelper::createEmptyBinaryImage(image.width(), image.height());
    
    int buffer = kernel.size() / 2;

    forXYnoBorders(image, x, y, buffer) {
        bool isErosion = true;
        for (int i = 0; i < kernel.size(); i++) {
            for (int j = 0; j < kernel[i].size(); j++) {
                if (kernel[j][i] == 1 && image(x + i - buffer, y + j - buffer) != 255) {
                    isErosion = false;
                    break;
                }
            }
        }
        erodedImage(x, y) = isErosion ? 255 : 0;
    }

    return erodedImage;
}

CImg<unsigned char> BinaryOp::opening(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel) {
    return dilation(erosion(image, kernel), kernel);
}

CImg<unsigned char> BinaryOp::closing(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel) {
    return erosion(dilation(image, kernel), kernel);
}

CImg<unsigned char> BinaryOp::binarizeImage(const CImg<unsigned char>& image, unsigned char threshold) {
    CImg<unsigned char> binarizedImage = GlobalHelper::createEmptyImage(image.width(), image.height());

    cimg_forXY(image, x, y) {
        binarizedImage(x, y) = (image(x, y) > threshold) ? 1 : 0;
    }

    return binarizedImage;
}

bool BinaryOp::saveBinaryImage(const CImg<unsigned char>& image, const char* filename) {
    try {
        std::ofstream pbm(filename, std::ios::binary);
        pbm << "P4\n" << image.width() << " " << image.height() << "\n";
        for (int y = 0; y < image.height(); y++) {
            unsigned char byte = 0;
            for (int x = 0; x < image.width(); x++) {
                byte == (byte << 1) | image(x, y);
                if (x % 8 == 7 || x == image.width() - 1) {
                    pbm.put(byte);
                    byte = 0;
                }
            }
        }
        pbm.close();

        return true;
    } catch (std::exception& e) {
        return false;
    }
}

CImg<unsigned char> BinaryOp::imageSubtract(const CImg<unsigned char>& imageA, const CImg<unsigned char>& imageB) {
    CImg<unsigned char> result = GlobalHelper::createEmptyBinaryImage(imageA.width(), imageA.height());

    cimg_forXY(imageA, x, y) {
        result(x, y) = (imageA(x, y) == 255 && imageB(x, y) == 0) ? 255 : 0;
    }

    return result;
}

CImg<unsigned char> BinaryOp::imageSum(const CImg<unsigned char>& imageA, const CImg<unsigned char>& imageB) {
    CImg<unsigned char> result = GlobalHelper::createEmptyBinaryImage(imageA.width(), imageA.height());

    cimg_forXY(imageA, x, y) {
        result(x, y) = (imageA(x, y) == 255 || imageB(x, y) == 255) ? 255 : 0;
    }

    return result;
}

CImg<unsigned char> BinaryOp::imageIntersection(const CImg<unsigned char>& imageA, const CImg<unsigned char>& imageB) {
    CImg<unsigned char> result = GlobalHelper::createEmptyBinaryImage(imageA.width(), imageA.height());

    cimg_forXY(imageA, x, y) {
        result(x, y) = (imageA(x, y) == 255 && imageB(x, y) == 255) ? 255 : 0;
    }

    return result;
}

CImg<unsigned char> BinaryOp::M7(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel, int k) {
    std::vector<CImg<unsigned char>> stages;
    CImg<unsigned char> result = GlobalHelper::createEmptyBinaryImage(image.width(), image.height());

    for (int i = 0; i <= k; ++i) {
        if (i == 0) {
            stages.push_back(image);
        } else {
            stages.push_back(erosion(stages[i - 1], kernel));
        }
    }

    for (int i = 0; i <= k; ++i) {
        result = imageSum(result, imageSubtract(stages[i], opening(stages[i], kernel)));
    }
    
    return result;
}

CImg<unsigned char> BinaryOp::complement(const CImg<unsigned char>& image) {
    CImg<unsigned char> result = GlobalHelper::createEmptyBinaryImage(image.width(), image.height());

    cimg_forXY(image, x, y) {
        result(x, y) = (image(x, y) == 255) ? 0 : 255;
    }

    return result;
}

CImg<unsigned char> BinaryOp::HMT(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernelA, const std::array<std::array<bool, 3>, 3>& kernelB) {
    CImg<unsigned char> result = GlobalHelper::createEmptyBinaryImage(image.width(), image.height());
    CImg<unsigned char> imageComplement = BinaryOp::complement(image);

    return imageIntersection(erosion(image, kernelA), erosion(imageComplement, kernelB));
}

CImg<unsigned char> BinaryOp::regionGrowing(const CImg<unsigned char>& image, int seedX, int seedY, int threshold) { // threshold 0 for binary images
    // Create the result binary image
    CImg<unsigned char> result(image.width(), image.height(), 1, 1, 0); // Initialize to 0 (black)
    
    // Seed pixel intensity
    unsigned char seedValue = image(seedX, seedY);
    result(seedX, seedY) = 255; // Mark the seed as part of the region (white)
    
    // Directions for 4-connectivity (up, down, left, right)
    // const int dx[4] = {-1, 1, 0, 0};
    // const int dy[4] = {0, 0, -1, 1};

    // Directions for 8-connectivity (up, down, left, right, top-left, top-right, bottom-left, bottom-right)
    const int dx[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
    const int dy[8] = {0, 0, -1, 1, -1, -1, 1, 1};
    
    // Queue for region-growing (BFS)
    std::queue<std::pair<int, int>> pixelQueue;
    pixelQueue.push({seedX, seedY});
    
    while (!pixelQueue.empty()) {
        auto [x, y] = pixelQueue.front();
        pixelQueue.pop();
        
        // Check all 8 neighbors
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            // Ensure the neighbor is within image bounds and not yet visited
            if (nx >= 0 && nx < image.width() && ny >= 0 && ny < image.height() && result(nx, ny) == 0) {
                
                // Threshold-based inclusion for grayscale images
                if (std::abs(image(nx, ny) - seedValue) <= threshold) {
                    result(nx, ny) = 255; // Add to the region
                    pixelQueue.push({nx, ny}); // Push to queue for further exploration
                }
            }
        }
    }
    
    return result;
}


// Kernels
const std::array<std::array<bool, 3>, 3> kernel_1 = {{{0, 0, 0}, {0, 1, 1}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_2 = {{{0, 0, 0}, {0, 1, 0}, {0, 1, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_3 = {{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}};
const std::array<std::array<bool, 3>, 3> kernel_4 = {{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_5 = {{{0, 0, 0}, {0, 1, 1}, {0, 1, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_6 = {{{0, 0, 0}, {0, 0, 1}, {0, 1, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_7 = {{{0, 0, 0}, {1, 1, 1}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_8 = {{{0, 0, 0}, {1, 0, 1}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_9 = {{{0, 0, 0}, {1, 1, 0}, {1, 0, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_10 = {{{0, 1, 1}, {0, 1, 0}, {0, 0, 0}}};

const std::array<std::array<bool, 3>, 3> kernel_11_left = {{{1, 0, 0}, {1, 0, 0}, {1, 0, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_11_right = {{{0, 0, 1}, {0, 0, 1}, {0, 0, 1}}};
const std::array<std::array<bool, 3>, 3> kernel_11_up = {{{1, 1, 1}, {0, 0, 0}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_11_down = {{{0, 0, 0}, {0, 0, 0}, {1, 1, 1}}};
const std::array<std::array<bool, 3>, 3> kernel_11_complement = {{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}}; 

const std::array<std::array<bool, 3>, 3> kernel_12_bottom = {{{0, 0, 0}, {0, 1, 0}, {1, 1, 1}}};
const std::array<std::array<bool, 3>, 3> kernel_12_bottom_complement = {{{1, 1, 1}, {0, 0, 0}, {0, 0, 0}}};

const std::array<std::array<bool, 3>, 3> kernel_12_top = {{{1, 1, 1}, {0, 1, 0}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_12_top_complement = {{{0, 0, 0}, {0, 0, 0}, {1, 1, 1}}};

const std::array<std::array<bool, 3>, 3> kernel_12_left = {{{1, 0, 0}, {1, 1, 0}, {1, 0, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_12_left_complement = {{{0, 0, 1}, {0, 0, 1}, {0, 0, 1}}};

const std::array<std::array<bool, 3>, 3> kernel_12_right = {{{0, 0, 1}, {0, 1, 1}, {0, 0, 1}}};
const std::array<std::array<bool, 3>, 3> kernel_12_right_complement = {{{1, 0, 0}, {1, 0, 0}, {1, 0, 0}}};

const std::array<std::array<bool, 3>, 3> kernel_12_bottom_left = {{{0, 0, 0}, {1, 1, 0}, {1, 1, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_12_bottom_left_complement = {{{0, 1, 1}, {0, 0, 1}, {0, 0, 0}}};

const std::array<std::array<bool, 3>, 3> kernel_12_bottom_right = {{{0, 0, 0}, {0, 1, 1}, {0, 1, 1}}};
const std::array<std::array<bool, 3>, 3> kernel_12_bottom_right_complement = {{{1, 1, 0}, {1, 0, 0}, {0, 0, 0}}};

const std::array<std::array<bool, 3>, 3> kernel_12_top_left = {{{1, 1, 0}, {1, 1, 0}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_12_top_left_complement = {{{0, 0, 0}, {0, 0, 1}, {0, 1, 1}}};

const std::array<std::array<bool, 3>, 3> kernel_12_top_right = {{{0, 1, 1}, {0, 1, 1}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> kernel_12_top_right_complement = {{{0, 0, 0}, {1, 0, 0}, {1, 1, 0}}};