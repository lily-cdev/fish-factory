#include <rendering.h>

void Render_Ocean() {
	Interface.Ocean_Cycle += LDE_STATICRATE / ((float)Interface.Frame_Rate);
	if (Interface.Ocean_Cycle >= 9) {
		Interface.Ocean_Cycle = 0;
	}
	SDL_FRect Ocean_Rectangle = {
		0,
		0,
		(float)LDE_OCEANSIZE,
		(float)LDE_OCEANSIZE
	};
	int Iterations = (int)ceilf(scale_f((LDE_GRIDSIZE * LDE_TILESIZE) + LDE_BUFFERSIZE) / LDE_OCEANSIZE);
	for (int C1 = 0; C1 < Iterations; C1++) {
		for (int C2 = 0; C2 < Iterations; C2++) {
			Ocean_Rectangle.x = (C1 * Ocean_Rectangle.w) - scale_f(Core.Camera.X + LDE_BUFFERSIZE);
			Ocean_Rectangle.y = (C2 * Ocean_Rectangle.h) - scale_f(Core.Camera.Y + LDE_BUFFERSIZE);
			Render_Texture(Textures.None.Data[(int)(Interface.Ocean_Cycle)], &Ocean_Rectangle);
		}
	}
}