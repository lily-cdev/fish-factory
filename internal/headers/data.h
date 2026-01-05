#pragma once
#include <core.h>
#include <prepping.h>
#include <connectables.h>
#include <items.h>

void Get_Filesizes();
bool Save_Data(int Slot);
bool Load_Data(int Slot);
bool Load_Text();
void Free_Text();
bool Save_Settings();
void Load_Settings();
void Clear_Settings();
void Recalibrate_Settings();
void Reset_Statistics();
void Reload_All();