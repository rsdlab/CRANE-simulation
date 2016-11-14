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

#RT_CRANE_RTCのbuild
cd ../../RT_CRANE_RTC/
mkdir build
cd build
cmake ..
make

#元のディレクトリへ
cd ../../script



