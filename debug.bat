#!/usr/bin/env bash
echo building fish factory debug

rm -rf "build/assets"

cd "build"
cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
	-DCMAKE_C_FLAGS="-m64 -O0 -ferror-limit=0" \
	-DCMAKE_CXX_FLAGS="-m64 -O0 -ferror-limit=0" ..
ninja
if [ $? -ne 0 ]; then
	exit 1
fi

rsync -aq "../modules/" "../build"
echo build complete