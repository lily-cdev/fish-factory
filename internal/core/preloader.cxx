#include <preloader.h>

bool Detect_Mouse_Collision(const SDL_FRect &Target) {
	return (Core.Mouse.X >= Target.x && Core.Mouse.X <= Target.x + Target.w &&
		Core.Mouse.Y >= Target.y && Core.Mouse.Y <= Target.y + Target.h);
}

SDL_FRect Buffer_Rectangle(const SDL_FRect &Source, const int X, const int Y) {
	return { Source.x - (X * Settings.Screen_Size), Source.y - (Y * Settings.Screen_Size),
		Source.w + ((X * 2) * Settings.Screen_Size), Source.h + ((Y * 2) * Settings.Screen_Size) };
}

bool Check_Clearance(const int X, const int Y, const int W, const int H) {
	if (X + W > LDE_GRIDSIZE || Y + H > LDE_GRIDSIZE) {
		return false;
	} 
	for (int Counter1 = 0; Counter1 < W; Counter1++) {
		for (int Counter2 = 0; Counter2 < H; Counter2++) {
			if (Data.Visual_Grid[X + Counter1][Y + Counter2] != 0) {
				return false;
			}
		}
	}
	return true;
}

void Fill_Clearance(const int Identifier, const int X, const int Y, const int W, const int H) {
	for (int Counter1 = 0; Counter1 < W; Counter1++) {
		for (int Counter2 = 0; Counter2 < H; Counter2++) {
			Data.Visual_Grid[X + Counter1][Y + Counter2] = Identifier;
			if (Counter1 > 0 || Counter2 > 0) {
				Data_L.Settings_Grid[X + Counter1][Y + Counter2][1] = X;
				Data_L.Settings_Grid[X + Counter1][Y + Counter2][2] = Y;
			}
		}
	}
}

void Update_Tilestack(bool X_Lock, int X, bool Y_Lock, int Y) {
	X = X * Settings.Screen_Size;
	Y = Y * Settings.Screen_Size;
	if (!X_Lock) {
		Rects.Tile_1x1.x = X;
		Rects.Tile_1x2.x = X;
		Rects.Tile_2x1.x = X;
		Rects.Tile_2x2.x = X;
		Rects.Tile_2x3.x = X;
		Rects.Tile_3x2.x = X;
		Rects.Tile_3x3.x = X;
		Rects.Tile_3x4.x = X;
		Rects.Tile_4x3.x = X;
		Rects.Tile_4x6.x = X;
		Rects.Tile_6x4.x = X;
		Rects.Tile_6x8.x = X;
		Rects.Tile_3x3.x = X;
		Rects.Tile_8x6.x = X;
	}
	if (!Y_Lock) {
		Rects.Tile_1x1.y = Y;
		Rects.Tile_1x2.y = Y;
		Rects.Tile_2x1.y = Y;
		Rects.Tile_2x2.y = Y;
		Rects.Tile_2x3.y = Y;
		Rects.Tile_3x2.y = Y;
		Rects.Tile_3x3.y = Y;
		Rects.Tile_3x4.y = Y;
		Rects.Tile_4x3.y = Y;
		Rects.Tile_4x6.y = Y;
		Rects.Tile_6x4.y = Y;
		Rects.Tile_6x8.y = Y;
		Rects.Tile_3x3.y = Y;
		Rects.Tile_8x6.y = Y;
	}
}

std::string Abbreviate_Number(long double Number) {
	int Marker = 0;
	for (int Counter = 0; Counter < LDE_SUFFIXES - 1; Counter++) {
		if (Number >= 1000) {
			Marker++;
			Number = Number / 1000;
		} else {
			break;
		}
	}
	std::ostringstream Temporary_String;
	Temporary_String << std::fixed << std::setprecision(2) << Number;
	std::string Returning_String = Temporary_String.str();
	if (Core.Suffixes[Marker] != 'J') {
		std::string Teritary_String(1, Core.Suffixes[Marker]);
		Returning_String = Returning_String + Teritary_String;
	}
	return Returning_String;
}

std::string Truncate(double Number, int Depth = LDE_INVALID) {
	if (Depth == LDE_INVALID) {
		for (int Counter = 0; Counter < LDE_SUFFIXES - 1; Counter++) {
			if (Number > 1000) {
				Number = Number / 1000;
			} else {
				break;
			}
		}
	} else {
		Number = Number / std::pow(1000, Depth);
	}
	std::ostringstream Temporary_String;
	Temporary_String << std::fixed << std::setprecision(2) << Number;
	std::string Returning_String = Temporary_String.str();
	return Returning_String;
}

Texture_Array Load_Modular(std::string Path, int Size) {
	SDL_FPoint Tile_Centrepoint = { LDE_TILESIZE * Size * 0.5f, LDE_TILESIZE * Size * 0.5f };
	Texture_Array Yield;
	Yield.Data = static_cast<SDL_Texture**>(malloc(sizeof(SDL_Texture*) * 16));
	Yield.Length = 16;
	SDL_Surface* Spritesheet_Surface = Load_BMP(Path.c_str());
	SDL_Texture* Spritesheet_Texture = SDL_GenerateTextureFromSurface(
		Core.Renderer, Spritesheet_Surface);
	Texture_Array Subtextures;
	Subtextures.Data = static_cast<SDL_Texture**>(malloc(sizeof(SDL_Texture*) * 6));
	Subtextures.Length = 6;
	for (int Counter = 0; Counter < 6; Counter++) {
		Subtextures.Data[Counter] = SDL_GenerateTexture(Core.Renderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
		SDL_FRect Separating_Rectangle = {
			static_cast<float>(LDE_TILESIZE * Size) * Counter,
			0.0f,
			static_cast<float>(LDE_TILESIZE * Size),
			static_cast<float>(LDE_TILESIZE * Size)
		};
		SDL_SetRenderTarget(Core.Renderer, Subtextures.Data[Counter]);
		SDL_SetTextureBlendMode(Subtextures.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_RenderTexture(Core.Renderer, Spritesheet_Texture, &Separating_Rectangle, NULL);
	}
	SDL_Texture* Isolated_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Isolated_Texture);
	SDL_SetTextureBlendMode(Isolated_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTexture(Core.Renderer, Subtextures.Data[0], NULL, NULL);
	Yield.Data[0] = Isolated_Texture;
	SDL_Texture* Surrounded_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Surrounded_Texture);
	SDL_SetTextureBlendMode(Surrounded_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTexture(Core.Renderer, Subtextures.Data[1], NULL, NULL);
	Yield.Data[1] = Surrounded_Texture;
	SDL_Texture* Junction1_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Junction1_Texture);
	SDL_SetTextureBlendMode(Junction1_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTexture(Core.Renderer, Subtextures.Data[2], NULL, NULL);
	Yield.Data[2] = Junction1_Texture;
	SDL_Texture* Junction2_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Junction2_Texture);
	SDL_SetTextureBlendMode(Junction2_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[2],
		NULL, NULL, 180, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[3] = Junction2_Texture;
	SDL_Texture* Junction3_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Junction3_Texture);
	SDL_SetTextureBlendMode(Junction3_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[2],
		NULL, NULL, 90, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[4] = Junction3_Texture;
	SDL_Texture* Junction4_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Junction4_Texture);
	SDL_SetTextureBlendMode(Junction4_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[2],
		NULL, NULL, 270, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[5] = Junction4_Texture;
	SDL_Texture* Vertical_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Vertical_Texture);
	SDL_SetTextureBlendMode(Vertical_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTexture(Core.Renderer, Subtextures.Data[3], NULL, NULL);
	Yield.Data[6] = Vertical_Texture;
	SDL_Texture* Horizontal_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Horizontal_Texture);
	SDL_SetTextureBlendMode(Horizontal_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[3],
		NULL, NULL, 90, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[7] = Horizontal_Texture;
	SDL_Texture* Corner1_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Corner1_Texture);
	SDL_SetTextureBlendMode(Corner1_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTexture(Core.Renderer, Subtextures.Data[4], NULL, NULL);
	Yield.Data[8] = Corner1_Texture;
	SDL_Texture* Corner2_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Corner2_Texture);
	SDL_SetTextureBlendMode(Corner2_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[4],
		NULL, NULL, 90, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[9] = Corner2_Texture;
	SDL_Texture* Corner3_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Corner3_Texture);
	SDL_SetTextureBlendMode(Corner3_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[4],
		NULL, NULL, 180, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[10] = Corner3_Texture;
	SDL_Texture* Corner4_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Corner4_Texture);
	SDL_SetTextureBlendMode(Corner4_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[4],
		NULL, NULL, 270, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[11] = Corner4_Texture;
	SDL_Texture* Cap1_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Cap1_Texture);
	SDL_SetTextureBlendMode(Cap1_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTexture(Core.Renderer, Subtextures.Data[5], NULL, NULL);
	Yield.Data[12] = Cap1_Texture;
	SDL_Texture* Cap2_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Cap2_Texture);
	SDL_SetTextureBlendMode(Cap2_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[5],
		NULL, NULL, 90, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[13] = Cap2_Texture;
	SDL_Texture* Cap3_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Cap3_Texture);
	SDL_SetTextureBlendMode(Cap3_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[5],
		NULL, NULL, 180, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[14] = Cap3_Texture;
	SDL_Texture* Cap4_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, LDE_TILESIZE * Size, LDE_TILESIZE * Size);
	SDL_SetRenderTarget(Core.Renderer, Cap4_Texture);
	SDL_SetTextureBlendMode(Cap4_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core.Renderer, Subtextures.Data[5],
		NULL, NULL, 270, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[15] = Cap4_Texture;
	Clear_Texture_Array(&Subtextures);
	SDL_DestroySurface(Spritesheet_Surface);
	SDL_DestroyTexture(Spritesheet_Texture);
	SDL_SetRenderTarget(Core.Renderer, nullptr);
	return Yield;
}

Texture_Array Load_Rotational(std::string Path) {
	Path = "Assets/Core/Images/" + Path + ".bmp";
	Texture_Array Yield;
	Yield.Length = 4;
	Yield.Data = static_cast<SDL_Texture**>(malloc(sizeof(SDL_Texture*) * 4));
	SDL_Surface* Primary_Surface = Load_BMP(Path.c_str());
	float Maximum = Primary_Surface->w;
	if (Primary_Surface->h > Maximum) {
		Maximum = Primary_Surface->h;
	}
	SDL_FPoint Tile_Centrepoint = { Maximum * 0.5f, Maximum * 0.5f };
	Yield.Data[0] = SDL_GenerateTextureFromSurface(Core.Renderer, Primary_Surface);
	SDL_DestroySurface(Primary_Surface);
	for (int Counter = 1; Counter < 4; Counter++) {
		Yield.Data[Counter] = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, Maximum, Maximum);
		SDL_SetTextureBlendMode(Yield.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core.Renderer, Yield.Data[Counter]);
		SDL_RenderTextureRotated(Core.Renderer, Yield.Data[0], NULL,
			NULL, Counter * 90, &Tile_Centrepoint, SDL_FLIP_NONE);
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
	return Yield;
}

Texture2_Array Load_Mirrored_Button(std::string Path, SDL_FRect &Rectangle) {
	Path = "Assets/Core/" + Path + ".bmp";
	Texture2_Array Yield;
	Yield.Length = 2;
	Yield.Data = static_cast<Texture_Array*>(malloc(sizeof(Texture_Array) * 2));
	for (int Counter = 0; Counter < 2; Counter++) {
		Yield.Data[Counter].Data = static_cast<SDL_Texture**>(
			malloc(sizeof(SDL_Texture**) * 2));
		Yield.Data[Counter].Length = 2;
	}
	SDL_Surface* Carrying_Surface = Load_BMP(Path.c_str());
	SDL_Texture* Carrying_Texture = SDL_GenerateTextureFromSurface(
		Core.Renderer, Carrying_Surface);
	SDL_Texture* First_Texture = SDL_GenerateTexture(
		Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, Carrying_Surface->w / 2, Carrying_Surface->h);
	SDL_FRect Separating_Rectangle = { 0.0f, 0.0f, static_cast<float>(
		Carrying_Surface->w / 2), static_cast<float>(Carrying_Surface->h) };
	Rectangle.w = (Separating_Rectangle.w / 6) * Settings.Screen_Size;
	Rectangle.h = (Separating_Rectangle.h / 6) * Settings.Screen_Size;
	SDL_SetTextureBlendMode(First_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, First_Texture);
	SDL_RenderTexture(Core.Renderer, Carrying_Texture, &Separating_Rectangle, NULL);
	Yield.Data[0].Data[0] = First_Texture;
	SDL_Texture* Second_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, Carrying_Surface->w / 2, Carrying_Surface->h);
		SDL_SetTextureBlendMode(Second_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Second_Texture);
	SDL_RenderTextureRotated(Core.Renderer, Carrying_Texture,
		&Separating_Rectangle, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	Yield.Data[1].Data[0] = Second_Texture;
	Separating_Rectangle.x = Carrying_Surface->w / 2;
	SDL_Texture* Third_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, Carrying_Surface->w / 2, Carrying_Surface->h);
	SDL_SetTextureBlendMode(Third_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Third_Texture);
	SDL_RenderTexture(Core.Renderer, Carrying_Texture, &Separating_Rectangle, NULL);
	Yield.Data[0].Data[1] = Third_Texture;
	SDL_Texture* Fourth_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, Carrying_Surface->w / 2, Carrying_Surface->h);
	SDL_SetTextureBlendMode(Fourth_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Fourth_Texture);
	SDL_RenderTextureRotated(Core.Renderer, Carrying_Texture,
		&Separating_Rectangle, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	Yield.Data[1].Data[1] = Fourth_Texture;
	SDL_DestroySurface(Carrying_Surface);
	SDL_DestroyTexture(Carrying_Texture);
	SDL_SetRenderTarget(Core.Renderer, NULL);
	return Yield;
}

Texture_Array Load_Mirrored(std::string Path, SDL_FRect &Rectangle) {
	Path = "Assets/Core/" + Path + ".bmp";
	Texture_Array Yield;
	Yield.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 2));
	Yield.Length = 2;
	SDL_Surface* Primary_Surface = Load_BMP(Path.c_str());
	Rectangle.w = (Primary_Surface->w / 6) * Settings.Screen_Size;
	Rectangle.h = (Primary_Surface->h / 6) * Settings.Screen_Size;
	SDL_Texture* Primary_Texture = SDL_GenerateTextureFromSurface(
		Core.Renderer, Primary_Surface);
	SDL_DestroySurface(Primary_Surface);
	Yield.Data[0] = Primary_Texture;
	SDL_Texture* Derivative_Texture = SDL_GenerateTexture(
		Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, Rectangle.w, Rectangle.h);
	SDL_SetTextureBlendMode(Derivative_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Derivative_Texture);
	SDL_RenderTextureRotated(Core.Renderer,
		Primary_Texture, NULL, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	Yield.Data[1] = Derivative_Texture;
	SDL_SetRenderTarget(Core.Renderer, NULL);
	return Yield;
}

