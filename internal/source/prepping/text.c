#include <prepping.h>

void Recache_TT_Commands() {
	String2 Carrier;
	Carrier.Length = Temporary.Docks.Length;
	Carrier.Data = malloc(sizeof(char*) * Carrier.Length);
	for (int Counter = 0; Counter < Carrier.Length; Counter++) {
		char Buffer[128];
		snprintf(Buffer, sizeof(Buffer), "Dock %d", Counter + 1);
		Carrier.Data[Counter] = Buffer;
	}
	Preload_Terminal_Sidebar(Carrier, &Textures.TT_Buttons, &Rects.TT_Buttons);
	free_c(Carrier.Data);
}

void Preload_Terminal_Sidebar(const String2 Texts, Texture2_Array* Yield, Rect2_Array* Rectangles) {
	String2 Carrier;
	Carrier.Length = Texts.Length + 2;
	Carrier.Data = malloc(sizeof(char*) * Carrier.Length);
	for (int Counter = 0; Counter < Texts.Length; Counter++) {
		Carrier.Data[Counter] = malloc(sizeof(char) * (strlen(Texts.Data[Counter]) + 1));
		strcpy(Carrier.Data[Counter], Texts.Data[Counter]);
	}
	Carrier.Data[Carrier.Length - 1] = malloc(sizeof(char) * (strlen(Metadata.Buttons[37]) + 1));
	Carrier.Data[Carrier.Length - 2] = malloc(sizeof(char) * (strlen(Metadata.Buttons[36]) + 1));
	strcpy(Carrier.Data[Carrier.Length - 1], Metadata.Buttons[37]);
	strcpy(Carrier.Data[Carrier.Length - 2], Metadata.Buttons[36]);
	Yield->Length = Carrier.Length;
	Yield->Data = malloc(sizeof(Texture_Array) * Carrier.Length);
	Rectangles->Length = Carrier.Length;
	Rectangles->Data = malloc(sizeof(Rect_Array) * Carrier.Length);
	for (int Counter1 = 0; Counter1 < Carrier.Length; Counter1++) {
		Rectangles->Data[Counter1].Length = 2;
		Rectangles->Data[Counter1].Data = calloc(2, sizeof(SDL_FRect));
		Rectangles->Data[Counter1].Data[0].x = LDE_INVALID;
		Rectangles->Data[Counter1].Data[0].y = (float)((Counter1 * 30) + 50) * Settings.Screen_Size;
		Load_Button(Fonts.Terminal_Font, Carrier.Data[Counter1], &Yield->Data[Counter1], Rectangles->Data[Counter1],
			Colors.Cherry_Blossom, Colors.Pure_White);
		for (int Counter2 = 0; Counter2 < 2; Counter2++) {
			Rectangles->Data[Counter1].Data[Counter2].x += Settings.Screen_Size * 210;
		}
	}
	Free_String2(&Carrier);
}

void Load_Button(TTF_Font* Font, const char* Text, Texture_Array* Yield, Rect_Array Rectangles,
	SDL_Color Color1, SDL_Color Color2) {
	Yield->Length = 2;
	Yield->Data = malloc(sizeof(SDL_Texture*) * 2);
	SDL_Surface* Button_Surface = TTF_RenderText_Blended(Font, Text, 0, Color1);
	Yield->Data[0] = SDL_GenerateTextureFromSurface(Core.Renderer, Button_Surface);
	if (Rectangles.Data[0].x == LDE_INVALID) {
		Rectangles.Data[0].x = (320 * Settings.Screen_Size) - (Button_Surface->w * 0.5);
	}
	if (Rectangles.Data[0].y == LDE_INVALID) {
		Rectangles.Data[0].y = (180 * Settings.Screen_Size) - (Button_Surface->h * 0.5);
	}
	Rectangles.Data[0].w = Button_Surface->w;
	Rectangles.Data[0].h = Button_Surface->h;
	char Buffer[256];
	snprintf(Buffer, sizeof(Buffer), "> %s <", Text);
	SDL_DestroySurface(Button_Surface);
	Button_Surface = TTF_RenderText_Blended(Font, "> ", 0, Color1);
	int Offset = Button_Surface->w;
	SDL_DestroySurface(Button_Surface);
	Button_Surface = TTF_RenderText_Blended(Font, Buffer, 0, Color2);
	Yield->Data[1] = SDL_GenerateTextureFromSurface(Core.Renderer, Button_Surface);
	Rectangles.Data[1].x = Rectangles.Data[0].x - Offset;
	Rectangles.Data[1].y = Rectangles.Data[0].y;
	Rectangles.Data[1].w = (float)(Button_Surface->w);
	Rectangles.Data[1].h = (float)(Button_Surface->h);
	SDL_DestroySurface(Button_Surface);
}