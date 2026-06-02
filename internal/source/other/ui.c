#include <ui.h>

void (*Interface_Functions[12])(Point Pos) = {
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
	Render_MT_Input,
	Render_P_Generator
};

void Clear_Renderer() {
	SDL_SetRenderDrawColor(Core.Renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
}

void Set_Renderer_Color(const SDL_Color Color) {
	SDL_SetRenderDrawColor(Core.Renderer, Color.r, Color.g, Color.b, SDL_ALPHA_OPAQUE);
}

void Render_Outline(SDL_FRect Rectangle, SDL_Color Color, int Multiplier) {
	Set_Renderer_Color(Color);
	for (int C1 = 0; C1 < ktn_scale(ktn_border_width * Multiplier); C1++) {
		SDL_RenderRect(Core.Renderer, &Rectangle);
		Rectangle.x++;
		Rectangle.y++;
		Rectangle.w -= 2;
		Rectangle.h -= 2;
	}
	Clear_Renderer();
}

void Render_Box(Point Pos, int W, int H, SDL_Color Inner_Color, SDL_Color Outer_Color) {
	SDL_FRect External_Rectangle = { ktn_fscale(Pos.X - 4), ktn_fscale(Pos.Y - 4), ktn_fscale(W + 8), ktn_fscale(H + 8) };
	Set_Renderer_Color(Outer_Color);
	SDL_RenderFillRect(Core.Renderer, &External_Rectangle);
	SDL_FRect Internal_Rectangle = { ktn_fscale(Pos.X), ktn_fscale(Pos.Y), ktn_fscale(W), ktn_fscale(H) };
	Set_Renderer_Color(Inner_Color);
	SDL_RenderFillRect(Core.Renderer, &Internal_Rectangle);
	Clear_Renderer();
}

SDL_FRect Buffer_Rectangle(const SDL_FRect Source, Point Pos) {
	SDL_FRect Yield = {
		Source.x - ktn_fscale(Pos.X),
		Source.y - ktn_fscale(Pos.Y),
		Source.w + ktn_fscale(Pos.X * 2.0f),
		Source.h + ktn_fscale(Pos.Y * 2.0f)
	};
	return Yield;
}

void Render_Blueprint(int Size_X, int Size_Y) {
	if (!Cache.Blueprint_Cache) {
		return;
	}
	SDL_FRect Hitbox = { 0.0f, 0.0f, ktn_fscale(Size_X * ktn_tile_size), ktn_fscale(Size_Y * ktn_tile_size) };
	SDL_FRect Invisible_Hitbox = { 0.0f, 0.0f, ktn_fscale(ktn_tile_size), ktn_fscale(ktn_tile_size) };
	for (int Column = 0; Column < ktn_grid_size; Column++) {
		Hitbox.x = ktn_fscale((Column * ktn_tile_size) - Core.Camera.X);
		Invisible_Hitbox.x = ktn_fscale((Column * ktn_tile_size) - Core.Camera.X);
		for (int Row = 0; Row < ktn_grid_size; Row++) {
			Hitbox.y = ktn_fscale((Row * ktn_tile_size) - Core.Camera.Y);
			Invisible_Hitbox.y = ktn_fscale((Row * ktn_tile_size) - Core.Camera.Y);
			if (!Detect_Mouse_Collision(Invisible_Hitbox)) {
				continue;
			}
			if ((Hitbox.x + Hitbox.w <= ktn_fscale((ktn_grid_size * ktn_tile_size) - Core.Camera.X) && Hitbox.y + Hitbox.h <=
				ktn_fscale((ktn_grid_size * ktn_tile_size) - Core.Camera.Y)) || (Size_X != 2 && Size_Y != 2)) {
				bool Placeable = Check_Clearance((Point){ Column, Row }, Size_X, Size_Y);
				if ((Data.CMD_Placed && Interface.Item->Command) || (Row != 0 && ktn_stricmp(Interface.Item->Index, "sub_dock"))) {
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

void Render_Game_UI() {
	SDL_FRect Rectangles[4] = { Rects.Help, Rects.Save, Rects.Recipe, Rects.Exit };
	SDL_Texture* Bars[4] = { Textures.Help_Sidebutton, Textures.Save_Sidebutton, Textures.Recipe_Sidebutton,
		Textures.Exit_Sidebutton };
	if (Interface.Tool == T_None && Interface.Prompt_Identifier == ktn_invalid) {
		for (int C1 = 0; C1 < 4; C1++) {
			if (Detect_Mouse_Collision(Rectangles[C1])) {
				Rectangles[C1].x = Core.Screensize.X - Rectangles[C1].w;
				Interface.UI_Query = (UI_Link){ Click_Sidebar, .Param.Integer = C1 };
			} else {
				Rectangles[C1].x = (Settings.Scalar * 14) + Core.Screensize.X - Rectangles[C1].w;
			}
			Render_Texture(Bars[C1], &Rectangles[C1]);
		}
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
	Process_Supply(&Supplies.Money, Buffer, F_Halftext, Colors.Abyss_Black, (Point){ 10, 30 });
	memset(Buffer, 0, sizeof(Buffer));
	snprintf(Buffer, sizeof(Buffer), "%s, %sday", Time, Metadata.Days[Data.Day]);
	Process_Supply(&Supplies.Time, Buffer, F_Halftext, Colors.Abyss_Black, (Point){ 10, 50 });
	if (Interface.Tool == T_Inspecting) {
		float Content_Vector[7] = { 0, 0, 0, 0, ktn_invalid, 0, 0 };
		Item_Ptr Item;
		int Temperature;
		for (int Column = 0; Column < ktn_grid_size; Column++) {
			Rects.Tile_1x1.x = ktn_fscale((Column * ktn_tile_size) - Core.Camera.X);
			for (int Row = 0; Row < ktn_grid_size; Row++) {
				Rects.Tile_1x1.y = ktn_fscale((Row * ktn_tile_size) - Core.Camera.Y);
				if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
					ktn_memcpy(Content_Vector, Data.Data_Grid[Column][Row], sizeof(Content_Vector));
					Item = Get_ID_Item(Data.Items_Grid[Column][Row]);
					Temperature = Data.Temperature_Grid[Column][Row];
					break;
				}
			}
		}
		if (Item && Item->ID != ktn_invalid) {
			char Buffer[64];
			snprintf(Buffer, sizeof(Buffer), "item: %s", Item->Name);
			strncpy(Data_Fragments[Index], Buffer, sizeof(Data_Fragments[Index]));
			Index++;
			char Subbuffer[64];
			Truncate(Temperature, 0, Subbuffer, sizeof(Subbuffer));
			snprintf(Buffer, sizeof(Buffer), "%s °F", Subbuffer);
			strncpy(Data_Fragments[Index], Buffer, sizeof(Data_Fragments[Index]));
			Index++;
			float Pressure = Calculate_Pressure(Temperature, Item->Boil_Pt, Item->V_Enthalpy);
			if (Pressure == ktn_invalid) {
				strncpy(Data_Fragments[Index], "gas", sizeof(Data_Fragments[Index]));
				Index++;
			} else {
				Pressure = ktn_max(Pressure, 1);
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
				Truncate(Content_Vector[0], Get_Depth(Content_Vector[1]), Subbuffer1, sizeof(Subbuffer1));
				char Subbuffer2[64];
				Abbreviate_Number(Content_Vector[1], Subbuffer2, sizeof(Subbuffer2));
				snprintf(Buffer, sizeof(Buffer), "%s / %s "ktn_unit".", Subbuffer1, Subbuffer2);
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
				snprintf(Buffer, sizeof(Buffer), "%s / %s "ktn_unit".", Subbuffer1, Subbuffer2);
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
		strncpy(Data_Fragments[Index], ktn_null_string, sizeof(Data_Fragments[Index]));
		Index++;
		int Fragment_Size = ktn_veclen(Data_Fragments), Max_Width = 0;
		SDL_Texture* Fragment_Textures[16];
		SDL_FRect Fragment_Rectangles[16];
		for (int C1 = 0; C1 < Fragment_Size; C1++) {
			SDL_Texture* Fragment_Texture = Render_Text(F_Subtext, Data_Fragments[C1], Colors.Abyss_Black);
			Max_Width = max(Max_Width, Fragment_Texture->w);
			Fragment_Textures[C1] = Fragment_Texture;
			Fragment_Rectangles[C1] = (SDL_FRect){
				ktn_fscale(630.0f) - Fragment_Texture->w,
				ktn_fscale((C1 * 20.0f) + 10.0f),
				(float)Fragment_Texture->w,
				(float)Fragment_Texture->h
			};
		}
		int Total_Height = Fragment_Rectangles[Fragment_Size - 1].y + Fragment_Rectangles[Fragment_Size - 1].h;
		Set_Renderer_Color(Colors.Dark_Grey);
		SDL_FRect Background = {
			(Settings.Scalar * 615.0f) - Max_Width,
			0,
			(Settings.Scalar * 25.0f) + Max_Width,
			(Settings.Scalar * 15.0f) + Total_Height
		};
		SDL_RenderFillRect(Core.Renderer, &Background);
		Set_Renderer_Color(Colors.Light_Grey);
		Background = (SDL_FRect){
			(Settings.Scalar * 620.0f) - Max_Width,
			0,
			(Settings.Scalar * 20.0f) + Max_Width,
			(Settings.Scalar * 10.0f) + Total_Height
		};
		SDL_RenderFillRect(Core.Renderer, &Background);
		Clear_Renderer();
		for (int C1 = 0; C1 < Fragment_Size; C1++) {
			Render_Texture(Fragment_Textures[C1], &Fragment_Rectangles[C1]);
			ktn_free_texture(Fragment_Textures[C1]);
		}
	}
	if (Interface.Save_Frames > 0) {
		SDL_Color Fading_Color = Colors.Cherry_Blossom;
		Fading_Color.a = (uint8_t)(ceilf((Interface.Save_Frames / (Interface.Frame_Rate * 2.0f)) * 255.0f));
		char Buffer[16] = "Data saved!";
		Process_Supply(&Supplies.Save_Text, Buffer, F_Subtext, Fading_Color, (Point){ ktn_invalid, 300 });
		Interface.Save_Frames--;
	}
}

void Render_Saveloader() {
	Render_Texture(Textures.Saveloader, &Rects.Saveloader);
	for (int C1 = 0; C1 < ktn_savefiles; C1++) {
		if (Core.Save_Filesizes[C1] > 0) {
			Render_Button(&Textures.Load.Data[C1], &Rects.Load.Data[C1], (UI_Link){ Load_Save, .Param.Integer = C1 },
				Colors.Cherry_Blossom);
			Render_Button(&Textures.Clear.Data[C1], &Rects.Clear.Data[C1], (UI_Link){ Free_Save, .Param.Integer = C1 },
				Colors.Cherry_Blossom);
		} else {
			Render_Button(&Textures.New.Data[C1], &Rects.New.Data[C1], (UI_Link){ New_Save, .Param.Integer = C1 },
				Colors.Cherry_Blossom);
		}
	}
	for (int C1 = 0; C1 < ktn_savefiles; C1++) {
		char Buffer[64];
		char Subbuffer[64];
		Abbreviate_Number(Core.Save_Filesizes[C1], Subbuffer, sizeof(Subbuffer));
		snprintf(Buffer, sizeof(Buffer), "Slot %i (%sb)", C1 + 1, Subbuffer);
		Process_Supply(&Supplies.Filesizes[C1], Buffer, F_Subtext, Colors.Abyss_Black, (Point){ 40, (C1 * 40) + 160 });
	}
}

void Render_Prompts() {
	if (Interface.Prompt_Identifier != ktn_invalid) {
		Interface_Functions[Interface.Prompt_Identifier](Interface.Tile);
	}
}

void Drain_Query() {
	for (int C1 = 0; C1 < Cache.Query_Length; C1++) {
		if (Cache.ID_Query[C1] == 0) {
			Render_Outline(Cache.Query[C1], Cache.Color_Query[C1], 1);
		} else if (Cache.ID_Query[C1] == 1) {
			float Length = sqrtf(powf(Cache.Query[C1].x - Cache.Query[C1].w, 2) + powf(Cache.Query[C1].y - Cache.Query[C1].h, 2));
			float Rotation = atan2f(Cache.Query[C1].y - Cache.Query[C1].h, Cache.Query[C1].x - Cache.Query[C1].w) / (M_PI / 180);
			SDL_FPoint Centerpoint = { ktn_fscale(5.0f), ktn_fscale(5.0f) };
			for (int C2 = 0; C2 < floorf(Length / ktn_fscale(10.0f)); C2++) {
				SDL_FRect Tilebox = { 0.0f, 0.0f, ktn_fscale(10.0f), ktn_fscale(10.0f) };
				Tilebox.x = (float)(Cache.Query[C1].x - (ktn_fscale(C2 * 10.0f) * cosf(Rotation * (M_PI / 180.0f))) - ktn_fscale(
					5.0f));
				Tilebox.y = (float)(Cache.Query[C1].y - (ktn_fscale(C2 * 10.0f) * sinf(Rotation * (M_PI / 180.0f))) - ktn_fscale(
					5.0f));
				SDL_RenderTextureRotated(Core.Renderer, Textures.Path_Arrow, NULL, &Tilebox, Rotation + 90, &Centerpoint,
					SDL_FLIP_NONE);
			}
		}
	}
	Cache.Query_Length = 0;
}