#!/bin/bash

# Build glogg for win32 using the cross-compiler

QTXDIR=$HOME/qt-x-win32
QTVERSION=5.12.8-32
BOOSTDIR=$QTXDIR/boost_1_50_0

make clean
if [ "$1" == "debug" ]; then
    echo "Building a debug version"
    qmake-qt5 glogg.pro -spec win32-x-g++ -r CONFIG+="debug win32 rtti no-dbus version_checker" BOOST_PATH=$BOOSTDIR
elif [ -z "$VERSION" ]; then
    echo "Building default version"
    qmake-qt5 glogg.pro -spec win32-x-g++ -r CONFIG+="release win32 rtti no-dbus version_checker" BOOST_PATH=$BOOSTDIR
else
    echo "Building version $VERSION"
    qmake-qt5 glogg.pro -spec win32-x-g++ -r CONFIG+="release win32 rtti no-dbus version_checker" BOOST_PATH=$BOOSTDIR VERSION="$VERSION"
fi
make -j3
cp $QTXDIR/$QTVERSION/lib/{Qt5Core,Qt5Gui,Qt5Network,Qt5Widgets}.dll release/
cp $QTXDIR/$QTVERSION/lib/{Qt5Core,Qt5Gui,Qt5Network,Qt5Widgets}.dll debug/
cp /usr/i686-w64-mingw32/lib/libwinpthread-1.dll release/
if [ -z "$VERSION" ]; then
    VERSION=`git describe`;
fi
echo Generating installer for glogg-$VERSION
wine $QTXDIR/NSIS/makensis -DVERSION=$VERSION -DARCH32 glogg.nsi
