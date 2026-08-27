#include <rendering.h>

void Render_Pyramid() {
	float Width = ktn_fscale((ktn_grid_size * Core.Tile_Size) + (Core.Buffer_Size * 2.0f));
	for (int X = 0; X < 2; X++) {
		for (int Y = 0; Y < 2; Y++) {
			SDL_FRect Pyramid_Rectangle = {
				(Width * X) - ktn_fscale(Core.Camera.X) - ktn_fscale(Core.Buffer_Size),
				(Width * Y) - ktn_fscale(Core.Camera.Y) - ktn_fscale(Core.Buffer_Size),
				Width,
				Width
			};
			Render_Texture(Textures.Pyramid.Data[(X * 2) + Y], &Pyramid_Rectangle);
		}
	}
}