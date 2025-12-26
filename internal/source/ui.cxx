#include <ui.h>

void (*Interface_Functions[11])(int X, int Y) {
	Render_Help,
	Render_Shop,
	Render_Daily_Report,
	Render_MSP_Controller,
	Render_T_Tower,
	Render_S_Dock,
	Render_H_Exchanger,
	Render_M_Generator,
	Render_F_Generator,
	Render_Catalog,
	Render_MT_Input
};

void Render_Blueprint(int Size_X, int Size_Y) {
	SDL_FRect Hitbox = { 0, 0, static_cast<float>(Size_X * 40) * Settings.Screen_Size,
		static_cast<float>(Size_Y * 40) * Settings.Screen_Size };
	SDL_FRect Invisible_Hitbox = { 0, 0, 40.0f * Settings.Screen_Size, 40.0f * Settings.Screen_Size };
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Hitbox.x = static_cast<int>((Column * 40) - Interface.Camera_X) * Settings.Screen_Size;
		Invisible_Hitbox.x = static_cast<int>((Column * 40) - Interface.Camera_X) * Settings.Screen_Size;
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Hitbox.y = static_cast<int>((Row * 40) - Interface.Camera_Y) * Settings.Screen_Size;
			Invisible_Hitbox.y = static_cast<int>((Row * 40) - Interface.Camera_Y) * Settings.Screen_Size;
			if (Detect_Mouse_Collision(Invisible_Hitbox)) {
				if ((Hitbox.x + Hitbox.w <= ((LDE_GRIDSIZE * 40) - Interface.Camera_X) * Settings.Screen_Size &&
					Hitbox.y + Hitbox.h <= ((LDE_GRIDSIZE * 40) - Interface.Camera_Y) * Settings.Screen_Size)
					|| (Size_X != 2 && Size_Y != 2)) {
					bool Placeable = Check_Clearance(Column, Row, Size_X, Size_Y);
					if ((Interface.Placing_Item == Command_Platform + 1 && Data.CMD_Placed) ||
						(Interface.Placing_Item == Submarine_Dock + 1 && Row != 0)) {
						Placeable = false;
					}
					if (Placeable) {
						Render_Outline(Hitbox, Colors.Pure_White);
					} else {
						SDL_SetTextureColorMod(Cache.Blueprint_Cache, Colors.Hostile_Red.r,
							Colors.Hostile_Red.g, Colors.Hostile_Red.b);
						Render_Outline(Hitbox, Colors.Hostile_Red);
					}
					SDL_RenderTexture(Core.Renderer, Cache.Blueprint_Cache,
						NULL, &Hitbox);
					SDL_SetTextureColorMod(Cache.Blueprint_Cache, 255, 255, 255);
					return;
				}
			}
		}
	}
}

void Render_Sidebar(SDL_Texture* Texture, SDL_FRect Rectangle, int Selection) {
	if (Detect_Mouse_Collision(Rectangle)) {
		Rectangle.x = (640 * Settings.Screen_Size) - Rectangle.w;
		Interface.UI_Selection = Selection;
	} else {
		Rectangle.x = (654 * Settings.Screen_Size) - Rectangle.w;
	}
	SDL_RenderTexture(Core.Renderer, Texture, NULL, &Rectangle);
}

