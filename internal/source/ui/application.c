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
			Clear_Unconnected_Wires();
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