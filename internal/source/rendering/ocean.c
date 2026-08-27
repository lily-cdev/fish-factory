#include <rendering.h>

void Render_Ocean() {
	Interface.Ocean_Cycle += ktn_static_rate / ((float)Interface.Frame_Rate);
	if (Interface.Ocean_Cycle >= 9) {
		Interface.Ocean_Cycle = 0;
	}
	SDL_FRect Ocean_Rectangle = {
		0,
		0,
		(float)ktn_ocean_size,
		(float)ktn_ocean_size
	};
	int Iterations = (int)ceilf(ktn_fscale((ktn_grid_size * Core.Tile_Size) + (Core.Buffer_Size * 2)) / ktn_ocean_size);
	for (int C1 = 0; C1 < Iterations; C1++) {
		for (int C2 = 0; C2 < Iterations; C2++) {
			Ocean_Rectangle.x = (C1 * Ocean_Rectangle.w) - ktn_fscale(Core.Camera.X + Core.Buffer_Size);
			Ocean_Rectangle.y = (C2 * Ocean_Rectangle.h) - ktn_fscale(Core.Camera.Y + Core.Buffer_Size);
			Render_Texture(Textures.None.Data[(int)(Interface.Ocean_Cycle)], &Ocean_Rectangle);
		}
	}
}