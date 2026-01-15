#include <prepping.h>

void Load_Modular(const char* Path, Texture_Array* Yield, int Size) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "Assets/Core/Images/%s.bmp", Path);
	SDL_FPoint Tile_Centerpoint = { LDE_TILESIZE * Size * 0.5f, LDE_TILESIZE * Size * 0.5f };
	Yield->Data = malloc(sizeof(SDL_Texture*) * 16);
	Yield->Length = 16;
	SDL_Surface* Spritesheet_Surface = Load_BMP(Buffer);
	if (Spritesheet_Surface == NULL) {
		puts("fail");
	}
	SDL_Texture* Spritesheet_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Spritesheet_Surface);
	Texture_Array Subtextures;
	Subtextures.Data = malloc(sizeof(SDL_Texture*) * 6);
	Subtextures.Length = 6;
	for (int Counter = 0; Counter < 6; Counter++) {
		Subtextures.Data[Counter] = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
		SDL_FRect Separating_Rectangle = {
			(float)(LDE_TILESIZE * Size) * Counter,
			0.0f,
			(float)(LDE_TILESIZE * Size),
			(float)(LDE_TILESIZE * Size)
		};
		SDL_SetRenderTarget(Core.Renderer, Subtextures.Data[Counter]);
		SDL_SetTextureBlendMode(Subtextures.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_RenderTexture(Core.Renderer, Spritesheet_Texture, &Separating_Rectangle, NULL);
	}
	SDL_Texture* Isolated_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Isolated_Texture);
	SDL_SetTextureBlendMode(Isolated_Texture, SDL_BLENDMODE_BLEND);
	Render_Texture(Subtextures.Data[0], NULL);
	Yield->Data[0] = Isolated_Texture;
	SDL_Texture* Surrounded_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Surrounded_Texture);
	SDL_SetTextureBlendMode(Surrounded_Texture, SDL_BLENDMODE_BLEND);
	Render_Texture(Subtextures.Data[1], NULL);
	Yield->Data[1] = Surrounded_Texture;
	SDL_Texture* Junction1_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Junction1_Texture);
	SDL_SetTextureBlendMode(Junction1_Texture, SDL_BLENDMODE_BLEND);
	Render_Texture(Subtextures.Data[2], NULL);
	Yield->Data[2] = Junction1_Texture;
	SDL_Texture* Junction2_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Junction2_Texture);
	SDL_SetTextureBlendMode(Junction2_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[2], NULL, NULL, 180, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[3] = Junction2_Texture;
	SDL_Texture* Junction3_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Junction3_Texture);
	SDL_SetTextureBlendMode(Junction3_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[2], NULL, NULL, 90, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[4] = Junction3_Texture;
	SDL_Texture* Junction4_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Junction4_Texture);
	SDL_SetTextureBlendMode(Junction4_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[2], NULL, NULL, 270, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[5] = Junction4_Texture;
	SDL_Texture* Vertical_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Vertical_Texture);
	SDL_SetTextureBlendMode(Vertical_Texture, SDL_BLENDMODE_BLEND);
	Render_Texture(Subtextures.Data[3], NULL);
	Yield->Data[6] = Vertical_Texture;
	SDL_Texture* Horizontal_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Horizontal_Texture);
	SDL_SetTextureBlendMode(Horizontal_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[3], NULL, NULL, 90, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[7] = Horizontal_Texture;
	SDL_Texture* Corner1_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Corner1_Texture);
	SDL_SetTextureBlendMode(Corner1_Texture, SDL_BLENDMODE_BLEND);
	Render_Texture(Subtextures.Data[4], NULL);
	Yield->Data[8] = Corner1_Texture;
	SDL_Texture* Corner2_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Corner2_Texture);
	SDL_SetTextureBlendMode(Corner2_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[4], NULL, NULL, 90, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[9] = Corner2_Texture;
	SDL_Texture* Corner3_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Corner3_Texture);
	SDL_SetTextureBlendMode(Corner3_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[4], NULL, NULL, 180, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[10] = Corner3_Texture;
	SDL_Texture* Corner4_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Corner4_Texture);
	SDL_SetTextureBlendMode(Corner4_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[4], NULL, NULL, 270, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[11] = Corner4_Texture;
	SDL_Texture* Cap1_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Cap1_Texture);
	SDL_SetTextureBlendMode(Cap1_Texture, SDL_BLENDMODE_BLEND);
	Render_Texture(Subtextures.Data[5], NULL);
	Yield->Data[12] = Cap1_Texture;
	SDL_Texture* Cap2_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Cap2_Texture);
	SDL_SetTextureBlendMode(Cap2_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[5], NULL, NULL, 90, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[13] = Cap2_Texture;
	SDL_Texture* Cap3_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Cap3_Texture);
	SDL_SetTextureBlendMode(Cap3_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[5], NULL, NULL, 180, &Tile_Centerpoint, SDL_FLIP_NONE);
	Yield->Data[14] = Cap3_Texture;
	SDL_Texture* Cap4_Texture = SDL_GenerateTexture(Core.Renderer, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
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
	snprintf(Buffer, sizeof(Buffer), "Assets/Core/Images/%s.bmp", Path);
	Yield->Length = 4;
	Yield->Data = malloc(sizeof(SDL_Texture*) * 4);
	SDL_Surface* Primary_Surface = Load_BMP(Buffer);
	float Maximum = Primary_Surface->w;
	if (Primary_Surface->h > Maximum) {
		Maximum = Primary_Surface->h;
	}
	SDL_FPoint Tile_Centerpoint = { Maximum * 0.5f, Maximum * 0.5f };
	Yield->Data[0] = SDL_GenerateTextureFromSurface(Core.Renderer, Primary_Surface);
	SDL_DestroySurface(Primary_Surface);
	for (int Counter = 1; Counter < 4; Counter++) {
		Yield->Data[Counter] = SDL_GenerateTexture(Core.Renderer, Maximum, Maximum);
		SDL_SetTextureBlendMode(Yield->Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core.Renderer, Yield->Data[Counter]);
		SDL_RenderTextureRotated(Core.Renderer, Yield->Data[0], NULL,
			NULL, Counter * 90, &Tile_Centerpoint, SDL_FLIP_NONE);
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
}

void Load_Mirrored_Button(const char* Path, Texture2_Array* Yield, SDL_FRect* Rectangle) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "Assets/Core/Images/%s.bmp", Path);
	Yield->Length = 2;
	Yield->Data = malloc(sizeof(Texture_Array) * 2);
	for (int Counter = 0; Counter < 2; Counter++) {
		Yield->Data[Counter].Data = malloc(sizeof(SDL_Texture*) * 2);
		Yield->Data[Counter].Length = 2;
	}
	SDL_Surface* Carrying_Surface = Load_BMP(Buffer);
	if (Carrying_Surface == NULL) {
		puts("fail");
	}
	SDL_Texture* Carrying_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Carrying_Surface);
	SDL_Texture* First_Texture = SDL_GenerateTexture(Core.Renderer, Carrying_Surface->w * 0.5, Carrying_Surface->h);
	SDL_FRect Separating_Rectangle = {
		0.0f,
		0.0f,
		(float)(Carrying_Surface->w * 0.5),
		(float)(Carrying_Surface->h)
	};
	Rectangle->w = (Separating_Rectangle.w / 6) * Settings.Screen_Size;
	Rectangle->h = (Separating_Rectangle.h / 6) * Settings.Screen_Size;
	SDL_SetTextureBlendMode(First_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, First_Texture);
	SDL_RenderTexture(Core.Renderer, Carrying_Texture, &Separating_Rectangle, NULL);
	Yield->Data[0].Data[0] = First_Texture;
	SDL_Texture* Second_Texture = SDL_GenerateTexture(Core.Renderer, Carrying_Surface->w * 0.5, Carrying_Surface->h);
	SDL_SetTextureBlendMode(Second_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Second_Texture);
	SDL_RenderTextureRotated(Core.Renderer, Carrying_Texture, &Separating_Rectangle, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	Yield->Data[1].Data[0] = Second_Texture;
	Separating_Rectangle.x = Carrying_Surface->w * 0.5;
	SDL_Texture* Third_Texture = SDL_GenerateTexture(Core.Renderer, Carrying_Surface->w * 0.5, Carrying_Surface->h);
	SDL_SetTextureBlendMode(Third_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Third_Texture);
	SDL_RenderTexture(Core.Renderer, Carrying_Texture, &Separating_Rectangle, NULL);
	Yield->Data[0].Data[1] = Third_Texture;
	SDL_Texture* Fourth_Texture = SDL_GenerateTexture(Core.Renderer, Carrying_Surface->w * 0.5, Carrying_Surface->h);
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
	snprintf(Buffer, sizeof(Buffer), "Assets/Core/Images/%s.bmp", Path);
	Yield->Data = malloc(sizeof(SDL_Texture*) * 2);
	Yield->Length = 2;
	SDL_Surface* Primary_Surface = Load_BMP(Buffer);
	if (Primary_Surface == NULL) {
		puts("fail");
	}
	Rectangle->w = (Primary_Surface->w / 6) * Settings.Screen_Size;
	Rectangle->h = (Primary_Surface->h / 6) * Settings.Screen_Size;
	SDL_Texture* Primary_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Primary_Surface);
	SDL_DestroySurface(Primary_Surface);
	Yield->Data[0] = Primary_Texture;
	SDL_Texture* Derivative_Texture = SDL_GenerateTexture(Core.Renderer, Rectangle->w, Rectangle->h);
	SDL_SetTextureBlendMode(Derivative_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Derivative_Texture);
	SDL_RenderTextureRotated(Core.Renderer, Primary_Texture, NULL, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	Yield->Data[1] = Derivative_Texture;
	SDL_SetRenderTarget(Core.Renderer, NULL);
}

