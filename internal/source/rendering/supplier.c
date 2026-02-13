#include <rendering.h>

void Process_Supply(Texture_Supply* Supply, const char* Replacement, TTF_Font* Font, const SDL_Color Color, int X, int Y) {
	if (Replacement == NULL) {
		puts("failed");
	}
	if (strcmp(Supply->Stored, Replacement) != 0 || !Compare_Colors(Supply->Color, Color) || Supply->Data == NULL) {
		free_texture(Supply->Data);
		memset(&Supply->Bounds, 0, sizeof(SDL_FRect));
		Supply->Bounds.y = Y * Settings.Screen_Size;
		strncpy(Supply->Stored, Replacement, sizeof(Supply->Stored));
		Supply->Color.r = Color.r;
		Supply->Color.g = Color.g;
		Supply->Color.b = Color.b;
		Supply->Color.a = Color.a;
		SDL_Surface* Carrier = TTF_RenderText_Blended(Font, Replacement, 0, Color);
		if (Carrier == NULL) {
			puts("1");
		}
		Supply->Bounds.w = Carrier->w;
		Supply->Bounds.h = Carrier->h;
		if (X == LDE_INVALID) {
			Supply->Bounds.x = (Settings.Screen_Size * 320) - (Carrier->w * 0.5);
		} else {
			Supply->Bounds.x = X * Settings.Screen_Size;
		}
		Supply->Data = SDL_GenerateTextureFromSurface(Core.Renderer, Carrier);
		SDL_DestroySurface(Carrier);
	}
	Render_Texture(Supply->Data, &Supply->Bounds);
}

void Free_Supplies() {
	free_texture(Supplies.FPS.Data);
	free_texture(Supplies.Scroll_Percent.Data);
	free_texture(Supplies.Changelog_Scroll.Data);
	free_texture(Supplies.Report_Header.Data);
	free_texture(Supplies.Monitor_Size.Data);
	free_texture(Supplies.Tutorial.Data);
	free_texture(Supplies.Subtutorial.Data);
	free_texture(Supplies.Fluid_Production.Data);
	free_texture(Supplies.Money_Production.Data);
	free_texture(Supplies.Shop1.Data);
	free_texture(Supplies.Shop2.Data);
	free_texture(Supplies.Shop3.Data);
	free_texture(Supplies.Shop4.Data);
	free_texture(Supplies.Shop5.Data);
	free_texture(Supplies.Money.Data);
	free_texture(Supplies.Time.Data);
	free_texture(Supplies.Save_Text.Data);
	free_texture(Supplies.Terminal_Title.Data);
	free_texture(Supplies.Terminal_Command.Data);
	for (int C1 = 0; C1 < LDE_LOGMAX; C1++) {
		free_texture(Supplies.Terminal_Logs[C1].Data);
	}
	for (int C1 = 0; C1 < LDE_RECIPETYPES; C1++) {
		free_texture(Supplies.Catalog1[C1].Data);
		free_texture(Supplies.Catalog2[C1].Data);
		free_texture(Supplies.Catalog3[C1].Data);
	}
	for (int C1 = 0; C1 < LDE_SAVEFILES; C1++) {
		free_texture(Supplies.Filesizes[C1].Data);
	}
}