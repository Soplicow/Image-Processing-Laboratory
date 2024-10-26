#include "CImg.h"
#include "Elementary.h"
#include "Geometry.h"
#include "Noise.h"
#include "Measuring.h"
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

        std::string command;

        // pargv is a pointer to the current argument
        for (char** pargv = argv + 1; *pargv != argv[argc]; pargv++) {
                if (std::string(*pargv).find("--file") != std::string::npos) {
                        try {
                                std::cout << "Writing results to: " << *(pargv + 1) << std::endl;
                                freopen(*(pargv + 1), "a", stdout);
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
                } 
                
                if (std::string(*pargv).find("--negative") != std::string::npos) {
                        try {
                                modifiedImage = Elementary::negative(modifiedImage);
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Error while modifying image" << std::endl;
                                return 0;
                        }
                } 
                
                if (std::string(*pargv).find("--hflip") != std::string::npos) {
                        try {
                                modifiedImage = Geometry::horizontalFlip(modifiedImage);
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Error while modifying image" << std::endl;
                                return 0;
                        }
                } 
                
                if (std::string(*pargv).find("--vflip") != std::string::npos) {
                        try {
                                modifiedImage = Geometry::verticalFlip(modifiedImage);
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Error while modifying image" << std::endl;
                                return 0;
                        }
                } 
                
                if (std::string(*pargv).find("--dflip") != std::string::npos) {
                        try {
                                modifiedImage = Geometry::diagonalFlip(modifiedImage);
                        } catch (std::invalid_argument& e) {
                                std::cerr << "Error while modifying image" << std::endl;
                                return 0;
                        }
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
                }

                if (std::string(*pargv).find("--help") != std::string::npos) {
                        try {
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
                                        << "--maxdiff\n";
                                return 0;
                        } catch (const std::exception& e) {
                                std::cerr << "Error displaying help: " << e.what() << std::endl;
                                return 0;
                        }
                }
        }
        
        modifiedImage.save_bmp(output_name);
}