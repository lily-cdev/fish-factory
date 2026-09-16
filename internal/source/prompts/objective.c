#include <ui.h>

void Render_Objective(Point Pos) {
	Render_Box((Point){ 10, 10 }, 620, 340, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Texture(Textures.Objective_Content, &Rects.Objective_Content);
	if (Data.Objective_Placed) {
		for (int C1 = 0; C1 < Data.Objective_Ct[Data.Objective_Phase]; C1++) {
			SDL_FRect Background = {
				ktn_fscale(40.0f),
				ktn_fscale((C1 * 44) + 70.0f),
				ktn_fscale(560),
				ktn_fscale(24.0f)
			};
			Set_Renderer_Color(Colors.Cherry_Blossom);
			SDL_RenderFillRect(Core.Renderer, &Background);
			SDL_FRect Item_Subrect = {
				ktn_fscale(40.0f),
				ktn_fscale((C1 * 44) + 70.0f),
				ktn_fscale((Data.Objective_Progress[C1] / Data.Objective_Amounts[Data.Objective_Phase][C1]) * 560),
				ktn_fscale(24.0f)
			};
			Set_Renderer_Color(Colors.Carnage_Pink);
			SDL_RenderFillRect(Core.Renderer, &Item_Subrect);
			Clear_Renderer();
			SDL_FRect Item_Rect = {
				ktn_fscale(42.0f),
				ktn_fscale((C1 * 44) + 72.0f),
				ktn_fscale(20.0f),
				ktn_fscale(20.0f)
			};
			Item_Ptr Subitem = Get_Item(Data.Objectives[Data.Objective_Phase][C1]);
			Render_Texture(Subitem->Icon, &Item_Rect);
			char Buffer[128] = "complete";
			if (Data.Objective_Progress[C1] < Data.Objective_Amounts[Data.Objective_Phase][C1] - ktn_epsilon) {
				snprintf(Buffer, sizeof(Buffer), "%s - %.2fkg needed", Subitem->Name, Data.Objective_Amounts[Data.Objective_Phase][C1] - Data.Objective_Progress[C1]);
			}
			SDL_Texture* Carrier = Render_Text(F_Text, Buffer, Colors.Abyss_Black);
			SDL_FRect Text_Rect = { ktn_fscale(72.0f), 0, Carrier->w, Carrier->h };
			Text_Rect.y = ktn_fscale((C1 * 44) - (Carrier->h / Settings.Scalar * 0.5f) + 82.0f);
			Render_Texture(Carrier, &Text_Rect);
			ktn_free_texture(Carrier);
		}
	} else {
		SDL_Texture* Carrier = Render_Text(F_Text, "drydock intake must be placed!", Colors.Abyss_Black);
		SDL_FRect Text_Rect = {
			ktn_fscale(320) - (Carrier->w * 0.5f),
			ktn_fscale(70),
			Carrier->w,
			Carrier->h
		};
		Render_Texture(Carrier, &Text_Rect);
		ktn_free_texture(Carrier);
	}
}