#pragma once
#include <Core.h>
#include <Preloader.h>

extern std::vector<std::string> Errors;

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