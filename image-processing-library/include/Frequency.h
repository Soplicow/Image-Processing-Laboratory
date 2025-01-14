#ifndef FREQUENCY_H
#define FREQUENCY_H

#define Complex std::complex<double>
#define CVector std::vector<Complex>
#define CVector2D std::vector<std::vector<Complex>>

#include <vector>
#include <complex>
#include "CImg.h"

using namespace cimg_library;

// Note from creator:
// Those functions will work for RGB images, but will only use the red channels
// Because I'm lazy

class Frequency {
public:
    Frequency();

    ~Frequency();

    // Convert CImg to a 2D vector of complex numbers
    static CVector2D CImgToCVector2D(const CImg<unsigned char>& image, int channel);
    static CVector2D CImgToCVector2D(const CImg<double>& image, int channel);

    // Convert real part of complex numbers to CImg
    static CImg<unsigned char> CVector2DToCImg(const CVector2D& input);
    static CImg<double> CVector2DToTiff(const CVector2D& input);

    // Discrete Fourier Transform using 2D array of complex numbers
    static void DFT_2D(CVector2D& input, bool inverse);

    // Fast Fourier Transform using 2D array of complex numbers
    static void FFT_2D(CVector2D& input, bool inverse);


    // 1D Discrete Fourier Transform
    static void DFT_1D(CVector& input, bool inverse);

    // 1D Fast Fourier Transform
    static void FFT_1D(CVector& input, bool inverse);

    // Convert 2D array of complex numbers to an image of fourier spectrum
    static CImg<double> computeSpectrum(CVector2D& input);

    static CImg<unsigned char> calculateMagnitudeSpectrum(CVector2D& input);

    // Reconstruct the image from 2D array of complex numbers
    static CVector2D reVecotrizeSpectrum(const CImg<double>& input, int channel);

    // Convert an image into its Fourier spectrum (real and imaginary parts) using FFT
    static CImg<double> FFT(const CImg<unsigned char>& image);

    // Convert an image into its spatial domain from Fourier spectrum using FFT
    static CImg<unsigned char> IFFT(const CImg<double>& image);

    // Convert an image into its Fourier spectrum (real and imaginary parts) using DFT
    static CImg<double> DFT(const CImg<unsigned char>& image);

    // Convert an image into its spatial domain from Fourier spectrum using DFT
    static CImg<unsigned char> IDFT(const CImg<unsigned char>& image);

    // Complete Functions (use in main)

    static CImg<unsigned char> MagnitudeSpectrum(const CImg<unsigned char>& image);

    static CImg<unsigned char> LowPass(const CImg<unsigned char>& image, int radius);

    static CImg<unsigned char> HighPass(const CImg<unsigned char>& image, int radius);

    static CImg<unsigned char> BandPass(const CImg<unsigned char>& image, int radius1, int radius2);

    static CImg<unsigned char> BandCut(const CImg<unsigned char>& image, int radius1, int radius2);

    static CImg<unsigned char> HighPassEdgeDetection(const CImg<unsigned char>& image, const CImg<unsigned char>& mask, int radius, int edgeDirection);

    static CImg<unsigned char> PhaseMod(const CImg<unsigned char>& image1, int k, int l);
private:

};

#endif // FREQUENCY_H