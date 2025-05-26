param (
	[string]$installPrefix = "C:\Program Files\WeaNet"
	)
New-Item -ItemType Directory -Force -Path "build"
Set-Location -Path "build"

cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$installPrefix -B build -S . -DBUILD_EXAMPLES=OFF
cmake .. --build build --target uninstall
