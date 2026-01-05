#include <Legacy_UI.hpp>

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
		Hitbox.x = static_cast<int>((Column * 40) - Core.Camera.X) * Settings.Screen_Size;
		Invisible_Hitbox.x = static_cast<int>((Column * 40) - Core.Camera.X) * Settings.Screen_Size;
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Hitbox.y = static_cast<int>((Row * 40) - Core.Camera.Y) * Settings.Screen_Size;
			Invisible_Hitbox.y = static_cast<int>((Row * 40) - Core.Camera.Y) * Settings.Screen_Size;
			if (Detect_Mouse_Collision(Invisible_Hitbox)) {
				if ((Hitbox.x + Hitbox.w <= ((LDE_GRIDSIZE * 40) - Core.Camera.X) * Settings.Screen_Size &&
					Hitbox.y + Hitbox.h <= ((LDE_GRIDSIZE * 40) - Core.Camera.Y) * Settings.Screen_Size)
					|| (Size_X != 2 && Size_Y != 2)) {
					bool Placeable = Check_Clearance(Column, Row, Size_X, Size_Y);
					if ((Interface.Placing_Item == Command_Platform + 1 && Data.CMD_Placed) ||
						(Interface.Placing_Item == Submarine_Dock + 1 && Row != 0)) {
						Placeable = false;
					}
					if (Placeable) {
						Render_Outline(Hitbox, Colors.Pure_White, 1);
					} else {
						SDL_SetTextureColorMod(Cache.Blueprint_Cache, Colors.Hostile_Red.r,
							Colors.Hostile_Red.g, Colors.Hostile_Red.b);
						Render_Outline(Hitbox, Colors.Hostile_Red, 1);
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
	char Buffer[64];
	char Subbuffer[64];
	Abbreviate_Number(Data.Funds, Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "%sLA", Subbuffer);
	Render_Dynamic_Text(Fonts.Halftext_Font, Buffer, Colors.Abyss_Black, 10, 30);
	memset(Buffer, 0, sizeof(Buffer));
	snprintf(Buffer, sizeof(Buffer), "%s, %sday", Time.c_str(), Metadata.Days[Data.Day]);
	Render_Dynamic_Text(Fonts.Halftext_Font, Buffer, Colors.Abyss_Black, 10, 50);
	if (Interface.Tool == 2) {
		double Content_Vector[7] = { 0, 0, 0, 0, LDE_INVALID, 0, 0 };
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			Rects.Tile_1x1.x = static_cast<int>(((Column * 40) - Core.Camera.X) * Settings.Screen_Size);
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				Rects.Tile_1x1.y = static_cast<int>(((Row * 40) - Core.Camera.Y) * Settings.Screen_Size);
				if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
					memcpy(Content_Vector, Data.Data_Grid[Column][Row], sizeof(Content_Vector));
				}
			}
		}
		Item_Stack Returned_Item = Get_Item_Stack_Data();
		if (Returned_Item.Identifier != LDE_INVALID) {
			char Buffer[64];
			snprintf(Buffer, sizeof(Buffer), "Item: %s", Returned_Item.Display_Name);
			std::string qmp = Buffer;
			Queried_Data_Fragments.push_back(qmp);
			char Subbuffer[64];
			Truncate(Returned_Item.Temperature, 0, Subbuffer, sizeof(Subbuffer));
			snprintf(Buffer, sizeof(Buffer), "%s°F", Subbuffer);
			std::string tmp = Buffer;
			Queried_Data_Fragments.push_back(tmp);
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
				char Buffer[64];
				char Subbuffer[64];
				Abbreviate_Number(Pressure, Subbuffer, sizeof(Subbuffer));
				snprintf(Buffer, sizeof(Buffer), "%s bar liquid", Subbuffer);
				std::string tmp = Buffer;
				Queried_Data_Fragments.push_back(tmp);
			}
			if (Content_Vector[1] != 0) {
				char Buffer[64];
				char Subbuffer1[64];
				Truncate(Content_Vector[0] * Multiplier, Get_Depth(Content_Vector[1] * Multiplier),
					Subbuffer1, sizeof(Subbuffer1));
				char Subbuffer2[64];
				Abbreviate_Number(Content_Vector[1] * Multiplier, Subbuffer2, sizeof(Subbuffer2));
				snprintf(Buffer, sizeof(Buffer), "%s / %sL.", Subbuffer1, Subbuffer2);
				std::string tmp = Buffer;
				Queried_Data_Fragments.push_back(tmp);
			}
		} else {
			if (Content_Vector[1] != 0) {
				char Buffer[64];
				char Subbuffer1[64];
				Truncate(0, 0, Subbuffer1, sizeof(Subbuffer1));
				char Subbuffer2[64];
				Abbreviate_Number(Content_Vector[1], Subbuffer2, sizeof(Subbuffer2));
				snprintf(Buffer, sizeof(Buffer), "%s / %sL.", Subbuffer1, Subbuffer2);
				std::string tmp = Buffer;
				Queried_Data_Fragments.push_back(tmp);
			}
		}
		if (Content_Vector[3] != 0) {
			char Buffer[64];
			char Subbuffer1[64];
			char Subbuffer2[64];
			Truncate(Content_Vector[2], Get_Depth(Content_Vector[3]), Subbuffer1, sizeof(Subbuffer1));
			Abbreviate_Number(Content_Vector[3], Subbuffer2, sizeof(Subbuffer2));
			snprintf(Buffer, sizeof(Buffer), "%s / %sJ.", Subbuffer1, Subbuffer2);
			std::string str = Buffer;
			Queried_Data_Fragments.push_back(str);
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
		Fading_Color.a = (uint8_t)(ceil(((double)Interface.Save_Frames / (Interface.Frame_Rate * 2)) * 255));
		char Buffer[] = "Data saved!";
		Render_Dynamic_Text(Fonts.Subtext_Font, Buffer, Fading_Color, LDE_INVALID, 300);
		Interface.Save_Frames--;
	}
}

