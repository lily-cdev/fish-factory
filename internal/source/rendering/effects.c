#include <rendering.h>

void Render_Lighting() {
	for (int X = 0; X < 2; X++) {
		for (int Y = 0; Y < 2; Y++) {
			SDL_FRect Rect = {
				(Temporary.Pixels * X) - ktn_fscale(Core.Camera.X),
				(Temporary.Pixels * Y) - ktn_fscale(Core.Camera.Y),
				Temporary.Pixels,
				Temporary.Pixels
			};
			Render_Texture(Temporary.Lighting[(X * 2) + Y], &Rect);
		}
	}
}