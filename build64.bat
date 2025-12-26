@echo off
echo building fish factory release x64

rmdir /s /q "build"
mkdir "build"
cd "build"
rmdir /s /q "win32"
mkdir "win32"
rmdir /s /q "win64"
mkdir "win64"

cd "win64"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ^
  -DCMAKE_CXX_COMPILER=clang++.exe ^
  -DCMAKE_CXX_FLAGS="-m64 -O3 -funroll-loops" ^
  ...
ninja

robocopy ".../modules/neutral" ".../build/win64" /e /NFL /NDL /NJH /NJS /nc /ns /np

echo build complete