void Render_Game_UI() {
	if (Interface.Tool == LDE_INVALID && Interface.Prompt_Identifier == LDE_INVALID) {
		Render_Sidebar(Textures.Help_Sidebutton, Rects.Help, 1);
		Render_Sidebar(Textures.Save_Sidebutton, Rects.Save, 2);
		Render_Sidebar(Textures.Recipe_Sidebutton, Rects.Recipe, 3);
		Render_Sidebar(Textures.Exit_Sidebutton, Rects.Exit, 4);
	}
	std::vector<std::string> Queried_Data_Fragments = { };
	int Hour = Data.Time / 60;
	int Minute =  Data.Time % 60;
	bool Afternoon = false;
	if (Hour > 11) {
		Hour -= 12;
		Afternoon = true;
	}
	if (Hour == 0) {
		Hour = 12;
	}
	std::string Time;
	if (Hour < 10) {
		Time = "0" + std::to_string(Hour) + ":";
	} else {
		Time = std::to_string(Hour) + ":";
	}
	if (Minute < 10) {
		Time += "0" + std::to_string(Minute);
	} else {
		Time += std::to_string(Minute);
	}
	if (Afternoon) {
		Time += "PM";
	} else {
		Time += "AM";
	}
	Render_Dynamic_Text(Fonts.Halftext_Font, Abbreviate_Number(Data.Funds) + "LA", Colors.Abyss_Black, 10, 30);
	Render_Dynamic_Text(Fonts.Halftext_Font, Time + ", " + Metadata.Days[Data.Day] + "day",
		Colors.Abyss_Black, 10, 50);
	if (Interface.Tool == 2) {
		std::vector<double> Content_Vector = Get_Grid_Data(Data.Data_Grid);
		Item_Stack Returned_Item = Get_Item_Stack_Data();
		if (Returned_Item.Identifier != LDE_INVALID) {
			Queried_Data_Fragments.push_back("Item: " + Returned_Item.Display_Name);
			Queried_Data_Fragments.push_back(Truncate(Returned_Item.Temperature, 0) + "°F");
			double Pressure = Calculate_Pressure(Returned_Item.Temperature, Returned_Item.Boiling_Point,
				Returned_Item.Vaporisation_Enthalpy);
			int Multiplier = 1;
			if (Pressure == LDE_INVALID) {
				Queried_Data_Fragments.push_back("gas");
				Multiplier = 10;
			} else {
				if (Pressure < 1) {
					Pressure = 1;
				}
				Queried_Data_Fragments.push_back(Abbreviate_Number(Pressure) + " bar liquid");
			}
			if (Content_Vector[1] != 0) {
				Queried_Data_Fragments.push_back(Truncate(Content_Vector[0] * Multiplier, Get_Depth(Content_Vector[1] *
					Multiplier)) + " / " + Abbreviate_Number(Content_Vector[1] * Multiplier) + "L.");
			}
		} else {
			if (Content_Vector[1] != 0) {
				Queried_Data_Fragments.push_back(Truncate(0, 0) + " / " + Abbreviate_Number(Content_Vector[1]) + "L.");
			}
		}
		if (Content_Vector[3] != 0) {
			Queried_Data_Fragments.push_back(Truncate(Content_Vector[2], Get_Depth(Content_Vector[3])) + " / " +
				Abbreviate_Number(Content_Vector[3]) + "J.");
		}
		if (Queried_Data_Fragments.size() <= 0) {
			Queried_Data_Fragments.push_back("No data");
		}
		int Maximum_Width = 0;
		std::vector<SDL_Texture*> Fragment_Textures = { };
		std::vector<SDL_FRect> Fragment_Rectangles = { };
		for (int Counter = 0; Counter < Queried_Data_Fragments.size(); Counter++) {
			SDL_Surface* Fragment_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font,
				Queried_Data_Fragments[Counter].c_str(), Queried_Data_Fragments
				[Counter].size(), Colors.Abyss_Black);
			if (Fragment_Surface->w > Maximum_Width) {
				Maximum_Width = Fragment_Surface->w;
			}
			SDL_Texture* Fragment_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Fragment_Surface);
			Fragment_Textures.push_back(Fragment_Texture);
			Fragment_Rectangles.push_back({ static_cast<float>(630 * Settings.Screen_Size) -
				Fragment_Surface->w, static_cast<float>(10 + (Counter * 20)) *
				Settings.Screen_Size, static_cast<float>(Fragment_Surface->w),
				static_cast<float>(Fragment_Surface->h) });
			SDL_DestroySurface(Fragment_Surface);
		}
		int Total_Height = Fragment_Rectangles[Fragment_Rectangles.size() - 1].y + Fragment_Rectangles[Fragment_Rectangles.size() - 1].h;
		Set_Renderer_Color(Colors.Dark_Grey);
		SDL_FRect Background_Rectangle = { static_cast<float>(615 * Settings.Screen_Size) -
			Maximum_Width, 0, Maximum_Width + static_cast<float>(25 * Settings.Screen_Size),
			Total_Height + static_cast<float>(15 * Settings.Screen_Size) };
		SDL_RenderFillRect(Core.Renderer, &Background_Rectangle);
		Set_Renderer_Color(Colors.Light_Grey);
		Background_Rectangle = { static_cast<float>(620 * Settings.Screen_Size) - Maximum_Width,
			0, Maximum_Width + static_cast<float>(20 * Settings.Screen_Size), Total_Height +
			static_cast<float>(10 * Settings.Screen_Size) };
		SDL_RenderFillRect(Core.Renderer, &Background_Rectangle);
		Clear_Renderer();
		for (int Counter = 0; Counter < Fragment_Textures.size(); Counter++) {
			SDL_RenderTexture(Core.Renderer, Fragment_Textures[Counter], NULL, &Fragment_Rectangles[Counter]);
			SDL_DestroyTexture(Fragment_Textures[Counter]);
		}
		Fragment_Textures.clear();
		Fragment_Rectangles.clear();
	}
	if (Interface.Save_Frames > 0) {
		SDL_Color Fading_Color = Colors.Cherry_Blossom;
		Fading_Color.a = static_cast<Uint8>(ceil(((double) Interface.Save_Frames / (Interface.Frame_Rate * 2)) * 255));
		Render_Dynamic_Text(Fonts.Subtext_Font, "Data saved!", Fading_Color, LDE_INVALID, 300);
		Interface.Save_Frames--;
	}
}

