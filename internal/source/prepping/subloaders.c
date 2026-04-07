#include <prepping.h>

void Load_Modular(const char* Path, Texture_Array* Yield, int Size) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "assets/core/images/%s.bmp", Path);
	SDL_FPoint Tile_Centerpoint = { LDE_TILESIZE * Size * 0.5f, LDE_TILESIZE * Size * 0.5f };
	Yield->Data = malloc(sizeof(SDL_Texture*) * 16);
	Yield->Length = 16;
	SDL_Surface* Spritesheet_Surface;
	load_bmp(Spritesheet_Surface, Buffer);
	SDL_Texture* Spritesheet_Texture = Surface_To_Texture(Core.Renderer, Spritesheet_Surface);
	Texture_Array Subtextures;
	Subtextures.Data = malloc(sizeof(SDL_Texture*) * 6);
	Subtextures.Length = 6;
	for (int C1 = 0; C1 < 6; C1++) {
		Subtextures.Data[C1] = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
		SDL_FRect Separating_Rectangle = {
			(float)(LDE_TILESIZE * Size) * C1,
			0.0f,
			(float)(LDE_TILESIZE * Size),
			(float)(LDE_TILESIZE * Size)
		};
		SDL_SetRenderTarget(Core.Renderer, Subtextures.Data[C1]);
		SDL_SetTextureBlendMode(Subtextures.Data[C1], SDL_BLENDMODE_BLEND);
		SDL_RenderTexture(Core.Renderer, Spritesheet_Texture, &Separating_Rectangle, NULL);
	}
	SDL_Texture* Isolated_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Isolated_Texture);
	SDL_SetTextureBlendMode(Isolated_Texture, SDL_BLENDMODE_BLEND);
	Render_Texture(Subtextures.Data[0], NULL);
	Yield->Data[0] = Isolated_Texture;
	SDL_Texture* Surrounded_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Surrounded_Texture);
	SDL_SetTextureBlendMode(Surrounded_Texture, SDL_BLENDMODE_BLEND);
	Render_Texture(Subtextures.Data[1], NULL);
	Yield->Data[1] = Surrounded_Texture;
	SDL_Texture* Junction1_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Junction1_Texture);
	SDL_SetTextureBlendMode(Junction1_Texture, SDL_BLENDMODE_BLEND);
	Render_Texture(Subtextures.Data[2], NULL);
	Yield->Data[2] = Junction1_Texture;
	SDL_Texture* Junction2_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Junction2_Texture);
	SDL_SetTextureBlendMode(Junction2_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[2], NULL, NULL, 180, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[3] = Junction2_Texture;
	SDL_Texture* Junction3_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Junction3_Texture);
	SDL_SetTextureBlendMode(Junction3_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[2], NULL, NULL, 90, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[4] = Junction3_Texture;
	SDL_Texture* Junction4_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Junction4_Texture);
	SDL_SetTextureBlendMode(Junction4_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[2], NULL, NULL, 270, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[5] = Junction4_Texture;
	SDL_Texture* Vertical_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Vertical_Texture);
	SDL_SetTextureBlendMode(Vertical_Texture, SDL_BLENDMODE_BLEND);
	Render_Texture(Subtextures.Data[3], NULL);
	Yield->Data[6] = Vertical_Texture;
	SDL_Texture* Horizontal_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Horizontal_Texture);
	SDL_SetTextureBlendMode(Horizontal_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[3], NULL, NULL, 90, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[7] = Horizontal_Texture;
	SDL_Texture* Corner1_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Corner1_Texture);
	SDL_SetTextureBlendMode(Corner1_Texture, SDL_BLENDMODE_BLEND);
	Render_Texture(Subtextures.Data[4], NULL);
	Yield->Data[8] = Corner1_Texture;
	SDL_Texture* Corner2_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Corner2_Texture);
	SDL_SetTextureBlendMode(Corner2_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[4], NULL, NULL, 90, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[9] = Corner2_Texture;
	SDL_Texture* Corner3_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Corner3_Texture);
	SDL_SetTextureBlendMode(Corner3_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[4], NULL, NULL, 180, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[10] = Corner3_Texture;
	SDL_Texture* Corner4_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Corner4_Texture);
	SDL_SetTextureBlendMode(Corner4_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[4], NULL, NULL, 270, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[11] = Corner4_Texture;
	SDL_Texture* Cap1_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Cap1_Texture);
	SDL_SetTextureBlendMode(Cap1_Texture, SDL_BLENDMODE_BLEND);
	Render_Texture(Subtextures.Data[5], NULL);
	Yield->Data[12] = Cap1_Texture;
	SDL_Texture* Cap2_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Cap2_Texture);
	SDL_SetTextureBlendMode(Cap2_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[5], NULL, NULL, 90, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[13] = Cap2_Texture;
	SDL_Texture* Cap3_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Cap3_Texture);
	SDL_SetTextureBlendMode(Cap3_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[5], NULL, NULL, 180, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[14] = Cap3_Texture;
	SDL_Texture* Cap4_Texture = New_Texture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Cap4_Texture);
	SDL_SetTextureBlendMode(Cap4_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[5], NULL, NULL, 270, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[15] = Cap4_Texture;
	Clear_Texture_Array(&Subtextures);
	SDL_DestroySurface(Spritesheet_Surface);
	free_texture(Spritesheet_Texture);
	SDL_SetRenderTarget(Core.Renderer, NULL);
}

