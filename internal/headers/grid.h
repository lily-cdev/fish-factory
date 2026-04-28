#pragma once
#include <core.h>
#include <prepping.h>
#include <data.h>
#include <items.h>
#include <connectables.h>
#include <transitions.h>
#include <rendering.h>

void Restore_Cache();
void Destroy_Clearance(Point Pos, int Width, int Height);
void Update_Grid();
void Build_Grid();
bool Destroy_Grid();
void Update_Machines();
void Recast_Machines();
void Process_Movement();
void Find_Effect();
Point Find_Linked(const char* Identifier, Point Parent);
int Get_Simple_Grid_Tile(int Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], int Neutral);
bool Place_Reinforced_Pipe(Point Pos);
bool Place_Ram_Pump(Point Pos);
bool Place_Incinerator(Point Pos);
bool Place_Submarine_Dock(Point Pos);
void Cycle_Ram_Pump(Point Pos, const int Rotation);
bool Place_Filtration_Plant(Point Pos);
bool Place_Bio_Generator(Point Pos);
bool Place_Spawning_Pool(Point Pos);
bool Place_Distillery(Point Pos);
bool Place_Algae_Bed(Point Pos);
bool Place_Command_Platform(Point Pos);
bool Place_Battery(Point Pos);
bool Place_Spawning_Controller(Point Pos);
bool Place_Spawning_Output(Point Pos);
bool Place_Spawning_Input(Point Pos);
bool Place_Electrolytic_Cell(Point Pos);
bool Place_Fluid_Mixer(Point Pos);
bool Place_Signal_Tower(Point Pos);
bool Place_Geo_Well(Point Pos);
bool Place_Large_Pipe(Point Pos);
bool Place_Heat_Exchanger(Point Pos);
bool Place_Money_Generator(Point Pos);
bool Place_Fluid_Generator(Point Pos);
bool Place_RL_Intersection(Point Pos);
bool Place_RL_Intersection(Point Pos);
bool Place_Condenser_Input(Point Pos);
bool Place_Condenser_Transferor(Point Pos);
bool Place_Condenser_Heatsink(Point Pos);
bool Place_Condenser_Output(Point Pos);
bool Place_Turbine_Input(Point Pos);
bool Place_Turbine_Impulse(Point Pos);
bool Place_Turbine_Output(Point Pos);
bool Place_Power_Generator(Point Pos);
void Cycle_RTG(Point Pos, const int Rotation);
void Cycle_Bio_Gen(Point Pos, const int Rotation);
void Cycle_Geo_Well(Point Pos, const int Rotation);
void Cycle_HX(Point Pos, const int Rotation);
void Cycle_Turbine_Input(Point Pos, const int Rotation);
void Cycle_Large_Pipe(Point Pos, const int Rotation);
void Cycle_Intersection(Point Pos, const int Rotation);
void Cycle_Distillery(Point Pos, const int Rotation);
void Cycle_Electrolytic_Cell(Point Pos, const int Rotation);
void Cycle_Fluid_Mixer(Point Pos, const int Rotation);
void Cycle_Incinerator(Point Pos, const int Rotation);
void Cycle_Signal_Tower(Point Pos, const int Rotation);
void Cycle_Money_Generator(Point Pos, const int Rotation);
void Cycle_Fluid_Generator(Point Pos, const int Rotation);
void Cycle_Algae_Bed(Point Pos, const int Rotation);
void Cycle_Power_Generator(Point Pos, const int Rotation);