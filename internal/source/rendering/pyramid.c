#include <rendering.h>

void Render_Pyramid() {
	float Width = ktn_fscale((ktn_grid_size * ktn_tile_size) + (ktn_buffer_size * 2.0f));
	for (int X = 0; X < 2; X++) {
		for (int Y = 0; Y < 2; Y++) {
			SDL_FRect Pyramid_Rectangle = {
				(Width * X) - ktn_fscale(Core.Camera.X) - ktn_fscale(ktn_buffer_size),
				(Width * Y) - ktn_fscale(Core.Camera.Y) - ktn_fscale(ktn_buffer_size),
				Width,
				Width
			};
			Render_Texture(Textures.Pyramid.Data[(X * 2) + Y], &Pyramid_Rectangle);
		}
	}
}