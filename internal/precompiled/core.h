#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#define LDE_BORDERWIDTH 4
#define LDE_BUFFERSIZE 360
#define LDE_BUTTONS 43
#define LDE_CATEGORIES 8
#define LDE_CHANNELS 1
#define LDE_DOCKCAPACITY 750.0
#define LDE_GRIDSIZE 48
#define LDE_HXCAPACITY 1200
#define LDE_HXEFFICIENCY 1200
#define LDE_INVALID -1
#define LDE_ITEMCOUNT 11
#define LDE_LARGECAP 150
#define LDE_MACHINES 40
#define LDE_REINFORCEDCAP 30
#define LDE_ROOMTEMP 65
#define LDE_SLIDERS 14
#define LDE_STATICRATE 15
#define LDE_SUBCATEGORIES 6
#define LDE_SUFFIXES 5
#define LDE_TILESIZE 40
#define LDE_TTSLIDES 2
#define LDE_TURBINECOEFFICIENT 0.15
#define LDE_VESSELSPEED 4
#define LDE_WASTETOX 200
#define LDE_WATERBOILPOINT 211.3

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <corecrt_math_defines.h>
#include <enums.h>
#include <types.h>
#include <macros.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

extern SDL_ScaleMode Scaling_Quality;

SDL_Surface* Load_BMP(const char* Path);
SDL_Texture* SDL_GenerateTexture(SDL_Renderer* Renderer, SDL_PixelFormat Format,
    SDL_TextureAccess Access, int Width, int Height);
SDL_Texture* SDL_GenerateTextureFromSurface(SDL_Renderer* Renderer, SDL_Surface* Surface);
SDL_Texture* IMG_GenerateTexture(SDL_Renderer* Renderer, const char* Path);
int sgn(long double Input);
long double sqr_d(long double Input);
int sqr_i(int Input);
bool evn_i(int Input);