void Load_Rotational(const char* Path, Texture_Array* Yield) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "assets/core/images/%s.bmp", Path);
	Yield->Length = 4;
	Yield->Data = malloc(sizeof(SDL_Texture*) * 4);
	SDL_Surface* Primary_Surface;
	load_bmp(Primary_Surface, Buffer);
	float Maximum = Primary_Surface->w;
	if (Primary_Surface->h > Maximum) {
		Maximum = Primary_Surface->h;
	}
	SDL_FPoint Tile_Centerpoint = { Maximum * 0.5f, Maximum * 0.5f };
	Yield->Data[0] = Surface_To_Texture(Core.Renderer, Primary_Surface);
	SDL_DestroySurface(Primary_Surface);
	for (int C1 = 1; C1 < 4; C1++) {
		Yield->Data[C1] = New_Texture(Core.Renderer, Maximum, Maximum);
		SDL_SetTextureBlendMode(Yield->Data[C1], SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core.Renderer, Yield->Data[C1]);
		SDL_RenderTextureRotated(Core.Renderer, Yield->Data[0], NULL, NULL, C1 * 90, &Tile_Centerpoint, SDL_FLIP_NONE);
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
}

void Load_Mirrored_Button(const char* Path, Texture2_Array* Yield, SDL_FRect* Rectangle) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "assets/core/images/%s.bmp", Path);
	Yield->Length = 2;
	Yield->Data = malloc(sizeof(Texture_Array) * 2);
	for (int C1 = 0; C1 < 2; C1++) {
		Yield->Data[C1].Data = malloc(sizeof(SDL_Texture*) * 2);
		Yield->Data[C1].Length = 2;
	}
	SDL_Surface* Carrying_Surface;
	load_bmp(Carrying_Surface, Buffer);
	SDL_Texture* Carrying_Texture = Surface_To_Texture(Core.Renderer, Carrying_Surface);
	SDL_Texture* First_Texture = New_Texture(Core.Renderer, Carrying_Surface->w * 0.5, Carrying_Surface->h);
	SDL_FRect Separating_Rectangle = {
		0.0f,
		0.0f,
		(float)(Carrying_Surface->w * 0.5),
		(float)(Carrying_Surface->h)
	};
	Rectangle->w = (Separating_Rectangle.w / 6) * Settings.Scalar;
	Rectangle->h = (Separating_Rectangle.h / 6) * Settings.Scalar;
	SDL_SetTextureBlendMode(First_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, First_Texture);
	SDL_RenderTexture(Core.Renderer, Carrying_Texture, &Separating_Rectangle, NULL);
	Yield->Data[0].Data[0] = First_Texture;
	SDL_Texture* Second_Texture = New_Texture(Core.Renderer, Carrying_Surface->w * 0.5, Carrying_Surface->h);
	SDL_SetTextureBlendMode(Second_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Second_Texture);
	SDL_RenderTextureRotated(Core.Renderer, Carrying_Texture, &Separating_Rectangle, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	Yield->Data[1].Data[0] = Second_Texture;
	Separating_Rectangle.x = Carrying_Surface->w * 0.5;
	SDL_Texture* Third_Texture = New_Texture(Core.Renderer, Carrying_Surface->w * 0.5, Carrying_Surface->h);
	SDL_SetTextureBlendMode(Third_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Third_Texture);
	SDL_RenderTexture(Core.Renderer, Carrying_Texture, &Separating_Rectangle, NULL);
	Yield->Data[0].Data[1] = Third_Texture;
	SDL_Texture* Fourth_Texture = New_Texture(Core.Renderer, Carrying_Surface->w * 0.5, Carrying_Surface->h);
	SDL_SetTextureBlendMode(Fourth_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Fourth_Texture);
	SDL_RenderTextureRotated(Core.Renderer, Carrying_Texture, &Separating_Rectangle, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	Yield->Data[1].Data[1] = Fourth_Texture;
	SDL_DestroySurface(Carrying_Surface);
	free_texture(Carrying_Texture);
	SDL_SetRenderTarget(Core.Renderer, NULL);
}

void Load_Mirrored(const char* Path, Texture_Array* Yield, SDL_FRect* Rectangle) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "assets/core/images/%s.bmp", Path);
	Yield->Data = malloc(sizeof(SDL_Texture*) * 2);
	Yield->Length = 2;
	SDL_Surface* Primary_Surface;
	load_bmp(Primary_Surface, Buffer);
	Rectangle->w = (Primary_Surface->w / 6.0f) * Settings.Scalar;
	Rectangle->h = (Primary_Surface->h / 6.0f) * Settings.Scalar;
	SDL_Texture* Primary_Texture = Surface_To_Texture(Core.Renderer, Primary_Surface);
	SDL_DestroySurface(Primary_Surface);
	Yield->Data[0] = Primary_Texture;
	SDL_Texture* Derivative_Texture = New_Texture(Core.Renderer, Rectangle->w, Rectangle->h);
	SDL_SetTextureBlendMode(Derivative_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Derivative_Texture);
	SDL_RenderTextureRotated(Core.Renderer, Primary_Texture, NULL, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	Yield->Data[1] = Derivative_Texture;
	SDL_SetRenderTarget(Core.Renderer, NULL);
}

