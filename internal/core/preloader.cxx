#include <Legacy_Preloader.hpp>

std::string Abbreviate_Number(long double Number) {
	int Marker = 0;
	for (int Counter = 0; Counter < LDE_SUFFIXES - 1; Counter++) {
		if (Number >= 1000) {
			Marker++;
			Number = Number / 1000;
		} else {
			break;
		}
	}
	std::ostringstream Temporary_String;
	Temporary_String << std::fixed << std::setprecision(2) << Number;
	std::string Returning_String = Temporary_String.str();
	if (Core.Suffixes[Marker] != 'J') {
		std::string Teritary_String(1, Core.Suffixes[Marker]);
		Returning_String = Returning_String + Teritary_String;
	}
	return Returning_String;
}

std::string Truncate(double Number, int Depth = LDE_INVALID) {
	if (Depth == LDE_INVALID) {
		for (int Counter = 0; Counter < LDE_SUFFIXES - 1; Counter++) {
			if (Number > 1000) {
				Number = Number / 1000;
			} else {
				break;
			}
		}
	} else {
		Number = Number / std::pow(1000, Depth);
	}
	std::ostringstream Temporary_String;
	Temporary_String << std::fixed << std::setprecision(2) << Number;
	std::string Returning_String = Temporary_String.str();
	return Returning_String;
}

