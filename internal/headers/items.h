#pragma once
#include <core.h>
#include <prepping.h>

typedef struct {
	int Identifier;
	int Hazard;
	int Value;
	char Display_Name[32];
	float Sale_Value;
	float Toxicity;
	float Temperature;
	float Chemical_Energy;
	float Boiling_Point;
	float Vaporisation_Enthalpy;
} Item_Stack;

typedef struct {
	bool Shuffling_Barred;
	bool Voiding_Excess;
	int Time;
	int Power;
	Item_Stack Input_Items[16];
	float Input_Counts[16];
    int Inputs;
	Item_Stack Output_Items[16];
	float Output_Counts[16];
    int Outputs;
	int ID;
} Recipe;

typedef struct {
	char Name[32];
	int Identifier;
	int Max_Growth;
	float Food_Consumption;
} Fish;

typedef struct {
	int Identifier;
	char Display_Name[32];
	Item_Stack Contents[64];
    int Length;
} Item_Category;

typedef struct {
	Item_Stack Raw_Saltwater;
	Item_Stack Saltwater;
	Item_Stack Marine_Snow;
	Item_Stack Waste;
	Item_Stack Steam;
	Item_Stack Desalinated_Water;
	Item_Stack Salt;
	Item_Stack Raw_Algae;
	Item_Stack Biopaste;
	Item_Stack Milkfish;
	Item_Stack Mojarra;
	Item_Stack Menhaden;
	Item_Stack Drill_Mud;
	Item_Stack J1;
	Item_Stack J2;
	Item_Stack Hydrogen;
	Item_Stack Oxygen;
	Item_Stack Chlorine;
	Item_Stack Sodium_Hydroxide;
	Item_Stack Hydrogen_Chloride;
	Item_Stack Hydrochloric_Acid;
	Item_Stack Item_List[LDE_ITEMS];
} PRESET_ITEMS;

typedef struct {
	Item_Category Coolant;
	Item_Category Feedwater;
	Item_Category Biomass;
} PRESET_CATEGORIES;

typedef struct {
	Item_Stack Blank_Item;
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
	Item_Stack Blank_Item;
} PRESET_I_RECIPES;

typedef struct {
	Item_Stack Blank_Item;
	Recipe RP_Saltwater;
	Recipe GB_Algae;
} PRESET_O_RECIPES;

typedef struct {
	Fish Milkfish;
	Fish Mojarra;
	Fish Menhaden;
} PRESET_FISH;

extern PRESET_ITEMS Preset_Items;
extern PRESET_CATEGORIES Preset_Categories;
extern PRESET_IO_RECIPES Preset_IO_Recipes;
extern PRESET_I_RECIPES Preset_I_Recipes;
extern PRESET_O_RECIPES Preset_O_Recipes;
extern PRESET_FISH Preset_Fish;
extern Fish Fish_Catalog[LDE_FISH];
extern char Growth_Phases[LDE_FISHPHASES][32];
extern char Plural_Growth_Phases[LDE_FISHPHASES][32];
extern int Growth_Weights[LDE_FISHPHASES];
extern Recipe* Recipes[LDE_RECIPETYPES][LDE_MACHINES];

void Prep_Items();
void Free_Items();
void Update_Item(Point Pos, int Identifier, int Temperature);
Item_Stack Get_Item(Point Pos);
Item_Stack ID_To_Item(const int ID);
Item_Stack Get_Item_Stack_Data();
void Purge_Items();
bool Check_Category(int Item, Item_Category Category);
float Calculate_Pressure(int Temperature, float Boiling_Point, float H_Vaporisation);
int Get_Phase(int Fish, int Progress);
void Get_Phase_Name(char* Buffer, int Length, int Fish, int Progress, int Count);
Item_Stack Get_Fish_Item(int Identifier);
bool Process_O_Recipe(Recipe Selected_Recipe, Point Pos, Node Output_Locations);
bool Process_IO_Recipe(Recipe Selected_Recipe, Point Pos, Node Input_Locations, Node Output_Locations);
bool Extend_Recipe(Recipe Selected_Recipe, Point Pos, Node Preconfiguration[4]);