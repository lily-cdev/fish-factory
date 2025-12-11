#include <Core.h>
#include <Preloader.h>
#include <Items.h>
#include <Legacy.hpp>
#include <Connectables.h>
#include <Data_Handler.h>

void Preclear_Temporaries() {
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			Data_Access.Animation_Grid[X][Y].clear();
			for (int Counter = 0; Counter < 3; Counter++) {
				Data_Access.Animation_Grid[X][Y].push_back(LDE_INVALID);
			}
		}
	}
}

auto Convert_Simple_Grid(int Input[LDE_GRIDSIZE][LDE_GRIDSIZE]) {
	nlohmann::json Grid = nlohmann::json::array();
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		nlohmann::json Data_Row = nlohmann::json::array();
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Data_Row.push_back(Input[Column][Row]);
		}
		Grid.push_back(Data_Row);
	}
	return Grid;
}

auto Convert_Complex_Grid(std::vector<double> Input[LDE_GRIDSIZE][LDE_GRIDSIZE]) {
	nlohmann::json Grid = nlohmann::json::array();
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		nlohmann::json Data_Row = nlohmann::json::array();
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			nlohmann::json Data_Column = nlohmann::json::array();
			for (int Counter = 0; Counter < Input[Column][Row].size(); Counter++) {
				Data_Column.push_back(Input[Column][Row][Counter]);
			}
			Data_Row.push_back(Data_Column);
		}
		Grid.push_back(Data_Row);
	}
	return Grid;
}

void Recieve_Simple_Grid(nlohmann::json File, int Input[LDE_GRIDSIZE][LDE_GRIDSIZE]) {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Input[Column][Row] = File.at(Column).at(Row).get<int>();
		}
	}
}

void Recieve_Complex_Grid(nlohmann::json File, std::vector<double> Input[LDE_GRIDSIZE][LDE_GRIDSIZE], int Length) {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Input[Column][Row].clear();
			for (int Counter = 0; Counter < Length; Counter++) {
				Input[Column][Row].resize(Length);
				Input[Column][Row][Counter] = File.at(Column).at(Row).at(Counter).get<int>();
			}
		}
	}
}

void to_json(nlohmann::json &File, const Wire &Input) {
	File = nlohmann::json{
		{ "Filled", Input.Filled },
		{ "First_X", Input.First_X },
		{ "First_Y", Input.First_Y },
		{ "Second_X", Input.Second_X },
		{ "Second_Y", Input.Second_Y }
	};
}

void to_json(nlohmann::json &File, const Pipe &Input) {
	File = nlohmann::json{
		{ "Filled", Input.Filled },
		{ "First_X", Input.First_X },
		{ "First_Y", Input.First_Y },
		{ "Second_X", Input.Second_X },
		{ "Second_Y", Input.Second_Y },
		{ "X_Offset", Input.X_Offset },
		{ "Y_Offset", Input.Y_Offset },
		{ "Orientation", Input.Orienation }
	};
}

void to_json(nlohmann::json &File, const Legacy_Item_Stack &Input) {
	File = nlohmann::json{
		{ "Identifier", Input.Identifier },
		{ "Display_Name", Input.Display_Name },
		{ "Sale_Value", Input.Sale_Value },
		{ "Toxicity", Input.Toxicity },
		{ "Temperature", Input.Temperature },
		{ "Chemical_Energy", Input.Chemical_Energy }
	};
}

void from_json(const nlohmann::json &File, Wire &Output) {
	File.at("Filled").get_to(Output.Filled);
	File.at("First_X").get_to(Output.First_X);
	File.at("First_Y").get_to(Output.First_Y);
	File.at("Second_X").get_to(Output.Second_X);
	File.at("Second_Y").get_to(Output.Second_Y);
}

void from_json(const nlohmann::json &File, Pipe &Output) {
	File.at("Filled").get_to(Output.Filled);
	File.at("First_X").get_to(Output.First_X);
	File.at("First_Y").get_to(Output.First_Y);
	File.at("Second_X").get_to(Output.Second_X);
	File.at("Second_Y").get_to(Output.Second_Y);
	File.at("X_Offset").get_to(Output.X_Offset);
	File.at("Y_Offset").get_to(Output.Y_Offset);
	File.at("Orientation").get_to(Output.Orienation);
}