void Preload_Assets_L() {
	Core.Game_Texture = SDL_GenerateTexture(Core.Renderer, 640 * Settings.Screen_Size, 360 * Settings.Screen_Size);
	for (int Counter = 0; Counter < LDE_MACHINES; Counter++) {
		Metadata_L.Machine_Quirks.push_back({ false, false, false, false });
	}
	for (int Counter1 = 0; Counter1 < Metadata_L.Quirk_Positions.size(); Counter1++) {
		for (int Counter2 = 0; Counter2 < Metadata_L.Quirk_Positions[Counter1].size(); Counter2++) {
			Metadata_L.Machine_Quirks[Metadata_L.Quirk_Positions[Counter1][Counter2]][Counter1] = true;
		}
	}
	SDL_Surface* Carrying_Surface = nullptr;
	Interface.Maximum_Time_Frames = Interface.Frame_Rate;
	Interface.Maximum_Subtime_Frames = Interface.Frame_Rate / 3;
	Interface_L.Slider_Texts[5].resize(101, std::string());
	for (int Counter = 0; Counter < 101; Counter++) {
		Interface_L.Slider_Texts[5][Counter] = std::to_string(Counter) + "%";
	}
	const std::vector<int> Queried = {
		7,
		11,
		13
	};
	for (int Counter1 = 0; Counter1 < Queried.size(); Counter1++) {
		Interface_L.Slider_Texts[Queried[Counter1]].resize(Interface_L.Valve300_Postions.size(), std::string());
		for (int Counter2 = 0; Counter2 < Interface_L.Valve300_Postions.size(); Counter2++) {
			Interface_L.Slider_Texts[Queried[Counter1]][Counter2] = std::to_string(
				Interface_L.Valve300_Postions[Counter2]) + "L/s";
		}
	}
	Interface_L.Slider_Texts[10].resize(241, std::string());
	for (int Counter = 0; Counter < 241; Counter++) {
		Interface_L.Slider_Texts[10][Counter] = std::to_string(Counter * 5) + " °F";
	}
	Interface.Tile_Centerpoint = { 20.0f * Settings.Screen_Size, 20.0f * Settings.Screen_Size };
	Load_Sound(&Audio.Primary_Ambience, "Assets/Core/Audio/Ambient/Background.wav");
	Load_Sound(&Audio.Filtration_Loop, "Assets/Core/Audio/Machines/Filtration_Loop.wav");
	Load_Sound(&Audio.Ram_Loop, "Assets/Core/Audio/Machines/Ram_Loop.wav");
	Load_Sound(&Audio.Click, "Assets/Core/Audio/UI/Click.wav");
	std::string Tool_Texts[5] = { "Building", "Deleting", "Inspecting", "Wiring", "Plumbing" };
	Textures.Tool.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 5));
	Textures.Tool.Length = 5;
	for (int Counter = 0; Counter < 5; Counter++) {
		std::string Tool_String = "[" + std::to_string(Counter + 1) + "] " + Tool_Texts[Counter];
		SDL_Surface* Text_Surface = TTF_RenderText_Blended(Fonts.Halftext_Font,
			Tool_String.c_str(), Tool_String.size(), Colors.Abyss_Black);
		Rects.Tool[Counter] = { (320.0f * Settings.Screen_Size) -
			static_cast<float>(Text_Surface->w / 2), 335.0f * Settings.Screen_Size,
			static_cast<float>(Text_Surface->w), static_cast<float>(Text_Surface->h) };
		Textures.Tool.Data[Counter] = SDL_GenerateTextureFromSurface(
			Core.Renderer, Text_Surface);
		SDL_DestroySurface(Text_Surface);
	}
	Carrying_Surface = TTF_RenderText_Blended(Fonts.Large_Font, "Fish Factory Help",
		17, Colors.Abyss_Black);
	Rects.Help_Content[0] = { (320 * Settings.Screen_Size) -
		static_cast<float>(Carrying_Surface->w / 2), 20.0f * Settings.Screen_Size,
		static_cast<float>(Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
	Textures.Help_Content.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 2));
	Textures.Help_Content.Length = 2;
	Textures.Help_Content.Data[0] = SDL_GenerateTextureFromSurface(
		Core.Renderer, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	Carrying_Surface = TTF_RenderText_Blended(Fonts.Large_Font, "Catalog",
		7, Colors.Abyss_Black);
	Rects.Recipe_Content = { (320 * Settings.Screen_Size) -
		static_cast<float>(Carrying_Surface->w / 2), 20.0f * Settings.Screen_Size,
		static_cast<float>(Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
	Textures.Recipe_Content = SDL_GenerateTextureFromSurface(
		Core.Renderer, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	std::string Keycore = SDL_GetKeyName(Keybinds_L.Keybind_List[13]);
	Keycore = "Press \"" + Keycore + "\" to close.";
	Carrying_Surface = TTF_RenderText_Blended(Fonts.Text_Font, Keycore.c_str(),
		Keycore.size(), Colors.Abyss_Black);
	Rects.Help_Content[1] = { (320 * Settings.Screen_Size) -
		static_cast<float>(Carrying_Surface->w / 2), 320.0f * Settings.Screen_Size,
		static_cast<float>(Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
	Textures.Help_Content.Data[1] = SDL_GenerateTextureFromSurface(
		Core.Renderer, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	Textures.Quirk.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 4));
	Textures.Quirk_Label.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 4));
	Textures.Quirk.Length = 4;
	Textures.Quirk_Label.Length = 4;
	SDL_DestroySurface(Carrying_Surface);
	Textures.Quirk.Data[0] = Preload_Texture("UI/Quirks/No_Rotation");
	Textures.Quirk.Data[1] = Preload_Texture("UI/Quirks/Modular");
	Textures.Quirk.Data[2] = Preload_Texture("UI/Quirks/Interactable");
	Textures.Quirk.Data[3] = Preload_Texture("UI/Quirks/All_Direction");
	std::string Quirk_Texts[4] = { "Non-Rotatable", "Modular", "Interactable", "Omnidirectional" };
	for (int Counter = 0; Counter < 4; Counter++) {
		Carrying_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Quirk_Texts[Counter].c_str(),
			Quirk_Texts[Counter].size(), Colors.Abyss_Black);
		Textures.Quirk_Label.Data[Counter] = SDL_GenerateTextureFromSurface(
			Core.Renderer, Carrying_Surface);
		SDL_DestroySurface(Carrying_Surface);
	}
	Textures.Log_Background = SDL_GenerateTextureFromSurface(
		Core.Renderer, Carrying_Surface);
	Rects.Log_Background = {
		0, 0, static_cast<float>(Carrying_Surface->w / 6) *
		Settings.Screen_Size, static_cast<float>(Carrying_Surface->h / 6) * Settings.Screen_Size };
	Interface_L.Log_Heights.clear();
	Interface_L.Log_Heights.resize(3);
	Cache_L.Log_Rectangles.clear();
	Cache_L.Log_Rectangles.resize(3);
	Cache.Log_Cache.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 3));
	Cache.Log_Cache.Length = 3;
	for (int Counter1 = 0; Counter1 < Metadata_L.Logs.size(); Counter1++) {
		int Height = Render_Rich_Text(Fonts.Halftext_Font, Metadata_L.Logs[Counter1],
			0, 0, Temporary.Log_Inversions[Counter1], true) - (210 * Settings.Screen_Size);
		Interface_L.Log_Heights[Counter1] = Height;
		Cache_L.Log_Rectangles[Counter1].clear();
		int Cap = std::ceil((double)Height / (682 / 2 * Settings.Screen_Size));
		Cache.Log_Cache.Data[Counter1].Data = static_cast<SDL_Texture**>(
			malloc(sizeof(SDL_Texture*) * Cap));
		Cache.Log_Cache.Data[Counter1].Length = Cap;
		for (int Counter2 = 0; Counter2 < Cap; Counter2++) {
			Cache.Log_Cache.Data[Counter1].Data[Counter2] =
				SDL_GenerateTexture(Core.Renderer,
				Settings.Screen_Size * 640, Settings.Screen_Size * 1000);
			SDL_FRect New_Rectangle = { 0, Counter2 * Settings.Screen_Size * 1000.0f,
				640.0f * Settings.Screen_Size, 1000.0f * Settings.Screen_Size };
			SDL_SetTextureBlendMode(Cache.Log_Cache.Data[
				Counter1].Data[Counter2], SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(Core.Renderer, Cache
				.Log_Cache.Data[Counter1].Data[Counter2]);
			Render_Rich_Text(Fonts.Halftext_Font, Metadata_L.Logs[Counter1],
				52, 52 - (New_Rectangle.y / Settings.Screen_Size),
				Temporary.Log_Inversions[Counter1], false);
			SDL_SetRenderTarget(Core.Renderer, NULL);
			Cache_L.Log_Rectangles[Counter1].push_back(New_Rectangle);			
		}
	}
	Cache.Wire_Cache.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 4));
	Cache.Wire_Cache.Length = 4;
	for (int Counter = 0; Counter < 4; Counter++) {
		Cache.Wire_Cache.Data[Counter] = SDL_GenerateTexture(
			Core.Renderer, LDE_GRIDSIZE * Settings.Screen_Size * 20,
			LDE_GRIDSIZE * Settings.Screen_Size * 20);
		SDL_SetTextureBlendMode(Cache.Wire_Cache.Data[Counter], SDL_BLENDMODE_BLEND);
	}
	Cache.Wire_Box = { 0, 0, 20.0f * LDE_GRIDSIZE * Settings.Screen_Size,
		20.0f *	LDE_GRIDSIZE * Settings.Screen_Size };
}

