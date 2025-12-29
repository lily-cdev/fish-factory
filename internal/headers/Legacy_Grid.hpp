#pragma once
extern "C" {
	#include <core.h>
	#include <prepping.h>
	#include <transitions.h>
	#include <grid.h>
}
#include <Legacy_Preloader.hpp>
#include <Legacy_Items.hpp>
#include <Legacy_Connectables.hpp>
#include <Legacy_Data.hpp>

void Update_Grid();
void Build_Grid();
void Restore_Cache();
bool Destroy_Grid();
void Update_Machines();
void Recast_Machines();
int Get_Simple_Grid_Tile(int Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], int Neutral);
void Reset_Statistics();