void from_json(const nlohmann::json &File, Legacy_Item_Stack &Output) {
	File.at("Identifier").get_to(Output.Identifier);
	File.at("Display_Name").get_to(Output.Display_Name);
	File.at("Toxicity").get_to(Output.Toxicity);
	File.at("Temperature").get_to(Output.Temperature);
	File.at("Chemical_Energy").get_to(Output.Chemical_Energy);
}

auto Convert_Items_Grid(Legacy_Item_Stack Input[LDE_GRIDSIZE][LDE_GRIDSIZE]) {
	nlohmann::json Grid = nlohmann::json::array();
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		nlohmann::json Data_Row = nlohmann::json::array();
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Data_Row.push_back(Input[Column][Row]);
		}
		Grid.push_back(Data_Row);
	}
	return Grid;
}

void Recieve_Items_Grid(nlohmann::json File, Legacy_Item_Stack Input[LDE_GRIDSIZE][LDE_GRIDSIZE]) {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Input[Column][Row] = File.at(Column).at(Row).get<Legacy_Item_Stack>();
		}
	}
}

bool Save_Data(int Slot) {
	Clear_File("Assets/Data/Slot" + std::to_string(Slot));
	nlohmann::json File = nlohmann::json {
		{ "Version", Data_Access.Version },
		{ "Funds", Data_Access.Funds },
		{ "Time", Data_Access.Time },
		{ "Day", Data_Access.Day },
		{ "CMD Placed", Data_Access.CMD_Placed }
	};
	File["Visual Grid"] = Convert_Simple_Grid(Data_Access.Visual_Grid);
	File["Connection Grid"] = Convert_Simple_Grid(Data_Access.Connection_Grid);
	File["Behaviour Grid"] = Convert_Simple_Grid(Data_Access.Behaviour_Grid);
	File["Wiring Grid"] = Convert_Simple_Grid(Data_Access.Wiring_Grid);
	File["Plumbing Grid"] = Convert_Simple_Grid(Data_Access.Plumbing_Grid);
	File["Data Grid"] = Convert_Complex_Grid(Data_Access.Data_Grid);
	File["Settings Grid"] = Convert_Complex_Grid(Data_Access.Settings_Grid);
	File["Wires List"] = Wires_List;
	File["Pipes List"] = Pipes_List;
	File["Items List"] = Convert_Simple_Grid(Data_Access.Items_Grid);
	File["Temp List"] = Convert_Simple_Grid(Data_Access.Temperature_Grid);
	std::string Path = "Assets/Data/Slot" + std::to_string(Slot) + ".json";
	std::ofstream Destination(Path.c_str());
	if (Destination) {
		Destination << File.dump();
		Destination.close();
	} else {
		return false;
	}
	return true;
}