void Render_Dynamic_Text(TTF_Font* Selected_Font, std::string Text, SDL_Color Color, int X, int Y) {
	SDL_Surface* Text_Surface = TTF_RenderText_Blended(Selected_Font, Text.c_str(), Text.size(), Color);
	SDL_Texture* Text_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Text_Surface);
	int Multiplier = Settings.Screen_Size;
	if (X == LDE_INVALID) {
		X = (320 * Settings.Screen_Size) - (Text_Surface->w / 2);
		Multiplier = 1;
	}
	SDL_FRect Text_Rectangle = { static_cast<float>(X * Multiplier),
		static_cast<float>(Y * Settings.Screen_Size),
		static_cast<float>(Text_Surface->w), static_cast<float>(Text_Surface->h) };
	SDL_RenderTexture(Core.Renderer, Text_Texture, NULL, &Text_Rectangle);
	SDL_DestroySurface(Text_Surface);
	SDL_DestroyTexture(Text_Texture);
}

int Render_Rich_Text(TTF_Font* Selected_Font, std::string Raw_Text, int X, int Y, bool Inverted, bool Disabled) {
	std::string Text = Raw_Text;
	std::vector<std::string> Fragments = { };
	size_t Start = 0;
	size_t End = 0;
	int Offset = 0;
	while ((End = Text.find('|', Start)) != std::string::npos) {
		Fragments.push_back(Text.substr(Start, End - Start));
		Start = End + 1;
	}
	Fragments.push_back(Text.substr(Start));
	int Multiplier = LDE_INVALID;
	int Subtractor = 0;
	if (Inverted) {
		Multiplier = 1;
		Subtractor = static_cast<int>(Fragments.size()) - 1;
	}
	for (size_t Counter = 0; Counter < Fragments.size(); Counter++) {
		size_t Position;
		while ((Position = Fragments[Counter].find("[c]")) != std::string::npos) {
			Fragments[Counter].replace(Position, 3, "    ");
		}
	}
	for (size_t Counter1 = 0; Counter1 < Fragments.size(); Counter1++) {
		int Type = LDE_INVALID;
		std::vector<std::string> Targets = { "[a]", "[b]" };
		for (int Counter2 = 0; Counter2 < Targets.size(); Counter2++) {
			bool Matched = true;
			if (Fragments[Multiplier * (Subtractor - Counter1)] == " ") {
				Matched = false;
			} else {
				for (int Counter3 = 0; Counter3 < 3; Counter3++) {
					if (Fragments[Multiplier * (Subtractor - Counter1)][Counter3] != Targets[Counter2][Counter3]) {
						Matched = false;
					}
				}
			}
			if (Matched) {
				Type = Counter2;
				break;
			}
		}
		if ((Type == 0 && Inverted) || (Type == 1 && !Inverted)) {
			continue;
		} else if (Type != LDE_INVALID) {
			Fragments[Multiplier * (Subtractor - Counter1)].erase(0, 3);
		}
		SDL_Surface* Fragment_Surface = TTF_RenderText_Blended(Selected_Font, Fragments
			[Multiplier * (Subtractor - Counter1)].c_str(), Fragments[Multiplier * (Subtractor -
			Counter1)].size(), Colors.Abyss_Black);
		SDL_FRect Fragment_Rectangle = { static_cast<float>(X * Settings.Screen_Size),
			static_cast<float>(Y * Settings.Screen_Size) + Offset, static_cast<float>(
			Fragment_Surface->w), static_cast<float>(Fragment_Surface->h) };
		if (!Disabled) {
			SDL_Texture* Fragment_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Fragment_Surface);
			SDL_RenderTexture(Core.Renderer, Fragment_Texture, NULL, &Fragment_Rectangle);
			SDL_DestroyTexture(Fragment_Texture);
		}
		SDL_DestroySurface(Fragment_Surface);
		Offset = Offset + Fragment_Rectangle.h;
	}
	return Offset;
}