#!/bin/sh

#ManipulatorControlSampleのbuild
cd ../ManipulatorControlSample/
mkdir build
cd build
cmake ..
make

#ChoreonoidCRANEControllerRTCのbuild
cd ../../ChoreonoidCRANEControllerRTC/
mkdir build
cd build
cmake ..
make

#CraneplusRTCのbuild
cd ../../CraneplusRTC/
mkdir build
cd build
cmake ..
make

#元のディレクトリへ
cd ../../script



