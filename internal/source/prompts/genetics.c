#include <ui.h>

void Render_Genetics(Point Pos) {
	Render_Box((Point){ 10, 10 }, 620, 340, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Texture(Textures.Genetics_Content, &Rects.Genetics_Content);
	/*for (int C1 = 0; C1 < Core.Genes; C1++) {
		SDL_FRect Bounding = { ktn_fscale((C1 * 52) + 120), ktn_fscale(50), ktn_fscale(40), ktn_fscale(40) };
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
		if (Detect_Mouse_Collision(Initial)) {
			Interface.UI_Query = (UI_Link){ .Carrier = Set_Gene, .Param.Integer = C1 };
			char Carrier[4][128];
			snprintf(Carrier[0], sizeof(Carrier[0]), "%s - %ipt", Metadata.Genes[C1].Name, Metadata.Genes[C1].Cost);
			snprintf(Carrier[1], sizeof(Carrier[1]), "x%i%% food consumption", (int)(Metadata.Genes[C1].Consumption * 100));
			snprintf(Carrier[2], sizeof(Carrier[2]), "x%i%% req. volume", (int)(Metadata.Genes[C1].Space * 100));
			snprintf(Carrier[3], sizeof(Carrier[3]), "x%i%% growth rate", (int)(Metadata.Genes[C1].Rate * 100));
			for (int C2 = 0; C2 < 4; C2++) {
				SDL_Texture* Text = Render_Text(F_Subtext, Carrier[C2], Colors.Abyss_Black);
				Render_Texture(Text, &(SDL_FRect){
					(Bounding.w * 0.5f) - (Text->w * 0.5f) + Bounding.x,
					Bounding.y + Bounding.h + ktn_fscale((C2 * 15) + 5),
					Text->w,
					Text->h
				});
				ktn_free_texture(Text);
			}
		}
		Render_Texture((Metadata.Fish[Interface.Slider_Positions[16]].Genes[C1]) ? Textures.Gene_Added : Metadata.Genes[C1].Icon, &Subcarrier);
	}
	Render_Slider(16, 1, Core.Fishes - 1, (Point){ 130, 300 }, 380, Colors.Abyss_Black, Colors.Cherry_Blossom, true);*/
}