bool Load_Data(int Slot) {
	nlohmann::json File;
	std::string Path = "Assets/Data/Slot" + std::to_string(Slot) + ".json";
	std::ifstream Source(Path.c_str());
	if (Source) {
		Source >> File;
	} else {
		return false;
	}
	Source.close();
	File.at("Version").get_to(Data_Access.Version);
	File.at("Funds").get_to(Data_Access.Funds);
	Recieve_Simple_Grid(File.at("Visual Grid"), Data_Access.Visual_Grid);
	Recieve_Simple_Grid(File.at("Connection Grid"), Data_Access.Connection_Grid);
	Recieve_Simple_Grid(File.at("Behaviour Grid"), Data_Access.Behaviour_Grid);
	Recieve_Simple_Grid(File.at("Wiring Grid"), Data_Access.Wiring_Grid);
	Recieve_Simple_Grid(File.at("Plumbing Grid"), Data_Access.Plumbing_Grid);
	Recieve_Complex_Grid(File.at("Data Grid"), Data_Access.Data_Grid, 7);
	Wires_List = File.at("Wires List").get<std::vector<Wire>>();
	Pipes_List = File.at("Pipes List").get<std::vector<Pipe>>();
	if (Data_Access.Version < 1) {
		Data_Access.Version = 1;
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				Legacy_Item_Stack Blank_Item;
				Blank_Item.Identifier = LDE_INVALID;
				Legacy_Item_Grid[Column][Row] = Blank_Item;
			}
		}
	} else if (Data_Access.Version < 3) {
		Recieve_Items_Grid(File.at("Items List"), Legacy_Item_Grid);
	}
	if (Data_Access.Version < 2) {
		Recieve_Complex_Grid(File.at("Settings Grid"), Data_Access.Settings_Grid, 3);
		Data_Access.Version = 2;
		Data_Access.Time = 0;
		Data_Access.Day = 0;
		Data_Access.CMD_Placed = false;
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				for (int Counter = 0; Counter < 5; Counter++) {
					Data_Access.Settings_Grid[Column][Row].push_back(LDE_INVALID);
				}
			}
		}
	} else if (Data_Access.Version < 5) {
		File.at("Time").get_to(Data_Access.Time);
		File.at("Day").get_to(Data_Access.Day);
		File.at("CMD Placed").get_to(Data_Access.CMD_Placed);
	}
	if (Data_Access.Version < 3) {
		Data_Access.Version = 3;
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				Data_Access.Items_Grid[Column][Row] = Legacy_Item_Grid[Column][Row].Identifier;
			}
		}
	} else {
		Recieve_Simple_Grid(File.at("Items List"), Data_Access.Items_Grid);
	}
	if (Data_Access.Version < 4) {
		Data_Access.Version = 4;
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				Data_Access.Temperature_Grid[Column][Row] = Get_Item(Column, Row).Temperature;
			}
		}
	} else {
		Recieve_Simple_Grid(File.at("Temp List"), Data_Access.Temperature_Grid);
	}
	if (Data_Access.Version < 5) {
		Data_Access.Version = 5;
		Recieve_Complex_Grid(File.at("Settings Grid"), Data_Access.Settings_Grid, 8);
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				for (int Counter = 0; Counter < 8; Counter++) {
					Data_Access.Settings_Grid[Column][Row].push_back(LDE_INVALID);
				}
			}
		}
	} else {
		Recieve_Complex_Grid(File.at("Settings Grid"), Data_Access.Settings_Grid, 16);
	}
	Preclear_Temporaries();
	return true;
}

bool Update_Metadata() {
	int Index = SDL_GetDisplayForWindow(Core_Access.Application_Window);
	const SDL_DisplayMode* Display = SDL_GetDesktopDisplayMode(Index);
	Metadata_Access.Monitor_Size = std::to_string(Display->w) + "x" + std::to_string(Display->h);
	std::vector<std::string> Resolution_Names = { "nHD", "HD", "FHD", "QHD", "QHD+", "4K" };
	for (int Counter = 0; Counter < Metadata_Access.Supported_Resolutions.size(); Counter++) {
		if (Display->w == Metadata_Access.Supported_Resolutions[Counter][0] &&
			Display->h == Metadata_Access.Supported_Resolutions[Counter][1]) {
			Metadata_Access.Monitor_Size = Metadata_Access.Monitor_Size + " (" + Resolution_Names[Counter] + ")";
			break;
		}
	}
	Metadata_Access.Monitor_Size = "Detected Resolution: " + Metadata_Access.Monitor_Size;
	nlohmann::json File;
	std::string Path = "Assets/Data/Metadata.json";
	std::ifstream Source(Path.c_str());
	if (Source) {
		Source >> File;
	} else {
		return false;
	}
	Source.close();
	Metadata_Access.Logs.clear();
	Metadata_Access.Logs.resize(3);
	File.at("Changelog").get_to(Metadata_Access.Logs[Changelog]);
	File.at("Crediting").get_to(Metadata_Access.Logs[Credits]);
	File.at("Licensing").get_to(Metadata_Access.Logs[Legal]);
	return true;
}

void Get_Filesizes() {
	for (int Counter = 1; Counter < 5; Counter++) {
		std::string Path = "Assets/Data/Slot" + std::to_string(Counter) + ".json";
		std::ifstream File(Path, std::ios::binary | std::ios::ate);
		Core_Access.Save_Filesizes[Counter - 1] = static_cast<double>(File.tellg());
		File.close();
	}
}

void Clear_File(std::string Path) {
	Path = Path + ".json";
	std::ofstream File(Path, std::ios::trunc);
	File.close();
}