void Render_Saveloader() {
	SDL_RenderTexture(Core.Renderer, Textures.Saveloader,
		NULL, &Rects.Saveloader);
	for (int Counter = 0; Counter < 4; Counter++) {
		if (Core.Save_Filesizes[Counter] > 0) {
			Render_Button(Textures.Load.Data[Counter],
				Rects.Load.Data[Counter], 6 + Counter);
			Render_Button(Textures.Clear.Data[Counter],
				Rects.Clear.Data[Counter], 10 + Counter);
		} else {
			Render_Button(Textures.New.Data[Counter],
				Rects.New.Data[Counter], 2 + Counter);
		}
	}
	for (int Counter = 0; Counter < 4; Counter++) {
		std::string Text = "Factory " + std::to_string(Counter + 1) + " (" +
			Abbreviate_Number(Core.Save_Filesizes[Counter]) + "b)";
		Render_Dynamic_Text(Fonts.Subtext_Font, Text.c_str(),
			Colors.Abyss_Black, 40, 160 + (40 * Counter));
	}
}

void Render_Prompts() {
	if (Interface.Prompt_Identifier != LDE_INVALID) {
		Interface_Functions[Interface.Prompt_Identifier](
			Interface.Target_Tile.X, Interface.Target_Tile.Y);
	}
}