void Load_Animated(const char* Path, Texture_Array* Yield, int Height, bool Inverted, const int* Rotationals) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "assets/core/images/%s.bmp", Path);
	SDL_Texture* Carrying_Texture = IMG_To_Texture(Core.Renderer, Buffer);
	float Full_Width = 0, Full_Height = 0;
	SDL_GetTextureSize(Carrying_Texture, &Full_Width, &Full_Height);
	int Total_Chunks = floor(Full_Height / (Height * 240)), Chunks = 1;
	for (int C1 = 0; C1 < Total_Chunks; C1++, Chunks++) {
		for (int C2 = 0; C2 < intlen(Rotationals); C2++) {
			if (C1 == Rotationals[C2]) {
				Chunks += 3;
				break;
			}
		}
	}
	Yield->Data = malloc(sizeof(SDL_Texture*) * Chunks);
	Yield->Length = Chunks;
	int Index = 1;
	for (int C1 = 0; C1 < Total_Chunks; C1++) {
		SDL_Texture* Subtexture = New_Texture(Core.Renderer, Full_Width, Height * 240);
		SDL_SetTextureBlendMode(Subtexture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core.Renderer, Subtexture);
		SDL_FRect Splitting_Rectangle = {
			0.0f,
			C1 * Height * 240.0f,
			(float)(Full_Width),
			Height * 240.0f
		};
		SDL_RenderTexture(Core.Renderer, Carrying_Texture, &Splitting_Rectangle, NULL);
		SDL_SetRenderTarget(Core.Renderer, NULL);
		bool Matched = false;
		for (int C2 = 0; C2 < intlen(Rotationals); C2++) {
			if (C1 == Rotationals[C2]) {
				Matched = true;
				break;
			}
		}
		if (Matched) {
			SDL_FPoint Centerpoint = { Height * 120.0f, Height * 120.0f };
			for (int C2 = 0; C2 < 4; C2++) {
				SDL_Texture* Subtexture2 = New_Texture(Core.Renderer, Height * 240, Height * 240);
				SDL_SetTextureBlendMode(Subtexture2, SDL_BLENDMODE_BLEND);
				SDL_SetRenderTarget(Core.Renderer, Subtexture2);
				SDL_RenderTextureRotated(Core.Renderer, Subtexture, NULL, NULL, 90 * C2, &Centerpoint, SDL_FLIP_NONE);
				Yield->Data[Index] = Subtexture2;
				Index++;
			}
			SDL_SetRenderTarget(Core.Renderer, NULL);
			free_texture(Subtexture);
		} else {
			Yield->Data[Index] = Subtexture;
			Index++;
		}
	}
	SDL_Texture* Root_Texture = New_Texture(Core.Renderer, Full_Width, Height * 240);
	SDL_SetTextureBlendMode(Root_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Root_Texture);
	int Min = 1, Max = Yield->Length - 1;
	while (Min <= Max) {
		int Selector = (Inverted) ? Max : Min;
		Render_Texture(Yield->Data[Selector], NULL);
		(Inverted) ? Max-- : Min++;
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
	Yield->Data[0] = Root_Texture;
	free_texture(Carrying_Texture);
}

