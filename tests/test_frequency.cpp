#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#define cimg_use_tiff
#include "Frequency.h"
#include <iostream>
using namespace cimg_library;

TEST_CASE("Frequency::CImgToCVector2D", "[frequency]") {
    CImg<unsigned char> testImage("mandril.bmp");
    CVector2D v1 = Frequency::CImgToCVector2D(testImage, 0);
    REQUIRE(v1.size() == testImage.height());
    REQUIRE(v1[0].size() == testImage.width());
}

TEST_CASE("Frequency::CVector2DToCImg", "[frequency]") {
    CImg<unsigned char> testImage("mandril.bmp");
    CVector2D v1 = Frequency::CImgToCVector2D(testImage, 0);
    CImg<unsigned char> result = Frequency::CVector2DToCImg(v1);
    REQUIRE(result.width() == testImage.width());
    REQUIRE(result.height() == testImage.height());
    cimg_forXYC(result, x, y, c) {
        REQUIRE(result(x, y, c) == testImage(x, y, c));
    }
}

TEST_CASE("Frequency::CVector2DToTiff", "[frequency]") {
    CImg<unsigned char> testImage("mandril.bmp");
    CVector2D v1 = Frequency::CImgToCVector2D(testImage, 0);
    Frequency::FFT_2D(v1, false);
    CImg<double> result = Frequency::CVector2DToTiff(v1);
    REQUIRE(result.width() == testImage.width());
    REQUIRE(result.height() == testImage.height());
    REQUIRE(result.depth() == 2);
    CVector2D v2 = Frequency::CImgToCVector2D(result, 0);
    REQUIRE(v1[0][0].real() == v2[0][0].real());
    REQUIRE(v1[0][0].imag() == v2[0][0].imag());
}

TEST_CASE("Frequency TiffAndBack", "[frequency]") {
    CImg<unsigned char> testImage("mandrilc.bmp");
    CVector2D v1 = Frequency::CImgToCVector2D(testImage, 0);
    Frequency::FFT_2D(v1, false);
    CImg<double> result = Frequency::CVector2DToTiff(v1);
    result.save_tiff("test.tiff");
    CImg<double> loadImage("test.tiff");
    REQUIRE(loadImage.width() == testImage.width());
    REQUIRE(loadImage.height() == testImage.height());
    REQUIRE(loadImage.depth() == 2);
    CVector2D v2 = Frequency::CImgToCVector2D(loadImage, 0);
    CImg<unsigned char> output = Frequency::CVector2DToCImg(v2);
    output.save_bmp("test2.bmp");
    for (size_t i = 0; i < v1.size(); ++i) {
        for (size_t j = 0; j < v1[i].size(); ++j) {
            REQUIRE_THAT(v1[i][j].real(), Catch::Matchers::WithinRel(v2[i][j].real(), 0.999));
            REQUIRE_THAT(v1[i][j].imag(), Catch::Matchers::WithinAbs(v2[i][j].imag(), 0.999));
        }
    }
}

TEST_CASE("Frequency::DFT_1D - not inverse", "[frequency]") {
    CVector v1 = {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)};
    Frequency::DFT_1D(v1, false);

    CVector expected = {
        Complex(10, 0),
        Complex(-2, 2),
        Complex(-2, 0),
        Complex(-2, -2)
    };

    for (size_t i = 0; i < v1.size(); ++i) {
        REQUIRE_THAT(v1[i].real(), Catch::Matchers::WithinRel(expected[i].real(), 1e-6));
        REQUIRE_THAT(v1[i].imag(), Catch::Matchers::WithinAbs(expected[i].imag(), 1e-6));
    }

    Frequency::DFT_1D(v1, true);
}

TEST_CASE("Frequency::FFT_1D - not inverse", "[frequency]") {
    CVector v1 = {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)};
    Frequency::FFT_1D(v1, false);
    
    CVector expected = {
        Complex(10, 0),
        Complex(-2, 2),
        Complex(-2, 0),
        Complex(-2, -2)
    };

    for (size_t i = 0; i < v1.size(); ++i) {
        REQUIRE_THAT(v1[i].real(), Catch::Matchers::WithinRel(expected[i].real(), 1e-6));
        REQUIRE_THAT(v1[i].imag(), Catch::Matchers::WithinAbs(expected[i].imag(), 1e-6));
    }
}

