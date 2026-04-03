#include <rendering.h>

void Render_Ocean() {
	Interface.Ocean_Cycle += LDE_STATICRATE / ((float)Interface.Frame_Rate);
	if (Interface.Ocean_Cycle >= 9) {
		Interface.Ocean_Cycle = 0;
	}
	SDL_FRect Ocean_Rectangle = {
		0,
		0,
		Settings.Scalar * 1200.0f,
		Settings.Scalar * 1200.0f
	};
	for (int C1 = 0; C1 < 3; C1++) {
		for (int C2 = 0; C2 < 3; C2++) {
			Ocean_Rectangle.x = (C1 * Ocean_Rectangle.w) - ((Core.Camera.X + LDE_BUFFERSIZE) * Settings.Scalar);
			Ocean_Rectangle.y = (C2 * Ocean_Rectangle.h) - ((Core.Camera.Y + LDE_BUFFERSIZE) * Settings.Scalar);
			Render_Texture(Textures.None.Data[(int)(Interface.Ocean_Cycle)], &Ocean_Rectangle);
		}
	}
}