#pragma once
extern "C" {
	#include <core.h>
}
#include <preloader.h>
#include <items.h>
#include <connectables.h>
#include <clib.hpp>

void Preclear_Temporaries();
bool Save_Data(int Slot);
bool Load_Data(int Slot);
bool Update_Metadata();
void Get_Filesizes();
void Clear_File(std::string Path);
bool Save_Settings();
void Load_Settings();
void Clear_Settings();
void Recalibrate_Settings();
void Reload_All();