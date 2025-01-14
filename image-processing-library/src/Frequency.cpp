#define cimg_use_tiff
#include <CImg.h>
#include "Frequency.h"
#include <GlobalHelper.h>

using namespace cimg_library;

Frequency::Frequency() {}

Frequency::~Frequency() {}

CVector2D Frequency::CImgToCVector2D(const CImg<unsigned char>& image, int channel) {
    int width = image.width();
    int height = image.height();
    CVector2D result(height, std::vector<Complex>(width));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            result[y][x] = Complex(image(x, y, channel), 0);
        }
    }
    return result;
}

CVector2D Frequency::CImgToCVector2D(const CImg<double>& image, int channel) {
    int width = image.width();
    int height = image.height();
    CVector2D result(height, std::vector<Complex>(width));
    cimg_forXYC(image, x, y, c) {
        result[y][x] = Complex(image(x, y, 0, c), image(x, y, 1, c));
    }
    return result;
}

CImg<unsigned char> Frequency::CVector2DToCImg(const CVector2D& input) {
    int height = input.size();
    int width = input[0].size();
    CImg<unsigned char> result(width, height, 1, 1, 0);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            result(x, y) = (unsigned char)std::abs(input[y][x].real());
        }
    }
    return result;
}

CImg<double> Frequency::CVector2DToTiff(const CVector2D& input) {
    int height = input.size();
    int width = input[0].size();
    CImg<double> result(width, height, 2, 1, 0);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            result(x, y, 0) = input[y][x].real();
            result(x, y, 1) = input[y][x].imag();
        }
    }
    return result;
}

/**
 * @brief Computes the Discrete Fourier Transform (DFT) or its inverse on the input vector.
 *
 * This function takes a vector of complex numbers and computes its DFT if `inverse` is false,
 * or the inverse DFT if `inverse` is true. The result is stored back in the input vector.
 *
 * @param input A reference to a vector of complex numbers (CVector) to be transformed.
 * @param inverse A boolean flag indicating whether to compute the inverse DFT (true) or the DFT (false).
 */
void Frequency::DFT_1D(CVector& input, bool inverse) {
    int N = input.size();
    double sign = inverse ? 1 : -1;

    CVector result(N);
    for (int k = 0; k < N; k++) {
        Complex sum(0, 0);
        for (int n = 0; n < N; n++) {
            double angle = 2 * M_PI * n * k / N;
            sum += input[n] * std::polar(1.0, sign * angle);
        }
        if (inverse) { // Normalize the result
            sum /= N;
        }
        result[k] = sum;
    }

    input = std::move(result);
}

void Frequency::FFT_1D(CVector& input, bool inverse) {
    const size_t N = input.size();
    if (N <= 1) {
        return;
    }

    // rBitValue value is the bit-reversed value of bitValue 
    size_t rBitValue = 0;
    for (size_t bitValue = 1; bitValue < N; bitValue++) {
        size_t bit = N >> 1;
        while (rBitValue & bit) {
            rBitValue ^= bit;
            bit >>= 1;
        }
        rBitValue ^= bit;

        if (bitValue < rBitValue) {
            std::swap(input[bitValue], input[rBitValue]);
        }
    }

    // Iteration FFT
    double sign = inverse ? 1 : -1;
    for (size_t len = 2; len <= N; len <<= 1) {
        double angle = sign * 2 * M_PI / len;
        Complex wlen(std::cos(angle), std::sin(angle));
        for (size_t i = 0; i < N; i += len) {
            Complex w(1);
            for (size_t j = 0; j < len / 2; j++) {
                Complex u = input[i + j]; // Real part
                Complex v = input[i + j + len / 2] * w; // Imaginary part
                input[i + j] = u + v; 
                input[i + j + len / 2] = u - v; 
                w *= wlen;
            }
        }
    }

    // Normalize the result
    if (inverse) {
        for (size_t i = 0; i < N; i++) {
            input[i] /= N;
        }
    }
}

CImg<unsigned char> Frequency::calculateMagnitudeSpectrum(CVector2D& input) {
    const size_t rows = input.size();
    const size_t cols = input[0].size();

    std::vector<std::vector<double>> magnitude(rows, std::vector<double>(cols));
    double maxMagnitude = 0;

    // Calculate magnitude and find maximum
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            magnitude[i][j] = log(1 + std::abs(input[i][j]));
            if (magnitude[i][j] > maxMagnitude) {
                maxMagnitude = magnitude[i][j];
            }
        }
    }

    CImg<unsigned char> result(cols, rows, 1, 1, 0);
    // Normalize and assign to result
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result(j, i) = static_cast<unsigned char>(255 * magnitude[i][j] / maxMagnitude);
        }
    }

    // Center the spectrum for better visualization
    result.shift(cols / 2, rows / 2, 0, 0, 2);

    return result;
}

