#pragma once
#include <Core.h>
#include <Preloader.h>
#include <Items.h>
#include <Connectables.h>

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