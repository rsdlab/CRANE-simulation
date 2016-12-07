#!/bin/sh

COM="gnome-terminal -e"

echo ""
echo "CraneplusRTCとManipulatorControlSampleを実行します。"
echo "CRANE+とパソコンを接続し，CRANE+の電源をつけてください。"
echo ""

#コンポーネント実行
$COM "../CraneplusRTC/build/src/CraneplusRTCComp -f ../CraneplusRTC/rtc.conf" -t CraneplusRTC
$COM "../ManipulatorControlSample/build/src/ManipulatorControlSampleComp -f ../ManipulatorControlSample/rtc.conf" -t ManipulatorControlSample