void Load_Subanimated(const char* Path, Texture_Array* Yield, int Height) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "assets/core/images/%s.bmp", Path);
	SDL_Texture* Carrier = IMG_To_Texture(Core.Renderer, Buffer);
	Point Chunksize = {
		Carrier->w,
		((int)Carrier->h) / Height
	};
	Yield->Length = Height;
	Yield->Data = malloc(sizeof(SDL_Texture*) * Height);
	for (int C1 = 0; C1 < Height; C1++) {
		Yield->Data[C1] = New_Texture(Core.Renderer, Chunksize.X, Chunksize.Y);
		SDL_SetTextureBlendMode(Yield->Data[C1], SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core.Renderer, Yield->Data[C1]);
		SDL_FRect Splitter = {
			0.0f,
			(float)(Chunksize.Y * C1),
			(float)Chunksize.X,
			(float)Chunksize.Y
		};
		SDL_RenderTexture(Core.Renderer, Carrier, &Splitter, NULL);
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
	free_texture(Carrier);
}

void Load_Animated_Rotational(const char* Path, Texture2_Array* Yield, int Height, bool Inverted, const int* Rotationals) {
	Yield->Data = malloc(sizeof(Texture_Array) * 4);
	Yield->Length = 4;
	for (int C1 = 0; C1 < 4; C1++) {
		Texture_Array Subyield;
		Load_Animated(Path, &Subyield, Height, Inverted, Rotationals);
		Yield->Data[C1].Data = malloc(sizeof(SDL_Texture*) * Subyield.Length);
		Yield->Data[C1].Length = Subyield.Length;
		float X = 0, Y = 0, Max = 0;
		for (int C2 = 0; C2 < Subyield.Length; C2++) {
			SDL_GetTextureSize(Subyield.Data[C2], &X, &Y);
			Max = max(X, Y);
			SDL_FPoint Center = { Max * 0.5f, Max * 0.5f };
			Yield->Data[C1].Data[C2] = New_Texture(Core.Renderer, Max, Max);
			SDL_SetTextureBlendMode(Yield->Data[C1].Data[C2], SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(Core.Renderer, Yield->Data[C1].Data[C2]);
			SDL_RenderTextureRotated(Core.Renderer, Subyield.Data[C2], NULL, NULL, C1 * 90, &Center, SDL_FLIP_NONE);
			SDL_SetRenderTarget(Core.Renderer, NULL);
		}
		Clear_Texture_Array(&Subyield);
	}
}

SDL_Texture* Preload_Sidebutton(const char* Path, SDL_FRect* Rectangle, float Y) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "assets/core/images/ui/sidebar/%s.bmp", Path);
	SDL_Surface* Surface;
	load_bmp(Surface, Buffer);
	Rectangle->x = (float)(660 - (Surface->w / 6)) * Settings.Scalar;
	Rectangle->y = Y * Settings.Scalar;
	Rectangle->w = (float)(Surface->w / 6) * Settings.Scalar;
	Rectangle->h = (float)(Surface->h / 6) * Settings.Scalar;
	SDL_Texture* Texture = Surface_To_Texture(Core.Renderer, Surface);
	SDL_DestroySurface(Surface);
	return Texture;
}

SDL_Texture* Preload_Texture(const char* Path) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "assets/core/images/%s.bmp", Path);
	SDL_Surface* Carrier;
	load_bmp(Carrier, Buffer);
	SDL_Texture* Carrying_Texture = Surface_To_Texture(Core.Renderer, Carrier);
	SDL_DestroySurface(Carrier);
	return Carrying_Texture;
}