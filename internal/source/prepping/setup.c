#include <prepping.h>

void Preclear_Temporaries() {
	for (int X = 0; X < ktn_grid_size; X++) {
		for (int Y = 0; Y < ktn_grid_size; Y++) {
			for (int Z = 0; Z < sizeof(Data.Animation_Grid[X][Y]) / sizeof(Data.Animation_Grid[X][Y][0]); Z++) {
				Data.Animation_Grid[X][Y][Z] = ktn_invalid;
			}
		}
	}
}

void Render_Loadscreen(const char* Line) {
	Set_Renderer_Color(Colors.Pure_White);
	SDL_RenderClear(Core.Renderer);
	Clear_Renderer();
	Render_Texture(Temporary.Load_Text, &Temporary.Load_Text_Rect);
	uint64_t Carrier = SDL_GetTicks();
	SDL_RenderTextureRotated(Core.Renderer, Temporary.Spinner, NULL, &Temporary.Spinner_Rect, (Carrier & 1023) * 0.3515625f,
		NULL, SDL_FLIP_NONE);
	SDL_RenderPresent(Core.Renderer);
	SDL_PumpEvents();
	SDL_FlushEvents(SDL_EVENT_FIRST, SDL_EVENT_LAST);
}

void Preload_Noise() {
	Textures.None.Data = malloc(sizeof(SDL_Texture*) * 10);
	Textures.None.Length = 10;
	uint32_t Lookup_Table[32];
	const SDL_PixelFormatDetails* Pixel_Format = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
	for (int C1 = -16; C1 <= 16; C1++) {
		if (C1 != 0) {
			int Offset = 16;
			if (C1 > 0) {
				Offset = 15;
			}
			Lookup_Table[C1 + Offset] = SDL_MapRGBA(Pixel_Format, NULL,
				ktn_clamp(Colors.Ocean.r + C1, 0, 255),
				ktn_clamp(Colors.Ocean.g + C1, 0, 255),
				ktn_clamp(Colors.Ocean.b + C1, 0, 255),
				SDL_ALPHA_OPAQUE
			);
		}
	}
	char Buffer[64];
	for (int C1 = 0; C1 < 10; C1++) {
		snprintf(Buffer, sizeof(Buffer), "cache/noise%d.bmp", C1 + 1);
		SDL_Surface* Carrier;
		FILE* Cache_File = fopen(Buffer, "r");
		if (Cache_File == NULL) {
			Carrier = SDL_CreateSurface(ktn_ocean_size, ktn_ocean_size, SDL_PIXELFORMAT_RGBA8888);
			SDL_LockSurface(Carrier);
			uint32_t* Pixels = (uint32_t*)(Carrier->pixels);
			for (int C2 = 0; C2 < ktn_sqr(ktn_ocean_size); C2++) {
				ktn_tick();
				Pixels[C2] = Lookup_Table[(Core.State & 31)];
			}
			SDL_UnlockSurface(Carrier);
			Save_BMP(Buffer, Carrier);
		} else {
			fclose(Cache_File);
			ktn_load_bmp(Carrier, Buffer);
		}
		Textures.None.Data[C1] = Surface_To_Texture(Carrier);
		SDL_DestroySurface(Carrier);
	}
	const uint32_t Fire_Colors[4] = {
		SDL_MapRGBA(Pixel_Format, NULL, 255, 140, 0, SDL_ALPHA_OPAQUE),
		SDL_MapRGBA(Pixel_Format, NULL, 255, 163, 51, SDL_ALPHA_OPAQUE),
		SDL_MapRGBA(Pixel_Format, NULL, 255, 205, 6, SDL_ALPHA_OPAQUE),
		SDL_MapRGBA(Pixel_Format, NULL, 0, 0, 0, SDL_ALPHA_OPAQUE)
	};
	Textures.Fire.Data = malloc(sizeof(SDL_Texture*) * 10);
	Textures.Fire.Length = 10;
	SDL_Surface* Fire_Surfaces[10];
	for (int C1 = 0; C1 < 10; C1++) {
		Fire_Surfaces[C1] = SDL_CreateSurface(Settings.Scalar * ktn_tile_size, Settings.Scalar * ktn_tile_size,
			SDL_PIXELFORMAT_RGBA8888);
		SDL_LockSurface(Fire_Surfaces[C1]);
		uint32_t* Pixels = (uint32_t*)(Fire_Surfaces[C1]->pixels);
		for (int C2 = 0; C2 < ktn_sqr(Settings.Scalar * ktn_tile_size); C2++) {
			ktn_tick();
			Pixels[C2] = Fire_Colors[(Core.State & 3)];
		}
		SDL_UnlockSurface(Fire_Surfaces[C1]);
		Textures.Fire.Data[C1] = Surface_To_Texture(Fire_Surfaces[C1]);
		SDL_SetTextureScaleMode(Textures.Fire.Data[C1], SDL_SCALEMODE_NEAREST);
		SDL_SetTextureBlendMode(Textures.Fire.Data[C1], SDL_BLENDMODE_BLEND);
		SDL_DestroySurface(Fire_Surfaces[C1]);
	}
}

void Preload_Lights() {
	int Max_Rad = 0;
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		for (int C2 = 0; C2 < Metadata.Machines[C1].Light_Ct; C2++) {
			Max_Rad = max(Metadata.Machines[C1].Light_Range[C2], Max_Rad);
		}
	}
	Cache.Light_Grad = New_Texture(Max_Rad * 2, Max_Rad * 2);
	SDL_SetRenderTarget(Core.Renderer, Cache.Light_Grad);
	Set_Renderer_Color(Colors.Abyss_Black);
	SDL_RenderClear(Core.Renderer);
	for (int C1 = 0; C1 < ktn_sqr(Max_Rad * 2); C1++) {
		Point Applied = { C1 % (Max_Rad * 2), floorf(C1 / (Max_Rad * 2)) };
		float Distance = sqrtf(ktn_sqr(Applied.X - Max_Rad) + ktn_sqr(Applied.Y - Max_Rad));
		if (Distance < Max_Rad) {
			uint8_t Intensity = (Distance / Max_Rad) * 127.0f;
			SDL_SetRenderDrawColor(Core.Renderer, 0, 0, 0, Intensity);
			SDL_RenderPoint(Core.Renderer, Applied.X, Applied.Y);
		}
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
	SDL_BlendMode Lighting = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_MINIMUM,
		SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_MINIMUM);
	SDL_SetTextureBlendMode(Cache.Light_Grad, Lighting);
	Clear_Renderer();
}