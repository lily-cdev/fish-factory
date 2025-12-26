#pragma once
extern "C" {
	#include <core.h>
}
#include <preloader.h>
#include <clib.hpp>

class Item_Stack {
public:
	int Identifier = LDE_INVALID;
	int Hazard = 0;
	int Value = 0;
	std::string Display_Name = "None";
	double Sale_Value = 0;
	double Toxicity = 0;
	double Temperature = LDE_ROOMTEMP;
	double Chemical_Energy = 0;
	double Boiling_Point = 0;
	double Vaporisation_Enthalpy = 0;
};

class Item_Category {
public:
	int Identifier = LDE_INVALID;
	std::string Display_Name = "None";
	std::vector<Item_Stack> Contents = { };
};

class Recipe {
public:
	bool Shuffling_Barred = true;
	bool Voiding_Excess = false;
	int Time = 0;
	int Power = 0;
	std::vector<Item_Stack> Input_Items = { };
	std::vector<double> Input_Counts = { };
	std::vector<Item_Stack> Output_Items = { };
	std::vector<double> Output_Counts = { };
	int ID = 1;
};

class Fish {
public:
	std::string Name = "";
	int Identifier = 0;
	int Maximum_Growth = 0;
	double Food_Consumption = 0;
};

struct PRESET_ITEMS {
public:
	Item_Stack Raw_Saltwater{
		.Identifier = 0,
		.Hazard = Harmless,
		.Value = Worthless,
		.Display_Name = "Raw Seawater",
		.Sale_Value = 0.25,
		.Toxicity = 0.5,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = 220,
		.Vaporisation_Enthalpy = 44
	};
	Item_Stack Saltwater{
		.Identifier = 1,
		.Hazard = Harmless,
		.Value = Worthless,
		.Display_Name = "Clean Saltwater",
		.Sale_Value = 0.3,
		.Toxicity = 0.4,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = 215,
		.Vaporisation_Enthalpy = 42
	};
	Item_Stack Marine_Snow{
		.Identifier = 2,
		.Hazard = Harmless,
		.Value = Normal,
		.Display_Name = "Aqueous Marine Snow",
		.Sale_Value = 5,
		.Toxicity = 0.75,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 1700000,
		.Boiling_Point = 212,
		.Vaporisation_Enthalpy = 45
	};
	Item_Stack Waste{
		.Identifier = 3,
		.Hazard = Medium,
		.Value = Worthless,
		.Display_Name = "Liquid Waste",
		.Sale_Value = -2,
		.Toxicity = LDE_WASTETOX,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = -2,
		.Vaporisation_Enthalpy = -2
	};
	Item_Stack Steam{
		.Identifier = 4,
		.Hazard = Harmless,
		.Value = Worthless,
		.Display_Name = "Steam",
		.Sale_Value = 0,
		.Toxicity = 0,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = LDE_INVALID,
		.Vaporisation_Enthalpy = LDE_INVALID
	};
	Item_Stack Desalinated_Water{
		.Identifier = 5,
		.Hazard = Harmless,
		.Value = Worthless,
		.Display_Name = "Distilled Water",
		.Sale_Value = 5,
		.Toxicity = 0,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = 212,
		.Vaporisation_Enthalpy = 40.7
	};
	Item_Stack Salt{
		.Identifier = 6,
		.Hazard = Harmless,
		.Value = Worthless,
		.Display_Name = "Salt Sol'n",
		.Sale_Value = 20,
		.Toxicity = 0.25,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = 230,
		.Vaporisation_Enthalpy = 48
	};
	Item_Stack Raw_Algae{
		.Identifier = 7,
		.Hazard = Harmless,
		.Value = Worthless,
		.Display_Name = "Wet Algae",
		.Sale_Value = 12,
		.Toxicity = 0.5,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 10000,
		.Boiling_Point = 214,
		.Vaporisation_Enthalpy = 41
	};
	Item_Stack Biopaste{
		.Identifier = 8,
		.Hazard = Harmless,
		.Value = Normal,
		.Display_Name = "Algae Paste",
		.Sale_Value = 24,
		.Toxicity = 0.25,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 6000000,
		.Boiling_Point = 220,
		.Vaporisation_Enthalpy = 45
	};
	Item_Stack Milkfish{
		.Identifier = 9,
		.Hazard = Harmless,
		.Value = Normal,
		.Display_Name = "Milkfish",
		.Sale_Value = 250,
		.Toxicity = 0,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = -2,
		.Vaporisation_Enthalpy = -2
	};
	Item_Stack Mojarra{
		.Identifier = 10,
		.Hazard = Harmless,
		.Value = Normal,
		.Display_Name = "Mojarra",
		.Sale_Value = 120,
		.Toxicity = 0,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = -2,
		.Vaporisation_Enthalpy = -2
	};
	Item_Stack Menhaden{
		.Identifier = 11,
		.Hazard = Harmless,
		.Value = Normal,
		.Display_Name = "Menhaden",
		.Sale_Value = 100,
		.Toxicity = 0,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = -2,
		.Vaporisation_Enthalpy = -2
	};
	Item_Stack Drill_Mud{
		.Identifier = 12,
		.Hazard = Harmless,
		.Value = Normal,
		.Display_Name = "Drilling Mud",
		.Sale_Value = 40,
		.Toxicity = 12,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = 260,
		.Vaporisation_Enthalpy = 50
	};
	Item_Stack J1{
		13,
		0,
		0,
		"[none]"
	};
	Item_Stack J2{
		14,
		0,
		0,
		"[none]"
	};
	Item_Stack Hydrogen{
		.Identifier = 15,
		.Hazard = Harmless,
		.Value = Worthless,
		.Display_Name = "Hydrogen",
		.Sale_Value = 0.05,
		.Toxicity = 0,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 10000,
		.Boiling_Point = LDE_INVALID,
		.Vaporisation_Enthalpy = LDE_INVALID
	};
	Item_Stack Oxygen{
		.Identifier = 16,
		.Hazard = Harmless,
		.Value = Worthless,
		.Display_Name = "Oxygen",
		.Sale_Value = 0.03,
		.Toxicity = -20,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = LDE_INVALID,
		.Vaporisation_Enthalpy = LDE_INVALID
	};
	Item_Stack Chlorine{
		.Identifier = 17,
		.Hazard = Mild,
		.Value = Normal,
		.Display_Name = "Chlorine Gas",
		.Sale_Value = 5,
		.Toxicity = 10,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = LDE_INVALID,
		.Vaporisation_Enthalpy = LDE_INVALID
	};
	Item_Stack Sodium_Hydroxide{
		.Identifier = 18,
		.Hazard = Mild,
		.Value = Normal,
		.Display_Name = "Aqueous Lye",
		.Sale_Value = 8,
		.Toxicity = 12,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = 230,
		.Vaporisation_Enthalpy = 45
	};
	Item_Stack Hydrogen_Chloride{
		.Identifier = 19,
		.Hazard = Mild,
		.Value = Normal,
		.Display_Name = "Hydrogen Chloride",
		.Sale_Value = 10,
		.Toxicity = 10,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = LDE_INVALID,
		.Vaporisation_Enthalpy = LDE_INVALID
	};
	Item_Stack Hydrochloric_Acid{
		.Identifier = 20,
		.Hazard = Mild,
		.Value = Normal,
		.Display_Name = "Muriatic Acid",
		.Sale_Value = 10,
		.Toxicity = 12,
		.Temperature = LDE_ROOMTEMP,
		.Chemical_Energy = 0,
		.Boiling_Point = 110,
		.Vaporisation_Enthalpy = 32
	};
	std::vector<Item_Stack> Item_List = { Raw_Saltwater, Saltwater, Marine_Snow, Waste, Steam,
		Desalinated_Water, Salt, Raw_Algae, Biopaste, Milkfish, Mojarra, Menhaden, Drill_Mud, J1,
		J2, Hydrogen, Oxygen, Chlorine, Sodium_Hydroxide, Hydrogen_Chloride, Hydrochloric_Acid };
};

