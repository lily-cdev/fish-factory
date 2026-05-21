#include <items.h>

PRESET_IO_RECIPES Preset_IO_Recipes = {
	.Blank_Item = { .Identifier = ktn_invalid }
};

PRESET_I_RECIPES Preset_I_Recipes = {
	.Blank_Item = { .Identifier = ktn_invalid }
};

PRESET_O_RECIPES Preset_O_Recipes = {
	.Blank_Item = { .Identifier = ktn_invalid }
};

PRESET_FISH Preset_Fish = {
	.Milkfish = { "Milkfish", 0, 300, 0.05 },
	.Mojarra = { "Mojarra", 1, 50, 0.1 },
	.Menhaden = { "Menhaden", 2, 100, 0.15 }
};