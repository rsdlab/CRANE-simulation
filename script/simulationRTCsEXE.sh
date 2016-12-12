#!/bin/sh

COM="gnome-terminal -e"

echo ""
echo "ChoreonoidCRANEControllerRTCとManipulatorControlSampleを実行します。"
echo "Choreonoidでプロジェクトファイル[CRANEsimulation]を読み込んでください。"
echo ""

#コンポーネント実行
$COM "../ChoreonoidCRANEControllerRTC/build/src/ChoreonoidCRANEControllerRTCComp -f ../ChoreonoidCRANEControllerRTC/rtc.conf" -t ChoreonoidCRANEControllerRTC
$COM "../ManipulatorControlSample/build/src/ManipulatorControlSampleComp -f ../ManipulatorControlSample/rtc.conf" -t ManipulatorControlSample
