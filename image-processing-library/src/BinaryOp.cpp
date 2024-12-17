#include "BinaryOp.h"
#include "GlobalHelper.h"
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>

CImg<unsigned char> BinaryOp::dilation(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel) {
    CImg<unsigned char> dilatedImage = GlobalHelper::createEmptyBinaryImage(image.width(), image.height());
    
    int buffer = kernel.size() / 2;
    int kernelSize = kernel.size();

    cimg_forXY(image, x, y) {
        if (image(x, y) == 255) {
            for (int i = 0; i < kernelSize; i++) {
                for (int j = 0; j < kernelSize; j++) {
                    if (kernel[j][i]) {
                        int newX = x + i - buffer;
                        int newY = y + j - buffer;
                        if (newX >= 0 && newX < image.width() && newY >= 0 && newY < image.height()) {
                            dilatedImage(newX, newY) = 255;
                        }
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
    int kernelSize = kernel.size();

    forXYnoBorders(image, x, y, buffer) {
        bool isErosion = false;
        for (int i = 0; i < kernelSize && !isErosion; i++) {
            for (int j = 0; j < kernelSize; j++) {
                if (kernel[j][i] && image(x + i - buffer, y + j - buffer) != 255) {
                    isErosion = true;
                    break;
                }
            }
        }
        erodedImage(x, y) = isErosion ? 0 : 255;
    }

    return erodedImage;
}

CImg<unsigned char> BinaryOp::opening(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel) {
    return dilation(erosion(image, kernel), kernel);
}

CImg<unsigned char> BinaryOp::closing(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel) {
    return erosion(dilation(image, kernel), kernel);
}

// UNUSED
CImg<unsigned char> BinaryOp::binarizeImage(const CImg<unsigned char>& image, unsigned char threshold) {
    CImg<unsigned char> binarizedImage = GlobalHelper::createEmptyImage(image.width(), image.height());

    cimg_forXY(image, x, y) {
        binarizedImage(x, y) = (image(x, y) > threshold) ? 1 : 0;
    }

    return binarizedImage;
}

// UNUSED
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

CImg<unsigned char> BinaryOp::M7(const CImg<unsigned char>& image, const std::array<std::array<bool, 3>, 3>& kernel) {
    std::vector<CImg<unsigned char>> stages;
    CImg<unsigned char> result = GlobalHelper::createEmptyBinaryImage(image.width(), image.height());

    stages.push_back(image);
    while (true) {
        CImg<unsigned char> stage = erosion(stages.back(), kernel);
        if (GlobalHelper::isEqual(stage, result)) {
            break;
        }
        stages.push_back(stage);
    }

    for (const auto& stage : stages) {
        result = imageSum(result, imageSubtract(stage, opening(stage, kernel)));
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
    CImg<unsigned char> imageComplement = BinaryOp::complement(image);
    return imageIntersection(erosion(image, kernelA), erosion(imageComplement, kernelB));
}

CImg<unsigned char> BinaryOp::regionGrowing(const CImg<unsigned char>& image, int seedX, int seedY, int threshold, int criterion) { // threshold 0 for binary images
    // Create the result binary image
    CImg<unsigned char> result(image.width(), image.height(), 1, 1, 0); // Initialize to 0 (black)
    
    // Seed pixel intensity
    unsigned char seedValueR = image(seedX, seedY, 0, 0);
    unsigned char seedValueG = image(seedX, seedY, 0, 1);
    unsigned char seedValueB = image(seedX, seedY, 0, 2);
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
                unsigned char neighborValueR = image(nx, ny, 0, 0);
                unsigned char neighborValueG = image(nx, ny, 0, 1);
                unsigned char neighborValueB = image(nx, ny, 0, 2);
                float distance;

                if (criterion == 0) {
                    distance = std::sqrt(std::pow(neighborValueR - seedValueR, 2) + 
                                    std::pow(neighborValueG - seedValueG, 2) + 
                                    std::pow(neighborValueB - seedValueB, 2));
                } else if (criterion == 1) {
                    distance = std::abs(neighborValueR - seedValueR) + 
                                    std::abs(neighborValueG - seedValueG) + 
                                    std::abs(neighborValueB - seedValueB);
                } else if (criterion == 2) {
                    distance = std::max({std::abs(neighborValueR - seedValueR), 
                                            std::abs(neighborValueG - seedValueG), 
                                            std::abs(neighborValueB - seedValueB)});
                } else {
                    throw std::invalid_argument("Invalid criterion");
                }
                
                if (distance <= threshold) {
                    result(nx, ny) = 255; // Add to the region
                    pixelQueue.push({nx, ny}); // Push to queue for further exploration
                }
            }
        }
    }
    
    return result;
}

CImg<unsigned char> BinaryOp::task3Operations(const CImg<unsigned char>& image, int kernelNumber, std::string kernelDirection, std::string operation) {
    std::array<std::array<bool, 3>, 3> kernel;
    std::array<std::array<bool, 3>, 3> kernelComplement;
    
    switch (kernelNumber)
    {
    case (1):
        kernel = kernel_1;
        break;
    case (2):
        kernel = kernel_2;
        break;
    case (3):
        kernel = kernel_3;
        break;
    case (4):
        kernel = kernel_4;
        break;
    case (5):
        kernel = kernel_5;
        break;
    case (6):
        kernel = kernel_6;
        break;
    case (7):
        kernel = kernel_7;
        break;
    case (8):
        kernel = kernel_8;
        break;
    case (9):
        kernel = kernel_9;
        break;
    case (10):
        kernel = kernel_10;
        break;
    case (11):
        kernelComplement = kernel_11_complement;
        if (kernelDirection == "left") {
            kernel = kernel_11_left;
            break;
        } else if (kernelDirection == "right") {
            kernel = kernel_11_right;
            break;
        } else if (kernelDirection == "up") {
            kernel = kernel_11_up;
            break;
        } else if (kernelDirection == "down") {
            kernel = kernel_11_down;
            break;
        } else {
            throw std::invalid_argument("Invalid kernel direction");
            break;
        }
    case (12):
        if (kernelDirection == "left") {
            kernel = kernel_12_left;
            kernelComplement = kernel_12_left_complement;
            break;
        } else if (kernelDirection == "right") {
            kernel = kernel_12_right;
            kernelComplement = kernel_12_right_complement;
            break;
        } else if (kernelDirection == "top") {
            kernel = kernel_12_top;
            kernelComplement = kernel_12_top_complement;
            break;
        } else if (kernelDirection == "bottom") {
            kernel = kernel_12_bottom;
            kernelComplement = kernel_12_bottom_complement;
            break;
        } else if (kernelDirection == "top-left") {
            kernel = kernel_12_top_left;
            kernelComplement = kernel_12_top_left_complement;
            break;
        } else if (kernelDirection == "top-right") {
            kernel = kernel_12_top_right;
            kernelComplement = kernel_12_top_right_complement;
            break;
        } else if (kernelDirection == "bottom-left") {
            kernel = kernel_12_bottom_left;
            kernelComplement = kernel_12_bottom_left_complement;
            break;
        } else if (kernelDirection == "bottom-right") {
            kernel = kernel_12_bottom_right;
            kernelComplement = kernel_12_bottom_right_complement;
            break;
        } else {
            throw std::invalid_argument("Invalid kernel direction");
            break;
        }
        break;
    default:
        throw std::invalid_argument("Invalid kernel number");
        break;
    }

    if (operation == "erosion") {
        return BinaryOp::erosion(image, kernel);
    } else if (operation == "dilation") {
        return BinaryOp::dilation(image, kernel);
    } else if (operation == "opening") {
        return BinaryOp::opening(image, kernel);
    } else if (operation == "closing") {
        return BinaryOp::closing(image, kernel);
    } else if (operation == "HMT") {
        return BinaryOp::HMT(image, kernel, kernelComplement);
    } else if (operation == "M7") {
        return BinaryOp::M7(image, kernel);
    } else {
        throw std::invalid_argument("Invalid operation");
    }
}

// Kernels
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_1 = {{{0, 0, 0}, {0, 1, 1}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_2 = {{{0, 0, 0}, {0, 1, 0}, {0, 1, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_3 = {{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_4 = {{{0, 1, 0}, {1, 1, 1}, {0, 1, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_5 = {{{0, 0, 0}, {0, 1, 1}, {0, 1, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_6 = {{{0, 0, 0}, {0, 0, 1}, {0, 1, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_7 = {{{0, 0, 0}, {1, 1, 1}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_8 = {{{0, 0, 0}, {1, 0, 1}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_9 = {{{0, 0, 0}, {1, 1, 0}, {1, 0, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_10 = {{{0, 1, 1}, {0, 1, 0}, {0, 0, 0}}};

const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_11_left = {{{1, 0, 0}, {1, 0, 0}, {1, 0, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_11_right = {{{0, 0, 1}, {0, 0, 1}, {0, 0, 1}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_11_up = {{{1, 1, 1}, {0, 0, 0}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_11_down = {{{0, 0, 0}, {0, 0, 0}, {1, 1, 1}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_11_complement = {{{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}}; 

const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_bottom = {{{0, 0, 0}, {0, 1, 0}, {1, 1, 1}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_bottom_complement = {{{1, 1, 1}, {0, 0, 0}, {0, 0, 0}}};

const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_top = {{{1, 1, 1}, {0, 1, 0}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_top_complement = {{{0, 0, 0}, {0, 0, 0}, {1, 1, 1}}};

const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_left = {{{1, 0, 0}, {1, 1, 0}, {1, 0, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_left_complement = {{{0, 0, 1}, {0, 0, 1}, {0, 0, 1}}};

const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_right = {{{0, 0, 1}, {0, 1, 1}, {0, 0, 1}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_right_complement = {{{1, 0, 0}, {1, 0, 0}, {1, 0, 0}}};

const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_bottom_left = {{{0, 0, 0}, {1, 1, 0}, {1, 1, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_bottom_left_complement = {{{0, 1, 1}, {0, 0, 1}, {0, 0, 0}}};

const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_bottom_right = {{{0, 0, 0}, {0, 1, 1}, {0, 1, 1}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_bottom_right_complement = {{{1, 1, 0}, {1, 0, 0}, {0, 0, 0}}};

const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_top_left = {{{1, 1, 0}, {1, 1, 0}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_top_left_complement = {{{0, 0, 0}, {0, 0, 1}, {0, 1, 1}}};

const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_top_right = {{{0, 1, 1}, {0, 1, 1}, {0, 0, 0}}};
const std::array<std::array<bool, 3>, 3> BinaryOp::kernel_12_top_right_complement = {{{0, 0, 0}, {1, 0, 0}, {1, 1, 0}}};