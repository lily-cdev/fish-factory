#include <Data_Handler.h>
#include <legacy.hpp>

void Preclear_Temporaries() {
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			Data_L.Animation_Grid[X][Y].clear();
			for (int Counter = 0; Counter < 3; Counter++) {
				Data_L.Animation_Grid[X][Y].push_back(LDE_INVALID);
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
		{ "First_X", Input.X1 },
		{ "First_Y", Input.Y1 },
		{ "Second_X", Input.X2 },
		{ "Second_Y", Input.Y2 }
	};
}

void to_json(nlohmann::json &File, const Pipe &Input) {
	File = nlohmann::json{
		{ "Filled", Input.Filled },
		{ "First_X", Input.X1 },
		{ "First_Y", Input.Y1 },
		{ "Second_X", Input.X2 },
		{ "Second_Y", Input.Y2 },
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
	File.at("First_X").get_to(Output.X1);
	File.at("First_Y").get_to(Output.Y1);
	File.at("Second_X").get_to(Output.X2);
	File.at("Second_Y").get_to(Output.Y2);
}

void from_json(const nlohmann::json &File, Pipe &Output) {
	File.at("Filled").get_to(Output.Filled);
	File.at("First_X").get_to(Output.X1);
	File.at("First_Y").get_to(Output.Y1);
	File.at("Second_X").get_to(Output.X2);
	File.at("Second_Y").get_to(Output.Y2);
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
		{ "Version", Data.Version },
		{ "Funds", Data.Funds },
		{ "Time", Data.Time },
		{ "Day", Data.Day },
		{ "CMD Placed", Data.CMD_Placed }
	};
	File["Visual Grid"] = Convert_Simple_Grid(Data.Visual_Grid);
	File["Connection Grid"] = Convert_Simple_Grid(Data.Connection_Grid);
	File["Behaviour Grid"] = Convert_Simple_Grid(Data.Behavior_Grid);
	File["Wiring Grid"] = Convert_Simple_Grid(Data.Wiring_Grid);
	File["Plumbing Grid"] = Convert_Simple_Grid(Data.Plumbing_Grid);
	File["Data Grid"] = Convert_Complex_Grid(Data_L.Data_Grid);
	File["Settings Grid"] = Convert_Complex_Grid(Data_L.Settings_Grid);
	File["Wires List"] = Wires_List;
	File["Pipes List"] = Pipes_List;
	File["Items List"] = Convert_Simple_Grid(Data.Items_Grid);
	File["Temp List"] = Convert_Simple_Grid(Data.Temperature_Grid);
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
	File.at("Version").get_to(Data.Version);
	File.at("Funds").get_to(Data.Funds);
	Recieve_Simple_Grid(File.at("Visual Grid"), Data.Visual_Grid);
	Recieve_Simple_Grid(File.at("Connection Grid"), Data.Connection_Grid);
	Recieve_Simple_Grid(File.at("Behaviour Grid"), Data.Behavior_Grid);
	Recieve_Simple_Grid(File.at("Wiring Grid"), Data.Wiring_Grid);
	Recieve_Simple_Grid(File.at("Plumbing Grid"), Data.Plumbing_Grid);
	Recieve_Complex_Grid(File.at("Data Grid"), Data_L.Data_Grid, 7);
	Wires_List = File.at("Wires List").get<std::vector<Wire>>();
	Pipes_List = File.at("Pipes List").get<std::vector<Pipe>>();
	if (Data.Version < 1) {
		Data.Version = 1;
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				Legacy_Item_Stack Blank_Item;
				Blank_Item.Identifier = LDE_INVALID;
				Legacy_Item_Grid[Column][Row] = Blank_Item;
			}
		}
	} else if (Data.Version < 3) {
		Recieve_Items_Grid(File.at("Items List"), Legacy_Item_Grid);
	}
	if (Data.Version < 2) {
		Recieve_Complex_Grid(File.at("Settings Grid"), Data_L.Settings_Grid, 3);
		Data.Version = 2;
		Data.Time = 0;
		Data.Day = 0;
		Data.CMD_Placed = false;
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				for (int Counter = 0; Counter < 5; Counter++) {
					Data_L.Settings_Grid[Column][Row].push_back(LDE_INVALID);
				}
			}
		}
	} else if (Data.Version < 5) {
		File.at("Time").get_to(Data.Time);
		File.at("Day").get_to(Data.Day);
		File.at("CMD Placed").get_to(Data.CMD_Placed);
	}
	if (Data.Version < 3) {
		Data.Version = 3;
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				Data.Items_Grid[Column][Row] = Legacy_Item_Grid[Column][Row].Identifier;
			}
		}
	} else {
		Recieve_Simple_Grid(File.at("Items List"), Data.Items_Grid);
	}
	if (Data.Version < 4) {
		Data.Version = 4;
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				Data.Temperature_Grid[Column][Row] = Get_Item(Column, Row).Temperature;
			}
		}
	} else {
		Recieve_Simple_Grid(File.at("Temp List"), Data.Temperature_Grid);
	}
	if (Data.Version < 5) {
		Data.Version = 5;
		Recieve_Complex_Grid(File.at("Settings Grid"), Data_L.Settings_Grid, 8);
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				for (int Counter = 0; Counter < 8; Counter++) {
					Data_L.Settings_Grid[Column][Row].push_back(LDE_INVALID);
				}
			}
		}
	} else {
		Recieve_Complex_Grid(File.at("Settings Grid"), Data_L.Settings_Grid, 16);
	}
	Preclear_Temporaries();
	return true;
}

