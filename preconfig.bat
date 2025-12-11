@echo off
cmake -S "./external/SDL3" -B "./modules/tmp"
cmake --build "./modules/tmp"