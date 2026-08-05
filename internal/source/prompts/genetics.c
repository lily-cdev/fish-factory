#include <ui.h>

void Render_Genetics(Point Pos) {
	Render_Box((Point){ 10, 10 }, 620, 340, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Texture(Textures.Genetics_Content, &Rects.Genetics_Content);
	/*for (int C1 = 0; C1 < Core.Genes; C1++) {
		SDL_FRect Bounding = { ktn_fscale(((ktn_tile_size + 12) * C1) + 120), ktn_fscale(50), ktn_fscale(ktn_tile_size), ktn_fscale(
			ktn_tile_size) };
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
			SDL_Texture* Text = Render_Text(F_Subtext, Metadata.Genes[C1].Name, Colors.Abyss_Black);
			Render_Texture(Text, &(SDL_FRect){
				(Bounding.w * 0.5f) - (Text->w * 0.5f) + Bounding.x,
				Bounding.y + Bounding.h + ktn_fscale(5),
				Text->w,
				Text->h
			});
			Render_Texture(Textures.Gene_Add, &Subcarrier);
			ktn_free_texture(Text);
		} else {
			Render_Texture(Metadata.Genes[C1].Icon, &Subcarrier);
		}
	}*/ 
}