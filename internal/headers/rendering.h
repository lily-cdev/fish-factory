#pragma once
#include <core.h>
#include <prepping.h>

typedef struct {
	int Type;
	float Delta;
	float Max;
	Point Pos;
} Particle;

void Render_Grid();
void Render_Ocean();
void Render_Pyramid();
void Process_Supply(Texture_Supply* Supply, const char* Replacement, Font_Index Font, const SDL_Color Color, Point Pos);
void Free_Supplies();
void Push_Particle(const int Type, const Point Pos, const Point Subpos);
void Wipe_Tile(const Point Pos);
void Render_Particles(const Point Pos);
void Wipe_Grid();
void Init_Grid();
void Render_Lighting();
void Adjust_Audio();