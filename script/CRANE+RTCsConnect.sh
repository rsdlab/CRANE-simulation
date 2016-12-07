#!/bin/sh

export HOST="localhost"

echo ""
echo "CRANE+実機用RTCを接続します。"
echo ""

#コンポーネント接続
rtcon $HOST/CraneplusRTC0.rtc:ManipulatorCommonInterface_Common  $HOST/ManipulatorControlSample0.rtc:ManipulatorCommonInterface_Common
rtcon $HOST/CraneplusRTC0.rtc:ManipulatorCommonInterface_Middle  $HOST/ManipulatorControlSample0.rtc:ManipulatorCommonInterface_Middle
