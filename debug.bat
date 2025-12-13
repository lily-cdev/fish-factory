@echo off
echo building fish factory debug

rmdir /s /q "build/Assets"

cd "build"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="-m64 -ferror-limit=0" ..
ninja
if errorlevel 1 (
  exit /b 1
)

robocopy "../modules/dll/win32/*.dll" "../build" /e /NFL /NDL /NJH /NJS /nc /ns /np
robocopy "../modules/neutral" "../build" /e /NFL /NDL /NJH /NJS /nc /ns /np

Fish_Factory.exe

echo build complete