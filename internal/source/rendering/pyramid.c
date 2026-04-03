#include <rendering.h>

void Render_Pyramid() {
	float Width = ((LDE_GRIDSIZE * LDE_TILESIZE) + (LDE_BUFFERSIZE * 2)) * Settings.Scalar;
	SDL_FRect Mesh_Rectangle = {
		(float)(-(Core.Camera.X + 70)) * Settings.Scalar,
		(float)(-(Core.Camera.Y + 70)) * Settings.Scalar,
		((LDE_GRIDSIZE * LDE_TILESIZE) + 140.0f) * Settings.Scalar,
		((LDE_GRIDSIZE * LDE_TILESIZE) + 140.0f) * Settings.Scalar
	};
	Render_Texture(Textures.Mesh, &Mesh_Rectangle);
	for (int X = 0; X < 2; X++) {
		for (int Y = 0; Y < 2; Y++) {
			SDL_FRect Pyramid_Rectangle = {
				(float)(Width * X) - (float)(Core.Camera.X * Settings.Scalar) - (LDE_BUFFERSIZE * Settings.Scalar),
				(float)(Width * Y) - (float)(Core.Camera.Y * Settings.Scalar) - (LDE_BUFFERSIZE * Settings.Scalar),
				Width,
				Width
			};
			Render_Texture(Textures.Pyramid.Data[(X * 2) + Y], &Pyramid_Rectangle);
		}
	}
}