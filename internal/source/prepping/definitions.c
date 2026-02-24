#include <prepping.h>

lde_core Core = {
	.Is_Running = true,
	.Suffixes = { 'J', 'k', 'M', 'G', 'T' },
	.Selected_Save = LDE_INVALID,
	.Camera = { -140, 0 }
};
lde_data Data = { };
lde_metadata Metadata = {
	.Item_Labels = {
		{ Submarine_Dock, Cable_Node, LDE_TERMINATOR },
		{ Ram_Pump, LDE_TERMINATOR },
		{ Algae_Bed, LDE_TERMINATOR },
		{ Filtration_Plant, Distillery, Electrolytic_Cell, Fluid_Mixer, LDE_TERMINATOR },
		{ RTG, Bio_Generator, Geo_Well, Heat_Exchanger, LDE_TERMINATOR },
		{ Flowerpot, Ammunition_Shelf, LDE_TERMINATOR },
		{ Incinerator, Signal_Tower, Basic_Scrubber, LDE_TERMINATOR },
		{ Command_Platform, LDE_TERMINATOR }
	},
	.Subcategory_Positions = {
		{ Reinforced, Large, LDE_TERMINATOR },
		{ LDE_TERMINATOR },
		{ Modular_Spawning_Pool, LDE_TERMINATOR },
		{ Condenser, LDE_TERMINATOR },
		{ Turbine, LDE_TERMINATOR },
		{ Flooring, LDE_TERMINATOR },
		{ LDE_TERMINATOR },
		{ LDE_TERMINATOR }
	},
	.Subcontents = {
		{ Spawning_Controller, Spawning_Output, Spawning_Input, Spawning_Pool, LDE_TERMINATOR },
		{ Decoration, Petrified_Wood, Basalt_Tile, Silicone_Carpet, Hazard_Strip, LDE_TERMINATOR },
		{ Reinforced_Pipe, R_Intersection, LDE_TERMINATOR },
		{ Large_Pipe, L_Intersection, LDE_TERMINATOR },
		{ Condenser_Input, Condenser_Heatsink, Condenser_Transferor, LDE_TERMINATOR },
		{ Turbine_Input, Turbine_Impulse, Turbine_Output, LDE_TERMINATOR }
	},
	.Machine_Taxes = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	},
	.Machine_Prices = {
		4, 15, 20, 4, 1, 30, 40, 35, 12, 70, 50, 0, 40, 4, 3, 3, 20, 40, 10, 2,
		4, 3, 40, 3, 60, 10, 2, 4, 0, 0, 5, 5, 4, 30, 20, 90, 30, 50, 46, 20
	},
	.Quirk_Positions = {
		{ Reinforced_Pipe, Ram_Pump, Decoration, Submarine_Dock, Filtration_Plant, Hazard_Strip, Spawning_Pool,
			Spawning_Controller, Spawning_Output, Spawning_Input, Flowerpot, Cable_Node, Large_Pipe, Petrified_Wood,
			Basalt_Tile, Silicone_Carpet, Money_Generator, Fluid_Generator, LDE_TERMINATOR },
		{ Reinforced_Pipe, Spawning_Pool, Spawning_Controller, Spawning_Output, Spawning_Input, Large_Pipe,
			Condenser_Input, Condenser_Heatsink, Condenser_Transferor, Turbine_Input, Turbine_Impulse, Turbine_Output,
			LDE_TERMINATOR },
		{ Signal_Tower, Spawning_Controller, Submarine_Dock, Heat_Exchanger, Money_Generator, Fluid_Generator,
			Turbine_Input, LDE_TERMINATOR },
		{ Reinforced_Pipe, Spawning_Pool, Ram_Pump, Large_Pipe, Money_Generator, Fluid_Generator, LDE_TERMINATOR }
	},
	.Days = { "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur", "Sun" },
	.Supported_Resolutions = { { 640, 360 }, { 1280, 720 }, { 1920, 1080 }, { 2560, 1440 }, { 3200, 1800 }, { 3840,
		2160 } },
	.Tool_Texts = { "building", "deleting", "inspecting", "wiring", "plumbing", "linking" }
};
lde_settings Settings = {
	.AA_Temporary = true,
	.Anti_Aliasing = 1,
	.Volume = 50,
	.Raw_FPS = 2
};
lde_textures Textures = { };
lde_rects Rects = { };
lde_colors Colors = {
	.Abyss_Black = { 0, 0, 0 },
	.Pure_White = { 255, 255, 255 },
	.Light_Grey = { 235, 240, 240 },
	.Mid_Grey = { 180, 180, 180 },
	.Clean_Grey = { 155, 155, 155 },
	.Dark_Grey = { 105, 110, 105 },
	.Reinforced_Grey = { 42, 42, 42 },
	.Cherry_Blossom = { 255, 183, 197 },
	.Copper_Wire = { 184, 115, 51 },
	.Carnage_Pink = { 204, 163, 185 },
	.Hostile_Red = { 187, 10, 30 },
	.Ocean = { 6, 66, 116 }
};
lde_fonts Fonts = { };
lde_keybinds Keybinds = {
	.Keybind_List = { SDLK_W, SDLK_S, SDLK_A, SDLK_D, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_C, SDLK_E, SDLK_R,
		SDLK_LSHIFT, SDLK_ESCAPE },
	.Keybind_Settings = { SDLK_W, SDLK_S, SDLK_A, SDLK_D, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_C, SDLK_E, SDLK_R,
		SDLK_LSHIFT, SDLK_ESCAPE }
};
lde_temporary Temporary = {
	.Tutorial_Step = LDE_INVALID,
	.Log_Inversions = { true, false, false }
};
lde_cache Cache = {
	.Wire_State = LDE_INVALID
};
lde_supplies Supplies = { };
lde_interface Interface = {
	.Movespeed = 120,
	.Prompt_Identifier = P_None,
	.Subprompt_Identifier = LDE_INVALID,
	.Tool = LDE_INVALID,
	.UD_Input = LDE_INVALID,
	.LR_Input = LDE_INVALID,
	.UI_Tab = 1,
	.Frame_Rate = 60,
	.Item = 1,
	.Registering_Keybind = LDE_INVALID,
	.Valve300_Postions = { 0, 1, 2, 3, 5, 10, 15, 20, 50, 100, 150, 300 },
	.Slider_Positions = { 0, 0, 0, 0, 0, 50, 0, 0, 5, 0, 13, 0, 0, 0 },
	.Slider_Texts = {
		{ "nHD", "HD", "FHD", "QHD", "QHD+", "4K", NULLSTRING },
		{ "Milkfish", "Mojarra", "Menhaden", NULLSTRING },
		{ "credits", "legal", NULLSTRING },
		{ "overview", "tutorials", "cheats", NULLSTRING },
		{ "15 FPS", "30 FPS", "60 FPS", "120 FPS", "240 FPS", NULLSTRING },
		{ NULLSTRING },
		{ "windowed", "borderless", "fullscreen", NULLSTRING },
		{ NULLSTRING },
		{ "-1TLA/s", "-1GLA/s", "-1MLA/s", "-1kLA/s", "-1LA/s", "0LA/s", "1LA/s", "1kLA/s", "1MLA/s", "1GLA/s", "1TLA/s",
			NULLSTRING },
		{ NULLSTRING },
		{ NULLSTRING },
		{ NULLSTRING },
		{ NULLSTRING },
		{ NULLSTRING }
	}
};
lde_buffers Buffers = { };
lde_preconfigs Preconfigs = { };