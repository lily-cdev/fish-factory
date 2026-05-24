#pragma once
#include <core.h>
#include <prepping.h>

typedef struct {
	int Type;
	bool Shuffling_Barred;
	bool Voiding_Excess;
	int Time;
	int Power;
	Item_Ptr Input_Items[16];
	float Input_Counts[16];
    int Inputs;
	Item_Ptr Output_Items[16];
	float Output_Counts[16];
    int Outputs;
	int ID;
	Machine_Ptr Machine;
} Recipe;

typedef struct {
	char Name[32];
	int Identifier;
	int Max_Growth;
	float Food_Consumption;
} Fish;

typedef struct {
	Item_Ptr Blank_Item;
	Recipe FP_Saltwater;
	Recipe FP_Biopaste;
	Recipe FM_Drillmud_1;
	Recipe FM_Drillmud_2;
	Recipe FM_Hydrogen_Chloride;
	Recipe FM_Hydrochloric_Acid;
	Recipe D_Water;
	Recipe EP_Water;
	Recipe EP_Saltwater;
	Recipe EP_Salt;
} PRESET_IO_RECIPES;

typedef struct {
	Item_Ptr Blank_Item;
} PRESET_I_RECIPES;

typedef struct {
	Item_Ptr Blank_Item;
	Recipe RP_Saltwater;
	Recipe GB_Algae;
} PRESET_O_RECIPES;

typedef struct {
	Fish Milkfish;
	Fish Mojarra;
	Fish Menhaden;
} PRESET_FISH;

extern PRESET_FISH Preset_Fish;
extern Fish Fish_Catalog[ktn_fish];
extern char Growth_Phases[ktn_fish_phases][32];
extern char Plural_Growth_Phases[ktn_fish_phases][32];
extern int Growth_Weights[ktn_fish_phases];
extern Recipe* Recipes;
extern int Recipe_Ct;

void Prep_Items();
void Free_Items();
void Update_Item(Point Pos, int Identifier, int Temperature);
Item_Ptr Get_Item(const char* Index);
Item_Ptr Get_ID_Item(const int ID);
Item_Ptr Get_Fish_Item(int Identifier);
void Purge_Items();
float Calculate_Pressure(int Temperature, float Boiling_Point, float H_Vaporisation);
int Get_Phase(int Fish, int Progress);
void Get_Phase_Name(char* Buffer, int Length, int Fish, int Progress, int Count);
bool Process_O_Recipe(Recipe Chosen, Point Pos, Point* Outputs);
bool Process_IO_Recipe(Recipe Chosen, Point Pos, Point* Inputs, Point* Outputs);
bool Extend_Recipe(Recipe Chosen, Point Pos, Point* Outputs);