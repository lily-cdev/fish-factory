#include <ui.h>

void Render_Application() {
    SDL_SetRenderTarget(Core.Renderer, Core.Game_Texture);
	Render_Ocean();
	Render_Pyramid();
	if (Interface.Building && Data.Funds - Interface.Item->Price >= 0 && Interface.Prompt_Identifier == P_None) {
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
		Cache.Wire_Box.x = scale_f(Offset_X - Core.Camera.X);
		Cache.Wire_Box.y = scale_f(Offset_Y - Core.Camera.Y);
		Render_Texture(Cache.Wire_Cache.Data[C1], &Cache.Wire_Box);
	}
	if (Interface.Tool == T_Plumbing) {
		Render_Pipes();
	}
	if (Interface.Tool == T_Building && Interface.UI_Selection == 0 && Interface.Prompt_Identifier == P_None) {
		Point Pos;
		ID_To_Size(Interface.Item, Interface.Rotation, &Pos.X, &Pos.Y);
		if (Pos.X > 0 || Pos.Y > 0) {
			Render_Blueprint(Pos.X, Pos.Y);
		}
	}
	Render_Submarine();
	SDL_SetRenderTarget(Core.Renderer, NULL);
	SDL_FRect Temporary_Rectangle = { 0, 0, Core.Screensize.X, Core.Screensize.Y };
	Render_Texture(Core.Game_Texture, &Temporary_Rectangle);
	if (Interface.Tool > 0) {
		SDL_FRect Hitbox = {
			0.0f,
			0.0f,
			scale_f(LDE_TILESIZE),
			scale_f(LDE_TILESIZE)
		};
		Point Subpos = {
			scale_f(Core.Camera.X) + Core.Mouse.X,
			scale_f(Core.Camera.Y) + Core.Mouse.Y
		};
		Hitbox.x = floorf(Subpos.X / scale_f(LDE_TILESIZE) * scale_f(LDE_TILESIZE)) - scale_f(Core.Camera.X);
		Hitbox.y = floorf(Subpos.Y / scale_f(LDE_TILESIZE) * scale_f(LDE_TILESIZE)) - scale_f(Core.Camera.Y);
		int Limit = scale_f(LDE_TILESIZE * LDE_GRIDSIZE);
		bool Rendering = false;
		if (Subpos.X > 0 && Subpos.Y > 0 && Subpos.X < Limit && Subpos.Y < Limit) {
			Render_Texture(Textures.Crosshair, &Hitbox);
			Rendering = true;
		}
		if (Interface.Tool == T_Inspecting && Rendering) {
			float Padding = scale_f(2.0f);
			float Height = scale_f(24.0f);
			Point Pos = { };
			bool Satiated = false;
			for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
				Rects.Tile_1x1.x = scale_f((Column * LDE_TILESIZE) - Core.Camera.X);
				for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
					Rects.Tile_1x1.y = scale_f((Row * LDE_TILESIZE) - Core.Camera.Y);
					if (!Detect_Mouse_Collision(Rects.Tile_1x1)) {
						continue;
					}
					Pos = (Point){ Column, Row };
					Satiated = true;
					break;
				}
			}
			if (Satiated && Data.Data_Grid[pt(Pos)][Power_Cap] >= 0.1f) {
				SDL_FRect Energy = {
					0,
					0,
					scale_f(6.0f),
					Height
				};
				Energy.x = Hitbox.x - Energy.w - Padding;
				Energy.y = (Hitbox.h * 0.5f) - (Energy.h * 0.5f) + Hitbox.y;
				Set_Renderer_Color(Colors.Dark_Grey);
				SDL_RenderFillRect(Core.Renderer, &Energy);
				Clear_Renderer();
				Energy.h *= Data.Data_Grid[pt(Pos)][Stored_Power] / Data.Data_Grid[pt(Pos)][Power_Cap];
				Energy.y += Height - Energy.h;
				Set_Renderer_Color(Colors.Cherry_Blossom);
				SDL_RenderFillRect(Core.Renderer, &Energy);
				Clear_Renderer();
			}
			if (Satiated && Data.Data_Grid[pt(Pos)][Fluid_Cap] >= 0.1f) {
				SDL_FRect Item = {
					0,
					0,
					Settings.Scalar * 24.0f,
					Height
				};
				Item.x = Hitbox.x + Hitbox.w + Padding;
				int Y_Cache = (Hitbox.h * 0.5f) - (Item.h * 0.5f) + Hitbox.y;
				Item.y = Y_Cache;
				Set_Renderer_Color(Colors.Dark_Grey);
				SDL_RenderFillRect(Core.Renderer, &Item);
				Clear_Renderer();
				Item.h *= Data.Data_Grid[pt(Pos)][Stored_Fluids] / Data.Data_Grid[pt(Pos)][Fluid_Cap];
				Item.y += Height - Item.h;
				Set_Renderer_Color(Colors.Cherry_Blossom);
				SDL_RenderFillRect(Core.Renderer, &Item);
				Clear_Renderer();
				SDL_FRect Item_Rect = {
					(Settings.Scalar * 2.0f) + Item.x,
					(Settings.Scalar * 2.0f) + Y_Cache,
					Settings.Scalar * 20.0f,
					Settings.Scalar * 20.0f
				};
				if (Data.Items_Grid[pt(Pos)] == LDE_INVALID) {
					Render_Texture(Textures.None_Item, &Item_Rect);
				} else {
					Render_Texture(Textures.Items.Data[Data.Items_Grid[pt(Pos)]], &Item_Rect);
				}
			}
		}
		Hitbox.x = Core.Mouse.X - scale_f(LDE_TILESIZE * 0.5f);
		Hitbox.y = Core.Mouse.Y - scale_f(LDE_TILESIZE * 0.5f);
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
		SDL_Texture* Fragment_Texture = Render_Text(F_Subtext, Metadata.Tool_Texts[Interface.Tool], Colors.Abyss_Black);
		SDL_FRect Fragment_Rectangle = (SDL_FRect){
			0,
			Settings.Scalar * 10.0f,
			(float)Fragment_Texture->w,
			(float)Fragment_Texture->h
		};
		Fragment_Rectangle.x = Core.Screenhalfsize.X - (Fragment_Rectangle.w * 0.5f);
		int Height = Fragment_Rectangle.y + Fragment_Rectangle.h;
		Set_Renderer_Color(Colors.Dark_Grey);
		SDL_FRect Background = {
			0,
			0,
			(Settings.Scalar * 30.0f) + Fragment_Rectangle.w,
			(Settings.Scalar * 15.0f) + Height
		};
		Background.x = Core.Screenhalfsize.X - (Background.w * 0.5f);
		SDL_RenderFillRect(Core.Renderer, &Background);
		Set_Renderer_Color(Colors.Light_Grey);
		Background = (SDL_FRect){
			0,
			0,
			(Settings.Scalar * 20.0f) + Fragment_Rectangle.w,
			(Settings.Scalar * 10.0f) + Height
		};
		Background.x = Core.Screenhalfsize.X - (Background.w * 0.5f);
		SDL_RenderFillRect(Core.Renderer, &Background);
		Clear_Renderer();
		Render_Texture(Fragment_Texture, &Fragment_Rectangle);
		free_texture(Fragment_Texture);
	}
	float Bar_Height = Settings.Scalar * 310.0f;
	Interface.Bar_Up = false;
	if (Core.Mouse.Y >= Bar_Height && Interface.Prompt_Identifier == P_None) {
		Interface.Bar_Up = true;
		Set_Renderer_Color(Colors.Dark_Grey);
		float Bar_Width = Core.Screenhalfsize.Y - Bar_Height;
		const SDL_FRect Background = {
			0,
			Bar_Height,
			Core.Screensize.X,
			Bar_Width
		};
		SDL_RenderFillRect(Core.Renderer, &Background);
		float Padding = Settings.Scalar * 4.0f;
		float Width = scale_f(640.0f / LDE_TOOLS) - (((1.0f / LDE_TOOLS) + 1.0f) * Padding);
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
			Render_Texture(Textures.Tool.Data[C1], &Rects.Tool[C1]);
			char Carrier[32];
			snprintf(Carrier, sizeof(Carrier), "[%s]", SDL_GetKeyName(Keybinds.Keybind_List[C1 + 4]));
			SDL_Texture* Carrying_Texture = Render_Text(F_Microtext, Carrier, Colors.Abyss_Black);
			SDL_FRect Subcarrier = {
				Pasting.x - (Padding * 0.5f) + Width - Carrying_Texture->w,
				(Padding * 0.5f) + Pasting.y,
				Carrying_Texture->w,
				Carrying_Texture->h
			};
			Render_Texture(Carrying_Texture, &Subcarrier);
			free_texture(Carrying_Texture);
		}
	}
}