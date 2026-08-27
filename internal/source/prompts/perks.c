#include <ui.h>

void Render_Perks(Point Pos) {
	Render_Box((Point){ 10, 10 }, 620, 340, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Texture(Textures.Perks_Content, &Rects.Perks_Content);
	for (int C1 = 0; C1 < Core.Perks; C1++) {
		SDL_FRect Bounding = { ktn_fscale((C1 * 52) + 20), ktn_fscale(50), ktn_fscale(40), ktn_fscale(40) };
		SDL_FRect Initial = Bounding;
		Set_Renderer_Color((Detect_Mouse_Collision(Initial)) ? Colors.Cherry_Blossom : Colors.Abyss_Black);
		SDL_RenderFillRect(Core.Renderer, &Bounding);
		Set_Renderer_Color(Colors.Mid_Grey);
		Bounding.x += ktn_fscale(2);
		Bounding.y += ktn_fscale(2);
		Bounding.w -= ktn_fscale(4);
		Bounding.h -= ktn_fscale(4);
		SDL_RenderFillRect(Core.Renderer, &Bounding);
		Clear_Renderer();
		SDL_FRect Subcarrier = {
			Bounding.x += ktn_fscale(2),
			Bounding.y += ktn_fscale(2),
			Bounding.w -= ktn_fscale(4),
			Bounding.h -= ktn_fscale(4)
		};
		Render_Texture((Metadata.Perks[C1].Owned) ? Textures.Perk_Owned : Metadata.Perks[C1].Icon, &Subcarrier);
		if (Detect_Mouse_Collision(Initial)) {
			Interface.UI_Query = (UI_Link){ .Carrier = Buy_Perk, .Param.Integer = C1 };
			char Subcarrier[128];
			char Buffer[128];
			if (Metadata.Perks[C1].Owned) {
				strcpy(Buffer, "bought");
			} else {
				Abbreviate_Number(Metadata.Perks[C1].Cost, Buffer, sizeof(Buffer));
				strcat(Buffer, "LA");
			}
			snprintf(Subcarrier, sizeof(Subcarrier), "%s - %s", Metadata.Perks[C1].Name, Buffer);
			SDL_Texture* Carrier = Render_Text(F_Subtext, Subcarrier, Colors.Abyss_Black);
			SDL_FRect Rect = {
				fmaxf((Initial.w * 0.5f) + Initial.x - (Carrier->w * 0.5f), ktn_fscale(20)),
				ktn_fscale(10) + Initial.y + Initial.h,
				Carrier->w,
				Carrier->h
			};
			Render_Texture(Carrier, &Rect);
			ktn_free_texture(Carrier);
		}
	}
}