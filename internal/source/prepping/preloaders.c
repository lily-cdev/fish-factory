#include <prepping.h>

void Load_Rects() {
	Rects.Tile_1x1.w = ktn_fscale(ktn_tile_size);
	Rects.Tile_1x1.h = ktn_fscale(ktn_tile_size);
	Rects.Tile_1x2.w = ktn_fscale(ktn_tile_size);
	Rects.Tile_1x2.h = ktn_fscale(ktn_tile_size * 2.0f);
	Rects.Tile_2x1.w = ktn_fscale(ktn_tile_size * 2.0f);
	Rects.Tile_2x1.h = ktn_fscale(ktn_tile_size);
	Rects.Tile_2x2.w = ktn_fscale(ktn_tile_size * 2.0f);
	Rects.Tile_2x2.h = ktn_fscale(ktn_tile_size * 2.0f);
	Rects.Tile_2x3.w = ktn_fscale(ktn_tile_size * 2.0f);
	Rects.Tile_2x3.h = ktn_fscale(ktn_tile_size * 3.0f);
	Rects.Tile_3x2.w = ktn_fscale(ktn_tile_size * 3.0f);
	Rects.Tile_3x2.h = ktn_fscale(ktn_tile_size * 2.0f);
	Rects.Tile_3x3.w = ktn_fscale(ktn_tile_size * 3.0f);
	Rects.Tile_3x3.h = ktn_fscale(ktn_tile_size * 3.0f);
	Rects.Tile_3x4.w = ktn_fscale(ktn_tile_size * 3.0f);
	Rects.Tile_3x4.h = ktn_fscale(ktn_tile_size * 4.0f);
	Rects.Tile_4x3.w = ktn_fscale(ktn_tile_size * 4.0f);
	Rects.Tile_4x3.h = ktn_fscale(ktn_tile_size * 3.0f);
	Rects.Tile_4x6.w = ktn_fscale(ktn_tile_size * 4.0f);
	Rects.Tile_4x6.h = ktn_fscale(ktn_tile_size * 6.0f);
	Rects.Tile_6x4.w = ktn_fscale(ktn_tile_size * 6.0f);
	Rects.Tile_6x4.h = ktn_fscale(ktn_tile_size * 4.0f);
	Rects.Tile_6x8.w = ktn_fscale(ktn_tile_size * 6.0f);
	Rects.Tile_6x8.h = ktn_fscale(ktn_tile_size * 8.0f);
	Rects.Tile_8x6.w = ktn_fscale(ktn_tile_size * 8.0f);
	Rects.Tile_8x6.h = ktn_fscale(ktn_tile_size * 6.0f);
}

void Preload_Fonts() {
	Load_Rects();
	for (int C1 = 0; C1 < ktn_fonts; C1++) {
		char Carrier[128];
		snprintf(Carrier, sizeof(Carrier), "assets/core/fonts/%s.ttf", Fonts.Paths[C1]);
		Fonts.Faces[C1] = TTF_OpenFont(Carrier, ktn_fscale(Fonts.Sizes[C1]));
		if (Fonts.Faces[C1] == NULL) {
			char Subcarrier[128];
			snprintf(Subcarrier, sizeof(Subcarrier), "could not load font \"%s\"; \"%s\"", Carrier, SDL_GetError());
			ktn_jump(I_No_Font, Subcarrier);
		}
	}
}

void Preload_Machines() {
	const int Depth_Carrier[] = {//to rem
		2, 2, 3, 2, 1, 2, 2, 3, 2, 3, 3, 2, 2, 1, 1, 1, 2, 3, 2, 1, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 2,
		3, 3, 1
	};
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		Metadata.Machines[C1].Depth = Depth_Carrier[C1];
		switch (Metadata.Machines[C1].Animation_Type) {
		case A_Static:
			Metadata.Machines[C1].Depth = 1;
			Metadata.Machines[C1].Texture1 = Preload_Texture(Metadata.Machines[C1].Path);
			break;
		case A_Rot:
			Metadata.Machines[C1].Depth = 2;
			Load_Rotational(Metadata.Machines[C1].Path, &Metadata.Machines[C1].Texture2);
			break;
		case A_Modular:
			Metadata.Machines[C1].Depth = 2;
			Load_Modular(Metadata.Machines[C1].Path, &Metadata.Machines[C1].Texture2, Metadata.Machines[C1].Mod_Data.Parts);
			break;
		case A_Spinner:
			Metadata.Machines[C1].Depth = 3;
			Load_Animated_Rotational(Metadata.Machines[C1].Path, &Metadata.Machines[C1].Texture3, Metadata.Machines[C1].Size.Y,
				true);
			break;
		case A_None:
			char* Index = Metadata.Machines[C1].Index;
			if (ktn_stricmp(Index, "ram_pump")) {
				Load_Animated("core/images/machines/r_pump", &Metadata.Machines[C1].Texture2, 1, true);
			} else if (ktn_stricmp(Index, "incinerator")) {
				Load_Animated_Rotational("core/images/machines/incinerator", &Metadata.Machines[C1].Texture3, 1, true);
			} else if (ktn_stricmp(Index, "distillery")) {
				Load_Animated_Rotational("core/images/machines/distillery", &Metadata.Machines[C1].Texture3, 2, false);
			} else if (ktn_stricmp(Index, "electro_cell")) {
				Metadata.Machines[C1].Depth = 3;
				Load_Animated_Rotational("core/images/machines/e_plant", &Metadata.Machines[C1].Texture3, 2, true);
			} else if (ktn_stricmp(Index, "battery")) {
				Metadata.Machines[C1].Depth = 3;
				Load_Animated_Rotational("core/images/machines/battery", &Metadata.Machines[C1].Texture3, 2, true);
			} else if (ktn_stricmp(Index, "algae_bed")) {
				Load_Animated_Rotational("core/images/machines/g_bed", &Metadata.Machines[C1].Texture3, 3, true);
			} else if (ktn_stricmp(Index, "turbine_impulse")) {
				Load_Animated_Rotational("core/images/machines/stit_block", &Metadata.Machines[C1].Texture3, 3, true);
			} else if (ktn_stricmp(Index, "turbine_output")) {
				Load_Animated_Rotational("core/images/machines/st_output", &Metadata.Machines[C1].Texture3, 2, true);
			} else if (ktn_stricmp(Index, "filtration_plant")) {
				Load_Animated("core/images/machines/f_plant", &Metadata.Machines[C1].Texture2, 3, true);
			}
			break;
		default:
			break;
		}
	}
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		Point Pos = { };
		SDL_Texture* Carrier;
		if (ktn_stricmp(Metadata.Machines[C1].Index, "heavy_pipe") || ktn_stricmp(Metadata.Machines[C1].Index, "large_pipe")) {
			Pos.X = 1;
		}
		switch (Metadata.Machines[C1].Depth) {
		case 1:
			Carrier = Metadata.Machines[C1].Texture1;
			break;
		case 2:
			Carrier = Metadata.Machines[C1].Texture2.Data[Pos.X];
			break;
		case 3:
			Carrier = Metadata.Machines[C1].Texture3.Data[Pos.X].Data[Pos.Y];
			break;
		}
		Metadata.Machines[C1].Icon = Carrier;
	}
	Textures.Floor_Texture = Preload_Texture("core/images/tiles/ground");
	Textures.Frame_Texture = Preload_Texture("core/images/tiles/frame");
	Textures.Tile_Texture = Preload_Texture("core/images/tiles/tile");
	Load_Rotational("core/images/ui/other/direction", &Textures.Arrow);
	Textures.R_Flash = Preload_Texture("core/images/effects/light");
	Load_Subanimated("core/images/effects/bubble", &Textures.A_Bubble, 2);
	Rects.R_Flash = (SDL_FRect){ 0.0f, 0.0f, ktn_fscale(40.0f), ktn_fscale(40.0f) };
	Textures.Scrap = Preload_Texture("core/images/tiles/scrap");
	for (int C1 = 0; C1 < Core.Items; C1++) {
		char Carrier[64];
		snprintf(Carrier, sizeof(Carrier), "core/images/items/%s", Metadata.Items[C1].Path);
		Metadata.Items[C1].Icon = Preload_Texture(Carrier);
	}
}

