#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#define LDE_BORDERWIDTH 4
#define LDE_BUFFERSIZE 360
#define LDE_BUTTONS 49
#define LDE_CAPTIONS 6
#define LDE_CATEGORIES 8
#define LDE_CHANNELS 1
#define LDE_CMDMAX 16
#define LDE_DAYS 7
#define LDE_DOCKCAPACITY 750.0
#define LDE_EFFECTS 2
#define LDE_ERRORS 13
#define LDE_FISH 3
#define LDE_FISHPHASES 6
#define LDE_GRIDSIZE 48
#define LDE_HXCAPACITY 1200
#define LDE_HXEFFICIENCY 1200
#define LDE_INVALID -1
#define LDE_ITEMS 21
#define LDE_JSONMAX 8
#define LDE_KEYBINDS 14
#define LDE_LARGECAP 150
#define LDE_LOGMAX 11
#define LDE_LOGS 3
#define LDE_MACHINES 40
#define LDE_QUIRKS 4
#define LDE_RECIPETYPES 3
#define LDE_REINFORCEDCAP 30
#define LDE_ROOMTEMP 65
#define LDE_SAVEFILES 4
#define LDE_SLIDERS 14
#define LDE_STATICRATE 15
#define LDE_SUBCATEGORIES 6
#define LDE_SUFFIXES 5
#define LDE_SUPPORTEDRESOLUTIONS 6
#define LDE_TERMINATOR -105
#define LDE_TEXTUREPERSISTENCE 16
#define LDE_TILESIZE 40
#define LDE_TURBINECOEFFICIENT 0.15
#define LDE_VALVE300LENGTH 12
#define LDE_VESSELSPEED 4
#define LDE_WASTETOX 200
#define LDE_WATERBOILPOINT 211.3

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <corecrt_math_defines.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

#include <types.h>
#include <enums.h>
#include <macros.h>

extern SDL_ScaleMode Scaling_Quality;

SDL_Surface* Load_BMP(const char* Path);
SDL_Texture* SDL_GenerateTexture(SDL_Renderer* Renderer, int Width, int Height);
SDL_Texture* SDL_GenerateTextureFromSurface(SDL_Renderer* Renderer, SDL_Surface* Surface);
SDL_Texture* IMG_GenerateTexture(SDL_Renderer* Renderer, const char* Path);
int sgn(float Input);
float sqr_f(float Input);
int sqr_i(int Input);
bool evn_i(int Input);