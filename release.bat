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
  -DCMAKE_C_COMPILER=clang ^
  -DCMAKE_C_FLAGS="-m64 -O3 -funroll-loops" ^
  -DCMAKE_CXX_COMPILER=clang++ ^
  -DCMAKE_CXX_FLAGS="-m64 -O3 -funroll-loops" ^
  ../..
ninja

cd ..

cd "win32"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ^
  -DCMAKE_C_COMPILER=clang ^
  -DCMAKE_C_FLAGS="-m32 -O3 -funroll-loops" ^
  -DCMAKE_CXX_COMPILER=clang++ ^
  -DCMAKE_CXX_FLAGS="-m32 -O3 -funroll-loops" ^
  ../..
ninja

robocopy "../../modules" "../../build/win64" /e /NFL /NDL /NJH /NJS /nc /ns /np
robocopy "../../modules" "../../build/win32" /e /NFL /NDL /NJH /NJS /nc /ns /np

echo build complete