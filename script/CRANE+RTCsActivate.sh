#!/bin/sh

export HOST="localhost"

echo ""
echo "CRANE+コンポーネント群をActivateします。"
echo ""

rtact $HOST/CraneplusRTC0.rtc
rtact $HOST/ManipulatorControlSample0.rtc
