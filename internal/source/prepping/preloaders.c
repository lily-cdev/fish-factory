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

void Preload_Assets() {
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
	Textures.Return = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[0],
		Rects.Return, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.New_Game = Load_Button(Fonts.Text_Font, Metadata.Buttons[1],
		Rects.New_Game, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.Settings = Load_Button(Fonts.Text_Font, Metadata.Buttons[2],
		Rects.Settings, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.Update_Logs = Load_Button(Fonts.Text_Font, Metadata.Buttons[3],
		Rects.Update_Logs, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.Credits = Load_Button(Fonts.Text_Font, Metadata.Buttons[4],
		Rects.Credits, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.Quit_Game = Load_Button(Fonts.Text_Font, Metadata.Buttons[5],
		Rects.Quit_Game, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.Apply = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[6],
		Rects.Apply, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.Cancel = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[7],
		Rects.Cancel, Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.Next_Day = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[8],
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
		Rects.New.Data[Counter].Data[0].w = 0;
		Rects.New.Data[Counter].Data[0].h = 0;
		Textures.New.Data[Counter] = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[24],
			Rects.New.Data[Counter], Colors.Abyss_Black, Colors.Cherry_Blossom);
		Rects.Load.Data[Counter].Length = 2;
		Rects.Load.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Load.Data[Counter].Data[0].x = 340.0f * Settings.Screen_Size;
		Rects.Load.Data[Counter].Data[0].y = (float)((Counter * 40) + 160) * Settings.Screen_Size;
		Rects.Load.Data[Counter].Data[0].w = 0;
		Rects.Load.Data[Counter].Data[0].h = 0;
		Textures.Load.Data[Counter] = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[25],
			Rects.Load.Data[Counter], Colors.Abyss_Black, Colors.Cherry_Blossom);
		Rects.Clear.Data[Counter].Length = 2;
		Rects.Clear.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Clear.Data[Counter].Data[0].x = 490.0f * Settings.Screen_Size;
		Rects.Clear.Data[Counter].Data[0].y = (float)((Counter * 40) + 160) * Settings.Screen_Size;
		Rects.Clear.Data[Counter].Data[0].w = 0;
		Rects.Clear.Data[Counter].Data[0].h = 0;
		Textures.Clear.Data[Counter] = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[26],
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
		Rects.Categories.Data[Counter].Data[0].y = (float)(40 + (Counter * 30)) * Settings.Screen_Size;
		Rects.Categories.Data[Counter].Data[0].w = 0;
		Rects.Categories.Data[Counter].Data[0].h = 0;
		Textures.Categories.Data[Counter] = Load_Button(Fonts.Text_Font,
			Metadata.Categories[Counter], Rects.Categories.Data[Counter],
			Colors.Abyss_Black, Colors.Cherry_Blossom);
	}
	Rects.Error_Exit.Length = 2;
	Rects.Error_Exit.Data = calloc(2, sizeof(SDL_FRect));
	Rects.Error_Exit.Data[0].x = LDE_INVALID;
	Rects.Error_Exit.Data[0].y = Settings.Screen_Size * 50.0f;
	Rects.Error_Exit.Data[0].w = 0;
	Rects.Error_Exit.Data[0].h = 0;
	Textures.Error_Exit = Load_Button(Fonts.Terminal_Font, Metadata.Buttons[36],
		Rects.Error_Exit, Colors.Cherry_Blossom, Colors.Pure_White);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.Error_Exit.Data[Counter].x += Settings.Screen_Size * 210;
	}
	Rects.Anti_Aliasing.Length = 2;
	Rects.Anti_Aliasing.Data = malloc(sizeof(Rect_Array) * 2);
	Textures.Anti_Aliasing.Length = 2;
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.Anti_Aliasing.Data[Counter].Length = 2;
		Rects.Anti_Aliasing.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Anti_Aliasing.Data[Counter].Data[0].x = 370.0f * Settings.Screen_Size;
		Rects.Anti_Aliasing.Data[Counter].Data[0].y = 300.0f * Settings.Screen_Size;
		Rects.Anti_Aliasing.Data[Counter].Data[0].w = 0;
		Rects.Anti_Aliasing.Data[Counter].Data[0].h = 0;
	}
	Textures.Anti_Aliasing.Data = malloc(sizeof(Texture_Array) * 2);
	Textures.Anti_Aliasing.Data[0] = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[22],
		Rects.Anti_Aliasing.Data[0], Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.Anti_Aliasing.Data[1] = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[23],
		Rects.Anti_Aliasing.Data[1], Colors.Abyss_Black, Colors.Cherry_Blossom);
	Rects.V_Sync.Length = 2;
	Rects.V_Sync.Data = malloc(sizeof(Rect_Array) * 2);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.V_Sync.Data[Counter].Length = 2;
		Rects.V_Sync.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.V_Sync.Data[Counter].Data[0].x = 370.0f * Settings.Screen_Size;
		Rects.V_Sync.Data[Counter].Data[0].y = 320.0f * Settings.Screen_Size;
		Rects.V_Sync.Data[Counter].Data[0].w = 0;
		Rects.V_Sync.Data[Counter].Data[0].h = 0;
	}
	Textures.V_Sync.Data = malloc(sizeof(Texture_Array) * 2);
	Textures.V_Sync.Length = 2;
	Textures.V_Sync.Data[0] = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[20],
		Rects.V_Sync.Data[0], Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.V_Sync.Data[1] = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[21],
		Rects.V_Sync.Data[1], Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.Sort.Data =  malloc(sizeof(Texture_Array) * 2);
	Textures.Sort.Length = 2;
	Rects.Sort.Length = 2;
	Rects.Sort.Data = malloc(sizeof(Rect_Array) * 2);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.Sort.Data[Counter].Length = 2;
		Rects.Sort.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.Sort.Data[Counter].Data[0].x = LDE_INVALID;
		Rects.Sort.Data[Counter].Data[0].y = 334.0f * Settings.Screen_Size;
		Rects.Sort.Data[Counter].Data[0].w = 0;
		Rects.Sort.Data[Counter].Data[0].h = 0;
	}
	Textures.Sort.Data[0] = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[18],
		Rects.Sort.Data[0], Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.Sort.Data[1] = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[19],
		Rects.Sort.Data[1], Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.TBW_Texture.Data = malloc(sizeof(Texture_Array) * 2);
	Textures.TBW_Texture.Length = 2;
	Rects.TBW_Rectangle.Length = 2;
	Rects.TBW_Rectangle.Data = malloc(sizeof(Rect_Array) * 2);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.TBW_Rectangle.Data[Counter].Length = 2;
		Rects.TBW_Rectangle.Data[Counter].Data = calloc(2, sizeof(SDL_FRect));
		Rects.TBW_Rectangle.Data[Counter].Data[0].x = 0;
		Rects.TBW_Rectangle.Data[Counter].Data[0].y = 334.0f * Settings.Screen_Size;
		Rects.TBW_Rectangle.Data[Counter].Data[0].w = 0;
		Rects.TBW_Rectangle.Data[Counter].Data[0].h = 0;
	}
	Textures.TBW_Texture.Data[0] = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[16],
		Rects.TBW_Rectangle.Data[0], Colors.Abyss_Black, Colors.Cherry_Blossom);
	Textures.TBW_Texture.Data[1] = Load_Button(Fonts.Subtext_Font, Metadata.Buttons[17],
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
	SDL_Surface* Carrying_Surface = Load_BMP("Assets/Core/Images/Other/Submarine.bmp");
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