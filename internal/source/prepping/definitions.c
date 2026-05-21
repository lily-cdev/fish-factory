#include <prepping.h>

struct lde_core Core = {
	.Is_Running = true,
	.Suffixes = { 'J', 'k', 'M', 'G', 'T' },
	.Selected_Save = ktn_invalid,
	.Camera = { -140, 0 }
};
struct lde_data Data = { };
struct lde_metadata Metadata = {
	.Item_Labels = {
		{ "sub_dock", "cable_node", ktn_null_string },
		{ "ram_pump", ktn_null_string },
		{ "algae_bed", ktn_null_string },
		{ "filtration_plant", "distillery", "electro_cell", "fluid_mixer", ktn_null_string },
		{ "rtg", "furnace", "geo_well", "hx", ktn_null_string },
		{ "flowerpot", "ammo_rack", ktn_null_string },
		{ "incinerator", "signal_tower", "battery", ktn_null_string },
		{ "command_platform", ktn_null_string }
	},
	.Subcategory_Positions = {
		{ Reinforced, Large, ktn_terminator },
		{ ktn_terminator },
		{ Modular_Spawning_Pool, ktn_terminator },
		{ Condenser, ktn_terminator },
		{ Turbine, ktn_terminator },
		{ Flooring, ktn_terminator },
		{ ktn_terminator },
		{ ktn_terminator }
	},
	.Subcontents = {
		{ "spawning_controller", "spawning_output", "spawning_input", "spawning_pool", ktn_null_string },
		{ "plate", "petrified_wood", "basalt_tile", "carpet", "hazard_strip", ktn_null_string },
		{ "heavy_pipe", "heavy_intersection", ktn_null_string },
		{ "large_pipe", "large_intersection", ktn_null_string },
		{ "condenser_input", "condenser_heatsink", "condenser_hx", "condenser_output", ktn_null_string },
		{ "turbine_input", "turbine_impulse", "turbine_output", ktn_null_string }
	},
	.Days = { "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur", "Sun" },
	.Supported_Resolutions = { { 640, 360 }, { 1280, 720 }, { 1920, 1080 }, { 2560, 1440 }, { 3200, 1800 }, { 3840, 2160 } },
	.Tool_Texts = { "building", "deleting", "inspecting", "wiring", "plumbing" }
};
struct lde_settings Settings = {
	.AA_Temporary = true,
	.Anti_Aliasing = 1,
	.VS_Temporary = true,
	.VSync = 1,
	.Volume = 50,
	.Raw_FPS = 2
};
struct lde_textures Textures = { };
struct lde_rects Rects = { };
const struct lde_colors Colors = {
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
struct lde_fonts Fonts = {
	.Paths = {
		"oxygen/regular",
		"cantarell/regular",
		"cantarell/regular",
		"cantarell/regular",
		"cantarell/regular",
		"cantarell/regular",
		"oxygen/regular"
	},
	.Sizes = { 32, 24, 18, 16, 12, 10, 12 }
};
struct lde_keybinds Keybinds = {
	.Keybind_List = { SDLK_W, SDLK_S, SDLK_A, SDLK_D, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_C, SDLK_E, SDLK_R,
		SDLK_LSHIFT, SDLK_ESCAPE },
	.Keybind_Settings = { SDLK_W, SDLK_S, SDLK_A, SDLK_D, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_C, SDLK_E, SDLK_R,
		SDLK_LSHIFT, SDLK_ESCAPE }
};
struct lde_temporary Temporary = {
	.Tutorial_Step = ktn_invalid,
	.Log_Inversions = { true, false, false }
};
struct lde_cache Cache = {
	.Wire_State = ktn_invalid
};
struct lde_supplies Supplies = { };
struct lde_interface Interface = {
	.Movespeed = 120,
	.Prompt_Identifier = P_None,
	.Subprompt_Identifier = ktn_invalid,
	.Tool = ktn_invalid,
	.UD_Input = ktn_invalid,
	.LR_Input = ktn_invalid,
	.UI_Tab = 1,
	.Frame_Rate = 60,
	.Item = NULL,
	.Registering_Keybind = ktn_invalid,
	.Valve300_Postions = { 0, 1, 2, 3, 5, 10, 15, 20, 50, 100, 150, 300 },
	.Slider_Positions = { 0, 0, 0, 0, 0, 50, 0, 0, 5, 0, 13, 0, 0, 0 },
	.Slider_Texts = {
		{ "nHD", "HD", "FHD", "QHD", "QHD+", "4K", ktn_null_string },
		{ "Milkfish", "Mojarra", "Menhaden", ktn_null_string },
		{ "credits", "legal", ktn_null_string },
		{ "overview", "tutorials", "cheats", ktn_null_string },
		{ "15 FPS", "30 FPS", "60 FPS", "120 FPS", "240 FPS", ktn_null_string },
		{ ktn_null_string },
		{ "windowed", "borderless", "fullscreen", ktn_null_string },
		{ ktn_null_string },
		{ "-1TLA/s", "-1GLA/s", "-1MLA/s", "-1kLA/s", "-1LA/s", "0LA/s", "1LA/s", "1kLA/s", "1MLA/s", "1GLA/s", "1TLA/s",
			ktn_null_string },
		{ ktn_null_string },
		{ ktn_null_string },
		{ ktn_null_string },
		{ ktn_null_string },
		{ ktn_null_string },
		{ ktn_null_string }
	}
};
struct lde_buffers Buffers = { };
struct lde_preconfigs Preconfigs = { };