bool Save_Settings() {
	nlohmann::json Keybinds_Vector = nlohmann::json::array();
	for (int Counter = 0; Counter < 14; Counter++) {
		Keybinds_Vector.push_back(static_cast<int>(Keybinds_Access.Keybind_List[Counter]));
	}
	Clear_File("Assets/Data/Settings");
	nlohmann::json File = nlohmann::json {
		{ "Version", 3 },
		{ "Scale_Quality", Settings_Access.Anti_Aliasing },
		{ "V_Sync", Settings_Access.VSync },
		{ "Fullscreen", Settings_Access.Fullscreen },
		{ "Screen_Size", Settings_Access.Screen_Size },
		{ "Volume", Settings_Access.Volume },
		{ "FPS_Cap", Settings_Access.Raw_FPS }
	};
	File["Keybinds"] = Keybinds_Vector;
	std::ofstream Destination("Assets/Data/Settings.json");
	if (Destination) {
		Destination << File.dump();
		Destination.close();
	} else {
		return false;
	}
	return true;
}

void Load_Settings() {
	std::ifstream File("Assets/Data/Settings.json", std::ios::binary | std::ios::ate);
	if (File.tellg() > 0) {
		File.close();
		nlohmann::json Save_File;
		std::ifstream Source("Assets/Data/Settings.json");
		Source >> Save_File;
		Source.close();
		int Version = 0;
		Save_File.at("Version").get_to(Version);
		if (Version > 2) {
			Save_File.at("Scale_Quality").get_to(Settings_Access.Anti_Aliasing);
			Save_File.at("V_Sync").get_to(Settings_Access.VSync);
			Save_File.at("Fullscreen").get_to(Settings_Access.Fullscreen);
			Save_File.at("Screen_Size").get_to(Settings_Access.Screen_Size);
			Save_File.at("Volume").get_to(Settings_Access.Volume);
			Save_File.at("FPS_Cap").get_to(Settings_Access.Raw_FPS);
			for (int Counter = 0; Counter < 14; Counter++) {
				Keybinds_Access.Keybind_List[Counter] = Save_File.at("Keybinds").at(Counter).get<int>();
			}
		} else {
			Clear_File("Assets/Data/Settings");
		}
	} else {
		File.close();
		int Index = SDL_GetDisplayForWindow(Core_Access.Application_Window);
		const SDL_DisplayMode* Display = SDL_GetDesktopDisplayMode(Index);
		for (int Counter = 0; Counter < Metadata_Access.Supported_Resolutions.size(); Counter++) {
			if (Display->w >= Metadata_Access.Supported_Resolutions[Counter][0] &&
				Display->h >= Metadata_Access.Supported_Resolutions[Counter][1]) {
				Settings_Access.Screen_Size++;
			} else {
				break;
			}
		}
		if (Settings_Access.Screen_Size == 0) {
			Settings_Access.Screen_Size = 1;
		}
	}
}

void Clear_Settings() {
	UI_Access.Slider_Positions[0] = Settings_Access.Screen_Size - 1;
	UI_Access.Slider_Positions[4] = Settings_Access.Raw_FPS;
	UI_Access.Slider_Positions[5] = Settings_Access.Volume;
	UI_Access.Slider_Positions[6] = Settings_Access.Fullscreen;
	Settings_Access.AA_Temporary = static_cast<bool>(Settings_Access.Anti_Aliasing);
	Settings_Access.VS_Temporary = static_cast<bool>(Settings_Access.VSync);
	for (int Counter = 0; Counter < Keybinds_Access.Keybind_List.size(); Counter++) {
		Keybinds_Access.Keybind_Settings[Counter] = Keybinds_Access.Keybind_List[Counter];
	}
}

void Recalibrate_Settings() {
	Settings_Access.Screen_Size = UI_Access.Slider_Positions[0] + 1;
	Settings_Access.Raw_FPS = UI_Access.Slider_Positions[4];
	Settings_Access.Volume = UI_Access.Slider_Positions[5];
	Settings_Access.Fullscreen = UI_Access.Slider_Positions[6];
	Settings_Access.Anti_Aliasing = static_cast<int>(Settings_Access.AA_Temporary);
	Settings_Access.VSync = static_cast<int>(Settings_Access.VS_Temporary);
	for (int Counter = 0; Counter < Keybinds_Access.Keybind_List.size(); Counter++) {
		Keybinds_Access.Keybind_List[Counter] = Keybinds_Access.Keybind_Settings[Counter];
	}
	Reload_All();
}

