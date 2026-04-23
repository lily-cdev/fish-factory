#include <rendering.h>

void Render_Pyramid() {
	float Width = scale_f((LDE_GRIDSIZE * LDE_TILESIZE) + (LDE_BUFFERSIZE * 2.0f));
	SDL_FRect Mesh_Rectangle = {
		scale_f(-(Core.Camera.X + 70.0f)),
		scale_f(-(Core.Camera.Y + 70.0f)),
		scale_f((LDE_GRIDSIZE * LDE_TILESIZE) + 140.0f),
		scale_f((LDE_GRIDSIZE * LDE_TILESIZE) + 140.0f)
	};
	Render_Texture(Textures.Mesh, &Mesh_Rectangle);
	for (int X = 0; X < 2; X++) {
		for (int Y = 0; Y < 2; Y++) {
			SDL_FRect Pyramid_Rectangle = {
				(Width * X) - scale_f(Core.Camera.X) - scale_f(LDE_BUFFERSIZE),
				(Width * Y) - scale_f(Core.Camera.Y) - scale_f(LDE_BUFFERSIZE),
				Width,
				Width
			};
			Render_Texture(Textures.Pyramid.Data[(X * 2) + Y], &Pyramid_Rectangle);
		}
	}
}