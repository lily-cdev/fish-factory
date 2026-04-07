#include <ui.h>

void Render_Keybinds() {
    for (int C1 = 0; C1 < LDE_KEYBINDS; C1++) {
		char Text[64];
		snprintf(Text, sizeof(Text), "%s...", Keybinds.Keybind_Texts[C1]);
		SDL_Texture* Prefix_Texture = Render_Text(F_Subtext, Text, Colors.Abyss_Black);
		SDL_FRect Prefix_Rectangle = {
			Settings.Scalar * 370.0f,
			(float)((C1 * 16) + 40) * Settings.Scalar,
			(float)Prefix_Texture->w,
			(float)Prefix_Texture->h
		};
		Render_Texture(Prefix_Texture, &Prefix_Rectangle);
		if (Interface.Registering_Keybind == C1) {
			SDL_Texture* Registering_Texture = Render_Text(F_Subtext, "...", Colors.Abyss_Black);
			SDL_FRect Registering_Rectangle = {
				Prefix_Rectangle.x + Prefix_Rectangle.w + 20,
				Prefix_Rectangle.y,
				(float)Registering_Texture->w,
				(float)Registering_Texture->h
			};
			Render_Texture(Registering_Texture, &Registering_Rectangle);
			free_texture(Registering_Texture);
		} else {
			char Subcore[32];
			strncpy(Subcore, SDL_GetKeyName(Keybinds.Keybind_Settings[C1]), sizeof(Subcore));
			for (int C2 = 0; C2 < strlen(Subcore); C2++) {
				Subcore[C2] = (char)(tolower(Subcore[C2]));
			}
			SDL_Texture* Deadbutton_Texture = Render_Text(F_Subtext, Subcore, Colors.Abyss_Black);
			SDL_FRect Deadbutton_Rectangle = {
				Prefix_Rectangle.x + Prefix_Rectangle.w + 20,
				Prefix_Rectangle.y,
				(float)Deadbutton_Texture->w,
				(float)Deadbutton_Texture->h
			};
			if (Detect_Mouse_Collision(Deadbutton_Rectangle)) {
				Interface.UI_Selection = C1 + 6;
				char Alivebutton_Text[64];
				snprintf(Alivebutton_Text, sizeof(Alivebutton_Text), "> %s <", Subcore);
				SDL_Texture* Alivebutton_Texture = Render_Text(F_Subtext, Alivebutton_Text, Colors.Cherry_Blossom);
				SDL_Texture* Temporary_Texture = Render_Text(F_Subtext, "> ", Colors.Cherry_Blossom);
				int Offset = Temporary_Texture->w;
				free_texture(Temporary_Texture);
				SDL_FRect Alivebutton_Rectangle = {
					Deadbutton_Rectangle.x - Offset,
					Deadbutton_Rectangle.y,
					(float)Alivebutton_Texture->w,
					(float)Alivebutton_Texture->h
				};
				Render_Texture(Alivebutton_Texture, &Alivebutton_Rectangle);
				SDL_FRect Underline_Rectangle = {
					Deadbutton_Rectangle.x,
					Deadbutton_Rectangle.y +
					Deadbutton_Rectangle.h + 2,
					Deadbutton_Rectangle.w,
					Deadbutton_Rectangle.h * 0.1f
				};
				SDL_SetRenderDrawColor(Core.Renderer, Colors.Cherry_Blossom.r, Colors.Cherry_Blossom.g, Colors.Cherry_Blossom.b,
					SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(Core.Renderer, &Underline_Rectangle);
				Clear_Renderer();
				free_texture(Alivebutton_Texture);
			} else {
				Render_Texture(Deadbutton_Texture, &Deadbutton_Rectangle);
			}
			free_texture(Deadbutton_Texture);
		}
		free_texture(Prefix_Texture);
	}
}

void Render_Settings() {
	for (int C1 = 0; C1 < Textures.Settings_Label.Length; C1++) {
		Render_Texture(Textures.Settings_Label.Data[C1], &Rects.Settings_Label.Data[C1]);
	}
	Render_Button(&Textures.Return, &Rects.Return, (UI_Link){ Back }, Colors.Cherry_Blossom);
	Render_Slider(Interface.Slider_Texts[0], 1, 5, &Interface.Slider_Positions[0], (Point){ 50, 70 }, 220, Colors.Abyss_Black,
		Colors.Cherry_Blossom, true);
	Render_Slider(Interface.Slider_Texts[4], 2, 4, &Interface.Slider_Positions[4], (Point){ 50, 140 }, 220, Colors.Abyss_Black,
		Colors.Cherry_Blossom, true);
	Render_Slider(Interface.Slider_Texts[5], 3, 100, &Interface.Slider_Positions[5], (Point){ 50, 210 }, 220, Colors.Abyss_Black,
		Colors.Cherry_Blossom, true);
	Render_Slider(Interface.Slider_Texts[6], 4, 2, &Interface.Slider_Positions[6], (Point){ 50, 280 }, 220, Colors.Abyss_Black,
		Colors.Cherry_Blossom, true);
	Render_Button(&Textures.Anti_Aliasing.Data[(int)(!Settings.AA_Temporary)], &Rects.Anti_Aliasing.Data[(int)(
		!Settings.AA_Temporary)], (UI_Link){ Swap_AA }, Colors.Cherry_Blossom);
	Render_Button(&Textures.V_Sync.Data[(int)Settings.VS_Temporary], &Rects.V_Sync.Data[(int)Settings.VS_Temporary],
		(UI_Link){ Swap_VS }, Colors.Cherry_Blossom);
	if (Temporary.Settings_Changed) {
		Render_Button(&Textures.Save_Settings, &Rects.Save_Settings, (UI_Link){ Update_Settings }, Colors.Cherry_Blossom);
	}
	Process_Supply(&Supplies.Monitor_Size, Metadata.Monitor_Size, F_Subtext, Colors.Abyss_Black, (Point){ 50, 40 });
	Render_Keybinds();
	Verify_Settings();
}