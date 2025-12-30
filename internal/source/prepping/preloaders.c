#include <prepping.h>

void Preload_Fonts() {
	Fonts.Logo_Font = TTF_OpenFont("Assets/Core/Fonts/Oxygen/Oxygen_Regular.ttf",
		Settings.Screen_Size * 32);
	Fonts.Large_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings.Screen_Size * 24);
	Fonts.Text_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings.Screen_Size * 18);
	Fonts.Halftext_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings.Screen_Size * 16);
	Fonts.Subtext_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings.Screen_Size * 12);
	Fonts.Microtext_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings.Screen_Size * 10);
	Fonts.Terminal_Font = TTF_OpenFont("Assets/Core/Fonts/Oxygen/Oxygen_Regular.ttf",
		Settings.Screen_Size * 12);
}

typedef struct {
	SDL_Texture* Textures[LDE_MACHINES];
	SDL_FRect Rects[LDE_MACHINES];
} Ctr;

void Preload_Machines() {
	int No_Rotationals[1] = { LDE_INVALID };
	Textures.Floor_Texture = Preload_Texture("Tiles/Ground");
	Textures.Frame_Texture = Preload_Texture("Tiles/Frame");
	Textures.Tile_Texture = Preload_Texture("Tiles/Tile");
	Load_Modular("Machines/R_Pipe", &Textures.R_Pipe, 6);
	Load_Modular("Machines/L_Pipe", &Textures.L_Pipe, 6);
	Load_Modular("Machines/MSP", &Textures.MS_Pool, 6);
	Load_Rotational("UI/Other/Direction", &Textures.Arrow);
	Load_Rotational("Machines/S_Dock", &Textures.S_Dock);
	Textures.R_Flash = Preload_Texture("Effects/Light");
	Rects.R_Flash.x = 0;
	Rects.R_Flash.y = 0;
	Rects.R_Flash.w = Settings.Screen_Size * 40.0f;
	Rects.R_Flash.h = Settings.Screen_Size * 40.0f;
	Textures.Bubble = Preload_Texture("Effects/Bubble");
	int RP_Rotationals[4] = { 2, 3, 4, LDE_INVALID };
	Load_Animated("Machines/R_Pump", &Textures.R_Pump, 1, false, RP_Rotationals);
	Load_Animated_Rotational("Machines/Incinerator", &Textures.Incinerator, 1, true, No_Rotationals);
	Textures.P_Generator = Preload_Texture("Machines/P_Generator");
	Load_Animated("Machines/F_Plant", &Textures.F_Plant, 3, true, No_Rotationals);
	Load_Animated_Rotational("Machines/B_Generator", &Textures.B_Generator, 3, true, No_Rotationals);
	Load_Animated_Rotational("Machines/Distillery", &Textures.Distillery, 2, false, No_Rotationals);
	Load_Animated_Rotational("Machines/G_Bed", &Textures.G_Bed, 3, true, No_Rotationals);
	Load_Rotational("Machines/B_Scrubber", &Textures.B_Scrubber);
	Textures.MS_Controller = Preload_Texture("Machines/MS_Controller");
	Textures.MS_Output = Preload_Texture("Machines/MS_Output");
	Textures.MS_Input = Preload_Texture("Machines/MS_Input");
	Load_Rotational("Machines/E_Plant", &Textures.E_Plant);
	Load_Animated_Rotational("Machines/F_Mixer", &Textures.F_Mixer, 3, true, No_Rotationals);
	Textures.Flowerpot = Preload_Texture("Machines/Flowerpot");
	Textures.C_Node = Preload_Texture("Machines/C_Node");
	Load_Rotational("Machines/G_Well", &Textures.G_Well);
	Load_Rotational("Machines/H_Exchanger", &Textures.H_Exchanger);
	Load_Rotational("Machines/C_Platform", &Textures.C_Platform);
	Load_Rotational("Machines/T_Tower", &Textures.T_Tower);
	Load_Rotational("Machines/A_Shelf", &Textures.A_Shelf);
	Textures.P_Wood = Preload_Texture("Tiles/P_Wood");
	Textures.B_Tile = Preload_Texture("Tiles/B_Tile");
	Textures.S_Carpet = Preload_Texture("Tiles/S_Carpet");
	Textures.H_Strip = Preload_Texture("Tiles/H_Strip");
	Textures.M_Generator = Preload_Texture("Cheats/M_Generator");
	Textures.F_Generator = Preload_Texture("Cheats/F_Generator");
	Load_Rotational("Machines/R_Intersection", &Textures.R_Intersection);
	Load_Rotational("Machines/L_Intersection", &Textures.L_Intersection);
	Load_Rotational("Machines/SC_Input", &Textures.SC_Input);
	Load_Rotational("Machines/SCH_Sink", &Textures.SCH_Sink);
	Load_Rotational("Machines/SC_Transferor", &Textures.SC_Transferor);
	Load_Rotational("Machines/SC_Output", &Textures.SC_Output);
	Load_Rotational("Machines/ST_Input", &Textures.ST_Input);
	Load_Animated_Rotational("Machines/STIT_Block", &Textures.STIT_Block, 3, true, No_Rotationals);
	Load_Animated_Rotational("Machines/ST_Output", &Textures.ST_Output, 2, true, No_Rotationals);
	Textures.Scrap = Preload_Texture("Tiles/Scrap");
}

