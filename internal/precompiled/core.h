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
void Save_BMP(const char* Path, SDL_Surface* Carrier);