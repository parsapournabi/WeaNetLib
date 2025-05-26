param (
	[string]$installPrefix = "C:\Program Files\WeaNet"
	)
$buildDir = "build"
if (-Not (Test-Path $buildDir)) {
        mkdir build
}
#Set-Location $buildDir

cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_MAKE_PROGRAM="C:/Qt/Tools/mingw1310_64/bin/mingw32-make.exe" -DCMAKE_CXX_COMPILER="C:/Qt/Tools/mingw1310_64/bin/g++.exe" -DCMAKE_INSTALL_PREFIX=$installPrefix -DBUILD_EXAMPLE=OFF
cmake --build build
cmake --install build

Write-Host "Installation completed to $installPrefix"