void Preload_Foundation() {
	Textures.Pyramid.Data = malloc(sizeof(SDL_Texture*) * 4);
	Textures.Pyramid.Length = 4;
	float Full_Width = ((LDE_GRIDSIZE * 40) + (LDE_BUFFERSIZE * 2)) * Settings.Screen_Size;
	int Candidate_Length = Full_Width * 0.25;
	if (evn_i(Candidate_Length)) {
		Candidate_Length--;
	}
	const int Resolution = 2001;
	SDL_Surface* Mesh_Surface = SDL_CreateSurface(Resolution, Resolution, SDL_PIXELFORMAT_RGBA8888);
	const SDL_PixelFormatDetails* Pixel_Format = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
	SDL_LockSurface(Mesh_Surface);
	uint32_t Empty = SDL_MapRGBA(Pixel_Format, NULL, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
	uint32_t Light = SDL_MapRGBA(Pixel_Format, NULL, Colors.Mid_Grey.r,
		Colors.Mid_Grey.g, Colors.Mid_Grey.b, SDL_ALPHA_OPAQUE);
	uint32_t* Pixels = (uint32_t*)(Mesh_Surface->pixels);
	for (int Counter = 0; Counter < sqr_i(Resolution); Counter++) {
		if (evn_i(Counter) && (int)(Counter & 3) == 0) {
				Pixels[Counter] = Light;
		} else {
			Pixels[Counter] = Empty;
		}
	}
	SDL_UnlockSurface(Mesh_Surface);
	Textures.Mesh = SDL_GenerateTextureFromSurface(Core.Renderer, Mesh_Surface);
	SDL_SetTextureScaleMode(Textures.Mesh, SDL_SCALEMODE_NEAREST);
	SDL_DestroySurface(Mesh_Surface);
	for (int Counter = 0; Counter < 4; Counter++) {
		Textures.Pyramid.Data[Counter] = SDL_GenerateTexture(Core.Renderer, Full_Width * 0.25, Full_Width * 0.25);
		SDL_SetTextureBlendMode(Textures.Pyramid.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_SetTextureScaleMode(Textures.Pyramid.Data[Counter], SDL_SCALEMODE_NEAREST);
	}
	SDL_Color Pyramid_Color = Colors.Reinforced_Grey;
	Pyramid_Color.a = SDL_ALPHA_OPAQUE;
	Set_Renderer_Color(Pyramid_Color);
	float Subwidth = ((LDE_GRIDSIZE + 2) * Settings.Screen_Size * 40.0f) * 0.5f;
	for (int X = 0; X < 2; X++) {
		for (int Y = 0; Y < 2; Y++) {
			SDL_SetRenderTarget(Core.Renderer, Textures.Pyramid.Data[(X * 2) + Y]);
			SDL_FRect Subrectangle = {
				((LDE_BUFFERSIZE - 280.0f) * Settings.Screen_Size) - (X * Subwidth),
				((LDE_BUFFERSIZE - 280.0f) * Settings.Screen_Size) - (Y * Subwidth),
				Settings.Screen_Size * 500.0f,
				Settings.Screen_Size * 500.0f
			};
			SDL_RenderFillRect(Core.Renderer, &Subrectangle);
			Subrectangle.x -= Settings.Screen_Size * 5.0f;
			Subrectangle.y -= Settings.Screen_Size * 5.0f;
			Subrectangle.w += Settings.Screen_Size * 10.0f;
			Subrectangle.h += Settings.Screen_Size * 10.0f;
			for (int Counter = 0; Counter < 5 * Settings.Screen_Size; Counter++) {
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

void Preload_Assets() {
	Preload_Machines();
	Preload_Foundation();
	SDL_Texture* Carrying_Texture = Preload_Texture("UI/Backgrounds/Doors");
	Textures.Door.Data = malloc(sizeof(SDL_Texture*) * 2);
	Textures.Door.Length = 2;
	for (int Counter = 0; Counter < 2; Counter++) {
		Textures.Door.Data[Counter] = SDL_GenerateTexture(Core.Renderer, Settings.Screen_Size * 320,
			Settings.Screen_Size * 360);
		SDL_SetTextureBlendMode(Textures.Door.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core.Renderer, Textures.Door.Data[Counter]);
		SDL_FRect Half_Rectangle = { 1920.0f * Counter, 0, 1920, 2160 };
		Rects.Door[Counter].w = 320 * Settings.Screen_Size;
		Rects.Door[Counter].h = 360 * Settings.Screen_Size;
		SDL_RenderTexture(Core.Renderer, Carrying_Texture, &Half_Rectangle, NULL);
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
	SDL_DestroyTexture(Carrying_Texture);
	Rects.Tunnel.Length = 2;
	Rects.Tunnel.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Tunnel.Data[0].w = Settings.Screen_Size * 240.0f;
	Rects.Tunnel.Data[0].h = Settings.Screen_Size * 90.0f;
	Rects.Tunnel.Data[1].w = Settings.Screen_Size * 90.0f;
	Rects.Tunnel.Data[1].h = Settings.Screen_Size * 240.0f;
	Load_Rotational("Other/Tunnel", &Textures.Tunnel);
	Load_Mirrored("UI/Other/UI_Cap", &Textures.Cap, &Rects.Cap);
	Rects.Cap.y = Settings.Screen_Size * 330;
	Load_Mirrored_Button("UI/Other/UI_Arrow", &Textures.Cap_Button, &Rects.Cap_Button);
	Rects.Cap_Button.y = Settings.Screen_Size * 330;
	Rects.Cap_Hitbox.Length = 2;
	Rects.Cap_Hitbox.Data = malloc(sizeof(SDL_FRect) * 2);
	SDL_Surface* Carrying_Surface = Load_BMP("Assets/Core/Images/UI/Other/Logo.bmp");
	Textures.Logo = SDL_GenerateTextureFromSurface(Core.Renderer, Carrying_Surface);
	SDL_SetWindowIcon(Core.Window, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	SDL_GetTextureSize(Textures.Logo, &Rects.Logo.w, &Rects.Logo.h);
	Rects.Logo.w = (int)(((double)Rects.Logo.w / 6) * Settings.Screen_Size);
	Rects.Logo.h = (int)(((double)Rects.Logo.h / 6) * Settings.Screen_Size);
	Rects.Logo.x = (Settings.Screen_Size * 315) - Rects.Logo.w;
	Rects.Logo.y = Settings.Screen_Size * 32;
	Textures.Crosshair = Preload_Texture("UI/Other/Crosshair");
	Textures.Cursor = Preload_Texture("UI/Other/Cursor");
	Textures.Cursor_Core = Preload_Texture("UI/Other/Cursor_Core");
	Textures.Sapling = Preload_Texture("UI/Other/Sapling");
	Rects.Sapling = Rects.Tile_1x1;
	Textures.Node = Preload_Texture("UI/Other/Node");
	Rects.Node = Rects.Tile_1x1;
	Textures.Path_Arrow = Preload_Texture("UI/Other/Path_Arrow");
	Carrying_Surface = Load_BMP("Assets/Core/Images/UI/Backgrounds/Scrollframe.bmp");
	Textures.Saveloader = Preload_Texture("UI/Backgrounds/Saveloader");
	Rects.Saveloader.x = 0;
	Rects.Saveloader.y = 0;
	Rects.Saveloader.w = Settings.Screen_Size * 640.0f;
	Rects.Saveloader.h = Settings.Screen_Size * 360.0f;
	Textures.Help_Sidebutton = Preload_Sidebutton("Help", &Rects.Help, 60);
	Textures.Save_Sidebutton = Preload_Sidebutton("Save", &Rects.Save, 84);
	Textures.Recipe_Sidebutton = Preload_Sidebutton("Recipe", &Rects.Recipe, 108);
	Textures.Exit_Sidebutton = Preload_Sidebutton("Exit", &Rects.Exit, 132);
	Rects.Return.Length = 2;
	Rects.Return.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Return.Data[0].x = Settings.Screen_Size * 10.0f;
	Rects.Return.Data[0].y = Settings.Screen_Size * 334.0f;
	Rects.New_Game.Length = 2;
	Rects.New_Game.Data = calloc(2, sizeof(SDL_FRect));
	Rects.New_Game.Data[0].x = LDE_INVALID;
	Rects.New_Game.Data[0].y = Settings.Screen_Size * 160.0f;
	Rects.Settings.Length = 2;
	Rects.Settings.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Settings.Data[0].x = LDE_INVALID;
	Rects.Settings.Data[0].y = Settings.Screen_Size * 190.0f;
	Rects.Update_Logs.Length = 2;
	Rects.Update_Logs.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Update_Logs.Data[0].x = LDE_INVALID;
	Rects.Update_Logs.Data[0].y = Settings.Screen_Size * 220.0f;
	Rects.Credits.Length = 2;
	Rects.Credits.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Credits.Data[0].x = LDE_INVALID;
	Rects.Credits.Data[0].y = Settings.Screen_Size * 250.0f;
	Rects.Quit_Game.Length = 2;
	Rects.Quit_Game.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Quit_Game.Data[0].x = LDE_INVALID;
	Rects.Quit_Game.Data[0].y = Settings.Screen_Size * 280.0f;
	Rects.Apply.Length = 2;
	Rects.Apply.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Apply.Data[0].x = Settings.Screen_Size * 60.0f;
	Rects.Apply.Data[0].y = Settings.Screen_Size * 334.0f;
	Rects.Cancel.Length = 2;
	Rects.Cancel.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Cancel.Data[0].x = Settings.Screen_Size * 110.0f;
	Rects.Cancel.Data[0].y = Settings.Screen_Size * 334.0f;
	Rects.Next_Day.Length = 2;
	Rects.Next_Day.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Next_Day.Data[0].x = LDE_INVALID;
	Rects.Next_Day.Data[0].y = Settings.Screen_Size * 300.0f;
	Interface.Map_X = (LDE_TILESIZE * LDE_GRIDSIZE) - 640 + LDE_BUFFERSIZE;
	Interface.Map_Y = (LDE_TILESIZE * LDE_GRIDSIZE) - 360 + LDE_BUFFERSIZE;
	Rects.Subcategories.Length = LDE_CATEGORIES;
	Rects.Subcategories.Data = malloc(sizeof(Rect2_Array) * LDE_CATEGORIES);
	Textures.Subcategories.Length = LDE_CATEGORIES;
	Textures.Subcategories.Data = malloc(sizeof(Texture2_Array) * LDE_CATEGORIES);
	for (int Counter1 = 0; Counter1 < LDE_CATEGORIES; Counter1++) {
		int Length = intlen(Metadata.Subcategory_Positions[Counter1]);
		Rects.Subcategories.Data[Counter1].Length = Length;
		Rects.Subcategories.Data[Counter1].Data = malloc(sizeof(Rect_Array) * Length);
		Textures.Subcategories.Data[Counter1].Length =  Length;
		Textures.Subcategories.Data[Counter1].Data = malloc(sizeof(Texture_Array) * Length);
		for (int Counter2 = 0; Counter2 < Length; Counter2++) {
			Rects.Subcategories.Data[Counter1].Data[Counter2].Length = 2;
			Rects.Subcategories.Data[Counter1].Data[Counter2].Data = calloc(2, sizeof(SDL_FRect));
			Rects.Subcategories.Data[Counter1].Data[Counter2].Data[0].x = LDE_INVALID;
			Rects.Subcategories.Data[Counter1].Data[Counter2].Data[0].y = (float)(
				(Counter2 * 30) + 40) * Settings.Screen_Size;
			Load_Button(Fonts.Halftext_Font, Metadata.Subcategories[Metadata.Subcategory_Positions[
				Counter1][Counter2]], &Textures.Subcategories.Data[Counter1].Data[Counter2],
				Rects.Subcategories.Data[Counter1].Data[Counter2], Colors.Abyss_Black, Colors.Cherry_Blossom);
		}
	}
	Rects.Subcontents.Data = malloc(sizeof(Rect2_Array) * LDE_SUBCATEGORIES);
	Rects.Subcontents.Length = LDE_SUBCATEGORIES;
	Textures.Subcontents.Data = malloc(sizeof(Texture2_Array) * LDE_SUBCATEGORIES);
	Textures.Subcontents.Length = LDE_SUBCATEGORIES;
	for (int Counter1 = 0; Counter1 < LDE_SUBCATEGORIES; Counter1++) {
		int Length = intlen(Metadata.Subcontents[Counter1]);
		Rects.Subcontents.Data[Counter1].Data = malloc(sizeof(Rect_Array) * Length);
		Rects.Subcontents.Data[Counter1].Length = Length;
		Textures.Subcontents.Data[Counter1].Data = malloc(sizeof(Texture_Array) * Length);
		Textures.Subcontents.Data[Counter1].Length = Length;
		for (int Counter2 = 0; Counter2 < Length; Counter2++) {
			Rects.Subcontents.Data[Counter1].Data[Counter2].Length = 2;
			Rects.Subcontents.Data[Counter1].Data[Counter2].Data = calloc(2, sizeof(SDL_FRect));
			Rects.Subcontents.Data[Counter1].Data[Counter2].Data[0].x = LDE_INVALID;
			Rects.Subcontents.Data[Counter1].Data[Counter2].Data[0].y = (float)((Counter2 * 30) + 40) *
				Settings.Screen_Size;
			Load_Button(Fonts.Halftext_Font, Metadata.Names[Metadata.Subcontents[Counter1][Counter2]],
				&Textures.Subcontents.Data[Counter1].Data[Counter2], Rects.Subcontents.Data[Counter1]
				.Data[Counter2], Colors.Abyss_Black, Colors.Cherry_Blossom);
		}
	}
	Rects.Item_Labels.Length = LDE_CATEGORIES;
	Rects.Item_Labels.Data = malloc(sizeof(Rect2_Array) * LDE_CATEGORIES);
	Textures.Item_Labels.Data = malloc(sizeof(Texture2_Array) *	LDE_CATEGORIES);
	Textures.Item_Labels.Length = LDE_CATEGORIES;
	for (int Counter1 = 0; Counter1 < LDE_CATEGORIES; Counter1++) {
		int Length = intlen(Metadata.Item_Labels[Counter1]);
		Rects.Item_Labels.Data[Counter1].Data = malloc(sizeof(Rect_Array) * Length);
		Rects.Item_Labels.Data[Counter1].Length = Length;
		Textures.Item_Labels.Data[Counter1].Data = malloc(sizeof(Texture_Array) * Length);
		Textures.Item_Labels.Data[Counter1].Length = Length;
		for (int Counter2 = 0; Counter2 < Length; Counter2++) {
			Rects.Item_Labels.Data[Counter1].Data[Counter2].Length = 2;
			Rects.Item_Labels.Data[Counter1].Data[Counter2].Data = calloc(2, sizeof(SDL_FRect));
			Rects.Item_Labels.Data[Counter1].Data[Counter2].Data[0].x = LDE_INVALID;
			Rects.Item_Labels.Data[Counter1].Data[Counter2].Data[0].y = (float)(((Counter2 +
				intlen(Metadata.Subcategory_Positions[Counter1])) * 30) + 40) * Settings.Screen_Size;
			Load_Button(Fonts.Halftext_Font, Metadata.Names[Metadata.Item_Labels[Counter1][Counter2]],
				&Textures.Item_Labels.Data[Counter1].Data[Counter2], Rects.Item_Labels.Data[Counter1].Data[Counter2],
				Colors.Abyss_Black, Colors.Cherry_Blossom);
		}
	}
	Rects.Clear_Tutorial.Length = 2;
	Rects.Clear_Tutorial.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Clear_Tutorial.Data[0].x = LDE_INVALID;
	Rects.Clear_Tutorial.Data[0].y = 160;
	Load_Button(Fonts.Halftext_Font, Metadata.Buttons[11], &Textures.Clear_Tutorial, Rects.Clear_Tutorial,
		Colors.Abyss_Black, Colors.Cherry_Blossom);
	Rects.Tutorials.Length = 3;
	Textures.Tutorials.Data = malloc(sizeof(Texture_Array) * 3);
	Textures.Tutorials.Length = 3;
	Rects.Tutorials.Data = malloc(sizeof(Rect_Array) * 3);
	for (int Counter = 0; Counter < 3; Counter++) {
		Rects.Tutorials.Data[Counter].Length = 2;
		Rects.Tutorials.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Tutorials.Data[Counter].Data[0].x = LDE_INVALID;
		Rects.Tutorials.Data[Counter].Data[0].y = (float)((Counter * 40) + 160) * Settings.Screen_Size;
		Load_Button(Fonts.Halftext_Font, Metadata.Buttons[Counter + 12], &Textures.Tutorials.Data[Counter],
			Rects.Tutorials.Data[Counter], Colors.Abyss_Black, Colors.Cherry_Blossom);
	}
	Rects.Tutorial_Hitbox.Length = 2;
	Rects.Tutorial_Hitbox.Data = malloc(sizeof(SDL_FRect) * 2);
	Rects.Cheats.Length = 2;
	Rects.Cheats.Data = malloc(sizeof(Rect_Array) * 2);
	Textures.Cheats.Length = 2;
	Textures.Cheats.Data = malloc(sizeof(Texture_Array) * 2);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.Cheats.Data[Counter].Length = 2;
		Rects.Cheats.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Cheats.Data[Counter].Data[0].x = LDE_INVALID;
		Rects.Cheats.Data[Counter].Data[0].y = (float)((Counter * 40) + 160) * Settings.Screen_Size;
		Load_Button(Fonts.Halftext_Font, Metadata.Buttons[Counter + 9], &Textures.Cheats.Data[Counter],
			Rects.Cheats.Data[Counter], Colors.Abyss_Black, Colors.Cherry_Blossom);
	}
	Rects.Confirmation.Length = 2;
	Rects.Confirmation.Data = malloc(sizeof(Rect_Array) * 2);
	Textures.Confirmation.Length = 2;
	Textures.Confirmation.Data = malloc(sizeof(Texture_Array) * 2);
	for (int Counter1 = 0; Counter1 < 2; Counter1++) {
		Rects.Confirmation.Data[Counter1].Length = 2;
		Rects.Confirmation.Data[Counter1].Data = calloc(2, sizeof(SDL_FRect));
		Load_Button(Fonts.Halftext_Font, Metadata.Buttons[Counter1 + 6],
			&Textures.Confirmation.Data[Counter1], Rects.Confirmation.Data[Counter1],
			Colors.Abyss_Black, Colors.Cherry_Blossom);
		for (int Counter2 = 0; Counter2 < 2; Counter2++) {
			Rects.Confirmation.Data[Counter1].Data[Counter2].x =
				(((Counter1 * 320) + 160) *	Settings.Screen_Size) -
				(Rects.Confirmation.Data[Counter1].Data[Counter2].w * 0.5);
			Rects.Confirmation.Data[Counter1].Data[Counter2].y = Settings.Screen_Size * 260;
		}
	}
	String2 Carrier;
	Carrier.Length = 4;
	Carrier.Data = malloc(sizeof(char*) * Carrier.Length);
	for (int Counter = 0; Counter < 4; Counter++) {
		Carrier.Data[Counter] = Metadata.Buttons[Counter + 27];
	}
	Textures.MSP_Buttons = Preload_Terminal_Sidebar(Carrier, Rects.MSP_Buttons);
	free_c(Carrier.Data);
	Carrier.Length = 4;
	Carrier.Data = malloc(sizeof(char*) * Carrier.Length);
	for (int Counter = 0; Counter < 4; Counter++) {
		Carrier.Data[Counter] = Metadata.Buttons[Counter + 31];
	}
	Textures.SD_Buttons = Preload_Terminal_Sidebar(Carrier, Rects.SD_Buttons);
	free_c(Carrier.Data);
	Carrier.Length = 1;
	Carrier.Data = malloc(sizeof(char*) * Carrier.Length);
	Carrier.Data[0] = Metadata.Buttons[35];
	Textures.HX_Buttons = Preload_Terminal_Sidebar(Carrier, Rects.HX_Buttons);
	Textures.MT_Buttons = Preload_Terminal_Sidebar(Carrier, Rects.MT_Buttons);
	free_c(Carrier.Data);
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[0], &Textures.Return,
		Rects.Return, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(Fonts.Text_Font, Metadata.Buttons[1], &Textures.New_Game,
		Rects.New_Game, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(Fonts.Text_Font, Metadata.Buttons[2], &Textures.Settings,
		Rects.Settings, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(Fonts.Text_Font, Metadata.Buttons[3], &Textures.Update_Logs,
		Rects.Update_Logs, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(Fonts.Text_Font, Metadata.Buttons[4], &Textures.Credits,
		Rects.Credits, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(Fonts.Text_Font, Metadata.Buttons[5], &Textures.Quit_Game,
		Rects.Quit_Game, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[6], &Textures.Apply,
		Rects.Apply, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[7], &Textures.Cancel,
		Rects.Cancel, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[8], &Textures.Next_Day,
		Rects.Next_Day, Colors.Abyss_Black, Colors.Cherry_Blossom);
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
	for (int Counter = 0; Counter < 4; Counter++) {
		Rects.New.Data[Counter].Length = 2;
		Rects.New.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.New.Data[Counter].Data[0].x = 340.0f * Settings.Screen_Size;
		Rects.New.Data[Counter].Data[0].y = (float)((Counter * 40) + 160) * Settings.Screen_Size;
		Load_Button(Fonts.Subtext_Font, Metadata.Buttons[24], &Textures.New.Data[Counter],
			Rects.New.Data[Counter], Colors.Abyss_Black, Colors.Cherry_Blossom);
		Rects.Load.Data[Counter].Length = 2;
		Rects.Load.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Load.Data[Counter].Data[0].x = 340.0f * Settings.Screen_Size;
		Rects.Load.Data[Counter].Data[0].y = (float)((Counter * 40) + 160) * Settings.Screen_Size;
		Load_Button(Fonts.Subtext_Font, Metadata.Buttons[25], &Textures.Load.Data[Counter],
			Rects.Load.Data[Counter], Colors.Abyss_Black, Colors.Cherry_Blossom);
		Rects.Clear.Data[Counter].Length = 2;
		Rects.Clear.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Clear.Data[Counter].Data[0].x = 490.0f * Settings.Screen_Size;
		Rects.Clear.Data[Counter].Data[0].y = (float)((Counter * 40) + 160) * Settings.Screen_Size;
		Load_Button(Fonts.Subtext_Font, Metadata.Buttons[26], &Textures.Clear.Data[Counter],
			Rects.Clear.Data[Counter], Colors.Abyss_Black, Colors.Cherry_Blossom);
	}
	Textures.Categories.Data = malloc(sizeof(Texture_Array) * LDE_CATEGORIES);
	Textures.Categories.Length = LDE_CATEGORIES;
	Rects.Categories.Data = malloc(sizeof(Rect_Array) * LDE_CATEGORIES);
	Rects.Categories.Length = LDE_CATEGORIES;
	for (int Counter = 0; Counter < LDE_CATEGORIES; Counter++) {
		Rects.Categories.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Categories.Data[Counter].Length = 2;
		Rects.Categories.Data[Counter].Data[0].x = LDE_INVALID;
		Rects.Categories.Data[Counter].Data[0].y = (float)((Counter * 30) + 40) * Settings.Screen_Size;
		Load_Button(Fonts.Text_Font, Metadata.Categories[Counter], &Textures.Categories.Data[Counter],
			Rects.Categories.Data[Counter], Colors.Abyss_Black, Colors.Cherry_Blossom);
	}
	char* Captions[LDE_CAPTIONS] = {
		Metadata.Buttons[43], Metadata.Buttons[44], Metadata.Buttons[45],
		Metadata.Buttons[46], Metadata.Buttons[47], Metadata.Buttons[48]
	};
	Rects.Settings_Label.Length = LDE_CAPTIONS;
	Rects.Settings_Label.Data = calloc(LDE_CAPTIONS, sizeof(SDL_FRect));
	Textures.Settings_Label.Length = LDE_CAPTIONS;
	Textures.Settings_Label.Data = malloc(sizeof(SDL_Texture*) * LDE_CAPTIONS);
	for (int Counter = 0; Counter < LDE_CAPTIONS; Counter++) {
		Carrying_Surface = TTF_RenderText_Blended(Fonts.Halftext_Font, Captions[Counter], strlen(Captions[Counter]),
			Colors.Abyss_Black);
		Textures.Settings_Label.Data[Counter] = SDL_GenerateTextureFromSurface(Core.Renderer, Carrying_Surface);
		Rects.Settings_Label.Data[Counter].x = Settings.Screen_Size * 10.0f;
		Rects.Settings_Label.Data[Counter].w = (float)(Carrying_Surface->w);
		Rects.Settings_Label.Data[Counter].h = (float)(Carrying_Surface->h);
		SDL_DestroySurface(Carrying_Surface);
	}
	Rects.Settings_Label.Data[0].y = 10;
	Rects.Settings_Label.Data[1].y = 100;
	Rects.Settings_Label.Data[2].y = 170;
	Rects.Settings_Label.Data[3].y = 240;
	Rects.Settings_Label.Data[4].y = 270;
	Rects.Settings_Label.Data[4].x = 330 * Settings.Screen_Size;
	Rects.Settings_Label.Data[5].y = 10;
	Rects.Settings_Label.Data[5].x = 330 * Settings.Screen_Size;
	for (int Counter = 0; Counter < LDE_CAPTIONS; Counter++) {
		Rects.Settings_Label.Data[Counter].y *= Settings.Screen_Size;
	}
	Rects.Save_Settings.Length = 2;
	Rects.Save_Settings.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Save_Settings.Data[0].y = Settings.Screen_Size * 334.0f;
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[15], &Textures.Save_Settings, Rects.Save_Settings,
		Colors.Abyss_Black, Colors.Cherry_Blossom);
	Rects.Save_Settings.Data[0].x = (Settings.Screen_Size * 630) - Rects.Save_Settings.Data[0].w;
	Rects.Save_Settings.Data[1].x = Rects.Save_Settings.Data[0].x + (Rects.Save_Settings.Data[0].w * 0.5) -
		(Rects.Save_Settings.Data[1].w * 0.5);
	Rects.Error_Exit.Length = 2;
	Rects.Error_Exit.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Error_Exit.Data[0].x = LDE_INVALID;
	Rects.Error_Exit.Data[0].y = Settings.Screen_Size * 50.0f;
	Load_Button(Fonts.Terminal_Font, Metadata.Buttons[36], &Textures.Error_Exit, Rects.Error_Exit,
		Colors.Cherry_Blossom, Colors.Pure_White);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.Error_Exit.Data[Counter].x += Settings.Screen_Size * 210;
	}
	Rects.Anti_Aliasing.Length = 2;
	Rects.Anti_Aliasing.Data = malloc(sizeof(Rect_Array) * 2);
	Textures.Anti_Aliasing.Length = 2;
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.Anti_Aliasing.Data[Counter].Length = 2;
		Rects.Anti_Aliasing.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Anti_Aliasing.Data[Counter].Data[0].x = Settings.Screen_Size * 370.0f;
		Rects.Anti_Aliasing.Data[Counter].Data[0].y = Settings.Screen_Size * 300.0f;
	}
	Textures.Anti_Aliasing.Data = malloc(sizeof(Texture_Array) * 2);
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[22], &Textures.Anti_Aliasing.Data[0],
		Rects.Anti_Aliasing.Data[0], Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[23], &Textures.Anti_Aliasing.Data[1],
		Rects.Anti_Aliasing.Data[1], Colors.Abyss_Black, Colors.Cherry_Blossom);
	Rects.V_Sync.Length = 2;
	Rects.V_Sync.Data = malloc(sizeof(Rect_Array) * 2);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.V_Sync.Data[Counter].Length = 2;
		Rects.V_Sync.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.V_Sync.Data[Counter].Data[0].x = Settings.Screen_Size * 370.0f;
		Rects.V_Sync.Data[Counter].Data[0].y = Settings.Screen_Size * 320.0f;
	}
	Textures.V_Sync.Data = malloc(sizeof(Texture_Array) * 2);
	Textures.V_Sync.Length = 2;
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[20], &Textures.V_Sync.Data[0], Rects.V_Sync.Data[0],
		Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[21], &Textures.V_Sync.Data[1], Rects.V_Sync.Data[1],
		Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.Sort.Data =  malloc(sizeof(Texture_Array) * 2);
	Textures.Sort.Length = 2;
	Rects.Sort.Length = 2;
	Rects.Sort.Data = malloc(sizeof(Rect_Array) * 2);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.Sort.Data[Counter].Length = 2;
		Rects.Sort.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Sort.Data[Counter].Data[0].x = LDE_INVALID;
		Rects.Sort.Data[Counter].Data[0].y = Settings.Screen_Size * 334.0f;
	}
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[18], &Textures.Sort.Data[0],
		Rects.Sort.Data[0], Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[19], &Textures.Sort.Data[1],
		Rects.Sort.Data[1], Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.TBW_Texture.Data = malloc(sizeof(Texture_Array) * 2);
	Textures.TBW_Texture.Length = 2;
	Rects.TBW_Rectangle.Length = 2;
	Rects.TBW_Rectangle.Data = malloc(sizeof(Rect_Array) * 2);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.TBW_Rectangle.Data[Counter].Length = 2;
		Rects.TBW_Rectangle.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.TBW_Rectangle.Data[Counter].Data[0].y = Settings.Screen_Size * 334.0f;
	}
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[16], &Textures.TBW_Texture.Data[0],
		Rects.TBW_Rectangle.Data[0], Colors.Abyss_Black, Colors.Cherry_Blossom);
	Load_Button(Fonts.Subtext_Font, Metadata.Buttons[17], &Textures.TBW_Texture.Data[1],
		Rects.TBW_Rectangle.Data[1], Colors.Abyss_Black, Colors.Cherry_Blossom);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.TBW_Rectangle.Data[Counter].Data[0].x = (Settings.Screen_Size * 630) -
			Rects.TBW_Rectangle.Data[Counter].Data[0].w;
		Rects.TBW_Rectangle.Data[Counter].Data[1].x = Rects.TBW_Rectangle.Data[Counter].Data[0].x +
			(Rects.TBW_Rectangle.Data[Counter].Data[0].w * 0.5) - (Rects.TBW_Rectangle.Data[
			Counter].Data[1].w * 0.5);
	}
	Rects.Tile_1x1.w = (float)(LDE_TILESIZE * Settings.Screen_Size);
	Rects.Tile_1x1.h = (float)(LDE_TILESIZE * Settings.Screen_Size);
	Rects.Tile_1x2.w = (float)(LDE_TILESIZE * Settings.Screen_Size);
	Rects.Tile_1x2.h = LDE_TILESIZE * Settings.Screen_Size * 2.0f;
	Rects.Tile_2x1.w = LDE_TILESIZE * Settings.Screen_Size * 2.0f;
	Rects.Tile_2x1.h = (float)(LDE_TILESIZE * Settings.Screen_Size);
	Rects.Tile_2x2.w = LDE_TILESIZE * Settings.Screen_Size * 2.0f;
	Rects.Tile_2x2.h = LDE_TILESIZE * Settings.Screen_Size * 2.0f;
	Rects.Tile_2x3.w = LDE_TILESIZE * Settings.Screen_Size * 2.0f;
	Rects.Tile_2x3.h = LDE_TILESIZE * Settings.Screen_Size * 3.0f;
	Rects.Tile_3x2.w = LDE_TILESIZE * Settings.Screen_Size * 3.0f;
	Rects.Tile_3x2.h = LDE_TILESIZE * Settings.Screen_Size * 2.0f;
	Rects.Tile_3x3.w = LDE_TILESIZE * Settings.Screen_Size * 3.0f;
	Rects.Tile_3x3.h = LDE_TILESIZE * Settings.Screen_Size * 3.0f;
	Rects.Tile_3x4.w = LDE_TILESIZE * Settings.Screen_Size * 3.0f;
	Rects.Tile_3x4.h = LDE_TILESIZE * Settings.Screen_Size * 4.0f;
	Rects.Tile_4x3.w = LDE_TILESIZE * Settings.Screen_Size * 4.0f;
	Rects.Tile_4x3.h = LDE_TILESIZE * Settings.Screen_Size * 3.0f;
	Rects.Tile_4x6.w = LDE_TILESIZE * Settings.Screen_Size * 4.0f;
	Rects.Tile_4x6.h = LDE_TILESIZE * Settings.Screen_Size * 6.0f;
	Rects.Tile_6x4.w = LDE_TILESIZE * Settings.Screen_Size * 6.0f;
	Rects.Tile_6x4.h = LDE_TILESIZE * Settings.Screen_Size * 4.0f;
	Rects.Tile_6x8.w = LDE_TILESIZE * Settings.Screen_Size * 6.0f;
	Rects.Tile_6x8.h = LDE_TILESIZE * Settings.Screen_Size * 8.0f;
	Rects.Tile_8x6.w = LDE_TILESIZE * Settings.Screen_Size * 8.0f;
	Rects.Tile_8x6.h = LDE_TILESIZE * Settings.Screen_Size * 6.0f;
	Carrying_Surface = Load_BMP("Assets/Core/Images/Other/Submarine.bmp");
	Textures.Submarine.Data = malloc(sizeof(SDL_Texture*) * 2);
	Textures.Submarine.Length = 2;
	for (int Counter = 0; Counter < 2; Counter++) {
		SDL_Surface* Dividing_Surface = SDL_CreateSurface(Carrying_Surface->w * 0.5,
			Carrying_Surface->h, Carrying_Surface->format);
		SDL_Rect Dividing_Rectangle = { (Carrying_Surface->w * 0.5) * Counter, 0,
			Carrying_Surface->w * 0.5, Carrying_Surface->h };
		SDL_BlitSurface(Carrying_Surface, &Dividing_Rectangle, Dividing_Surface, NULL);
		Textures.Submarine.Data[Counter] = SDL_GenerateTextureFromSurface(
			Core.Renderer, Dividing_Surface);
		SDL_DestroySurface(Dividing_Surface);
	}
	SDL_DestroySurface(Carrying_Surface);
	SDL_GetTextureSize(Textures.Submarine.Data[0], &Rects.Submarine.w, &Rects.Submarine.h);
	Rects.Submarine.w = (int)(((double)Rects.Submarine.w / 3) * Settings.Screen_Size);
	Rects.Submarine.h = (int)(((double)Rects.Submarine.h / 6) * Settings.Screen_Size);
	Ctr Container = { {
		Textures.R_Pipe.Data[1], Textures.R_Pump.Data[0], Textures.Incinerator
		.Data[0].Data[0], Textures.P_Generator, Textures.Tile_Texture, Textures
		.S_Dock.Data[0], Textures.F_Plant.Data[0], Textures.B_Generator.Data[0].Data[0],
		Textures.MS_Pool.Data[0], Textures.Distillery.Data[0].Data[0], Textures
		.G_Bed.Data[0].Data[0], Textures.C_Platform.Data[0], Textures.B_Scrubber.Data[0], Textures
		.MS_Controller, Textures.MS_Output, Textures.MS_Input, Textures.E_Plant
		.Data[0], Textures.F_Mixer.Data[0].Data[0], Textures.T_Tower.Data[0],
		Textures.Flowerpot, Textures.A_Shelf.Data[0], Textures.C_Node, Textures
		.G_Well.Data[0], Textures.L_Pipe.Data[1], Textures.H_Exchanger.Data[0], Textures
		.P_Wood, Textures.B_Tile, Textures.S_Carpet, Textures.M_Generator, Textures
		.F_Generator, Textures.R_Intersection.Data[0], Textures.L_Intersection.Data[0],
		Textures.H_Strip, Textures.SC_Input.Data[0], Textures.SCH_Sink.Data[0],
		Textures.SC_Transferor.Data[0], Textures.SC_Output.Data[0], Textures.ST_Input.Data[0],
		Textures.STIT_Block.Data[0].Data[0], Textures.ST_Output.Data[0].Data[0]
	}, {
		Rects.Tile_1x1, Rects.Tile_1x1, Rects.Tile_1x1,
		Rects.Tile_1x1, Rects.Tile_1x1, Rects.Tile_6x4,
		Rects.Tile_2x3, Rects.Tile_3x3,	Rects.Tile_1x1,
		Rects.Tile_2x2, Rects.Tile_2x3,	Rects.Tile_8x6,
		Rects.Tile_2x2, Rects.Tile_1x1,	Rects.Tile_1x1,
		Rects.Tile_1x1, Rects.Tile_3x2,	Rects.Tile_3x3,
		Rects.Tile_3x3, Rects.Tile_1x1,	Rects.Tile_2x1,
		Rects.Tile_1x1, Rects.Tile_2x3,	Rects.Tile_1x1,
		Rects.Tile_4x3, Rects.Tile_1x1,	Rects.Tile_1x1,
		Rects.Tile_1x1, Rects.Tile_1x1,	Rects.Tile_1x1,
		Rects.Tile_3x3, Rects.Tile_3x3,	Rects.Tile_1x1,
		Rects.Tile_2x1, Rects.Tile_2x1,	Rects.Tile_2x3,
		Rects.Tile_2x1, Rects.Tile_2x3, Rects.Tile_2x3,
		Rects.Tile_2x2
	} };
	for (int Counter = 0; Counter < LDE_MACHINES; Counter++) {
		Metadata.Machine_Sprites[Counter] = Container.Textures[Counter];
		Metadata.Machine_Rectangles[Counter] = Container.Rects[Counter];
	}
}