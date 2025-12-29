#pragma once
extern "C" {
	#include <core.h>
	#include <prepping.h>
}
#include <clib.hpp>

struct OLD_METADATA {
public:
	std::vector<std::string> Logs;
	std::string Monitor_Size;
	const std::vector<int> Machine_Taxes = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1
	};
	const std::vector<std::vector<int>> Item_Labels = {
		{ Submarine_Dock, Cable_Node },
		{ Ram_Pump },
		{ Algae_Bed },
		{ Filtration_Plant, Distillery, Electrolytic_Cell, Fluid_Mixer },
		{ Piezo_Generator, Bio_Generator, Geo_Well, Heat_Exchanger },
		{ Flowerpot, Ammunition_Shelf },
		{ Incinerator, Signal_Tower, Basic_Scrubber },
		{ Command_Platform }
	};
	const std::vector<int> Machine_Prices = {
		4, 15, 20, 4, 1, 30, 40, 35, 12, 70, 50, 0, 40, 4, 3, 3,
		20, 40, 10, 2, 4, 3, 40, 3, 60, 10, 2, 4, 0, 0, 5, 5, 4,
		30, 20, 90, 30, 50, 46, 20
	};
	std::vector<std::vector<bool>> Machine_Quirks = { };
	const std::vector<std::vector<int>> Quirk_Positions = {
		{ Reinforced_Pipe, Ram_Pump, Piezo_Generator, Decoration, Submarine_Dock, Filtration_Plant, Hazard_Strip,
			Spawning_Pool, Spawning_Controller, Spawning_Output, Spawning_Input, Flowerpot, Cable_Node,
			Large_Pipe, Petrified_Wood, Basalt_Tile, Silicone_Carpet, Money_Generator, Fluid_Generator },
		{ Reinforced_Pipe, Spawning_Pool, Spawning_Controller, Spawning_Output, Spawning_Input, Large_Pipe,
			Condenser_Input, Condenser_Heatsink, Condenser_Transferor, Turbine_Input, Turbine_Impulse,
			Turbine_Output },
		{ Signal_Tower, Spawning_Controller, Submarine_Dock, Heat_Exchanger, Money_Generator, Fluid_Generator,
			Turbine_Input },
		{ Reinforced_Pipe, Spawning_Pool, Ram_Pump, Large_Pipe, Money_Generator, Fluid_Generator }
	};
	const std::vector<std::vector<int>> Subcontents = {
		{ Spawning_Controller, Spawning_Output, Spawning_Input, Spawning_Pool },
		{ Decoration, Petrified_Wood, Basalt_Tile, Silicone_Carpet, Hazard_Strip },
		{ Reinforced_Pipe, R_Intersection },
		{ Large_Pipe, L_Intersection },
		{ Condenser_Input, Condenser_Heatsink, Condenser_Transferor },
		{ Turbine_Input, Turbine_Impulse, Turbine_Output }
	};
	const std::vector<std::vector<int>> Subcategory_Positions = {
		{ Reinforced, Large },
		{ },
		{ Modular_Spawning_Pool },
		{ Condenser },
		{ Turbine },
		{ Flooring },
		{ },
		{ }
	};
	const std::vector<std::string> Days = { "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur", "Sun" };
	const std::vector<std::vector<int>> Supported_Resolutions = { { 640, 360 }, { 1280, 720 }, { 1920, 1080 },
		{ 2560, 1440 }, { 3200, 1800 }, { 3840, 2160 } };
	const std::vector<int> Heating_Machines = { Incinerator, Geo_Well };//unused
};

struct OLD_KEYBINDS {
public:
	std::vector<std::string> Keybind_Texts = {
		"Drift up", "Drift down", "Drift left", "Drift right", "Toggle placing",
		"Toggle deleting", "Toggle inspecting", "Toggle wiring", "Toggle plumbing",
		"Toggle catalog", "Interact", "Rotate", "Sprint", "Exit"
	};
	std::vector<SDL_Keycode> Keybind_List = { SDLK_W, SDLK_S, SDLK_A, SDLK_D, SDLK_1, SDLK_2, SDLK_3,
		SDLK_4, SDLK_5, SDLK_C, SDLK_E, SDLK_R, SDLK_LSHIFT, SDLK_ESCAPE };
	std::vector<SDL_Keycode> Keybind_Settings = Keybind_List;
};

struct OLD_TEMPORARY {
public:
	std::vector<double> FPS_Query = { };
	std::vector<SDL_FRect> Query = { };
	std::vector<int> ID_Query = { };
	std::vector<SDL_Color> Color_Query = { };
};

struct OLD_CACHE {
public:
	std::vector<std::vector<SDL_FRect>> Log_Rectangles;
};

struct OLD_INTERFACE {
public:
	std::vector<std::vector<std::string>> Slider_Texts = {
		{ "nHD", "HD", "FHD", "QHD", "QHD+", "4K" },
		{ "Milkfish", "Mojarra", "Menhaden" },
		{ "Credits", "Legal" },
		{ "Overview", "Tutorials", "Cheats" },
		{ "15 FPS", "30 FPS", "60 FPS", "120 FPS", "240 FPS" },
		{ },
		{ "Windowed", "Borderless", "Fullscreen" },
		{ },
		{ "-1TLA/s", "-1GLA/s", "-1MLA/s", "-1kLA/s", "-1LA/s", "0LA/s",
			"1LA/s", "1kLA/s", "1MLA/s", "1GLA/s", "1TLA/s" },
		{ },
		{ },
		{ },
		{ },
		{ }
	};
	const std::vector<int> Valve300_Postions { 0, 1, 2, 3, 5, 10, 15, 20, 50, 100, 150, 300 };
	std::vector<std::string> Terminal_Logs = { };
	std::vector<int> Default_Positions = { 0 };
	std::string Terminal_Entry;
	std::vector<long double> Log_Heights;
	std::vector<double> Effects = std::vector<double>(1, 0);
};

extern OLD_METADATA Metadata_L;
extern OLD_KEYBINDS Keybinds_L;
extern OLD_TEMPORARY Temporary_L;
extern OLD_CACHE Cache_L;
extern OLD_INTERFACE Interface_L;

SDL_FRect Buffer_Rectangle(const SDL_FRect &Source, const int X, const int Y);
std::string Abbreviate_Number(long double Number);
std::string Truncate(double Number, int Depth);
void Recache_TT_Commands();
void Preload_Assets_L();
void Render_Dynamic_Text(TTF_Font* Selected_Font, std::string Text, SDL_Color Color, int X, int Y);
int Render_Rich_Text(TTF_Font* Selected_Font, std::string Raw_Text, int X, int Y,
	bool Inverted = false, bool Disabled = false);