void Render_Saveloader() {
	SDL_RenderTexture(Core.Renderer, Textures.Saveloader,
		NULL, &Rects.Saveloader);
	for (int Counter = 0; Counter < 4; Counter++) {
		if (Core.Save_Filesizes[Counter] > 0) {
			Render_Button(Textures.Load.Data[Counter], Rects.Load.Data[Counter], Counter + 6, Colors.Cherry_Blossom);
			Render_Button(Textures.Clear.Data[Counter], Rects.Clear.Data[Counter], Counter + 10, Colors.Cherry_Blossom);
		} else {
			Render_Button(Textures.New.Data[Counter], Rects.New.Data[Counter], Counter + 2, Colors.Cherry_Blossom);
		}
	}
	for (int Counter = 0; Counter < 4; Counter++) {
		char Buffer[64];
		char Subbuffer[64];
		Abbreviate_Number(Core.Save_Filesizes[Counter], Subbuffer, sizeof(Subbuffer));
		Render_Dynamic_Text(Fonts.Subtext_Font, Buffer, Colors.Abyss_Black, 40, (Counter * 40) + 160);
	}
}

void Render_Prompts() {
	if (Interface.Prompt_Identifier != LDE_INVALID) {
		Interface_Functions[Interface.Prompt_Identifier](
			Interface.Target_Tile.X, Interface.Target_Tile.Y);
	}
}

void Render_Slider(char Labels[256][32], int Engagement, int Nodes, int Selection, int &Position,
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
			if (Core.Mouse.X < Separators[0]) {
				Position = 0;
			} else if (Core.Mouse.X >= Separators[Nodes - 1]) {
				Position = Nodes;
			} else if (Core.Mouse.X >= Separators[Counter] && Core.Mouse.X < Separators[Counter + 1]) {
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
		SDL_Surface* Caption_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Labels[Position],
			strlen(Labels[Position]), Primary);
		SDL_FRect Caption_Rectangle = {
			(float)(((((double)Position / Nodes) * Width) + X) * Settings.Screen_Size) - (float)(Caption_Surface->w * 0.5),
			(float)(Y + 10) * Settings.Screen_Size,
			(float)(Caption_Surface->w),
			(float)(Caption_Surface->h)
		};
		SDL_Texture* Caption_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Caption_Surface);
		SDL_RenderTexture(Core.Renderer, Caption_Texture, NULL, &Caption_Rectangle);
		SDL_DestroySurface(Caption_Surface);
		SDL_DestroyTexture(Caption_Texture);
	}
}

void Drain_Query() {
	for (int Counter1 = 0; Counter1 < Temporary_L.Query.size(); Counter1++) {
		if (Temporary_L.ID_Query[Counter1] == 0) {
			Render_Outline(Temporary_L.Query[Counter1], Temporary_L.Color_Query[Counter1], 1);
		} else if (Temporary_L.ID_Query[Counter1] == 1) {
			double Length = std::sqrt(std::pow(Temporary_L.Query[Counter1].x -
				Temporary_L.Query[Counter1].w, 2) + std::pow(Temporary_L
				.Query[Counter1].y - Temporary_L.Query[Counter1].h, 2));
			double Rotation = std::atan2(Temporary_L.Query[Counter1].y -
				Temporary_L.Query[Counter1].h, Temporary_L.Query[Counter1].x -
				Temporary_L.Query[Counter1].w) / (M_PI / 180);
			SDL_FPoint Centerpoint = { 5.0f * Settings.Screen_Size,
				5.0f * Settings.Screen_Size };
			for (int Counter2 = 0; Counter2 < std::floor(Length /
				(Settings.Screen_Size * 10)); Counter2++) {
				SDL_FRect Tilebox = { 0.0f, 0.0f, Settings.Screen_Size *
					10.0f, Settings.Screen_Size * 10.0f };
				Tilebox.x = static_cast<float>(Temporary_L.Query[Counter1].x -
					((Counter2 * Settings.Screen_Size * 10) * cos(Rotation *
					(M_PI / 180))) - (5 * Settings.Screen_Size));
				Tilebox.y = static_cast<float>(Temporary_L.Query[Counter1].y -
					((Counter2 * Settings.Screen_Size * 10) * sin(Rotation *
					(M_PI / 180))) - (5 * Settings.Screen_Size));
				SDL_RenderTextureRotated(Core.Renderer,
					Textures.Path_Arrow, NULL, &Tilebox,
					Rotation + 90, &Centerpoint, SDL_FLIP_NONE);
			}
		}
	}
	Temporary_L.ID_Query.clear();
	Temporary_L.Query.clear();
	Temporary_L.Color_Query.clear();
}