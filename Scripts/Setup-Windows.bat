@echo off

pushd ..
Vendor\Binaries\Premake\Windows\premake5.exe  --cc=gcc  gmake 
Vendor\Binaries\Premake\Windows\premake5.exe  vs2022
popd
pause