void Load_Animated(const char* Path, Texture_Array* Yield, int Height, bool Inverted, int* Rotationals) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "Assets/Core/Images/%s.bmp", Path);
	SDL_Texture* Carrying_Texture = IMG_GenerateTexture(Core.Renderer, Buffer);
	float Full_Width = 0;
	float Full_Height = 0;
	SDL_GetTextureSize(Carrying_Texture, &Full_Width, &Full_Height);
	int Total_Chunks = floor(Full_Height / (Height * 240));
	int Chunks = 1;
	for (int Counter1 = 0; Counter1 < Total_Chunks; Counter1++, Chunks++) {
		for (int Counter2 = 0; Counter2 < intlen(Rotationals); Counter2++) {
			if (Counter1 == Rotationals[Counter2]) {
				Chunks += 3;
				break;
			}
		}
	}
	Yield->Data = malloc(sizeof(SDL_Texture*) * Chunks);
	Yield->Length = Chunks;
	int Index = 1;
	for (int Counter1 = 0; Counter1 < Total_Chunks; Counter1++) {
		SDL_Texture* Subtexture = SDL_GenerateTexture(Core.Renderer, Full_Width, Height * 240);
		SDL_SetTextureBlendMode(Subtexture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core.Renderer, Subtexture);
		SDL_FRect Splitting_Rectangle = {
			0.0f,
			Counter1 * Height * 240.0f,
			(float)(Full_Width),
			Height * 240.0f
		};
		SDL_RenderTexture(Core.Renderer, Carrying_Texture, &Splitting_Rectangle, NULL);
		SDL_SetRenderTarget(Core.Renderer, NULL);
		bool Matched = false;
		for (int Counter2 = 0; Counter2 < intlen(Rotationals); Counter2++) {
			if (Counter1 == Rotationals[Counter2]) {
				Matched = true;
				break;
			}
		}
		if (Matched) {
			SDL_FPoint Centerpoint = { Height * 120.0f, Height * 120.0f };
			for (int Counter2 = 0; Counter2 < 4; Counter2++) {
				SDL_Texture* Subtexture2 = SDL_GenerateTexture(Core.Renderer, Height * 240, Height * 240);
				SDL_SetTextureBlendMode(Subtexture2, SDL_BLENDMODE_BLEND);
				SDL_SetRenderTarget(Core.Renderer, Subtexture2);
				SDL_RenderTextureRotated(Core.Renderer, Subtexture, NULL, NULL, 90 * Counter2, &Centerpoint, SDL_FLIP_NONE);
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
	SDL_Texture* Root_Texture = SDL_GenerateTexture(Core.Renderer, Full_Width, Height * 240);
	SDL_SetTextureBlendMode(Root_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Root_Texture);
	int Minimum = 1;
	int Maximum = Yield->Length - 1;
	while (Minimum <= Maximum) {
		int Selector = Minimum;
		if (Inverted) {
			Selector = Maximum;
		}
		Render_Texture(Yield->Data[Selector], NULL);
		if (Inverted) {
			Maximum--;
		} else {
			Minimum++;
		}
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
	Yield->Data[0] = Root_Texture;
	free_texture(Carrying_Texture);
}

void Load_Animated_Rotational(const char* Path, Texture2_Array* Yield, int Height, bool Inverted, int* Rotationals) {
	Yield->Data = malloc(sizeof(Texture_Array) * 4);
	Yield->Length = 4;
	for (int Counter1 = 0; Counter1 < 4; Counter1++) {
		Texture_Array Subyield;
		Load_Animated(Path, &Subyield, Height, Inverted, Rotationals);
		Yield->Data[Counter1].Data = malloc(sizeof(SDL_Texture*) * Subyield.Length);
		Yield->Data[Counter1].Length = Subyield.Length;
		float X;
		float Y;
		float Maximum;
		for (int Counter2 = 0; Counter2 < Subyield.Length; Counter2++) {
			SDL_GetTextureSize(Subyield.Data[Counter2], &X, &Y);
			Maximum = X > Y ? X : Y;
			SDL_FPoint Center = { Maximum * 0.5f, Maximum * 0.5f };
			Yield->Data[Counter1].Data[Counter2] = SDL_GenerateTexture(Core.Renderer, Maximum, Maximum);
			SDL_SetTextureBlendMode(Yield->Data[Counter1].Data[Counter2], SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(Core.Renderer, Yield->Data[Counter1].Data[Counter2]);
			SDL_RenderTextureRotated(Core.Renderer, Subyield.Data[Counter2], NULL, NULL, Counter1 * 90, &Center,
				SDL_FLIP_NONE);
			SDL_SetRenderTarget(Core.Renderer, NULL);
		}
		Clear_Texture_Array(&Subyield);
	}
}

SDL_Texture* Preload_Sidebutton(const char* Path, SDL_FRect* Rectangle, float Y) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "Assets/Core/Images/UI/Sidebar/%s.bmp", Path);
	SDL_Surface* Surface = Load_BMP(Buffer);
	if (Surface == NULL) {
		puts("fail");
	}
	Rectangle->x = (float)(660 - (Surface->w / 6)) * Settings.Screen_Size;
	Rectangle->y = Y * Settings.Screen_Size;
	Rectangle->w = (float)(Surface->w / 6) * Settings.Screen_Size;
	Rectangle->h = (float)(Surface->h / 6) * Settings.Screen_Size;
	SDL_Texture* Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Surface);
	SDL_DestroySurface(Surface);
	return Texture;
}

SDL_Texture* Preload_Texture(const char* Path) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "Assets/Core/Images/%s.bmp", Path);
	SDL_Surface* Carrying_Surface = Load_BMP(Buffer);
	if (Carrying_Surface == NULL) {
		puts("fail");
	}
	SDL_Texture* Carrying_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	return Carrying_Texture;
}