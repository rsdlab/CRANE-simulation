#!/bin/sh

#必要パッケージのインストール
sudo apt-get install freeglut3-dev libglew-dev python-dev libboost-devlibboost-regex-dev libboost-date-time-dev libboost-thread-dev libboost-system-dev libboost-iostreams-dev libboost-filesystem-dev libboost-program-options-dev libboost-python-dev libeigen3-dev libqt4-dev libping12-dev libjpeg-dev Libode-dev libyaml-dev

cd ../

#コレオノイドホームページからダウンロード
wget http://choreonoid.org/_downloads/choreonoid-1.5.0.zip
unzip choreonoid-1.5.0.zip 

#buildディレクトリ作成
cd choreonoid-1.5.0
mkdir build
cd build

#一部プラグインをONにしてcmake
cmake .. -DENABLE_CORBA=ON -DBUILD_CORBA_PLUGIN=ON -DBUILD_OPENRTM_PLUGIN=ON  -DBUILD_OPENRTM_SAMPLES=ON

#コレオノイドソースからビルド
make

cd ../../
rm -rf choreonoid-1.5.0.zip