void Preload_Noise() {
	Textures_Access.None.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 10));
	Textures_Access.None.Length = 10;
	uint32_t Lookup_Table[32];
	const SDL_PixelFormatDetails* Pixel_Format = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
	for (int Counter = -16; Counter <= 16; Counter++) {
		if (Counter != 0) {
			int Offset = 16;
			if (Counter > 0) {
				Offset = 15;
			}
			Lookup_Table[Counter + Offset] = SDL_MapRGB(
				Pixel_Format, NULL,
				std::clamp(Colors_Access.Ocean.r + Counter, 0, 255),
				std::clamp(Colors_Access.Ocean.g + Counter, 0, 255),
				std::clamp(Colors_Access.Ocean.b + Counter, 0, 255)
			);
		}
	}
	SDL_Surface* None_Surfaces[10];
	std::vector<std::thread> Threads;
	for (int Counter1 = 0; Counter1 < 10; Counter1++) {
		Threads.emplace_back([&, Counter1]{
			uint32_t Shade = static_cast<uint32_t>((std::chrono::duration_cast<
				std::chrono::seconds>(Clock::now().time_since_epoch()).count() * Counter1) % UINT8_MAX);
			SDL_Surface* Noise_Surface = SDL_CreateSurface(Settings_Access.Screen_Size * 1200,
				Settings_Access.Screen_Size * 1200, SDL_PIXELFORMAT_RGBA8888);
			SDL_LockSurface(Noise_Surface);
			uint32_t* Pixels = (uint32_t*)Noise_Surface->pixels;
			for (int Counter2 = 0; Counter2 < sqr_i(Settings_Access.Screen_Size *
				1200); Counter2++, Pixels++) {
				Shade = (Shade * 2891336453u) + 747796405u;
				Shade ^= Shade >> 16;
				*Pixels = Lookup_Table[(Shade & 31)];
			}
			SDL_UnlockSurface(Noise_Surface);
			None_Surfaces[Counter1] = Noise_Surface;
		});
	}
	for (std::thread &Thread : Threads) {
		Thread.join();
	}
	for (int Counter = 0; Counter < 10; Counter++) {
		Textures_Access.None.Data[Counter] = SDL_GenerateTextureFromSurface(
			Core_Access.Application_Renderer, None_Surfaces[Counter]);
		SDL_SetTextureScaleMode(Textures_Access.None.Data[Counter], SDL_SCALEMODE_NEAREST);
		SDL_SetTextureBlendMode(Textures_Access.None.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_DestroySurface(None_Surfaces[Counter]);
	}
	const SDL_Color Fire_Colors[4] = {
		{ 255, 140, 0 },
		{ 255, 163, 51 },
		{ 255, 205, 6 },
		{ 0, 0, 0 }
	};
	Textures_Access.Fire.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 10));
	Textures_Access.Fire.Length = 10;
	SDL_Surface* Fire_Surfaces[10];
	uint32_t Random = static_cast<uint32_t>((std::chrono::duration_cast<
		std::chrono::seconds>(Clock::now().time_since_epoch()).count()) & 255);
	for (int Counter1 = 0; Counter1 < 10; Counter1++) {
		Fire_Surfaces[Counter1] = SDL_CreateSurface(Settings_Access.Screen_Size * 40,
			Settings_Access.Screen_Size * 40, SDL_PIXELFORMAT_RGBA8888);
		SDL_LockSurface(Fire_Surfaces[Counter1]);
		uint32_t* Pixels = static_cast<uint32_t*>(Fire_Surfaces[Counter1]->pixels);
		for (int Counter2 = 0; Counter2 < sqr_i(Settings_Access.Screen_Size * 40); Counter2++) {
			Random = (Random * 2891336453u) + 747796405u;
			Random ^= Random >> 16;
			Pixels[Counter2] = SDL_MapRGB(Pixel_Format, NULL, Fire_Colors[(Random & 3)].r,
				Fire_Colors[(Random & 3)].g, Fire_Colors[(Random & 3)].b);
		}
		SDL_UnlockSurface(Fire_Surfaces[Counter1]);
		Textures_Access.Fire.Data[Counter1] = SDL_GenerateTextureFromSurface(
			Core_Access.Application_Renderer, Fire_Surfaces[Counter1]);
		SDL_SetTextureScaleMode(Textures_Access.Fire.Data[Counter1], SDL_SCALEMODE_NEAREST);
		SDL_SetTextureBlendMode(Textures_Access.Fire.Data[Counter1], SDL_BLENDMODE_BLEND);
		SDL_DestroySurface(Fire_Surfaces[Counter1]);
	}
}

