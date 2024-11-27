# task2_bash.ps1

Write-Output "Running ImageProcessing Task2"
$path_to_exe = "../build"

# Clear text files if they exist
if (Test-Path "../output/lena_hexponent.txt") {
    Clear-Content -Path "../output/lena_hexponent.txt"
}
if (Test-Path "../output/lena_orosenfeld.txt") {
    Clear-Content -Path "../output/lena_orosenfeld.txt"
}
if (Test-Path "../output/lena_extractionOfDetails.txt") {
    Clear-Content -Path "../output/lena_extractionOfDetails.txt"
}
if (Test-Path "../output/pentagon_hexponent.txt") {
    Clear-Content -Path "../output/pentagon_hexponent.txt"
}

$characteristics = "--cmean", "--cvariance", "--cstdev", "--cvarcoi", "--cvarcoii", "--casyco", "--cflatco", "--centropy"

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp $characteristics --file ../output/lena.txt 

# Run histogram
& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_30_250_05.bmp --histogram 0 ../output/lena_histogram.bmp --hexponent 30 250 0.5 --histogram 0 ../output/lena_histogram_hexponent_30_250_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_60_220_05.bmp --hexponent 60 220 0.5 --histogram 0 ../output/lena_histogram_hexponent_60_220_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_90_190_05.bmp --hexponent 90 190 0.5 --histogram 0 ../output/lena_histogram_hexponent_90_190_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_30_250_1.bmp --hexponent 30 250 1 --histogram 0 ../output/lena_histogram_hexponent_30_250_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_60_220_1.bmp --hexponent 60 220 1 --histogram 0 ../output/lena_histogram_hexponent_60_220_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_90_190_1.bmp --hexponent 90 190 1 --histogram 0 ../output/lena_histogram_hexponent_90_190_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_30_250_2.bmp --hexponent 30 250 2 --histogram 0 ../output/lena_histogram_hexponent_30_250_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_60_220_2.bmp --hexponent 60 220 2 --histogram 0 ../output/lena_histogram_hexponent_60_220_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_90_190_2.bmp --hexponent 90 190 2 --histogram 0 ../output/lena_histogram_hexponent_90_190_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_30_250_025.bmp --hexponent 30 250 0.25 --histogram 0 ../output/lena_histogram_hexponent_30_250_025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_60_220_025.bmp --hexponent 60 220 0.25 --histogram 0 ../output/lena_histogram_hexponent_60_220_025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_90_190_025.bmp --hexponent 90 190 0.25 --histogram 0 ../output/lena_histogram_hexponent_90_190_025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_30_250_005.bmp --hexponent 30 250 0.05 --histogram 0 ../output/lena_histogram_hexponent_30_250_005.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_60_220_005.bmp --hexponent 60 220 0.05 --histogram 0 ../output/lena_histogram_hexponent_60_220_005.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_90_190_005.bmp --hexponent 90 190 0.05 --histogram 0 ../output/lena_histogram_hexponent_90_190_005.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lenac.bmp --output ../output/lenac_hexponent_60_220_1.bmp --histogram 0 ../output/lenac_histogram_red.bmp --histogram 1 ../output/lenac_histogram_green.bmp --histogram 2 ../output/lenac_histogram_blue.bmp --hexponent 60 220 1 --histogram 0 ../output/lenac_histogram_red_hexponent_60_220_1.bmp --histogram 1 ../output/lenac_histogram_green_hexponent_60_220_1.bmp --histogram 2 ../output/lenac_histogram_blue_hexponent_60_220_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lenac.bmp --output ../output/lenac_hexponent_60_220_05.bmp --hexponent 60 220 0.5 --histogram 0 ../output/lenac_histogram_red_hexponent_60_220_05.bmp --histogram 1 ../output/lenac_histogram_green_hexponent_60_220_05.bmp --histogram 2 ../output/lenac_histogram_blue_hexponent_60_220_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lenac.bmp --output ../output/lenac_hexponent_60_220_2.bmp --hexponent 60 220 2 --histogram 0 ../output/lenac_histogram_red_hexponent_60_220_2.bmp --histogram 1 ../output/lenac_histogram_green_hexponent_60_220_2.bmp --histogram 2 ../output/lenac_histogram_blue_hexponent_60_220_2.bmp


& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_30_250_05.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_60_220_05.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_90_190_05.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_30_250_1.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_60_220_1.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_90_190_1.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_30_250_2.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_60_220_2.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_90_190_2.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_30_250_025.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_60_220_025.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_90_190_025.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lenac_hexponent_60_220_1.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lenac_hexponent_60_220_05.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lenac_hexponent_60_220_2.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_30_250_005.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_60_220_005.bmp $characteristics --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_hexponent_90_190_005.bmp $characteristics --file ../output/lena_hexponent.txt

# Run nonLinearSpatial
& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_orosenfeld_0.bmp --orosenfeld 0 --histogram 0 ../output/lena_histogram_orosenfeld_0.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_orosenfeld_1.bmp --orosenfeld 1 --histogram 0 ../output/lena_histogram_orosenfeld_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_orosenfeld_2.bmp --orosenfeld 2 --histogram 0 ../output/lena_histogram_orosenfeld_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_orosenfeld_3.bmp --orosenfeld 3 --histogram 0 ../output/lena_histogram_orosenfeld_3.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_orosenfeld_4.bmp --orosenfeld 4 --histogram 0 ../output/lena_histogram_orosenfeld_4.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_orosenfeld_5.bmp --orosenfeld 5 --histogram 0 ../output/lena_histogram_orosenfeld_5.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_orosenfeld_6.bmp --orosenfeld 6 --histogram 0 ../output/lena_histogram_orosenfeld_6.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_orosenfeld_7.bmp --orosenfeld 7 --histogram 0 ../output/lena_histogram_orosenfeld_7.bmp



& "$path_to_exe/imageProcessing.exe" --input ../output/lena_orosenfeld_0.bmp $characteristics --file ../output/lena_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_orosenfeld_1.bmp $characteristics --file ../output/lena_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_orosenfeld_2.bmp $characteristics --file ../output/lena_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_orosenfeld_3.bmp $characteristics --file ../output/lena_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_orosenfeld_4.bmp $characteristics --file ../output/lena_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_orosenfeld_5.bmp $characteristics --file ../output/lena_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_orosenfeld_6.bmp $characteristics --file ../output/lena_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_orosenfeld_7.bmp $characteristics --file ../output/lena_orosenfeld.txt

# Run linearSpatial
& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_extractionOfDetailsN.bmp --sexdeti N --histogram 0 ../output/lena_histogram_N.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_extractionOfDetailsNE.bmp --sexdeti NE --histogram 0 ../output/lena_histogram_NE.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_extractionOfDetailsE.bmp --sexdeti E --histogram 0 ../output/lena_histogram_E.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_extractionOfDetailsSE.bmp --sexdeti SE --histogram 0 ../output/lena_histogram_SE.bmp



& "$path_to_exe/imageProcessing.exe" --input ../output/lena_extractionOfDetailsN.bmp $characteristics --file ../output/lena_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_extractionOfDetailsNE.bmp $characteristics --file ../output/lena_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_extractionOfDetailsE.bmp $characteristics --file ../output/lena_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_extractionOfDetailsSE.bmp $characteristics --file ../output/lena_extractionOfDetails.txt








# The same for impulse noise
# Run histogram
& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_30_250_05.bmp --histogram 0 ../output/lena_impulse3_histogram.bmp --hexponent 30 250 0.5 --histogram 0 ../output/lena_impulse3_histogram_hexponent_30_250_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_60_220_05.bmp --hexponent 60 220 0.5 --histogram 0 ../output/lena_impulse3_histogram_hexponent_60_220_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_90_190_05.bmp --hexponent 90 190 0.5 --histogram 0 ../output/lena_impulse3_histogram_hexponent_90_190_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_30_250_1.bmp --hexponent 30 250 1 --histogram 0 ../output/lena_impulse3_histogram_hexponent_30_250_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_60_220_1.bmp --hexponent 60 220 1 --histogram 0 ../output/lena_impulse3_histogram_hexponent_60_220_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_90_190_1.bmp --hexponent 90 190 1 --histogram 0 ../output/lena_impulse3_histogram_hexponent_90_190_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_30_250_2.bmp --hexponent 30 250 2 --histogram 0 ../output/lena_impulse3_histogram_hexponent_30_250_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_60_220_2.bmp --hexponent 60 220 2 --histogram 0 ../output/lena_impulse3_histogram_hexponent_60_220_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_90_190_2.bmp --hexponent 90 190 2 --histogram 0 ../output/lena_impulse3_histogram_hexponent_90_190_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_30_250_025.bmp --hexponent 30 250 0.25 --histogram 0 ../output/lena_impulse3_histogram_hexponent_30_250_025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_60_220_025.bmp --hexponent 60 220 0.25 --histogram 0 ../output/lena_impulse3_histogram_hexponent_60_220_025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_90_190_025.bmp --hexponent 90 190 0.25 --histogram 0 ../output/lena_impulse3_histogram_hexponent_90_190_025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_30_250_005.bmp --hexponent 30 250 0.05 --histogram 0 ../output/lena_impulse3_histogram_hexponent_30_250_005.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_60_220_005.bmp --hexponent 60 220 0.05 --histogram 0 ../output/lena_impulse3_histogram_hexponent_60_220_005.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_hexponent_90_190_005.bmp --hexponent 90 190 0.05 --histogram 0 ../output/lena_impulse3_histogram_hexponent_90_190_005.bmp


& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_30_250_05.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_60_220_05.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_90_190_05.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_30_250_1.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_60_220_1.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_90_190_1.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_30_250_2.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_60_220_2.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_90_190_2.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_30_250_025.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_60_220_025.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_90_190_025.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_30_250_005.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_60_220_005.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_hexponent_90_190_005.bmp $characteristics --file ../output/lena_impulse3_hexponent.txt

# Run nonLinearSpatial
& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_orosenfeld_0.bmp --orosenfeld 0 --histogram 0 ../output/lena_impulse3_histogram_orosenfeld_0.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_orosenfeld_1.bmp --orosenfeld 1 --histogram 0 ../output/lena_impulse3_histogram_orosenfeld_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_orosenfeld_2.bmp --orosenfeld 2 --histogram 0 ../output/lena_impulse3_histogram_orosenfeld_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_orosenfeld_3.bmp --orosenfeld 3 --histogram 0 ../output/lena_impulse3_histogram_orosenfeld_3.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_orosenfeld_4.bmp --orosenfeld 4 --histogram 0 ../output/lena_impulse3_histogram_orosenfeld_4.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_orosenfeld_5.bmp --orosenfeld 5 --histogram 0 ../output/lena_impulse3_histogram_orosenfeld_5.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_orosenfeld_6.bmp --orosenfeld 6 --histogram 0 ../output/lena_impulse3_histogram_orosenfeld_6.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_orosenfeld_7.bmp --orosenfeld 7 --histogram 0 ../output/lena_impulse3_histogram_orosenfeld_7.bmp



& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_orosenfeld_0.bmp $characteristics --file ../output/lena_impulse3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_orosenfeld_1.bmp $characteristics --file ../output/lena_impulse3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_orosenfeld_2.bmp $characteristics --file ../output/lena_impulse3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_orosenfeld_3.bmp $characteristics --file ../output/lena_impulse3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_orosenfeld_4.bmp $characteristics --file ../output/lena_impulse3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_orosenfeld_5.bmp $characteristics --file ../output/lena_impulse3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_orosenfeld_6.bmp $characteristics --file ../output/lena_impulse3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_orosenfeld_7.bmp $characteristics --file ../output/lena_impulse3_orosenfeld.txt

# Run linearSpatial
& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_extractionOfDetailsN.bmp --sexdeti N --histogram 0 ../output/lena_impulse3_histogram_N.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_extractionOfDetailsNE.bmp --sexdeti NE --histogram 0 ../output/lena_impulse3_histogram_NE.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_extractionOfDetailsE.bmp --sexdeti E --histogram 0 ../output/lena_impulse3_histogram_E.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_impulse3.bmp --output ../output/lena_impulse3_extractionOfDetailsSE.bmp --sexdeti SE --histogram 0 ../output/lena_impulse3_histogram_SE.bmp



& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_extractionOfDetailsN.bmp $characteristics --file ../output/lena_impulse3_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_extractionOfDetailsNE.bmp $characteristics --file ../output/lena_impulse3_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_extractionOfDetailsE.bmp $characteristics --file ../output/lena_impulse3_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_impulse3_extractionOfDetailsSE.bmp $characteristics --file ../output/lena_impulse3_extractionOfDetails.txt