void Render_Slider(std::vector<std::string> Labels, int Engagement, int Nodes, int Selection, int &Position,
	int X, int Y, int Width, SDL_Color Primary, SDL_Color Secondary, bool Text_Visible) {
	bool Active = false;
	SDL_FRect Background_Rectangle = { static_cast<float>(X * Settings.Screen_Size),
		static_cast<float>(Y - 3) * Settings.Screen_Size, static_cast<float>(Width *
		Settings.Screen_Size), 6.0f * Settings.Screen_Size };
	if (Interface.Engagement == Engagement) {
		Active = true;
		std::vector<int>Separators = { };
		for (int Counter = 0; Counter < Nodes; Counter++) {
			Separators.push_back(static_cast<int>(((((double)Counter / Nodes) * Width) + (Width / (Nodes * 2)) + X)) *
				Settings.Screen_Size);
		}
		for (int Counter = 0; Counter < Nodes; Counter++) {
			if (Core.Debug_Mode) {
				SDL_RenderLine(Core.Renderer, static_cast<float>(Separators[Counter]),
					0, static_cast<float>(Separators[Counter]), 360.0f * Settings.Screen_Size);
			}
			if (Interface.X_Mouse_Position < Separators[0]) {
				Position = 0;
			} else if (Interface.X_Mouse_Position >= Separators[Nodes - 1]) {
				Position = Nodes;
			} else if (Interface.X_Mouse_Position >= Separators[Counter] && Interface.X_Mouse_Position < Separators[Counter + 1]) {
				Position = Counter + 1;
			}
		}
	}
	Set_Renderer_Color(Primary);
	SDL_RenderFillRect(Core.Renderer, &Background_Rectangle);
	if (Active) {
		Set_Renderer_Color(Secondary);
	}
	SDL_FRect Node_Rectangle = { static_cast<float>((((double) Position / Nodes) * Width) + X - 6) *
		Settings.Screen_Size, static_cast<float>(Y - 6) * Settings.Screen_Size,
		12.0f * Settings.Screen_Size, 12.0f * Settings.Screen_Size};
	if (Detect_Mouse_Collision(Node_Rectangle)) {
		Interface.UI_Selection = Selection;
		Set_Renderer_Color(Secondary);
	}
	SDL_RenderFillRect(Core.Renderer, &Node_Rectangle);
	Clear_Renderer();
	if (Text_Visible) {
		SDL_Surface* Caption_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font,
			Labels[Position].c_str(), Labels[Position].size(), Primary);
		SDL_FRect Caption_Rectangle = { static_cast<float>(((((double)Position / Nodes) * Width) + X) *
			Settings.Screen_Size) - (Caption_Surface->w / 2), static_cast<float>(Y + 10) *
			Settings.Screen_Size, static_cast<float>(Caption_Surface->w), static_cast<float>(Caption_Surface->h) };
		SDL_Texture* Caption_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Caption_Surface);
		SDL_RenderTexture(Core.Renderer, Caption_Texture, NULL, &Caption_Rectangle);
		SDL_DestroySurface(Caption_Surface);
		SDL_DestroyTexture(Caption_Texture);
	}
}

void Drain_Query() {
	for (int Counter1 = 0; Counter1 < Temporary.Query.size(); Counter1++) {
		if (Temporary.ID_Query[Counter1] == 0) {
			Render_Outline(Temporary.Query[Counter1], Temporary.Color_Query[Counter1]);
		} else if (Temporary.ID_Query[Counter1] == 1) {
			double Length = std::sqrt(std::pow(Temporary.Query[Counter1].x -
				Temporary.Query[Counter1].w, 2) + std::pow(Temporary
				.Query[Counter1].y - Temporary.Query[Counter1].h, 2));
			double Rotation = std::atan2(Temporary.Query[Counter1].y -
				Temporary.Query[Counter1].h, Temporary.Query[Counter1].x -
				Temporary.Query[Counter1].w) / (M_PI / 180);
			SDL_FPoint Centerpoint = { 5.0f * Settings.Screen_Size,
				5.0f * Settings.Screen_Size };
			for (int Counter2 = 0; Counter2 < std::floor(Length /
				(Settings.Screen_Size * 10)); Counter2++) {
				SDL_FRect Tilebox = { 0.0f, 0.0f, Settings.Screen_Size *
					10.0f, Settings.Screen_Size * 10.0f };
				Tilebox.x = static_cast<float>(Temporary.Query[Counter1].x -
					((Counter2 * Settings.Screen_Size * 10) * cos(Rotation *
					(M_PI / 180))) - (5 * Settings.Screen_Size));
				Tilebox.y = static_cast<float>(Temporary.Query[Counter1].y -
					((Counter2 * Settings.Screen_Size * 10) * sin(Rotation *
					(M_PI / 180))) - (5 * Settings.Screen_Size));
				SDL_RenderTextureRotated(Core.Renderer,
					Textures.Path_Arrow, NULL, &Tilebox,
					Rotation + 90, &Centerpoint, SDL_FLIP_NONE);
			}
		}
	}
	Temporary.ID_Query.clear();
	Temporary.Query.clear();
	Temporary.Color_Query.clear();
}

