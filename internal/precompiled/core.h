#pragma once
#include <defines.h>
#include <includes.h>
#include <types.h>
#include <enums.h>
#include <macros.h>

extern SDL_ScaleMode Scaling_Quality;
extern jmp_buf Exception;
extern int Exception_Value;
extern char Exception_Text[128];

SDL_Surface* Load_BMP(const char* Path);
SDL_Texture* SDL_GenerateTexture(SDL_Renderer* Renderer, int Width, int Height);
SDL_Texture* SDL_GenerateTextureFromSurface(SDL_Renderer* Renderer, SDL_Surface* Surface);
SDL_Texture* IMG_GenerateTexture(SDL_Renderer* Renderer, const char* Path);
int sgn(float Input);
bool evn_i(int Input);