#include <data.h>

void Preclear_Temporaries() {
	memset(Data.Animation_Grid, LDE_INVALID, sizeof(Data.Animation_Grid));
}

void Render_Loadscreen() {
	Set_Renderer_Color(Colors.Pure_White);
	SDL_RenderClear(Core.Renderer);
	Clear_Renderer();
	SDL_Surface* Text_Surface = TTF_RenderText_Blended(Fonts.Logo_Font,
		"loading assets", 14, Colors.Abyss_Black);
	SDL_FRect Pasting_Rectangle = {
		(Settings.Screen_Size * 320.0f) - (Text_Surface->w * 0.5),
		(Settings.Screen_Size * 180.0f) - (Text_Surface->h * 0.5),
		(float)(Text_Surface->w),
		(float)(Text_Surface->h)
	};
	SDL_Texture* Text_Texture = SDL_GenerateTextureFromSurface(
		Core.Renderer, Text_Surface);
	SDL_RenderTexture(Core.Renderer, Text_Texture,
		NULL, &Pasting_Rectangle);
	SDL_DestroySurface(Text_Surface);
	SDL_DestroyTexture(Text_Texture);
	SDL_RenderPresent(Core.Renderer);
	SDL_PumpEvents();
}