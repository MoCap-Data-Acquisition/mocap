#!/bin/bash
set -ev

# Install other dependencies
pushd dependencies

# Install CMake 3.2.2
wget http://www.cmake.org/files/v3.2/cmake-3.2.2-Linux-x86_64.tar.gz --no-check-certificate

tar xf cmake-3.2.2-Linux-x86_64.tar.gz

# Install Qt 5.4.1
wget http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_54/qt.54.gcc_64/5.4.1-0qt5_essentials.7z
wget http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_54/qt.54.gcc_64/5.4.1-0qt5_essentials.7z.sha1
wget http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_54/qt.54.gcc_64/5.4.1-0icu_53_1_ubuntu_11_10_64.7z
wget http://download.qt.io/online/qtsdkrepository/linux_x64/desktop/qt5_54/qt.54.gcc_64/5.4.1-0icu_53_1_ubuntu_11_10_64.7z.sha1

7z x 5.4.1-0qt5_essentials.7z > /dev/null
7z x 5.4.1-0icu_53_1_ubuntu_11_10_64.7z > /dev/null

# Install VLC-Qt prepared for examples
mkdir vlc-qt
pushd vlc-qt
curl -LO "https://googledrive.com/host/0B7I7Zg8w-HxRfmxSMmdhM3dTMGJnSklRX1c4ZkxmekJkcFplYnRLTU80R3Znd1VITkNueGs/vlc-qt_linux_examples.tar.bz2"
tar xf vlc-qt_linux_examples.tar.bz2
popd

export CC="gcc-4.8"
export CXX="g++-4.8"
export PATH=$PWD/vlc-qt/bin/:$PWD/cmake-3.2.2-Linux-x86_64/bin/:$PWD/5.4/gcc_64/bin/:$PATH

popd
