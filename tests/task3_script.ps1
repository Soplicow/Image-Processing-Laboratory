# task3_script.ps1

Write-Output "Running ImageProcessing Task3"
$path_to_exe = "../build"
$output = "../output/task_3"
$erosion = "$output/erosion"
$dilation = "$output/dilation"
$HMT = "$output/HMT"
$opening = "$output/opening"
$closing = "$output/closing"
$regionGrowing = "$output/regionGrowing"
$M7 = "$output/M7"

if (-Not (Test-Path -Path $output)) {
    New-Item -ItemType Directory -Path $output
}
if (-Not (Test-Path -Path $erosion)) {
    New-Item -ItemType Directory -Path $erosion
}
if (-Not (Test-Path -Path $dilation)) {
    New-Item -ItemType Directory -Path $dilation
}
if (-Not (Test-Path -Path $HMT)) {
    New-Item -ItemType Directory -Path $HMT
}
if (-Not (Test-Path -Path $opening)) {
    New-Item -ItemType Directory -Path $opening
}
if (-Not (Test-Path -Path $closing)) {
    New-Item -ItemType Directory -Path $closing
}
if (-Not (Test-Path -Path $regionGrowing)) {
    New-Item -ItemType Directory -Path $regionGrowing
}
if (-Not (Test-Path -Path $M7)) {
    New-Item -ItemType Directory -Path $M7
}


Write-Output "Running Erosion"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$erosion/lenabw_erosion3.bmp" --erosion 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$erosion/mandrilbw_erosion3.bmp" --erosion 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$erosion/lenabw_erosion4.bmp" --erosion 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$erosion/mandrilbw_erosion4.bmp" --erosion 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$erosion/lenabw_erosion6.bmp" --erosion 6

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$erosion/mandrilbw_erosion6.bmp" --erosion 6

Write-Output "Running Dilation"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$dilation/lenabw_dilation3.bmp" --dilation 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$dilation/mandrilbw_dilation3.bmp" --dilation 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$dilation/lenabw_dilation4.bmp" --dilation 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$dilation/mandrilbw_dilation4.bmp" --dilation 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$dilation/lenabw_dilation6.bmp" --dilation 6

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$dilation/mandrilbw_dilation6.bmp" --dilation 6

Write-Output "Running Opening"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$opening/lenabw_opening3.bmp" --opening 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$opening/mandrilbw_opening3.bmp" --opening 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$opening/lenabw_opening4.bmp" --opening 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$opening/mandrilbw_opening4.bmp" --opening 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$opening/lenabw_opening6.bmp" --opening 6

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$opening/mandrilbw_opening6.bmp" --opening 6

Write-Output "Running Closing"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$closing/lenabw_closing3.bmp" --closing 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$closing/mandrilbw_closing3.bmp" --closing 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$closing/lenabw_closing4.bmp" --closing 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$closing/mandrilbw_closing4.bmp" --closing 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$closing/lenabw_closing6.bmp" --closing 6

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$closing/mandrilbw_closing6.bmp" --closing 6

Write-Output "Running HMT"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$HMT/lenabw_htm_11left.bmp" --HMT 11 left

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$HMT/mandrilbw_htm_11left.bmp" --HMT 11 left

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$HMT/lenabw_htm_11right.bmp" --HMT 11 right

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$HMT/mandrilbw_htm_11right.bmp" --HMT 11 right

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$HMT/lenabw_htm_12bottomleft.bmp" --HMT 12 bottom-left

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$HMT/mandrilbw_htm_12bottomleft.bmp" --HMT 12 bottom-left

Write-Output "Running M7"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$M7/lenabw_m7_3.bmp" --M7 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$M7/mandrilbw_m7_3.bmp" --M7 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$M7/lenabw_m7_4.bmp" --M7 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$M7/mandrilbw_m7_4.bmp" --M7 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$M7/lenabw_m7_6.bmp" --M7 6

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$M7/mandrilbw_m7_6.bmp" --M7 6

Write-Output "Running region growing"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenac.bmp --output "$regionGrowing/lenac_region_growing_15_15_160_0.bmp" --regionGrowing 15 15 160 0

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenac.bmp --output "$regionGrowing/lenac_region_growing_320_450_120_0.bmp" --regionGrowing 320 450 120 0

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilc.bmp --output "$regionGrowing/mandrilc_region_growing_200_250_100_0.bmp" --regionGrowing 200 250 100 0

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilc.bmp --output "$regionGrowing/mandrilc_region_growing_250_250_162_0.bmp" --regionGrowing 250 250 162 0


& "$path_to_exe/ImageProcessing.exe" --input ../images/lenac.bmp --output "$regionGrowing/lenac_region_growing_15_15_300_1.bmp" --regionGrowing 15 15 300 1

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenac.bmp --output "$regionGrowing/lenac_region_growing_320_450_160_1.bmp" --regionGrowing 320 450 160 1

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilc.bmp --output "$regionGrowing/mandrilc_region_growing_200_250_100_1.bmp" --regionGrowing 200 250 100 1

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilc.bmp --output "$regionGrowing/mandrilc_region_growing_250_250_162_1.bmp" --regionGrowing 250 250 250 1


& "$path_to_exe/ImageProcessing.exe" --input ../images/lenac.bmp --output "$regionGrowing/lenac_region_growing_15_15_130_2.bmp" --regionGrowing 15 15 130 2

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenac.bmp --output "$regionGrowing/lenac_region_growing_320_450_100_2.bmp" --regionGrowing 320 450 100 2

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilc.bmp --output "$regionGrowing/mandrilc_region_growing_200_250_85_2.bmp" --regionGrowing 200 250 85 2

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilc.bmp --output "$regionGrowing/mandrilc_region_growing_250_250_110_2.bmp" --regionGrowing 250 250 110 2