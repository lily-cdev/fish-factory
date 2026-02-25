#include <ui.h>

void Render_Application() {
    SDL_SetRenderTarget(Core.Renderer, Core.Game_Texture);
	Render_Ocean();
	Render_Pyramid();
	if (Interface.Building && Data.Funds - Metadata.Machine_Prices[Interface.Item - 1] > 0 &&
		Interface.Prompt_Identifier == P_None) {
		Build_Grid();
		Update_Grid();
	}
	Render_Grid();
	if (Cache.Wire_State != LDE_INVALID) {
		Render_Wires();
		if (Cache.Wire_State == Deep_Recache) {
			Clear_Unconnected_Bridges(&Wires);
			Update_Grid();
		}
		Cache.Wire_State = LDE_INVALID;
	}
	Render_Wire_Nodes();
	for (int C1 = 0; C1 < 4; C1++) {
		int Offset_X = 0;
		int Offset_Y = 0;
		switch (C1) {
		case 1:
			Offset_X = 1;
			break;
		case 2:
			Offset_X = 1;
			Offset_Y = 1;
			break;
		case 3:
			Offset_Y = 1;
			break;
		default:
			break;
		}
		Offset_X *= LDE_GRIDSIZE * 20;
		Offset_Y *= LDE_GRIDSIZE * 20;
		Cache.Wire_Box.x = (int)(Offset_X - Core.Camera.X) * Settings.Screen_Size;
		Cache.Wire_Box.y = (int)(Offset_Y - Core.Camera.Y) * Settings.Screen_Size;
		Render_Texture(Cache.Wire_Cache.Data[C1], &Cache.Wire_Box);
	}
	if (Interface.Tool == T_Plumbing) {
		Render_Pipes();
	}
	if (Interface.Tool == T_Building && Interface.UI_Selection == 0 && Interface.Prompt_Identifier == P_None) {
		int X;
		int Y;
		ID_To_Size(Interface.Item - 1, Interface.Rotation, &X, &Y);
		Render_Blueprint(X, Y);
	}
	Render_Submarine();
	SDL_SetRenderTarget(Core.Renderer, NULL);
	SDL_FRect Temporary_Rectangle = { 0, 0, Settings.Screen_Size * 640.0f, Settings.Screen_Size * 360.0f };
	Render_Texture(Core.Game_Texture, &Temporary_Rectangle);
	if (Interface.Tool > 0) {
		SDL_FRect Hitbox = {
			0.0f,
			0.0f,
			(float)(LDE_TILESIZE * Settings.Screen_Size),
			(float)(LDE_TILESIZE * Settings.Screen_Size)
		};
		Point Subpos = {
			(Core.Camera.X * Settings.Screen_Size) + Core.Mouse.X,
			(Core.Camera.Y * Settings.Screen_Size) + Core.Mouse.Y
		};
		Hitbox.x = ((int)(Subpos.X / (LDE_TILESIZE * Settings.Screen_Size)) * (LDE_TILESIZE * Settings.Screen_Size)) -
			(Core.Camera.X * Settings.Screen_Size);
		Hitbox.y = ((int)(Subpos.Y  / (LDE_TILESIZE * Settings.Screen_Size)) * (LDE_TILESIZE * Settings.Screen_Size)) -
			(Core.Camera.Y * Settings.Screen_Size);
		int Limit = LDE_TILESIZE * LDE_GRIDSIZE * Settings.Screen_Size;
		bool Rendering = false;
		if (Subpos.X > 0 && Subpos.Y > 0 && Subpos.X < Limit && Subpos.Y < Limit) {
			Render_Texture(Textures.Crosshair, &Hitbox);
			Rendering = true;
		}
		if (Interface.Tool == T_Inspecting && Rendering) {
			float Padding = Settings.Screen_Size * 2.0f;
			float Height = Settings.Screen_Size * 24.0f;
			Point Pos = { };
			bool Satiated = false;
			for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
				Rects.Tile_1x1.x = (float)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size);
				for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
					Rects.Tile_1x1.y = (float)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size);
					if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
						Pos = (Point){ Column, Row };
						Satiated = true;
						break;
					}
				}
			}
			if (Satiated && Data.Data_Grid[Pos.X][Pos.Y][Power_Cap] >= 0.1f) {
				SDL_FRect Energy = {
					0,
					0,
					Settings.Screen_Size * 6.0f,
					Height
				};
				Energy.x = Hitbox.x - Energy.w - Padding;
				Energy.y = (Hitbox.h * 0.5f) - (Energy.h * 0.5f) + Hitbox.y;
				Set_Renderer_Color(Colors.Dark_Grey);
				SDL_RenderFillRect(Core.Renderer, &Energy);
				Clear_Renderer();
				Energy.h *= Data.Data_Grid[Pos.X][Pos.Y][Stored_Power] / Data.Data_Grid[Pos.X][Pos.Y][Power_Cap];
				Energy.y += Height - Energy.h;
				Set_Renderer_Color(Colors.Cherry_Blossom);
				SDL_RenderFillRect(Core.Renderer, &Energy);
				Clear_Renderer();
			}
			//get fill percent
			if (Satiated && Data.Data_Grid[Pos.X][Pos.Y][Fluid_Cap] >= 0.1f) {
				SDL_FRect Item = {
					0,
					0,
					Settings.Screen_Size * 24.0f,
					Height
				};
				Item.x = Hitbox.x + Hitbox.w + Padding;
				Item.y = (Hitbox.h * 0.5f) - (Item.h * 0.5f) + Hitbox.y;
				Set_Renderer_Color(Colors.Dark_Grey);
				SDL_RenderFillRect(Core.Renderer, &Item);
				Clear_Renderer();
			}
		}
		Hitbox.x = Core.Mouse.X - (LDE_TILESIZE * Settings.Screen_Size * 0.5f);
		Hitbox.y = Core.Mouse.Y - (LDE_TILESIZE * Settings.Screen_Size * 0.5f);
		Render_Texture(Textures.Cursor, &Hitbox);
		bool Targeting = false;
		switch (Interface.Tool) {
		case 1:
			if (Get_Simple_Grid_Tile(Data.Visual_Grid, 0) != 0) {
				Targeting = true;
			}
			break;
		default:
			break;
		}
		if (Targeting) {
			Render_Texture(Textures.Cursor_Core, &Hitbox);
		}
	}
}

