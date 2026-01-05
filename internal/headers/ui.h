#pragma once
#include <core.h>
#include <prepping.h>
#include <grid.h>

void Render_Toolbar();
void Verify_Settings();
void Render_Tile_Prompts();
void Render_Interaction();
void Render_Effects();
void Find_Effect();
void Cache_Blueprint();
void Cache_Price();
void Render_Daily_Report(int X, int Y);
void Render_Help(int X, int Y);
void Render_Shop(int X, int Y);
void Render_Slider(char Labels[256][32], int Engagement, int Nodes, int Selection, int* Position,
	int X, int Y, int Width, SDL_Color Primary, SDL_Color Secondary, bool Text_Visible);