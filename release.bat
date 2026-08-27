#!/usr/bin/env bash
echo building fish factory release x64

rm -rf "build"
mkdir "build"
cd "build"
rm -rf "linux32"
mkdir "linux32"
rm -rf "linux64"
mkdir "linux64"
rm -rf "win32"
mkdir "win32"
rm -rf "win64"
mkdir "win64"

cd "linux32"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_C_FLAGS="-m32 -O3 -funroll-loops" \
	-DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="-m32 -O3 -funroll-loops" ../..
ninja

cd ..

cd "linux64"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_C_FLAGS="-m64 -O3 -funroll-loops" \
	-DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="-m64 -O3 -funroll-loops" ../..
ninja

cd ..

cd "win32"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_RC_COMPILER=i686-w64-mingw32-windres \
	-DCMAKE_C_COMPILER=clang -DCMAKE_C_FLAGS="--target=i686-w64-windows-gnu -m32 -O3 -funroll-loops" \
	-DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="--target=i686-w64-windows-gnu -m32 -O3 -funroll-loops" ../..
ninja

cd ..

cd "win64"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_RC_COMPILER=x86_64-w64-mingw32-windres \
	-DCMAKE_C_COMPILER=clang -DCMAKE_C_FLAGS="--target=x86_64-w64-windows-gnu -m64 -O3 -funroll-loops" \
	-DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="--target=x86_64-w64-windows-gnu -m64 -O3 -funroll-loops" ../..
ninja

cd ..

cp -r "../modules/." "../build/linux32"
cp -r "../modules/." "../build/linux64"
cp -r "../modules/." "../build/win32"
cp -r "../modules/." "../build/win64"

echo build complete