bool Update_Metadata() {
	int Index = SDL_GetDisplayForWindow(Core.Window);
	const SDL_DisplayMode* Display = SDL_GetDesktopDisplayMode(Index);
	Metadata_L.Monitor_Size = std::to_string(Display->w) + "x" + std::to_string(Display->h);
	std::vector<std::string> Resolution_Names = { "nHD", "HD", "FHD", "QHD", "QHD+", "4K" };
	for (int Counter = 0; Counter < Metadata_L.Supported_Resolutions.size(); Counter++) {
		if (Display->w == Metadata_L.Supported_Resolutions[Counter][0] &&
			Display->h == Metadata_L.Supported_Resolutions[Counter][1]) {
			Metadata_L.Monitor_Size = Metadata_L.Monitor_Size + " (" + Resolution_Names[Counter] + ")";
			break;
		}
	}
	Metadata_L.Monitor_Size = "Detected Resolution: " + Metadata_L.Monitor_Size;
	nlohmann::json File;
	std::string Path = "Assets/Data/Metadata_L.json";
	std::ifstream Source(Path.c_str());
	if (Source) {
		Source >> File;
	} else {
		return false;
	}
	Source.close();
	Metadata_L.Logs.clear();
	Metadata_L.Logs.resize(3);
	File.at("Changelog").get_to(Metadata_L.Logs[Changelog]);
	File.at("Crediting").get_to(Metadata_L.Logs[Credits]);
	File.at("Licensing").get_to(Metadata_L.Logs[Legal]);
	return true;
}

void Get_Filesizes() {
	for (int Counter = 1; Counter < 5; Counter++) {
		std::string Path = "Assets/Data/Slot" + std::to_string(Counter) + ".json";
		std::ifstream File(Path, std::ios::binary | std::ios::ate);
		Core.Save_Filesizes[Counter - 1] = static_cast<double>(File.tellg());
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
		Keybinds_Vector.push_back(static_cast<int>(Keybinds_L.Keybind_List[Counter]));
	}
	Clear_File("Assets/Data/Settings");
	nlohmann::json File = nlohmann::json {
		{ "Version", 3 },
		{ "Scale_Quality", Settings.Anti_Aliasing },
		{ "V_Sync", Settings.VSync },
		{ "Fullscreen", Settings.Fullscreen },
		{ "Screen_Size", Settings.Screen_Size },
		{ "Volume", Settings.Volume },
		{ "FPS_Cap", Settings.Raw_FPS }
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
			Save_File.at("Scale_Quality").get_to(Settings.Anti_Aliasing);
			Save_File.at("V_Sync").get_to(Settings.VSync);
			Save_File.at("Fullscreen").get_to(Settings.Fullscreen);
			Save_File.at("Screen_Size").get_to(Settings.Screen_Size);
			Save_File.at("Volume").get_to(Settings.Volume);
			Save_File.at("FPS_Cap").get_to(Settings.Raw_FPS);
			for (int Counter = 0; Counter < 14; Counter++) {
				Keybinds_L.Keybind_List[Counter] = Save_File.at("Keybinds").at(Counter).get<int>();
			}
		} else {
			Clear_File("Assets/Data/Settings");
		}
	} else {
		File.close();
		int Index = SDL_GetDisplayForWindow(Core.Window);
		const SDL_DisplayMode* Display = SDL_GetDesktopDisplayMode(Index);
		for (int Counter = 0; Counter < Metadata_L.Supported_Resolutions.size(); Counter++) {
			if (Display->w >= Metadata_L.Supported_Resolutions[Counter][0] &&
				Display->h >= Metadata_L.Supported_Resolutions[Counter][1]) {
				Settings.Screen_Size++;
			} else {
				break;
			}
		}
		if (Settings.Screen_Size == 0) {
			Settings.Screen_Size = 1;
		}
	}
}

