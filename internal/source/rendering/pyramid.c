#include <rendering.h>

void Render_Pyramid() {
	float Width = ((LDE_GRIDSIZE * LDE_TILESIZE) + (LDE_BUFFERSIZE * 2)) * Settings.Screen_Size;
	SDL_FRect Mesh_Rectangle = {
		(float)(-(Core.Camera.X + 70)) * Settings.Screen_Size,
		(float)(-(Core.Camera.Y + 70)) * Settings.Screen_Size,
		((LDE_GRIDSIZE * LDE_TILESIZE) + 140.0f) * Settings.Screen_Size,
		((LDE_GRIDSIZE * LDE_TILESIZE) + 140.0f) * Settings.Screen_Size
	};
	Render_Texture(Textures.Mesh, &Mesh_Rectangle);
	for (int X = 0; X < 2; X++) {
		for (int Y = 0; Y < 2; Y++) {
			SDL_FRect Pyramid_Rectangle = {
				(float)(Width * X) - (float)(Core.Camera.X * Settings.Screen_Size) - (LDE_BUFFERSIZE * Settings.Screen_Size),
				(float)(Width * Y) - (float)(Core.Camera.Y * Settings.Screen_Size) - (LDE_BUFFERSIZE * Settings.Screen_Size),
				Width,
				Width
			};
			Render_Texture(Textures.Pyramid.Data[(X * 2) + Y], &Pyramid_Rectangle);
		}
	}
}