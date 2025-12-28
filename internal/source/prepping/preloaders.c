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