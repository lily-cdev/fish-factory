#pragma once
#include <Core.h>

#include <Audio_Handler.h>

struct Core {
public:
	SDL_Window* Application_Window = nullptr;
	SDL_Renderer* Application_Renderer = nullptr;
	SDL_Texture* Game_Texture = nullptr;
	bool Is_Running = true;
	bool Debug_Mode = false;
	std::vector<char> Suffixes = { 'J', 'k', 'M', 'G', 'T' };
	double Save_Filesizes[4];
	int Selected_Save = LDE_INVALID;
};

struct Metadata {
public:
	std::vector<std::string> Logs;
	std::string Monitor_Size;
	const std::vector<std::string> Machine_Names = {
		"Reinforced Pipe",
		"Ram Pump",
		"Incinerator",
		"Piezoelectric Generator",
		"Decoration",
		"Submarine Dock",
		"Filtration Plant",
		"Bioelectric Generator",
		"Pool",
		"Distillery",
		"Algae Growth Bed",
		"Command Platform",
		"[NF] Basic Scrubber",
		"Controller",
		"Output",
		"Input",
		"Electrolytic Cell",
		"Fluid Mixer",
		"Signal Tower",
		"Flowerpot",
		"Ammunition Shelf",
		"Cable Node",
		"Geothermal Well",
		"Large Pipe",
		"Heat Exchanger",
		"Petrified Wood Tile",
		"Basalt Tile",
		"Silicone Carpet",
		"Money Generator",
		"Fluid Generator",
		"Reinforced Intersection",
		"Large Intersection",
		"Hazard Strip",
		"Input",
		"Heat Sink",
		"Transferor",
		"Output",
		"Input",
		"Impulse Block",
		"Output"
	};
	const std::vector<std::string> Machine_Descriptions = {
		"A Steel-shelled pipe bearing an internal lining of silicon carbide. It's resistant to pretty much everything,"
			" save for fluorine.",
		"A low-power pump that uses the natural pressure of the Ocean to force seawater into pipes."
			" It's literally just a glorified valve.",
		"Disposes of unwanted fluids by degrading them with 1,500 °F temperatures, before"
			" safely releasing them into the Ocean.",
		"Converts friction from the Ocean into miniscule amounts of power.",
		"Functionally inert, but looks a whole heck of a lot prettier than raw seabed.",
		"A dock allowing for products to be exported and shipped. Must be placed against a wall in order to function.",
		"Filters liquids, using very little electricity to operate.",
		"Containes genetically-engineered microbes which consume biomass and directly yield electricity.",
		"A pool in which to grow fish.",
		"Distills fluids. Useful for purification jobs beyond what the filtration plant can handle.",
		"An enclosed chamber, holding perfect conditions for rapid algae growth.",
		"A space for the staff of two to work and sleep, containing a small armoury, command centre, bunk bed, and bathroom."
			" Required for the factory to function.",
		"[NOT FUNCTIONAL] Intakes lye to remove carbon dioxide from the atmosphere. Produces waste as a byproduct.",
		"A controller required for a Modular Spawning Pool to function.",
		"A valve that can output the remaining fish.",
		"An input for fish-compatible biomass.",
		"Uses electrolysis to rip apart fluids into their separate ions.",
		"Mixes fluids inside of an armoured chamber.",
		"Broadcasts Morse code signals on a 2kHz bandwidth.",
		"A large flowerpot bearing the oversized Ceracanth flower, genetically engineered to bear a pleasant smell",
		"An ammunition rack holding an array of 40×399mm anti-aircraft rounds.",
		"A node able to group cables together.",
		"Uses the heat of underground magma to raise the temperature of a heating medium.",
		"A plain Steel pipe that can transport non-hazardous liquids in bulk.",
		"A large boiler that intakes feedwater and a heating medium in order to yield steam.",
		"A thick slab of synthetic petrified wood. Non-flammable, pretty, and VERY expensive.",
		"Heavy floor tiles made of locally-sourced basalt. Non-flammable, pretty, and slippery when wet.",
		"A soft and fluffy carpet made from dyed silicone. Non-flammable, pretty, and quite comfortable.",
		"Creates a set amount of money per second.",
		"Creates a set amount of a set fluid per second. Temperature can be adjusted as well.",
		"Allows for two different reinforced pipelines to cross over each other.",
		"Allows for two different large pipelines to cross over each other.",
		"A strip of high-visibility dyed polycarbonate platic, used for marking hazardous zones.",
		"The input of a modular condenser. Accepts steam of any temperature.",
		"Cools the contained steam using an electric fan.",
		"Cools the contained steam using an input of cold water.",
		"Outputs condensed water.",
		"Intakes fresh steam and feeds it to the rest of the turbine.",
		"Expands the turbine, and generates torque at the cost of steam energy.",
		"The last item in a turbine. Outputs low-temperature steam."
	};
	const std::vector<std::string> Machine_Comments = {
		"it can't transport fluorine, but that's okay because we never liked that diva of an element anyways.",
		"it's literally just a pretty valve.",
		"a wonderful place to put junk mail!",
		"free energy that might even power a single desk lamp!",
		"a technician actually got paid to make this. be nice.",
		"half the sub captains drink salted coffee.",
		"turns mystery fluids into cleaner mystery fluids.",
		"it's safe, but i still wouldn't sit on it.",
		"please don't swim here. for both your sake and mine.",
		"saltwater is not an acquired taste, contrary to what sub crews tell you.",
		"basically a fancy box of green sludge.",
		"a tiny home, but it's more fun because there's a gun rack!",
		"the filters get kinda icky after a while, so it's best to have the interns clean it out.",
		"it monitors fish, so it's kinda like their equivalent of 1984.",
		"a technician legitimately woke up and thought making a valve that spits out fish would be a good idea.",
		"i sometimes put my dinner leftovers in here.",
		"it makes water flammable! it does other things too, but that was the most enjoyable function i found.",
		"boring fluids go in, silly chemicals come out. need i say more?",
		"..--- -.- .... --.. / -.. .. ...- .-",
		"smells nice, looks pretty, and stays quiet. it's pretty much the opposite of PR employees.",
		"gun? more like 40×399mm fun!",
		"kinda like a hairtie, but for wires!",
		"it looks complex to operate, but in reality all it does is pump water down then back up.",
		"apparently you can shove a lot more liquid in a pipe if you just strip away the protective lining!",
		"it has way more pipes than it really needs.",
		"i think you can see where all of our funding went.",
		"easy to clean and quite scratch resistant too. it's a janitor's dream.",
		"for carpet pretty much woven from industrial-grade insulation, it's surprisingly sit to stand on.",
		"MONEY!!!",
		"LIQUIDS!!!",
		"it's literally just two pipes slapped on top of each other.",
		"same as the reinforced intersection, but without the protective lining.",
		"studies prove that placing a visible border on the floor makes people think twice before"
			" crossing it. studies also prove that whoever cares about that little fact is a nerd.",
		"apparently one steam input just wasn't enough.",
		"they should kinda put a grate over the fan, but then again, nobody in their right mind"
			" would jump into rapidly-spinning fan blades.",
		"[under construction]",
		"[to be added]",
		"typing on a console positioned directly next to a high voltage cable anchor is certainly an... experience.",
		"[tba]",
		"[tba]"
	};
	const std::vector<int> Machine_Taxes = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1
	};
	const std::vector<std::vector<int>> Item_Labels = {
		{ Submarine_Dock, Cable_Node },
		{ Ram_Pump },
		{ Algae_Bed },
		{ Filtration_Plant, Distillery, Electrolytic_Cell, Fluid_Mixer, Heat_Exchanger },
		{ Piezo_Generator, Bio_Generator, Geo_Well },
		{ Flowerpot, Ammunition_Shelf },
		{ Incinerator, Signal_Tower, Basic_Scrubber },
		{ Command_Platform }
	};
	const std::vector<std::string> Categories = {
		"Logistics",
		"Extraction",
		"Cultivation",
		"Processing",
		"Generation",
		"Decoration",
		"Other",
		"Special"
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
	const std::vector<std::string> Subcategory_Names = {
		"Modular Spawning Pool",
		"Flooring",
		"Reinforced",
		"Large",
		"Modular Condenser",
		"Modular Turbine"
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
	std::vector<SDL_Texture*> Machine_Sprites = { };
	std::vector<SDL_FRect> Machine_Rectangles = { };
	const std::vector<std::string> Days = { "Mon", "Tues", "Wednes", "Thurs", "Fri", "Satur", "Sun" };
	std::vector<std::vector<std::string>> TT_Texts = {
		{ "Sell Exports" },
		{ }
	};
	std::vector<std::vector<std::vector<std::string>>> TT_Parameters = {
		{ { "transmit", "REQUEST_EXPORT" } },
		{ }
	};
	std::vector<std::vector<int>> TT_Types = {
		{ Execute },
		{ }
	};
	const std::vector<std::vector<int>> Supported_Resolutions = { { 640, 360 }, { 1280, 720 }, { 1920, 1080 },
		{ 2560, 1440 }, { 3200, 1800 }, { 3840, 2160 } };
	const std::vector<int> Heating_Machines = { Incinerator, Geo_Well };//unused
	unsigned int Machine_Count;
};

struct Data {
public:
	bool CMD_Placed = false;
	int Version = 5;
	int Time = 0;
	int Day = 0;
	std::vector<double> Data_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	std::vector<double> Settings_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	std::vector<double> Animation_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	int Visual_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	int Connection_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	int Behaviour_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	int Wiring_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	int Plumbing_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	int Items_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	int Temperature_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	long double Funds = 0;
};

struct Settings {
public:
	bool AA_Temporary = true;
	bool VS_Temporary = false;
	int Fullscreen = 0;
	int Screen_Size = 0;
	int Anti_Aliasing = 1;
	int VSync = 0;
	int Volume = 50;
	int Raw_FPS = 2;
};

struct Textures {
public:
	Texture3_Array Item_Labels;
	Texture3_Array Subcategories;
	Texture3_Array Subcontents;
	Texture2_Array New;
	Texture2_Array Load;
	Texture2_Array Clear;
	Texture2_Array Cap_Button;
	Texture2_Array Categories;
	Texture_Array Error_Exit;
	Texture2_Array MSP_Buttons;
	Texture2_Array SD_Buttons;
	Texture2_Array HX_Buttons;
	Texture3_Array TT_Buttons;
	Texture2_Array MT_Buttons;
	Texture_Array R_Pipe;
	Texture_Array L_Pipe;
	Texture_Array MS_Pool;
	Texture_Array Arrow;
	Texture_Array S_Dock;
	Texture_Array Tunnel;
	Texture_Array Return;
	Texture_Array New_Game;
	Texture_Array Settings;
	Texture_Array Update_Logs;
	Texture_Array Credits;
	Texture_Array Quit_Game;
	Texture_Array Apply;
	Texture_Array Cancel;
	Texture_Array Next_Day;
	Texture_Array Cap;
	Texture2_Array Anti_Aliasing;
	Texture2_Array V_Sync;
	Texture2_Array Sort;
	Texture2_Array TBW_Texture;
	Texture_Array Quirk;
	Texture_Array Quirk_Label;
	Texture2_Array Tutorials;
	Texture2_Array Cheats;
	Texture_Array Clear_Tutorial;
	Texture_Array Settings_Label;
	Texture_Array Save_Settings;
	Texture_Array Tool;
	Texture_Array Help_Content;
	SDL_Texture* Recipe_Content;
	Texture_Array Door;
	SDL_Texture* Logo;
	SDL_Texture* Crosshair;
	SDL_Texture* Cursor;
	SDL_Texture* Cursor_Core;
	SDL_Texture* Sapling;
	SDL_Texture* Node;
	SDL_Texture* Path_Arrow;
	SDL_Texture* Log_Background;
	SDL_Texture* Saveloader;
	SDL_Texture* RFlash;
	SDL_Texture* Floor_Texture;
	SDL_Texture* Frame_Texture;
	SDL_Texture* Tile_Texture;
	Texture_Array R_Pump;
	Texture2_Array Incinerator;
	SDL_Texture* P_Generator;
	Texture_Array F_Plant;
	Texture2_Array B_Generator;
	Texture2_Array Distillery;
	Texture2_Array G_Bed;
	Texture_Array C_Platform;
	Texture_Array B_Scrubber;
	SDL_Texture* MS_Controller;
	SDL_Texture* MS_Output;
	SDL_Texture* MS_Input;
	Texture_Array E_Plant;
	Texture2_Array F_Mixer;
	Texture_Array T_Tower;
	SDL_Texture* Flowerpot;
	Texture_Array A_Shelf;
	SDL_Texture* C_Node;
	Texture_Array G_Well;
	Texture_Array H_Exchanger;
	SDL_Texture* P_Wood;
	SDL_Texture* B_Tile;
	SDL_Texture* S_Carpet;
	SDL_Texture* H_Strip;
	SDL_Texture* M_Generator;
	SDL_Texture* F_Generator;
	Texture_Array R_Intersection;
	Texture_Array L_Intersection;
	Texture_Array SC_Input;
	Texture_Array SCH_Sink;
	Texture_Array SC_Transferor;
	Texture_Array SC_Output;
	Texture_Array ST_Input;
	Texture2_Array STIT_Block;
	Texture2_Array ST_Output;
	SDL_Texture* Scrap;
	SDL_Texture* Help_Sidebutton;
	SDL_Texture* Save_Sidebutton;
	SDL_Texture* Recipe_Sidebutton;
	SDL_Texture* Exit_Sidebutton;
	Texture_Array Submarine;
	Texture2_Array Confirmation;
	Texture_Array Pyramid;
	SDL_Texture* Mesh;
	Texture_Array Fire;
	Texture_Array None;
};

struct Rectangles {
public:
	Rect3_Array Item_Labels;
	Rect3_Array Subcategories;
	Rect3_Array Subcontents;
	Rect2_Array New;
	Rect2_Array Load;
	Rect2_Array Clear;
	Rect2_Array Categories;
	Rect_Array Error_Exit;
	Rect2_Array MSP_Buttons;
	Rect2_Array SD_Buttons;
	Rect2_Array HX_Buttons;
	Rect2_Array MT_Buttons;
	Rect3_Array TT_Buttons;
	Rect_Array Tunnel;
	Rect_Array Return;
	Rect_Array New_Game;
	Rect_Array Settings;
	Rect_Array Update_Logs;
	Rect_Array Credits;
	Rect_Array Quit_Game;
	Rect_Array Apply;
	Rect_Array Cancel;
	Rect_Array Next_Day;
	Rect2_Array Anti_Aliasing;
	Rect2_Array V_Sync;
	Rect2_Array Sort;
	Rect2_Array TBW_Rectangle;
	Rect2_Array Tutorials;
	Rect_Array Tutorial_Hitbox;
	Rect2_Array Cheats;
	Rect_Array Clear_Tutorial;
	Rect_Array Settings_Label;
	Rect_Array Save_Settings;
	SDL_FRect Tool[5];
	SDL_FRect Help_Content[2];
	SDL_FRect Recipe_Content;
	SDL_FRect Door[2];
	SDL_FRect Logo;
	SDL_FRect Tile_1x1;
	SDL_FRect Tile_1x2;
	SDL_FRect Tile_2x1;
	SDL_FRect Tile_2x2;
	SDL_FRect Tile_2x3;
	SDL_FRect Tile_3x2;
	SDL_FRect Tile_3x3;
	SDL_FRect Tile_3x4;
	SDL_FRect Tile_4x3;
	SDL_FRect Tile_4x6;
	SDL_FRect Tile_6x4;
	SDL_FRect Tile_6x8;
	SDL_FRect Tile_8x6;
	SDL_FRect Cap;
	SDL_FRect Cap_Button;
	Rect_Array Cap_Hitbox;
	SDL_FRect Sapling;
	SDL_FRect Node;
	SDL_FRect RFlash;
	SDL_FRect Log_Background;
	SDL_FRect Saveloader;
	SDL_FRect Help;
	SDL_FRect Save;
	SDL_FRect Recipe;
	SDL_FRect Exit;
	SDL_FRect Submarine;
	Rect2_Array Confirmation;
};

struct Colors {
public:
	SDL_Color Abyss_Black = { 0, 0, 0 };
	SDL_Color Pure_White = { 255, 255, 255 };
	SDL_Color Light_Grey = { 235, 240, 240 };
	SDL_Color Mid_Grey = { 180, 180, 180 };
	SDL_Color Clean_Grey = { 155, 155, 155 };
	SDL_Color Dark_Grey = { 105, 110, 105 };
	SDL_Color Reinforced_Grey = { 42, 42, 42 };
	SDL_Color Cherry_Blossom = { 255, 183, 197 };
	SDL_Color Copper_Wire = { 184, 115, 51 };
	SDL_Color Carnage_Pink = { 204, 163, 185 };
	SDL_Color Hostile_Red = { 187, 10, 30 };
	SDL_Color Ocean = { 6, 66, 116 };
};

struct Fonts {
public:
	TTF_Font* Logo_Font;
	TTF_Font* Large_Font;
	TTF_Font* Text_Font;
	TTF_Font* Halftext_Font;
	TTF_Font* Subtext_Font;
	TTF_Font* Microtext_Font;
	TTF_Font* Terminal_Font;
};

struct Keybinds {
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

struct Temporary {
public:
	bool Settings_Changed = false;
	int First_Modular_Requirement = 0;
	int Second_Modular_Requirement = 0;
	int Dialogue_Position = 0;
	int Ticker_Target = 0;
	int Ticker_Position = 0;
	int Ticker_Frames = 0;
	int Tutorial_Step = LDE_INVALID;
	std::vector<int> Tutorial_Size = { };
	std::vector<int> Tutorial_Offset = { };
	int Temporary_FPS;
	std::vector<double> FPS_Query = { };
	double Scroll_Percent = 0;
	int Dialogue_Maximum = 0;
	std::vector<bool> Log_Inversions = { true, false, false };
	std::vector<std::vector<int>> Docks = { };
	std::vector<int> Submarine_Position = { LDE_INVALID, LDE_INVALID };
	int Submarine_Side = 1;
	int Submarine_Phase = LDE_INVALID;
	double Submarine_Offset = 0;
	double Submarine_Vertical = 0;
	std::vector<int> First_Coordinate = { 0, 0 };
	std::vector<SDL_FRect> Query = { };
	std::vector<int> ID_Query = { };
	std::vector<SDL_Color> Color_Query = { };
};

struct Cache {
public:
	int Wire_State = LDE_INVALID;
	Texture_Array Wire_Cache;
	SDL_FRect Wire_Box;
	SDL_Texture* Blueprint_Cache;
	Texture2_Array Log_Cache;
	std::vector<std::vector<SDL_FRect>> Log_Rectangles;
};

struct Preconfigurations {
public:
	const std::vector<Point> EP_Inputs[4] = {
		{ { 1, 1 } },
		{ { 0, 1 } },
		{ { 1, 0 } },
		{ { 1, 1 } }
	};
	const std::vector<Point> EP_Outputs[4] = {
		{ { 0, 0 }, { 1, 0 }, { 2, 0 } },
		{ { 1, 0 }, { 1, 1 }, { 1, 2 } },
		{ { 0, 1 }, { 1, 1 }, { 2, 1 } },
		{ { 0, 0 }, { 0, 1 }, { 0, 2 } }
	};
	const std::vector<Point> FM_Inputs[4] = {
		{ { 0, 0 }, { 0, 1 }, { 0, 2 }, { 2, 0 }, { 2, 1 }, { 2, 2 } },
		{ { 0, 2 }, { 1, 2 }, { 2, 2 }, { 0, 0 }, { 1, 0 }, { 2, 0 } },
		{ { 2, 0 }, { 2, 1 }, { 2, 2 }, { 0, 0 }, { 0, 1 }, { 0, 2 } },
		{ { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 2 }, { 1, 2 }, { 2, 2 } }
	};
	const std::vector<Point> FM_Outputs[4] = {
		{ { 1, 0 }, { 1, 2 } },
		{ { 0, 1 }, { 2, 1 } },
		{ { 1, 2 }, { 1, 0 } },
		{ { 2, 1 }, { 0, 1 } }
	};
	const std::vector<Point> BG_Inputs[4] = {
		{ { 0, 2 } },
		{ { 0, 0 } },
		{ { 2, 0 } },
		{ { 2, 2 } }
	};
	const std::vector<Point> I_Inputs[4] = {
		{ { 0, 1 }, { 1, 0 } },
		{ { 1, 0 }, { 2, 1 } },
		{ { 2, 1 }, { 1, 2 } },
		{ { 1, 2 }, { 0, 1 } }
	};
	const std::vector<Point> I_Outputs[4] = {
		{ { 2, 1 }, { 1, 2 } },
		{ { 1, 2 }, { 0, 1 } },
		{ { 0, 1 }, { 1, 0 } },
		{ { 1, 0 }, { 2, 1 } }
	};
	const std::vector<Point> D_Inputs[4] = {
		{ { 0, 0 } },
		{ { 1, 0 } },
		{ { 1, 1 } },
		{ { 0, 1 } }
	};
	const std::vector<Point> D_Outputs[4] = {
		{ { 1, 0 }, { 1, 1 } },
		{ { 1, 1 }, { 0, 1 } },
		{ { 0, 1 }, { 0, 0 } },
		{ { 0, 0 }, { 1, 0 } }
	};
	const std::vector<Point> STI_Inputs[4] = {
		{ { 0, 2 } },
		{ { 0, 0 } },
		{ { 1, 0 } },
		{ { 2, 1 } }
	};
	const std::vector<Point> GB_Outputs[4] = {
		{ { 0, 2 }, { 1, 2 } },
		{ { 0, 0 }, { 0, 1 } },
		{ { 0, 0 }, { 1, 0 } },
		{ { 2, 0 }, { 2, 1 } }
	};
};

struct UI {
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
	std::vector<int> Slider_Positions = { 0, 0, 0, 0, 0, 50, 0, 0, 5, 0, 13, 0, 0, 0 };
	std::vector<int> Default_Positions = { 0 };
	std::string Terminal_Entry;
	SDL_FPoint Tile_Centrepoint = { 0, 0 };
	bool Animation_Locked = false;
	bool Building = false;
	bool Sprinting = false;
	bool Terminal_Clearing;
	double Camera_X = -140;
	double Camera_Y = 0;
	double Ocean_Cycle = 0;
	double Node_Cycle = 0;
	double Movespeed = 120;
	long double Log_Offset = 0;
	std::vector<long double> Log_Heights;
	float X_Mouse_Position = 0;
	float Y_Mouse_Position = 0;
	Point Target_Tile = { 0, 0 };
	int Prompt_Identifier = LDE_INVALID;
	int Subprompt_Identifier = LDE_INVALID;
	int Tool = LDE_INVALID;
	int UD_Input = LDE_INVALID;
	int LR_Input = LDE_INVALID;
	int Queried_Price = 0;
	int Engagement = 0;
	int UI_Tab = 1;
	int Subtab = 0;
	int UI_Selection = 0;
	int Frame_Rate = 60;
	int Time_Frames = 0;
	int Maximum_Time_Frames = 0;
	int Subtime_Frames = 0;
	int Maximum_Subtime_Frames = 0;
	int Placing_Item = 1;
	int Placing_Rotation = 0;
	int Save_Frames = 0;
	int Map_X = 0;
	int Map_Y = 0;
	std::vector<double> Effects = std::vector<double>(1, 0);
	int Registering_Keybind = LDE_INVALID;
};

extern Core Core_Access;
extern Metadata Metadata_Access;
extern Data Data_Access;
extern Settings Settings_Access;
extern Textures Textures_Access;
extern Rectangles Rectangles_Access;
extern Colors Colors_Access;
extern Fonts Fonts_Access;
extern Keybinds Keybinds_Access;
extern Temporary Temporary_Access;
extern Cache Cache_Access;
extern UI UI_Access;
extern Preconfigurations Preconfigurations_Access;

void Clear_Renderer();

void Set_Renderer_Color(const SDL_Color &Color);

bool Detect_Mouse_Collision(const SDL_FRect &Target);

SDL_FRect Buffer_Rectangle(const SDL_FRect &Source, const int X, const int Y);

bool Check_Clearance(const int X, const int Y, const int W, const int H);

void Fill_Clearance(const int Identifier, const int X, const int Y, const int W, const int H);

void Update_Tilestack(bool X_Lock, int X, bool Y_Lock, int Y);

std::string Abbreviate_Number(long double Number);

int Get_Depth(double Number);

std::string Truncate(double Number, int Depth);

Texture_Array Load_Button(TTF_Font* Font, std::string Text, Rect_Array &Rectangles,
	SDL_Color Primary_Color, SDL_Color Secondary_Color);

void Render_Button(const Texture_Array &Button, const Rect_Array &Hitbox, int Selection,
	SDL_Color Underline_Color = Colors_Access.Cherry_Blossom);

void Reload_Commandlist(Texture3_Array &Commandlist, Rect3_Array &Boxlist,
	std::vector<std::vector<std::string>> Contents);

void Recache_TT_Commands();

void Preload_Fonts();

void Preload_Assets();

void Cleanup_Assets();

void Render_Dynamic_Text(TTF_Font* Selected_Font, std::string Text, SDL_Color Color, int X, int Y);

int Render_Rich_Text(TTF_Font* Selected_Font, std::string Raw_Text, int X, int Y,
	bool Inverted = false, bool Disabled = false);

void Render_Outline(SDL_FRect Rectangle, SDL_Color Color, int Multiplier = 1);
std::vector<Point> Return_Nodes(const int Column, const int Row, const int Rotation,
	const std::vector<Point>(&Preconfiguration)[4]);
int Visual_To_ID(const int Identifier);
int Visual_To_Rotation(const int Identifier);
void ID_To_Size(const int ID, const int Rotation, int &X, int &Y);
void Render_Box(int X, int Y, int W, int H, SDL_Color Inner_Color, SDL_Color Outer_Color);