# The same for uniform noise
# Run histogram
& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_30_250_05.bmp --histogram 0 ../output/lena_uniform3_histogram.bmp --hexponent 30 250 0.5 --histogram 0 ../output/lena_uniform3_histogram_hexponent_30_250_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_60_220_05.bmp --hexponent 60 220 0.5 --histogram 0 ../output/lena_uniform3_histogram_hexponent_60_220_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_90_190_05.bmp --hexponent 90 190 0.5 --histogram 0 ../output/lena_uniform3_histogram_hexponent_90_190_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_30_250_1.bmp --hexponent 30 250 1 --histogram 0 ../output/lena_uniform3_histogram_hexponent_30_250_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_60_220_1.bmp --hexponent 60 220 1 --histogram 0 ../output/lena_uniform3_histogram_hexponent_60_220_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_90_190_1.bmp --hexponent 90 190 1 --histogram 0 ../output/lena_uniform3_histogram_hexponent_90_190_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_30_250_2.bmp --hexponent 30 250 2 --histogram 0 ../output/lena_uniform3_histogram_hexponent_30_250_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_60_220_2.bmp --hexponent 60 220 2 --histogram 0 ../output/lena_uniform3_histogram_hexponent_60_220_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_90_190_2.bmp --hexponent 90 190 2 --histogram 0 ../output/lena_uniform3_histogram_hexponent_90_190_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_30_250_025.bmp --hexponent 30 250 0.25 --histogram 0 ../output/lena_uniform3_histogram_hexponent_30_250_025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_60_220_025.bmp --hexponent 60 220 0.25 --histogram 0 ../output/lena_uniform3_histogram_hexponent_60_220_025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_90_190_025.bmp --hexponent 90 190 0.25 --histogram 0 ../output/lena_uniform3_histogram_hexponent_90_190_025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_30_250_005.bmp --hexponent 30 250 0.05 --histogram 0 ../output/lena_uniform3_histogram_hexponent_30_250_005.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_60_220_005.bmp --hexponent 60 220 0.05 --histogram 0 ../output/lena_uniform3_histogram_hexponent_60_220_005.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_hexponent_90_190_005.bmp --hexponent 90 190 0.05 --histogram 0 ../output/lena_uniform3_histogram_hexponent_90_190_005.bmp


& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_30_250_05.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_60_220_05.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_90_190_05.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_30_250_1.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_60_220_1.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_90_190_1.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_30_250_2.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_60_220_2.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_90_190_2.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_30_250_025.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_60_220_025.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_90_190_025.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_30_250_005.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_60_220_005.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_hexponent_90_190_005.bmp $characteristics --file ../output/lena_uniform3_hexponent.txt

# Run nonLinearSpatial
& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_orosenfeld_0.bmp --orosenfeld 0 --histogram 0 ../output/lena_uniform3_histogram_orosenfeld_0.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_orosenfeld_1.bmp --orosenfeld 1 --histogram 0 ../output/lena_uniform3_histogram_orosenfeld_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_orosenfeld_2.bmp --orosenfeld 2 --histogram 0 ../output/lena_uniform3_histogram_orosenfeld_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_orosenfeld_3.bmp --orosenfeld 3 --histogram 0 ../output/lena_uniform3_histogram_orosenfeld_3.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_orosenfeld_4.bmp --orosenfeld 4 --histogram 0 ../output/lena_uniform3_histogram_orosenfeld_4.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_orosenfeld_5.bmp --orosenfeld 5 --histogram 0 ../output/lena_uniform3_histogram_orosenfeld_5.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_orosenfeld_6.bmp --orosenfeld 6 --histogram 0 ../output/lena_uniform3_histogram_orosenfeld_6.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_orosenfeld_7.bmp --orosenfeld 7 --histogram 0 ../output/lena_uniform3_histogram_orosenfeld_7.bmp



& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_orosenfeld_0.bmp $characteristics --file ../output/lena_uniform3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_orosenfeld_1.bmp $characteristics --file ../output/lena_uniform3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_orosenfeld_2.bmp $characteristics --file ../output/lena_uniform3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_orosenfeld_3.bmp $characteristics --file ../output/lena_uniform3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_orosenfeld_4.bmp $characteristics --file ../output/lena_uniform3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_orosenfeld_5.bmp $characteristics --file ../output/lena_uniform3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_orosenfeld_6.bmp $characteristics --file ../output/lena_uniform3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_orosenfeld_7.bmp $characteristics --file ../output/lena_uniform3_orosenfeld.txt

