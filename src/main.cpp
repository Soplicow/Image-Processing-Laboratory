#include "../include/CImg.h" // modify the path if necessary
#include "../include/elementary.h"
#include "../include/geometry.h"
#include "../include/noise.h"
#include "../include/measuring.h"
#include <iostream>
#include <string>
using namespace cimg_library;

int main(int argc, char* argv[]) {
        if (argc < 2) {
                std::cerr << "Usage: " << "<image.bmp> " << "--command " << "[-argument=value [...]]" << std::endl;
                return 0;
        }

        CImg<unsigned char> originalImage;
        CImg<unsigned char> modifiedImage;

        try {
                originalImage.load_bmp(argv[1]);
                modifiedImage.assign(originalImage);
        } catch (const CImgIOException& e) {
                std::cerr << "Error loading image: " << e.what() << std::endl;
                return 0;
        }

        std::string command = argv[2];
        if (command == "--brightness") {
                if (argc < 4) {
                        std::cerr << "Usage: " << "--brightness " << "[-value=50]" << std::endl;
                        return 0;
                }

                try {
                        int brightness = std::stoi(argv[3]);
                        modifiedImage = Elementary::brightnessMod(modifiedImage, brightness);
                        modifiedImage.save_bmp("output.bmp");
                } catch (std::invalid_argument& e) {
                        std::cerr << "Invalid argument: " << argv[2] << std::endl;
                        return 0;
                }

        } else if (command == "--contrast") {
                if (argc < 4) {
                        std::cerr << "Usage: " << "--contrast " << "[-value=1.5]" << std::endl;
                        return 0;
                }

                try {
                        float contrast = std::stof(argv[3]);
                        modifiedImage = Elementary::contrastMod(modifiedImage, contrast);
                } catch (std::invalid_argument& e) {
                        std::cerr << "Invalid argument: " << argv[2] << std::endl;
                        return 0;
                }
        } else if (command == "--negative") {
                try {
                        modifiedImage = Elementary::negative(modifiedImage);
                } catch (std::invalid_argument& e) {
                        std::cerr << "error" << std::endl;
                        return 0;
                }
        } else if (command == "--hflip") {
                try {
                        modifiedImage = Geometry::horizontalFlip(modifiedImage);
                } catch (std::invalid_argument& e) {
                        std::cerr << "error" << std::endl;
                        return 0;
                }
        } else if (command == "-vflip") {
                try {
                        modifiedImage = Geometry::verticalFlip(modifiedImage);
                } catch (std::invalid_argument& e) {
                        std::cerr << "error" << std::endl;
                        return 0;
                }
        } else if (command == "--dflip") {
                try {
                        modifiedImage = Geometry::diagonalFlip(modifiedImage);
                } catch (std::invalid_argument& e) {
                        std::cerr << "error" << std::endl;
                        return 0;
                }
        } else if (command == "--shrink") {
                if (argc < 4) {
                        std::cerr << "Usage: " << "--shrink " << "[-factor=2]" << std::endl;
                        return 0;
                }

                try {
                        int factor = std::stoi(argv[3]);
                        modifiedImage = Geometry::imageShrinking(modifiedImage, factor);
                } catch (std::invalid_argument& e) {
                        std::cerr << "Invalid argument: " << argv[2] << std::endl;
                        return 0;
                }
        } else if (command == "--enlarge") {
                if (argc < 4) {
                        std::cerr << "Usage: " << "--enlarge " << "[-factor=2]" << std::endl;
                        return 0;
                }

                try {
                        int factor = std::stoi(argv[3]);
                        modifiedImage = Geometry::imageEnlargement(modifiedImage, factor);
                } catch (std::invalid_argument& e) {
                        std::cerr << "Invalid argument: " << argv[2] << std::endl;
                        return 0;
                }
        } else if (command == "--median") {
                if (argc < 5) {
                        std::cerr << "Usage: " << "--median " << "[-horizontal=3] " << "[-vertical=3]" << std::endl;
                        return 0;
                }

                try {
                        int windowHorizontal = std::stoi(argv[3]);
                        int windowVertical = std::stoi(argv[4]);
                        modifiedImage = Noise::medianFilter(modifiedImage, windowHorizontal, windowVertical);
                } catch (std::invalid_argument& e) {
                        std::cerr << "Invalid argument: " << argv[3] << " or " << argv[4] << std::endl;
                }
        } else if (command == "--harmonic") {
                if (argc < 5) {
                        std::cerr << "Usage: " << "--harmonic " << "[-horizontal=3] " << "[-vertical=3]" << std::endl;
                        return 0;
                }

                try {
                        int windowHorizontal = std::stoi(argv[3]);
                        int windowVertical = std::stoi(argv[4]);
                        modifiedImage = Noise::harmonicMeanFilter(modifiedImage, windowHorizontal, windowVertical);
                } catch (std::invalid_argument& e) {
                        std::cerr << "Invalid argument: " << argv[2] << " or " << argv[3] << std::endl;
                }
        } else if (command == "--snr") {
                if (argc < 4) {
                        std::cerr << "Usage: " << "--snr " << "<image.bmp>" << std::endl;
                        return 0;
                }

                CImg<unsigned char> modifiedImage(argv[3]);
                float snr = Measuring::signalToNoiseRatio(originalImage, modifiedImage);
                std::cout << "Signal to Noise Ratio: " << snr << std::endl;
        } else {
                std::cerr << "Invalid command: " << command << std::endl;
                return 0;
        }
}