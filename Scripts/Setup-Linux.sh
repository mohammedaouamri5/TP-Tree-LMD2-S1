#!/bin/bash

pushd ..
Vendor/Binaries/Premake/Linux/premake5 --cc=gcc  gmake2
popd
