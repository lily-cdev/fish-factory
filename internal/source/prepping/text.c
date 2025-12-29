#include <prepping.h>

void Recache_TT_Commands() {
	Metadata.TT_Texts[0].Data = realloc(Metadata.TT_Texts[0].Data, sizeof(String1));
	Metadata.TT_Texts[0].Length = 1;
	Metadata.TT_Texts[1].Data = realloc(Metadata.TT_Texts[1].Data,
		sizeof(String1) * (Temporary.Docks.Length + 1));
	Metadata.TT_Texts[1].Length = Temporary.Docks.Length + 1;
	Metadata.TT_Parameters[0].Data = realloc(Metadata.TT_Parameters[
		0].Data, sizeof(String2));
	Metadata.TT_Parameters[0].Length = 1;
	Metadata.TT_Parameters[0].Data[0].Data = realloc(Metadata.TT_Parameters[
		0].Data[0].Data, sizeof(String1) * 2);
	Metadata.TT_Parameters[0].Data[0].Length = 2;
	Metadata.TT_Parameters[1].Data = realloc(Metadata.TT_Parameters[
		1].Data, sizeof(String2) * (Temporary.Docks.Length + 1));
	Metadata.TT_Parameters[1].Length = Temporary.Docks.Length + 1;
	for (int Counter = 0; Counter < Temporary.Docks.Length + 1; Counter++) {
		Metadata.TT_Parameters[1].Data[Counter].Data = realloc(Metadata.TT_Parameters[
			1].Data, sizeof(String1) * 2);
		Metadata.TT_Parameters[1].Data[Counter].Length = 2;
	}
	for (int Counter = 0; Counter < LDE_TTSLIDES; Counter++) {
		Metadata.TT_Types[Counter] = malloc(sizeof(int) * 2);
	}
	Metadata.TT_Texts[0].Data[0] = Metadata.Buttons[38];
	Metadata.TT_Texts[1].Data[0] = Metadata.Buttons[39];
	Metadata.TT_Parameters[0].Data[0].Data[0] = Metadata.Buttons[40];
	Metadata.TT_Parameters[0].Data[0].Data[1] = Metadata.Buttons[42];
	Metadata.TT_Parameters[1].Data[0].Data[0] = Metadata.Buttons[40];
	Metadata.TT_Parameters[1].Data[0].Data[1] = Metadata.Buttons[41];
	Metadata.TT_Types[0][0] = Execute;
	Metadata.TT_Types[0][1] = Execute;
	Metadata.TT_Types[1][0] = LDE_INVALID;
	Metadata.TT_Types[1][1] = LDE_INVALID;
	for (int Counter = 0; Counter < Temporary.Docks.Length; Counter++) {
		char Buffer[256];
		snprintf(Buffer, sizeof(Buffer), "Dock %d", Counter + 1);
		String1 Text_String;
		Text_String.Data = malloc(sizeof(char) * (strlen(Buffer) + 1));
		strcpy(Text_String.Data, Buffer);
		Text_String.Data[strlen(Buffer)] = '\0';
		Text_String.Length = strlen(Buffer) + 1;
		Metadata.TT_Texts[1].Data[Counter + 1] = Text_String;
		snprintf(Buffer, sizeof(Buffer), "POS_DOCK_%d", Counter + 1);
		String1 Parameter_String;
		Parameter_String.Data = malloc(sizeof(char) * (strlen(Buffer) + 1));
		strcpy(Parameter_String.Data, Buffer);
		Parameter_String.Data[strlen(Buffer)] = '\0';
		Parameter_String.Length = strlen(Buffer) + 1;
		Metadata.TT_Parameters[1].Data[Counter].Data[0] = Metadata.Buttons[40];
		Metadata.TT_Parameters[1].Data[Counter].Data[1] = Parameter_String;
	}
	Reload_Commandlist(&Textures.TT_Buttons, &Rects.TT_Buttons, Metadata.TT_Texts);
}