Texture_Array Load_Button(TTF_Font* Font, std::string Text, Rect_Array &Rectangles,
	SDL_Color Primary_Color = Colors.Abyss_Black, SDL_Color Secondary_Color = Colors.Cherry_Blossom) {
	Texture_Array Yield;
	Yield.Length = 2;
	Yield.Data = static_cast<SDL_Texture**>(malloc(sizeof(SDL_Texture*) * 2));
	SDL_Surface* Button_Surface = TTF_RenderText_Blended(Font, Text.c_str(), Text.size(), Primary_Color);
	Yield.Data[0] = SDL_GenerateTextureFromSurface(Core.Renderer, Button_Surface);
	if (Rectangles.Data[0].x == LDE_INVALID) {
		Rectangles.Data[0].x = (320 * Settings.Screen_Size) - (Button_Surface->w / 2);
	}
	if (Rectangles.Data[0].y == LDE_INVALID) {
		Rectangles.Data[0].y = (180 * Settings.Screen_Size) - (Button_Surface->h / 2);
	}
	Rectangles.Data[0].w = Button_Surface->w;
	Rectangles.Data[0].h = Button_Surface->h;
	Text = "> " + Text + " <";
	SDL_DestroySurface(Button_Surface);
	Button_Surface = TTF_RenderText_Blended(Font, "> ", 2, Primary_Color);
	int Offset = Button_Surface->w;
	SDL_DestroySurface(Button_Surface);
	Button_Surface = TTF_RenderText_Blended(Font, Text.c_str(), Text.size(), Secondary_Color);
	Yield.Data[1] = SDL_GenerateTextureFromSurface(Core.Renderer, Button_Surface);
	Rectangles.Data[1] = { Rectangles.Data[0].x - Offset, Rectangles.Data[0].y,
		static_cast<float>(Button_Surface->w), static_cast<float>(Button_Surface->h) };
	SDL_DestroySurface(Button_Surface);
	return Yield;
}

