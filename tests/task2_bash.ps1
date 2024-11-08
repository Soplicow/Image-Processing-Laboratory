# task2_bash.ps1

Write-Output "Running ImageProcessing Task2"
$path_to_exe = "../build"

# Clear text files
Clear-Content -Path "../output/lena_hexponent.txt"
Clear-Content -Path "../output/lena_orosenfeld.txt"
Clear-Content -Path "../output/lena_extractionOfDetails.txt"

# Run histogram
& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_30_250_05.bmp --histogram 0 ../output/lena_histogram.bmp --hexponent 30 250 0.5 --histogram 0 ../output/lena_histogram_hexponent_30_250_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_60_220_05.bmp --hexponent 60 220 0.5 --histogram 0 ../output/lena_histogram_hexponent_60_220_05.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_30_250_1.bmp --hexponent 30 250 1 --histogram 0 ../output/lena_histogram_hexponent_30_250_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_60_220_1.bmp --hexponent 60 220 1 --histogram 0 ../output/lena_histogram_hexponent_60_220_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_30_250_2.bmp --hexponent 30 250 2 --histogram 0 ../output/lena_histogram_hexponent_30_250_2.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_hexponent_60_220_2.bmp --hexponent 60 220 2 --histogram 0 ../output/lena_histogram_hexponent_60_220_2.bmp



& "$path_to_exe/imageProcessing.exe" --input ../output/lena_histogram_hexponent_30_250_05.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_histogram_hexponent_60_220_05.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_histogram_hexponent_30_250_1.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_histogram_hexponent_60_220_1.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_histogram_hexponent_30_250_2.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_hexponent.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_histogram_hexponent_60_220_2.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_hexponent.txt

# Run nonLinearSpatial
& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_orosenfeld_0.bmp --orosenfeld 0 --histogram 0 ../output/lena_histogram_orosenfeld_0.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_orosenfeld_1.bmp --orosenfeld 1 --histogram 0 ../output/lena_histogram_orosenfeld_1.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_orosenfeld_2.bmp --orosenfeld 2 --histogram 0 ../output/lena_histogram_orosenfeld_2.bmp



& "$path_to_exe/imageProcessing.exe" --input ../output/lena_orosenfeld_0.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_orosenfeld_1.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_orosenfeld.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_orosenfeld_2.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_orosenfeld.txt

# Run linearSpatial
& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_extractionOfDetailsNE.bmp --sexdeti NE --histogram 0 ../output/lena_histogram_NE.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_extractionOfDetailsN.bmp --sexdeti N --histogram 0 ../output/lena_histogram_N.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_extractionOfDetailsE.bmp --sexdeti E --histogram 0 ../output/lena_histogram_E.bmp

& "$path_to_exe/imageProcessing.exe" --input ../images/lena.bmp --output ../output/lena_extractionOfDetailsSE.bmp --sexdeti SE --histogram 0 ../output/lena_histogram_SE.bmp



& "$path_to_exe/imageProcessing.exe" --input ../output/lena_extractionOfDetailsN.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_extractionOfDetailsNE.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_extractionOfDetailsE.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_extractionOfDetails.txt

& "$path_to_exe/imageProcessing.exe" --input ../output/lena_extractionOfDetailsSE.bmp --cmean --cvariance --cstdev --cvarcoi --cvarcoii --casyco --cflatco --centropy --file ../output/lena_extractionOfDetails.txt