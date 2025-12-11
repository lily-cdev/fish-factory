#pragma once
#include <Core.h>
#include <Preloader.h>
#include <Items.h>
#include <Connectables.h>
#include <Data_Handler.h>

void Clear_Grid(int Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], int Placeholder);
void Clear_Vector_Grid(std::vector<double> Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], std::vector<double> Placeholder);
void Update_Grid();
void Build_Grid(int Item);
void Restore_Cache();
bool Destroy_Grid();
void Update_Machines();
void Recast_Machines();
std::vector<double> Get_Grid_Data(std::vector<double> Grid[LDE_GRIDSIZE][LDE_GRIDSIZE]);
int Get_Simple_Grid_Tile(int Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], int Neutral);
void Reset_Statistics();