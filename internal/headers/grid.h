#pragma once
#include <core.h>
#include <prepping.h>
#include <data.h>
#include <items.h>
#include <connectables.h>
#include <transitions.h>
#include <rendering.h>

void Restore_Cache();
void Destroy_Clearance(int X, int Y, int Width, int Height);
void Update_Grid();
void Build_Grid();
bool Destroy_Grid();
void Update_Machines();
void Recast_Machines();
void Process_Movement();
void Find_Effect();
Point Find_Linked(int Identifier, int Parent_X, int Parent_Y);
int Get_Simple_Grid_Tile(int Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], int Neutral);
bool Place_Reinforced_Pipe(int X, int Y);
bool Place_Ram_Pump(int X, int Y);
bool Place_Incinerator(int X, int Y);
bool Place_RTG(int X, int Y);
bool Place_Decoration(int X, int Y);
bool Place_Submarine_Dock(int X, int Y);
void Cycle_Ram_Pump(const int X, const int Y, const int Rotation);
bool Place_Filtration_Plant(int X, int Y);
bool Place_Bio_Generator(int X, int Y);
bool Place_Spawning_Pool(int X, int Y);
bool Place_Distillery(int X, int Y);
bool Place_Algae_Bed(int X, int Y);
bool Place_Command_Platform(int X, int Y);
bool Place_Battery(int X, int Y);
bool Place_Spawning_Controller(int X, int Y);
bool Place_Spawning_Output(int X, int Y);
bool Place_Spawning_Input(int X, int Y);
bool Place_Electrolytic_Cell(int X, int Y);
bool Place_Fluid_Mixer(int X, int Y);
bool Place_Signal_Tower(int X, int Y);
bool Place_Flowerpot(int X, int Y);
bool Place_Ammunition_Shelf(int X, int Y);
bool Place_Cable_Node(int X, int Y);
bool Place_Geo_Well(int X, int Y);
bool Place_Large_Pipe(int X, int Y);
bool Place_Heat_Exchanger(int X, int Y);
bool Place_Petrified_Wood(int X, int Y);
bool Place_Basalt_Tile(int X, int Y);
bool Place_Silicone_Carpet(int X, int Y);
bool Place_Money_Generator(int X, int Y);
bool Place_Fluid_Generator(int X, int Y);
bool Place_RL_Intersection(int X, int Y);
bool Place_RL_Intersection(int X, int Y);
bool Place_Hazard_Strip(int X, int Y);
bool Place_Condenser_Input(int X, int Y);
bool Place_Condenser_Transferor(int X, int Y);
bool Place_Condenser_Heatsink(int X, int Y);
bool Place_Condenser_Output(int X, int Y);
bool Place_Turbine_Input(int X, int Y);
bool Place_Turbine_Impulse(int X, int Y);
bool Place_Turbine_Output(int X, int Y);
bool Place_Power_Generator(int X, int Y);
void Cycle_RTG(const int X, const int Y, const int Rotation);
void Cycle_Bio_Gen(const int X, const int Y, const int Rotation);
void Cycle_Geo_Well(const int X, const int Y, const int Rotation);
void Cycle_HX(const int X, const int Y, const int Rotation);
void Cycle_Turbine_Input(const int X, const int Y, const int Rotation);
void Cycle_Large_Pipe(const int X, const int Y, const int Rotation);
void Cycle_Intersection(const int X, const int Y, const int Rotation);
void Cycle_Distillery(const int X, const int Y, const int Rotation);
void Cycle_Electrolytic_Cell(const int X, const int Y, const int Rotation);
void Cycle_Fluid_Mixer(const int X, const int Y, const int Rotation);
void Cycle_Incinerator(const int X, const int Y, const int Rotation);
void Cycle_Signal_Tower(const int X, const int Y, const int Rotation);
void Cycle_Money_Generator(const int X, const int Y, const int Rotation);
void Cycle_Fluid_Generator(const int X, const int Y, const int Rotation);
void Cycle_Algae_Bed(const int X, const int Y, const int Rotation);
void Cycle_Power_Generator(const int X, const int Y, const int Rotation);