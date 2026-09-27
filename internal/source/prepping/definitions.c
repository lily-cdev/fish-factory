#include <prepping.h>

struct Proto_Core Core = {
	.Is_Running = true,
	.Suffixes = { 'J', 'k', 'M', 'G', 'T' },
	.Selected_Save = ktn_invalid,
	.Camera = { -140, 0 },
	.Tile_Size = 40,
	.Buffer_Size = 360,
	.Ratio = 1
};
struct Proto_Data Data = {
	.Version = 4
};
struct Proto_Metadata Metadata = {
.Days = { "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur", "Sun" },
	.Supported_Resolutions = { { 640, 360 }, { 1280, 720 }, { 1920, 1080 }, { 2560, 1440 }, { 3200, 1800 }, { 3840, 2160 } },
	.Tool_Texts = { "building", "deleting", "inspecting", "wiring", "plumbing" }
};
struct Proto_Settings Settings = {
	.AA_Temporary = true,
	.Fullscreen = 2,
	.Anti_Aliasing = 1,
	.VS_Temporary = true,
	.VSync = 1,
	.Volume = 50,
	.Raw_FPS = 2
};
struct Proto_Textures Textures = { };
struct Proto_Rects Rects = { };
const struct Proto_Colors Colors = {
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
	.Ocean = { 6, 66, 116 },
	.Base_Pair = { { 0, 255, 0 }, { 255, 0, 0 }, { 0, 0, 0 }, { 0, 0, 255 } }
};
struct Proto_Fonts Fonts = {
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
struct Proto_Keybinds Keybinds = {
	.Keybind_List = { SDLK_W, SDLK_S, SDLK_A, SDLK_D, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_C, SDLK_E, SDLK_R,
		SDLK_LSHIFT, SDLK_ESCAPE },
	.Keybind_Settings = { SDLK_W, SDLK_S, SDLK_A, SDLK_D, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_C, SDLK_E, SDLK_R,
		SDLK_LSHIFT, SDLK_ESCAPE }
};
struct Proto_Temporary Temporary = {
	.Tutorial_Step = ktn_invalid,
	.Log_Inversions = { true, false, false },
};
struct Proto_Cache Cache = {
	.Wire_State = ktn_invalid
};
struct Proto_Supplies Supplies = { };
struct Proto_Interface Interface = {
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
	.Valve300_Postions = { 0, 1, 2, 3, 5, 10, 20 },
	.Time_Positions = { 0.5f,  1.0f, 2.0f, 3.0f, 5.0f },
	.Slider_Positions = { 0, 0, 0, 0, 0, 50, 0, 0, 5, 0, 13, 0, 0, 0, 0, 1, 0 },
	.Slider_Texts = {
		{ "nHD", "HD", "FHD", "QHD", "QHD+", "4K", ktn_null_string },
		{ "Milkfish", "Mojarra", "Menhaden", ktn_null_string },
		{ "credits", "legal", ktn_null_string },
		{ "tutorials", "overview", "cheats", ktn_null_string },
		{ "15 FPS", "30 FPS", "60 FPS", "120 FPS", "240 FPS", ktn_null_string },
		{ ktn_null_string },
		{ "windowed", "borderless", "fullscreen", ktn_null_string },
		{ ktn_null_string },
		{ "-1TLA/s", "-1GLA/s", "-1MLA/s", "-1kLA/s", "-1LA/s", "0LA/s", "1LA/s", "1kLA/s", "1MLA/s", "1GLA/s", "1TLA/s", ktn_null_string },
		{ ktn_null_string },
		{ ktn_null_string },
		{ ktn_null_string },
		{ ktn_null_string },
		{ ktn_null_string },
		{ ktn_null_string },
		{ "0.5x", "1.0x", "2.0x", "3.0x", "5.0x", ktn_null_string },
		{ ktn_null_string }
	}
};
struct Proto_Buffers Buffers = { };