void Render_Button(const Texture_Array &Button, const Rect_Array &Hitbox,
	int Selection, SDL_Color Underline_Color) {
	if (Detect_Mouse_Collision(Hitbox.Data[0])) {
		Interface.UI_Selection = Selection;
		SDL_FRect Underline_Rectangle = { Hitbox.Data[0].x, Hitbox.Data[0].y +
			Hitbox.Data[0].h + 2, Hitbox.Data[0].w, Hitbox.Data[0].h / 10 };
		SDL_SetRenderDrawColor(Core.Renderer, Underline_Color.r, Underline_Color.g,
			Underline_Color.b, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(Core.Renderer, &Underline_Rectangle);
		Clear_Renderer();
		SDL_RenderTexture(Core.Renderer, Button.Data[1], NULL, &Hitbox.Data[1]);
	} else {
		SDL_RenderTexture(Core.Renderer, Button.Data[0], NULL, &Hitbox.Data[0]);
	}
}

Texture_Array Load_Animated(std::string Path, const int Height,
	const bool Inverted, const std::vector<int> &Rotationals) {
	Path = "Assets/Core/Images/" + Path + ".bmp";
	SDL_Texture* Carrying_Texture = IMG_GenerateTexture(Core.Renderer, Path.c_str());
	float Full_Width = 0;
	float Full_Height = 0;
	SDL_GetTextureSize(Carrying_Texture, &Full_Width, &Full_Height);
	Texture_Array Yield;
	int Total_Chunks = std::floor(Full_Height / (Height * 240));
	int Chunks = 1;
	for (int Counter1 = 0; Counter1 < Total_Chunks; Counter1++, Chunks++) {
		for (int Counter2 = 0; Counter2 < Rotationals.size(); Counter2++) {
			if (Counter1 == Rotationals[Counter2]) {
				Chunks += 3;
				break;
			}
		}
	}
	Yield.Data = static_cast<SDL_Texture**>(malloc(sizeof(SDL_Texture*) * Chunks));
	Yield.Length = Chunks;
	int Index = 1;
	for (int Counter1 = 0; Counter1 < Total_Chunks; Counter1++) {
		SDL_Texture* Subtexture = SDL_GenerateTexture(Core.Renderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Full_Width, Height * 240);
		SDL_SetTextureBlendMode(Subtexture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core.Renderer, Subtexture);
		SDL_FRect Splitting_Rectangle = { 0.0f, Counter1 * Height * 240.0f, static_cast<float>(Full_Width), Height * 240.0f };
		SDL_RenderTexture(Core.Renderer, Carrying_Texture, &Splitting_Rectangle, NULL);
		SDL_SetRenderTarget(Core.Renderer, NULL);
		bool Matched = false;
		for (int Counter2 = 0; Counter2 < Rotationals.size(); Counter2++) {
			if (Counter1 == Rotationals[Counter2]) {
				Matched = true;
				break;
			}
		}
		if (Matched) {
			SDL_FPoint Centrepoint = { Height * 120.0f, Height * 120.0f };
			for (int Counter2 = 0; Counter2 < 4; Counter2++) {
				SDL_Texture* Subtexture2 = SDL_GenerateTexture(Core.Renderer,
					SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Height * 240, Height * 240);
					SDL_SetTextureBlendMode(Subtexture2, SDL_BLENDMODE_BLEND);
				SDL_SetRenderTarget(Core.Renderer, Subtexture2);
				SDL_RenderTextureRotated(Core.Renderer, Subtexture,
					NULL, NULL, 90 * Counter2, &Centrepoint, SDL_FLIP_NONE);
				Yield.Data[Index] = Subtexture2;
				Index++;
			}
			SDL_SetRenderTarget(Core.Renderer, NULL);
			SDL_DestroyTexture(Subtexture);
		} else {
			Yield.Data[Index] = Subtexture;
			Index++;
		}
	}
	SDL_Texture* Root_Texture = SDL_GenerateTexture(Core.Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Full_Width, Height * 240);
		SDL_SetTextureBlendMode(Root_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Root_Texture);
	int Minimum = 1;
	int Maximum = Yield.Length - 1;
	while (Minimum <= Maximum) {
		int Selector = Minimum;
		if (Inverted) {
			Selector = Maximum;
		}
		SDL_RenderTexture(Core.Renderer, Yield.Data[Selector], NULL, NULL);
		if (Inverted) {
			Maximum--;
		} else {
			Minimum++;
		}
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
	Yield.Data[0] = Root_Texture;
	SDL_DestroyTexture(Carrying_Texture);
	return Yield;
}

Texture2_Array Load_Animated_Rotational(const std::string &Path, const int Height,
	const bool Inverted, const std::vector<int> &Rotationals) {
	Texture2_Array Yield;
	Yield.Data = static_cast<Texture_Array*>(malloc(sizeof(Texture_Array) * 4));
	Yield.Length = 4;
	for (int Counter1 = 0; Counter1 < 4; Counter1++) {
		Texture_Array Subyield = Load_Animated(Path, Height, Inverted, Rotationals);
		Yield.Data[Counter1].Data = static_cast<SDL_Texture**>(
			malloc(sizeof(SDL_Texture*) * Subyield.Length));
		Yield.Data[Counter1].Length = Subyield.Length;
		float X;
		float Y;
		float Maximum;
		for (int Counter2 = 0; Counter2 < Subyield.Length; Counter2++) {
			SDL_GetTextureSize(Subyield.Data[Counter2], &X, &Y);
			Maximum = X > Y ? X : Y;
			SDL_FPoint Center = { Maximum * 0.5f, Maximum * 0.5f };
			Yield.Data[Counter1].Data[Counter2] = SDL_GenerateTexture(Core.Renderer,
				SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Maximum, Maximum);
			SDL_SetTextureBlendMode(Yield.Data[Counter1].Data[Counter2], SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(Core.Renderer, Yield.Data[Counter1].Data[Counter2]);
			SDL_RenderTextureRotated(Core.Renderer, Subyield.Data[Counter2],
				NULL, NULL, Counter1 * 90, &Center, SDL_FLIP_NONE);
			SDL_SetRenderTarget(Core.Renderer, NULL);
		}
		Clear_Texture_Array(&Subyield);
	}
	return Yield;
}

SDL_Texture* Preload_Sidebutton(std::string Path, SDL_FRect &Rectangle, float Y) {
	Path = "Assets/Core/Images/UI/Sidebar/" + Path + ".bmp";
	SDL_Surface* Surface = Load_BMP(Path.c_str());
	Rectangle = { static_cast<float>(660 - (Surface->w / 6)) * Settings.Screen_Size,
		Y * Settings.Screen_Size, static_cast<float>(Surface->w / 6) * Settings.Screen_Size,
		static_cast<float>(Surface->h / 6) * Settings.Screen_Size };
	SDL_Texture* Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Surface);
	SDL_DestroySurface(Surface);
	return Texture;
}

Texture2_Array Preload_Terminal_Sidebar(std::vector<std::string> Texts, Rect2_Array &Rectangles) {
	int Length = Texts.size() + 2;
	Texts.push_back("Clear Screen");
	Texts.push_back("Exit");
	Texture2_Array Yield;
	Yield.Length = Length;
	Yield.Data = static_cast<Texture_Array*>(malloc(sizeof(Texture_Array) * Length));
	Rectangles.Length = Length;
	Rectangles.Data = static_cast<Rect_Array*>(malloc(sizeof(Rect_Array) * Length));
	for (int Counter1 = 0; Counter1 < Length; Counter1++) {
		Rectangles.Data[Counter1].Length = 2;
		Rectangles.Data[Counter1].Data = static_cast<SDL_FRect*>(
			calloc(2, sizeof(SDL_FRect)));
		Rectangles.Data[Counter1].Data[0] = { LDE_INVALID, static_cast<float>(50 +
			(Counter1 * 30)) * Settings.Screen_Size, 0, 0 };
		Yield.Data[Counter1] = Load_Button(Fonts.Terminal_Font, Texts[Counter1],
			Rectangles.Data[Counter1], Colors.Cherry_Blossom, Colors.Pure_White);
		for (int Counter2 = 0; Counter2 < 2; Counter2++) {
			Rectangles.Data[Counter1].Data[Counter2].x += 210 * Settings.Screen_Size;
		}
	}
	return Yield;
}

void Reload_Commandlist(Texture3_Array &Commandlist, Rect3_Array &Boxlist,
	std::vector<std::vector<std::string>> Contents) {
	Clear_Rect3_Array(&Boxlist);
	Clear_Texture3_Array(&Commandlist);
	Boxlist.Length = Contents.size();
	Boxlist.Data = static_cast<Rect2_Array*>(
		malloc(sizeof(Rect2_Array) * Contents.size()));
	Commandlist.Length = Contents.size();
	Commandlist.Data = static_cast<Texture2_Array*>(
		malloc(sizeof(Texture2_Array) * Contents.size()));
	for (int Counter = 0; Counter < Contents.size(); Counter++) {
		Commandlist.Data[Counter] = Preload_Terminal_Sidebar(
			Contents[Counter], Boxlist.Data[Counter]);
	}
}

void Recache_TT_Commands() {
	Metadata_L.TT_Texts[1] = { "Return" };
	Metadata_L.TT_Parameters[1] = { { "transmit", "EXIT" } };
	Metadata_L.TT_Types[1] = { Execute };
	for (int Counter = 0; Counter < Temporary_L.Docks.size(); Counter++) {
		Metadata_L.TT_Texts[1].push_back("Dock " + std::to_string(Counter + 1));
		Metadata_L.TT_Parameters[1].push_back({ "transmit", "POS_DOCK_" +
			std::to_string(Counter + 1) });
	}
	Reload_Commandlist(Textures.TT_Buttons, Rects.TT_Buttons, Metadata_L.TT_Texts);
}

void Preload_Assets() {
	Core.Game_Texture = SDL_GenerateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, 640 * Settings.Screen_Size, 360 * Settings.Screen_Size);
	for (int Counter = 0; Counter < LDE_MACHINES; Counter++) {
		Metadata_L.Machine_Quirks.push_back({ false, false, false, false });
	}
	for (int Counter1 = 0; Counter1 < Metadata_L.Quirk_Positions.size(); Counter1++) {
		for (int Counter2 = 0; Counter2 < Metadata_L.Quirk_Positions[Counter1].size(); Counter2++) {
			Metadata_L.Machine_Quirks[Metadata_L.Quirk_Positions[Counter1][Counter2]][Counter1] = true;
		}
	}
	SDL_Surface* Carrying_Surface = nullptr;
	auto Preload_Texture = [&Carrying_Surface](std::string Path) {
		Path = "Assets/Core/Images/" + Path + ".bmp";
		Carrying_Surface = Load_BMP(Path.c_str());
		SDL_Texture* Carrying_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Carrying_Surface);
		SDL_DestroySurface(Carrying_Surface);
		return Carrying_Texture;
	};
	Interface.Maximum_Time_Frames = Interface.Frame_Rate;
	Interface.Maximum_Subtime_Frames = Interface.Frame_Rate / 3;
	Interface_L.Slider_Texts[5].resize(101, std::string());
	for (int Counter = 0; Counter < 101; Counter++) {
		Interface_L.Slider_Texts[5][Counter] = std::to_string(Counter) + "%";
	}
	const std::vector<int> Queried = {
		7,
		11,
		13
	};
	for (int Counter1 = 0; Counter1 < Queried.size(); Counter1++) {
		Interface_L.Slider_Texts[Queried[Counter1]].resize(Interface_L.Valve300_Postions.size(), std::string());
		for (int Counter2 = 0; Counter2 < Interface_L.Valve300_Postions.size(); Counter2++) {
			Interface_L.Slider_Texts[Queried[Counter1]][Counter2] = std::to_string(
				Interface_L.Valve300_Postions[Counter2]) + "L/s";
		}
	}
	Interface_L.Slider_Texts[10].resize(241, std::string());
	for (int Counter = 0; Counter < 241; Counter++) {
		Interface_L.Slider_Texts[10][Counter] = std::to_string(Counter * 5) + " °F";
	}
	Interface.Tile_Centerpoint = { 20.0f * Settings.Screen_Size, 20.0f * Settings.Screen_Size };
	Load_Sound(&Audio.Primary_Ambience, "Assets/Core/Audio/Ambient/Background.wav");
	Load_Sound(&Audio.Filtration_Loop, "Assets/Core/Audio/Machines/Filtration_Loop.wav");
	Load_Sound(&Audio.Ram_Loop, "Assets/Core/Audio/Machines/Ram_Loop.wav");
	Load_Sound(&Audio.Click, "Assets/Core/Audio/UI/Click.wav");
	Rects.Return.Length = 2;
	Rects.Return.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rects.Return.Data[0] = { 10.0f * Settings.Screen_Size,
		334.0f * Settings.Screen_Size, 0, 0 };
	Rects.New_Game.Length = 2;
	Rects.New_Game.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rects.New_Game.Data[0] = { LDE_INVALID, 160.0f * Settings.Screen_Size, 0, 0 };
	Rects.Settings.Length = 2;
	Rects.Settings.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rects.Settings.Data[0] = { LDE_INVALID, 190.0f * Settings.Screen_Size, 0, 0 };
	Rects.Update_Logs.Length = 2;
	Rects.Update_Logs.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rects.Update_Logs.Data[0] = { LDE_INVALID, 220.0f * Settings.Screen_Size, 0, 0 };
	Rects.Credits.Length = 2;
	Rects.Credits.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rects.Credits.Data[0] = { LDE_INVALID, 250.0f * Settings.Screen_Size, 0, 0 };
	Rects.Quit_Game.Length = 2;
	Rects.Quit_Game.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rects.Quit_Game.Data[0] = { LDE_INVALID, 280.0f * Settings.Screen_Size, 0, 0 };
	Rects.Apply.Length = 2;
	Rects.Apply.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rects.Apply.Data[0] = { 60.0f * Settings.Screen_Size,
		334.0f * Settings.Screen_Size, 0, 0 };
	Rects.Cancel.Length = 2;
	Rects.Cancel.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rects.Cancel.Data[0] = { 110.0f * Settings.Screen_Size,
		334.0f * Settings.Screen_Size, 0, 0 };
	Rects.Next_Day.Length = 2;
	Rects.Next_Day.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rects.Next_Day.Data[0] = { LDE_INVALID, 300.0f * Settings.Screen_Size, 0, 0 };
	Interface.Map_X = (LDE_TILESIZE * LDE_GRIDSIZE) - 640 + LDE_BUFFERSIZE;
	Interface.Map_Y = (LDE_TILESIZE * LDE_GRIDSIZE) - 360 + LDE_BUFFERSIZE;
	Rects.Subcategories.Length = Metadata_L.Subcategory_Positions.size();
	Rects.Subcategories.Data = static_cast<Rect2_Array*>(
		malloc(sizeof(Rect2_Array) * Metadata_L.Subcategory_Positions.size()));
	Textures.Subcategories.Length = Metadata_L.Subcategory_Positions.size();
	Textures.Subcategories.Data = static_cast<Texture2_Array*>(
		malloc(sizeof(Texture2_Array) * Metadata_L.Subcategory_Positions.size()));
	for (int Counter1 = 0; Counter1 < Metadata_L.Subcategory_Positions.size(); Counter1++) {
		Rects.Subcategories.Data[Counter1].Length = 
			Metadata_L.Subcategory_Positions[Counter1].size();
		Rects.Subcategories.Data[Counter1].Data = static_cast<Rect_Array*>(
			malloc(sizeof(Rect_Array) * Metadata_L.Subcategory_Positions[Counter1].size()));
		Textures.Subcategories.Data[Counter1].Length = 
			Metadata_L.Subcategory_Positions[Counter1].size();
		Textures.Subcategories.Data[Counter1].Data = static_cast<Texture_Array*>(
			malloc(sizeof(Texture_Array) * Metadata_L.Subcategory_Positions[Counter1].size()));
		for (int Counter2 = 0; Counter2 < Metadata_L.Subcategory_Positions[Counter1].size(); Counter2++) {
			Rects.Subcategories.Data[Counter1].Data[Counter2].Length = 2;
			Rects.Subcategories.Data[Counter1].Data[Counter2].Data =
				static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
			Rects.Subcategories.Data[Counter1].Data[Counter2].Data[0] = {
				LDE_INVALID, static_cast<float>(40 + (Counter2 *
				30)) * Settings.Screen_Size, 0, 0 };
			Textures.Subcategories.Data[Counter1].Data[Counter2] =
				Load_Button(Fonts.Halftext_Font, Metadata_L.Subcategory_Names[
				Metadata_L.Subcategory_Positions[Counter1][Counter2]],
				Rects.Subcategories.Data[Counter1].Data[Counter2]);
		}
	}
	Rects.Subcontents.Data = static_cast<Rect2_Array*>(malloc(
		sizeof(Rect2_Array) * Metadata_L.Subcontents.size()));
	Rects.Subcontents.Length = Metadata_L.Subcontents.size();
	Textures.Subcontents.Data = static_cast<Texture2_Array*>(
		malloc(sizeof(Texture2_Array) * Metadata_L.Subcontents.size()));
	Textures.Subcontents.Length = Metadata_L.Subcontents.size();
	for (int Counter1 = 0; Counter1 < Metadata_L.Subcontents.size(); Counter1++) {
		Rects.Subcontents.Data[Counter1].Data = static_cast<Rect_Array*>(malloc(
			sizeof(Rect_Array) * Metadata_L.Subcontents[Counter1].size()));
		Rects.Subcontents.Data[Counter1].Length = Metadata_L.Subcontents[Counter1].size();
		Textures.Subcontents.Data[Counter1].Data = static_cast<Texture_Array*>(
			malloc(sizeof(Texture_Array) * Metadata_L.Subcontents[Counter1].size()));
		Textures.Subcontents.Data[Counter1].Length = Metadata_L.Subcontents[Counter1].size();
		for (int Counter2 = 0; Counter2 < Metadata_L.Subcontents[Counter1].size(); Counter2++) {
			Rects.Subcontents.Data[Counter1].Data[Counter2].Length = 2;
			Rects.Subcontents.Data[Counter1].Data[Counter2].Data =
				static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
			Rects.Subcontents.Data[Counter1].Data[Counter2].Data[0] = {
				LDE_INVALID, static_cast<float>(40 + (Counter2 * 30)) *
				Settings.Screen_Size, 0, 0 };
			Textures.Subcontents.Data[Counter1].Data[Counter2] =
				Load_Button(Fonts.Halftext_Font, Metadata_L.Machine_Names[
				Metadata_L.Subcontents[Counter1][Counter2]],
				Rects.Subcontents.Data[Counter1].Data[Counter2]);
		}
	}
	Rects.Item_Labels.Length = Metadata_L.Item_Labels.size();
	Rects.Item_Labels.Data = static_cast<Rect2_Array*>(
		malloc(sizeof(Rect2_Array) * Metadata_L.Item_Labels.size()));
	Textures.Item_Labels.Data = static_cast<Texture2_Array*>(
		malloc(sizeof(Texture2_Array) *	Metadata_L.Item_Labels.size()));
	Textures.Item_Labels.Length = Metadata_L.Item_Labels.size();
	for (int Counter1 = 0; Counter1 < Metadata_L.Item_Labels.size(); Counter1++) {
		Rects.Item_Labels.Data[Counter1].Data = static_cast<Rect_Array*>(
			malloc(sizeof(Rect_Array) * Metadata_L.Item_Labels[Counter1].size()));
		Rects.Item_Labels.Data[Counter1].Length =
			Metadata_L.Item_Labels[Counter1].size();
		Textures.Item_Labels.Data[Counter1].Data = static_cast<Texture_Array*>(
			malloc(sizeof(Texture_Array) * Metadata_L.Item_Labels[Counter1].size()));
		Textures.Item_Labels.Data[Counter1].Length =
			Metadata_L.Item_Labels[Counter1].size();
		for (int Counter2 = 0; Counter2 < Metadata_L.Item_Labels[Counter1].size(); Counter2++) {
			Rects.Item_Labels.Data[Counter1].Data[Counter2].Length = 2;
			Rects.Item_Labels.Data[Counter1].Data[Counter2].Data =
				static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
			Rects.Item_Labels.Data[Counter1].Data[Counter2].Data[0] =
				{ LDE_INVALID, static_cast<float>(40 + ((Counter2 + Metadata_L
				.Subcategory_Positions[Counter1].size()) * 30)) * Settings.Screen_Size, 0, 0 };
			Textures.Item_Labels.Data[Counter1].Data[Counter2] =
				Load_Button(Fonts.Halftext_Font,	Metadata_L.Machine_Names[
				Metadata_L.Item_Labels[Counter1][Counter2]], Rects
				.Item_Labels.Data[Counter1].Data[Counter2]);
		}
	}
	Textures.Categories.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * Metadata_L.Categories.size()));
	Textures.Categories.Length = Metadata_L.Categories.size();
	Rects.Categories.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * Metadata_L.Categories.size()));
	Rects.Categories.Length = Metadata_L.Categories.size();
	for (int Counter = 0; Counter < Metadata_L.Categories.size(); Counter++) {
		Rects.Categories.Data[Counter].Data = static_cast<
			SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rects.Categories.Data[Counter].Length = 2;
		Rects.Categories.Data[Counter].Data[0] = {
			LDE_INVALID, static_cast<float>(40 + (Counter * 30)) *
			Settings.Screen_Size, 0, 0 };
		Textures.Categories.Data[Counter] = Load_Button(
			Fonts.Text_Font, Metadata_L.Categories[Counter],
			Rects.Categories.Data[Counter]);
	}
	Rects.Error_Exit.Length = 2;
	Rects.Error_Exit.Data = static_cast<SDL_FRect*>(
		calloc(2, sizeof(SDL_FRect)));
	Rects.Error_Exit.Data[0] = { LDE_INVALID, Settings.Screen_Size * 50.0f, 0, 0 };
	Textures.Error_Exit = Load_Button(Fonts.Terminal_Font, "Exit",
		Rects.Error_Exit, Colors.Cherry_Blossom, Colors.Pure_White);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.Error_Exit.Data[Counter].x += Settings.Screen_Size * 210;
	}
	Textures.MSP_Buttons = Preload_Terminal_Sidebar(
		{ "Tank Info", "Fish Info", "Fill Pool", "Empty Pool" },
		Rects.MSP_Buttons);
	Textures.SD_Buttons = Preload_Terminal_Sidebar(
		{ "Export Items", "View Manifest", "Drain Tank 1",
		"Drain Tank 2" }, Rects.SD_Buttons);
	Textures.HX_Buttons = Preload_Terminal_Sidebar(
		{ "View Status" }, Rects.HX_Buttons);
	Textures.MT_Buttons = Preload_Terminal_Sidebar(
		{ "View Status" }, Rects.MT_Buttons);
	Textures.New.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 4));
	Textures.Load.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 4));
	Textures.Clear.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 4));
	Textures.New.Length = 4;
	Textures.Load.Length = 4;
	Textures.Clear.Length = 4;
	Rects.New.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 4));
	Rects.Load.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 4));
	Rects.Clear.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 4));
	Rects.New.Length = 4;
	Rects.Load.Length = 4;
	Rects.Clear.Length = 4;
	for (int Counter = 0; Counter < 4; Counter++) {
		Rects.New.Data[Counter].Length = 2;
		Rects.New.Data[Counter].Data = static_cast<
			SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rects.New.Data[Counter].Data[0] = {
			340.0f * Settings.Screen_Size, static_cast<float>(
			160 + (Counter * 40)) * Settings.Screen_Size, 0, 0 };
		Textures.New.Data[Counter] = Load_Button(Fonts.Subtext_Font,
			"New Factory", Rects.New.Data[Counter]);
		Rects.Load.Data[Counter].Length = 2;
		Rects.Load.Data[Counter].Data = static_cast<
			SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rects.Load.Data[Counter].Data[0] = {
			340.0f * Settings.Screen_Size, static_cast<float>(
			160 + (Counter * 40)) * Settings.Screen_Size, 0, 0 };
		Textures.Load.Data[Counter] = Load_Button(Fonts.Subtext_Font,
			"Load Factory", Rects.Load.Data[Counter]);
		Rects.Clear.Data[Counter].Length = 2;
		Rects.Clear.Data[Counter].Data = static_cast<
			SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rects.Clear.Data[Counter].Data[0] = {
			490.0f * Settings.Screen_Size, static_cast<float>(
			160 + (Counter * 40)) * Settings.Screen_Size, 0, 0 };
		Textures.Clear.Data[Counter] = Load_Button(Fonts.Subtext_Font,
			"Clear Factory", Rects.Clear.Data[Counter]);
	}
	std::string Tool_Texts[5] = { "Building", "Deleting", "Inspecting", "Wiring", "Plumbing" };
	Textures.Tool.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 5));
	Textures.Tool.Length = 5;
	for (int Counter = 0; Counter < 5; Counter++) {
		std::string Tool_String = "[" + std::to_string(Counter + 1) + "] " + Tool_Texts[Counter];
		SDL_Surface* Text_Surface = TTF_RenderText_Blended(Fonts.Halftext_Font,
			Tool_String.c_str(), Tool_String.size(), Colors.Abyss_Black);
		Rects.Tool[Counter] = { (320.0f * Settings.Screen_Size) -
			static_cast<float>(Text_Surface->w / 2), 335.0f * Settings.Screen_Size,
			static_cast<float>(Text_Surface->w), static_cast<float>(Text_Surface->h) };
		Textures.Tool.Data[Counter] = SDL_GenerateTextureFromSurface(
			Core.Renderer, Text_Surface);
		SDL_DestroySurface(Text_Surface);
	}
	Rects.Anti_Aliasing.Length = 2;
	Rects.Anti_Aliasing.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 2));
	Textures.Anti_Aliasing.Length = 2;
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.Anti_Aliasing.Data[Counter].Length = 2;
		Rects.Anti_Aliasing.Data[Counter].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rects.Anti_Aliasing.Data[Counter].Data[0] = { 370.0f *
			Settings.Screen_Size, 300.0f * Settings.Screen_Size, 0, 0 };
	}
	Textures.Anti_Aliasing.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 2));
	Textures.Anti_Aliasing.Data[0] = Load_Button(Fonts.Subtext_Font,
		"Scaling Quality: High", Rects.Anti_Aliasing.Data[0]);
	Textures.Anti_Aliasing.Data[1] = Load_Button(Fonts.Subtext_Font,
		"Scaling Quality: Low", Rects.Anti_Aliasing.Data[1]);
	Rects.V_Sync.Length = 2;
	Rects.V_Sync.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 2));
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.V_Sync.Data[Counter].Length = 2;
		Rects.V_Sync.Data[Counter].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	}
	Rects.V_Sync.Data[0].Data[0] = { 370.0f * Settings
		.Screen_Size, 320.0f * Settings.Screen_Size, 0, 0 };
	Rects.V_Sync.Data[1].Data[0] = { 370.0f * Settings
		.Screen_Size, 320.0f * Settings.Screen_Size, 0, 0 };
	Textures.V_Sync.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 2));
	Textures.V_Sync.Length = 2;
	Textures.V_Sync.Data[0] = Load_Button(Fonts.Subtext_Font,
		"V-Sync: Off", Rects.V_Sync.Data[0]);
	Textures.V_Sync.Data[1] = Load_Button(Fonts.Subtext_Font,
		"V-Sync: On", Rects.V_Sync.Data[1]);
	Textures.Sort.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 2));
	Textures.Sort.Length = 2;
	Rects.Sort.Length = 2;
	Rects.Sort.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 2));
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.Sort.Data[Counter].Length = 2;
		Rects.Sort.Data[Counter].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rects.Sort.Data[Counter].Data[0] =
			{ LDE_INVALID, 334.0f * Settings.Screen_Size, 0, 0 };
	}
	Textures.Sort.Data[0] = Load_Button(Fonts.Subtext_Font,
		"Sort: Newest", Rects.Sort.Data[0]);
	Textures.Sort.Data[1] = Load_Button(Fonts.Subtext_Font,
		"Sort: Oldest", Rects.Sort.Data[1]);
	Textures.TBW_Texture.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 2));
	Textures.TBW_Texture.Length = 2;
	Rects.TBW_Rectangle.Length = 2;
	Rects.TBW_Rectangle.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 2));
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.TBW_Rectangle.Data[Counter].Length = 2;
		Rects.TBW_Rectangle.Data[Counter].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rects.TBW_Rectangle.Data[Counter].Data[0] =
			{ 0, 334.0f * Settings.Screen_Size, 0, 0 };
	}
	Textures.TBW_Texture.Data[0] = Load_Button(Fonts.Subtext_Font,
		"Go to bottom", Rects.TBW_Rectangle.Data[0]);
	Textures.TBW_Texture.Data[1] = Load_Button(Fonts.Subtext_Font,
		"Go to top", Rects.TBW_Rectangle.Data[1]);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.TBW_Rectangle.Data[Counter].Data[0].x =
			(630 * Settings.Screen_Size) -
			Rects.TBW_Rectangle.Data[Counter].Data[0].w;
		Rects.TBW_Rectangle.Data[Counter].Data[1].x =
			Rects.TBW_Rectangle.Data[Counter].Data[0].x +
			(Rects.TBW_Rectangle.Data[Counter].Data[0].w / 2) -
			(Rects.TBW_Rectangle.Data[Counter].Data[1].w / 2);
	}
	Rects.Tile_1x1 = { 0, 0, static_cast<float>(LDE_TILESIZE * Settings.Screen_Size),
		static_cast<float>(LDE_TILESIZE * Settings.Screen_Size) };
	Rects.Tile_1x2 = { 0, 0, static_cast<float>(LDE_TILESIZE * Settings.Screen_Size),
		LDE_TILESIZE * Settings.Screen_Size * 2.0f };
	Rects.Tile_2x1 = { 0, 0, LDE_TILESIZE * Settings.Screen_Size * 2.0f,
		static_cast<float>(LDE_TILESIZE * Settings.Screen_Size) };
	Rects.Tile_2x2 = { 0, 0, LDE_TILESIZE * Settings.Screen_Size * 2.0f,
		LDE_TILESIZE * Settings.Screen_Size * 2.0f };
	Rects.Tile_2x3 = { 0, 0, LDE_TILESIZE * Settings.Screen_Size * 2.0f,
		LDE_TILESIZE * Settings.Screen_Size * 3.0f };
	Rects.Tile_3x2 = { 0, 0, LDE_TILESIZE * Settings.Screen_Size * 3.0f,
		LDE_TILESIZE * Settings.Screen_Size * 2.0f };
	Rects.Tile_3x3 = { 0, 0, LDE_TILESIZE * Settings.Screen_Size * 3.0f,
		LDE_TILESIZE * Settings.Screen_Size * 3.0f };
	Rects.Tile_3x4 = { 0, 0, LDE_TILESIZE * Settings.Screen_Size * 3.0f,
		LDE_TILESIZE * Settings.Screen_Size * 4.0f };
	Rects.Tile_4x3 = { 0, 0, LDE_TILESIZE * Settings.Screen_Size * 4.0f,
		LDE_TILESIZE * Settings.Screen_Size * 3.0f };
	Rects.Tile_4x6 = { 0, 0, LDE_TILESIZE * Settings.Screen_Size * 4.0f,
		LDE_TILESIZE * Settings.Screen_Size * 6.0f };
	Rects.Tile_6x4 = { 0, 0, LDE_TILESIZE * Settings.Screen_Size * 6.0f,
		LDE_TILESIZE * Settings.Screen_Size * 4.0f };
	Rects.Tile_6x8 = { 0, 0, LDE_TILESIZE * Settings.Screen_Size * 6.0f,
		LDE_TILESIZE * Settings.Screen_Size * 8.0f };
	Rects.Tile_8x6 = { 0, 0, LDE_TILESIZE * Settings.Screen_Size * 8.0f,
		LDE_TILESIZE * Settings.Screen_Size * 6.0f };
	Carrying_Surface = TTF_RenderText_Blended(Fonts.Large_Font, "Fish Factory Help",
		17, Colors.Abyss_Black);
	Rects.Help_Content[0] = { (320 * Settings.Screen_Size) -
		static_cast<float>(Carrying_Surface->w / 2), 20.0f * Settings.Screen_Size,
		static_cast<float>(Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
	Textures.Help_Content.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 2));
	Textures.Help_Content.Length = 2;
	Textures.Help_Content.Data[0] = SDL_GenerateTextureFromSurface(
		Core.Renderer, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	Carrying_Surface = TTF_RenderText_Blended(Fonts.Large_Font, "Catalog",
		7, Colors.Abyss_Black);
	Rects.Recipe_Content = { (320 * Settings.Screen_Size) -
		static_cast<float>(Carrying_Surface->w / 2), 20.0f * Settings.Screen_Size,
		static_cast<float>(Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
	Textures.Recipe_Content = SDL_GenerateTextureFromSurface(
		Core.Renderer, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	std::vector<std::string> Captions = { "Resolution", "Framerate Cap",
		"Volume", "Fullscreen", "Toggles", "Keybinds" };
	Rects.Settings_Label.Length = Captions.size();
	Rects.Settings_Label.Data = static_cast<SDL_FRect*>(
		malloc(sizeof(SDL_FRect) * Captions.size()));
	Textures.Settings_Label.Length = Captions.size();
	Textures.Settings_Label.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * Captions.size()));
	for (int Counter = 0; Counter < Captions.size(); Counter++) {
		Carrying_Surface = TTF_RenderText_Blended(Fonts.Halftext_Font, Captions[Counter].c_str(),
		Captions[Counter].size(), Colors.Abyss_Black);
		Textures.Settings_Label.Data[Counter] =
			SDL_GenerateTextureFromSurface(Core.Renderer, Carrying_Surface);
		Rects.Settings_Label.Data[Counter] = { 10.0f * Settings.Screen_Size, 0,
			static_cast<float>(Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
		SDL_DestroySurface(Carrying_Surface);
	}
	Rects.Settings_Label.Data[0].y = 10;
	Rects.Settings_Label.Data[1].y = 100;
	Rects.Settings_Label.Data[2].y = 170;
	Rects.Settings_Label.Data[3].y = 240;
	Rects.Settings_Label.Data[4].y = 270;
	Rects.Settings_Label.Data[4].x = 330 * Settings.Screen_Size;
	Rects.Settings_Label.Data[5].y = 10;
	Rects.Settings_Label.Data[5].x = 330 * Settings.Screen_Size;
	for (int Counter = 0; Counter < Captions.size(); Counter++) {
		Rects.Settings_Label.Data[Counter].y *= Settings.Screen_Size;
	}
	Rects.Save_Settings.Length = 2;
	Rects.Save_Settings.Data = static_cast<SDL_FRect*>(
		calloc(2, sizeof(SDL_FRect)));
	Rects.Save_Settings.Data[0] = { 0, 334.0f * Settings.Screen_Size, 0, 0 };
	Textures.Save_Settings = Load_Button(Fonts.Subtext_Font, "Save Settings",
		Rects.Save_Settings);
	Rects.Save_Settings.Data[0].x = (630 * Settings.Screen_Size) -
		Rects.Save_Settings.Data[0].w;
	Rects.Save_Settings.Data[1].x = Rects.Save_Settings.Data[0].x +
		(Rects.Save_Settings.Data[0].w / 2) - (Rects.Save_Settings.Data[1].w / 2);
	SDL_Texture* Carrying_Texture = Preload_Texture("UI/Backgrounds/Doors");
	Textures.Door.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 2));
	Textures.Door.Length = 2;
	for (int Counter = 0; Counter < 2; Counter++) {
		Textures.Door.Data[Counter] = SDL_GenerateTexture(
			Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, 320 * Settings.Screen_Size, 360 *
			Settings.Screen_Size);
		SDL_SetTextureBlendMode(Textures.Door.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core.Renderer, Textures.Door.Data[Counter]);
		SDL_FRect Half_Rectangle = { 1920.0f * Counter, 0, 1920, 2160 };
		Rects.Door[Counter].w = 320 * Settings.Screen_Size;
		Rects.Door[Counter].h = 360 * Settings.Screen_Size;
		SDL_RenderTexture(Core.Renderer, Carrying_Texture, &Half_Rectangle, NULL);
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
	SDL_DestroyTexture(Carrying_Texture);
	Rects.Clear_Tutorial.Length = 2;
	Rects.Clear_Tutorial.Data = static_cast<SDL_FRect*>(
		calloc(2, sizeof(SDL_FRect)));
	Rects.Clear_Tutorial.Data[0] = { LDE_INVALID, 160, 0, 0 };
	Textures.Clear_Tutorial = Load_Button(Fonts.Halftext_Font,
		"Cancel Tutorial", Rects.Clear_Tutorial);
	std::string Tutorial_Labels[3] = { "The Command Platform", "Simple Generator", "[NF] Simple Fish Farm" };
	Textures.Tutorials.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 3));
	Rects.Tutorials.Length = 3;
	Rects.Tutorials.Data =
		static_cast<Rect_Array*>(malloc(sizeof(Rect_Array) * 3));
	Textures.Tutorials.Length = 3;
	for (int Counter = 0; Counter < 3; Counter++) {
		Rects.Tutorials.Data[Counter].Length = 2;
		Rects.Tutorials.Data[Counter].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rects.Tutorials.Data[Counter].Data[0] = {
			LDE_INVALID, static_cast<float>(160 + (Counter * 40)) *
			Settings.Screen_Size, 0, 0 };
		Textures.Tutorials.Data[Counter] = Load_Button(Fonts.Halftext_Font,
			Tutorial_Labels[Counter].c_str(), Rects.Tutorials.Data[Counter]);
	}
	Rects.Tutorial_Hitbox.Length = 2;
	Rects.Tutorial_Hitbox.Data = static_cast<SDL_FRect*>(
		malloc(sizeof(SDL_FRect) * 2));
	std::string Cheat_Labels[2] = { "Money Generator", "Fluid Generator" };
	Rects.Cheats.Length = 2;
	Rects.Cheats.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 2));
	Textures.Cheats.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 2));
	Textures.Cheats.Length = 2;
	for (int Counter = 0; Counter < 2; Counter++) {
		Rects.Cheats.Data[Counter].Length = 2;
		Rects.Cheats.Data[Counter].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rects.Cheats.Data[Counter].Data[0] = {
			LDE_INVALID, static_cast<float>(160 + (Counter * 40)) *
			Settings.Screen_Size, 0, 0 };
		Textures.Cheats.Data[Counter] = Load_Button(Fonts.Halftext_Font,
			Cheat_Labels[Counter].c_str(), Rects.Cheats.Data[Counter]);
	}
	std::string Keycore = SDL_GetKeyName(Keybinds_L.Keybind_List[13]);
	Keycore = "Press \"" + Keycore + "\" to close.";
	Carrying_Surface = TTF_RenderText_Blended(Fonts.Text_Font, Keycore.c_str(),
		Keycore.size(), Colors.Abyss_Black);
	Rects.Help_Content[1] = { (320 * Settings.Screen_Size) -
		static_cast<float>(Carrying_Surface->w / 2), 320.0f * Settings.Screen_Size,
		static_cast<float>(Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
	Textures.Help_Content.Data[1] = SDL_GenerateTextureFromSurface(
		Core.Renderer, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	Textures.Floor_Texture = Preload_Texture("Tiles/Ground");
	Textures.Frame_Texture = Preload_Texture("Tiles/Frame");
	Textures.Tile_Texture = Preload_Texture("Tiles/Tile");
	Textures.R_Pipe = Load_Modular("Assets/Core/Images/Machines/R_Pipe.bmp", 6);
	Textures.L_Pipe = Load_Modular("Assets/Core/Images/Machines/L_Pipe.bmp", 6);
	Textures.MS_Pool = Load_Modular("Assets/Core/Images/Machines/MSP.bmp", 6);
	Textures.Arrow = Load_Rotational("UI/Other/Direction");
	Textures.S_Dock = Load_Rotational("Machines/S_Dock");
	Textures.Tunnel = Load_Rotational("Other/Tunnel");
	Rects.Tunnel.Length = 2;
	Rects.Tunnel.Data = static_cast<SDL_FRect*>(
		malloc(sizeof(SDL_FRect) * 2));
	Rects.Tunnel.Data[0] = {
		0,
		0,
		Settings.Screen_Size * 240.0f,
		Settings.Screen_Size * 90.0f
	};
	Rects.Tunnel.Data[1] = {
		0,
		0,
		Settings.Screen_Size * 90.0f,
		Settings.Screen_Size * 240.0f
	};
	Textures.Cap = Load_Mirrored("Images/UI/Other/UI_Cap", Rects.Cap);
	Rects.Cap.y = Settings.Screen_Size * 330;
	Textures.Cap_Button = Load_Mirrored_Button("Images/UI/Other/UI_Arrow",
		Rects.Cap_Button);
	Rects.Cap_Button.y = Settings.Screen_Size * 330;
	Rects.Cap_Hitbox.Length = 2;
	Rects.Cap_Hitbox.Data = static_cast<SDL_FRect*>(malloc(sizeof(SDL_FRect) * 2));
	Carrying_Surface = Load_BMP("Assets/Core/Images/UI/Other/Logo.bmp");
	Textures.Logo = SDL_GenerateTextureFromSurface(Core.Renderer, Carrying_Surface);
	SDL_SetWindowIcon(Core.Window, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	SDL_GetTextureSize(Textures.Logo, &Rects.Logo.w,
		&Rects.Logo.h);
	Rects.Logo.w = static_cast<int>(((double)Rects.Logo.w / 6) *
		Settings.Screen_Size);
	Rects.Logo.h = static_cast<int>(((double)Rects.Logo.h / 6) *
		Settings.Screen_Size);
	Rects.Logo.x = (315 * Settings.Screen_Size) - Rects.Logo.w;
	Rects.Logo.y = 32 * Settings.Screen_Size;
	Textures.Crosshair = Preload_Texture("UI/Other/Crosshair");
	Textures.Cursor = Preload_Texture("UI/Other/Cursor");
	Textures.Cursor_Core = Preload_Texture("UI/Other/Cursor_Core");
	Textures.Sapling = Preload_Texture("UI/Other/Sapling");
	Rects.Sapling = Rects.Tile_1x1;
	Textures.Node = Preload_Texture("UI/Other/Node");
	Rects.Node = Rects.Tile_1x1;
	Textures.Path_Arrow = Preload_Texture("UI/Other/Path_Arrow");
	Carrying_Surface = Load_BMP("Assets/Core/Images/UI/Backgrounds/Scrollframe.bmp");
	Textures.Log_Background = SDL_GenerateTextureFromSurface(
		Core.Renderer, Carrying_Surface);
	Rects.Log_Background = { 0, 0, static_cast<float>(Carrying_Surface->w / 6) *
		Settings.Screen_Size, static_cast<float>(Carrying_Surface->h / 6) * Settings.Screen_Size };
	SDL_DestroySurface(Carrying_Surface);
	Textures.Saveloader = Preload_Texture("UI/Backgrounds/Saveloader");
	Rects.Saveloader = { 0, 0, 640.0f * Settings.Screen_Size,
		360.0f * Settings.Screen_Size };
	Textures.Help_Sidebutton = Preload_Sidebutton("Help",
		Rects.Help, 60);
	Textures.Save_Sidebutton = Preload_Sidebutton("Save",
		Rects.Save, 84);
	Textures.Recipe_Sidebutton = Preload_Sidebutton("Recipe",
		Rects.Recipe, 108);
	Textures.Exit_Sidebutton = Preload_Sidebutton("Exit",
		Rects.Exit, 132);
	Textures.Quirk.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 4));
	Textures.Quirk_Label.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 4));
	Textures.Quirk.Length = 4;
	Textures.Quirk_Label.Length = 4;
	SDL_DestroySurface(Carrying_Surface);
	Textures.Quirk.Data[0] = Preload_Texture("UI/Quirks/No_Rotation");
	Textures.Quirk.Data[1] = Preload_Texture("UI/Quirks/Modular");
	Textures.Quirk.Data[2] = Preload_Texture("UI/Quirks/Interactable");
	Textures.Quirk.Data[3] = Preload_Texture("UI/Quirks/All_Direction");
	std::string Quirk_Texts[4] = { "Non-Rotatable", "Modular", "Interactable", "Omnidirectional" };
	for (int Counter = 0; Counter < 4; Counter++) {
		Carrying_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Quirk_Texts[Counter].c_str(),
			Quirk_Texts[Counter].size(), Colors.Abyss_Black);
		Textures.Quirk_Label.Data[Counter] = SDL_GenerateTextureFromSurface(
			Core.Renderer, Carrying_Surface);
		SDL_DestroySurface(Carrying_Surface);
	}
	Textures.R_Flash = Preload_Texture("Effects/Light");
	Rects.R_Flash = { 0, 0, 40.0f * Settings
		.Screen_Size, 40.0f * Settings.Screen_Size };
	Textures.Bubble = Preload_Texture("Effects/Bubble");
	Textures.R_Pump = Load_Animated("Machines/R_Pump", 1, false, { 2, 3, 4 });
	Textures.Incinerator = Load_Animated_Rotational("Machines/Incinerator", 1, true, { });
	Textures.P_Generator = Preload_Texture("Machines/P_Generator");
	Textures.F_Plant = Load_Animated("Machines/F_Plant", 3, true, { });
	Textures.B_Generator = Load_Animated_Rotational("Machines/B_Generator", 3, true, { });
	Textures.Distillery = Load_Animated_Rotational("Machines/Distillery", 2, false, { });
	Textures.G_Bed = Load_Animated_Rotational("Machines/G_Bed", 3, true, { });
	Textures.B_Scrubber = Load_Rotational("Machines/B_Scrubber");
	Textures.MS_Controller = Preload_Texture("Machines/MS_Controller");
	Textures.MS_Output = Preload_Texture("Machines/MS_Output");
	Textures.MS_Input = Preload_Texture("Machines/MS_Input");
	Textures.E_Plant = Load_Rotational("Machines/E_Plant");
	Textures.F_Mixer = Load_Animated_Rotational("Machines/F_Mixer", 3, true, { });
	Textures.Flowerpot = Preload_Texture("Machines/Flowerpot");
	Textures.C_Node = Preload_Texture("Machines/C_Node");
	Textures.G_Well = Load_Rotational("Machines/G_Well");
	Textures.H_Exchanger= Load_Rotational("Machines/H_Exchanger");
	Textures.C_Platform = Load_Rotational("Machines/C_Platform");
	Textures.T_Tower = Load_Rotational("Machines/T_Tower");
	Textures.A_Shelf = Load_Rotational("Machines/A_Shelf");
	Textures.P_Wood = Preload_Texture("Tiles/P_Wood");
	Textures.B_Tile = Preload_Texture("Tiles/B_Tile");
	Textures.S_Carpet = Preload_Texture("Tiles/S_Carpet");
	Textures.H_Strip = Preload_Texture("Tiles/H_Strip");
	Textures.M_Generator = Preload_Texture("Cheats/M_Generator");
	Textures.F_Generator = Preload_Texture("Cheats/F_Generator");
	Textures.R_Intersection = Load_Rotational("Machines/R_Intersection");
	Textures.L_Intersection = Load_Rotational("Machines/L_Intersection");
	Textures.SC_Input = Load_Rotational("Machines/SC_Input");
	Textures.SCH_Sink = Load_Rotational("Machines/SCH_Sink");
	Textures.SC_Transferor = Load_Rotational("Machines/SC_Transferor");
	Textures.SC_Output = Load_Rotational("Machines/SC_Output");
	Textures.ST_Input = Load_Rotational("Machines/ST_Input");
	Textures.STIT_Block = Load_Animated_Rotational("Machines/STIT_Block", 3, true, { });
	Textures.ST_Output = Load_Animated_Rotational("Machines/ST_Output", 2, true, { });
	Textures.Scrap = Preload_Texture("Tiles/Scrap");
	Textures.Return= Load_Button(Fonts.Subtext_Font,
		"Back", Rects.Return);
	Textures.New_Game = Load_Button(Fonts.Text_Font,
		"Play", Rects.New_Game);
	Textures.Settings = Load_Button(Fonts.Text_Font,
		"Settings", Rects.Settings);
	Textures.Update_Logs = Load_Button(Fonts.Text_Font,
		"Changelog", Rects.Update_Logs);
	Textures.Credits = Load_Button(Fonts.Text_Font,
		"Credits", Rects.Credits);
	Textures.Quit_Game = Load_Button(Fonts.Text_Font,
		"Quit", Rects.Quit_Game);
	Textures.Apply = Load_Button(Fonts.Subtext_Font,
		"Apply", Rects.Apply);
	Textures.Cancel = Load_Button(Fonts.Subtext_Font,
		"Cancel", Rects.Cancel);
	Textures.Next_Day = Load_Button(Fonts.Subtext_Font,
		"Proceed", Rects.Next_Day);
	Carrying_Surface = Load_BMP("Assets/Core/Images/Other/Submarine.bmp");
	Textures.Submarine.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 2));
	Textures.Submarine.Length = 2;
	for (int Counter = 0; Counter < 2; Counter++) {
		SDL_Surface* Dividing_Surface = SDL_CreateSurface(Carrying_Surface->w / 2,
			Carrying_Surface->h, Carrying_Surface->format);
		SDL_Rect Dividing_Rectangle = { (Carrying_Surface->w / 2) * Counter, 0,
			Carrying_Surface->w / 2, Carrying_Surface->h };
		SDL_BlitSurface(Carrying_Surface, &Dividing_Rectangle, Dividing_Surface, NULL);
		Textures.Submarine.Data[Counter] = SDL_GenerateTextureFromSurface(
			Core.Renderer, Dividing_Surface);
		SDL_DestroySurface(Dividing_Surface);
	}
	SDL_DestroySurface(Carrying_Surface);
	SDL_GetTextureSize(Textures.Submarine.Data[0], &Rects
		.Submarine.w, &Rects.Submarine.h);
	Rects.Submarine.w = static_cast<int>(((double)Rects
		.Submarine.w / 3) * Settings.Screen_Size);
	Rects.Submarine.h = static_cast<int>(((double)Rects
		.Submarine.h / 6) * Settings.Screen_Size);
	Metadata_L.Machine_Sprites = {
		Textures.R_Pipe.Data[1], Textures.R_Pump.Data[0], Textures.Incinerator
		.Data[0].Data[0], Textures.P_Generator, Textures.Tile_Texture, Textures
		.S_Dock.Data[0], Textures.F_Plant.Data[0], Textures.B_Generator.Data[0].Data[0],
		Textures.MS_Pool.Data[0], Textures.Distillery.Data[0].Data[0], Textures
		.G_Bed.Data[0].Data[0], Textures.C_Platform.Data[0], Textures.B_Scrubber.Data[0], Textures
		.MS_Controller, Textures.MS_Output, Textures.MS_Input, Textures.E_Plant
		.Data[0], Textures.F_Mixer.Data[0].Data[0], Textures.T_Tower.Data[0],
		Textures.Flowerpot, Textures.A_Shelf.Data[0], Textures.C_Node, Textures
		.G_Well.Data[0], Textures.L_Pipe.Data[1], Textures.H_Exchanger.Data[0], Textures
		.P_Wood, Textures.B_Tile, Textures.S_Carpet, Textures.M_Generator, Textures
		.F_Generator, Textures.R_Intersection.Data[0], Textures.L_Intersection.Data[0],
		Textures.H_Strip, Textures.SC_Input.Data[0], Textures.SCH_Sink.Data[0],
		Textures.SC_Transferor.Data[0], Textures.SC_Output.Data[0], Textures.ST_Input.Data[0],
		Textures.STIT_Block.Data[0].Data[0], Textures.ST_Output.Data[0].Data[0]
	};
	Metadata_L.Machine_Rectangles = {
		Rects.Tile_1x1, Rects.Tile_1x1, Rects.Tile_1x1,
		Rects.Tile_1x1, Rects.Tile_1x1, Rects.Tile_6x4,
		Rects.Tile_2x3, Rects.Tile_3x3,	Rects.Tile_1x1,
		Rects.Tile_2x2, Rects.Tile_2x3,	Rects.Tile_8x6,
		Rects.Tile_2x2, Rects.Tile_1x1,	Rects.Tile_1x1,
		Rects.Tile_1x1, Rects.Tile_3x2,	Rects.Tile_3x3,
		Rects.Tile_3x3, Rects.Tile_1x1,	Rects.Tile_2x1,
		Rects.Tile_1x1, Rects.Tile_2x3,	Rects.Tile_1x1,
		Rects.Tile_4x3, Rects.Tile_1x1,	Rects.Tile_1x1,
		Rects.Tile_1x1, Rects.Tile_1x1,	Rects.Tile_1x1,
		Rects.Tile_3x3, Rects.Tile_3x3,	Rects.Tile_1x1,
		Rects.Tile_2x1, Rects.Tile_2x1,	Rects.Tile_2x3,
		Rects.Tile_2x1, Rects.Tile_2x3, Rects.Tile_2x3,
		Rects.Tile_2x2
	};
	Interface_L.Log_Heights.clear();
	Interface_L.Log_Heights.resize(3);
	Cache_L.Log_Rectangles.clear();
	Cache_L.Log_Rectangles.resize(3);
	Cache.Log_Cache.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 3));
	Cache.Log_Cache.Length = 3;
	for (int Counter1 = 0; Counter1 < Metadata_L.Logs.size(); Counter1++) {
		int Height = Render_Rich_Text(Fonts.Halftext_Font, Metadata_L.Logs[Counter1],
			0, 0, Temporary.Log_Inversions[Counter1], true) - (210 * Settings.Screen_Size);
		Interface_L.Log_Heights[Counter1] = Height;
		Cache_L.Log_Rectangles[Counter1].clear();
		int Cap = std::ceil((double)Height / (682 / 2 * Settings.Screen_Size));
		Cache.Log_Cache.Data[Counter1].Data = static_cast<SDL_Texture**>(
			malloc(sizeof(SDL_Texture*) * Cap));
		Cache.Log_Cache.Data[Counter1].Length = Cap;
		for (int Counter2 = 0; Counter2 < Cap; Counter2++) {
			Cache.Log_Cache.Data[Counter1].Data[Counter2] =
				SDL_GenerateTexture(Core.Renderer,
				SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640 *
				Settings.Screen_Size, 1000 * Settings.Screen_Size);
			SDL_FRect New_Rectangle = { 0, Counter2 * Settings.Screen_Size * 1000.0f,
				640.0f * Settings.Screen_Size, 1000.0f * Settings.Screen_Size };
			SDL_SetTextureBlendMode(Cache.Log_Cache.Data[
				Counter1].Data[Counter2], SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(Core.Renderer, Cache
				.Log_Cache.Data[Counter1].Data[Counter2]);
			Render_Rich_Text(Fonts.Halftext_Font, Metadata_L.Logs[Counter1],
				52, 52 - (New_Rectangle.y / Settings.Screen_Size),
				Temporary.Log_Inversions[Counter1], false);
			SDL_SetRenderTarget(Core.Renderer, NULL);
			Cache_L.Log_Rectangles[Counter1].push_back(New_Rectangle);			
		}
	}
	Cache.Wire_Cache.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 4));
	Cache.Wire_Cache.Length = 4;
	for (int Counter = 0; Counter < 4; Counter++) {
		Cache.Wire_Cache.Data[Counter] = SDL_GenerateTexture(
			Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, 20 * LDE_GRIDSIZE * Settings.Screen_Size, 20 *
			LDE_GRIDSIZE * Settings.Screen_Size);
		SDL_SetTextureBlendMode(Cache.Wire_Cache.Data[Counter], SDL_BLENDMODE_BLEND);
	}
	Cache.Wire_Box = { 0, 0, 20.0f * LDE_GRIDSIZE * Settings.Screen_Size,
		20.0f *	LDE_GRIDSIZE * Settings.Screen_Size };
	std::string Labels[2] = { "Apply", "Cancel" };
	Rects.Confirmation.Length = 2;
	Rects.Confirmation.Data = static_cast<
		Rect_Array*>(malloc(sizeof(Rect_Array) * 2));
	Textures.Confirmation.Data = static_cast<
		Texture_Array*>(malloc(sizeof(Texture_Array) * 2));
	Textures.Confirmation.Length = 2;
	for (int Counter1 = 0; Counter1 < 2; Counter1++) {
		Rects.Confirmation.Data[Counter1].Length = 2;
		Rects.Confirmation.Data[Counter1].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Textures.Confirmation.Data[Counter1] = Load_Button(Fonts.Halftext_Font,
			Labels[Counter1], Rects.Confirmation.Data[Counter1]);
		for (int Counter2 = 0; Counter2 < 2; Counter2++) {
			Rects.Confirmation.Data[Counter1].Data[Counter2].x =
				(((Counter1 * 320) + 160) *	Settings.Screen_Size) -
				(Rects.Confirmation.Data[Counter1].Data[Counter2].w / 2);
			Rects.Confirmation.Data[Counter1].Data[Counter2].y = 260 * Settings.Screen_Size;
		}
	}
	Textures.Pyramid.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 4));
	Textures.Pyramid.Length = 4;
	float Full_Width = ((LDE_GRIDSIZE * 40) + (LDE_BUFFERSIZE * 2)) *
		Settings.Screen_Size;
	int Candidate_Length = Full_Width * 0.25;
	if (evn_i(Candidate_Length)) {
		Candidate_Length--;
	}
	const int Resolution = 2001;
	SDL_Surface* Mesh_Surface = SDL_CreateSurface(Resolution, Resolution, SDL_PIXELFORMAT_RGBA8888);
	const SDL_PixelFormatDetails* Pixel_Format = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
	SDL_LockSurface(Mesh_Surface);
	uint32_t Empty = SDL_MapRGBA(Pixel_Format, NULL, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
	uint32_t Light = SDL_MapRGBA(Pixel_Format, NULL, Colors.Mid_Grey.r,
		Colors.Mid_Grey.g, Colors.Mid_Grey.b, SDL_ALPHA_OPAQUE);
	uint32_t* Pixels = static_cast<uint32_t*>(Mesh_Surface->pixels);
	for (int Counter = 0; Counter < sqr_i(Resolution); Counter++) {
		if (evn_i(Counter) && static_cast<int>(Counter & 3) == 0) {
				Pixels[Counter] = Light;
		} else {
			Pixels[Counter] = Empty;
		}
	}
	SDL_UnlockSurface(Mesh_Surface);
	Textures.Mesh = SDL_GenerateTextureFromSurface(
		Core.Renderer, Mesh_Surface);
	SDL_SetTextureScaleMode(Textures.Mesh, SDL_SCALEMODE_NEAREST);
	SDL_DestroySurface(Mesh_Surface);
	for (int Counter = 0; Counter < 4; Counter++) {
		Textures.Pyramid.Data[Counter] = SDL_GenerateTexture(
			Core.Renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, Full_Width * 0.25, Full_Width * 0.25);
		SDL_SetTextureBlendMode(Textures.Pyramid.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_SetTextureScaleMode(Textures.Pyramid.Data[Counter], SDL_SCALEMODE_NEAREST);
	}
	SDL_Color Pyramid_Color = Colors.Reinforced_Grey;
	Pyramid_Color.a = SDL_ALPHA_OPAQUE;
	Set_Renderer_Color(Pyramid_Color);
	float Subwidth = ((LDE_GRIDSIZE + 2) * Settings.Screen_Size * 40.0f) * 0.5f;
	for (int X = 0; X < 2; X++) {
		for (int Y = 0; Y < 2; Y++) {
			SDL_SetRenderTarget(Core.Renderer,
				Textures.Pyramid.Data[(X * 2) + Y]);
			SDL_FRect Subrectangle = {
				((LDE_BUFFERSIZE - 280.0f) * Settings.Screen_Size) - (X * Subwidth),
				((LDE_BUFFERSIZE - 280.0f) * Settings.Screen_Size) - (Y * Subwidth),
				500.0f * Settings.Screen_Size,
				500.0f * Settings.Screen_Size
			};
			SDL_RenderFillRect(Core.Renderer, &Subrectangle);
			Subrectangle.x -= Settings.Screen_Size * 5.0f;
			Subrectangle.y -= Settings.Screen_Size * 5.0f;
			Subrectangle.w += Settings.Screen_Size * 10.0f;
			Subrectangle.h += Settings.Screen_Size * 10.0f;
			for (int Counter = 0; Counter < 5 * Settings.Screen_Size; Counter++) {
				Subrectangle.x--;
				Subrectangle.y--;
				Subrectangle.w += 2;
				Subrectangle.h += 2;
				SDL_SetRenderDrawBlendMode(Core.Renderer, SDL_BLENDMODE_BLEND);
				SDL_RenderRect(Core.Renderer, &Subrectangle);
			}
		}
	}
	SDL_SetRenderTarget(Core.Renderer, NULL);
	Clear_Renderer();
}

void Render_Dynamic_Text(TTF_Font* Selected_Font, std::string Text, SDL_Color Color, int X, int Y) {
	SDL_Surface* Text_Surface = TTF_RenderText_Blended(Selected_Font, Text.c_str(), Text.size(), Color);
	SDL_Texture* Text_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Text_Surface);
	int Multiplier = Settings.Screen_Size;
	if (X == LDE_INVALID) {
		X = (320 * Settings.Screen_Size) - (Text_Surface->w / 2);
		Multiplier = 1;
	}
	SDL_FRect Text_Rectangle = { static_cast<float>(X * Multiplier),
		static_cast<float>(Y * Settings.Screen_Size),
		static_cast<float>(Text_Surface->w), static_cast<float>(Text_Surface->h) };
	SDL_RenderTexture(Core.Renderer, Text_Texture, NULL, &Text_Rectangle);
	SDL_DestroySurface(Text_Surface);
	SDL_DestroyTexture(Text_Texture);
}