void Clear_Settings() {
	Interface.Slider_Positions[0] = Settings.Screen_Size - 1;
	Interface.Slider_Positions[4] = Settings.Raw_FPS;
	Interface.Slider_Positions[5] = Settings.Volume;
	Interface.Slider_Positions[6] = Settings.Fullscreen;
	Settings.AA_Temporary = static_cast<bool>(Settings.Anti_Aliasing);
	Settings.VS_Temporary = static_cast<bool>(Settings.VSync);
	for (int Counter = 0; Counter < Keybinds_L.Keybind_List.size(); Counter++) {
		Keybinds_L.Keybind_Settings[Counter] = Keybinds_L.Keybind_List[Counter];
	}
}

void Recalibrate_Settings() {
	Settings.Screen_Size = Interface.Slider_Positions[0] + 1;
	Settings.Raw_FPS = Interface.Slider_Positions[4];
	Settings.Volume = Interface.Slider_Positions[5];
	Settings.Fullscreen = Interface.Slider_Positions[6];
	Settings.Anti_Aliasing = static_cast<int>(Settings.AA_Temporary);
	Settings.VSync = static_cast<int>(Settings.VS_Temporary);
	for (int Counter = 0; Counter < Keybinds_L.Keybind_List.size(); Counter++) {
		Keybinds_L.Keybind_List[Counter] = Keybinds_L.Keybind_Settings[Counter];
	}
	Reload_All();
}

