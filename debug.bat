@echo off
echo building fish factory debug

rmdir /s /q "build/Assets"

cd "build"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang-cl -DCMAKE_C_FLAGS="-m64 -fsanitize=undefined -ferror-limit=0" ..
ninja
if errorlevel 1 (
  exit /b 1
)

robocopy "../modules/dll/win64/" "../build/" "SDL3.dll" /e /NFL /NDL /NJH /NJS /nc /ns /np
robocopy "../modules/dll/win64/" "../build/" "SDL3_ttf.dll" /e /NFL /NDL /NJH /NJS /nc /ns /np
robocopy "../modules/neutral" "../build" /e /NFL /NDL /NJH /NJS /nc /ns /np

echo build complete