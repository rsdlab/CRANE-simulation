#!/bin/sh

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
