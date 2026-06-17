#include <prepping.h>

void Recache_TT_Commands() {
	String2 Carrier;
	Carrier.Length = min(Temporary.Docks.Length, ktn_cmd_max);
	Carrier.Data = malloc(sizeof(char*) * Carrier.Length);
	for (int C1 = 0; C1 < Carrier.Length; C1++) {
		Carrier.Data[C1] = malloc(128);
		snprintf(Carrier.Data[C1], 128, "Dock %d", C1 + 1);
	}
	Preload_Terminal_Sidebar(&Carrier, &Textures.TT_Buttons, &Rects.TT_Buttons);
	Free_String2(&Carrier);
}

void Preload_Terminal_Sidebar(const String2* Texts, Texture2_Array* Yield, Rect2_Array* Rectangles) {
	String2 Carrier;
	Carrier.Length = Texts->Length + 2;
	Carrier.Data = malloc(sizeof(char*) * Carrier.Length);
	for (int C1 = 0; C1 < Texts->Length; C1++) {
		Carrier.Data[C1] = malloc(strlen(Texts->Data[C1]) + 1);
		strcpy(Carrier.Data[C1], Texts->Data[C1]);
	}
	Carrier.Data[Carrier.Length - 2] = malloc(strlen(Metadata.Buttons[37]) + 1);
	Carrier.Data[Carrier.Length - 1] = malloc(strlen(Metadata.Buttons[36]) + 1);
	strcpy(Carrier.Data[Carrier.Length - 2], Metadata.Buttons[37]);
	strcpy(Carrier.Data[Carrier.Length - 1], Metadata.Buttons[36]);
	Yield->Length = Carrier.Length;
	Yield->Data = malloc(sizeof(Texture_Array) * Carrier.Length);
	Rectangles->Length = Carrier.Length;
	Rectangles->Data = malloc(sizeof(Rect_Array) * Carrier.Length);
	for (int C1 = 0; C1 < Carrier.Length; C1++) {
		Rectangles->Data[C1].Length = 2;
		Rectangles->Data[C1].Data = calloc(2, sizeof(SDL_FRect));
		Rectangles->Data[C1].Data[0].x = ktn_invalid;
		Rectangles->Data[C1].Data[0].y = ktn_fscale((C1 * 30.0f) + 50.0f);
		Load_Button(F_Text, Carrier.Data[C1], &Yield->Data[C1], Rectangles->Data[C1],
			Colors.Cherry_Blossom, Colors.Pure_White);
		for (int C2 = 0; C2 < 2; C2++) {
			Rectangles->Data[C1].Data[C2].x += ktn_fscale(210.0f);
		}
	}
	Free_String2(&Carrier);
}

void Load_Button(Font_Index Font, const char* Text, Texture_Array* Yield, Rect_Array Rectangles, SDL_Color Color1,
	SDL_Color Color2) {
	Yield->Length = 2;
	Yield->Data = malloc(sizeof(SDL_Texture*) * 2);
	SDL_Texture* Carrier = Render_Text(Font, Text, Color1);
	Yield->Data[0] = Carrier;
	if (Rectangles.Data[0].x == ktn_invalid) {
		Rectangles.Data[0].x = Core.Screenhalfsize.X - (Carrier->w * 0.5f);
	}
	if (Rectangles.Data[0].y == ktn_invalid) {
		Rectangles.Data[0].y = Core.Screenhalfsize.Y - (Carrier->h * 0.5f);
	}
	Rectangles.Data[0].w = Carrier->w;
	Rectangles.Data[0].h = Carrier->h;
	char Buffer[256];
	snprintf(Buffer, sizeof(Buffer), "> %s <", Text);
	Carrier = Render_Text(Font, "> ", Color1);
	int Offset = Carrier->w;
	ktn_free_texture(Carrier);
	Carrier = Render_Text(Font, Buffer, Color2);
	Yield->Data[1] = Carrier;
	Rectangles.Data[1] = (SDL_FRect){
		Rectangles.Data[0].x - Offset,
		Rectangles.Data[0].y,
		(float)Carrier->w,
		(float)Carrier->h
	};
}