void Render_Toolbar() {
	if (Interface.Tool > LDE_INVALID) {
		Set_Renderer_Color(Colors.Dark_Grey);
		SDL_FRect Backing_Rectangle = Rects.Tool[Interface.Tool];
		Backing_Rectangle.x = Backing_Rectangle.x - (2 * Settings.Screen_Size);
		Backing_Rectangle.w = Backing_Rectangle.w + (4 * Settings.Screen_Size);
		Backing_Rectangle.y = 330 * Settings.Screen_Size;
		Backing_Rectangle.h = 38 * Settings.Screen_Size;
		SDL_RenderFillRect(Core.Renderer, &Backing_Rectangle);
		Backing_Rectangle.y = 334 * Settings.Screen_Size;
		Backing_Rectangle.h = 34 * Settings.Screen_Size;
		Set_Renderer_Color(Colors.Light_Grey);
		SDL_RenderFillRect(Core.Renderer, &Backing_Rectangle);
		Clear_Renderer();
		Rects.Cap.x = Backing_Rectangle.x + Backing_Rectangle.w;
		Rects.Cap_Button.x = Rects.Cap.x + Rects.Cap.w + 12;
		Rects.Cap_Hitbox.Data[0] = Rects.Cap_Button;
		Rects.Cap_Hitbox.Data[1] = Rects.Cap_Button;
		Render_Button(Textures.Cap_Button.Data[0], Rects.Cap_Hitbox, 4);
		SDL_RenderTexture(Core.Renderer, Textures
			.Cap.Data[0], NULL, &Rects.Cap);
		Rects.Cap.x = Backing_Rectangle.x - Rects.Cap.w;
		Rects.Cap_Button.x = Rects.Cap.x -
			Rects.Cap_Button.w - 12;
		Rects.Cap_Hitbox.Data[0] = Rects.Cap_Button;
		Rects.Cap_Hitbox.Data[1] = Rects.Cap_Button;
		Render_Button(Textures.Cap_Button.Data[1], Rects.Cap_Hitbox, 5);
		SDL_RenderTexture(Core.Renderer, Textures.Cap
			.Data[1], NULL, &Rects.Cap);
		SDL_RenderTexture(Core.Renderer, Textures.Tool
			.Data[Interface.Tool], NULL, &Rects.Tool[Interface.Tool]);
	}
	if (Interface.Tool == 0) {
		std::string Machine_Text = Metadata.Machine_Names[Interface.Placing_Item - 1] + " | " +
			Abbreviate_Number(Interface.Queried_Price) + "LA";
		SDL_Surface* Machine_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Machine_Text.c_str(),
			Machine_Text.size(), Colors.Abyss_Black);
		SDL_FRect Machine_Rectangle = { static_cast<float>(312 * Settings.Screen_Size) -
			(Machine_Surface->w / 2), 290.0f * Settings.Screen_Size, Machine_Surface->w +
			static_cast<float>(16 * Settings.Screen_Size), TTF_GetFontHeight(
			Fonts.Subtext_Font) + static_cast<float>(18 * Settings.Screen_Size) };
		Set_Renderer_Color(Colors.Dark_Grey);
		SDL_RenderFillRect(Core.Renderer, &Machine_Rectangle);
		Machine_Rectangle.x = Machine_Rectangle.x + (4 * Settings.Screen_Size);
		Machine_Rectangle.y = Machine_Rectangle.y + (4 * Settings.Screen_Size);
		Machine_Rectangle.w = Machine_Rectangle.w - (8 * Settings.Screen_Size);
		Machine_Rectangle.h = Machine_Rectangle.h - (8 * Settings.Screen_Size);
		Set_Renderer_Color(Colors.Light_Grey);
		SDL_RenderFillRect(Core.Renderer, &Machine_Rectangle);
		Clear_Renderer();
		Machine_Rectangle.x = Machine_Rectangle.x + (4 * Settings.Screen_Size);
		Machine_Rectangle.y = Machine_Rectangle.y + (4 * Settings.Screen_Size);
		Machine_Rectangle.w = Machine_Surface->w;
		Machine_Rectangle.h = Machine_Surface->h;
		SDL_Texture* Machine_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Machine_Surface);
		SDL_RenderTexture(Core.Renderer, Machine_Texture, NULL, &Machine_Rectangle);
		SDL_DestroySurface(Machine_Surface);
		SDL_DestroyTexture(Machine_Texture);
	}
}

