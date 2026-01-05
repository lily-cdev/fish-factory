#pragma once
extern "C" {
	#include <core.h>
	#include <prepping.h>
	#include <data.h>
	#include <ui.h>
	#include <grid.h>
	#include <items.h>
}
#include <Legacy_Preloader.hpp>

extern std::vector<std::string> Errors;

void Render_Blueprint(int Size_X, int Size_Y);
void Render_Game_UI();
void Render_Saveloader();
void Render_Prompts();
void Render_Slider(char Labels[256][32], int Engagement, int Nodes, int Selection, int &Position,
	int X, int Y, int Width, SDL_Color Primary, SDL_Color Secondary, bool Text_Visible);
void Drain_Query();
void Render_Backing();
void Render_Sidebuttons(const Texture2_Array &Buttons, const Rect2_Array &Hitboxes);
void Print_Error(int Input);
void Print_Fatal_Error(int Input);
void Process_Exit();
void Print_Response(std::string Response);
void Print_JSON(std::vector<std::string> Input);
void Print_Input();
void Purge_Excess();
void Forward_Essentials(int Buttons, int Sliders);
void Backward_Essentials();
void Render_Necessities(std::string Machine, std::string Prefix);
void Tick_Input(int Target, bool Slider = false);
std::string Return_Command(int Type, std::vector<std::string> Parameters);
void Process_Commands(std::vector<int> Types, std::vector<std::vector<std::string>> Parameters);
void Render_MSP_Controller(int X, int Y);
void Render_T_Tower(int X, int Y);
void Render_S_Dock(int X, int Y);
void Render_H_Exchanger(int X, int Y);
void Render_M_Generator(int X, int Y);
void Render_F_Generator(int X, int Y);
void Render_Catalog(int X, int Y);
void Render_MT_Input(int X, int Y);