TEST_CASE("Frequency::DFT_1D - reverse", "[frequency]") {
    CVector v1 = {Complex(10, 0), Complex(-2, 2), Complex(-2, 0), Complex(-2, -2)};
    Frequency::DFT_1D(v1, true);

    CVector expected = {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)};

    for (size_t i = 0; i < v1.size(); ++i) {
        REQUIRE_THAT(v1[i].real(), Catch::Matchers::WithinRel(expected[i].real(), 1e-6));
        REQUIRE_THAT(v1[i].imag(), Catch::Matchers::WithinAbs(expected[i].imag(), 1e-6));
    }
}

TEST_CASE("Frequency::FFT_1D - reverse", "[frequency]") {
    CVector v1 = {Complex(10, 0), Complex(-2, 2), Complex(-2, 0), Complex(-2, -2)};
    Frequency::FFT_1D(v1, true);

    CVector expected = {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)};

    for (size_t i = 0; i < v1.size(); ++i) {
        REQUIRE_THAT(v1[i].real(), Catch::Matchers::WithinRel(expected[i].real(), 1e-6));
        REQUIRE_THAT(v1[i].imag(), Catch::Matchers::WithinAbs(expected[i].imag(), 1e-6));
    }
}

TEST_CASE("Frequency::DFT_2D - not inverse", "[frequency]") {
    CVector2D v1 = {
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)},
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)},
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)},
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)}
    };
    Frequency::DFT_2D(v1, false);

    CVector2D expected = {
        {Complex(40, 0), Complex(-8, 8), Complex(-8, 0), Complex(-8, -8)},
        {Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)},
        {Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)},
        {Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)}
    };

    for (size_t i = 0; i < v1.size(); ++i) {
        for (size_t j = 0; j < v1[i].size(); ++j) {
            if (std::abs(expected[i][j].real()) < 1e-6) {
                REQUIRE_THAT(v1[i][j].real(), Catch::Matchers::WithinAbs(expected[i][j].real(), 1e-6));
            } else {
                REQUIRE_THAT(v1[i][j].real(), Catch::Matchers::WithinRel(expected[i][j].real(), 1e-6));
            }
            REQUIRE_THAT(v1[i][j].imag(), Catch::Matchers::WithinAbs(expected[i][j].imag(), 1e-6));
        }
    }
}

TEST_CASE("Frequency::DFT_2D - inverse", "[frequency]") {
    CVector2D v1 = {
        {Complex(40, 0), Complex(-8, 8), Complex(-8, 0), Complex(-8, -8)},
        {Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)},
        {Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)},
        {Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)}
    };
    Frequency::DFT_2D(v1, true);

    CVector2D expected = {
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)},
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)},
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)},
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)}
    };

    for (size_t i = 0; i < v1.size(); ++i) {
        for (size_t j = 0; j < v1[i].size(); ++j) {
            REQUIRE_THAT(v1[i][j].real(), Catch::Matchers::WithinRel(expected[i][j].real(), 1e-6));
            REQUIRE_THAT(v1[i][j].imag(), Catch::Matchers::WithinAbs(expected[i][j].imag(), 1e-6));
        }
    }
}

TEST_CASE("Frequency::FFT_2D - not inverse", "[frequency]") {
    CVector2D v1 = {
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)},
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)},
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)},
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)}
    };
    Frequency::FFT_2D(v1, false);

    CVector2D expected = {
        {Complex(40, 0), Complex(-8, 8), Complex(-8, 0), Complex(-8, -8)},
        {Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)},
        {Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)},
        {Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)}
    };

    for (size_t i = 0; i < v1.size(); ++i) {
        for (size_t j = 0; j < v1[i].size(); ++j) {
            REQUIRE_THAT(v1[i][j].real(), Catch::Matchers::WithinRel(expected[i][j].real(), 1e-6));
            REQUIRE_THAT(v1[i][j].imag(), Catch::Matchers::WithinAbs(expected[i][j].imag(), 1e-6));
        }
    }
}

TEST_CASE("Frequency::FFT_2D - inverse", "[frequency]") {
    CVector2D v1 = {
        {Complex(40, 0), Complex(-8, 8), Complex(-8, 0), Complex(-8, -8)},
        {Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)},
        {Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)},
        {Complex(0, 0), Complex(0, 0), Complex(0, 0), Complex(0, 0)}
    };
    Frequency::FFT_2D(v1, true);

    CVector2D expected = {
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)},
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)},
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)},
        {Complex(1, 0), Complex(2, 0), Complex(3, 0), Complex(4, 0)}
    };

    for (size_t i = 0; i < v1.size(); ++i) {
        for (size_t j = 0; j < v1[i].size(); ++j) {
            REQUIRE_THAT(v1[i][j].real(), Catch::Matchers::WithinRel(expected[i][j].real(), 1e-6));
            REQUIRE_THAT(v1[i][j].imag(), Catch::Matchers::WithinAbs(expected[i][j].imag(), 1e-6));
        }
    }
}

