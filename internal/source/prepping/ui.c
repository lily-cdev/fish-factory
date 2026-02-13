#include <ui.h>

void (*Interface_Functions[11])(int X, int Y) = {
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

void Clear_Renderer() {
	SDL_SetRenderDrawColor(Core.Renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
}

void Set_Renderer_Color(const SDL_Color Color) {
	SDL_SetRenderDrawColor(Core.Renderer, Color.r, Color.g, Color.b, SDL_ALPHA_OPAQUE);
}

void Render_Outline(SDL_FRect Rectangle, SDL_Color Color, int Multiplier) {
	Set_Renderer_Color(Color);
	for (int C1 = 0; C1 < LDE_BORDERWIDTH * Settings.Screen_Size * Multiplier; C1++) {
		SDL_RenderRect(Core.Renderer, &Rectangle);
		Rectangle.x++;
		Rectangle.y++;
		Rectangle.w -= 2;
		Rectangle.h -= 2;
	}
	Clear_Renderer();
}

void Render_Box(int X, int Y, int W, int H, SDL_Color Inner_Color, SDL_Color Outer_Color) {
	SDL_FRect External_Rectangle = { (float)(X - 4) * Settings.Screen_Size,
		(float)(Y - 4) * Settings.Screen_Size, (float)(W + 8) *
		Settings.Screen_Size, (float)(H + 8) * Settings.Screen_Size };
	Set_Renderer_Color(Outer_Color);
	SDL_RenderFillRect(Core.Renderer, &External_Rectangle);
	SDL_FRect Internal_Rectangle = { (float)(X * Settings.Screen_Size),
		(float)(Y * Settings.Screen_Size), (float)(W *
		Settings.Screen_Size), (float)(H * Settings.Screen_Size) };
	Set_Renderer_Color(Inner_Color);
	SDL_RenderFillRect(Core.Renderer, &Internal_Rectangle);
	Clear_Renderer();
}

SDL_FRect Buffer_Rectangle(const SDL_FRect Source, const int X, const int Y) {
	SDL_FRect Yield = { Source.x - (X * Settings.Screen_Size), Source.y - (Y * Settings.Screen_Size),
		Source.w + ((X * 2) * Settings.Screen_Size), Source.h + ((Y * 2) * Settings.Screen_Size) };
	return Yield;
}

void Render_Blueprint(int Size_X, int Size_Y) {
	SDL_FRect Hitbox = { 0, 0, (float)(Size_X * LDE_TILESIZE) * Settings.Screen_Size, (float)(Size_Y * LDE_TILESIZE) *
		Settings.Screen_Size };
	SDL_FRect Invisible_Hitbox = { 0, 0, Settings.Screen_Size * (float)LDE_TILESIZE, Settings.Screen_Size *
		(float)LDE_TILESIZE };
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Hitbox.x = (int)((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
		Invisible_Hitbox.x = (int)((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Hitbox.y = (int)((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
			Invisible_Hitbox.y = (int)((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
			if (Detect_Mouse_Collision(Invisible_Hitbox)) {
				if ((Hitbox.x + Hitbox.w <= ((LDE_GRIDSIZE * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size &&
					Hitbox.y + Hitbox.h <= ((LDE_GRIDSIZE * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size)
					|| (Size_X != 2 && Size_Y != 2)) {
					bool Placeable = Check_Clearance(Column, Row, Size_X, Size_Y);
					if ((Interface.Item == Command_Platform + 1 && Data.CMD_Placed) || (Interface.Item == Submarine_Dock +
						1 && Row != 0)) {
						Placeable = false;
					}
					if (Placeable) {
						Render_Outline(Hitbox, Colors.Pure_White, 1);
					} else {
						SDL_SetTextureColorMod(Cache.Blueprint_Cache, Colors.Hostile_Red.r, Colors.Hostile_Red.g,
							Colors.Hostile_Red.b);
						Render_Outline(Hitbox, Colors.Hostile_Red, 1);
					}
					Render_Texture(Cache.Blueprint_Cache, &Hitbox);
					SDL_SetTextureColorMod(Cache.Blueprint_Cache, 255, 255, 255);
					return;
				}
			}
		}
	}
}

void Render_Sidebar(SDL_Texture* Texture, SDL_FRect Rectangle, int Selection) {
	if (Detect_Mouse_Collision(Rectangle)) {
		Rectangle.x = (Settings.Screen_Size * 640) - Rectangle.w;
		Interface.UI_Selection = Selection;
	} else {
		Rectangle.x = (Settings.Screen_Size * 654) - Rectangle.w;
	}
	Render_Texture(Texture, &Rectangle);
}

void Render_Game_UI() {
	if (Interface.Tool == LDE_INVALID && Interface.Prompt_Identifier == LDE_INVALID) {
		Render_Sidebar(Textures.Help_Sidebutton, Rects.Help, 1);
		Render_Sidebar(Textures.Save_Sidebutton, Rects.Save, 2);
		Render_Sidebar(Textures.Recipe_Sidebutton, Rects.Recipe, 3);
		Render_Sidebar(Textures.Exit_Sidebutton, Rects.Exit, 4);
	}
	char Data_Fragments[16][128];
	int Index = 0;
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
	char Time[64];
	snprintf(Time, sizeof(Time), "%02i:%02i%cM", Hour, Minute, (Afternoon) ? 'P' : 'A');
	char Buffer[64];
	char Subbuffer[64];
	Abbreviate_Number(Data.Funds, Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "%sLA", Subbuffer);
	Process_Supply(&Supplies.Money, Buffer, Fonts.Halftext_Font, Colors.Abyss_Black, 10, 30);
	memset(Buffer, 0, sizeof(Buffer));
	snprintf(Buffer, sizeof(Buffer), "%s, %sday", Time, Metadata.Days[Data.Day]);
	Process_Supply(&Supplies.Time, Buffer, Fonts.Halftext_Font, Colors.Abyss_Black, 10, 50);
	if (Interface.Tool == 2) {
		float Content_Vector[7] = { 0, 0, 0, 0, LDE_INVALID, 0, 0 };
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			Rects.Tile_1x1.x = (float)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size);
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				Rects.Tile_1x1.y = (float)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size);
				if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
					memcpy(Content_Vector, Data.Data_Grid[Column][Row], sizeof(Content_Vector));
				}
			}
		}
		Item_Stack Returned_Item = Get_Item_Stack_Data();
		if (Returned_Item.Identifier != LDE_INVALID) {
			char Buffer[64];
			snprintf(Buffer, sizeof(Buffer), "Item: %s", Returned_Item.Display_Name);
			strncpy(Data_Fragments[Index], Buffer, sizeof(Data_Fragments[Index]));
			Index++;
			char Subbuffer[64];
			Truncate(Returned_Item.Temperature, 0, Subbuffer, sizeof(Subbuffer));
			snprintf(Buffer, sizeof(Buffer), "%s °F", Subbuffer);
			strncpy(Data_Fragments[Index], Buffer, sizeof(Data_Fragments[Index]));
			Index++;
			float Pressure = Calculate_Pressure(Returned_Item.Temperature, Returned_Item.Boiling_Point,
				Returned_Item.Vaporisation_Enthalpy);
			int Multiplier = 1;
			if (Pressure == LDE_INVALID) {
				strncpy(Data_Fragments[Index], "gas", sizeof(Data_Fragments[Index]));
				Index++;
				Multiplier = 10;
			} else {
				if (Pressure < 1) {
					Pressure = 1;
				}
				char Buffer[64];
				char Subbuffer[64];
				Abbreviate_Number(Pressure, Subbuffer, sizeof(Subbuffer));
				snprintf(Buffer, sizeof(Buffer), "%s bar liquid", Subbuffer);
				strncpy(Data_Fragments[Index], Buffer, sizeof(Data_Fragments[Index]));
				Index++;
			}
			if (Content_Vector[1] != 0) {
				char Buffer[64];
				char Subbuffer1[64];
				Truncate(Content_Vector[0] * Multiplier, Get_Depth(Content_Vector[1] * Multiplier), Subbuffer1,
					sizeof(Subbuffer1));
				char Subbuffer2[64];
				Abbreviate_Number(Content_Vector[1] * Multiplier, Subbuffer2, sizeof(Subbuffer2));
				snprintf(Buffer, sizeof(Buffer), "%s / %sL.", Subbuffer1, Subbuffer2);
				strncpy(Data_Fragments[Index], Buffer, sizeof(Data_Fragments[Index]));
				Index++;
			}
		} else {
			if (Content_Vector[1] != 0) {
				char Buffer[64];
				char Subbuffer1[64];
				Truncate(0, 0, Subbuffer1, sizeof(Subbuffer1));
				char Subbuffer2[64];
				Abbreviate_Number(Content_Vector[1], Subbuffer2, sizeof(Subbuffer2));
				snprintf(Buffer, sizeof(Buffer), "%s / %sL.", Subbuffer1, Subbuffer2);
				strncpy(Data_Fragments[Index], Buffer, sizeof(Data_Fragments[Index]));
				Index++;
			}
		}
		if (Content_Vector[3] != 0) {
			char Buffer[64];
			char Subbuffer1[64];
			char Subbuffer2[64];
			Truncate(Content_Vector[2], Get_Depth(Content_Vector[3]), Subbuffer1, sizeof(Subbuffer1));
			Abbreviate_Number(Content_Vector[3], Subbuffer2, sizeof(Subbuffer2));
			snprintf(Buffer, sizeof(Buffer), "%s / %sJ.", Subbuffer1, Subbuffer2);
			strncpy(Data_Fragments[Index], Buffer, sizeof(Data_Fragments[Index]));
			Index++;
		}
		if (Index <= 0) {
			strncpy(Data_Fragments[Index], "No data", sizeof(Data_Fragments[Index]));
			Index++;
		}
		strncpy(Data_Fragments[Index], NULLSTRING, sizeof(Data_Fragments[Index]));
		Index++;
		int Fragment_Size = veclen(Data_Fragments), Max_Width = 0;
		SDL_Texture* Fragment_Textures[16];
		SDL_FRect Fragment_Rectangles[16];
		for (int C1 = 0; C1 < Fragment_Size; C1++) {
			SDL_Surface* Fragment_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Data_Fragments[C1], 0,
				Colors.Abyss_Black);
			Max_Width = max(Max_Width, Fragment_Surface->w);
			SDL_Texture* Fragment_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Fragment_Surface);
			Fragment_Textures[C1] = Fragment_Texture;
			Fragment_Rectangles[C1] = (SDL_FRect){
				(float)(Settings.Screen_Size * 630) - Fragment_Surface->w,
				(float)((C1 * 20) + 10) * Settings.Screen_Size,
				(float)(Fragment_Surface->w),
				(float)(Fragment_Surface->h)
			};
			SDL_DestroySurface(Fragment_Surface);
		}
		int Total_Height = Fragment_Rectangles[Fragment_Size - 1].y + Fragment_Rectangles[Fragment_Size - 1].h;
		Set_Renderer_Color(Colors.Dark_Grey);
		SDL_FRect Background_Rectangle = {
			(float)(Settings.Screen_Size * 615) - Max_Width,
			0,
			(float)(Settings.Screen_Size * 25) + Max_Width,
			(float)(Settings.Screen_Size * 15) + Total_Height
		};
		SDL_RenderFillRect(Core.Renderer, &Background_Rectangle);
		Set_Renderer_Color(Colors.Light_Grey);
		Background_Rectangle = (SDL_FRect){
			(float)(Settings.Screen_Size * 620) - Max_Width,
			0,
			(float)(Settings.Screen_Size * 20) + Max_Width,
			(float)(Settings.Screen_Size * 10) + Total_Height
		};
		SDL_RenderFillRect(Core.Renderer, &Background_Rectangle);
		Clear_Renderer();
		for (int C1 = 0; C1 < Fragment_Size; C1++) {
			Render_Texture(Fragment_Textures[C1], &Fragment_Rectangles[C1]);
			free_texture(Fragment_Textures[C1]);
		}
	}
	if (Interface.Save_Frames > 0) {
		SDL_Color Fading_Color = Colors.Cherry_Blossom;
		Fading_Color.a = (uint8_t)(ceil(((float)Interface.Save_Frames / (Interface.Frame_Rate * 2)) * 255));
		char Buffer[16] = "Data saved!";
		Process_Supply(&Supplies.Save_Text, Buffer, Fonts.Subtext_Font, Fading_Color, LDE_INVALID, 300);
		Interface.Save_Frames--;
	}
}

void Render_Saveloader() {
	Render_Texture(Textures.Saveloader, &Rects.Saveloader);
	for (int C1 = 0; C1 < LDE_SAVEFILES; C1++) {
		if (Core.Save_Filesizes[C1] > 0) {
			Render_Button(&Textures.Load.Data[C1], &Rects.Load.Data[C1], C1 + 6, Colors.Cherry_Blossom);
			Render_Button(&Textures.Clear.Data[C1], &Rects.Clear.Data[C1], C1 + 10, Colors.Cherry_Blossom);
		} else {
			Render_Button(&Textures.New.Data[C1], &Rects.New.Data[C1], C1 + 2, Colors.Cherry_Blossom);
		}
	}
	for (int C1 = 0; C1 < LDE_SAVEFILES; C1++) {
		char Buffer[64];
		char Subbuffer[64];
		Abbreviate_Number(Core.Save_Filesizes[C1], Subbuffer, sizeof(Subbuffer));
		snprintf(Buffer, sizeof(Buffer), "Slot %i (%sb)", C1 + 1, Subbuffer);
		Process_Supply(&Supplies.Filesizes[C1], Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, 40, (C1 * 40) + 160);
	}
}

void Render_Prompts() {
	if (Interface.Prompt_Identifier != LDE_INVALID) {
		Interface_Functions[Interface.Prompt_Identifier](Interface.Tile.X, Interface.Tile.Y);
	}
}

void Drain_Query() {
	for (int C1 = 0; C1 < Cache.Query_Length; C1++) {
		if (Cache.ID_Query[C1] == 0) {
			Render_Outline(Cache.Query[C1], Cache.Color_Query[C1], 1);
		} else if (Cache.ID_Query[C1] == 1) {
			float Length = sqrt(pow(Cache.Query[C1].x - Cache.Query[C1].w, 2) + pow(Cache.Query[C1].y - Cache.Query[C1].h, 2));
			float Rotation = atan2(Cache.Query[C1].y - Cache.Query[C1].h, Cache.Query[C1].x - Cache.Query[C1].w) / (M_PI /
				180);
			SDL_FPoint Centerpoint = { Settings.Screen_Size * 5.0f, Settings.Screen_Size * 5.0f };
			for (int C2 = 0; C2 < floor(Length / (Settings.Screen_Size * 10)); C2++) {
				SDL_FRect Tilebox = { 0.0f, 0.0f, Settings.Screen_Size * 10.0f, Settings.Screen_Size * 10.0f };
				Tilebox.x = (float)(Cache.Query[C1].x - ((C2 * Settings.Screen_Size * 10) * cos(Rotation * (M_PI / 180))) -
					(Settings.Screen_Size * 5));
				Tilebox.y = (float)(Cache.Query[C1].y - ((C2 * Settings.Screen_Size * 10) * sin(Rotation * (M_PI / 180))) -
					(Settings.Screen_Size * 5));
				SDL_RenderTextureRotated(Core.Renderer, Textures.Path_Arrow, NULL, &Tilebox, Rotation + 90, &Centerpoint,
					SDL_FLIP_NONE);
			}
		}
	}
	Cache.Query_Length = 0;
}