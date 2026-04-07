@echo off
echo building fish factory debug

rmdir /s /q "build/assets"

cd "build"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl ^
	-DCMAKE_C_FLAGS="-m64 -fsanitize=undefined -ferror-limit=0" ^
	-DCMAKE_CXX_FLAGS="-m64 -fsanitize=undefined -ferror-limit=0" ..
ninja
if errorlevel 1 (
	exit /b 1
)

robocopy "../modules" "../build" /e /NFL /NDL /NJH /NJS /nc /ns /np

echo build complete