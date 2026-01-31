#include <ui.h>

void Render_Keybinds() {
    for (int Counter1 = 0; Counter1 < LDE_KEYBINDS; Counter1++) {
		char Text[64];
		snprintf(Text, sizeof(Text), "%s...", Keybinds.Keybind_Texts[Counter1]);
		SDL_Surface* Prefix_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Text, 0, Colors.Abyss_Black);
		SDL_Texture* Prefix_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Prefix_Surface);
		SDL_FRect Prefix_Rectangle = {
			Settings.Screen_Size * 370.0f,
			(float)((Counter1 * 16) + 40) * Settings.Screen_Size,
			(float)(Prefix_Surface->w),
			(float)(Prefix_Surface->h)
		};
		Render_Texture(Prefix_Texture, &Prefix_Rectangle);
		if (Interface.Registering_Keybind == Counter1) {
			SDL_Surface* Registering_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, "...", 0, Colors.Abyss_Black);
			SDL_Texture* Registering_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Registering_Surface);
			SDL_FRect Registering_Rectangle = {
				Prefix_Rectangle.x + Prefix_Rectangle.w + 20,
				Prefix_Rectangle.y,
				(float)(Registering_Surface->w),
				(float)(Registering_Surface->h)
			};
			Render_Texture(Registering_Texture, &Registering_Rectangle);
			SDL_DestroySurface(Registering_Surface);
			free_texture(Registering_Texture);
		} else {
			char Subcore[32];
			strcpy(Subcore, SDL_GetKeyName(Keybinds.Keybind_Settings[Counter1]));
			for (int Counter2 = 0; Counter2 < strlen(Subcore); Counter2++) {
				Subcore[Counter2] = (char)(tolower(Subcore[Counter2]));
			}
			SDL_Surface* Deadbutton_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Subcore, 0, Colors.Abyss_Black);
			SDL_Texture* Deadbutton_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Deadbutton_Surface);
			SDL_FRect Deadbutton_Rectangle = {
				Prefix_Rectangle.x + Prefix_Rectangle.w + 20,
				Prefix_Rectangle.y,
				(float)(Deadbutton_Surface->w),
				(float)(Deadbutton_Surface->h)
			};
			if (Detect_Mouse_Collision(Deadbutton_Rectangle)) {
				Interface.UI_Selection = Counter1 + 6;
				char Alivebutton_Text[64];
				snprintf(Alivebutton_Text, sizeof(Alivebutton_Text), "> %s <", Subcore);
				SDL_Surface* Alivebutton_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Alivebutton_Text, 0,
					Colors.Cherry_Blossom);
				SDL_Texture* Alivebutton_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Alivebutton_Surface);
				SDL_Surface* Temporary_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, "> ", 0, Colors.Cherry_Blossom);
				int Offset = Temporary_Surface->w;
				SDL_DestroySurface(Temporary_Surface);
				SDL_FRect Alivebutton_Rectangle = {
					Deadbutton_Rectangle.x - Offset,
					Deadbutton_Rectangle.y,
					(float)(Alivebutton_Surface->w),
					(float)(Alivebutton_Surface->h)
				};
				Render_Texture(Alivebutton_Texture, &Alivebutton_Rectangle);
				SDL_FRect Underline_Rectangle = {
					Deadbutton_Rectangle.x,
					Deadbutton_Rectangle.y +
					Deadbutton_Rectangle.h + 2,
					Deadbutton_Rectangle.w,
					Deadbutton_Rectangle.h * 0.1f
				};
				SDL_SetRenderDrawColor(Core.Renderer, Colors.Cherry_Blossom.r, Colors.Cherry_Blossom.g,
					Colors.Cherry_Blossom.b, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(Core.Renderer, &Underline_Rectangle);
				Clear_Renderer();
				SDL_DestroySurface(Alivebutton_Surface);
				free_texture(Alivebutton_Texture);
			} else {
				Render_Texture(Deadbutton_Texture, &Deadbutton_Rectangle);
			}
			SDL_DestroySurface(Deadbutton_Surface);
			free_texture(Deadbutton_Texture);
		}
		SDL_DestroySurface(Prefix_Surface);
		free_texture(Prefix_Texture);
	}
}

void Render_Settings() {
	for (int Counter = 0; Counter < Textures.Settings_Label.Length; Counter++) {
		Render_Texture(Textures.Settings_Label.Data[Counter], &Rects.Settings_Label.Data[Counter]);
	}
	Render_Button(&Textures.Return, &Rects.Return, 1, Colors.Cherry_Blossom);
	Render_Slider(Interface.Slider_Texts[0], 1, 5, 4, &Interface.Slider_Positions[0], 50, 70, 220, Colors.Abyss_Black,
		Colors.Cherry_Blossom, true);
	Render_Slider(Interface.Slider_Texts[4], 2, 4, 20, &Interface.Slider_Positions[4], 50, 140, 220, Colors.Abyss_Black,
		Colors.Cherry_Blossom, true);
	Render_Slider(Interface.Slider_Texts[5], 3, 100, 21, &Interface.Slider_Positions[5], 50, 210, 220, Colors.Abyss_Black,
		Colors.Cherry_Blossom, true);
	Render_Slider(Interface.Slider_Texts[6], 4, 2, 22, &Interface.Slider_Positions[6], 50, 280, 220, Colors.Abyss_Black,
		Colors.Cherry_Blossom, true);
	if (Settings.AA_Temporary) {
		Render_Button(&Textures.Anti_Aliasing.Data[0], &Rects.Anti_Aliasing.Data[0], 5, Colors.Cherry_Blossom);
	} else {
		Render_Button(&Textures.Anti_Aliasing.Data[1], &Rects.Anti_Aliasing.Data[1], 5, Colors.Cherry_Blossom);
	}
	if (Settings.VS_Temporary) {
		Render_Button(&Textures.V_Sync.Data[1], &Rects.V_Sync.Data[1], 24, Colors.Cherry_Blossom);
	} else {
		Render_Button(&Textures.V_Sync.Data[0], &Rects.V_Sync.Data[0], 24, Colors.Cherry_Blossom);
	}
	if (Temporary.Settings_Changed) {
		Render_Button(&Textures.Save_Settings, &Rects.Save_Settings, 23, Colors.Cherry_Blossom);
	}
	Process_Supply(&Supplies.Monitor_Size, Metadata.Monitor_Size, Fonts.Subtext_Font, Colors.Abyss_Black, 50, 40);
	Render_Keybinds();
	Verify_Settings();
}