CImg<double> Frequency::computeSpectrum(CVector2D& input) {
    const size_t rows = input.size();
    const size_t cols = input[0].size();

    std::vector<std::vector<double>> magnitude(rows, std::vector<double>(cols));
    double maxMagnitude = 0;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            magnitude[i][j] = log(1 + std::abs(input[i][j]));
        }
    }

    std::vector<std::vector<double>> phase(rows, std::vector<double>(cols));
    double maxPhase = 0;
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            phase[i][j] = std::arg(input[i][j]);
        }
    }

    CImg<double> spectrum(cols, rows, 2, 1, 0);

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            spectrum(j, i, 0) = magnitude[i][j];
            spectrum(j, i, 1) = phase[i][j];
        }
    }

    spectrum.shift(cols / 2, rows / 2, 0, 0, 2);

    return spectrum;
}

CVector2D Frequency::reVecotrizeSpectrum(const CImg<double>& input, int channel) {
    // get selected channel
    CImg<double> image = input.get_shared_channel(channel);

    image.shift(-input.width() / 2, -input.height() / 2, 0, 0, 2);

    int width = input.width();
    int height = input.height();
    CVector2D newVector(height, std::vector<Complex>(width));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // get magnitude and phase
            double magnitude = exp(image(x, y, 0)) - 1; // magnitude is log(1 + magnitude)
            double phase = image(x, y, 1); // phase is as it is
            // calculate real and imaginary parts
            newVector[y][x] = Complex(magnitude * cos(phase), magnitude * sin(phase));
        }
    }
    return newVector;
}

void Frequency::DFT_2D(CVector2D& input, bool inverse) {
    if (input.empty() || input[0].empty()) {
        return;
    }

    for (auto& row : input) {
        DFT_1D(row, inverse);
    }

    for (size_t i = 0; i < input[0].size(); i++) {
        CVector column(input.size());
        for (size_t j = 0; j < input.size(); j++) {
            column[j] = input[j][i];
        }
        DFT_1D(column, inverse);
        for (size_t j = 0; j < input.size(); j++) {
            input[j][i] = column[j];
        }
    }
}

void Frequency::FFT_2D(CVector2D& input, bool inverse) {
    if (input.empty() || input[0].empty()) {
        return;
    }

    for (size_t i = 0; i < input.size(); i++) {
        FFT_1D(input[i], inverse);
    }

    for (size_t i = 0; i < input[0].size(); i++) {
        CVector column(input.size());
        for (size_t j = 0; j < input.size(); j++) {
            column[j] = input[j][i];
        }
        FFT_1D(column, inverse);
        for (size_t j = 0; j < input.size(); j++) {
            input[j][i] = column[j];
        }
    }
}

CImg<unsigned char> Frequency::MagnitudeSpectrum(const CImg<unsigned char>& image) {
    CVector2D input = CImgToCVector2D(image, 0);
    FFT_2D(input, false);
    return calculateMagnitudeSpectrum(input);
}

CImg<double> Frequency::FFT(const CImg<unsigned char>& image) {
    CVector2D input = CImgToCVector2D(image, 0);
    FFT_2D(input, false);
    CImg<double> spectrum = computeSpectrum(input);
    return spectrum;
}

CImg<unsigned char> Frequency::IFFT(const CImg<double>& image) {
    CVector2D input = reVecotrizeSpectrum(image, 0);
    FFT_2D(input, true); // after this input is only real part
    CImg<unsigned char> result = CVector2DToCImg(input);
    return GlobalHelper::doubleToUnsignedChar(result);
}

CImg<double> Frequency::DFT(const CImg<unsigned char>& image) {
    CVector2D input = CImgToCVector2D(image, 0);
    DFT_2D(input, false);
    CImg<double> spectrum = computeSpectrum(input);
    return spectrum;
}

CImg<unsigned char> Frequency::IDFT(const CImg<unsigned char>& image) {
    CVector2D input = reVecotrizeSpectrum(image, 0);
    FFT_2D(input, true); // after this input is only real part
    CImg<unsigned char> result = CVector2DToCImg(input);
    return GlobalHelper::doubleToUnsignedChar(result);
}

CImg<unsigned char> Frequency::LowPass(const CImg<unsigned char>& image, int radius) {
    CImg<double> spectrum = FFT(image);
    int width = spectrum.width();
    int height = spectrum.height();
    int cx = width / 2;
    int cy = height / 2;

    cimg_forXY(spectrum, x, y) {
        if (std::hypot(x - cx, y - cy) > radius) {
            spectrum(x, y, 0) = 0;
            spectrum(x, y, 1) = 0;
        }
    }

    return IFFT(spectrum);
}

