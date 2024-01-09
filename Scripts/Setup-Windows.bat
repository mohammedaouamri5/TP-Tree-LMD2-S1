@echo off

pushd ..
Vendor\Binaries\Premake\Windows\premake5.exe  --cc=mingw gmake2
Vendor\Binaries\Premake\Windows\premake5.exe  vs2022
popd
pause