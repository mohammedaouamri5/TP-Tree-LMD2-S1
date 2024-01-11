@echo off

pushd ..
Vendor\Binaries\Premake\Windows\premake5.exe  --cc=gcc  gmake2
popd
pause