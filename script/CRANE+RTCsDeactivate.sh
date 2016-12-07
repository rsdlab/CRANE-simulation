#!/bin/sh

export HOST="localhost"

echo ""
echo "CRANE+コンポーネント群をDeactivateします。"
echo "終了しない場合ManipulatorControlSampleのコマンド「9:終了」を選択してください"
echo ""

rtdeact $HOST/CraneplusRTC0.rtc
rtdeact $HOST/ManipulatorControlSample0.rtc
