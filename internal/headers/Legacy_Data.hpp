#pragma once
extern "C" {
	#include <core.h>
	#include <prepping.h>
	#include <data.h>
}
#include <Legacy_Preloader.hpp>
#include <Legacy_Items.hpp>
#include <Legacy_Connectables.hpp>
#include <clib.hpp>

bool Update_Metadata();
void Clear_File(std::string Path);
bool Save_Settings();
void Load_Settings();
void Clear_Settings();
void Recalibrate_Settings();
void Reload_All();