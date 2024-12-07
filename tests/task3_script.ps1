# task3_script.ps1

Write-Output "Running ImageProcessing Task3"
$path_to_exe = "../build"
$output = "../output/task_3"
if (-Not (Test-Path -Path $output)) {
    New-Item -ItemType Directory -Path $output
}

Write-Output "Running Erosion"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_erosion3.bmp" --erosion 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_erosion3.bmp" --erosion 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_erosion4.bmp" --erosion 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_erosion4.bmp" --erosion 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_erosion6.bmp" --erosion 6

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_erosion6.bmp" --erosion 6

Write-Output "Running Dilation"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_dilation3.bmp" --dilation 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_dilation3.bmp" --dilation 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_dilation4.bmp" --dilation 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_dilation4.bmp" --dilation 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_dilation6.bmp" --dilation 6

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_dilation6.bmp" --dilation 6

Write-Output "Running Opening"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_opening3.bmp" --opening 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_opening3.bmp" --opening 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_opening4.bmp" --opening 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_opening4.bmp" --opening 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_opening6.bmp" --opening 6

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_opening6.bmp" --opening 6

Write-Output "Running Closing"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_closing3.bmp" --closing 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_closing3.bmp" --closing 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_closing4.bmp" --closing 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_closing4.bmp" --closing 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_closing6.bmp" --closing 6

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_closing6.bmp" --closing 6

Write-Output "Running HTM"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_htm_11left.bmp" --HTM 11 "left"

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_htm_11left.bmp" --HTM 11 "left"

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_htm_11right.bmp" --HTM 11 "right"

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_htm_11right.bmp" --HTM 11 "right"

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_htm_12bottomleft.bmp" --HTM 12 "bottom-left"

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_htm_12bottomleft.bmp" --HTM 12 "bottom-left"

Write-Output "Running M7"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_m7_3.bmp" --M7 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_m7_3.bmp" --M7 3

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_m7_4.bmp" --M7 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_m7_4.bmp" --M7 4

& "$path_to_exe/ImageProcessing.exe" --input ../images/lenabw.bmp --output "$output/lenabw_m7_6.bmp" --M7 6

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilbw.bmp --output "$output/mandrilbw_m7_6.bmp" --M7 6

Write-Output "Running region growing"
& "$path_to_exe/ImageProcessing.exe" --input ../images/lenac.bmp --output "$output/lenac_region_growing_100_100_100.bmp" --regionGrowing 100 100 100

& "$path_to_exe/ImageProcessing.exe" --input ../images/mandrilc.bmp --output "$output/mandrilc_region_growing_100_100_100.bmp" --regionGrowing 100 100 100

