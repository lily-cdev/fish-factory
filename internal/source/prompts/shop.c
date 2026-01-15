#include <ui.h>

void Render_Shop(int X, int Y) {
	Render_Box(210, 10, 220, 340, Colors.Light_Grey, Colors.Dark_Grey);
	if (Interface.Subtab > 0) {
		if (Interface.Subtab < 9) {
			int Subcategories = intlen(Metadata.Subcategory_Positions[Interface.Subtab - 1]);
			for (int Counter = 0; Counter < Subcategories; Counter++) {
				Render_Button(&Textures.Subcategories.Data[Interface.Subtab - 1].Data[Counter], &Rects
					.Subcategories.Data[Interface.Subtab - 1].Data[Counter], Counter + 3, Colors.Cherry_Blossom);
			}
			for (int Counter = 0; Counter < intlen(Metadata.Item_Labels[Interface.Subtab - 1]); Counter++) {
				Render_Button(&Textures.Item_Labels.Data[Interface.Subtab - 1].Data[Counter], &Rects
					.Item_Labels.Data[Interface.Subtab - 1].Data[Counter], Counter + Subcategories + 3, Colors.Cherry_Blossom);
			}
		} else {
			for (int Counter = 0; Counter < intlen(Metadata.Subcontents[Interface.Subtab - 9]); Counter++) {
				Render_Button(&Textures.Subcontents.Data[Interface.Subtab - 9].Data[Counter], &Rects
					.Subcontents.Data[Interface.Subtab - 9].Data[Counter], Counter + 3, Colors.Cherry_Blossom);
			}
		}
		Render_Box(10, 10, 186, 340, Colors.Light_Grey, Colors.Dark_Grey);
		SDL_FRect Icon_Rectangle = Metadata.Machine_Rectangles[Interface.Placing_Item - 1];
		double Multiplier = ((double)120 * Settings.Screen_Size) / Icon_Rectangle.w;
		Icon_Rectangle = (SDL_FRect){
			(Settings.Screen_Size * 103) - (Icon_Rectangle.w * 0.5),
			(Settings.Screen_Size * 24),
			(int)(Icon_Rectangle.w * Multiplier),
			(int)(Icon_Rectangle.h * Multiplier)
		};
		int Offset = (Icon_Rectangle.y + Icon_Rectangle.h) / Settings.Screen_Size;
		Render_Box((Icon_Rectangle.x / Settings.Screen_Size) - 4, (Icon_Rectangle.y / Settings.Screen_Size) - 4,
			(Icon_Rectangle.w / Settings.Screen_Size) + 8, (Icon_Rectangle.h / Settings.Screen_Size) + 8,
			Colors.Light_Grey, Colors.Dark_Grey);
		Render_Texture(Metadata.Machine_Sprites[Interface.Placing_Item - 1], &Icon_Rectangle);
		int Quirk_Stack[LDE_QUIRKS + 1];
		int Index = 0;
		for (int Counter = 0; Counter < LDE_QUIRKS; Counter++) {
			if (Metadata.Machine_Quirks[Interface.Placing_Item - 1][Counter]) {
				Quirk_Stack[Index] = Counter;
				Index++;
			}
		}
		Quirk_Stack[Index] = LDE_TERMINATOR;
		SDL_FRect Label_Rects[3] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
		float Start = (float)((Settings.Screen_Size * 103) - (((intlen(Quirk_Stack) * Settings.Screen_Size * 20) +
			((intlen(Quirk_Stack) - 1) * Settings.Screen_Size * 10)) * 0.5));
		for (int Counter = 0; Counter < intlen(Quirk_Stack); Counter++) {
			SDL_FRect Quirk_Rectangle = {
				(Counter * Settings.Screen_Size * 30) + Start,
				(float)(Offset + 16) * Settings.Screen_Size,
				Settings.Screen_Size * 20.0f,
				Settings.Screen_Size * 20.0f
			};
			Render_Texture(Textures.Quirk.Data[Quirk_Stack[Counter]], &Quirk_Rectangle);
			if (Detect_Mouse_Collision(Quirk_Rectangle)) {
				SDL_GetTextureSize(Textures.Quirk_Label.Data[Quirk_Stack[Counter]], &Label_Rects[Counter].w,
					&Label_Rects[Counter].h);
				Label_Rects[Counter].x = (Settings.Screen_Size * 10) + Quirk_Rectangle.x - (Label_Rects[Counter].w * 0.5);
				Label_Rects[Counter].y = (Settings.Screen_Size * 24) + Quirk_Rectangle.y;
			}
		}
		if (intlen(Quirk_Stack) > 0) {
			Offset += 32;
		}
		SDL_Surface* Name_Surface = TTF_RenderText_Blended(Fonts.Halftext_Font, Metadata.Names[Interface.Placing_Item - 1], 0,
			Colors.Abyss_Black);
		SDL_Texture* Name_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Name_Surface);
		SDL_FRect Name_Rectangle = {
			(float)(Settings.Screen_Size * 103) - (Name_Surface->w * 0.5),
			(float)(Offset + 10) * Settings.Screen_Size,
			(float)(Name_Surface->w),
			(float)(Name_Surface->h)
		};
		Render_Texture(Name_Texture, &Name_Rectangle);
		SDL_DestroySurface(Name_Surface);
		free_texture(Name_Texture);
		SDL_Surface* Carrying_Surface = TTF_RenderText_Blended_Wrapped(Fonts.Subtext_Font, Metadata.Descriptions[
			Interface.Placing_Item - 1], 0, Colors.Abyss_Black, Settings.Screen_Size * 180);
		SDL_FRect Description_Rectangle = {
			Settings.Screen_Size * 16.0f,
			(Offset + 40.0f) * Settings.Screen_Size,
			(float)(Carrying_Surface->w),
			(float)(Carrying_Surface->h)
		};
		SDL_Texture* Description_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Carrying_Surface);
		Render_Texture(Description_Texture, &Description_Rectangle);
		SDL_DestroySurface(Carrying_Surface);
		free_texture(Description_Texture);
		for (int Counter = 0; Counter < intlen(Quirk_Stack); Counter++) {
			Set_Renderer_Color(Colors.Light_Grey);
			SDL_FRect Temporary_Rectangle = Buffer_Rectangle(Label_Rects[Counter], 4, 1);
			SDL_RenderFillRect(Core.Renderer, &Temporary_Rectangle);
			Clear_Renderer();
			Render_Texture(Textures.Quirk_Label.Data[Quirk_Stack[Counter]], &Label_Rects[Counter]);
		}
		Render_Box(444, 10, 186, 340, Colors.Light_Grey, Colors.Dark_Grey);
		Render_Texture(Textures.Price_Header, &Rects.Price_Header);
		char Buffer[64];
		snprintf(Buffer, sizeof(Buffer), "Base: %iLA", Metadata.Machine_Prices[Interface.Placing_Item - 1]);
		Process_Supply(&Supplies.Shop1, Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, 456, 30);
		snprintf(Buffer, sizeof(Buffer), "Tax: %iLA", (int)(Metadata.Machine_Prices[Interface.Placing_Item - 1] * 0.1));
		Process_Supply(&Supplies.Shop2, Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, 456, 50);
		snprintf(Buffer, sizeof(Buffer), "Shipping Fee: %iLA", Metadata.Machine_Taxes[Interface.Placing_Item - 1]);
		Process_Supply(&Supplies.Shop3, Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, 456, 70);
		snprintf(Buffer, sizeof(Buffer), "Processing Fee: %iLA", 1);//tmp
		Process_Supply(&Supplies.Shop4, Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, 456, 90);
		Cache_Price();
		snprintf(Buffer, sizeof(Buffer), "Total: %iLA", Interface.Queried_Price);
		Process_Supply(&Supplies.Shop5, Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, 456, 110);
	} else {
		for (int Counter = 0; Counter < LDE_CATEGORIES; Counter++) {
			Render_Button(&Textures.Categories.Data[Counter], &Rects.Categories.Data[Counter], Counter + 3,
				Colors.Cherry_Blossom);
		}
	}
}