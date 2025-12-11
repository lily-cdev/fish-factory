#pragma once
#include <Core.h>
#include <Preloader.h>
#include <Items.h>
#include <Grid_Handler.h>
#include <Data_Handler.h>

void Render_Blueprint(int Size_X, int Size_Y);
void Render_Game_UI();
void Render_Saveloader();
void Render_Prompts();
void Render_Slider(std::vector<std::string> Labels, int Engagement, int Nodes, int Selection, int &Position,
	int X, int Y, int Width, SDL_Color Primary, SDL_Color Secondary, bool Text_Visible);
void Drain_Query();
void Render_Toolbar();
void Verify_Settings();
void Render_Tile_Prompts();
void Render_Interaction();
void Render_Effects();
void Find_Effect();
void Cache_Blueprint();
void Cache_Price();