Texture2_Array Preload_Terminal_Sidebar(const String2 Texts, Rect2_Array Rectangles) {
	String2 Carrier;
	Carrier.Length = Texts.Length + 2;
	Carrier.Data = malloc(sizeof(String1) * Carrier.Length);
	if (Carrier.Data==NULL)printf("CARRIER FAILED");
	memcpy(Carrier.Data, Texts.Data, sizeof(String1) * Texts.Length);
	Carrier.Data[Carrier.Length - 1].Data = malloc(sizeof(char) * Metadata.Buttons[37].Length);
	Carrier.Data[Carrier.Length - 2].Data = malloc(sizeof(char) * Metadata.Buttons[36].Length);
	strcpy(Carrier.Data[Carrier.Length - 1].Data, Metadata.Buttons[37].Data);
	strcpy(Carrier.Data[Carrier.Length - 2].Data, Metadata.Buttons[36].Data);
	Carrier.Data[Carrier.Length - 1].Length = Metadata.Buttons[37].Length;
	Carrier.Data[Carrier.Length - 2].Length = Metadata.Buttons[36].Length;
	Texture2_Array Yield;
	Yield.Length = Carrier.Length;
	Yield.Data = malloc(sizeof(Texture_Array) * Carrier.Length);
	Rectangles.Length = Carrier.Length;
	Rectangles.Data = malloc(sizeof(Rect_Array) * Carrier.Length);
	for (int Counter1 = 0; Counter1 < Carrier.Length; Counter1++) {
		Rectangles.Data[Counter1].Length = 2;
		Rectangles.Data[Counter1].Data = calloc(2, sizeof(SDL_FRect));
		Rectangles.Data[Counter1].Data[0].x = LDE_INVALID;
		Rectangles.Data[Counter1].Data[0].y = (float)(50 + (Counter1 * 30)) * Settings.Screen_Size;
		Rectangles.Data[Counter1].Data[0].w = 0;
		Rectangles.Data[Counter1].Data[0].h = 0;
		Yield.Data[Counter1] = Load_Button(Fonts.Terminal_Font, Carrier.Data[Counter1],
			Rectangles.Data[Counter1], Colors.Cherry_Blossom, Colors.Pure_White);
		for (int Counter2 = 0; Counter2 < 2; Counter2++) {
			Rectangles.Data[Counter1].Data[Counter2].x += 210 * Settings.Screen_Size;
		}
	}
	printf("-----\n");
	for (int x=0; x<Carrier.Length;x++) {
		printf("%s\n", Carrier.Data[x].Data);
	}
	Free_String2(&Carrier);
	return Yield;
}

void Reload_Commandlist(Texture3_Array* Commandlist, Rect3_Array* Boxlist, String2 Contents[LDE_TTSLIDES]) {
	Clear_Rect3_Array(Boxlist);
	Clear_Texture3_Array(Commandlist);
	Boxlist->Length = LDE_TTSLIDES;
	Boxlist->Data = malloc(sizeof(Rect2_Array) * LDE_TTSLIDES);
	Commandlist->Length = LDE_TTSLIDES;
	Commandlist->Data = malloc(sizeof(Texture2_Array) * LDE_TTSLIDES);
	for (int Counter = 0; Counter < LDE_TTSLIDES; Counter++) {
		Commandlist->Data[Counter] = Preload_Terminal_Sidebar(
			Contents[Counter], Boxlist->Data[Counter]);
	}
}

Texture_Array Load_Button(TTF_Font* Font, const String1 Text, Rect_Array Rectangles, SDL_Color Color1, SDL_Color Color2) {
	Texture_Array Yield;
	Yield.Length = 2;
	Yield.Data = malloc(sizeof(SDL_Texture*) * 2);
	SDL_Surface* Button_Surface = TTF_RenderText_Blended(Font, Text.Data, Text.Length - 1, Color1);
	Yield.Data[0] = SDL_GenerateTextureFromSurface(Core.Renderer, Button_Surface);
	if (Rectangles.Data[0].x == LDE_INVALID) {
		Rectangles.Data[0].x = (320 * Settings.Screen_Size) - (Button_Surface->w * 0.5);
	}
	if (Rectangles.Data[0].y == LDE_INVALID) {
		Rectangles.Data[0].y = (180 * Settings.Screen_Size) - (Button_Surface->h * 0.5);
	}
	Rectangles.Data[0].w = Button_Surface->w;
	Rectangles.Data[0].h = Button_Surface->h;
	char Buffer[256];
	snprintf(Buffer, sizeof(Buffer), "> %s <", Text.Data);
	SDL_DestroySurface(Button_Surface);
	Button_Surface = TTF_RenderText_Blended(Font, "> ", 2, Color1);
	int Offset = Button_Surface->w;
	SDL_DestroySurface(Button_Surface);
	Button_Surface = TTF_RenderText_Blended(Font, Buffer, strlen(Buffer), Color2);
	Yield.Data[1] = SDL_GenerateTextureFromSurface(Core.Renderer, Button_Surface);
	Rectangles.Data[1].x = Rectangles.Data[0].x - Offset;
	Rectangles.Data[1].y = Rectangles.Data[0].y;
	Rectangles.Data[1].w = (float)(Button_Surface->w);
	Rectangles.Data[1].h = (float)(Button_Surface->h);
	SDL_DestroySurface(Button_Surface);
	return Yield;
}