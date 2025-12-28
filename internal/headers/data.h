#pragma once
#include <core.h>
#include <prepping.h>

void Get_Filesizes();
void Preclear_Temporaries();
void Render_Loadscreen();
bool Save_Data(int Slot);
bool Load_Data(int Slot);
bool Load_Text();
void Free_Text();