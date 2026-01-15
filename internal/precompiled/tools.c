#include <core.h>

SDL_Texture* SDL_GenerateTexture(SDL_Renderer* Renderer, int Width, int Height) {
	SDL_Texture* Texture = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width, Height);
	SDL_SetTextureScaleMode(Texture, Scaling_Quality);
	return Texture;
}

SDL_Texture* SDL_GenerateTextureFromSurface(SDL_Renderer* Renderer, SDL_Surface* Surface) {
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
	if (Texture == NULL) {
		puts("fail2");
	}
	SDL_SetTextureScaleMode(Texture, Scaling_Quality);
	return Texture;
}

SDL_Texture* IMG_GenerateTexture(SDL_Renderer* Renderer, const char* Path) {
	SDL_Surface* Surface = Load_BMP(Path);
	if (Surface == NULL) {
		puts("fail");
	}
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Renderer, Surface);
	SDL_SetTextureScaleMode(Texture, Scaling_Quality);
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

float sqr_f(float Input) {
	return Input * Input;
}

int sqr_i(int Input) {
	return Input * Input;
}

bool evn_i(int Input) {
	return (int)(Input & 1) == 0;
}