void Preload_Foundation() {
	Textures.Pyramid.Data = malloc(sizeof(SDL_Texture*) * 4);
	Textures.Pyramid.Length = 4;
	float Full_Width = ktn_fscale((ktn_grid_size * ktn_tile_size) + (ktn_buffer_size * 2.0f));
	int Candidate_Length = Full_Width * 0.25f;
	if (ktn_evn(Candidate_Length)) {
		Candidate_Length--;
	}
	const int Resolution = 2001;
	SDL_Surface* Mesh_Surface = SDL_CreateSurface(Resolution, Resolution, SDL_PIXELFORMAT_RGBA8888);
	const SDL_PixelFormatDetails* Pixel_Format = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
	SDL_LockSurface(Mesh_Surface);
	uint32_t Empty = SDL_MapRGBA(Pixel_Format, NULL, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
	uint32_t Light = SDL_MapRGBA(Pixel_Format, NULL, Colors.Mid_Grey.r, Colors.Mid_Grey.g, Colors.Mid_Grey.b,
		SDL_ALPHA_OPAQUE);
	uint32_t* Pixels = (uint32_t*)(Mesh_Surface->pixels);
	for (int C1 = 0; C1 < ktn_sqr(Resolution); C1++) {
		if (ktn_evn(C1) && (int)(C1 & 3) == 0) {
			Pixels[C1] = Light;
		} else {
			Pixels[C1] = Empty;
		}
	}
	SDL_UnlockSurface(Mesh_Surface);
	Textures.Mesh = Surface_To_Texture(Mesh_Surface);
	SDL_SetTextureScaleMode(Textures.Mesh, SDL_SCALEMODE_NEAREST);
	SDL_DestroySurface(Mesh_Surface);
	for (int C1 = 0; C1 < 4; C1++) {
		Textures.Pyramid.Data[C1] = New_Texture(Full_Width * 0.25, Full_Width * 0.25);
		SDL_SetTextureBlendMode(Textures.Pyramid.Data[C1], SDL_BLENDMODE_BLEND);
		SDL_SetTextureScaleMode(Textures.Pyramid.Data[C1], SDL_SCALEMODE_NEAREST);
	}
	SDL_Color Pyramid_Color = Colors.Reinforced_Grey;
	Pyramid_Color.a = SDL_ALPHA_OPAQUE;
	Set_Renderer_Color(Pyramid_Color);
	float Subwidth = ktn_fscale((ktn_grid_size + 2) * 40.0f) * 0.5f;
	for (int X = 0; X < 2; X++) {
		for (int Y = 0; Y < 2; Y++) {
			SDL_SetRenderTarget(Core.Renderer, Textures.Pyramid.Data[(X * 2) + Y]);
			SDL_FRect Subrectangle = {
				ktn_fscale(ktn_buffer_size - 280.0f) - (X * Subwidth),
				ktn_fscale(ktn_buffer_size - 280.0f) - (Y * Subwidth),
				Settings.Scalar * 500.0f,
				Settings.Scalar * 500.0f
			};
			SDL_RenderFillRect(Core.Renderer, &Subrectangle);
			Subrectangle.x -= Settings.Scalar * 5.0f;
			Subrectangle.y -= Settings.Scalar * 5.0f;
			Subrectangle.w += Settings.Scalar * 10.0f;
			Subrectangle.h += Settings.Scalar * 10.0f;
			for (int C1 = 0; C1 < ktn_scale(5); C1++) {
				Subrectangle.x--;
				Subrectangle.y--;
				Subrectangle.w += 2;
				Subrectangle.h += 2;
				SDL_SetRenderDrawBlendMode(Core.Renderer, SDL_BLENDMODE_BLEND);
				SDL_RenderRect(Core.Renderer, &Subrectangle);
			}
		}
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
	Clear_Renderer();
}

void Preload_Text(SDL_Texture** Texture, SDL_FRect* Rect, const char* Text, Font_Index Font, const SDL_Color Color,
	const Point Position) {
	SDL_Texture* Carrier = Render_Text(Font, Text, Color);
	Rect->w = Carrier->w;
	Rect->h = Carrier->h;
	Rect->x = (Position.X == ktn_invalid) ? Core.Screenhalfsize.X - (Carrier->w * 0.5f) : Settings.Scalar * Position.X;
	Rect->y = (Position.Y == ktn_invalid) ? Core.Screenhalfsize.Y - (Carrier->h * 0.5f) : Settings.Scalar * Position.Y;
	(*Texture) = Carrier;
}

void Preload_Assets() {
	SDL_Texture* Carrying_Texture;
	Metadata.Null_Item = (Item_Data){
		.Name = "none",
		.Index = "none",
		.ID = ktn_invalid,
		.Worth = Worthless,
		.Danger = Harmless,
		.Price = 0,
		.Nutrition = 0,
		.Chem_Energy = 0,
		.Boil_Pt = -2,
		.V_Enthalpy = -2,
		.Icon = Preload_Texture("core/images/items/none")
	};
	Core.Game_Texture = New_Texture((int)Core.Screensize.X, (int)Core.Screensize.Y);
	Interface.Tile_Centerpoint.x = Settings.Scalar * (ktn_tile_size * 0.5f);
	Interface.Tile_Centerpoint.y = Settings.Scalar * (ktn_tile_size * 0.5f);
	Preload_Machines();
	Preload_Foundation();
	Carrying_Texture = Preload_Texture("core/images/ui/backgrounds/doors");
	Textures.Door.Data = malloc(sizeof(SDL_Texture*) * 2);
	Textures.Door.Length = 2;
	for (int C1 = 0; C1 < 2; C1++) {
		Textures.Door.Data[C1] = New_Texture((int)Core.Screenhalfsize.X, (int)Core.Screensize.Y);
		SDL_SetTextureBlendMode(Textures.Door.Data[C1], SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core.Renderer, Textures.Door.Data[C1]);
		SDL_FRect Half_Rectangle = { C1 * 1920.0f, 0.0f, 1920.0f, 2160.0f };
		Rects.Door[C1].w = Core.Screenhalfsize.X;
		Rects.Door[C1].h = Core.Screensize.Y;
		SDL_RenderTexture(Core.Renderer, Carrying_Texture, &Half_Rectangle, NULL);
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
	ktn_free_texture(Carrying_Texture);
	Preload_Text(&Textures.Logo1, &Rects.Logo1, "fish", F_Logo, Colors.Abyss_Black, (Point){ 325, 44 });
	Preload_Text(&Textures.Logo2, &Rects.Logo2, "factory", F_Logo, Colors.Abyss_Black, (Point){ 325, 78 });
	Preload_Text(&Textures.CMD_Warning1, &Rects.CMD_Warning1, "time will not progress until the command platform is installed",
		F_Text, Colors.Cherry_Blossom, (Point){ ktn_invalid, ktn_invalid });
	Preload_Text(&Textures.CMD_Warning2, &Rects.CMD_Warning2, "install the command platform for complete tutorial access",
		F_Halftext, Colors.Abyss_Black, (Point){ ktn_invalid, 120.0f });
	Preload_Text(&Textures.Price_Header, &Rects.Price_Header, "machine price:", F_Subtext, Colors.Abyss_Black, (Point){ 456, 10 });
	Rects.Tunnel.Length = 2;
	Rects.Tunnel.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Tunnel.Data[0].w = ktn_fscale(240.0f);
	Rects.Tunnel.Data[0].h = ktn_fscale(90.0f);
	Rects.Tunnel.Data[1].w = ktn_fscale(90.0f);
	Rects.Tunnel.Data[1].h = ktn_fscale(240.0f);
	Load_Rotational("core/images/other/tunnel", &Textures.Tunnel);
	SDL_Surface* Carrying_Surface;
	ktn_load_bmp(Carrying_Surface, "assets/core/images/ui/other/logo.bmp");
	Textures.Emblem = Surface_To_Texture(Carrying_Surface);
	SDL_SetWindowIcon(Core.Window, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	SDL_GetTextureSize(Textures.Emblem, &Rects.Emblem.w, &Rects.Emblem.h);
	Rects.Emblem.w = ktn_fscale(Rects.Emblem.w / 6.0f);
	Rects.Emblem.h = ktn_fscale(Rects.Emblem.h / 6.0f);
	Rects.Emblem.x = (Settings.Scalar * 315.0f) - Rects.Emblem.w;
	Rects.Emblem.y = Settings.Scalar * 32.0f;
	Textures.Crosshair = Preload_Texture("core/images/ui/other/crosshair");
	Textures.Cursor = Preload_Texture("core/images/ui/other/cursor");
	Textures.Cursor_Core = Preload_Texture("core/images/ui/other/cursor_core");
	Textures.Sapling = Preload_Texture("core/images/ui/other/sapling");
	Rects.Sapling = Rects.Tile_1x1;
	Textures.Node = Preload_Texture("core/images/ui/other/node");
	Rects.Node = Rects.Tile_1x1;
	Textures.Path_Arrow = Preload_Texture("core/images/ui/other/path_arrow");
	Textures.Saveloader = Preload_Texture("core/images/ui/backgrounds/saveloader");
	Rects.Saveloader = (SDL_FRect) {
		0,
		0,
		Core.Screensize.X,
		Core.Screensize.Y
	};
	Textures.Help_Sidebutton = Preload_Sidebutton("help", &Rects.Help, 60);
	Textures.Save_Sidebutton = Preload_Sidebutton("save", &Rects.Save, 84);
	Textures.Recipe_Sidebutton = Preload_Sidebutton("recipe", &Rects.Recipe, 108);
	Textures.Exit_Sidebutton = Preload_Sidebutton("exit", &Rects.Exit, 132);
	Rects.Return.Length = 2;
	Rects.Return.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Return.Data[0].x = Settings.Scalar * 10.0f;
	Rects.Return.Data[0].y = Settings.Scalar * 334.0f;
	Rects.New_Game.Length = 2;
	Rects.New_Game.Data = calloc(2, sizeof(SDL_FRect));
	Rects.New_Game.Data[0].x = ktn_invalid;
	Rects.New_Game.Data[0].y = Settings.Scalar * 160.0f;
	Rects.Settings.Length = 2;
	Rects.Settings.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Settings.Data[0].x = ktn_invalid;
	Rects.Settings.Data[0].y = Settings.Scalar * 190.0f;
	Rects.Update_Logs.Length = 2;
	Rects.Update_Logs.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Update_Logs.Data[0].x = ktn_invalid;
	Rects.Update_Logs.Data[0].y = Settings.Scalar * 220.0f;
	Rects.Credits.Length = 2;
	Rects.Credits.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Credits.Data[0].x = ktn_invalid;
	Rects.Credits.Data[0].y = Settings.Scalar * 250.0f;
	Rects.Quit_Game.Length = 2;
	Rects.Quit_Game.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Quit_Game.Data[0].x = ktn_invalid;
	Rects.Quit_Game.Data[0].y = Settings.Scalar * 280.0f;
	Rects.Apply.Length = 2;
	Rects.Apply.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Apply.Data[0].x = Settings.Scalar * 60.0f;
	Rects.Apply.Data[0].y = Settings.Scalar * 334.0f;
	Rects.Cancel.Length = 2;
	Rects.Cancel.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Cancel.Data[0].x = Settings.Scalar * 110.0f;
	Rects.Cancel.Data[0].y = Settings.Scalar * 334.0f;
	Rects.Next_Day.Length = 2;
	Rects.Next_Day.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Next_Day.Data[0].x = ktn_invalid;
	Rects.Next_Day.Data[0].y = Settings.Scalar * 300.0f;
	Interface.Map_X = (ktn_tile_size * ktn_grid_size) - 640 + ktn_buffer_size;
	Interface.Map_Y = (ktn_tile_size * ktn_grid_size) - 360 + ktn_buffer_size;
	Rects.Subcategories.Length = ktn_categories;
	Rects.Subcategories.Data = malloc(sizeof(Rect2_Array) * ktn_categories);
	Textures.Subcategories.Length = ktn_categories;
	Textures.Subcategories.Data = malloc(sizeof(Texture2_Array) * ktn_categories);
	for (int C1 = 0; C1 < ktn_categories; C1++) {
		int Length = ktn_intlen(Metadata.Subcategory_Positions[C1]);
		Rects.Subcategories.Data[C1].Length = Length;
		Rects.Subcategories.Data[C1].Data = malloc(sizeof(Rect_Array) * Length);
		Textures.Subcategories.Data[C1].Length =  Length;
		Textures.Subcategories.Data[C1].Data = malloc(sizeof(Texture_Array) * Length);
		for (int C2 = 0; C2 < Length; C2++) {
			Rects.Subcategories.Data[C1].Data[C2].Length = 2;
			Rects.Subcategories.Data[C1].Data[C2].Data = calloc(2, sizeof(SDL_FRect));
			Rects.Subcategories.Data[C1].Data[C2].Data[0].x = ktn_invalid;
			Rects.Subcategories.Data[C1].Data[C2].Data[0].y = ktn_fscale((C2 * 30.0f) + 40.0f);
			Load_Button(F_Halftext, Metadata.Subcategories[Metadata.Subcategory_Positions[C1][C2]],
				&Textures.Subcategories.Data[C1].Data[C2], Rects.Subcategories.Data[C1].Data[C2], Colors.Abyss_Black,
				Colors.Cherry_Blossom);
		}
	}
	Rects.Subcontents.Data = malloc(sizeof(Rect2_Array) * ktn_subcategories);
	Rects.Subcontents.Length = ktn_subcategories;
	Textures.Subcontents.Data = malloc(sizeof(Texture2_Array) * ktn_subcategories);
	Textures.Subcontents.Length = ktn_subcategories;
	for (int C1 = 0; C1 < ktn_subcategories; C1++) {
		int Length = ktn_veclen(Metadata.Subcontents[C1]);
		Rects.Subcontents.Data[C1].Data = malloc(sizeof(Rect_Array) * Length);
		Rects.Subcontents.Data[C1].Length = Length;
		Textures.Subcontents.Data[C1].Data = malloc(sizeof(Texture_Array) * Length);
		Textures.Subcontents.Data[C1].Length = Length;
		for (int C2 = 0; C2 < Length; C2++) {
			Rects.Subcontents.Data[C1].Data[C2].Length = 2;
			Rects.Subcontents.Data[C1].Data[C2].Data = calloc(2, sizeof(SDL_FRect));
			Rects.Subcontents.Data[C1].Data[C2].Data[0].x = ktn_invalid;
			Rects.Subcontents.Data[C1].Data[C2].Data[0].y = ktn_fscale((C2 * 30.0f) + 40.0f);
			Load_Button(F_Halftext, Get_Machine(Metadata.Subcontents[C1][C2])->Name, &Textures.Subcontents.Data[C1].Data[C2],
				Rects.Subcontents.Data[C1].Data[C2], Colors.Abyss_Black, Colors.Cherry_Blossom);
		}
	}
	Rects.Item_Labels.Length = ktn_categories;
	Rects.Item_Labels.Data = malloc(sizeof(Rect2_Array) * ktn_categories);
	Textures.Item_Labels.Data = malloc(sizeof(Texture2_Array) *	ktn_categories);
	Textures.Item_Labels.Length = ktn_categories;
	for (int C1 = 0; C1 < ktn_categories; C1++) {
		int Length = ktn_veclen(Metadata.Item_Labels[C1]);
		Rects.Item_Labels.Data[C1].Data = malloc(sizeof(Rect_Array) * Length);
		Rects.Item_Labels.Data[C1].Length = Length;
		Textures.Item_Labels.Data[C1].Data = malloc(sizeof(Texture_Array) * Length);
		Textures.Item_Labels.Data[C1].Length = Length;
		for (int C2 = 0; C2 < Length; C2++) {
			Rects.Item_Labels.Data[C1].Data[C2].Length = 2;
			Rects.Item_Labels.Data[C1].Data[C2].Data = calloc(2, sizeof(SDL_FRect));
			Rects.Item_Labels.Data[C1].Data[C2].Data[0].x = ktn_invalid;
			Rects.Item_Labels.Data[C1].Data[C2].Data[0].y = ktn_fscale(((C2 + ktn_intlen(Metadata.Subcategory_Positions[C1])) * 30.0f) +
				40.0f);
			Load_Button(F_Halftext, Get_Machine(Metadata.Item_Labels[C1][C2])->Name, &Textures.Item_Labels.Data[C1].Data[C2],
				Rects.Item_Labels.Data[C1].Data[C2], Colors.Abyss_Black, Colors.Cherry_Blossom);
		}
	}
	Interface.Max_Time_Frames = Interface.Frame_Rate;
	Cache.FPS_Cache = malloc(sizeof(float) * Interface.Frame_Rate);
	Cache.FPS_Tick = 0;
	Temporary.Temporary_FPS = Interface.Frame_Rate;
	for (int C1 = 0; C1 < 101; C1++) {
		char Buffer[32];
		snprintf(Buffer, sizeof(Buffer), "%i%%", C1);
		strncpy(Interface.Slider_Texts[5][C1], Buffer, sizeof(Interface.Slider_Texts[5][C1]));
	}
	strncpy(Interface.Slider_Texts[5][101], ktn_null_string, sizeof(Interface.Slider_Texts[5][101]));
	const int Queried[4] = {
		7,
		11,
		13,
		ktn_terminator
	};
	for (int C1 = 0; C1 < ktn_intlen(Queried); C1++) {
		for (int C2 = 0; C2 < ktn_valve300_len; C2++) {
			snprintf(Interface.Slider_Texts[Queried[C1]][C2], sizeof(Interface.Slider_Texts[Queried[C1]][C2]), "%iL/s",
				Interface.Valve300_Postions[C2]);
		}
		strncpy(Interface.Slider_Texts[Queried[C1]][ktn_valve300_len], ktn_null_string, sizeof(Interface.Slider_Texts[Queried[C1]][
			ktn_valve300_len]));
	}
	for (int C1 = 0; C1 < 241; C1++) {
		char Buffer[32];
		snprintf(Buffer, sizeof(Buffer), "%i %sF", C1 * 5, ktn_degree);
		strncpy(Interface.Slider_Texts[10][C1], Buffer, sizeof(Interface.Slider_Texts[10][C1]));
	}
	strncpy(Interface.Slider_Texts[10][241], ktn_null_string, sizeof(Interface.Slider_Texts[10][241]));
	for (int C1 = 0; C1 < 6; C1++) {
		char Subcarrier[64];
		Abbreviate_Number((C1 == 0) ? 0 : powf(10.0f, C1 - 1.0f), Subcarrier, sizeof(Subcarrier));
		snprintf(Interface.Slider_Texts[14][C1], sizeof(Interface.Slider_Texts[14][C1]), "%sJ/s", Subcarrier);
	}
	strncpy(Interface.Slider_Texts[14][6], ktn_null_string, sizeof(Interface.Slider_Texts[14][6]));
	Textures.Tool.Data = malloc(sizeof(SDL_Texture*) * ktn_tools);
	Textures.Tool.Length = ktn_tools;
	for (int C1 = 0; C1 < ktn_tools; C1++) {
		SDL_Texture* Text_Texture = Render_Text(F_Halftext, Metadata.Tool_Texts[C1], Colors.Abyss_Black);
		Rects.Tool[C1].w = (float)Text_Texture->w;
		Rects.Tool[C1].h = (float)Text_Texture->h;
		Textures.Tool.Data[C1] = Text_Texture;
	}
	Carrying_Texture = Render_Text(F_Large, "fish factory help", Colors.Abyss_Black);
	Rects.Help_Content[0] = (SDL_FRect) {
		Core.Screenhalfsize.X - (float)(Carrying_Texture->w * 0.5f),
		Settings.Scalar * 20.0f,
		(float)Carrying_Texture->w,
		(float)Carrying_Texture->h
	};
	Textures.Help_Content.Data = malloc(sizeof(SDL_Texture*) * 2);
	Textures.Help_Content.Length = 2;
	Textures.Help_Content.Data[0] = Carrying_Texture;
	Carrying_Texture = Render_Text(F_Large, "catalog", Colors.Abyss_Black);
	Rects.Recipe_Content = (SDL_FRect){
		Core.Screenhalfsize.X - (float)(Carrying_Texture->w * 0.5f),
		Settings.Scalar * 20.0f,
		(float)Carrying_Texture->w,
		(float)Carrying_Texture->h
	};
	Textures.Recipe_Content = Carrying_Texture;
	char Keycore[64];
	char Subkeycore[64];
	strncpy(Subkeycore, SDL_GetKeyName(Keybinds.Keybind_List[13]), sizeof(Subkeycore));
	snprintf(Keycore, sizeof(Keycore), "Press \"%s\" to close.", Subkeycore);
	Carrying_Texture = Render_Text(F_Text, Keycore, Colors.Abyss_Black);
	Rects.Help_Content[1] = (SDL_FRect){
		Core.Screenhalfsize.X - (Carrying_Texture->w * 0.5f),
		Core.Screenhalfsize.X,
		(float)Carrying_Texture->w,
		(float)Carrying_Texture->h
	};
	Textures.Help_Content.Data[1] = Carrying_Texture;
	Textures.Quirk.Data = malloc(sizeof(SDL_Texture*) * 4);
	Textures.Quirk_Label.Data = malloc(sizeof(SDL_Texture*) * 4);
	Textures.Quirk.Length = 4;
	Textures.Quirk_Label.Length = 4;
	SDL_DestroySurface(Carrying_Surface);
	Textures.Quirk.Data[0] = Preload_Texture("core/images/ui/quirks/no_rotation");
	Textures.Quirk.Data[1] = Preload_Texture("core/images/ui/quirks/modular");
	Textures.Quirk.Data[2] = Preload_Texture("core/images/ui/quirks/interactable");
	Textures.Quirk.Data[3] = Preload_Texture("core/images/ui/quirks/omnidirectional");
	char* Quirk_Texts[4] = { "Non-Rotatable", "Modular", "Interactable", "Omnidirectional" };
	for (int C1 = 0; C1 < 4; C1++) {
		Textures.Quirk_Label.Data[C1] = Render_Text(F_Subtext, Quirk_Texts[C1], Colors.Abyss_Black);
	}
	ktn_load_bmp(Carrying_Surface, "assets/core/images/ui/backgrounds/scrollframe.bmp");
	Textures.Log_Background = Surface_To_Texture(Carrying_Surface);
	Rects.Log_Background = (SDL_FRect){
		0.0f,
		0.0f,
		ktn_fscale(Carrying_Surface->w / 6.0f),
		ktn_fscale(Carrying_Surface->h / 6.0f)
	};
	SDL_DestroySurface(Carrying_Surface);
	memset(Interface.Log_Heights, 0, sizeof(Interface.Log_Heights));
	Cache.Log_Rectangles.Data = calloc(ktn_logs, sizeof(Rect_Array));
	Cache.Log_Rectangles.Length = ktn_logs;
	Cache.Log_Cache.Data = malloc(sizeof(Texture_Array) * ktn_logs);
	Cache.Log_Cache.Length = ktn_logs;
	for (int C1 = 0; C1 < ktn_logs; C1++) {
		int Height = Render_Rich_Text(F_Halftext, Metadata.Logs[C1], (Point) { 0, 0 }, Temporary.Log_Inversions[C1], true) -
			ktn_fscale(210.0f);
		Interface.Log_Heights[C1] = Height;
		int Cap = (int)ceilf(Height / ktn_fscale(341.0f));
		Cache.Log_Rectangles.Data[C1].Data = calloc(Cap, sizeof(SDL_FRect));
		Cache.Log_Rectangles.Data[C1].Length = Cap;
		Cache.Log_Cache.Data[C1].Data = malloc(sizeof(SDL_Texture*) * Cap);
		Cache.Log_Cache.Data[C1].Length = Cap;
		for (int C2 = 0; C2 < Cap; C2++) {
			Cache.Log_Cache.Data[C1].Data[C2] = New_Texture(Core.Screensize.X, ktn_fscale(1000.0f));
			SDL_FRect New_Rectangle = {
				0,
				ktn_fscale(C2 * 1000.0f),
				Core.Screensize.X,
				ktn_fscale(1000.0f)
			};
			SDL_SetTextureBlendMode(Cache.Log_Cache.Data[C1].Data[C2], SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(Core.Renderer, Cache.Log_Cache.Data[C1].Data[C2]);
			Render_Rich_Text(F_Subtext, Metadata.Logs[C1], (Point){ 52, 52 - (New_Rectangle.y / Settings.Scalar) },
				Temporary.Log_Inversions[C1], false);
			SDL_SetRenderTarget(Core.Renderer, NULL);
			Cache.Log_Rectangles.Data[C1].Data[C2] = New_Rectangle;
		}
	}
	Cache.Wire_Cache.Data = malloc(sizeof(SDL_Texture*) * 4);
	Cache.Wire_Cache.Length = 4;
	for (int C1 = 0; C1 < 4; C1++) {
		Cache.Wire_Cache.Data[C1] = New_Texture(Settings.Scalar * ktn_grid_size * (ktn_tile_size * 0.5),
			Settings.Scalar * ktn_grid_size * (ktn_tile_size * 0.5));
		SDL_SetTextureBlendMode(Cache.Wire_Cache.Data[C1], SDL_BLENDMODE_BLEND);
	}
	Cache.Wire_Box.x = 0;
	Cache.Wire_Box.y = 0;
	Cache.Wire_Box.w = Settings.Scalar * ktn_grid_size * (ktn_tile_size * 0.5);
	Cache.Wire_Box.h = Settings.Scalar * ktn_grid_size * (ktn_tile_size * 0.5);
	Rects.Clear_Tutorial.Length = 2;
	Rects.Clear_Tutorial.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Clear_Tutorial.Data[0].x = ktn_invalid;
	Rects.Clear_Tutorial.Data[0].y = 160;
	Load_Button(F_Halftext, Metadata.Buttons[11], &Textures.Clear_Tutorial, Rects.Clear_Tutorial, Colors.Abyss_Black,
		Colors.Cherry_Blossom);
	Rects.Tutorials.Length = 3;
	Textures.Tutorials.Data = malloc(sizeof(Texture_Array) * 3);
	Textures.Tutorials.Length = 3;
	Rects.Tutorials.Data = malloc(sizeof(Rect_Array) * 3);
	for (int C1 = 0; C1 < 3; C1++) {
		Rects.Tutorials.Data[C1].Length = 2;
		Rects.Tutorials.Data[C1].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Tutorials.Data[C1].Data[0].x = ktn_invalid;
		Rects.Tutorials.Data[C1].Data[0].y = ktn_fscale((C1 * 40.0f) + 160.0f);
		Load_Button(F_Halftext, Metadata.Buttons[C1 + 12], &Textures.Tutorials.Data[C1], Rects.Tutorials.Data[C1],
			Colors.Abyss_Black, Colors.Cherry_Blossom);
	}
	Rects.Cheats.Length = 3;
	Rects.Cheats.Data = malloc(sizeof(Rect_Array) * 3);
	Textures.Cheats.Length = 3;
	Textures.Cheats.Data = malloc(sizeof(Texture_Array) * 3);
	for (int C1 = 0; C1 < 3; C1++) {
		Rects.Cheats.Data[C1].Length = 2;
		Rects.Cheats.Data[C1].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Cheats.Data[C1].Data[0].x = ktn_invalid;
		Rects.Cheats.Data[C1].Data[0].y = ktn_fscale((C1 * 40.0f) + 160.0f);
		Load_Button(F_Halftext, Metadata.Buttons[(C1 == 2) ? 49 : C1 + 9], &Textures.Cheats.Data[C1], Rects.Cheats.Data[C1],
			Colors.Abyss_Black, Colors.Cherry_Blossom);
	}
	Rects.Confirmation.Length = 2;
	Rects.Confirmation.Data = malloc(sizeof(Rect_Array) * 2);
	Textures.Confirmation.Length = 2;
	Textures.Confirmation.Data = malloc(sizeof(Texture_Array) * 2);
	for (int C1 = 0; C1 < 2; C1++) {
		Rects.Confirmation.Data[C1].Length = 2;
		Rects.Confirmation.Data[C1].Data = calloc(2, sizeof(SDL_FRect));
		Load_Button(F_Halftext, Metadata.Buttons[C1 + 6], &Textures.Confirmation.Data[C1], Rects.Confirmation.Data[C1],
			Colors.Abyss_Black, Colors.Cherry_Blossom);
		for (int C2 = 0; C2 < 2; C2++) {
			Rects.Confirmation.Data[C1].Data[C2].x = ktn_fscale((C1 * 320.0f) + 160.0f) - (Rects.Confirmation.Data[C1].Data[C2].w *
				0.5);
			Rects.Confirmation.Data[C1].Data[C2].y = ktn_fscale(260.0f);
		}
	}
	String2 Carrier;
	Carrier.Length = 4;
	Carrier.Data = malloc(sizeof(char*) * Carrier.Length);
	for (int C1 = 0; C1 < Carrier.Length; C1++) {
		Carrier.Data[C1] = malloc(strlen(Metadata.Buttons[C1 + 27]) + 1);
		strcpy(Carrier.Data[C1], Metadata.Buttons[C1 + 27]);
	}
	Preload_Terminal_Sidebar(&Carrier, &Textures.MSP_Buttons, &Rects.MSP_Buttons);
	Free_String2(&Carrier);
	Carrier.Length = 4;
	Carrier.Data = malloc(sizeof(char*) * Carrier.Length);
	for (int C1 = 0; C1 < Carrier.Length; C1++) {
		Carrier.Data[C1] = malloc(strlen(Metadata.Buttons[C1 + 31]) + 1);
		strcpy(Carrier.Data[C1], Metadata.Buttons[C1 + 31]);
	}
	Preload_Terminal_Sidebar(&Carrier, &Textures.SD_Buttons, &Rects.SD_Buttons);
	Free_String2(&Carrier);
	Carrier.Length = 1;
	Carrier.Data = malloc(sizeof(char*) * Carrier.Length);
	Carrier.Data[0] = malloc(strlen(Metadata.Buttons[35]) + 1);
	strcpy(Carrier.Data[0], Metadata.Buttons[35]);
	Preload_Terminal_Sidebar(&Carrier, &Textures.HX_Buttons, &Rects.HX_Buttons);
	Preload_Terminal_Sidebar(&Carrier, &Textures.MT_Buttons, &Rects.MT_Buttons);
	Free_String2(&Carrier);
	Load_Button(F_Subtext, Metadata.Buttons[0], &Textures.Return, Rects.Return, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(F_Text, Metadata.Buttons[1], &Textures.New_Game, Rects.New_Game, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(F_Text, Metadata.Buttons[2], &Textures.Settings, Rects.Settings, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(F_Text, Metadata.Buttons[3], &Textures.Update_Logs, Rects.Update_Logs, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(F_Text, Metadata.Buttons[4], &Textures.Credits, Rects.Credits, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(F_Text, Metadata.Buttons[5], &Textures.Quit_Game, Rects.Quit_Game, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(F_Subtext, Metadata.Buttons[6], &Textures.Apply, Rects.Apply, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(F_Subtext, Metadata.Buttons[7], &Textures.Cancel, Rects.Cancel, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(F_Subtext, Metadata.Buttons[8], &Textures.Next_Day, Rects.Next_Day, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.New.Data = malloc(sizeof(Texture_Array) * 4);
	Textures.Load.Data = malloc(sizeof(Texture_Array) * 4);
	Textures.Clear.Data = malloc(sizeof(Texture_Array) * 4);
	Textures.New.Length = 4;
	Textures.Load.Length = 4;
	Textures.Clear.Length = 4;
	Rects.New.Data = malloc(sizeof(Rect_Array) * 4);
	Rects.Load.Data = malloc(sizeof(Rect_Array) * 4);
	Rects.Clear.Data = malloc(sizeof(Rect_Array) * 4);
	Rects.New.Length = 4;
	Rects.Load.Length = 4;
	Rects.Clear.Length = 4;
	for (int C1 = 0; C1 < 4; C1++) {
		Rects.New.Data[C1].Length = 2;
		Rects.New.Data[C1].Data = calloc(2, sizeof(SDL_FRect));
		Rects.New.Data[C1].Data[0].x = ktn_fscale(340.0f);
		Rects.New.Data[C1].Data[0].y = ktn_fscale((C1 * 40.0f) + 160.0f);
		Load_Button(F_Subtext, Metadata.Buttons[24], &Textures.New.Data[C1], Rects.New.Data[C1], Colors.Abyss_Black,
			Colors.Cherry_Blossom);
		Rects.Load.Data[C1].Length = 2;
		Rects.Load.Data[C1].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Load.Data[C1].Data[0].x = ktn_fscale(340.0f);
		Rects.Load.Data[C1].Data[0].y = ktn_fscale((C1 * 40.0f) + 160.0f);
		Load_Button(F_Subtext, Metadata.Buttons[25], &Textures.Load.Data[C1], Rects.Load.Data[C1], Colors.Abyss_Black,
			Colors.Cherry_Blossom);
		Rects.Clear.Data[C1].Length = 2;
		Rects.Clear.Data[C1].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Clear.Data[C1].Data[0].x = ktn_fscale(490.0f);
		Rects.Clear.Data[C1].Data[0].y = ktn_fscale((C1 * 40.0f) + 160.0f);
		Load_Button(F_Subtext, Metadata.Buttons[26], &Textures.Clear.Data[C1], Rects.Clear.Data[C1], Colors.Abyss_Black,
			Colors.Cherry_Blossom);
	}
	Textures.Categories.Data = malloc(sizeof(Texture_Array) * ktn_categories);
	Textures.Categories.Length = ktn_categories;
	Rects.Categories.Data = malloc(sizeof(Rect_Array) * ktn_categories);
	Rects.Categories.Length = ktn_categories;
	for (int C1 = 0; C1 < ktn_categories; C1++) {
		Rects.Categories.Data[C1].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Categories.Data[C1].Length = 2;
		Rects.Categories.Data[C1].Data[0].x = ktn_invalid;
		Rects.Categories.Data[C1].Data[0].y = ktn_fscale((C1 * 30.0f) + 40.0f);
		Load_Button(F_Text, Metadata.Categories[C1], &Textures.Categories.Data[C1], Rects.Categories.Data[C1],
			Colors.Abyss_Black, Colors.Cherry_Blossom);
	}
	char* Captions[ktn_captions] = {
		Metadata.Buttons[43], Metadata.Buttons[44], Metadata.Buttons[45], Metadata.Buttons[46], Metadata.Buttons[47],
		Metadata.Buttons[48]
	};
	Rects.Settings_Label.Length = ktn_captions;
	Rects.Settings_Label.Data = calloc(ktn_captions, sizeof(SDL_FRect));
	Textures.Settings_Label.Length = ktn_captions;
	Textures.Settings_Label.Data = malloc(sizeof(SDL_Texture*) * ktn_captions);
	for (int C1 = 0; C1 < ktn_captions; C1++) {
		SDL_Texture* Carrier = Render_Text(F_Halftext, Captions[C1], Colors.Abyss_Black);
		Textures.Settings_Label.Data[C1] = Carrier;
		Rects.Settings_Label.Data[C1].x = Settings.Scalar * 10.0f;
		Rects.Settings_Label.Data[C1].w = (float)Carrier->w;
		Rects.Settings_Label.Data[C1].h = (float)Carrier->h;
	}
	Rects.Settings_Label.Data[0].y = 10.0f;
	Rects.Settings_Label.Data[1].y = 100.0f;
	Rects.Settings_Label.Data[2].y = 170.0f;
	Rects.Settings_Label.Data[3].y = 240.0f;
	Rects.Settings_Label.Data[4].y = 270.0f;
	Rects.Settings_Label.Data[4].x = Settings.Scalar * 330.0f;
	Rects.Settings_Label.Data[5].y = 10.0f;
	Rects.Settings_Label.Data[5].x = Settings.Scalar * 330.0f;
	for (int C1 = 0; C1 < ktn_captions; C1++) {
		Rects.Settings_Label.Data[C1].y *= Settings.Scalar;
	}
	Rects.Save_Settings.Length = 2;
	Rects.Save_Settings.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Save_Settings.Data[0].y = Settings.Scalar * 334.0f;
	Load_Button(F_Subtext, Metadata.Buttons[15], &Textures.Save_Settings, Rects.Save_Settings, Colors.Abyss_Black,
		Colors.Cherry_Blossom);
	Rects.Save_Settings.Data[0].x = (Settings.Scalar * 630) - Rects.Save_Settings.Data[0].w;
	Rects.Save_Settings.Data[1].x = Rects.Save_Settings.Data[0].x + (Rects.Save_Settings.Data[0].w * 0.5f) -
		(Rects.Save_Settings.Data[1].w * 0.5f);
	Rects.Error_Exit.Length = 2;
	Rects.Error_Exit.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Error_Exit.Data[0].x = ktn_invalid;
	Rects.Error_Exit.Data[0].y = Settings.Scalar * 50.0f;
	Load_Button(F_Terminal, Metadata.Buttons[36], &Textures.Error_Exit, Rects.Error_Exit, Colors.Cherry_Blossom,
		Colors.Pure_White);
	for (int C1 = 0; C1 < 2; C1++) {
		Rects.Error_Exit.Data[C1].x += Settings.Scalar * 210.0f;
	}
	Rects.Anti_Aliasing.Length = 2;
	Rects.Anti_Aliasing.Data = malloc(sizeof(Rect_Array) * 2);
	Textures.Anti_Aliasing.Length = 2;
	for (int C1 = 0; C1 < 2; C1++) {
		Rects.Anti_Aliasing.Data[C1].Length = 2;
		Rects.Anti_Aliasing.Data[C1].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Anti_Aliasing.Data[C1].Data[0].x = Settings.Scalar * 370.0f;
		Rects.Anti_Aliasing.Data[C1].Data[0].y = Settings.Scalar * 300.0f;
	}
	Textures.Anti_Aliasing.Data = malloc(sizeof(Texture_Array) * 2);
	Load_Button(F_Subtext, Metadata.Buttons[22], &Textures.Anti_Aliasing.Data[0], Rects.Anti_Aliasing.Data[0], Colors.Abyss_Black,
		Colors.Cherry_Blossom);
	Load_Button(F_Subtext, Metadata.Buttons[23], &Textures.Anti_Aliasing.Data[1], Rects.Anti_Aliasing.Data[1], Colors.Abyss_Black,
		Colors.Cherry_Blossom);
	Rects.V_Sync.Length = 2;
	Rects.V_Sync.Data = malloc(sizeof(Rect_Array) * 2);
	for (int C1 = 0; C1 < 2; C1++) {
		Rects.V_Sync.Data[C1].Length = 2;
		Rects.V_Sync.Data[C1].Data = calloc(2, sizeof(SDL_FRect));
		Rects.V_Sync.Data[C1].Data[0].x = Settings.Scalar * 370.0f;
		Rects.V_Sync.Data[C1].Data[0].y = Settings.Scalar * 320.0f;
	}
	Textures.V_Sync.Data = malloc(sizeof(Texture_Array) * 2);
	Textures.V_Sync.Length = 2;
	Load_Button(F_Subtext, Metadata.Buttons[20], &Textures.V_Sync.Data[0], Rects.V_Sync.Data[0], Colors.Abyss_Black,
		Colors.Cherry_Blossom);
	Load_Button(F_Subtext, Metadata.Buttons[21], &Textures.V_Sync.Data[1], Rects.V_Sync.Data[1], Colors.Abyss_Black,
		Colors.Cherry_Blossom);
	Textures.Sort.Data =  malloc(sizeof(Texture_Array) * 2);
	Textures.Sort.Length = 2;
	Rects.Sort.Length = 2;
	Rects.Sort.Data = malloc(sizeof(Rect_Array) * 2);
	for (int C1 = 0; C1 < 2; C1++) {
		Rects.Sort.Data[C1].Length = 2;
		Rects.Sort.Data[C1].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Sort.Data[C1].Data[0].x = ktn_invalid;
		Rects.Sort.Data[C1].Data[0].y = Settings.Scalar * 334.0f;
	}
	Load_Button(F_Subtext, Metadata.Buttons[18], &Textures.Sort.Data[0], Rects.Sort.Data[0], Colors.Abyss_Black,
		Colors.Cherry_Blossom);
	Load_Button(F_Subtext, Metadata.Buttons[19], &Textures.Sort.Data[1], Rects.Sort.Data[1], Colors.Abyss_Black,
		Colors.Cherry_Blossom);
	Textures.TBW_Texture.Data = malloc(sizeof(Texture_Array) * 2);
	Textures.TBW_Texture.Length = 2;
	Rects.TBW_Rectangle.Data = malloc(sizeof(Rect_Array) * 2);
	Rects.TBW_Rectangle.Length = 2;
	for (int C1 = 0; C1 < 2; C1++) {
		Rects.TBW_Rectangle.Data[C1].Length = 2;
		Rects.TBW_Rectangle.Data[C1].Data = calloc(2, sizeof(SDL_FRect));
		Rects.TBW_Rectangle.Data[C1].Data[0].y = Settings.Scalar * 334.0f;
	}
	Load_Button(F_Subtext, Metadata.Buttons[16], &Textures.TBW_Texture.Data[0], Rects.TBW_Rectangle.Data[0], Colors.Abyss_Black,
		Colors.Cherry_Blossom);
	Load_Button(F_Subtext, Metadata.Buttons[17], &Textures.TBW_Texture.Data[1], Rects.TBW_Rectangle.Data[1], Colors.Abyss_Black,
		Colors.Cherry_Blossom);
	for (int C1 = 0; C1 < 2; C1++) {
		Rects.TBW_Rectangle.Data[C1].Data[0].x = (Settings.Scalar * 630.0f) - Rects.TBW_Rectangle.Data[C1].Data[0].w;
		Rects.TBW_Rectangle.Data[C1].Data[1].x = Rects.TBW_Rectangle.Data[C1].Data[0].x + (Rects.TBW_Rectangle.Data[C1].Data[
			0].w * 0.5f) - (Rects.TBW_Rectangle.Data[C1].Data[1].w * 0.5f);
	}
	ktn_load_bmp(Carrying_Surface, "assets/core/images/other/submarine.bmp");
	Textures.Submarine.Data = malloc(sizeof(SDL_Texture*) * 2);
	Textures.Submarine.Length = 2;
	for (int C1 = 0; C1 < 2; C1++) {
		SDL_Surface* Dividing_Surface = SDL_CreateSurface(Carrying_Surface->w * 0.5f, Carrying_Surface->h,
			Carrying_Surface->format);
		SDL_Rect Dividing_Rectangle = { (Carrying_Surface->w * 0.5f) * C1, 0, Carrying_Surface->w * 0.5f, Carrying_Surface->h };
		SDL_BlitSurface(Carrying_Surface, &Dividing_Rectangle, Dividing_Surface, NULL);
		Textures.Submarine.Data[C1] = Surface_To_Texture(Dividing_Surface);
		SDL_DestroySurface(Dividing_Surface);
	}
	SDL_DestroySurface(Carrying_Surface);
	SDL_GetTextureSize(Textures.Submarine.Data[0], &Rects.Submarine.w, &Rects.Submarine.h);
	Rects.Submarine.w = ktn_fscale(Rects.Submarine.w / 3.0f);
	Rects.Submarine.h = ktn_fscale(Rects.Submarine.h / 6.0f);
}