extern PRESET_ITEMS Preset_Items;

struct PRESET_CATEGORIES {
public:
	Item_Category Coolant{
		.Identifier = 0,
		.Display_Name = "Heating Medium",
		.Contents = {
			Preset_Items.Saltwater,
			Preset_Items.Desalinated_Water
		}
	};
	Item_Category Feedwater{
		.Identifier = 0,
		.Display_Name = "Feedwater",
		.Contents = {
			Preset_Items.Desalinated_Water
		}
	};
	Item_Category Biomass{
		.Identifier = 1,
		.Display_Name = "Biomass",
		.Contents = {
			Preset_Items.Marine_Snow,
			Preset_Items.Raw_Algae,
			Preset_Items.Biopaste,
			Preset_Items.Milkfish,
			Preset_Items.Mojarra,
			Preset_Items.Menhaden
		}
	};
};

struct PRESET_IO_RECIPES {
public:
	Item_Stack Blank_Item;
	Recipe FP_Saltwater{ true, false, 1, 70, { Preset_Items.Raw_Saltwater }, { 12 }, { Preset_Items.Saltwater,
		Preset_Items.Marine_Snow, Preset_Items.Waste }, { 8.5, 2, 1.5 }, 1 };
	Recipe FP_Biopaste{ true, false, 1, 70, { Preset_Items.Raw_Algae }, { 4 }, { Blank_Item,
		Preset_Items.Biopaste, Preset_Items.Waste }, { 0, 2, 0.5 }, 1 };
	Recipe FM_Drillmud_1{ false, false, 1, 650, { Preset_Items.Saltwater, Preset_Items.Marine_Snow }, { 1, 5 },
		{ Preset_Items.Drill_Mud }, { 6 }, 1 };
	Recipe FM_Drillmud_2{ false, false, 1, 650, { Preset_Items.Desalinated_Water, Preset_Items.Marine_Snow },
		{ 1, 5 }, { Preset_Items.Drill_Mud }, { 6 }, 1 };
	Recipe FM_Hydrogen_Chloride{ false, false, 1, 650, { Preset_Items.Hydrogen, Preset_Items.Chlorine }, { 3, 3 },
		{ Preset_Items.Hydrogen_Chloride }, { 3 }, 1 };
	Recipe FM_Hydrochloric_Acid{ false, false, 1, 650, { Preset_Items.Hydrogen_Chloride,
		Preset_Items.Desalinated_Water }, { 6, 1 }, { Preset_Items.Hydrochloric_Acid }, { 1 }, 1 };
	Recipe D_Water{ true, false, 5, 400, { Preset_Items.Saltwater }, { 4 }, { Preset_Items.Salt,
		Preset_Items.Desalinated_Water }, { 1, 2.5 }, 1 };
	Recipe EP_Water{ true, false, 10, 5000, { Preset_Items.Desalinated_Water }, { 12 }, { Preset_Items.Hydrogen,
		Blank_Item, Preset_Items.Oxygen }, { 12, 0, 12 }, 1 };
	Recipe EP_Saltwater{ true, false, 10, 5000, { Preset_Items.Saltwater }, { 12 }, { Preset_Items.Hydrogen,
		Preset_Items.Sodium_Hydroxide, Preset_Items.Chlorine }, { 6, 12, 6 }, 2 };
	Recipe EP_Salt{ true, false, 10, 5000, { Preset_Items.Saltwater }, { 18 }, { Preset_Items.Hydrogen,
		Preset_Items.Sodium_Hydroxide, Preset_Items.Chlorine }, { 9, 18, 9 }, 3 };
};

