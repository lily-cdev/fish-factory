#include <items.h>

PRESET_ITEMS Preset_Items = {
	.Raw_Saltwater = {
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
	},
	.Saltwater = {
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
	},
	.Marine_Snow = {
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
	},
	.Waste = {
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
	},
	.Steam = {
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
	},
	.Desalinated_Water = {
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
	},
	.Salt = {
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
	},
	.Raw_Algae = {
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
	},
	.Biopaste = {
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
	},
	.Milkfish = {
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
	},
	.Mojarra = {
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
	},
	.Menhaden = {
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
	},
	.Drill_Mud = {
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
	},
	.J1 = {
		.Identifier = 13,
		.Hazard = Harmless,
		.Value = Worthless,
		.Display_Name = "[none]"
	},
	.J2 = {
		.Identifier = 14,
		.Hazard = 0,
		.Value = 0,
		.Display_Name = "[none]"
	},
	.Hydrogen = {
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
	},
	.Oxygen = {
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
	},
	.Chlorine = {
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
	},
	.Sodium_Hydroxide = {
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
	},
	.Hydrogen_Chloride = {
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
	},
	.Hydrochloric_Acid = {
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
	},
};

PRESET_CATEGORIES Preset_Categories = { };

PRESET_IO_RECIPES Preset_IO_Recipes = {
	.Blank_Item = { .Identifier = LDE_INVALID }
};

PRESET_I_RECIPES Preset_I_Recipes = {
	.Blank_Item = { .Identifier = LDE_INVALID }
};

PRESET_O_RECIPES Preset_O_Recipes = {
	.Blank_Item = { .Identifier = LDE_INVALID }
};

PRESET_FISH Preset_Fish = {
	.Milkfish = { "Milkfish", 0, 300, 0.05 },
	.Mojarra = { "Mojarra", 1, 50, 0.1 },
	.Menhaden = { "Menhaden", 2, 100, 0.15 }
};