#include <core.h>

SDL_Texture* New_Texture(SDL_Renderer* Renderer, int Width, int Height) {
	SDL_Texture* Texture = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width, Height);
	if (Texture == NULL) {
		jump(I_No_Texture, "could not create texture");
	}
	SDL_SetTextureScaleMode(Texture, Scaling_Quality);
	SDL_SetRenderTarget(Renderer, Texture);
	SDL_SetRenderDrawColor(0, 0, 0, SDL_ALPHA_TRANSPARENT);
	SDL_RenderClear(Texture);
	SDL_SetRenderTarget(Renderer, NULL);
	return Texture;
}

SDL_Texture* Surface_To_Texture(SDL_Renderer* Renderer, SDL_Surface* Surface) {
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
	if (Texture == NULL) {
		jump(I_No_Surface_Texture, "could not create texture from surface");
	}
	SDL_SetTextureScaleMode(Texture, Scaling_Quality);
	return Texture;
}

SDL_Texture* IMG_To_Texture(SDL_Renderer* Renderer, const char* Path) {
	SDL_Surface* Surface;
	load_bmp(Surface, Path);
	SDL_Texture* Texture = Surface_To_Texture(Renderer, Surface);
	SDL_DestroySurface(Surface);
	return Texture;
}

int sgn(float Input) {
	if (Input > 0) {
		return 1;
	} else if (Input < 0) {
		return -1;
	}
	return 0;
}