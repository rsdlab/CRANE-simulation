#!/bin/sh

export HOST="localhost"

echo "CRANE+実機用RTCを接続します。"

#コンポーネント接続
rtcon $HOST/RT_CRANE_RTC0.rtc:ManipulatorCommonInterface_Common  $HOST/ManipulatorControlSample0.rtc:ManipulatorCommonInterface_Common
rtcon $HOST/RT_CRANE_RTC0.rtc:ManipulatorCommonInterface_Middle  $HOST/ManipulatorControlSample0.rtc:ManipulatorCommonInterface_Middle