TEST_CASE("Frequency::computeSpectrum", "[frequency]") {
    CVector2D v1 = {
        {Complex(1, 2), Complex(3, 4), Complex(5, 6), Complex(7, 8)},
        {Complex(9, 10), Complex(11, 12), Complex(13, 14), Complex(15, 16)},
        {Complex(17, 18), Complex(19, 20), Complex(21, 22), Complex(23, 24)},
        {Complex(25, 26), Complex(27, 28), Complex(29, 30), Complex(31, 32)}
    };
    CImg<double> result = Frequency::computeSpectrum(v1);
    REQUIRE(result.depth() == 2);
    REQUIRE(result.width() == v1[0].size());
    REQUIRE(result.height() == v1.size());
}

TEST_CASE("Frequency::reVectorizeSpectrum", "[frequency]") {
    CVector2D v1 = {
        {Complex(1, 2), Complex(3, 4), Complex(5, 6), Complex(7, 8)},
        {Complex(9, 10), Complex(11, 12), Complex(13, 14), Complex(15, 16)},
        {Complex(17, 18), Complex(19, 20), Complex(21, 22), Complex(23, 24)},
        {Complex(25, 26), Complex(27, 28), Complex(29, 30), Complex(31, 32)}
    };
    CImg<double> spectrum = Frequency::computeSpectrum(v1);
    CVector2D v2 = Frequency::reVecotrizeSpectrum(spectrum, 0);
    for (size_t i = 0; i < v1.size(); ++i) {
        for (size_t j = 0; j < v1[i].size(); ++j) {
            REQUIRE_THAT(v1[i][j].real(), Catch::Matchers::WithinRel(v2[i][j].real(), 1e-6));
            REQUIRE_THAT(v1[i][j].imag(), Catch::Matchers::WithinAbs(v2[i][j].imag(), 1e-6));
        }
    }
}

TEST_CASE("Frequency::MagnitudeSpectrum", "[frequency]") {
    CImg<unsigned char> testImage("mandril.bmp");
    std::cout << testImage.spectrum() << '\n';
    CImg<unsigned char> result = Frequency::MagnitudeSpectrum(testImage);
    result.save("task4/mandril_magnitude_spectrum.bmp");
    REQUIRE(result.width() == testImage.width());
    REQUIRE(result.height() == testImage.height());
}

TEST_CASE("Frequency::LowPass - mandrilc.bmp", "[frequency]") {
    CImg<unsigned char> testImage("mandrilc.bmp");
    CImg<unsigned char> result = Frequency::LowPass(testImage, 10);
    result.save("task4/mandrilc_lowpass_10.bmp");
    REQUIRE(result.width() == testImage.width());
    REQUIRE(result.height() == testImage.height());
}

TEST_CASE("Frequency::LowPass - mandril.bmp", "[frequency]") {
    CImg<unsigned char> testImage("mandril.bmp");
    CImg<unsigned char> result = Frequency::LowPass(testImage, 10);
    result.save("task4/mandril_lowpass_10.bmp");
    REQUIRE(result.width() == testImage.width());
    REQUIRE(result.height() == testImage.height());
}

TEST_CASE("Frequency::HighPass - mandrilc.bmp", "[frequency]") {
    CImg<unsigned char> testImage("mandrilc.bmp");
    CImg<unsigned char> result = Frequency::HighPass(testImage, 1);
    result.save("task4/mandrilc_highpass_1.bmp");
    REQUIRE(result.width() == testImage.width());
    REQUIRE(result.height() == testImage.height());
}

TEST_CASE("Frequency::HighPass - mandril.bmp", "[frequency]") {
    CImg<unsigned char> testImage("mandril.bmp");
    CImg<unsigned char> result = Frequency::HighPass(testImage, 1);
    result.save("task4/mandril_highpass_1.bmp");
    REQUIRE(result.width() == testImage.width());
    REQUIRE(result.height() == testImage.height());
}

TEST_CASE("Frequency::HighPass - lenac.bmp", "[frequency]") {
    CImg<unsigned char> testImage("lenac.bmp");
    CImg<unsigned char> result = Frequency::HighPass(testImage, 20);
    result.save("task4/lenac_highpass_20.bmp");
    REQUIRE(result.width() == testImage.width());
    REQUIRE(result.height() == testImage.height());
}

