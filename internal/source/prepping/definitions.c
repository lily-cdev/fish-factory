#include <prepping.h>

AUDIO Audio;
CORE Core = {
	.Window = NULL,
	.Renderer = NULL,
	.Game_Texture = NULL,
	.Is_Running = true,
	.Debug_Mode = false,
	.Suffixes = { 'J', 'k', 'M', 'G', 'T' },
	.Selected_Save = LDE_INVALID,
	.Camera = { -140, 0 },
	.Mouse = { 0, 0 }
};
DATA Data = {
	.CMD_Placed = false,
	.Version = 0,
	.Time = 0,
	.Day = 0,
	.Visual_Grid = { },
	.Connection_Grid = { },
	.Behavior_Grid = { },
	.Wiring_Grid = { },
	.Plumbing_Grid = { },
	.Items_Grid = { },
	.Temperature_Grid = { },
	.Animation_Grid = { },
	.Data_Grid = { },
	.Funds = 0
};
METADATA Metadata = {
	.Item_Labels = {
		{ Submarine_Dock, Cable_Node, LDE_INVALID },
		{ Ram_Pump, LDE_INVALID },
		{ Algae_Bed, LDE_INVALID },
		{ Filtration_Plant, Distillery, Electrolytic_Cell, Fluid_Mixer, LDE_INVALID },
		{ Piezo_Generator, Bio_Generator, Geo_Well, Heat_Exchanger, LDE_INVALID },
		{ Flowerpot, Ammunition_Shelf, LDE_INVALID },
		{ Incinerator, Signal_Tower, Basic_Scrubber, LDE_INVALID },
		{ Command_Platform, LDE_INVALID }
	},
	.Subcategory_Positions = {
		{ Reinforced, Large, LDE_INVALID },
		{ LDE_INVALID },
		{ Modular_Spawning_Pool, LDE_INVALID },
		{ Condenser, LDE_INVALID },
		{ Turbine, LDE_INVALID },
		{ Flooring, LDE_INVALID },
		{ LDE_INVALID },
		{ LDE_INVALID }
	},
	.Subcontents = {
		{ Spawning_Controller, Spawning_Output, Spawning_Input, Spawning_Pool, LDE_INVALID },
		{ Decoration, Petrified_Wood, Basalt_Tile, Silicone_Carpet, Hazard_Strip, LDE_INVALID },
		{ Reinforced_Pipe, R_Intersection, LDE_INVALID },
		{ Large_Pipe, L_Intersection, LDE_INVALID },
		{ Condenser_Input, Condenser_Heatsink, Condenser_Transferor, LDE_INVALID },
		{ Turbine_Input, Turbine_Impulse, Turbine_Output, LDE_INVALID }
	},
	.Machine_Taxes = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	},
	.Machine_Prices = {
		4, 15, 20, 4, 1, 30, 40, 35, 12, 70, 50, 0, 40, 4, 3, 3, 20, 40, 10, 2,
		4, 3, 40, 3, 60, 10, 2, 4, 0, 0, 5, 5, 4, 30, 20, 90, 30, 50, 46, 20
	}
};
SETTINGS Settings = {
	.AA_Temporary = true,
	.VS_Temporary = false,
	.Fullscreen = 0,
	.Screen_Size = 0,
	.Anti_Aliasing = 1,
	.VSync = 0,
	.Volume = 50,
	.Raw_FPS = 2
};
TEXTURES Textures = { };
RECTS Rects = { };
COLORS Colors = {
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
FONTS Fonts = { };
TEMPORARY Temporary = {
	.Settings_Changed = false,
	.Modular1_Requirement = 0,
	.Modular2_Requirement = 0,
	.Dialogue_Position = 0,
	.Ticker_Target = 0,
	.Ticker_Position = 0,
	.Ticker_Frames = 0,
	.Tutorial_Step = LDE_INVALID,
	.Tutorial_Size = { },
	.Tutorial_Offset = { },
	.Scroll_Percent = 0,
	.Dialogue_Maximum = 0,
	.Log_Inversions = { true, false, false },
	.First_Coordinate = { 0, 0 },
	.Docks.Data = NULL
};
CACHE Cache = {
	.Wire_State = LDE_INVALID,
	.Wire_Cache.Data = NULL,
	.Blueprint_Cache = NULL,
	.Log_Cache.Data = NULL
};
INTERFACE Interface = {
	.Animation_Locked = false,
	.Building = false,
	.Sprinting = false,
	.Ocean_Cycle = 0,
	.Node_Cycle = 0,
	.Movespeed = 120,
	.Log_Offset = 0,
	.Target_Tile = { 0, 0 },
	.Prompt_Identifier = P_None,
	.Subprompt_Identifier = LDE_INVALID,
	.Tool = LDE_INVALID,
	.UD_Input = LDE_INVALID,
	.LR_Input = LDE_INVALID,
	.Queried_Price = 0,
	.Engagement = 0,
	.UI_Tab = 1,
	.Subtab = 0,
	.UI_Selection = 0,
	.Frame_Rate = 60,
	.Time_Frames = 0,
	.Maximum_Time_Frames = 0,
	.Subtime_Frames = 0,
	.Maximum_Subtime_Frames = 0,
	.Placing_Item = 1,
	.Placing_Rotation = 0,
	.Save_Frames = 0,
	.Map_X = 0,
	.Map_Y = 0,
	.Registering_Keybind = LDE_INVALID,
	.Slider_Positions = { 0, 0, 0, 0, 0, 50, 0, 0, 5, 0, 13, 0, 0, 0 },
	.Tile_Centerpoint = { 0, 0 }
};
PRECONFIGURATIONS Preconfigurations = { };