#include <Legacy_UI.hpp>

void Render_Shop(int X, int Y) {
	Render_Box(210, 10, 220, 340, Colors.Light_Grey, Colors.Dark_Grey);
	if (Interface.Subtab > 0) {
		if (Interface.Subtab < 9) {
			int Subcategories = intlen(Metadata.Subcategory_Positions[Interface.Subtab - 1]);
			for (int Counter = 0; Counter < Subcategories; Counter++) {
				Render_Button(Textures.Subcategories.Data[Interface.Subtab - 1].Data[Counter], Rects
					.Subcategories.Data[Interface.Subtab - 1].Data[Counter],
					Counter + 3, Colors.Cherry_Blossom);
			}
			for (int Counter = 0; Counter < intlen(Metadata.Item_Labels[Interface.Subtab - 1]); Counter++) {
				Render_Button(Textures.Item_Labels.Data[Interface.Subtab - 1].Data[Counter], Rects
					.Item_Labels.Data[Interface.Subtab - 1].Data[Counter],
					Counter + Subcategories + 3, Colors.Cherry_Blossom);
			}
		} else {
			for (int Counter = 0; Counter < intlen(Metadata.Subcontents[
				Interface.Subtab - 9]); Counter++) {
				Render_Button(Textures.Subcontents.Data[Interface.Subtab - 9].Data[Counter], Rects
					.Subcontents.Data[Interface.Subtab - 9].Data[Counter], Counter + 3, Colors.Cherry_Blossom);
			}
		}
		Render_Box(10, 10, 186, 340, Colors.Light_Grey, Colors.Dark_Grey);
		SDL_FRect Icon_Rectangle = Metadata.Machine_Rectangles[Interface.Placing_Item - 1];
		double Multiplier = ((double)120 * Settings.Screen_Size) / Icon_Rectangle.w;
		Icon_Rectangle.w = static_cast<int>(Icon_Rectangle.w * Multiplier);
		Icon_Rectangle.h = static_cast<int>(Icon_Rectangle.h * Multiplier);
		Icon_Rectangle.x = (103 * Settings.Screen_Size) - (Icon_Rectangle.w / 2);
		Icon_Rectangle.y = (24 * Settings.Screen_Size);
		int Offset = (Icon_Rectangle.y + Icon_Rectangle.h) / Settings.Screen_Size;
		Render_Box((Icon_Rectangle.x / Settings.Screen_Size) - 4,
			(Icon_Rectangle.y / Settings.Screen_Size) - 4,
			(Icon_Rectangle.w / Settings.Screen_Size) + 8,
			(Icon_Rectangle.h / Settings.Screen_Size) + 8,
			Colors.Light_Grey, Colors.Dark_Grey);
		SDL_RenderTexture(Core.Renderer, Metadata.Machine_Sprites[Interface.Placing_Item - 1], NULL, &Icon_Rectangle);
		std::vector<int> Quirk_Stack = { };
		for (int Counter = 0; Counter < 4; Counter++) {
			if (Metadata.Machine_Quirks[Interface.Placing_Item - 1][Counter]) {
				Quirk_Stack.push_back(Counter);
			}
		}
		std::vector<SDL_FRect> Label_Rectangles = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
		float Start = static_cast<float>((103 * Settings.Screen_Size) - (((20 * Quirk_Stack.size() *
			Settings.Screen_Size) + (10 * (Quirk_Stack.size() - 1) * Settings.Screen_Size)) / 2));
		for (int Counter = 0; Counter < Quirk_Stack.size(); Counter++) {
			SDL_FRect Quirk_Rectangle = { Start + (30 * Counter * Settings.Screen_Size),
				static_cast<float>(16 + Offset) * Settings.Screen_Size, 20.0f *
				Settings.Screen_Size, 20.0f * Settings.Screen_Size };
			SDL_RenderTexture(Core.Renderer, Textures
				.Quirk.Data[Quirk_Stack[Counter]], NULL, &Quirk_Rectangle);
			if (Detect_Mouse_Collision(Quirk_Rectangle)) {
				SDL_GetTextureSize(Textures.Quirk_Label.Data[Quirk_Stack[Counter]],
					&Label_Rectangles[Counter].w, &Label_Rectangles[Counter].h);
				Label_Rectangles[Counter].x = Quirk_Rectangle.x + (10 * Settings.Screen_Size) -
					(Label_Rectangles[Counter].w / 2);
				Label_Rectangles[Counter].y = Quirk_Rectangle.y + (24 * Settings.Screen_Size);
			}
		}
		if (Quirk_Stack.size() > 0) {
			Offset += 32;
		}
		SDL_Surface* Name_Surface = TTF_RenderText_Blended(Fonts.Halftext_Font, Metadata.Names[
			Interface.Placing_Item - 1], strlen(Metadata.Names[Interface.Placing_Item - 1]),
			Colors.Abyss_Black);
		SDL_Texture* Name_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Name_Surface);
		SDL_FRect Name_Rectangle = { static_cast<float>(103 * Settings.Screen_Size) - (Name_Surface->w / 2),
			static_cast<float>(10 + Offset) * Settings.Screen_Size, static_cast<float>(Name_Surface->w),
			static_cast<float>(Name_Surface->h) };
		SDL_RenderTexture(Core.Renderer, Name_Texture, NULL, &Name_Rectangle);
		SDL_DestroySurface(Name_Surface);
		SDL_DestroyTexture(Name_Texture);
		SDL_Surface* Carrying_Surface = TTF_RenderText_Blended_Wrapped(Fonts.Subtext_Font,
			Metadata.Descriptions[Interface.Placing_Item - 1],
			strlen(Metadata.Descriptions[Interface.Placing_Item - 1]),
			Colors.Abyss_Black, 180 * Settings.Screen_Size);
		SDL_FRect Description_Rectangle = { 16.0f * Settings.Screen_Size,
			(40.0f + Offset) * Settings.Screen_Size, static_cast<float>(
			Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
		SDL_Texture* Description_Texture = SDL_GenerateTextureFromSurface(
			Core.Renderer, Carrying_Surface);
		SDL_RenderTexture(Core.Renderer, Description_Texture,
			NULL, &Description_Rectangle);
		SDL_DestroySurface(Carrying_Surface);
		SDL_DestroyTexture(Description_Texture);
		SDL_FRect Comment_Rectangle = { 16.0f * Settings.Screen_Size, static_cast<float>(
			348 * Settings.Screen_Size) - Carrying_Surface->h, static_cast<float>(Carrying_Surface->w),
			static_cast<float>(Carrying_Surface->h) };
		SDL_Texture* Comment_Texture = SDL_GenerateTextureFromSurface(
			Core.Renderer, Carrying_Surface);
		SDL_RenderTexture(Core.Renderer, Comment_Texture, NULL, &Comment_Rectangle);
		SDL_DestroySurface(Carrying_Surface);
		SDL_DestroyTexture(Comment_Texture);
		for (int Counter = 0; Counter < Quirk_Stack.size(); Counter++) {
			Set_Renderer_Color(Colors.Light_Grey);
			SDL_FRect Temporary_Rectangle = Buffer_Rectangle(Label_Rectangles[Counter], 4, 1);
			SDL_RenderFillRect(Core.Renderer, &Temporary_Rectangle);
			Clear_Renderer();
			SDL_RenderTexture(Core.Renderer, Textures.Quirk_Label
				.Data[Quirk_Stack[Counter]], NULL, &Label_Rectangles[Counter]);
		}
		Render_Box(444, 10, 186, 340, Colors.Light_Grey, Colors.Dark_Grey);
		Render_Dynamic_Text(Fonts.Halftext_Font, "Price Sum:", Colors.Abyss_Black, 446, 10);
		char Buffer[64];
		snprintf(Buffer, sizeof(Buffer), "Base: %iLA", Metadata.Machine_Prices[Interface.Placing_Item - 1]);
		Render_Dynamic_Text(Fonts.Subtext_Font, Buffer, Colors.Abyss_Black, 456, 30);
		snprintf(Buffer, sizeof(Buffer), "Tax: %iLA", Metadata.Machine_Prices[Interface.Placing_Item - 1] / 10);
		Render_Dynamic_Text(Fonts.Subtext_Font, Buffer, Colors.Abyss_Black, 456, 50);
		snprintf(Buffer, sizeof(Buffer), "Shipping Fee: %iLA", Metadata.Machine_Taxes[Interface.Placing_Item - 1]);
		Render_Dynamic_Text(Fonts.Subtext_Font, Buffer, Colors.Abyss_Black, 456, 70);
		Render_Dynamic_Text(Fonts.Subtext_Font, "Processing Fee: 1LA", Colors.Abyss_Black, 456, 90);
		Cache_Price();
		snprintf(Buffer, sizeof(Buffer), "Total: %iLA", Interface.Queried_Price);
		Render_Dynamic_Text(Fonts.Subtext_Font, Buffer, Colors.Abyss_Black, 456, 110);
	} else {
		for (int Counter = 0; Counter < LDE_CATEGORIES; Counter++) {
			Render_Button(Textures.Categories.Data[Counter],
				Rects.Categories.Data[Counter],	Counter + 3, Colors.Cherry_Blossom);
		}
	}
}