void Verify_Settings() {
	bool Keybinds_Altered = false;
	for (int Counter = 0; Counter < Keybinds.Keybind_Settings.size(); Counter++) {
		if (Keybinds.Keybind_Settings[Counter] != Keybinds.Keybind_List[Counter]) {
			Keybinds_Altered = true;
			break;
		}
	}
	if (Settings.Screen_Size != Interface.Slider_Positions[0] + 1 || Keybinds_Altered ||
		static_cast<int>(Settings.AA_Temporary) != Settings.Anti_Aliasing ||
		static_cast<int>(Settings.VS_Temporary) != Settings.VSync || Settings.Raw_FPS !=
		Interface.Slider_Positions[4] || Settings.Volume != Interface.Slider_Positions[5] ||
		Interface.Slider_Positions[6] != Settings.Fullscreen) {
		Render_Button(Textures.Apply, Rects.Apply, 2);
		Render_Button(Textures.Cancel, Rects.Cancel, 3);
	}
}

void Render_Tile_Prompts() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = static_cast<int>(((Column * 40) -
			Interface.Camera_X) * Settings.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = static_cast<int>(((Row * 40) -
				Interface.Camera_Y) * Settings.Screen_Size);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				for (int Counter = 0; Counter < Metadata.Quirk_Positions[2].size(); Counter++) {
						if (Visual_To_ID(Data.Visual_Grid[Column][Row]) ==
							Metadata.Quirk_Positions[2][Counter]) {
						std::string Subcore = SDL_GetKeyName(Keybinds.Keybind_List[10]);
						for (int Counter = 0; Counter < Subcore.size(); Counter++) {
							Subcore[Counter] = static_cast<char>(std::tolower(Subcore[Counter]));
						}
						Subcore = "interact - (\"" + Subcore + "\")";
						SDL_Surface* Carrying_Surface = TTF_RenderText_Blended(
							Fonts.Halftext_Font, Subcore.c_str(),
							Subcore.size(), Colors.Cherry_Blossom);
						SDL_FRect Carrying_Rectangle = { static_cast<float>(320 * Settings.Screen_Size) -
							(Carrying_Surface->w / 2), 320.0f *	Settings.Screen_Size, static_cast<float>(
							Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
						SDL_Texture* Carrying_Texture = SDL_GenerateTextureFromSurface(
							Core.Renderer, Carrying_Surface);
						Render_Box((Carrying_Rectangle.x / Settings.Screen_Size) - 4,
							(Carrying_Rectangle.y / Settings.Screen_Size) - 4,
							(Carrying_Rectangle.w / Settings.Screen_Size) + 8,
							(Carrying_Rectangle.h / Settings.Screen_Size) + 8,
							Colors.Light_Grey, Colors.Dark_Grey);
						SDL_RenderTexture(Core.Renderer, Carrying_Texture, NULL, &Carrying_Rectangle);
						SDL_DestroySurface(Carrying_Surface);
						SDL_DestroyTexture(Carrying_Texture);
					}
				}
			}
		}
	}
}

