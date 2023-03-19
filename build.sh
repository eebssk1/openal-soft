#!/bin/sh

curl -L "https://github.com/eebssk1/mingw-gcc-build/releases/download/67de7744/mingw-gcc.tgz" | tar -zxf -
export PATH=$PWD/mingw-gcc/i686-w64-mingw32/bin:$PWD/mingw-gcc/x86_64-w64-mingw32/bin:$PATH

export SDIR=$PWD

if [ "x$(which ccache)" != "x" ]
then
export CCACHE=true
fi

buildthis () {
rm -rf build
mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$SDIR/tc.txt -DALSOFT_BUILD_ROUTER=ON -DALSOFT_REQUIRE_WINMM=ON -DALSOFT_REQUIRE_DSOUND=ON -DALSOFT_REQUIRE_WASAPI=ON -DALSOFT_STATIC_LIBGCC=ON -DALSOFT_STATIC_STDCXX=ON -DALSOFT_STATIC_WINPTHREAD=ON -DHOST=$1
cmake --build . -j 3 --verbose
cmake --install . --strip
RES=$?
if [ $RES != 0 ]
then
exit $RES
fi
cd ..
}

buildthis i686-w64-mingw32
buildthis x86_64-w64-mingw32

tar -zcf openalsoft.tgz -C out .