void Preload_Noise() {
	Textures.None.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 10));
	Textures.None.Length = 10;
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
				std::clamp(Colors.Ocean.r + Counter, 0, 255),
				std::clamp(Colors.Ocean.g + Counter, 0, 255),
				std::clamp(Colors.Ocean.b + Counter, 0, 255)
			);
		}
	}
	SDL_Surface* None_Surfaces[10];
	std::vector<std::thread> Threads;
	for (int Counter1 = 0; Counter1 < 10; Counter1++) {
		Threads.emplace_back([&, Counter1]{
			uint32_t Shade = static_cast<uint32_t>(SDL_GetTicks() & 255);
			SDL_Surface* Noise_Surface = SDL_CreateSurface(Settings.Screen_Size * 1200,
				Settings.Screen_Size * 1200, SDL_PIXELFORMAT_RGBA8888);
			SDL_LockSurface(Noise_Surface);
			uint32_t* Pixels = static_cast<uint32_t*>(Noise_Surface->pixels);
			for (int Counter2 = 0; Counter2 < sqr_i(Settings.Screen_Size *
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
		Textures.None.Data[Counter] = SDL_GenerateTextureFromSurface(
			Core.Renderer, None_Surfaces[Counter]);
		SDL_SetTextureScaleMode(Textures.None.Data[Counter], SDL_SCALEMODE_NEAREST);
		SDL_SetTextureBlendMode(Textures.None.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_DestroySurface(None_Surfaces[Counter]);
	}
	const SDL_Color Fire_Colors[4] = {
		{ 255, 140, 0 },
		{ 255, 163, 51 },
		{ 255, 205, 6 },
		{ 0, 0, 0 }
	};
	Textures.Fire.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 10));
	Textures.Fire.Length = 10;
	SDL_Surface* Fire_Surfaces[10];
	uint32_t Random = static_cast<uint32_t>(SDL_GetTicks() & 255);
	for (int Counter1 = 0; Counter1 < 10; Counter1++) {
		Fire_Surfaces[Counter1] = SDL_CreateSurface(Settings.Screen_Size * LDE_TILESIZE,
			Settings.Screen_Size * LDE_TILESIZE, SDL_PIXELFORMAT_RGBA8888);
		SDL_LockSurface(Fire_Surfaces[Counter1]);
		uint32_t* Pixels = static_cast<uint32_t*>(Fire_Surfaces[Counter1]->pixels);
		for (int Counter2 = 0; Counter2 < sqr_i(Settings.Screen_Size * LDE_TILESIZE); Counter2++) {
			Random = (Random * 2891336453u) + 747796405u;
			Random ^= Random >> 16;
			Pixels[Counter2] = SDL_MapRGB(Pixel_Format, NULL, Fire_Colors[(Random & 3)].r,
				Fire_Colors[(Random & 3)].g, Fire_Colors[(Random & 3)].b);
		}
		SDL_UnlockSurface(Fire_Surfaces[Counter1]);
		Textures.Fire.Data[Counter1] = SDL_GenerateTextureFromSurface(
			Core.Renderer, Fire_Surfaces[Counter1]);
		SDL_SetTextureScaleMode(Textures.Fire.Data[Counter1], SDL_SCALEMODE_NEAREST);
		SDL_SetTextureBlendMode(Textures.Fire.Data[Counter1], SDL_BLENDMODE_BLEND);
		SDL_DestroySurface(Fire_Surfaces[Counter1]);
	}
}

void Render_Loadscreen() {
	Set_Renderer_Color(Colors.Pure_White);
	SDL_RenderClear(Core.Renderer);
	Clear_Renderer();
	SDL_Surface* Text_Surface = TTF_RenderText_Blended(Fonts.Logo_Font,
		"loading assets", 15, Colors.Abyss_Black);
	SDL_FRect Pasting_Rectangle = {
		(Settings.Screen_Size * 320.0f) - (Text_Surface->w / 2),
		(Settings.Screen_Size * 180.0f) - (Text_Surface->h / 2),
		static_cast<float>(Text_Surface->w),
		static_cast<float>(Text_Surface->h)
	};
	SDL_Texture* Text_Texture = SDL_GenerateTextureFromSurface(
		Core.Renderer, Text_Surface);
	SDL_RenderTexture(Core.Renderer, Text_Texture,
		NULL, &Pasting_Rectangle);
	SDL_DestroySurface(Text_Surface);
	SDL_DestroyTexture(Text_Texture);
	SDL_RenderPresent(Core.Renderer);
	SDL_PumpEvents();
}

void Reload_All() {
	uint64_t Start = SDL_GetTicks();
	Preload_Recipes();
	Cleanup_Assets();
	SDL_SetWindowSize(Core.Window, 640 *
		Settings.Screen_Size, 360 * Settings.Screen_Size);
	Preload_Fonts();
	Render_Loadscreen();
	SDL_SetWindowPosition(Core.Window, 0, 0);
	Interface_L.Slider_Texts[9].resize(Preset_Items.Item_List.size());
	for (int Counter = 0; Counter < Preset_Items.Item_List.size(); Counter++) {
		Interface_L.Slider_Texts[9][Counter] = Preset_Items.Item_List[Counter].Display_Name;
	}
	Adjust_Sound(Settings.Volume * 0.01f);
	Interface.Frame_Rate = static_cast<int>(15 * std::pow(2, Settings.Raw_FPS));
	switch (Settings.Fullscreen) {
	case 0:
		SDL_SetWindowBordered(Core.Window, true);
		SDL_SetWindowFullscreen(Core.Window, false);
		break;
	case 1:
		SDL_SetWindowBordered(Core.Window, false);
		SDL_SetWindowFullscreen(Core.Window, false);
		break;
	case 2:
		SDL_SetWindowBordered(Core.Window, false);
		SDL_SetWindowFullscreen(Core.Window, true);
		break;
	default:
		break;
	}
	if (Settings.Anti_Aliasing == 0) {
		Scaling_Quality = SDL_SCALEMODE_NEAREST;
	} else {
		Scaling_Quality = SDL_SCALEMODE_LINEAR;
	}
	if (Settings.VSync == 0) {
		SDL_SetRenderVSync(Core.Renderer, 0);
	} else {
		SDL_SetRenderVSync(Core.Renderer, 1);
	}
	Preload_Assets();
	Preload_Noise();
	double Loading_Time = (SDL_GetTicks() - Start) / 1000.0;
	std::cout << "took " << Truncate(Loading_Time, 0) << "s" << std::endl;
}