void Render_Interaction() {
	int Indexes[7] = { 4, 3, 5, 6, 7, 8, 10 };
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = static_cast<int>(((Column * 40) -
			Interface.Camera_X) * Settings.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = static_cast<int>(((Row * 40) -
				Interface.Camera_Y) * Settings.Screen_Size);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				for (int Counter = 0; Counter < Metadata.Quirk_Positions[2].size(); Counter++) {
					if (Visual_To_ID(Data.Visual_Grid[Column][Row]) ==
						Metadata.Quirk_Positions[2][Counter]) {
						Interface.Prompt_Identifier = Indexes[Counter];
						Interface.Building = false;
						Interface.Target_Tile.X = Column;
						Interface.Target_Tile.Y = Row;
						switch (Visual_To_ID(Data.Visual_Grid[Column][Row])) {
						case Money_Generator:
							Interface.Slider_Positions[8] = Data.Settings_Grid
								[Interface.Target_Tile.X][Interface.Target_Tile.Y][3];
							break;
						case Fluid_Generator:
							Interface.Slider_Positions[9] = Data.Settings_Grid
								[Interface.Target_Tile.X][Interface.Target_Tile.Y][3];
							Interface.Slider_Positions[10] = Data.Settings_Grid
								[Interface.Target_Tile.X][Interface.Target_Tile.Y][4] / 5;
							for (int Counter = 0; Counter < Interface.Valve300_Postions.size(); Counter++) {
								if (Data.Settings_Grid[Interface.Target_Tile.X]
									[Interface.Target_Tile.Y][5] == Interface.Valve300_Postions[Counter]) {
									Interface.Slider_Positions[11] = Counter;
									break;
								}
							}
							break;
						default:
							break;
						}
						break;
					}
				}
				return;
			}
		}
	}
}

void Render_Effects() {
	if (Interface.Effects[Heat] > 0) {
		//std::cout << "boilin'" << " ";
	}
}

void Find_Effect() {
	Interface.Effects[Heat] = 0;
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			for (int Counter = 0; Counter < Metadata.Heating_Machines.size(); Counter++) {
				if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Metadata.Heating_Machines[Counter] &&
					X * 40 > Interface.Camera_X && Y * 40 > Interface.Camera_Y && X * 40 <
					Interface.Camera_X + 640 && Y * 40 < Interface.Camera_Y + 360) {
					Interface.Effects[Heat] += 0.1;
				}
			}
		}
	}
}

void Cache_Blueprint() {
	int Width;
	int Height;
	ID_To_Size(Interface.Placing_Item - 1, Interface.Placing_Rotation, Width, Height);
	int Maximum = (Width > Height ? Width : Height) * Settings.Screen_Size * 40;
	SDL_DestroyTexture(Cache.Blueprint_Cache);
	Cache.Blueprint_Cache = SDL_GenerateTexture(Core.Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Maximum, Maximum);
	SDL_SetTextureBlendMode(Cache.Blueprint_Cache, SDL_BLENDMODE_BLEND);
	SDL_Texture* Backing = SDL_GenerateTexture(Core.Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width *
		Settings.Screen_Size * 40, Height * Settings.Screen_Size * 40);
	SDL_SetTextureBlendMode(Backing, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Backing);
	for (int X = 0; X < Width; X++) {
		for (int Y = 0; Y < Height; Y++) {
			SDL_FRect Pasting_Rectangle = Rects.Tile_1x1;
			Pasting_Rectangle.x = X * Settings.Screen_Size * 40;
			Pasting_Rectangle.y = Y * Settings.Screen_Size * 40;
			SDL_RenderTexture(Core.Renderer, Textures.Tile_Texture,
				NULL, &Pasting_Rectangle);
		}
	}
	SDL_SetRenderTarget(Core.Renderer, Cache.Blueprint_Cache);
	SDL_RenderTexture(Core.Renderer, Backing, NULL, NULL);
	SDL_DestroyTexture(Backing);
	int Rotation = Interface.Placing_Rotation * 90;
	for (int Counter = 0; Counter < Metadata.Quirk_Positions[0].size(); Counter++) {
		if (Metadata.Quirk_Positions[0][Counter] == Interface.Placing_Item - 1) {
			Rotation = 0;
		}
	}
	SDL_FPoint Centerpoint = { Maximum * 0.5f, Maximum * 0.5f };
	SDL_RenderTextureRotated(Core.Renderer, Metadata.Machine_Sprites
		[Interface.Placing_Item - 1], NULL, NULL, Rotation, &Centerpoint, SDL_FLIP_NONE);
	SDL_SetRenderTarget(Core.Renderer, NULL);
	SDL_SetTextureAlphaMod(Cache.Blueprint_Cache, 190);
}

void Cache_Price() {
	Interface.Queried_Price = static_cast<int>((Metadata.Machine_Prices[Interface.Placing_Item - 1] *
		1.1)) +	Metadata.Machine_Taxes[Interface.Placing_Item - 1] + 1;
}