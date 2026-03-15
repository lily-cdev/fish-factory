#pragma once
#include <core.h>
#include <prepping.h>

typedef struct {
	int Type;
	float Delta;
	float Max;
	Point_f Pos;
} Particle;

void Render_Grid();
void Render_Ocean();
void Render_Pyramid();
void Process_Supply(Texture_Supply* Supply, const char* Replacement, TTF_Font* Font, const SDL_Color Color, int X, int Y);
void Free_Supplies();
void Push_Particle(const int Type, const Point Pos, const Point_f Subpos);
void Wipe_Tile(const Point Pos);
void Render_Particles(const Point Pos);
void Wipe_Grid();
void Init_Grid();