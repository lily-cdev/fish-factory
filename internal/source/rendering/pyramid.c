#include <rendering.h>

void Render_Pyramid() {
	float Width = ktn_fscale((ktn_grid_size * Core.Tile_Size) + (Core.Buffer_Size * 2.0f));
	for (int X = 0; X < 2; X++) {
		SDL_FRect Drydock_Rectangle;
		for (int Y = 0; Y < 2; Y++) {
			SDL_FRect Pyramid_Rectangle = {
				(Width * X) - ktn_fscale(Core.Camera.X) - ktn_fscale(Core.Buffer_Size),
				(Width * Y) - ktn_fscale(Core.Camera.Y) - ktn_fscale(Core.Buffer_Size),
				Width,
				Width
			};
			Render_Texture(Textures.Pyramid.Data[(X * 2) + Y], &Pyramid_Rectangle);
			if (Y == 0) {
				Drydock_Rectangle = Pyramid_Rectangle;
			}
		}
		Drydock_Rectangle.y += ktn_fscale((ktn_grid_size + 5) * Core.Tile_Size);
		Render_Texture(Textures.Drydock.Data[X], &Drydock_Rectangle);
		Rects.Drydock_Base.x = (Width * 0.5f) - (Rects.Drydock_Base.w * Core.Ratio * 0.7f) - ktn_fscale(Core.Camera.X);
		Rects.Drydock_Base.y = Drydock_Rectangle.y + ktn_fscale(Core.Tile_Size * 10);
		for (int C1 = 0; C1 < 2; C1++) {
			SDL_FRect Subrectangle = {
				Rects.Drydock_Base.x + ((Rects.Drydock_Base.w * Core.Ratio * 0.5f) * C1),
				Rects.Drydock_Base.y,
				Rects.Drydock_Base.w * Core.Ratio * 0.5f,
				Rects.Drydock_Base.h * Core.Ratio
			};
			Render_Texture(Textures.Drydock_Base.Data[C1], &Subrectangle);
			if (Data.Objective_Phase > 0) {
				Render_Texture(Textures.Drydock_Frames[Data.Objective_Phase - 1].Data[C1], &Subrectangle);
			}
		}
	}
	Rects.Tunnel.Data[0].x = ktn_fscale((Core.Tile_Size * 2) - Core.Camera.X);
	Rects.Tunnel.Data[0].y = ktn_fscale((Core.Tile_Size * 48.25f) - Core.Camera.Y);
	Render_Texture(Textures.Tunnel.Data[0], &Rects.Tunnel.Data[0]);
	Rects.Tunnel.Data[0].x = ktn_fscale((Core.Tile_Size * 2) - Core.Camera.X);
	Rects.Tunnel.Data[0].y = ktn_fscale((Core.Tile_Size * 50.25f) - Core.Camera.Y);
	Render_Texture(Textures.Tunnel.Data[0], &Rects.Tunnel.Data[0]);
	Rects.Tunnel.Data[0].x = ktn_fscale((Core.Tile_Size * 46) - (Rects.Tunnel.Data[0].w / Settings.Scalar) - Core.Camera.X);
	Rects.Tunnel.Data[0].y = ktn_fscale((Core.Tile_Size * 48.25f) - Core.Camera.Y);
	Render_Texture(Textures.Tunnel.Data[0], &Rects.Tunnel.Data[0]);
	Rects.Tunnel.Data[0].x = ktn_fscale((Core.Tile_Size * 46) - (Rects.Tunnel.Data[0].w / Settings.Scalar) - Core.Camera.X);
	Rects.Tunnel.Data[0].y = ktn_fscale((Core.Tile_Size * 50.25f) - Core.Camera.Y);
	Render_Texture(Textures.Tunnel.Data[0], &Rects.Tunnel.Data[0]);
}