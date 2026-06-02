#include <ui.h>

void Render_Shop(Point Pos) {
	Render_Box((Point){ 210, 10 }, 220, 340, Colors.Light_Grey, Colors.Dark_Grey);
	if (Interface.Subtab > 0) {
		if (Interface.Subtab <= ktn_categories) {
			int Subcategories = ktn_intlen(Metadata.Subcategory_Positions[Interface.Subtab - 1]);
			for (int C1 = 0; C1 < Subcategories; C1++) {
				Render_Button(&Textures.Subcategories.Data[Interface.Subtab - 1].Data[C1], &Rects.Subcategories.Data[
					Interface.Subtab - 1].Data[C1], (UI_Link){ Shop_Subcategory, .Param.Integer = C1 }, Colors.Cherry_Blossom);
			}
			for (int C1 = 0; C1 < ktn_veclen(Metadata.Item_Labels[Interface.Subtab - 1]); C1++) {
				Temporary.Tutorial_Buffer = C1;
				Render_Button(&Textures.Item_Labels.Data[Interface.Subtab - 1].Data[C1], &Rects.Item_Labels.Data[
					Interface.Subtab - 1].Data[C1], (UI_Link){ Shop_Subitem, .Param.Integer = C1 }, Colors.Cherry_Blossom);
			}
		} else {
			for (int C1 = 0; C1 < ktn_veclen(Metadata.Subcontents[Interface.Subtab - ktn_categories - 1]); C1++) {
				Render_Button(&Textures.Subcontents.Data[Interface.Subtab - ktn_categories - 1].Data[C1], &Rects.Subcontents.Data[
					Interface.Subtab - ktn_categories - 1].Data[C1], (UI_Link){ Shop_Item, .Param.Integer = C1 },
					Colors.Cherry_Blossom);
			}
		}
		Render_Box((Point){ 10, 10 }, 186, 340, Colors.Light_Grey, Colors.Dark_Grey);
		SDL_FRect Icon_Rectangle = Interface.Item->Rect;
		float Multiplier = ktn_fscale(120.0f) / Icon_Rectangle.w;
		Icon_Rectangle = (SDL_FRect){
			ktn_fscale(103.0f) - (Icon_Rectangle.w * Multiplier * 0.5f),
			ktn_fscale(24.0f),
			Icon_Rectangle.w * Multiplier,
			Icon_Rectangle.h * Multiplier
		};
		int Offset = (Icon_Rectangle.y + Icon_Rectangle.h) / Settings.Scalar;
		Render_Box((Point){ ((int)Icon_Rectangle.x / Settings.Scalar) - 4, (Icon_Rectangle.y / Settings.Scalar) - 4 },
			(Icon_Rectangle.w / Settings.Scalar) + 8, (Icon_Rectangle.h / Settings.Scalar) + 8, Colors.Light_Grey,
			Colors.Dark_Grey);
		Render_Texture(Interface.Item->Icon, &Icon_Rectangle);
		int Quirk_Stack[ktn_quirks + 1];
		int Index = 0;
		for (int C1 = 0; C1 < ktn_quirks; C1++) {
			if (Interface.Item->Quirks[C1]) {
				Quirk_Stack[Index] = C1;
				Index++;
			}
		}
		Quirk_Stack[Index] = ktn_terminator;
		SDL_FRect Label_Rects[3] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
		float Start = (float)(ktn_fscale(103.0f) - ((ktn_fscale(ktn_intlen(Quirk_Stack) * 20.0f) + (ktn_fscale(ktn_intlen(Quirk_Stack) - 1.0f) *
			10.0f)) * 0.5f));
		for (int C1 = 0; C1 < ktn_intlen(Quirk_Stack); C1++) {
			SDL_FRect Quirk_Rectangle = {
				ktn_fscale(C1 * 30.0f) + Start,
				ktn_fscale(Offset + 16.0f),
				ktn_fscale(20.0f),
				ktn_fscale(20.0f)
			};
			Render_Texture(Textures.Quirk.Data[Quirk_Stack[C1]], &Quirk_Rectangle);
			if (Detect_Mouse_Collision(Quirk_Rectangle)) {
				SDL_GetTextureSize(Textures.Quirk_Label.Data[Quirk_Stack[C1]], &Label_Rects[C1].w, &Label_Rects[C1].h);
				Label_Rects[C1].x = ktn_fscale(10.0f) + Quirk_Rectangle.x - (Label_Rects[C1].w * 0.5f);
				Label_Rects[C1].y = ktn_fscale(24.0f) + Quirk_Rectangle.y;
			}
		}
		if (ktn_intlen(Quirk_Stack) > 0) {
			Offset += 32;
		}
		SDL_Texture* Name_Texture = Render_Text(F_Halftext, Interface.Item->Name, Colors.Abyss_Black);
		SDL_FRect Name_Rectangle = {
			ktn_fscale(103.0f) - (Name_Texture->w * 0.5f),
			ktn_fscale(Offset + 10.0f),
			(float)Name_Texture->w,
			(float)Name_Texture->h
		};
		Render_Texture(Name_Texture, &Name_Rectangle);
		ktn_free_texture(Name_Texture);
		SDL_Surface* Desc_Surface = TTF_RenderText_Blended_Wrapped(Fonts.Faces[F_Subtext], Interface.Item->Desc, 0,
			Colors.Abyss_Black, ktn_fscale(180));
		SDL_Texture* Desc_Texture = Surface_To_Texture(Desc_Surface);
		SDL_FRect Desc_Rect = { ktn_fscale(16.0f), ktn_fscale(Offset + 40.0f), (float)Desc_Texture->w, (float)Desc_Texture->h };
		Render_Texture(Desc_Texture, &Desc_Rect);
		SDL_DestroySurface(Desc_Surface);
		ktn_free_texture(Desc_Texture);
		for (int C1 = 0; C1 < ktn_intlen(Quirk_Stack); C1++) {
			Set_Renderer_Color(Colors.Light_Grey);
			SDL_FRect Temporary_Rectangle = Buffer_Rectangle(Label_Rects[C1], (Point){ 4, 1 });
			SDL_RenderFillRect(Core.Renderer, &Temporary_Rectangle);
			Clear_Renderer();
			Render_Texture(Textures.Quirk_Label.Data[Quirk_Stack[C1]], &Label_Rects[C1]);
		}
		Render_Box((Point){ 444, 10 }, 186, 340, Colors.Light_Grey, Colors.Dark_Grey);
		Render_Texture(Textures.Price_Header, &Rects.Price_Header);
		char Buffer[64];
		snprintf(Buffer, sizeof(Buffer), "base: %iLA", Interface.Item->Price);
		Process_Supply(&Supplies.Shop1, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ 456, 30 });
		snprintf(Buffer, sizeof(Buffer), "tax: %iLA", (int)(Interface.Item->Price * 0.1f));
		Process_Supply(&Supplies.Shop2, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ 456, 50 });
		snprintf(Buffer, sizeof(Buffer), "shipping fee: %iLA", Interface.Item->Fee);
		Process_Supply(&Supplies.Shop3, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ 456, 70 });
		snprintf(Buffer, sizeof(Buffer), "processing fee: %iLA", 1);//tmp
		Process_Supply(&Supplies.Shop4, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ 456, 90 });
		Cache_Price();
		snprintf(Buffer, sizeof(Buffer), "total: %iLA", Interface.Queried_Price);
		Process_Supply(&Supplies.Shop5, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ 456, 110 });
	} else {
		for (int C1 = 0; C1 < ktn_categories; C1++) {
			Temporary.Tutorial_Buffer = C1;
			Render_Button(&Textures.Categories.Data[C1], &Rects.Categories.Data[C1], (UI_Link){ Shop_Category,
				.Param.Integer = C1 }, Colors.Cherry_Blossom);
		}
	}
}