#include "CImg.h"
#include "Elementary.h"
#include "Geometry.h"
#include "Noise.h"
#include "Measuring.h"
#include "Characteristics.h"
#include "LinearSpatial.h"
#include "NonLinearSpatial.h"
#include "Histogram.h"
#include "BinaryOp.h"
#include <chrono>

#include <iostream>
#include <string>
using namespace cimg_library;

int main(int argc, char* argv[]) {
        if (argc < 2) {
                std::cerr << "Usage: " << "--input <image.bmp> " << "--output <image.bmp>" 
                <<"--command " << "[-argument=value [...]]" << "\n";
                return 0;
        }

        CImg<unsigned char> originalImage;
        CImg<unsigned char> modifiedImage;
        char* output_name;

        // pargv is a pointer to the current argument
        for (char** pargv = argv + 1; *pargv != argv[argc]; pargv++) {
                if (std::string(*pargv).find("--file") != std::string::npos) {
                        try {
                                std::cout << "Writing results to: " << *(pargv + 1) << "\n";
                                freopen(*(pargv + 1), "a", stdout);
                                std::cout << "\n";
                        } catch (const std::exception& e) {
                                std::cerr << "Error: " << e.what() << "\n";
                                return 0;
                        }
                }
        }

        for (char** pargv = argv + 1; *pargv != argv[argc]; pargv++) {
                if (std::string(*pargv).find("--input") != std::string::npos) {
                        try {
                                std::cout << "Loading image: " << *(pargv + 1) << "\n";
                                originalImage.load_bmp(*(pargv + 1));
                                modifiedImage.assign(originalImage);
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                }
        }

        for (char** pargv = argv + 1; *pargv != argv[argc]; pargv++) {
                if (std::string(*pargv).find("--output") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--output " << "<output_name.bmp>" << "\n";
                                return 0;
                        }
                        
                        std::cout << "Output image: " << *(pargv + 1) << "\n";
                        output_name = *(pargv + 1);
                }
        }

        for (char** pargv = argv + 1; *pargv != argv[argc]; pargv++) {
                
                if (std::string(*pargv).find("--input") != std::string::npos) {
                        pargv++;
                        continue;
                }

                if (std::string(*pargv).find("--output") != std::string::npos) {
                        pargv++;
                        continue;
                }

                if (std::string(*pargv).find("--file") != std::string::npos) {
                        pargv++;
                        continue;
                }

                if (std::string(*pargv).find("--brightness") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--brightness " << "[-value=50]" << "\n";
                                return 0;
                        }

                        try {
                                int brightness = std::stoi(*(pargv + 1));
                                modifiedImage = Elementary::brightnessMod(modifiedImage, brightness);
                                pargv++; 
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--contrast") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--contrast " << "[-value=1.5]" << "\n";
                                return 0;
                        }

                        try {
                                float contrast = std::stof(*(pargv + 1));
                                modifiedImage = Elementary::contrastMod(modifiedImage, contrast);
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--negative") != std::string::npos) {
                        try {
                                modifiedImage = Elementary::negative(modifiedImage);
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Error while modifying image" << "\n";
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--hflip") != std::string::npos) {
                        try {
                                modifiedImage = Geometry::horizontalFlip(modifiedImage);
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Error while modifying image" << "\n";
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--vflip") != std::string::npos) {
                        try {
                                modifiedImage = Geometry::verticalFlip(modifiedImage);
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Error while modifying image" << "\n";
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--dflip") != std::string::npos) {
                        try {
                                modifiedImage = Geometry::diagonalFlip(modifiedImage);
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Error while modifying image" << "\n";
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--shrink") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--shrink " << "[-factor=2]" << "\n";
                                return 0;
                        }

                        try {
                                int factor = std::stoi(*(pargv + 1));
                                modifiedImage = Geometry::imageShrinking(modifiedImage, factor);
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--enlarge") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--enlarge " << "[-factor=2]" << "\n";
                                return 0;
                        }

                        try {
                                int factor = std::stoi(*(pargv + 1));
                                modifiedImage = Geometry::imageEnlargement(modifiedImage, factor);
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;
                } 

                if (std::string(*pargv).find("--max") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--max " << "[-size=3] " << "\n";
                                return 0;
                        }

                        try {
                                int windowSize = std::stoi(*(pargv + 1));
                                modifiedImage = Noise::maxFilter(modifiedImage, windowSize);
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;     
                } 
                
                if (std::string(*pargv).find("--min") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--min " << "[-size=3] " << "\n";
                                return 0;
                        }

                        try {
                                int windowSize = std::stoi(*(pargv + 1));
                                modifiedImage = Noise::minFilter(modifiedImage, windowSize);
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;
                } 

                if (std::string(*pargv).find("--adaptive") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc] || *(pargv + 2) == argv[argc]) {
                                std::cerr << "Usage: " << "--adaptive " << "[-size=3]" << "[-maxSize=7]" << "\n";
                                return 0;
                        }

                        try {
                                int windowSize = std::stoi(*(pargv + 1));
                                int maxSize = std::stoi(*(pargv + 2));
                                modifiedImage = Noise::adaptiveMedianFilter(modifiedImage, windowSize, maxSize);
                                pargv += 2;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << " or " << *(pargv + 2) << "\n";
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--snr") != std::string::npos) {
                        try {
                                modifiedImage.load_bmp(output_name);
                                float snr = Measuring::signalToNoiseRatio(originalImage, modifiedImage);
                                std::cout << "Signal to Noise Ratio: " << snr << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--mse") != std::string::npos) {
                        try {
                                modifiedImage.load_bmp(output_name);
                                float mse = Measuring::meanSquareError(originalImage, modifiedImage);
                                std::cout << "Mean Square Error: " << mse << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--pmse") != std::string::npos) {
                        try {
                                modifiedImage.load_bmp(output_name);
                                float pmse = Measuring::peakMeanSquareError(originalImage, modifiedImage);
                                std::cout << "Peak Mean Square Error: " << pmse << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--psnr") != std::string::npos) {
                        try {
                                modifiedImage.load_bmp(output_name);
                                float psnr = Measuring::peakSignalToNoiseRatio(originalImage, modifiedImage);
                                std::cout << "Peak Signal to Noise Ratio: " << psnr << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--md") != std::string::npos) {
                        try {
                                modifiedImage.load_bmp(output_name);
                                float maxDiff = Measuring::maximumDifference(originalImage, modifiedImage);
                                std::cout << "Maximum Difference: " << maxDiff << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--histogram") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc] || *(pargv + 2) == argv[argc]) {
                                std::cerr << "Usage: " << "--histogram " << "[-channel=2] " << "[-histogram_output = *.bmp]" << "\n";
                                return 0;
                        }
                        try {
                                int channel = std::stoi(*(pargv + 1));
                                char* histogram_output = *(pargv + 2);
                                CImg<unsigned char> histogramImage = Histogram::returnHistogramImage(modifiedImage, channel);
                                histogramImage.save_bmp(histogram_output);
                                pargv += 2;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--hexponent") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc] || *(pargv + 2) == argv[argc] || *(pargv + 3) == argv[argc]) {
                                std::cerr << "Usage: " << "--hexponent " << "[-min_brightness=30] " 
                                                << "[-max_brightness=250]" << "[-alpha=3.5]" << "\n";
                                return 0;
                        }
                        try {
                                int minBrightness = std::stoi(*(pargv + 1));
                                int maxBrightness = std::stoi(*(pargv + 2));
                                float alpha = std::stof(*(pargv + 3));

                                modifiedImage = Histogram::exponentialFPDF(originalImage, minBrightness, maxBrightness, alpha);
                                pargv += 3;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--cmean") != std::string::npos) {
                        try {
                                float mean = Characteristics::mean(originalImage);
                                std::cout << "Mean: " << mean << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--cvariance") != std::string::npos) {
                        try {
                                float variance = Characteristics::variance(originalImage);
                                std::cout << "Variance: " << variance << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--cstdev") != std::string::npos) {
                        try {
                                float stdDev = Characteristics::standardDeviation(originalImage);
                                std::cout << "Standard Deviation: " << stdDev << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--cvarcoi") != std::string::npos && std::string(*pargv).find("--cvarcoii") == std::string::npos) {
                        try {
                                float vcoeff1 = Characteristics::variationCoefficient_1(originalImage);
                                std::cout << "Variation Coefficient 1: " << vcoeff1 << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--cvarcoii") != std::string::npos) {
                        try {
                                float vcoeff2 = Characteristics::variationCoefficient_2(originalImage);
                                std::cout << "Variation Coefficient 2: " << vcoeff2 << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--casyco") != std::string::npos) {
                        try {
                                float assym = Characteristics::assymetryCoefficient(originalImage);
                                std::cout << "Asymmetry Coefficient: " << assym << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--cflatco") != std::string::npos) {
                        try {
                                float flat = Characteristics::flatteningCoefficient(originalImage);
                                std::cout << "Flattening Coefficient: " << flat << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--centropy") != std::string::npos) {
                        try {
                                float entropy = Characteristics::entropy(originalImage);
                                std::cout << "Entropy: " << entropy << "\n";
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--orosenfeld") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--rosenfeld " << "[-power=2]" << "\n";
                                return 0;
                        }

                        try {
                                unsigned int power = std::stoi(*(pargv + 1));
                                modifiedImage = NonLinearSpatial::rosenfeldOperator(modifiedImage, power);
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--sexdeti") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--sexdeti " << "[-mask=NE]" << "\n";
                                return 0;
                        }

                        try {
                                char* mask = *(pargv + 1);
                                std::cout << mask << "\n";
                                
                                LinearSpatial linearSpatial;

                                auto start = std::chrono::high_resolution_clock::now();
                                modifiedImage = linearSpatial.extractionOfDetails(modifiedImage, mask);
                                auto end = std::chrono::high_resolution_clock::now();
                                std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << "\n";

                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--erosion") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--erosion " << "[-structural_element=4]" << "\n";
                        }

                        try {
                                int kernel = std::stoi(*(pargv + 1));
                                modifiedImage = BinaryOp::task3Operations(modifiedImage, kernel, "", "erosion");
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--dilation") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--dilation " << "[-structural_element=4]" << "\n";
                        }

                        try {
                                int kernel = std::stoi(*(pargv + 1));
                                modifiedImage = BinaryOp::task3Operations(modifiedImage, kernel, "", "dilation");
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--opening") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--opening " << "[-structural_element=4]" << "\n";
                        }

                        try {
                                int kernel = std::stoi(*(pargv + 1));
                                modifiedImage = BinaryOp::task3Operations(modifiedImage, kernel, "", "opening");
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--closing") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--closing " << "[-structural_element=4]" << "\n";
                        }

                        try {
                                int kernel = std::stoi(*(pargv + 1));
                                modifiedImage = BinaryOp::task3Operations(modifiedImage, kernel, "", "closing");
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--HMT") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc] || *(pargv + 2) == argv[argc]) {
                                std::cerr << "Usage: " << "--HMT " << "[-structural_element=11]" << "[-structural_element_complement=bottom-left]" << "\n";
                        }

                        try {
                                int kernelA = std::stoi(*(pargv + 1));
                                std::string kernelB = std::string(*(pargv + 2));
                                
                                modifiedImage = BinaryOp::task3Operations(modifiedImage, kernelA, kernelB, "HMT");
                                pargv += 2;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << " or " << *(pargv + 2) << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--M7") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--M7 " << "[-structural_element=4]" << "\n";
                        }

                        try {
                                int kernel = std::stoi(*(pargv + 1));
                                modifiedImage = BinaryOp::task3Operations(modifiedImage, kernel, "", "M7");
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--regionGrowing") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc] || *(pargv + 2) == argv[argc]) {
                                std::cerr << "Usage: " << "--regionGrowing " << "[-x=0]" << "[-y=0]" << "[-threshold=30]" << "[-criterion=2]" << "\n";
                        }

                        try {
                                int x = std::stoi(*(pargv + 1));
                                int y = std::stoi(*(pargv + 2));
                                int threshold = std::stoi(*(pargv + 3));
                                int criterion = std::stoi(*(pargv + 4));
                                modifiedImage = BinaryOp::regionGrowing(modifiedImage, x, y, threshold, criterion);
                                pargv += 3;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << e.what() << "\n";
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--help") != std::string::npos) {
                        std::cout << "Available commands:\n"
                                << "--input <image.bmp>\n"
                                << "--output <output_name.bmp>\n"
                                << "--brightness [-value=50]\n"
                                << "--contrast [-value=1.5]\n"
                                << "--negative\n"
                                << "--hflip\n"
                                << "--vflip\n"
                                << "--dflip\n"
                                << "--shrink [-factor=2]\n"
                                << "--enlarge [-factor=2]\n"
                                << "--max [-size=3]\n"
                                << "--min [-size=3]\n"
                                << "--adaptive [-size=3] [-maxSize=7]\n"
                                << "--snr\n"
                                << "--mse\n"
                                << "--pmse\n"
                                << "--psnr\n"
                                << "--maxdiff\n"
                                << "--histogram [-channel=2] [-histogram_output=*.bmp]\n"
                                << "--hexponent [-min_brightness=30] [-max_brightness=250] [-alpha=3.5]\n"
                                << "--cmean\n"
                                << "--cvariance\n"
                                << "--cstdev\n"
                                << "--cvarcoi\n"
                                << "--cvarcoii\n"
                                << "--casyco\n"
                                << "--cflatco\n"
                                << "--centropy\n"
                                << "--orosenfeld [-power=2]\n"
                                << "--sexdeti [-mask=NE]\n"
                                << "--erosion [-structural_element=4]\n"
                                << "--dilation [-structural_element=4]\n"
                                << "--opening [-structural_element=4]\n"
                                << "--closing [-structural_element=4]\n"
                                << "--HMT [-structural_element_A=4] [-structural_element_complement=bottom-left]\n"
                                << "--M7 [-structural_element=4]\n"
                                << "--regionGrowing [-x=0] [-y=0] [-threshold=30]\n"
                                << "--help\n";
                        return 0;
                }
        }
        
        modifiedImage.save_bmp(output_name);
}