CImg<unsigned char> Frequency::HighPass(const CImg<unsigned char>& image, int radius) {
    CImg<double> spectrum = FFT(image);
    int width = spectrum.width();
    int height = spectrum.height();
    int cx = width / 2;
    int cy = height / 2;

    int DC_mag = spectrum(cx, cy, 0);
    int DC_phase = spectrum(cx, cy, 1);

    cimg_forXY(spectrum, x, y) {
        if (std::hypot(x - cx, y - cy) <= radius) {
            spectrum(x, y, 0) = 0;
            spectrum(x, y, 1) = 0;
        }
    }

    spectrum(cx, cy, 0) = DC_mag;
    spectrum(cx, cy, 1) = DC_phase;

    return IFFT(spectrum);
}

CImg<unsigned char> Frequency::BandPass(const CImg<unsigned char>& image, int low, int high) {
    CImg<double> spectrum = FFT(image);
    int width = spectrum.width();
    int height = spectrum.height();
    int cx = width / 2;
    int cy = height / 2;

    int DC_mag = spectrum(cx, cy, 0);
    int DC_phase = spectrum(cx, cy, 1);

    cimg_forXY(spectrum, x, y) {
        double distance = std::hypot(x - cx, y - cy);
        if (distance < low || distance > high) {
            spectrum(x, y, 0) = 0;
            spectrum(x, y, 1) = 0;
        }
    }

    spectrum(cx, cy, 0) = DC_mag;
    spectrum(cx, cy, 1) = DC_phase;

    return IFFT(spectrum);
}

CImg<unsigned char> Frequency::BandCut(const CImg<unsigned char>& image, int low, int high) {
    CImg<double> spectrum = FFT(image);
    int width = spectrum.width();
    int height = spectrum.height();
    int cx = width / 2;
    int cy = height / 2;

    int DC_mag = spectrum(cx, cy, 0);
    int DC_phase = spectrum(cx, cy, 1);

    cimg_forXY(spectrum, x, y) {
        double distance = std::hypot(x - cx, y - cy);
        if (distance >= low && distance <= high) {
            spectrum(x, y, 0) = 0;
            spectrum(x, y, 1) = 0;
        }
    }

    spectrum(cx, cy, 0) = DC_mag;
    spectrum(cx, cy, 1) = DC_phase;

    return IFFT(spectrum);
}

CImg<unsigned char> Frequency::HighPassEdgeDetection(const CImg<unsigned char>& image, const CImg<unsigned char>& mask, int radius, int edgeDirection) {
    CImg<double> spectrum = FFT(image);
    int width = spectrum.width();
    int height = spectrum.height();
    int cx = width / 2;
    int cy = height / 2;

    int DC_mag = spectrum(cx, cy, 0);
    int DC_phase = spectrum(cx, cy, 1);

    cimg_forXY(spectrum, x, y) {
        if (std::hypot(x - cx, y - cy) <= radius) {
            spectrum(x, y, 0) = 0;
            spectrum(x, y, 1) = 0;
        }
        if (mask(x, y) == 0) {
            spectrum(x, y, 0) = 0;
            spectrum(x, y, 1) = 0;
        }

        // Apply edge direction filter
        if (edgeDirection == 1) { // Horizontal edges
            if (std::abs(y - cy) > radius) {
                spectrum(x, y, 0) = 0;
                spectrum(x, y, 1) = 0;
            }
        } else if (edgeDirection == 2) { // Vertical edges
            if (std::abs(x - cx) > radius) {
                spectrum(x, y, 0) = 0;
                spectrum(x, y, 1) = 0;
            }
        } else if (edgeDirection == 3) { // Diagonal edges
            if (std::abs(x - y) > radius) {
                spectrum(x, y, 0) = 0;
                spectrum(x, y, 1) = 0;
            }
        }
    }

    spectrum(cx, cy, 0) = DC_mag;
    spectrum(cx, cy, 1) = DC_phase;

    return IFFT(spectrum);
}

CImg<unsigned char> Frequency::PhaseMod(const CImg<unsigned char>& image, int k, int l) {
    CImg<double> spectrum = FFT(image);
    Complex j = Complex(0, 1);
    int N = spectrum.width();
    int M = spectrum.height();
    
    CVector2D mask(spectrum.height(), std::vector<Complex>(spectrum.width()));
    for (int m = 0; m < M; m++) {
        for (int n = 0; n < N; n++) {
            double phase = -((n * k * 2 * M_PI) / N) - ((m * l * 2 * M_PI) / M) + (k + l) * M_PI;
            mask[m][n] = std::polar(1.0, phase);
        }
    }

    for (size_t m = 0; m < M; ++m) {
        for (size_t n = 0; n < N; ++n) {
            Complex value = Complex(spectrum(n, m, 0), spectrum(n, m, 1));
            value *= mask[m][n];
            spectrum(n, m, 0) = value.real();
            spectrum(n, m, 1) = value.imag();
        }
    }

    return IFFT(spectrum);
}