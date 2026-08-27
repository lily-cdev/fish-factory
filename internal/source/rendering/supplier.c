#include <rendering.h>

void Process_Supply(Texture_Supply* Supply, const char* Replacement, Font_Index Font, const SDL_Color Color, Point Pos) {
	if (Replacement == NULL || strlen(Replacement) <= 0) {
		return;
	}
	if (strcmp(Supply->Stored, Replacement) != 0 || !Compare_Colors(Supply->Color, Color) || Supply->Data == NULL ||
		Supply->Bounds.y != ktn_fscale(Pos.Y) || Supply->Bounds.x != ktn_fscale(Pos.X)) {
		ktn_free_texture(Supply->Data);
		memset(&Supply->Bounds, 0, sizeof(SDL_FRect));
		Supply->Bounds.y = ktn_fscale(Pos.Y);
		strncpy(Supply->Stored, Replacement, sizeof(Supply->Stored));
		Supply->Color = (SDL_Color){ Color.r, Color.g, Color.b, Color.a };
		SDL_Texture* Carrier = Render_Text(Font, Replacement, Color);
		if (Carrier == NULL) {
			puts("1");
		}
		Supply->Bounds.w = Carrier->w;
		Supply->Bounds.h = Carrier->h;
		Supply->Bounds.x = (Pos.X == ktn_invalid) ? Core.Screenhalfsize.X - (Carrier->w * 0.5f) : ktn_fscale(Pos.X);
		Supply->Data = Carrier;
	}
	Render_Texture(Supply->Data, &Supply->Bounds);
}

void Free_Supplies() {
	ktn_free_texture(Supplies.FPS.Data);
	ktn_free_texture(Supplies.Scroll_Percent.Data);
	ktn_free_texture(Supplies.Changelog_Scroll.Data);
	ktn_free_texture(Supplies.Report_Header.Data);
	ktn_free_texture(Supplies.Monitor_Size.Data);
	ktn_free_texture(Supplies.Tutorial.Data);
	ktn_free_texture(Supplies.Subtutorial.Data);
	ktn_free_texture(Supplies.Fluid_Production.Data);
	ktn_free_texture(Supplies.Money_Production.Data);
	ktn_free_texture(Supplies.Power_Production.Data);
	ktn_free_texture(Supplies.Shop1.Data);
	ktn_free_texture(Supplies.Shop2.Data);
	ktn_free_texture(Supplies.Shop3.Data);
	ktn_free_texture(Supplies.Shop4.Data);
	ktn_free_texture(Supplies.Shop5.Data);
	ktn_free_texture(Supplies.Save_Text.Data);
	ktn_free_texture(Supplies.Terminal_Title.Data);
	ktn_free_texture(Supplies.Terminal_Command.Data);
	for (int C1 = 0; C1 < ktn_log_max; C1++) {
		ktn_free_texture(Supplies.Terminal_Logs[C1].Data);
	}
	for (int C1 = 0; C1 < ktn_recipe_types; C1++) {
		ktn_free_texture(Supplies.Catalog1[C1].Data);
		ktn_free_texture(Supplies.Catalog2[C1].Data);
		ktn_free_texture(Supplies.Catalog3[C1].Data);
	}
	for (int C1 = 0; C1 < ktn_savefiles; C1++) {
		ktn_free_texture(Supplies.Filesizes[C1].Data);
	}
}