TEST_CASE("Frequency::BandCut - mandrilc.bmp", "[frequency]") {
    CImg<unsigned char> testImage("mandrilc.bmp");
    CImg<unsigned char> result = Frequency::BandCut(testImage, 40, 60);
    result.save("task4/mandrilc_bandcut_40_60.bmp");
    REQUIRE(result.width() == testImage.width());
    REQUIRE(result.height() == testImage.height());
}

TEST_CASE("Frequency::BandPass - mandrilc.bmp", "[frequency]") {
    CImg<unsigned char> testImage("mandrilc.bmp");
    CImg<unsigned char> result = Frequency::BandPass(testImage, 40, 60);
    result.save("task4/mandrilc_bandpass_40_60.bmp");
    REQUIRE(result.width() == testImage.width());
    REQUIRE(result.height() == testImage.height());
}

TEST_CASE("Frequency::HighPassEdgeDetection", "[frequency]") {
    CImg<unsigned char> testImage("F5test1.bmp");
    CImg<unsigned char> testImage2("F5test2.bmp");
    CImg<unsigned char> testImage3("F5test3.bmp");

    CImg<unsigned char> mask("F5mask1.bmp");
    CImg<unsigned char> mask2("F5mask2.bmp");

    CImg<unsigned char> result = Frequency::HighPassEdgeDetection(testImage, mask, 40, 1);
    CImg<unsigned char> result2 = Frequency::HighPassEdgeDetection(testImage2, mask, 40, 1);
    CImg<unsigned char> result3 = Frequency::HighPassEdgeDetection(testImage3, mask, 40, 1);
    CImg<unsigned char> result4 = Frequency::HighPassEdgeDetection(testImage, mask2, 40, 2);
    CImg<unsigned char> result5 = Frequency::HighPassEdgeDetection(testImage2, mask2, 40, 2);
    CImg<unsigned char> result6 = Frequency::HighPassEdgeDetection(testImage3, mask2, 40, 2);

    result.save("task4/F5test1_highpass_edge_detection_1_40_1.bmp");
    result2.save("task4/F5test2_highpass_edge_detection_1_40_1.bmp");
    result3.save("task4/F5test3_highpass_edge_detection_1_40_1.bmp");
    result4.save("task4/F5test1_highpass_edge_detection_2_40_2.bmp");
    result5.save("task4/F5test2_highpass_edge_detection_2_40_2.bmp");
    result6.save("task4/F5test3_highpass_edge_detection_2_40_2.bmp");

    REQUIRE(result.width() == testImage.width());
    REQUIRE(result.height() == testImage.height());
}

TEST_CASE("Frequency::PhaseMod - mandrilc.bmp", "[frequency]") {
    CImg<unsigned char> testImage("mandrilc.bmp");
    CImg<unsigned char> result = Frequency::PhaseMod(testImage, 10, 5);
    result.save("task4/mandrilc_phase_mod_10_5.bmp");
    REQUIRE(result.width() == testImage.width());
    REQUIRE(result.height() == testImage.height());
}