void Render_Hotbar() {
	if (Interface.Tool != T_None) {
		SDL_Surface* Fragment_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Metadata.Tool_Texts[Interface.Tool], 0,
			Colors.Abyss_Black);
		SDL_Texture* Fragment_Texture = Surface_To_Texture(Core.Renderer, Fragment_Surface);
		SDL_FRect Fragment_Rectangle = (SDL_FRect){
			0,
			Settings.Screen_Size * 10.0f,
			(float)Fragment_Surface->w,
			(float)Fragment_Surface->h
		};
		Fragment_Rectangle.x = (Settings.Screen_Size * 320.0f) - (Fragment_Rectangle.w * 0.5f);
		int Height = Fragment_Rectangle.y + Fragment_Rectangle.h;
		SDL_DestroySurface(Fragment_Surface);
		Set_Renderer_Color(Colors.Dark_Grey);
		SDL_FRect Background = {
			0,
			0,
			(Settings.Screen_Size * 30.0f) + Fragment_Rectangle.w,
			(Settings.Screen_Size * 15.0f) + Height
		};
		Background.x = (Settings.Screen_Size * 320.0f) - (Background.w * 0.5f);
		SDL_RenderFillRect(Core.Renderer, &Background);
		Set_Renderer_Color(Colors.Light_Grey);
		Background = (SDL_FRect){
			0,
			0,
			(Settings.Screen_Size * 20.0f) + Fragment_Rectangle.w,
			(Settings.Screen_Size * 10.0f) + Height
		};
		Background.x = (Settings.Screen_Size * 320.0f) - (Background.w * 0.5f);
		SDL_RenderFillRect(Core.Renderer, &Background);
		Clear_Renderer();
		SDL_RenderTexture(Core.Renderer, Fragment_Texture, NULL, &Fragment_Rectangle);
		free_texture(Fragment_Texture);
	}
	float Bar_Height = Settings.Screen_Size * 310.0f;
	Interface.Bar_Up = false;
	if (Core.Mouse.Y >= Bar_Height && Interface.Prompt_Identifier == P_None) {
		Interface.Bar_Up = true;
		Set_Renderer_Color(Colors.Dark_Grey);
		float Bar_Width = (Settings.Screen_Size * 360.0f) - Bar_Height;
		const SDL_FRect Background = {
			0,
			Bar_Height,
			Settings.Screen_Size * 640.0f,
			Bar_Width
		};
		SDL_RenderFillRect(Core.Renderer, &Background);
		float Padding = Settings.Screen_Size * 4.0f;
		float Width = ((640.0f / LDE_TOOLS) * Settings.Screen_Size) - (((1.0f / LDE_TOOLS) + 1.0f) * Padding);
		for (int C1 = 0; C1 < LDE_TOOLS; C1++) {
			SDL_FRect Pasting = {
				(C1 * Width) + ((C1 + 1) * Padding),
				Bar_Height + Padding,
				Width,
				Bar_Width - (Padding * 2.0f)
			};
			SDL_Color Color = (Detect_Mouse_Collision(Pasting)) ? Colors.Light_Grey : Colors.Mid_Grey;
			if (C1 == Interface.Tool) {
				Color = Colors.Cherry_Blossom;
			} else if (Detect_Mouse_Collision(Pasting)) {
				Interface.UI_Selection = C1;
			}
			Set_Renderer_Color(Color);
			SDL_RenderFillRect(Core.Renderer, &Pasting);
			Clear_Renderer();
			Rects.Tool[C1].x = (Pasting.w * 0.5f) - (Rects.Tool[C1].w * 0.5f) + Pasting.x;
			Rects.Tool[C1].y = (Bar_Width * 0.5f) - (Rects.Tool[C1].h * 0.5f) + Bar_Height;
			SDL_RenderTexture(Core.Renderer, Textures.Tool.Data[C1], NULL, &Rects.Tool[C1]);
			char Carrier[32];
			snprintf(Carrier, sizeof(Carrier), "[%s]", SDL_GetKeyName(Keybinds.Keybind_List[C1 + 4]));
			SDL_Surface* Surface = TTF_RenderText_Blended(Fonts.Microtext_Font, Carrier, 0, Colors.Abyss_Black);
			SDL_FRect Subcarrier = {
				Pasting.x - (Padding * 0.5f) + Width - Surface->w,
				(Padding * 0.5f) + Pasting.y,
				Surface->w,
				Surface->h
			};
			SDL_Texture* Texture = Surface_To_Texture(Core.Renderer, Surface);
			SDL_RenderTexture(Core.Renderer, Texture, NULL, &Subcarrier);
			free_texture(Texture);
			SDL_DestroySurface(Surface);
		}
	}
}