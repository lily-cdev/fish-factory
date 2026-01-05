#include <ui.h>

void Clear_Renderer() {
	SDL_SetRenderDrawColor(Core.Renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
}

void Set_Renderer_Color(const SDL_Color Color) {
	SDL_SetRenderDrawColor(Core.Renderer, Color.r, Color.g, Color.b, SDL_ALPHA_OPAQUE);
}

void Render_Outline(SDL_FRect Rectangle, SDL_Color Color, int Multiplier) {
	Set_Renderer_Color(Color);
	for (int Counter = 0; Counter < LDE_BORDERWIDTH * Settings.Screen_Size * Multiplier; Counter++) {
		SDL_RenderRect(Core.Renderer, &Rectangle);
		Rectangle.x++;
		Rectangle.y++;
		Rectangle.w -= 2;
		Rectangle.h -= 2;
	}
	Clear_Renderer();
}

void Render_Box(int X, int Y, int W, int H, SDL_Color Inner_Color, SDL_Color Outer_Color) {
	SDL_FRect External_Rectangle = { (float)(X - 4) * Settings.Screen_Size,
		(float)(Y - 4) * Settings.Screen_Size, (float)(W + 8) *
		Settings.Screen_Size, (float)(H + 8) * Settings.Screen_Size };
	Set_Renderer_Color(Outer_Color);
	SDL_RenderFillRect(Core.Renderer, &External_Rectangle);
	SDL_FRect Internal_Rectangle = { (float)(X * Settings.Screen_Size),
		(float)(Y * Settings.Screen_Size), (float)(W *
		Settings.Screen_Size), (float)(H * Settings.Screen_Size) };
	Set_Renderer_Color(Inner_Color);
	SDL_RenderFillRect(Core.Renderer, &Internal_Rectangle);
	Clear_Renderer();
}

SDL_FRect Buffer_Rectangle(const SDL_FRect Source, const int X, const int Y) {
	SDL_FRect Yield = { Source.x - (X * Settings.Screen_Size), Source.y - (Y * Settings.Screen_Size),
		Source.w + ((X * 2) * Settings.Screen_Size), Source.h + ((Y * 2) * Settings.Screen_Size) };
	return Yield;
}