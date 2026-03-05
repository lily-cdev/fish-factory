#include <prepping.h>

uint32_t Lookup_Table[32];
SDL_Surface* None_Surfaces[10];

int Step_Noise(void* C1) {
	int Index = (int)(intptr_t)C1;
	SDL_Surface* Noise_Surface = SDL_CreateSurface(Settings.Screen_Size * 1200, Settings.Screen_Size * 1200,
		SDL_PIXELFORMAT_RGBA8888);
	SDL_LockSurface(Noise_Surface);
	uint32_t* Pixels = (uint32_t*)(Noise_Surface->pixels);
	for (int C2 = 0; C2 < sqr(Settings.Screen_Size * 1200); C2++, Pixels++) {
		Tick_State();
		*Pixels = Lookup_Table[(Core.State & 31)];
	}
	SDL_UnlockSurface(Noise_Surface);
	None_Surfaces[Index] = Noise_Surface;
	return 0;
}

void Preclear_Temporaries() {
	memset(Data.Animation_Grid, LDE_INVALID, sizeof(Data.Animation_Grid));
}

void Render_Loadscreen() {
	Set_Renderer_Color(Colors.Pure_White);
	SDL_RenderClear(Core.Renderer);
	Clear_Renderer();
	SDL_Surface* Text_Surface = TTF_RenderText_Blended(Fonts.Logo_Font, "loading assets", 0, Colors.Abyss_Black);
	char Carrier[128];
	struct timespec Spec;
	timespec_get(&Spec, TIME_UTC);
	snprintf(Carrier, sizeof(Carrier), "fun fact: %s.", Metadata.Facts[(int)(Spec.tv_nsec / 1000000) % LDE_FACTS]);
	SDL_FRect Pasting_Rectangle = {
		(Settings.Screen_Size * 320.0f) - (Text_Surface->w * 0.5),
		(Settings.Screen_Size * 180.0f) - (Text_Surface->h * 0.5),
		(float)(Text_Surface->w),
		(float)(Text_Surface->h)
	};
	SDL_Texture* Text_Texture = Surface_To_Texture(Core.Renderer, Text_Surface);
	Render_Texture(Text_Texture, &Pasting_Rectangle);
	SDL_DestroySurface(Text_Surface);
	free_texture(Text_Texture);
	SDL_Surface* Fact_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Carrier, 0, Colors.Abyss_Black);
	SDL_Texture* Fact_Texture = Surface_To_Texture(Core.Renderer, Fact_Surface);
	SDL_FRect Fact_Rectangle = {
		(Settings.Screen_Size * 320.0f) - (Fact_Surface->w * 0.5),
		(Settings.Screen_Size * 10.0f) + Pasting_Rectangle.y + Pasting_Rectangle.h,
		(float)(Fact_Surface->w),
		(float)(Fact_Surface->h)
	};
	Render_Texture(Fact_Texture, &Fact_Rectangle);
	SDL_DestroySurface(Fact_Surface);
	free_texture(Fact_Texture);
	SDL_RenderPresent(Core.Renderer);
	SDL_PumpEvents();
}

void Preload_Noise() {
	Textures.None.Data = malloc(sizeof(SDL_Texture*) * 10);
	Textures.None.Length = 10;
	const SDL_PixelFormatDetails* Pixel_Format = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
	for (int C1 = -16; C1 <= 16; C1++) {
		if (C1 != 0) {
			int Offset = 16;
			if (C1 > 0) {
				Offset = 15;
			}
			Lookup_Table[C1 + Offset] = SDL_MapRGB(Pixel_Format, NULL,
				clamp_c(Colors.Ocean.r + C1, 0, 255),
				clamp_c(Colors.Ocean.g + C1, 0, 255),
				clamp_c(Colors.Ocean.b + C1, 0, 255)
			);
		}
	}
	thrd_t Threads[10];
	for (int C1 = 0; C1 < 10; C1++) {
		thrd_create(&Threads[C1], Step_Noise, (void*)(intptr_t)C1);
	}
	for (int C1 = 0; C1 < 10; C1++) {
		thrd_join(Threads[C1], NULL);
	}
	for (int C1 = 0; C1 < 10; C1++) {
		Textures.None.Data[C1] = Surface_To_Texture(Core.Renderer, None_Surfaces[C1]);
		SDL_SetTextureScaleMode(Textures.None.Data[C1], SDL_SCALEMODE_NEAREST);
		SDL_SetTextureBlendMode(Textures.None.Data[C1], SDL_BLENDMODE_BLEND);
		SDL_DestroySurface(None_Surfaces[C1]);
	}
	const SDL_Color Fire_Colors[4] = {
		{ 255, 140, 0 },
		{ 255, 163, 51 },
		{ 255, 205, 6 },
		{ 0, 0, 0 }
	};
	Textures.Fire.Data = malloc(sizeof(SDL_Texture*) * 10);
	Textures.Fire.Length = 10;
	SDL_Surface* Fire_Surfaces[10];
	uint32_t Random = (uint32_t)(SDL_GetTicks() & 255);
	for (int C1 = 0; C1 < 10; C1++) {
		Fire_Surfaces[C1] = SDL_CreateSurface(Settings.Screen_Size * LDE_TILESIZE,
			Settings.Screen_Size * LDE_TILESIZE, SDL_PIXELFORMAT_RGBA8888);
		SDL_LockSurface(Fire_Surfaces[C1]);
		uint32_t* Pixels = (uint32_t*)(Fire_Surfaces[C1]->pixels);
		for (int C2 = 0; C2 < sqr(Settings.Screen_Size * LDE_TILESIZE); C2++) {
			Tick_State();
			Pixels[C2] = SDL_MapRGB(Pixel_Format, NULL, Fire_Colors[(Random & 3)].r, Fire_Colors[(Random & 3)].g,
				Fire_Colors[(Random & 3)].b);
		}
		SDL_UnlockSurface(Fire_Surfaces[C1]);
		Textures.Fire.Data[C1] = Surface_To_Texture(Core.Renderer, Fire_Surfaces[C1]);
		SDL_SetTextureScaleMode(Textures.Fire.Data[C1], SDL_SCALEMODE_NEAREST);
		SDL_SetTextureBlendMode(Textures.Fire.Data[C1], SDL_BLENDMODE_BLEND);
		SDL_DestroySurface(Fire_Surfaces[C1]);
	}
}