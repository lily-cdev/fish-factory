#pragma once
#include <core.h>
#include <prepping.h>
#include <buttons.h>
#include <grid.h>
#include <rendering.h>
#include <tutorials.h>

extern char Errors[ktn_errors][32];

void Render_Toolbar();
void Verify_Settings();
void Render_Tile_Prompts();
void Render_Interaction();
void Render_Effects();
void Cache_Blueprint();
void Cache_Price();
void Render_Daily_Report(Point Pos);
void Render_Help(Point Pos);
void Render_Shop(Point Pos);
void Render_Catalog(Point Pos);
void Render_Genetics(Point Pos);
void Render_Perks(Point Pos);
void Render_Time(Point Pos);
void Render_Slider(int ID, int Engagement, int Nodes, Point Pos, int Width, SDL_Color Primary, SDL_Color Secondary, bool Text_Visible);
void Render_Application();
void Render_Main();
void Render_Loader();
void Render_Settings();
void Render_Changelog();
void Render_Credits();
void Render_Backing();
void Render_Sidebuttons(Texture2_Array* Buttons, Rect2_Array* Hitboxes, UI_Link* Links);
void Print_Error(int Input);
void Print_Fatal_Error(int Input);
void Print_Response(const char* Response);
void Print_JSON();
void Print_Input();
void Render_Necessities(char* Machine, char* Prefix);
void Tick_Input(int Target, bool Slider);
void Return_Command(const int Type, const int Length, const char Parameters[Length][ktn_param_max]);
void Process_Commands();
void Render_Blueprint(int Size_X, int Size_Y);
void Render_Game_UI();
void Render_Saveloader();
void Render_Prompts();
void Drain_Query();
void Render_MSP_Controller(Point Pos);
void Render_T_Tower(Point Pos);
void Render_S_Dock(Point Pos);
void Render_H_Exchanger(Point Pos);
void Render_M_Generator(Point Pos);
void Render_F_Generator(Point Pos);
void Render_MT_Input(Point Pos);
void Render_P_Generator(Point Pos);
void Render_Hotbar();