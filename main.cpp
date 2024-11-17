#include "CImg.h"
#include "Elementary.h"
#include "Geometry.h"
#include "Noise.h"
#include "Measuring.h"
#include "Characteristics.h"
#include "LinearSpatial.h"
#include "NonLinearSpatial.h"
#include "Histogram.h"
#include <chrono>

#include <iostream>
#include <string>
using namespace cimg_library;

int main(int argc, char* argv[]) {
        if (argc < 2) {
                std::cerr << "Usage: " << "--input <image.bmp> " << "--output <image.bmp>" 
                <<"--command " << "[-argument=value [...]]" << std::endl;
                return 0;
        }

        CImg<unsigned char> originalImage;
        CImg<unsigned char> modifiedImage;
        char* output_name;

        // pargv is a pointer to the current argument
        for (char** pargv = argv + 1; *pargv != argv[argc]; pargv++) {
                if (std::string(*pargv).find("--file") != std::string::npos) {
                        try {
                                std::cout << "Writing results to: " << *(pargv + 1) << std::endl;
                                freopen(*(pargv + 1), "a", stdout);
                                std::cout << "\n";
                        } catch (const std::exception& e) {
                                std::cerr << "Error: " << e.what() << std::endl;
                                return 0;
                        }
                }
        }

        for (char** pargv = argv + 1; *pargv != argv[argc]; pargv++) {
                if (std::string(*pargv).find("--input") != std::string::npos) {
                        try {
                                std::cout << "Loading image: " << *(pargv + 1) << std::endl;
                                originalImage.load_bmp(*(pargv + 1));
                                modifiedImage.assign(originalImage);
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                }
        }

        for (char** pargv = argv + 1; *pargv != argv[argc]; pargv++) {
                if (std::string(*pargv).find("--output") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--output " << "<output_name.bmp>" << std::endl;
                                return 0;
                        }
                        
                        std::cout << "Output image: " << *(pargv + 1) << std::endl;
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
                                std::cerr << "Usage: " << "--brightness " << "[-value=50]" << std::endl;
                                return 0;
                        }

                        try {
                                int brightness = std::stoi(*(pargv + 1));
                                modifiedImage = Elementary::brightnessMod(modifiedImage, brightness);
                                pargv++; 
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << std::endl;
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--contrast") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--contrast " << "[-value=1.5]" << std::endl;
                                return 0;
                        }

                        try {
                                float contrast = std::stof(*(pargv + 1));
                                modifiedImage = Elementary::contrastMod(modifiedImage, contrast);
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << std::endl;
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--negative") != std::string::npos) {
                        try {
                                modifiedImage = Elementary::negative(modifiedImage);
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Error while modifying image" << std::endl;
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--hflip") != std::string::npos) {
                        try {
                                modifiedImage = Geometry::horizontalFlip(modifiedImage);
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Error while modifying image" << std::endl;
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--vflip") != std::string::npos) {
                        try {
                                modifiedImage = Geometry::verticalFlip(modifiedImage);
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Error while modifying image" << std::endl;
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--dflip") != std::string::npos) {
                        try {
                                modifiedImage = Geometry::diagonalFlip(modifiedImage);
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Error while modifying image" << std::endl;
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--shrink") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--shrink " << "[-factor=2]" << std::endl;
                                return 0;
                        }

                        try {
                                int factor = std::stoi(*(pargv + 1));
                                modifiedImage = Geometry::imageShrinking(modifiedImage, factor);
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << std::endl;
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--enlarge") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--enlarge " << "[-factor=2]" << std::endl;
                                return 0;
                        }

                        try {
                                int factor = std::stoi(*(pargv + 1));
                                modifiedImage = Geometry::imageEnlargement(modifiedImage, factor);
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << std::endl;
                                return 0;
                        }
                        continue;
                } 

                if (std::string(*pargv).find("--max") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--max " << "[-size=3] " << std::endl;
                                return 0;
                        }

                        try {
                                int windowSize = std::stoi(*(pargv + 1));
                                modifiedImage = Noise::maxFilter(modifiedImage, windowSize);
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << std::endl;
                                return 0;
                        }
                        continue;     
                } 
                
                if (std::string(*pargv).find("--min") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--min " << "[-size=3] " << std::endl;
                                return 0;
                        }

                        try {
                                int windowSize = std::stoi(*(pargv + 1));
                                modifiedImage = Noise::minFilter(modifiedImage, windowSize);
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << std::endl;
                                return 0;
                        }
                        continue;
                } 

                if (std::string(*pargv).find("--adaptive") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc] || *(pargv + 2) == argv[argc]) {
                                std::cerr << "Usage: " << "--adaptive " << "[-size=3]" << "[-maxSize=7]" << std::endl;
                                return 0;
                        }

                        try {
                                int windowSize = std::stoi(*(pargv + 1));
                                int maxSize = std::stoi(*(pargv + 2));
                                modifiedImage = Noise::adaptiveMedianFilter(modifiedImage, windowSize, maxSize);
                                pargv += 2;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << " or " << *(pargv + 2) << std::endl;
                                return 0;
                        }
                        continue;
                } 
                
                if (std::string(*pargv).find("--snr") != std::string::npos) {
                        try {
                                modifiedImage.load_bmp(output_name);
                                float snr = Measuring::signalToNoiseRatio(originalImage, modifiedImage);
                                std::cout << "Signal to Noise Ratio: " << snr << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--mse") != std::string::npos) {
                        try {
                                modifiedImage.load_bmp(output_name);
                                float mse = Measuring::meanSquareError(originalImage, modifiedImage);
                                std::cout << "Mean Square Error: " << mse << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--pmse") != std::string::npos) {
                        try {
                                modifiedImage.load_bmp(output_name);
                                float pmse = Measuring::peakMeanSquareError(originalImage, modifiedImage);
                                std::cout << "Peak Mean Square Error: " << pmse << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--psnr") != std::string::npos) {
                        try {
                                modifiedImage.load_bmp(output_name);
                                float psnr = Measuring::peakSignalToNoiseRatio(originalImage, modifiedImage);
                                std::cout << "Peak Signal to Noise Ratio: " << psnr << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--md") != std::string::npos) {
                        try {
                                modifiedImage.load_bmp(output_name);
                                float maxDiff = Measuring::maximumDifference(originalImage, modifiedImage);
                                std::cout << "Maximum Difference: " << maxDiff << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--histogram") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc] || *(pargv + 2) == argv[argc]) {
                                std::cerr << "Usage: " << "--histogram " << "[-channel=2] " << "[-histogram_output = *.bmp]" << std::endl;
                                return 0;
                        }
                        try {
                                int channel = std::stoi(*(pargv + 1));
                                char* histogram_output = *(pargv + 2);
                                CImg<unsigned char> histogramImage = Histogram::returnHistogramImage(modifiedImage, channel);
                                histogramImage.save_bmp(histogram_output);
                                pargv += 2;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--hexponent") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc] || *(pargv + 2) == argv[argc] || *(pargv + 3) == argv[argc]) {
                                std::cerr << "Usage: " << "--hexponent " << "[-min_brightness=30] " 
                                                << "[-max_brightness=250]" << "[-alpha=3.5]" << std::endl;
                                return 0;
                        }
                        try {
                                int minBrightness = std::stoi(*(pargv + 1));
                                int maxBrightness = std::stoi(*(pargv + 2));
                                float alpha = std::stof(*(pargv + 3));

                                modifiedImage = Histogram::exponentialFPDF(originalImage, minBrightness, maxBrightness, alpha);
                                pargv += 3;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--cmean") != std::string::npos) {
                        try {
                                float mean = Characteristics::mean(originalImage);
                                std::cout << "Mean: " << mean << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--cvariance") != std::string::npos) {
                        try {
                                float variance = Characteristics::variance(originalImage);
                                std::cout << "Variance: " << variance << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--cstdev") != std::string::npos) {
                        try {
                                float stdDev = Characteristics::standardDeviation(originalImage);
                                std::cout << "Standard Deviation: " << stdDev << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--cvarcoi") != std::string::npos && std::string(*pargv).find("--cvarcoii") == std::string::npos) {
                        try {
                                float vcoeff1 = Characteristics::variationCoefficient_1(originalImage);
                                std::cout << "Variation Coefficient 1: " << vcoeff1 << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--cvarcoii") != std::string::npos) {
                        try {
                                float vcoeff2 = Characteristics::variationCoefficient_2(originalImage);
                                std::cout << "Variation Coefficient 2: " << vcoeff2 << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--casyco") != std::string::npos) {
                        try {
                                float assym = Characteristics::assymetryCoefficient(originalImage);
                                std::cout << "Asymmetry Coefficient: " << assym << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--cflatco") != std::string::npos) {
                        try {
                                float flat = Characteristics::flatteningCoefficient(originalImage);
                                std::cout << "Flattening Coefficient: " << flat << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--centropy") != std::string::npos) {
                        try {
                                float entropy = Characteristics::entropy(originalImage);
                                std::cout << "Entropy: " << entropy << std::endl;
                        } catch (const CImgIOException& e) {
                                std::cerr << "Error loading image: " << e.what() << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--orosenfeld") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--rosenfeld " << "[-power=2]" << std::endl;
                                return 0;
                        }

                        try {
                                unsigned int power = std::stoi(*(pargv + 1));
                                modifiedImage = NonLinearSpatial::rosenfeldOperator(modifiedImage, power);
                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << std::endl;
                                return 0;
                        }
                        continue;
                }

                if (std::string(*pargv).find("--sexdeti") != std::string::npos) {
                        if (*(pargv + 1) == argv[argc]) {
                                std::cerr << "Usage: " << "--sexdeti " << "[-mask=NE]" << std::endl;
                                return 0;
                        }

                        try {
                                char* mask = *(pargv + 1);
                                std::cout << mask << std::endl;
                                
                                LinearSpatial linearSpatial;

                                auto start = std::chrono::high_resolution_clock::now();
                                modifiedImage = linearSpatial.extractionOfDetails(modifiedImage, mask);
                                auto end = std::chrono::high_resolution_clock::now();
                                std::cout << "Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

                                pargv++;
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Invalid argument: " << *(pargv + 1) << std::endl;
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
                                << "--help\n";
                        return 0;
                }
        }
        
        modifiedImage.save_bmp(output_name);
}