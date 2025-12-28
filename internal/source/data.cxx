#include <Data_Handler.h>

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
	Preload_Assets_L();
	Preload_Assets();
	Preload_Noise();
	double Loading_Time = (SDL_GetTicks() - Start) / 1000.0;
	std::cout << "took " << Truncate(Loading_Time, 0) << "s" << std::endl;
}