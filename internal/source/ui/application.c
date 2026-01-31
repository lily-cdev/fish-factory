#include <ui.h>

void Render_Application() {
    SDL_SetRenderTarget(Core.Renderer, Core.Game_Texture);
	Render_Ocean();
	Render_Pyramid();
	if (Interface.Building && Data.Funds - Metadata.Machine_Prices[Interface.Placing_Item - 1] > 0) {
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
	for (int Counter = 0; Counter < 4; Counter++) {
		int Offset_X = 0;
		int Offset_Y = 0;
		switch (Counter) {
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
		Render_Texture(Cache.Wire_Cache.Data[Counter], &Cache.Wire_Box);
	}
	if (Interface.Tool == 4) {
		Render_Pipes();
	}
	if (Interface.Tool == 0 && Interface.UI_Selection == 0) {
		int X;
		int Y;
		ID_To_Size(Interface.Placing_Item - 1, Interface.Placing_Rotation, &X, &Y);
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
		Hitbox.x = (int)(((int)((Core.Mouse.X + (Core.Camera.X * Settings.Screen_Size)) / (LDE_TILESIZE *
			Settings.Screen_Size)) * (LDE_TILESIZE * Settings.Screen_Size)) - (Core.Camera.X * Settings.Screen_Size));
		Hitbox.y = (int)(((int)((Core.Mouse.Y + (Core.Camera.Y * Settings.Screen_Size)) / (LDE_TILESIZE *
			Settings.Screen_Size)) * (LDE_TILESIZE * Settings.Screen_Size)) - (Core.Camera.Y * Settings.Screen_Size));
		Render_Texture(Textures.Crosshair, &Hitbox);
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