void Render_Loadscreen() {
	Set_Renderer_Color(Colors_Access.Pure_White);
	SDL_RenderClear(Core_Access.Application_Renderer);
	Clear_Renderer();
	SDL_Surface* Text_Surface = TTF_RenderText_Blended(Fonts_Access.Logo_Font,
		"loading assets", 15, Colors_Access.Abyss_Black);
	SDL_FRect Pasting_Rectangle = {
		(Settings_Access.Screen_Size * 320.0f) - (Text_Surface->w / 2),
		(Settings_Access.Screen_Size * 180.0f) - (Text_Surface->h / 2),
		static_cast<float>(Text_Surface->w),
		static_cast<float>(Text_Surface->h)
	};
	SDL_Texture* Text_Texture = SDL_GenerateTextureFromSurface(
		Core_Access.Application_Renderer, Text_Surface);
	SDL_RenderTexture(Core_Access.Application_Renderer, Text_Texture,
		NULL, &Pasting_Rectangle);
	SDL_DestroySurface(Text_Surface);
	SDL_DestroyTexture(Text_Texture);
	SDL_RenderPresent(Core_Access.Application_Renderer);
	SDL_PumpEvents();
}

void Reload_All() {
	Clock::time_point Start = Clock::now();
	Metadata_Access.Machine_Count = Metadata_Access.Machine_Names.size();
	Preload_Recipes();
	Cleanup_Assets();
	SDL_SetWindowSize(Core_Access.Application_Window, 640 *
		Settings_Access.Screen_Size, 360 * Settings_Access.Screen_Size);
	Preload_Fonts();
	Render_Loadscreen();
	SDL_SetWindowPosition(Core_Access.Application_Window, 0, 0);
	UI_Access.Slider_Texts[9].resize(Preset_Items_Access.Item_List.size());
	for (int Counter = 0; Counter < Preset_Items_Access.Item_List.size(); Counter++) {
		UI_Access.Slider_Texts[9][Counter] = Preset_Items_Access.Item_List[Counter].Display_Name;
	}
	Audio_Access.Set_Volume(Settings_Access.Volume / 100.0f);
	UI_Access.Frame_Rate = static_cast<int>(15 * std::pow(2, Settings_Access.Raw_FPS));
	switch (Settings_Access.Fullscreen) {
	case 0:
		SDL_SetWindowBordered(Core_Access.Application_Window, true);
		SDL_SetWindowFullscreen(Core_Access.Application_Window, false);
		break;
	case 1:
		SDL_SetWindowBordered(Core_Access.Application_Window, false);
		SDL_SetWindowFullscreen(Core_Access.Application_Window, false);
		break;
	case 2:
		SDL_SetWindowBordered(Core_Access.Application_Window, false);
		SDL_SetWindowFullscreen(Core_Access.Application_Window, true);
		break;
	default:
		break;
	}
	if (Settings_Access.Anti_Aliasing == 0) {
		Scaling_Quality = SDL_SCALEMODE_NEAREST;
	} else {
		Scaling_Quality = SDL_SCALEMODE_LINEAR;
	}
	if (Settings_Access.VSync == 0) {
		SDL_SetRenderVSync(Core_Access.Application_Renderer, 0);
	} else {
		SDL_SetRenderVSync(Core_Access.Application_Renderer, 1);
	}
	Preload_Assets();
	Preload_Noise();
	Clock::time_point End = Clock::now();
	double Loading_Time = std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() / 1000.0;
	std::cout << "took " << Truncate(Loading_Time, 0) << "s" << std::endl;
}