int Render_Rich_Text(TTF_Font* Selected_Font, std::string Raw_Text, int X, int Y, bool Inverted, bool Disabled) {
	std::string Text = Raw_Text;
	std::vector<std::string> Fragments = { };
	size_t Start = 0;
	size_t End = 0;
	int Offset = 0;
	while ((End = Text.find('|', Start)) != std::string::npos) {
		Fragments.push_back(Text.substr(Start, End - Start));
		Start = End + 1;
	}
	Fragments.push_back(Text.substr(Start));
	int Multiplier = LDE_INVALID;
	int Subtractor = 0;
	if (Inverted) {
		Multiplier = 1;
		Subtractor = static_cast<int>(Fragments.size()) - 1;
	}
	for (size_t Counter = 0; Counter < Fragments.size(); Counter++) {
		size_t Position;
		while ((Position = Fragments[Counter].find("[c]")) != std::string::npos) {
			Fragments[Counter].replace(Position, 3, "    ");
		}
	}
	for (size_t Counter1 = 0; Counter1 < Fragments.size(); Counter1++) {
		int Type = LDE_INVALID;
		std::vector<std::string> Targets = { "[a]", "[b]" };
		for (int Counter2 = 0; Counter2 < Targets.size(); Counter2++) {
			bool Matched = true;
			if (Fragments[Multiplier * (Subtractor - Counter1)] == " ") {
				Matched = false;
			} else {
				for (int Counter3 = 0; Counter3 < 3; Counter3++) {
					if (Fragments[Multiplier * (Subtractor - Counter1)][Counter3] != Targets[Counter2][Counter3]) {
						Matched = false;
					}
				}
			}
			if (Matched) {
				Type = Counter2;
				break;
			}
		}
		if ((Type == 0 && Inverted) || (Type == 1 && !Inverted)) {
			continue;
		} else if (Type != LDE_INVALID) {
			Fragments[Multiplier * (Subtractor - Counter1)].erase(0, 3);
		}
		SDL_Surface* Fragment_Surface = TTF_RenderText_Blended(Selected_Font, Fragments
			[Multiplier * (Subtractor - Counter1)].c_str(), Fragments[Multiplier * (Subtractor -
			Counter1)].size(), Colors.Abyss_Black);
		SDL_FRect Fragment_Rectangle = { static_cast<float>(X * Settings.Screen_Size),
			static_cast<float>(Y * Settings.Screen_Size) + Offset, static_cast<float>(
			Fragment_Surface->w), static_cast<float>(Fragment_Surface->h) };
		if (!Disabled) {
			SDL_Texture* Fragment_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Fragment_Surface);
			SDL_RenderTexture(Core.Renderer, Fragment_Texture, NULL, &Fragment_Rectangle);
			SDL_DestroyTexture(Fragment_Texture);
		}
		SDL_DestroySurface(Fragment_Surface);
		Offset = Offset + Fragment_Rectangle.h;
	}
	return Offset;
}

std::vector<Point> Return_Nodes(const int Column, const int Row, const int Rotation,
	const std::vector<Point>(&Preconfiguration)[4]) {
	std::vector<Point> Yield(Preconfiguration[Rotation].size());
	for (int Counter = 0; Counter < Yield.size(); Counter++) {
		Yield[Counter] = {
			Column + Preconfiguration[Rotation][Counter].X,
			Row + Preconfiguration[Rotation][Counter].Y
		};
	}
	return Yield;
}