# Run linearSpatial
& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_extractionOfDetailsN.bmp --sexdeti N --histogram 0 ../output/lena_uniform3_histogram_N.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_extractionOfDetailsNE.bmp --sexdeti NE --histogram 0 ../output/lena_uniform3_histogram_NE.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_extractionOfDetailsE.bmp --sexdeti E --histogram 0 ../output/lena_uniform3_histogram_E.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_uniform3.bmp --output ../output/lena_uniform3_extractionOfDetailsSE.bmp --sexdeti SE --histogram 0 ../output/lena_uniform3_histogram_SE.bmp



& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_extractionOfDetailsN.bmp $characteristics --file ../output/lena_uniform3_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_extractionOfDetailsNE.bmp $characteristics --file ../output/lena_uniform3_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_extractionOfDetailsE.bmp $characteristics --file ../output/lena_uniform3_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_uniform3_extractionOfDetailsSE.bmp $characteristics --file ../output/lena_uniform3_extractionOfDetails.txt
















# The same for normal noise
# Run histogram
& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_30_250_05.bmp --histogram 0 ../output/lena_normal3_histogram.bmp --hexponent 30 250 0.5 --histogram 0 ../output/lena_normal3_histogram_hexponent_30_250_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_60_220_05.bmp --hexponent 60 220 0.5 --histogram 0 ../output/lena_normal3_histogram_hexponent_60_220_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_90_190_05.bmp --hexponent 90 190 0.5 --histogram 0 ../output/lena_normal3_histogram_hexponent_90_190_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_30_250_1.bmp --hexponent 30 250 1 --histogram 0 ../output/lena_normal3_histogram_hexponent_30_250_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_60_220_1.bmp --hexponent 60 220 1 --histogram 0 ../output/lena_normal3_histogram_hexponent_60_220_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_90_190_1.bmp --hexponent 90 190 1 --histogram 0 ../output/lena_normal3_histogram_hexponent_90_190_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_30_250_2.bmp --hexponent 30 250 2 --histogram 0 ../output/lena_normal3_histogram_hexponent_30_250_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_60_220_2.bmp --hexponent 60 220 2 --histogram 0 ../output/lena_normal3_histogram_hexponent_60_220_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_90_190_2.bmp --hexponent 90 190 2 --histogram 0 ../output/lena_normal3_histogram_hexponent_90_190_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_30_250_025.bmp --hexponent 30 250 0.25 --histogram 0 ../output/lena_normal3_histogram_hexponent_30_250_025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_60_220_025.bmp --hexponent 60 220 0.25 --histogram 0 ../output/lena_normal3_histogram_hexponent_60_220_025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_90_190_025.bmp --hexponent 90 190 0.25 --histogram 0 ../output/lena_normal3_histogram_hexponent_90_190_025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_30_250_005.bmp --hexponent 30 250 0.05 --histogram 0 ../output/lena_normal3_histogram_hexponent_30_250_005.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_60_220_005.bmp --hexponent 60 220 0.05 --histogram 0 ../output/lena_normal3_histogram_hexponent_60_220_005.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_hexponent_90_190_005.bmp --hexponent 90 190 0.05 --histogram 0 ../output/lena_normal3_histogram_hexponent_90_190_005.bmp


& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_30_250_05.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_60_220_05.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_90_190_05.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_30_250_1.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_60_220_1.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_90_190_1.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_30_250_2.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_60_220_2.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_90_190_2.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_30_250_025.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_60_220_025.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_90_190_025.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_30_250_005.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_60_220_005.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_hexponent_90_190_005.bmp $characteristics --file ../output/lena_normal3_hexponent.txt

# Run nonLinearSpatial
& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_orosenfeld_0.bmp --orosenfeld 0 --histogram 0 ../output/lena_normal3_histogram_orosenfeld_0.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_orosenfeld_1.bmp --orosenfeld 1 --histogram 0 ../output/lena_normal3_histogram_orosenfeld_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_orosenfeld_2.bmp --orosenfeld 2 --histogram 0 ../output/lena_normal3_histogram_orosenfeld_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_orosenfeld_3.bmp --orosenfeld 3 --histogram 0 ../output/lena_normal3_histogram_orosenfeld_3.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_orosenfeld_4.bmp --orosenfeld 4 --histogram 0 ../output/lena_normal3_histogram_orosenfeld_4.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_orosenfeld_5.bmp --orosenfeld 5 --histogram 0 ../output/lena_normal3_histogram_orosenfeld_5.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_orosenfeld_6.bmp --orosenfeld 6 --histogram 0 ../output/lena_normal3_histogram_orosenfeld_6.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_orosenfeld_7.bmp --orosenfeld 7 --histogram 0 ../output/lena_normal3_histogram_orosenfeld_7.bmp



& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_orosenfeld_0.bmp $characteristics --file ../output/lena_normal3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_orosenfeld_1.bmp $characteristics --file ../output/lena_normal3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_orosenfeld_2.bmp $characteristics --file ../output/lena_normal3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_orosenfeld_3.bmp $characteristics --file ../output/lena_normal3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_orosenfeld_4.bmp $characteristics --file ../output/lena_normal3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_orosenfeld_5.bmp $characteristics --file ../output/lena_normal3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_orosenfeld_6.bmp $characteristics --file ../output/lena_normal3_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_orosenfeld_7.bmp $characteristics --file ../output/lena_normal3_orosenfeld.txt

# Run linearSpatial
& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_extractionOfDetailsN.bmp --sexdeti N --histogram 0 ../output/lena_normal3_histogram_N.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_extractionOfDetailsNE.bmp --sexdeti NE --histogram 0 ../output/lena_normal3_histogram_NE.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_extractionOfDetailsE.bmp --sexdeti E --histogram 0 ../output/lena_normal3_histogram_E.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena_normal3.bmp --output ../output/lena_normal3_extractionOfDetailsSE.bmp --sexdeti SE --histogram 0 ../output/lena_normal3_histogram_SE.bmp



& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_extractionOfDetailsN.bmp $characteristics --file ../output/lena_normal3_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_extractionOfDetailsNE.bmp $characteristics --file ../output/lena_normal3_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_extractionOfDetailsE.bmp $characteristics --file ../output/lena_normal3_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_normal3_extractionOfDetailsSE.bmp $characteristics --file ../output/lena_normal3_extractionOfDetails.txt







& "$path_to_exe/imageProcessing.exe" --input ../images/pentagon.bmp --output ../output/pentagon_hexponent_70_255_0025.bmp --histogram 0 ../output/pentagon_histogram.bmp --hexponent 70 255 0.025 --histogram 0 ../output/pentagon_histogram_hexponent_70_255_0025.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/pentagon.bmp --output ../output/pentagon_hexponent_70_255_002.bmp --histogram 0 ../output/pentagon_histogram.bmp --hexponent 70 255 0.02 --histogram 0 ../output/pentagon_histogram_hexponent_70_255_002.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/pentagon.bmp --output ../output/pentagon_hexponent_70_255_003.bmp --histogram 0 ../output/pentagon_histogram.bmp --hexponent 70 255 0.03 --histogram 0 ../output/pentagon_histogram_hexponent_70_255_003.bmp

& "$path_to_exe/imageProcessing.exe" --input ../output/pentagon_hexponent_70_255_002.bmp $characteristics --file ../output/pentagon_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/pentagon_hexponent_70_255_0025.bmp $characteristics --file ../output/pentagon_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/pentagon_hexponent_70_255_003.bmp $characteristics --file ../output/pentagon_hexponent.txt



& "$path_to_exe/imageProcessing.exe" --input ../images/pentagon.bmp --output ../output/pentagon_orosenfeld_2.bmp --orosenfeld 2 --histogram 0 ../output/pentagon_histogram_orosenfeld_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/pentagon.bmp --output ../output/pentagon_orosenfeld_3.bmp --orosenfeld 3 --histogram 0 ../output/pentagon_histogram_orosenfeld_3.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/pentagon.bmp --output ../output/pentagon_orosenfeld_4.bmp --orosenfeld 4 --histogram 0 ../output/pentagon_histogram_orosenfeld_4.bmp



& "$path_to_exe/imageProcessing.exe" --input ../output/pentagon_orosenfeld_2.bmp $characteristics --file ../output/pentagon_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/pentagon_orosenfeld_3.bmp $characteristics --file ../output/pentagon_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/pentagon_orosenfeld_4.bmp $characteristics --file ../output/pentagon_orosenfeld.txt