#include <rendering.h>

void Render_Ocean() {
	Interface.Ocean_Cycle += LDE_STATICRATE / ((float)Interface.Frame_Rate);
	if (Interface.Ocean_Cycle >= 9) {
		Interface.Ocean_Cycle = 0;
	}
	SDL_FRect Ocean_Rectangle = {
		0,
		0,
		Settings.Screen_Size * 1200.0f,
		Settings.Screen_Size * 1200.0f
	};
	for (int Counter1 = 0; Counter1 < 3; Counter1++) {
		for (int Counter2 = 0; Counter2 < 3; Counter2++) {
			Ocean_Rectangle.x = (Counter1 * Ocean_Rectangle.w) - ((Core.Camera.X + LDE_BUFFERSIZE) * Settings.Screen_Size);
			Ocean_Rectangle.y = (Counter2 * Ocean_Rectangle.h) - ((Core.Camera.Y + LDE_BUFFERSIZE) * Settings.Screen_Size);
			Render_Texture(Textures.None.Data[(int)(Interface.Ocean_Cycle)], &Ocean_Rectangle);
		}
	}
}