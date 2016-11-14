#!/bin/sh

export HOST="localhost"

echo ""
echo "simulationRTCを接続します。"
echo ""

#コンポーネント接続
rtcon $HOST/ChoreonoidCRANEControllerRTC0.rtc:ManipulatorCommonInterface_Common  $HOST/ManipulatorControlSample0.rtc:ManipulatorCommonInterface_Common
rtcon $HOST/ChoreonoidCRANEControllerRTC0.rtc:ManipulatorCommonInterface_Middle  $HOST/ManipulatorControlSample0.rtc:ManipulatorCommonInterface_Middle

rtcon $HOST/ChoreonoidCRANEControllerRTC0.rtc:angle  $HOST/CRANE.rtc:JointValue
rtcon $HOST/ChoreonoidCRANEControllerRTC0.rtc:torque  $HOST/CRANE.rtc:JointTorque
