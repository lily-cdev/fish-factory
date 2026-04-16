#include <ui.h>

void Render_Shop(Point Pos) {
	Render_Box((Point){ 210, 10 }, 220, 340, Colors.Light_Grey, Colors.Dark_Grey);
	if (Interface.Subtab > 0) {
		if (Interface.Subtab <= LDE_CATEGORIES) {
			int Subcategories = intlen(Metadata.Subcategory_Positions[Interface.Subtab - 1]);
			for (int C1 = 0; C1 < Subcategories; C1++) {
				Render_Button(&Textures.Subcategories.Data[Interface.Subtab - 1].Data[C1], &Rects.Subcategories.Data[
					Interface.Subtab - 1].Data[C1], (UI_Link){ Shop_Subcategory, .Param.Integer = C1 }, Colors.Cherry_Blossom);
			}
			for (int C1 = 0; C1 < intlen(Metadata.Item_Labels[Interface.Subtab - 1]); C1++) {
				Render_Button(&Textures.Item_Labels.Data[Interface.Subtab - 1].Data[C1], &Rects.Item_Labels.Data[
					Interface.Subtab - 1].Data[C1], (UI_Link){ Shop_Subitem, .Param.Integer = C1 }, Colors.Cherry_Blossom);
			}
		} else {
			for (int C1 = 0; C1 < intlen(Metadata.Subcontents[Interface.Subtab - LDE_CATEGORIES - 1]); C1++) {
				Render_Button(&Textures.Subcontents.Data[Interface.Subtab - LDE_CATEGORIES - 1].Data[C1], &Rects.Subcontents.Data[
					Interface.Subtab - LDE_CATEGORIES - 1].Data[C1], (UI_Link){ Shop_Item, .Param.Integer = C1},
					Colors.Cherry_Blossom);
			}
		}
		Render_Box((Point){ 10, 10 }, 186, 340, Colors.Light_Grey, Colors.Dark_Grey);
		SDL_FRect Icon_Rectangle = Metadata.Machine_Rects[Interface.Item - 1];
		float Multiplier = (Settings.Scalar * 120.0f) / Icon_Rectangle.w;
		Icon_Rectangle = (SDL_FRect){
			(Settings.Scalar * 103.0f) - (Icon_Rectangle.w * Multiplier * 0.5f),
			Settings.Scalar * 24.0f,
			Icon_Rectangle.w * Multiplier,
			Icon_Rectangle.h * Multiplier
		};
		int Offset = (Icon_Rectangle.y + Icon_Rectangle.h) / Settings.Scalar;
		Render_Box((Point){ ((int)Icon_Rectangle.x / Settings.Scalar) - 4, (Icon_Rectangle.y / Settings.Scalar) - 4 },
			(Icon_Rectangle.w / Settings.Scalar) + 8, (Icon_Rectangle.h / Settings.Scalar) + 8, Colors.Light_Grey,
			Colors.Dark_Grey);
		Render_Texture(Metadata.Machines[Interface.Item - 1].Icon, &Icon_Rectangle);
		int Quirk_Stack[LDE_QUIRKS + 1];
		int Index = 0;
		for (int C1 = 0; C1 < LDE_QUIRKS; C1++) {
			if (Metadata.Machines[Interface.Item - 1].Quirks[C1]) {
				Quirk_Stack[Index] = C1;
				Index++;
			}
		}
		Quirk_Stack[Index] = LDE_TERMINATOR;
		SDL_FRect Label_Rects[3] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
		float Start = (float)((Settings.Scalar * 103) - (((intlen(Quirk_Stack) * Settings.Scalar * 20) + ((intlen(Quirk_Stack) -
			1) * Settings.Scalar * 10)) * 0.5));
		for (int C1 = 0; C1 < intlen(Quirk_Stack); C1++) {
			SDL_FRect Quirk_Rectangle = {
				(C1 * Settings.Scalar * 30) + Start,
				(float)(Offset + 16) * Settings.Scalar,
				Settings.Scalar * 20.0f,
				Settings.Scalar * 20.0f
			};
			Render_Texture(Textures.Quirk.Data[Quirk_Stack[C1]], &Quirk_Rectangle);
			if (Detect_Mouse_Collision(Quirk_Rectangle)) {
				SDL_GetTextureSize(Textures.Quirk_Label.Data[Quirk_Stack[C1]], &Label_Rects[C1].w, &Label_Rects[C1].h);
				Label_Rects[C1].x = (Settings.Scalar * 10) + Quirk_Rectangle.x - (Label_Rects[C1].w * 0.5);
				Label_Rects[C1].y = (Settings.Scalar * 24) + Quirk_Rectangle.y;
			}
		}
		if (intlen(Quirk_Stack) > 0) {
			Offset += 32;
		}
		SDL_Texture* Name_Texture = Render_Text(F_Halftext, Metadata.Machines[Interface.Item - 1].Name, Colors.Abyss_Black);
		SDL_FRect Name_Rectangle = {
			(float)(Settings.Scalar * 103) - (Name_Texture->w * 0.5),
			(float)(Offset + 10) * Settings.Scalar,
			(float)Name_Texture->w,
			(float)Name_Texture->h
		};
		Render_Texture(Name_Texture, &Name_Rectangle);
		free_texture(Name_Texture);
		SDL_Texture* Description_Texture = Render_Text(F_Subtext, Metadata.Descriptions[Interface.Item - 1], Colors.Abyss_Black);
		SDL_FRect Description_Rectangle = {
			Settings.Scalar * 16.0f,
			(Offset + 40.0f) * Settings.Scalar,
			(float)Description_Texture->w,
			(float)Description_Texture->h
		};
		Render_Texture(Description_Texture, &Description_Rectangle);
		free_texture(Description_Texture);
		for (int C1 = 0; C1 < intlen(Quirk_Stack); C1++) {
			Set_Renderer_Color(Colors.Light_Grey);
			SDL_FRect Temporary_Rectangle = Buffer_Rectangle(Label_Rects[C1], (Point){ 4, 1 });
			SDL_RenderFillRect(Core.Renderer, &Temporary_Rectangle);
			Clear_Renderer();
			Render_Texture(Textures.Quirk_Label.Data[Quirk_Stack[C1]], &Label_Rects[C1]);
		}
		Render_Box((Point){ 444, 10 }, 186, 340, Colors.Light_Grey, Colors.Dark_Grey);
		Render_Texture(Textures.Price_Header, &Rects.Price_Header);
		char Buffer[64];
		snprintf(Buffer, sizeof(Buffer), "base: %iLA", Metadata.Machines[Interface.Item - 1].Price);
		Process_Supply(&Supplies.Shop1, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ 456, 30 });
		snprintf(Buffer, sizeof(Buffer), "tax: %iLA", (int)(Metadata.Machines[Interface.Item - 1].Price * 0.1f));
		Process_Supply(&Supplies.Shop2, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ 456, 50 });
		snprintf(Buffer, sizeof(Buffer), "shipping fee: %iLA", Metadata.Machines[Interface.Item - 1].Fee);
		Process_Supply(&Supplies.Shop3, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ 456, 70 });
		snprintf(Buffer, sizeof(Buffer), "processing fee: %iLA", 1);//tmp
		Process_Supply(&Supplies.Shop4, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ 456, 90 });
		Cache_Price();
		snprintf(Buffer, sizeof(Buffer), "total: %iLA", Interface.Queried_Price);
		Process_Supply(&Supplies.Shop5, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ 456, 110 });
	} else {
		for (int C1 = 0; C1 < LDE_CATEGORIES; C1++) {
			Render_Button(&Textures.Categories.Data[C1], &Rects.Categories.Data[C1], (UI_Link){ Shop_Category,
				.Param.Integer = C1 }, Colors.Cherry_Blossom);
		}
	}
}