TEST_CASE("Task4 - raport", "[frequency]") {
    CImg<unsigned char> mandril("mandril.bmp");
    CImg<unsigned char> lena("lena.bmp");
    CImg<unsigned char> boat("boat.bmp");
    CImg<unsigned char> camera("camera.bmp");
    CImg<unsigned char> F5_1("F5test1.bmp");
    CImg<unsigned char> F5_2("F5test2.bmp");
    CImg<unsigned char> F5_3("F5test3.bmp");
    CImg<unsigned char> mask1("F5mask1.bmp");
    CImg<unsigned char> mask2("F5mask2.bmp");

    CImg<unsigned char> boat_mag_spectrum = Frequency::MagnitudeSpectrum(boat);
    CImg<unsigned char> camera_mag_spectrum = Frequency::MagnitudeSpectrum(camera);
    CImg<unsigned char> lena_mag_spectrum = Frequency::MagnitudeSpectrum(lena);
    CImg<unsigned char> mandril_mag_spectrum = Frequency::MagnitudeSpectrum(mandril);

    boat_mag_spectrum.save("task4/raport/boat_magnitude_spectrum.bmp");
    camera_mag_spectrum.save("task4/raport/camera_magnitude_spectrum.bmp");
    lena_mag_spectrum.save("task4/raport/lena_magnitude_spectrum.bmp");
    mandril_mag_spectrum.save("task4/raport/mandril_magnitude_spectrum.bmp");

    int low_pass_value = 30;
    CImg<unsigned char> boat_lowpass = Frequency::LowPass(boat, low_pass_value);
    CImg<unsigned char> camera_lowpass = Frequency::LowPass(camera, low_pass_value);
    CImg<unsigned char> lena_lowpass = Frequency::LowPass(lena, low_pass_value);
    CImg<unsigned char> mandril_lowpass = Frequency::LowPass(mandril, low_pass_value);
    boat_lowpass.save("task4/raport/boat_lowpass.bmp");
    camera_lowpass.save("task4/raport/camera_lowpass.bmp");
    lena_lowpass.save("task4/raport/lena_lowpass.bmp");
    mandril_lowpass.save("task4/raport/mandril_lowpass.bmp");

    int high_pass_value = 15;
    CImg<unsigned char> boat_highpass = Frequency::HighPass(boat, high_pass_value);
    CImg<unsigned char> camera_highpass = Frequency::HighPass(camera, high_pass_value);
    CImg<unsigned char> lena_highpass = Frequency::HighPass(lena, high_pass_value);
    CImg<unsigned char> mandril_highpass = Frequency::HighPass(mandril, high_pass_value);
    boat_highpass.save("task4/raport/boat_highpass.bmp");
    camera_highpass.save("task4/raport/camera_highpass.bmp");
    lena_highpass.save("task4/raport/lena_highpass.bmp");
    mandril_highpass.save("task4/raport/mandril_highpass.bmp");

    int bandpass_low = 10;
    int bandpass_high = 50;
    CImg<unsigned char> boat_bandpass = Frequency::BandPass(boat, bandpass_low, bandpass_high);
    CImg<unsigned char> camera_bandpass = Frequency::BandPass(camera, bandpass_low, bandpass_high);
    CImg<unsigned char> lena_bandpass = Frequency::BandPass(lena, bandpass_low, bandpass_high);
    CImg<unsigned char> mandril_bandpass = Frequency::BandPass(mandril, bandpass_low, bandpass_high);
    boat_bandpass.save("task4/raport/boat_bandpass.bmp");
    camera_bandpass.save("task4/raport/camera_bandpass.bmp");
    lena_bandpass.save("task4/raport/lena_bandpass.bmp");
    mandril_bandpass.save("task4/raport/mandril_bandpass.bmp");

    int bandcut_low = 15;
    int bandcut_high = 60;
    CImg<unsigned char> boat_bandcut = Frequency::BandCut(boat, bandcut_low, bandcut_high);
    CImg<unsigned char> camera_bandcut = Frequency::BandCut(camera, bandcut_low, bandcut_high);
    CImg<unsigned char> lena_bandcut = Frequency::BandCut(lena, bandcut_low, bandcut_high);
    CImg<unsigned char> mandril_bandcut = Frequency::BandCut(mandril, bandcut_low, bandcut_high);
    boat_bandcut.save("task4/raport/boat_bandcut.bmp");
    camera_bandcut.save("task4/raport/camera_bandcut.bmp");
    lena_bandcut.save("task4/raport/lena_bandcut.bmp");
    mandril_bandcut.save("task4/raport/mandril_bandcut.bmp");

    { // HighPassEdgeDetection
        CImg<unsigned char> F5_1_HPED_1_30_1 = Frequency::HighPassEdgeDetection(F5_1, mask1, 30, 1);
        CImg<unsigned char> F5_2_HPED_1_30_1 = Frequency::HighPassEdgeDetection(F5_2, mask1, 30, 1);
        CImg<unsigned char> F5_3_HPED_1_30_1 = Frequency::HighPassEdgeDetection(F5_3, mask1, 30, 1);
        CImg<unsigned char> F5_1_HPED_2_30_1 = Frequency::HighPassEdgeDetection(F5_1, mask2, 30, 1);
        CImg<unsigned char> F5_2_HPED_2_30_1 = Frequency::HighPassEdgeDetection(F5_2, mask2, 30, 1);
        CImg<unsigned char> F5_3_HPED_2_30_1 = Frequency::HighPassEdgeDetection(F5_3, mask2, 30, 1);

        CImg<unsigned char> F5_1_HPED_1_30_2 = Frequency::HighPassEdgeDetection(F5_1, mask1, 30, 2);
        CImg<unsigned char> F5_2_HPED_1_30_2 = Frequency::HighPassEdgeDetection(F5_2, mask1, 30, 2);
        CImg<unsigned char> F5_3_HPED_1_30_2 = Frequency::HighPassEdgeDetection(F5_3, mask1, 30, 2);
        CImg<unsigned char> F5_1_HPED_2_30_2 = Frequency::HighPassEdgeDetection(F5_1, mask2, 30, 2);
        CImg<unsigned char> F5_2_HPED_2_30_2 = Frequency::HighPassEdgeDetection(F5_2, mask2, 30, 2);
        CImg<unsigned char> F5_3_HPED_2_30_2 = Frequency::HighPassEdgeDetection(F5_3, mask2, 30, 2);

        CImg<unsigned char> F5_1_HPED_1_30_3 = Frequency::HighPassEdgeDetection(F5_1, mask1, 30, 3);
        CImg<unsigned char> F5_2_HPED_1_30_3 = Frequency::HighPassEdgeDetection(F5_2, mask1, 30, 3);
        CImg<unsigned char> F5_3_HPED_1_30_3 = Frequency::HighPassEdgeDetection(F5_3, mask1, 30, 3);
        CImg<unsigned char> F5_1_HPED_2_30_3 = Frequency::HighPassEdgeDetection(F5_1, mask2, 30, 3);
        CImg<unsigned char> F5_2_HPED_2_30_3 = Frequency::HighPassEdgeDetection(F5_2, mask2, 30, 3);
        CImg<unsigned char> F5_3_HPED_2_30_3 = Frequency::HighPassEdgeDetection(F5_3, mask2, 30, 3);

        F5_1_HPED_1_30_1.save("task4/raport/F5_1_HPED_1_30_1.bmp");
        F5_2_HPED_1_30_1.save("task4/raport/F5_2_HPED_1_30_1.bmp");
        F5_3_HPED_1_30_1.save("task4/raport/F5_3_HPED_1_30_1.bmp");
        F5_1_HPED_2_30_1.save("task4/raport/F5_1_HPED_2_30_1.bmp");
        F5_2_HPED_2_30_1.save("task4/raport/F5_2_HPED_2_30_1.bmp");
        F5_3_HPED_2_30_1.save("task4/raport/F5_3_HPED_2_30_1.bmp");

        F5_1_HPED_1_30_2.save("task4/raport/F5_1_HPED_1_30_2.bmp");
        F5_2_HPED_1_30_2.save("task4/raport/F5_2_HPED_1_30_2.bmp");
        F5_3_HPED_1_30_2.save("task4/raport/F5_3_HPED_1_30_2.bmp");
        F5_1_HPED_2_30_2.save("task4/raport/F5_1_HPED_2_30_2.bmp");
        F5_2_HPED_2_30_2.save("task4/raport/F5_2_HPED_2_30_2.bmp");
        F5_3_HPED_2_30_2.save("task4/raport/F5_3_HPED_2_30_2.bmp");

        F5_1_HPED_1_30_3.save("task4/raport/F5_1_HPED_1_30_3.bmp");
        F5_2_HPED_1_30_3.save("task4/raport/F5_2_HPED_1_30_3.bmp");
        F5_3_HPED_1_30_3.save("task4/raport/F5_3_HPED_1_30_3.bmp");
        F5_1_HPED_2_30_3.save("task4/raport/F5_1_HPED_2_30_3.bmp");
        F5_2_HPED_2_30_3.save("task4/raport/F5_2_HPED_2_30_3.bmp");
        F5_3_HPED_2_30_3.save("task4/raport/F5_3_HPED_2_30_3.bmp");
    }

    int k_factor = 6;
    int l_factor = 4;
    CImg<unsigned char> mandril_phase_mod = Frequency::PhaseMod(mandril, k_factor, l_factor);
    CImg<unsigned char> lena_phase_mod = Frequency::PhaseMod(lena, k_factor, l_factor);
    CImg<unsigned char> boat_phase_mod = Frequency::PhaseMod(boat, k_factor, l_factor);
    CImg<unsigned char> camera_phase_mod = Frequency::PhaseMod(camera, k_factor, l_factor);
    mandril_phase_mod.save("task4/raport/mandril_phase_mod_4_2.bmp");
    lena_phase_mod.save("task4/raport/lena_phase_mod_4_2.bmp");
    boat_phase_mod.save("task4/raport/boat_phase_mod_4_2.bmp");
    camera_phase_mod.save("task4/raport/camera_phase_mod_4_2.bmp");

    REQUIRE(1 == 1);
}