@echo off
echo building fish factory release x86

rmdir /s /q "build"
mkdir "build"

cd "build"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ^
  -DCMAKE_CXX_COMPILER=clang++.exe ^
  -DCMAKE_CXX_FLAGS="-m32 -O3" ^
  ..
ninja

robocopy "../modules/neutral" "../build" /e /NFL /NDL /NJH /NJS /nc /ns /np

echo build complete