struct PRESET_I_RECIPES {
public:
};

struct PRESET_O_RECIPES {
public:
	Item_Stack Blank_Item;
	Recipe RP_Saltwater{ false, false, 1, 4, { }, { }, { Preset_Items.Raw_Saltwater }, { 0.5 }, 1 };
	Recipe GB_Algae{ false, false, 2, 60, { }, { }, { Preset_Items.Raw_Algae,
		Preset_Items.Raw_Algae }, { 2.5, 2.5 }, 5 };
};

struct PRESET_FISH {
public:
	Fish Milkfish{ "Milkfish", 0, 300, 0.05 };
	Fish Mojarra{ "Mojarra", 1, 50, 0.1 };
	Fish Menhaden{ "Menhaden", 2, 100, 0.15 };
};

extern PRESET_CATEGORIES Preset_Categories;
extern std::vector<std::vector<Recipe*>> I_Recipes;
extern std::vector<std::vector<Recipe*>> O_Recipes;
extern std::vector<std::vector<Recipe*>> IO_Recipes;
extern std::vector<std::vector<Recipe*>> All_Recipes[3];
extern PRESET_IO_RECIPES Preset_IO_Recipes;
extern PRESET_I_RECIPES Preset_I_Recipes;
extern PRESET_O_RECIPES Preset_O_Recipes;
extern std::vector<Fish> Fish_Catalog;
extern std::vector<std::string> Growth_Phases;
extern std::vector<std::string> Plural_Growth_Phases;
extern std::vector<int> Growth_Weights;
extern PRESET_FISH Preset_Fish;

Item_Stack Get_Item(int X, int Y);
Item_Stack ID_To_Item(const int ID);
Item_Stack Get_Item_Stack_Data();
void Purge_Items();
void Update_Item(int X, int Y, int Identifier, int Temperature = LDE_ROOMTEMP);
bool Check_Category(int Item, Item_Category Category);
double Calculate_Pressure(int Temperature, double Boiling_Point, double H_Vaporisation);
bool Process_O_Recipe(Recipe Selected_Recipe, int X, int Y, std::vector<Point> Output_Locations);
bool Process_Recipe(Recipe Selected_Recipe, int X, int Y, std::vector<Point> Input_Locations,
	std::vector<Point> Output_Locations);
void Extend_Recipe(Recipe Selected_Recipe, int X, int Y, const std::vector<Point> (&Preconfiguration)[4]);
void Preload_Recipes();
int Get_Phase(int Fish, int Progress);
std::string Get_Phase_Name(int Fish, int Progress, int Count);
Item_Stack Get_Fish_Item(int Identifier);