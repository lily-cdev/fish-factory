#include <Core.h>
#include <Preloader.h>

Audio Audio_Access;

void Clear_Renderer() {
	SDL_SetRenderDrawColor(Core_Access.Application_Renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
}

void Set_Renderer_Color(const SDL_Color &Color) {
	SDL_SetRenderDrawColor(Core_Access.Application_Renderer, Color.r, Color.g, Color.b, SDL_ALPHA_OPAQUE);
}

bool Detect_Mouse_Collision(const SDL_FRect &Target) {
	return (UI_Access.X_Mouse_Position >= Target.x && UI_Access.X_Mouse_Position <= Target.x + Target.w &&
		UI_Access.Y_Mouse_Position >= Target.y && UI_Access.Y_Mouse_Position <= Target.y + Target.h);
}

SDL_FRect Buffer_Rectangle(const SDL_FRect &Source, const int X, const int Y) {
	return { Source.x - (X * Settings_Access.Screen_Size), Source.y - (Y * Settings_Access.Screen_Size),
		Source.w + ((X * 2) * Settings_Access.Screen_Size), Source.h + ((Y * 2) * Settings_Access.Screen_Size) };
}

void Clear_Texture_Array(Texture_Array &Target) {
	if (Target.Data != nullptr) {
		for (int Counter = 0; Counter < Target.Length; Counter++) {
			SDL_DestroyTexture(Target.Data[Counter]);
		}
		free(Target.Data);
	}
}

void Clear_Texture2_Array(Texture2_Array &Target) {
	if (Target.Data != nullptr) {
		for (int Counter = 0; Counter < Target.Length; Counter++) {
			Clear_Texture_Array(Target.Data[Counter]);
		}
		free(Target.Data);
	}
}

void Clear_Texture3_Array(Texture3_Array &Target) {
	if (Target.Data != nullptr) {
		for (int Counter = 0; Counter < Target.Length; Counter++) {
			Clear_Texture2_Array(Target.Data[Counter]);
		}
		free(Target.Data);
	}
}

void Clear_Rect_Array(Rect_Array &Target) {
	if (Target.Data != nullptr) {
		free(Target.Data);
	}
}

void Clear_Rect2_Array(Rect2_Array &Target) {
	if (Target.Data != nullptr) {
		for (int Counter = 0; Counter < Target.Length; Counter++) {
			Clear_Rect_Array(Target.Data[Counter]);
		}
		free(Target.Data);
	}
}

void Clear_Rect3_Array(Rect3_Array &Target) {
	if (Target.Data != nullptr) {
		for (int Counter = 0; Counter < Target.Length; Counter++) {
			Clear_Rect2_Array(Target.Data[Counter]);
		}
		free(Target.Data);
	}
}

bool Check_Clearance(const int X, const int Y, const int W, const int H) {
	if (X + W > LDE_GRIDSIZE || Y + H > LDE_GRIDSIZE) {
		return false;
	} 
	for (int First_Counter = 0; First_Counter < W; First_Counter++) {
		for (int Second_Counter = 0; Second_Counter < H; Second_Counter++) {
			if (Data_Access.Visual_Grid[X + First_Counter][Y + Second_Counter] != 0) {
				return false;
			}
		}
	}
	return true;
}

void Fill_Clearance(const int Identifier, const int X, const int Y, const int W, const int H) {
	for (int First_Counter = 0; First_Counter < W; First_Counter++) {
		for (int Second_Counter = 0; Second_Counter < H; Second_Counter++) {
			Data_Access.Visual_Grid[X + First_Counter][Y + Second_Counter] = Identifier;
			if (First_Counter > 0 || Second_Counter > 0) {
				Data_Access.Settings_Grid[X + First_Counter][Y + Second_Counter][1] = X;
				Data_Access.Settings_Grid[X + First_Counter][Y + Second_Counter][2] = Y;
			}
		}
	}
}

void Update_Tilestack(bool X_Lock, int X, bool Y_Lock, int Y) {
	X = X * Settings_Access.Screen_Size;
	Y = Y * Settings_Access.Screen_Size;
	if (!X_Lock) {
		Rectangles_Access.Tile_1x1.x = X;
		Rectangles_Access.Tile_1x2.x = X;
		Rectangles_Access.Tile_2x1.x = X;
		Rectangles_Access.Tile_2x2.x = X;
		Rectangles_Access.Tile_2x3.x = X;
		Rectangles_Access.Tile_3x2.x = X;
		Rectangles_Access.Tile_3x3.x = X;
		Rectangles_Access.Tile_3x4.x = X;
		Rectangles_Access.Tile_4x3.x = X;
		Rectangles_Access.Tile_4x6.x = X;
		Rectangles_Access.Tile_6x4.x = X;
		Rectangles_Access.Tile_6x8.x = X;
		Rectangles_Access.Tile_3x3.x = X;
		Rectangles_Access.Tile_8x6.x = X;
	}
	if (!Y_Lock) {
		Rectangles_Access.Tile_1x1.y = Y;
		Rectangles_Access.Tile_1x2.y = Y;
		Rectangles_Access.Tile_2x1.y = Y;
		Rectangles_Access.Tile_2x2.y = Y;
		Rectangles_Access.Tile_2x3.y = Y;
		Rectangles_Access.Tile_3x2.y = Y;
		Rectangles_Access.Tile_3x3.y = Y;
		Rectangles_Access.Tile_3x4.y = Y;
		Rectangles_Access.Tile_4x3.y = Y;
		Rectangles_Access.Tile_4x6.y = Y;
		Rectangles_Access.Tile_6x4.y = Y;
		Rectangles_Access.Tile_6x8.y = Y;
		Rectangles_Access.Tile_3x3.y = Y;
		Rectangles_Access.Tile_8x6.y = Y;
	}
}

std::string Abbreviate_Number(long double Number) {
	int Marker = 0;
	for (int Counter = 0; Counter < Core_Access.Suffixes.size() - 1; Counter++) {
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
	if (Core_Access.Suffixes[Marker] != 'J') {
		std::string Teritary_String(1, Core_Access.Suffixes[Marker]);
		Returning_String = Returning_String + Teritary_String;
	}
	return Returning_String;
}

int Get_Depth(double Number) {
	for (int Counter = 0; Counter < Core_Access.Suffixes.size() - 1; Counter++) {
		if (Number > 1000) {
			Number = Number / 1000;
		} else {
			return Counter;
		}
	}
	return LDE_INVALID;
}

std::string Truncate(double Number, int Depth = LDE_INVALID) {
	if (Depth == LDE_INVALID) {
		for (int Counter = 0; Counter < Core_Access.Suffixes.size() - 1; Counter++) {
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
	SDL_FPoint Tile_Centrepoint = { 20.0f * Size, 20.0f * Size };
	Texture_Array Yield;
	Yield.Data = static_cast<SDL_Texture**>(malloc(sizeof(SDL_Texture*) * 16));
	Yield.Length = 16;
	SDL_Surface* Spritesheet_Surface = IMG_Load(Path.c_str());
	SDL_Texture* Spritesheet_Texture = SDL_GenerateTextureFromSurface(
		Core_Access.Application_Renderer, Spritesheet_Surface);
	Texture_Array Subtextures;
	Subtextures.Data = static_cast<SDL_Texture**>(malloc(sizeof(SDL_Texture*) * 6));
	Subtextures.Length = 6;
	for (int Counter = 0; Counter < 6; Counter++) {
		Subtextures.Data[Counter] = SDL_GenerateTexture(Core_Access.Application_Renderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
		SDL_FRect Separating_Rectangle = { (40.0f * Size) * Counter, 0.0f, 40.0f * Size, 40.0f * Size };
		SDL_SetRenderTarget(Core_Access.Application_Renderer, Subtextures.Data[Counter]);
		SDL_SetTextureBlendMode(Subtextures.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_RenderTexture(Core_Access.Application_Renderer, Spritesheet_Texture, &Separating_Rectangle, NULL);
	}
	SDL_Texture* Isolated_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Isolated_Texture);
	SDL_SetTextureBlendMode(Isolated_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTexture(Core_Access.Application_Renderer, Subtextures.Data[0], NULL, NULL);
	Yield.Data[0] = Isolated_Texture;
	SDL_Texture* Surrounded_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Surrounded_Texture);
	SDL_SetTextureBlendMode(Surrounded_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTexture(Core_Access.Application_Renderer, Subtextures.Data[1], NULL, NULL);
	Yield.Data[1] = Surrounded_Texture;
	SDL_Texture* Junction1_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Junction1_Texture);
	SDL_SetTextureBlendMode(Junction1_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTexture(Core_Access.Application_Renderer, Subtextures.Data[2], NULL, NULL);
	Yield.Data[2] = Junction1_Texture;
	SDL_Texture* Junction2_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Junction2_Texture);
	SDL_SetTextureBlendMode(Junction2_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Subtextures.Data[2],
		NULL, NULL, 180, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[3] = Junction2_Texture;
	SDL_Texture* Junction3_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Junction3_Texture);
	SDL_SetTextureBlendMode(Junction3_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Subtextures.Data[2],
		NULL, NULL, 90, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[4] = Junction3_Texture;
	SDL_Texture* Junction4_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Junction4_Texture);
	SDL_SetTextureBlendMode(Junction4_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Subtextures.Data[2],
		NULL, NULL, 270, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[5] = Junction4_Texture;
	SDL_Texture* Vertical_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Vertical_Texture);
	SDL_SetTextureBlendMode(Vertical_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTexture(Core_Access.Application_Renderer, Subtextures.Data[3], NULL, NULL);
	Yield.Data[6] = Vertical_Texture;
	SDL_Texture* Horizontal_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Horizontal_Texture);
	SDL_SetTextureBlendMode(Horizontal_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Subtextures.Data[3],
		NULL, NULL, 90, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[7] = Horizontal_Texture;
	SDL_Texture* Corner1_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Corner1_Texture);
	SDL_SetTextureBlendMode(Corner1_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTexture(Core_Access.Application_Renderer, Subtextures.Data[4], NULL, NULL);
	Yield.Data[8] = Corner1_Texture;
	SDL_Texture* Corner2_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Corner2_Texture);
	SDL_SetTextureBlendMode(Corner2_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Subtextures.Data[4],
		NULL, NULL, 90, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[9] = Corner2_Texture;
	SDL_Texture* Corner3_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Corner3_Texture);
	SDL_SetTextureBlendMode(Corner3_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Subtextures.Data[4],
		NULL, NULL, 180, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[10] = Corner3_Texture;
	SDL_Texture* Corner4_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Corner4_Texture);
	SDL_SetTextureBlendMode(Corner4_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Subtextures.Data[4],
		NULL, NULL, 270, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[11] = Corner4_Texture;
	SDL_Texture* Cap1_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Cap1_Texture);
	SDL_SetTextureBlendMode(Cap1_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTexture(Core_Access.Application_Renderer, Subtextures.Data[5], NULL, NULL);
	Yield.Data[12] = Cap1_Texture;
	SDL_Texture* Cap2_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Cap2_Texture);
	SDL_SetTextureBlendMode(Cap2_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Subtextures.Data[5],
		NULL, NULL, 90, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[13] = Cap2_Texture;
	SDL_Texture* Cap3_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Cap3_Texture);
	SDL_SetTextureBlendMode(Cap3_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Subtextures.Data[5],
		NULL, NULL, 180, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[14] = Cap3_Texture;
	SDL_Texture* Cap4_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 40 * Size, 40 * Size);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Cap4_Texture);
	SDL_SetTextureBlendMode(Cap4_Texture, SDL_BLENDMODE_BLEND);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Subtextures.Data[5],
		NULL, NULL, 270, &Tile_Centrepoint, SDL_FLIP_NONE);
	Yield.Data[15] = Cap4_Texture;
	Clear_Texture_Array(Subtextures);
	SDL_DestroySurface(Spritesheet_Surface);
	SDL_DestroyTexture(Spritesheet_Texture);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, nullptr);
	return Yield;
}

Texture_Array Load_Rotational(std::string Path) {
	Path = "Assets/Core/Images/" + Path + ".png";
	Texture_Array Yield;
	Yield.Length = 4;
	Yield.Data = static_cast<SDL_Texture**>(malloc(sizeof(SDL_Texture*) * 4));
	SDL_Surface* Primary_Surface = IMG_Load(Path.c_str());
	float Maximum = Primary_Surface->w;
	if (Primary_Surface->h > Maximum) {
		Maximum = Primary_Surface->h;
	}
	SDL_FPoint Tile_Centrepoint = { Maximum * 0.5f, Maximum * 0.5f };
	Yield.Data[0] = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Primary_Surface);
	SDL_DestroySurface(Primary_Surface);
	for (int Counter = 1; Counter < 4; Counter++) {
		Yield.Data[Counter] = SDL_GenerateTexture(Core_Access.Application_Renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, Maximum, Maximum);
		SDL_SetTextureBlendMode(Yield.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core_Access.Application_Renderer, Yield.Data[Counter]);
		SDL_RenderTextureRotated(Core_Access.Application_Renderer, Yield.Data[0], NULL,
			NULL, Counter * 90, &Tile_Centrepoint, SDL_FLIP_NONE);
	}
	SDL_SetRenderTarget(Core_Access.Application_Renderer, NULL);
	return Yield;
}

Texture2_Array Load_Mirrored_Button(std::string Path, SDL_FRect &Rectangle) {
	Path = "Assets/Core/" + Path + ".png";
	Texture2_Array Yield;
	Yield.Length = 2;
	Yield.Data = static_cast<Texture_Array*>(malloc(sizeof(Texture_Array) * 2));
	for (int Counter = 0; Counter < 2; Counter++) {
		Yield.Data[Counter].Data = static_cast<SDL_Texture**>(
			malloc(sizeof(SDL_Texture**) * 2));
		Yield.Data[Counter].Length = 2;
	}
	SDL_Surface* Carrying_Surface = IMG_Load(Path.c_str());
	SDL_Texture* Carrying_Texture = SDL_GenerateTextureFromSurface(
		Core_Access.Application_Renderer, Carrying_Surface);
	SDL_Texture* First_Texture = SDL_GenerateTexture(
		Core_Access.Application_Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, Carrying_Surface->w / 2, Carrying_Surface->h);
	SDL_FRect Separating_Rectangle = { 0.0f, 0.0f, static_cast<float>(
		Carrying_Surface->w / 2), static_cast<float>(Carrying_Surface->h) };
	Rectangle.w = (Separating_Rectangle.w / 6) * Settings_Access.Screen_Size;
	Rectangle.h = (Separating_Rectangle.h / 6) * Settings_Access.Screen_Size;
	SDL_SetTextureBlendMode(First_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, First_Texture);
	SDL_RenderTexture(Core_Access.Application_Renderer, Carrying_Texture, &Separating_Rectangle, NULL);
	Yield.Data[0].Data[0] = First_Texture;
	SDL_Texture* Second_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, Carrying_Surface->w / 2, Carrying_Surface->h);
		SDL_SetTextureBlendMode(Second_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Second_Texture);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Carrying_Texture,
		&Separating_Rectangle, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	Yield.Data[1].Data[0] = Second_Texture;
	Separating_Rectangle.x = Carrying_Surface->w / 2;
	SDL_Texture* Third_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, Carrying_Surface->w / 2, Carrying_Surface->h);
	SDL_SetTextureBlendMode(Third_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Third_Texture);
	SDL_RenderTexture(Core_Access.Application_Renderer, Carrying_Texture, &Separating_Rectangle, NULL);
	Yield.Data[0].Data[1] = Third_Texture;
	SDL_Texture* Fourth_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, Carrying_Surface->w / 2, Carrying_Surface->h);
	SDL_SetTextureBlendMode(Fourth_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Fourth_Texture);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Carrying_Texture,
		&Separating_Rectangle, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	Yield.Data[1].Data[1] = Fourth_Texture;
	SDL_DestroySurface(Carrying_Surface);
	SDL_DestroyTexture(Carrying_Texture);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, NULL);
	return Yield;
}

Texture_Array Load_Mirrored(std::string Path, SDL_FRect &Rectangle) {
	Path = "Assets/Core/" + Path + ".png";
	Texture_Array Yield;
	Yield.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 2));
	Yield.Length = 2;
	SDL_Surface* Primary_Surface = IMG_Load(Path.c_str());
	Rectangle.w = (Primary_Surface->w / 6) * Settings_Access.Screen_Size;
	Rectangle.h = (Primary_Surface->h / 6) * Settings_Access.Screen_Size;
	SDL_Texture* Primary_Texture = SDL_GenerateTextureFromSurface(
		Core_Access.Application_Renderer, Primary_Surface);
	SDL_DestroySurface(Primary_Surface);
	Yield.Data[0] = Primary_Texture;
	SDL_Texture* Derivative_Texture = SDL_GenerateTexture(
		Core_Access.Application_Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, Rectangle.w, Rectangle.h);
	SDL_SetTextureBlendMode(Derivative_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Derivative_Texture);
	SDL_RenderTextureRotated(Core_Access.Application_Renderer,
		Primary_Texture, NULL, NULL, 0, NULL, SDL_FLIP_HORIZONTAL);
	Yield.Data[1] = Derivative_Texture;
	SDL_SetRenderTarget(Core_Access.Application_Renderer, NULL);
	return Yield;
}

Texture_Array Load_Button(TTF_Font* Font, std::string Text, Rect_Array &Rectangles,
	SDL_Color Primary_Color = Colors_Access.Abyss_Black, SDL_Color Secondary_Color = Colors_Access.Cherry_Blossom) {
	Texture_Array Yield;
	Yield.Length = 2;
	Yield.Data = static_cast<SDL_Texture**>(malloc(sizeof(SDL_Texture*) * 2));
	SDL_Surface* Button_Surface = TTF_RenderText_Blended(Font, Text.c_str(), Text.size(), Primary_Color);
	Yield.Data[0] = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Button_Surface);
	if (Rectangles.Data[0].x == LDE_INVALID) {
		Rectangles.Data[0].x = (320 * Settings_Access.Screen_Size) - (Button_Surface->w / 2);
	}
	if (Rectangles.Data[0].y == LDE_INVALID) {
		Rectangles.Data[0].y = (180 * Settings_Access.Screen_Size) - (Button_Surface->h / 2);
	}
	Rectangles.Data[0].w = Button_Surface->w;
	Rectangles.Data[0].h = Button_Surface->h;
	Text = "> " + Text + " <";
	SDL_DestroySurface(Button_Surface);
	Button_Surface = TTF_RenderText_Blended(Font, "> ", 2, Primary_Color);
	int Offset = Button_Surface->w;
	SDL_DestroySurface(Button_Surface);
	Button_Surface = TTF_RenderText_Blended(Font, Text.c_str(), Text.size(), Secondary_Color);
	Yield.Data[1] = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Button_Surface);
	Rectangles.Data[1] = { Rectangles.Data[0].x - Offset, Rectangles.Data[0].y,
		static_cast<float>(Button_Surface->w), static_cast<float>(Button_Surface->h) };
	SDL_DestroySurface(Button_Surface);
	return Yield;
}

void Render_Button(const Texture_Array &Button, const Rect_Array &Hitbox,
	int Selection, SDL_Color Underline_Color) {
	if (Detect_Mouse_Collision(Hitbox.Data[0])) {
		UI_Access.UI_Selection = Selection;
		SDL_FRect Underline_Rectangle = { Hitbox.Data[0].x, Hitbox.Data[0].y +
			Hitbox.Data[0].h + 2, Hitbox.Data[0].w, Hitbox.Data[0].h / 10 };
		SDL_SetRenderDrawColor(Core_Access.Application_Renderer, Underline_Color.r, Underline_Color.g,
			Underline_Color.b, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(Core_Access.Application_Renderer, &Underline_Rectangle);
		Clear_Renderer();
		SDL_RenderTexture(Core_Access.Application_Renderer, Button.Data[1], NULL, &Hitbox.Data[1]);
	} else {
		SDL_RenderTexture(Core_Access.Application_Renderer, Button.Data[0], NULL, &Hitbox.Data[0]);
	}
}

Texture_Array Load_Animated(std::string Path, const int Height,
	const bool Inverted, const std::vector<int> &Rotationals) {
	Path = "Assets/Core/Images/" + Path + ".png";
	SDL_Texture* Carrying_Texture = IMG_GenerateTexture(Core_Access.Application_Renderer, Path.c_str());
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
		SDL_Texture* Subtexture = SDL_GenerateTexture(Core_Access.Application_Renderer,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Full_Width, Height * 240);
		SDL_SetTextureBlendMode(Subtexture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core_Access.Application_Renderer, Subtexture);
		SDL_FRect Splitting_Rectangle = { 0.0f, Counter1 * Height * 240.0f, static_cast<float>(Full_Width), Height * 240.0f };
		SDL_RenderTexture(Core_Access.Application_Renderer, Carrying_Texture, &Splitting_Rectangle, NULL);
		SDL_SetRenderTarget(Core_Access.Application_Renderer, NULL);
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
				SDL_Texture* Subtexture2 = SDL_GenerateTexture(Core_Access.Application_Renderer,
					SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Height * 240, Height * 240);
					SDL_SetTextureBlendMode(Subtexture2, SDL_BLENDMODE_BLEND);
				SDL_SetRenderTarget(Core_Access.Application_Renderer, Subtexture2);
				SDL_RenderTextureRotated(Core_Access.Application_Renderer, Subtexture,
					NULL, NULL, 90 * Counter2, &Centrepoint, SDL_FLIP_NONE);
				Yield.Data[Index] = Subtexture2;
				Index++;
			}
			SDL_SetRenderTarget(Core_Access.Application_Renderer, NULL);
			SDL_DestroyTexture(Subtexture);
		} else {
			Yield.Data[Index] = Subtexture;
			Index++;
		}
	}
	SDL_Texture* Root_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Full_Width, Height * 240);
		SDL_SetTextureBlendMode(Root_Texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Root_Texture);
	int Minimum = 1;
	int Maximum = Yield.Length - 1;
	while (Minimum <= Maximum) {
		int Selector = Minimum;
		if (Inverted) {
			Selector = Maximum;
		}
		SDL_RenderTexture(Core_Access.Application_Renderer, Yield.Data[Selector], NULL, NULL);
		if (Inverted) {
			Maximum--;
		} else {
			Minimum++;
		}
	}
	SDL_SetRenderTarget(Core_Access.Application_Renderer, NULL);
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
			Yield.Data[Counter1].Data[Counter2] = SDL_GenerateTexture(Core_Access.Application_Renderer,
				SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Maximum, Maximum);
			SDL_SetTextureBlendMode(Yield.Data[Counter1].Data[Counter2], SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(Core_Access.Application_Renderer, Yield.Data[Counter1].Data[Counter2]);
			SDL_RenderTextureRotated(Core_Access.Application_Renderer, Subyield.Data[Counter2],
				NULL, NULL, Counter1 * 90, &Center, SDL_FLIP_NONE);
			SDL_SetRenderTarget(Core_Access.Application_Renderer, NULL);
		}
		Clear_Texture_Array(Subyield);
	}
	return Yield;
}

void Preload_Fonts() {
	Fonts_Access.Logo_Font = TTF_OpenFont("Assets/Core/Fonts/Oxygen/Oxygen_Regular.ttf",
		Settings_Access.Screen_Size * 32);
	Fonts_Access.Large_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings_Access.Screen_Size * 24);
	Fonts_Access.Text_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings_Access.Screen_Size * 18);
	Fonts_Access.Halftext_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings_Access.Screen_Size * 16);
	Fonts_Access.Subtext_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings_Access.Screen_Size * 12);
	Fonts_Access.Microtext_Font = TTF_OpenFont("Assets/Core/Fonts/Cantarell/Cantarell_Regular.ttf",
		Settings_Access.Screen_Size * 10);
	Fonts_Access.Terminal_Font = TTF_OpenFont("Assets/Core/Fonts/Oxygen/Oxygen_Regular.ttf",
		Settings_Access.Screen_Size * 12);
}

SDL_Texture* Preload_Sidebutton(std::string Path, SDL_FRect &Rectangle, float Y) {
	Path = "Assets/Core/Images/UI/Sidebar/" + Path + ".png";
	SDL_Surface* Surface = IMG_Load(Path.c_str());
	Rectangle = { static_cast<float>(660 - (Surface->w / 6)) * Settings_Access.Screen_Size,
		Y * Settings_Access.Screen_Size, static_cast<float>(Surface->w / 6) * Settings_Access.Screen_Size,
		static_cast<float>(Surface->h / 6) * Settings_Access.Screen_Size };
	SDL_Texture* Texture = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Surface);
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
			(Counter1 * 30)) * Settings_Access.Screen_Size, 0, 0 };
		Yield.Data[Counter1] = Load_Button(Fonts_Access.Terminal_Font, Texts[Counter1],
			Rectangles.Data[Counter1], Colors_Access.Cherry_Blossom, Colors_Access.Pure_White);
		for (int Counter2 = 0; Counter2 < 2; Counter2++) {
			Rectangles.Data[Counter1].Data[Counter2].x += 210 * Settings_Access.Screen_Size;
		}
	}
	return Yield;
}

void Reload_Commandlist(Texture3_Array &Commandlist, Rect3_Array &Boxlist,
	std::vector<std::vector<std::string>> Contents) {
	Clear_Rect3_Array(Boxlist);
	Clear_Texture3_Array(Commandlist);
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
	Metadata_Access.TT_Texts[1] = { "Return" };
	Metadata_Access.TT_Parameters[1] = { { "transmit", "EXIT" } };
	Metadata_Access.TT_Types[1] = { Execute };
	for (int Counter = 0; Counter < Temporary_Access.Docks.size(); Counter++) {
		Metadata_Access.TT_Texts[1].push_back("Dock " + std::to_string(Counter + 1));
		Metadata_Access.TT_Parameters[1].push_back({ "transmit", "POS_DOCK_" +
			std::to_string(Counter + 1) });
	}
	Reload_Commandlist(Textures_Access.TT_Buttons, Rectangles_Access.TT_Buttons, Metadata_Access.TT_Texts);
}

void Preload_Assets() {
	Core_Access.Game_Texture = SDL_GenerateTexture(Core_Access.Application_Renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET, 640 * Settings_Access.Screen_Size, 360 * Settings_Access.Screen_Size);
	for (int Counter = 0; Counter < Metadata_Access.Machine_Count; Counter++) {
		Metadata_Access.Machine_Quirks.push_back({ false, false, false, false });
	}
	for (int Counter1 = 0; Counter1 < Metadata_Access.Quirk_Positions.size(); Counter1++) {
		for (int Counter2 = 0; Counter2 < Metadata_Access.Quirk_Positions[Counter1].size(); Counter2++) {
			Metadata_Access.Machine_Quirks[Metadata_Access.Quirk_Positions[Counter1][Counter2]][Counter1] = true;
		}
	}
	SDL_Surface* Carrying_Surface = nullptr;
	auto Preload_Texture = [&Carrying_Surface](std::string Path) {
		Path = "Assets/Core/Images/" + Path + ".png";
		Carrying_Surface = IMG_Load(Path.c_str());
		SDL_Texture* Carrying_Texture = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Carrying_Surface);
		SDL_DestroySurface(Carrying_Surface);
		return Carrying_Texture;
	};
	UI_Access.Maximum_Time_Frames = UI_Access.Frame_Rate;
	UI_Access.Maximum_Subtime_Frames = UI_Access.Frame_Rate / 3;
	UI_Access.Slider_Texts[5].resize(101, std::string());
	for (int Counter = 0; Counter < 101; Counter++) {
		UI_Access.Slider_Texts[5][Counter] = std::to_string(Counter) + "%";
	}
	const std::vector<int> Queried = {
		7,
		11,
		13
	};
	for (int Counter1 = 0; Counter1 < Queried.size(); Counter1++) {
		UI_Access.Slider_Texts[Queried[Counter1]].resize(UI_Access.Valve300_Postions.size(), std::string());
		for (int Counter2 = 0; Counter2 < UI_Access.Valve300_Postions.size(); Counter2++) {
			UI_Access.Slider_Texts[Queried[Counter1]][Counter2] = std::to_string(
				UI_Access.Valve300_Postions[Counter2]) + "L/s";
		}
	}
	UI_Access.Slider_Texts[10].resize(241, std::string());
	for (int Counter = 0; Counter < 241; Counter++) {
		UI_Access.Slider_Texts[10][Counter] = std::to_string(Counter * 5) + " °F";
	}
	UI_Access.Tile_Centrepoint = { 20.0f * Settings_Access.Screen_Size, 20.0f * Settings_Access.Screen_Size };
	Audio_Access.Load(&Audio_Access.Primary_Ambience, "Assets/Core/Audio/Ambient/Background.wav");
	Audio_Access.Load(&Audio_Access.Filtration_Loop, "Assets/Core/Audio/Machines/Filtration_Loop.wav");
	Audio_Access.Load(&Audio_Access.Ram_Loop, "Assets/Core/Audio/Machines/Ram_Loop.wav");
	Audio_Access.Load(&Audio_Access.Click, "Assets/Core/Audio/UI/Click.wav");
	Rectangles_Access.Return.Length = 2;
	Rectangles_Access.Return.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rectangles_Access.Return.Data[0] = { 10.0f * Settings_Access.Screen_Size,
		334.0f * Settings_Access.Screen_Size, 0, 0 };
	Rectangles_Access.New_Game.Length = 2;
	Rectangles_Access.New_Game.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rectangles_Access.New_Game.Data[0] = { LDE_INVALID, 160.0f * Settings_Access.Screen_Size, 0, 0 };
	Rectangles_Access.Settings.Length = 2;
	Rectangles_Access.Settings.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rectangles_Access.Settings.Data[0] = { LDE_INVALID, 190.0f * Settings_Access.Screen_Size, 0, 0 };
	Rectangles_Access.Update_Logs.Length = 2;
	Rectangles_Access.Update_Logs.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rectangles_Access.Update_Logs.Data[0] = { LDE_INVALID, 220.0f * Settings_Access.Screen_Size, 0, 0 };
	Rectangles_Access.Credits.Length = 2;
	Rectangles_Access.Credits.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rectangles_Access.Credits.Data[0] = { LDE_INVALID, 250.0f * Settings_Access.Screen_Size, 0, 0 };
	Rectangles_Access.Quit_Game.Length = 2;
	Rectangles_Access.Quit_Game.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rectangles_Access.Quit_Game.Data[0] = { LDE_INVALID, 280.0f * Settings_Access.Screen_Size, 0, 0 };
	Rectangles_Access.Apply.Length = 2;
	Rectangles_Access.Apply.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rectangles_Access.Apply.Data[0] = { 60.0f * Settings_Access.Screen_Size,
		334.0f * Settings_Access.Screen_Size, 0, 0 };
	Rectangles_Access.Cancel.Length = 2;
	Rectangles_Access.Cancel.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rectangles_Access.Cancel.Data[0] = { 110.0f * Settings_Access.Screen_Size,
		334.0f * Settings_Access.Screen_Size, 0, 0 };
	Rectangles_Access.Next_Day.Length = 2;
	Rectangles_Access.Next_Day.Data = static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	Rectangles_Access.Next_Day.Data[0] = { LDE_INVALID, 300.0f * Settings_Access.Screen_Size, 0, 0 };
	UI_Access.Map_X = (40 * LDE_GRIDSIZE) - 640 + LDE_BUFFERSIZE;
	UI_Access.Map_Y = (40 * LDE_GRIDSIZE) - 360 + LDE_BUFFERSIZE;
	Rectangles_Access.Subcategories.Length = Metadata_Access.Subcategory_Positions.size();
	Rectangles_Access.Subcategories.Data = static_cast<Rect2_Array*>(
		malloc(sizeof(Rect2_Array) * Metadata_Access.Subcategory_Positions.size()));
	Textures_Access.Subcategories.Length = Metadata_Access.Subcategory_Positions.size();
	Textures_Access.Subcategories.Data = static_cast<Texture2_Array*>(
		malloc(sizeof(Texture2_Array) * Metadata_Access.Subcategory_Positions.size()));
	for (int Counter1 = 0; Counter1 < Metadata_Access.Subcategory_Positions.size(); Counter1++) {
		Rectangles_Access.Subcategories.Data[Counter1].Length = 
			Metadata_Access.Subcategory_Positions[Counter1].size();
		Rectangles_Access.Subcategories.Data[Counter1].Data = static_cast<Rect_Array*>(
			malloc(sizeof(Rect_Array) * Metadata_Access.Subcategory_Positions[Counter1].size()));
		Textures_Access.Subcategories.Data[Counter1].Length = 
			Metadata_Access.Subcategory_Positions[Counter1].size();
		Textures_Access.Subcategories.Data[Counter1].Data = static_cast<Texture_Array*>(
			malloc(sizeof(Texture_Array) * Metadata_Access.Subcategory_Positions[Counter1].size()));
		for (int Counter2 = 0; Counter2 < Metadata_Access.Subcategory_Positions[Counter1].size(); Counter2++) {
			Rectangles_Access.Subcategories.Data[Counter1].Data[Counter2].Length = 2;
			Rectangles_Access.Subcategories.Data[Counter1].Data[Counter2].Data =
				static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
			Rectangles_Access.Subcategories.Data[Counter1].Data[Counter2].Data[0] = {
				LDE_INVALID, static_cast<float>(40 + (Counter2 *
				30)) * Settings_Access.Screen_Size, 0, 0 };
			Textures_Access.Subcategories.Data[Counter1].Data[Counter2] =
				Load_Button(Fonts_Access.Halftext_Font, Metadata_Access.Subcategory_Names[
				Metadata_Access.Subcategory_Positions[Counter1][Counter2]],
				Rectangles_Access.Subcategories.Data[Counter1].Data[Counter2]);
		}
	}
	Rectangles_Access.Subcontents.Data = static_cast<Rect2_Array*>(malloc(
		sizeof(Rect2_Array) * Metadata_Access.Subcontents.size()));
	Rectangles_Access.Subcontents.Length = Metadata_Access.Subcontents.size();
	Textures_Access.Subcontents.Data = static_cast<Texture2_Array*>(
		malloc(sizeof(Texture2_Array) * Metadata_Access.Subcontents.size()));
	Textures_Access.Subcontents.Length = Metadata_Access.Subcontents.size();
	for (int Counter1 = 0; Counter1 < Metadata_Access.Subcontents.size(); Counter1++) {
		Rectangles_Access.Subcontents.Data[Counter1].Data = static_cast<Rect_Array*>(malloc(
			sizeof(Rect_Array) * Metadata_Access.Subcontents[Counter1].size()));
		Rectangles_Access.Subcontents.Data[Counter1].Length = Metadata_Access.Subcontents[Counter1].size();
		Textures_Access.Subcontents.Data[Counter1].Data = static_cast<Texture_Array*>(
			malloc(sizeof(Texture_Array) * Metadata_Access.Subcontents[Counter1].size()));
		Textures_Access.Subcontents.Data[Counter1].Length = Metadata_Access.Subcontents[Counter1].size();
		for (int Counter2 = 0; Counter2 < Metadata_Access.Subcontents[Counter1].size(); Counter2++) {
			Rectangles_Access.Subcontents.Data[Counter1].Data[Counter2].Length = 2;
			Rectangles_Access.Subcontents.Data[Counter1].Data[Counter2].Data =
				static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
			Rectangles_Access.Subcontents.Data[Counter1].Data[Counter2].Data[0] = {
				LDE_INVALID, static_cast<float>(40 + (Counter2 * 30)) *
				Settings_Access.Screen_Size, 0, 0 };
			Textures_Access.Subcontents.Data[Counter1].Data[Counter2] =
				Load_Button(Fonts_Access.Halftext_Font, Metadata_Access.Machine_Names[
				Metadata_Access.Subcontents[Counter1][Counter2]],
				Rectangles_Access.Subcontents.Data[Counter1].Data[Counter2]);
		}
	}
	Rectangles_Access.Item_Labels.Length = Metadata_Access.Item_Labels.size();
	Rectangles_Access.Item_Labels.Data = static_cast<Rect2_Array*>(
		malloc(sizeof(Rect2_Array) * Metadata_Access.Item_Labels.size()));
	Textures_Access.Item_Labels.Data = static_cast<Texture2_Array*>(
		malloc(sizeof(Texture2_Array) *	Metadata_Access.Item_Labels.size()));
	Textures_Access.Item_Labels.Length = Metadata_Access.Item_Labels.size();
	for (int Counter1 = 0; Counter1 < Metadata_Access.Item_Labels.size(); Counter1++) {
		Rectangles_Access.Item_Labels.Data[Counter1].Data = static_cast<Rect_Array*>(
			malloc(sizeof(Rect_Array) * Metadata_Access.Item_Labels[Counter1].size()));
		Rectangles_Access.Item_Labels.Data[Counter1].Length =
			Metadata_Access.Item_Labels[Counter1].size();
		Textures_Access.Item_Labels.Data[Counter1].Data = static_cast<Texture_Array*>(
			malloc(sizeof(Texture_Array) * Metadata_Access.Item_Labels[Counter1].size()));
		Textures_Access.Item_Labels.Data[Counter1].Length =
			Metadata_Access.Item_Labels[Counter1].size();
		for (int Counter2 = 0; Counter2 < Metadata_Access.Item_Labels[Counter1].size(); Counter2++) {
			Rectangles_Access.Item_Labels.Data[Counter1].Data[Counter2].Length = 2;
			Rectangles_Access.Item_Labels.Data[Counter1].Data[Counter2].Data =
				static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
			Rectangles_Access.Item_Labels.Data[Counter1].Data[Counter2].Data[0] =
				{ LDE_INVALID, static_cast<float>(40 + ((Counter2 + Metadata_Access
				.Subcategory_Positions[Counter1].size()) * 30)) * Settings_Access.Screen_Size, 0, 0 };
			Textures_Access.Item_Labels.Data[Counter1].Data[Counter2] =
				Load_Button(Fonts_Access.Halftext_Font,	Metadata_Access.Machine_Names[
				Metadata_Access.Item_Labels[Counter1][Counter2]], Rectangles_Access
				.Item_Labels.Data[Counter1].Data[Counter2]);
		}
	}
	Textures_Access.Categories.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * Metadata_Access.Categories.size()));
	Textures_Access.Categories.Length = Metadata_Access.Categories.size();
	Rectangles_Access.Categories.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * Metadata_Access.Categories.size()));
	Rectangles_Access.Categories.Length = Metadata_Access.Categories.size();
	for (int Counter = 0; Counter < Metadata_Access.Categories.size(); Counter++) {
		Rectangles_Access.Categories.Data[Counter].Data = static_cast<
			SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rectangles_Access.Categories.Data[Counter].Length = 2;
		Rectangles_Access.Categories.Data[Counter].Data[0] = {
			LDE_INVALID, static_cast<float>(40 + (Counter * 30)) *
			Settings_Access.Screen_Size, 0, 0 };
		Textures_Access.Categories.Data[Counter] = Load_Button(
			Fonts_Access.Text_Font, Metadata_Access.Categories[Counter],
			Rectangles_Access.Categories.Data[Counter]);
	}
	Rectangles_Access.Error_Exit.Length = 2;
	Rectangles_Access.Error_Exit.Data = static_cast<SDL_FRect*>(
		calloc(2, sizeof(SDL_FRect)));
	Rectangles_Access.Error_Exit.Data[0] = { LDE_INVALID, Settings_Access.Screen_Size * 50.0f, 0, 0 };
	Textures_Access.Error_Exit = Load_Button(Fonts_Access.Terminal_Font, "Exit",
		Rectangles_Access.Error_Exit, Colors_Access.Cherry_Blossom, Colors_Access.Pure_White);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rectangles_Access.Error_Exit.Data[Counter].x += Settings_Access.Screen_Size * 210;
	}
	Textures_Access.MSP_Buttons = Preload_Terminal_Sidebar(
		{ "Tank Info", "Fish Info", "Fill Pool", "Empty Pool" },
		Rectangles_Access.MSP_Buttons);
	Textures_Access.SD_Buttons = Preload_Terminal_Sidebar(
		{ "Export Items", "View Manifest", "Drain Tank 1",
		"Drain Tank 2" }, Rectangles_Access.SD_Buttons);
	Textures_Access.HX_Buttons = Preload_Terminal_Sidebar(
		{ "View Status" }, Rectangles_Access.HX_Buttons);
	Textures_Access.MT_Buttons = Preload_Terminal_Sidebar(
		{ "View Status" }, Rectangles_Access.MT_Buttons);
	Textures_Access.New.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 4));
	Textures_Access.Load.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 4));
	Textures_Access.Clear.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 4));
	Textures_Access.New.Length = 4;
	Textures_Access.Load.Length = 4;
	Textures_Access.Clear.Length = 4;
	Rectangles_Access.New.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 4));
	Rectangles_Access.Load.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 4));
	Rectangles_Access.Clear.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 4));
	Rectangles_Access.New.Length = 4;
	Rectangles_Access.Load.Length = 4;
	Rectangles_Access.Clear.Length = 4;
	for (int Counter = 0; Counter < 4; Counter++) {
		Rectangles_Access.New.Data[Counter].Length = 2;
		Rectangles_Access.New.Data[Counter].Data = static_cast<
			SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rectangles_Access.New.Data[Counter].Data[0] = {
			340.0f * Settings_Access.Screen_Size, static_cast<float>(
			160 + (Counter * 40)) * Settings_Access.Screen_Size, 0, 0 };
		Textures_Access.New.Data[Counter] = Load_Button(Fonts_Access.Subtext_Font,
			"New Factory", Rectangles_Access.New.Data[Counter]);
		Rectangles_Access.Load.Data[Counter].Length = 2;
		Rectangles_Access.Load.Data[Counter].Data = static_cast<
			SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rectangles_Access.Load.Data[Counter].Data[0] = {
			340.0f * Settings_Access.Screen_Size, static_cast<float>(
			160 + (Counter * 40)) * Settings_Access.Screen_Size, 0, 0 };
		Textures_Access.Load.Data[Counter] = Load_Button(Fonts_Access.Subtext_Font,
			"Load Factory", Rectangles_Access.Load.Data[Counter]);
		Rectangles_Access.Clear.Data[Counter].Length = 2;
		Rectangles_Access.Clear.Data[Counter].Data = static_cast<
			SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rectangles_Access.Clear.Data[Counter].Data[0] = {
			490.0f * Settings_Access.Screen_Size, static_cast<float>(
			160 + (Counter * 40)) * Settings_Access.Screen_Size, 0, 0 };
		Textures_Access.Clear.Data[Counter] = Load_Button(Fonts_Access.Subtext_Font,
			"Clear Factory", Rectangles_Access.Clear.Data[Counter]);
	}
	std::string Tool_Texts[5] = { "Building", "Deleting", "Inspecting", "Wiring", "Plumbing" };
	Textures_Access.Tool.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 5));
	Textures_Access.Tool.Length = 5;
	for (int Counter = 0; Counter < 5; Counter++) {
		std::string Tool_String = "[" + std::to_string(Counter + 1) + "] " + Tool_Texts[Counter];
		SDL_Surface* Text_Surface = TTF_RenderText_Blended(Fonts_Access.Halftext_Font,
			Tool_String.c_str(), Tool_String.size(), Colors_Access.Abyss_Black);
		Rectangles_Access.Tool[Counter] = { (320.0f * Settings_Access.Screen_Size) -
			static_cast<float>(Text_Surface->w / 2), 335.0f * Settings_Access.Screen_Size,
			static_cast<float>(Text_Surface->w), static_cast<float>(Text_Surface->h) };
		Textures_Access.Tool.Data[Counter] = SDL_GenerateTextureFromSurface(
			Core_Access.Application_Renderer, Text_Surface);
		SDL_DestroySurface(Text_Surface);
	}
	Rectangles_Access.Anti_Aliasing.Length = 2;
	Rectangles_Access.Anti_Aliasing.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 2));
	Textures_Access.Anti_Aliasing.Length = 2;
	for (int Counter = 0; Counter < 2; Counter++) {
		Rectangles_Access.Anti_Aliasing.Data[Counter].Length = 2;
		Rectangles_Access.Anti_Aliasing.Data[Counter].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rectangles_Access.Anti_Aliasing.Data[Counter].Data[0] = { 370.0f *
			Settings_Access.Screen_Size, 300.0f * Settings_Access.Screen_Size, 0, 0 };
	}
	Textures_Access.Anti_Aliasing.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 2));
	Textures_Access.Anti_Aliasing.Data[0] = Load_Button(Fonts_Access.Subtext_Font,
		"Scaling Quality: High", Rectangles_Access.Anti_Aliasing.Data[0]);
	Textures_Access.Anti_Aliasing.Data[1] = Load_Button(Fonts_Access.Subtext_Font,
		"Scaling Quality: Low", Rectangles_Access.Anti_Aliasing.Data[1]);
	Rectangles_Access.V_Sync.Length = 2;
	Rectangles_Access.V_Sync.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 2));
	for (int Counter = 0; Counter < 2; Counter++) {
		Rectangles_Access.V_Sync.Data[Counter].Length = 2;
		Rectangles_Access.V_Sync.Data[Counter].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
	}
	Rectangles_Access.V_Sync.Data[0].Data[0] = { 370.0f * Settings_Access
		.Screen_Size, 320.0f * Settings_Access.Screen_Size, 0, 0 };
	Rectangles_Access.V_Sync.Data[1].Data[0] = { 370.0f * Settings_Access
		.Screen_Size, 320.0f * Settings_Access.Screen_Size, 0, 0 };
	Textures_Access.V_Sync.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 2));
	Textures_Access.V_Sync.Length = 2;
	Textures_Access.V_Sync.Data[0] = Load_Button(Fonts_Access.Subtext_Font,
		"V-Sync: Off", Rectangles_Access.V_Sync.Data[0]);
	Textures_Access.V_Sync.Data[1] = Load_Button(Fonts_Access.Subtext_Font,
		"V-Sync: On", Rectangles_Access.V_Sync.Data[1]);
	Textures_Access.Sort.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 2));
	Textures_Access.Sort.Length = 2;
	Rectangles_Access.Sort.Length = 2;
	Rectangles_Access.Sort.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 2));
	for (int Counter = 0; Counter < 2; Counter++) {
		Rectangles_Access.Sort.Data[Counter].Length = 2;
		Rectangles_Access.Sort.Data[Counter].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rectangles_Access.Sort.Data[Counter].Data[0] =
			{ LDE_INVALID, 334.0f * Settings_Access.Screen_Size, 0, 0 };
	}
	Textures_Access.Sort.Data[0] = Load_Button(Fonts_Access.Subtext_Font,
		"Sort: Newest", Rectangles_Access.Sort.Data[0]);
	Textures_Access.Sort.Data[1] = Load_Button(Fonts_Access.Subtext_Font,
		"Sort: Oldest", Rectangles_Access.Sort.Data[1]);
	Textures_Access.TBW_Texture.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 2));
	Textures_Access.TBW_Texture.Length = 2;
	Rectangles_Access.TBW_Rectangle.Length = 2;
	Rectangles_Access.TBW_Rectangle.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 2));
	for (int Counter = 0; Counter < 2; Counter++) {
		Rectangles_Access.TBW_Rectangle.Data[Counter].Length = 2;
		Rectangles_Access.TBW_Rectangle.Data[Counter].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rectangles_Access.TBW_Rectangle.Data[Counter].Data[0] =
			{ 0, 334.0f * Settings_Access.Screen_Size, 0, 0 };
	}
	Textures_Access.TBW_Texture.Data[0] = Load_Button(Fonts_Access.Subtext_Font,
		"Go to bottom", Rectangles_Access.TBW_Rectangle.Data[0]);
	Textures_Access.TBW_Texture.Data[1] = Load_Button(Fonts_Access.Subtext_Font,
		"Go to top", Rectangles_Access.TBW_Rectangle.Data[1]);
	for (int Counter = 0; Counter < 2; Counter++) {
		Rectangles_Access.TBW_Rectangle.Data[Counter].Data[0].x =
			(630 * Settings_Access.Screen_Size) -
			Rectangles_Access.TBW_Rectangle.Data[Counter].Data[0].w;
		Rectangles_Access.TBW_Rectangle.Data[Counter].Data[1].x =
			Rectangles_Access.TBW_Rectangle.Data[Counter].Data[0].x +
			(Rectangles_Access.TBW_Rectangle.Data[Counter].Data[0].w / 2) -
			(Rectangles_Access.TBW_Rectangle.Data[Counter].Data[1].w / 2);
	}
	Rectangles_Access.Tile_1x1 = { 0, 0, 40.0f * Settings_Access.Screen_Size,
		40.0f * Settings_Access.Screen_Size };
	Rectangles_Access.Tile_1x2 = { 0, 0, 40.0f * Settings_Access.Screen_Size,
		80.0f * Settings_Access.Screen_Size };
	Rectangles_Access.Tile_2x1 = { 0, 0, 80.0f * Settings_Access.Screen_Size,
		40.0f * Settings_Access.Screen_Size };
	Rectangles_Access.Tile_2x2 = { 0, 0, 80.0f * Settings_Access.Screen_Size,
		80.0f * Settings_Access.Screen_Size };
	Rectangles_Access.Tile_2x3 = { 0, 0, 80.0f * Settings_Access.Screen_Size,
		120.0f * Settings_Access.Screen_Size };
	Rectangles_Access.Tile_3x2 = { 0, 0, 120.0f * Settings_Access.Screen_Size,
		80.0f * Settings_Access.Screen_Size };
	Rectangles_Access.Tile_3x3 = { 0, 0, 120.0f * Settings_Access.Screen_Size,
		120.0f * Settings_Access.Screen_Size };
	Rectangles_Access.Tile_3x4 = { 0, 0, 120.0f * Settings_Access.Screen_Size,
		160.0f * Settings_Access.Screen_Size };
	Rectangles_Access.Tile_4x3 = { 0, 0, 160.0f * Settings_Access.Screen_Size,
		120.0f * Settings_Access.Screen_Size };
	Rectangles_Access.Tile_4x6 = { 0, 0, 160.0f * Settings_Access.Screen_Size,
		240.0f * Settings_Access.Screen_Size };
	Rectangles_Access.Tile_6x4 = { 0, 0, 240.0f * Settings_Access.Screen_Size,
		160.0f * Settings_Access.Screen_Size };
	Rectangles_Access.Tile_6x8 = { 0, 0, 240.0f * Settings_Access.Screen_Size,
		320.0f * Settings_Access.Screen_Size };
	Rectangles_Access.Tile_8x6 = { 0, 0, 320.0f * Settings_Access.Screen_Size,
		240.0f * Settings_Access.Screen_Size };
	Carrying_Surface = TTF_RenderText_Blended(Fonts_Access.Large_Font, "Fish Factory Help",
		17, Colors_Access.Abyss_Black);
	Rectangles_Access.Help_Content[0] = { (320 * Settings_Access.Screen_Size) -
		static_cast<float>(Carrying_Surface->w / 2), 20.0f * Settings_Access.Screen_Size,
		static_cast<float>(Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
	Textures_Access.Help_Content.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 2));
	Textures_Access.Help_Content.Length = 2;
	Textures_Access.Help_Content.Data[0] = SDL_GenerateTextureFromSurface(
		Core_Access.Application_Renderer, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	Carrying_Surface = TTF_RenderText_Blended(Fonts_Access.Large_Font, "Catalog",
		7, Colors_Access.Abyss_Black);
	Rectangles_Access.Recipe_Content = { (320 * Settings_Access.Screen_Size) -
		static_cast<float>(Carrying_Surface->w / 2), 20.0f * Settings_Access.Screen_Size,
		static_cast<float>(Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
	Textures_Access.Recipe_Content = SDL_GenerateTextureFromSurface(
		Core_Access.Application_Renderer, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	std::vector<std::string> Captions = { "Resolution", "Framerate Cap",
		"Volume", "Fullscreen", "Toggles", "Keybinds" };
	Rectangles_Access.Settings_Label.Length = Captions.size();
	Rectangles_Access.Settings_Label.Data = static_cast<SDL_FRect*>(
		malloc(sizeof(SDL_FRect) * Captions.size()));
	Textures_Access.Settings_Label.Length = Captions.size();
	Textures_Access.Settings_Label.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * Captions.size()));
	for (int Counter = 0; Counter < Captions.size(); Counter++) {
		Carrying_Surface = TTF_RenderText_Blended(Fonts_Access.Halftext_Font, Captions[Counter].c_str(),
		Captions[Counter].size(), Colors_Access.Abyss_Black);
		Textures_Access.Settings_Label.Data[Counter] =
			SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Carrying_Surface);
		Rectangles_Access.Settings_Label.Data[Counter] = { 10.0f * Settings_Access.Screen_Size, 0,
			static_cast<float>(Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
		SDL_DestroySurface(Carrying_Surface);
	}
	Rectangles_Access.Settings_Label.Data[0].y = 10;
	Rectangles_Access.Settings_Label.Data[1].y = 100;
	Rectangles_Access.Settings_Label.Data[2].y = 170;
	Rectangles_Access.Settings_Label.Data[3].y = 240;
	Rectangles_Access.Settings_Label.Data[4].y = 270;
	Rectangles_Access.Settings_Label.Data[4].x = 330 * Settings_Access.Screen_Size;
	Rectangles_Access.Settings_Label.Data[5].y = 10;
	Rectangles_Access.Settings_Label.Data[5].x = 330 * Settings_Access.Screen_Size;
	for (int Counter = 0; Counter < Captions.size(); Counter++) {
		Rectangles_Access.Settings_Label.Data[Counter].y *= Settings_Access.Screen_Size;
	}
	Rectangles_Access.Save_Settings.Length = 2;
	Rectangles_Access.Save_Settings.Data = static_cast<SDL_FRect*>(
		calloc(2, sizeof(SDL_FRect)));
	Rectangles_Access.Save_Settings.Data[0] = { 0, 334.0f * Settings_Access.Screen_Size, 0, 0 };
	Textures_Access.Save_Settings = Load_Button(Fonts_Access.Subtext_Font, "Save Settings",
		Rectangles_Access.Save_Settings);
	Rectangles_Access.Save_Settings.Data[0].x = (630 * Settings_Access.Screen_Size) -
		Rectangles_Access.Save_Settings.Data[0].w;
	Rectangles_Access.Save_Settings.Data[1].x = Rectangles_Access.Save_Settings.Data[0].x +
		(Rectangles_Access.Save_Settings.Data[0].w / 2) - (Rectangles_Access.Save_Settings.Data[1].w / 2);
	SDL_Texture* Carrying_Texture = Preload_Texture("UI/Backgrounds/Doors");
	Textures_Access.Door.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 2));
	Textures_Access.Door.Length = 2;
	for (int Counter = 0; Counter < 2; Counter++) {
		Textures_Access.Door.Data[Counter] = SDL_GenerateTexture(
			Core_Access.Application_Renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, 320 * Settings_Access.Screen_Size, 360 *
			Settings_Access.Screen_Size);
		SDL_SetTextureBlendMode(Textures_Access.Door.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(Core_Access.Application_Renderer, Textures_Access.Door.Data[Counter]);
		SDL_FRect Half_Rectangle = { 1920.0f * Counter, 0, 1920, 2160 };
		Rectangles_Access.Door[Counter].w = 320 * Settings_Access.Screen_Size;
		Rectangles_Access.Door[Counter].h = 360 * Settings_Access.Screen_Size;
		SDL_RenderTexture(Core_Access.Application_Renderer, Carrying_Texture, &Half_Rectangle, NULL);
	}
	SDL_SetRenderTarget(Core_Access.Application_Renderer, NULL);
	SDL_DestroyTexture(Carrying_Texture);
	Rectangles_Access.Clear_Tutorial.Length = 2;
	Rectangles_Access.Clear_Tutorial.Data = static_cast<SDL_FRect*>(
		calloc(2, sizeof(SDL_FRect)));
	Rectangles_Access.Clear_Tutorial.Data[0] = { LDE_INVALID, 160, 0, 0 };
	Textures_Access.Clear_Tutorial = Load_Button(Fonts_Access.Halftext_Font,
		"Cancel Tutorial", Rectangles_Access.Clear_Tutorial);
	std::string Tutorial_Labels[3] = { "The Command Platform", "Simple Generator", "[NF] Simple Fish Farm" };
	Textures_Access.Tutorials.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 3));
	Rectangles_Access.Tutorials.Length = 3;
	Rectangles_Access.Tutorials.Data =
		static_cast<Rect_Array*>(malloc(sizeof(Rect_Array) * 3));
	Textures_Access.Tutorials.Length = 3;
	for (int Counter = 0; Counter < 3; Counter++) {
		Rectangles_Access.Tutorials.Data[Counter].Length = 2;
		Rectangles_Access.Tutorials.Data[Counter].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rectangles_Access.Tutorials.Data[Counter].Data[0] = {
			LDE_INVALID, static_cast<float>(160 + (Counter * 40)) *
			Settings_Access.Screen_Size, 0, 0 };
		Textures_Access.Tutorials.Data[Counter] = Load_Button(Fonts_Access.Halftext_Font,
			Tutorial_Labels[Counter].c_str(), Rectangles_Access.Tutorials.Data[Counter]);
	}
	Rectangles_Access.Tutorial_Hitbox.Length = 2;
	Rectangles_Access.Tutorial_Hitbox.Data = static_cast<SDL_FRect*>(
		malloc(sizeof(SDL_FRect) * 2));
	std::string Cheat_Labels[2] = { "Money Generator", "Fluid Generator" };
	Rectangles_Access.Cheats.Length = 2;
	Rectangles_Access.Cheats.Data = static_cast<Rect_Array*>(
		malloc(sizeof(Rect_Array) * 2));
	Textures_Access.Cheats.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 2));
	Textures_Access.Cheats.Length = 2;
	for (int Counter = 0; Counter < 2; Counter++) {
		Rectangles_Access.Cheats.Data[Counter].Length = 2;
		Rectangles_Access.Cheats.Data[Counter].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Rectangles_Access.Cheats.Data[Counter].Data[0] = {
			LDE_INVALID, static_cast<float>(160 + (Counter * 40)) *
			Settings_Access.Screen_Size, 0, 0 };
		Textures_Access.Cheats.Data[Counter] = Load_Button(Fonts_Access.Halftext_Font,
			Cheat_Labels[Counter].c_str(), Rectangles_Access.Cheats.Data[Counter]);
	}
	std::string Keycore = SDL_GetKeyName(Keybinds_Access.Keybind_List[13]);
	Keycore = "Press \"" + Keycore + "\" to close.";
	Carrying_Surface = TTF_RenderText_Blended(Fonts_Access.Text_Font, Keycore.c_str(),
		Keycore.size(), Colors_Access.Abyss_Black);
	Rectangles_Access.Help_Content[1] = { (320 * Settings_Access.Screen_Size) -
		static_cast<float>(Carrying_Surface->w / 2), 320.0f * Settings_Access.Screen_Size,
		static_cast<float>(Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
	Textures_Access.Help_Content.Data[1] = SDL_GenerateTextureFromSurface(
		Core_Access.Application_Renderer, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	Textures_Access.Floor_Texture = Preload_Texture("Tiles/Ground");
	Textures_Access.Frame_Texture = Preload_Texture("Tiles/Frame");
	Textures_Access.Tile_Texture = Preload_Texture("Tiles/Tile");
	Textures_Access.R_Pipe = Load_Modular("Assets/Core/Images/Machines/R_Pipe.png", 6);
	Textures_Access.L_Pipe = Load_Modular("Assets/Core/Images/Machines/L_Pipe.png", 6);
	Textures_Access.MS_Pool = Load_Modular("Assets/Core/Images/Machines/MSP.png", 6);
	Textures_Access.Arrow = Load_Rotational("UI/Other/Direction");
	Textures_Access.S_Dock = Load_Rotational("Machines/S_Dock");
	Textures_Access.Tunnel = Load_Rotational("Other/Tunnel");
	Rectangles_Access.Tunnel.Length = 2;
	Rectangles_Access.Tunnel.Data = static_cast<SDL_FRect*>(
		malloc(sizeof(SDL_FRect) * 2));
	Rectangles_Access.Tunnel.Data[0] = {
		0,
		0,
		Settings_Access.Screen_Size * 240.0f,
		Settings_Access.Screen_Size * 90.0f
	};
	Rectangles_Access.Tunnel.Data[1] = {
		0,
		0,
		Settings_Access.Screen_Size * 90.0f,
		Settings_Access.Screen_Size * 240.0f
	};
	Textures_Access.Cap = Load_Mirrored("Images/UI/Other/UI_Cap", Rectangles_Access.Cap);
	Rectangles_Access.Cap.y = Settings_Access.Screen_Size * 330;
	Textures_Access.Cap_Button = Load_Mirrored_Button("Images/UI/Other/UI_Arrow",
		Rectangles_Access.Cap_Button);
	Rectangles_Access.Cap_Button.y = Settings_Access.Screen_Size * 330;
	Rectangles_Access.Cap_Hitbox.Length = 2;
	Rectangles_Access.Cap_Hitbox.Data = static_cast<SDL_FRect*>(malloc(sizeof(SDL_FRect) * 2));
	Carrying_Surface = IMG_Load("Assets/Core/Images/UI/Other/Logo.png");
	Textures_Access.Logo = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Carrying_Surface);
	SDL_SetWindowIcon(Core_Access.Application_Window, Carrying_Surface);
	SDL_DestroySurface(Carrying_Surface);
	SDL_GetTextureSize(Textures_Access.Logo, &Rectangles_Access.Logo.w,
		&Rectangles_Access.Logo.h);
	Rectangles_Access.Logo.w = static_cast<int>(((double)Rectangles_Access.Logo.w / 6) *
		Settings_Access.Screen_Size);
	Rectangles_Access.Logo.h = static_cast<int>(((double)Rectangles_Access.Logo.h / 6) *
		Settings_Access.Screen_Size);
	Rectangles_Access.Logo.x = (315 * Settings_Access.Screen_Size) - Rectangles_Access.Logo.w;
	Rectangles_Access.Logo.y = 32 * Settings_Access.Screen_Size;
	Textures_Access.Crosshair = Preload_Texture("UI/Other/Crosshair");
	Textures_Access.Cursor = Preload_Texture("UI/Other/Cursor");
	Textures_Access.Cursor_Core = Preload_Texture("UI/Other/Cursor_Core");
	Textures_Access.Sapling = Preload_Texture("UI/Other/Sapling");
	Rectangles_Access.Sapling = Rectangles_Access.Tile_1x1;
	Textures_Access.Node = Preload_Texture("UI/Other/Node");
	Rectangles_Access.Node = Rectangles_Access.Tile_1x1;
	Textures_Access.Path_Arrow = Preload_Texture("UI/Other/Path_Arrow");
	Carrying_Surface = IMG_Load("Assets/Core/Images/UI/Backgrounds/Scrollframe.png");
	Textures_Access.Log_Background = SDL_GenerateTextureFromSurface(
		Core_Access.Application_Renderer, Carrying_Surface);
	Rectangles_Access.Log_Background = { 0, 0, static_cast<float>(Carrying_Surface->w / 6) *
		Settings_Access.Screen_Size, static_cast<float>(Carrying_Surface->h / 6) * Settings_Access.Screen_Size };
	SDL_DestroySurface(Carrying_Surface);
	Textures_Access.Saveloader = Preload_Texture("UI/Backgrounds/Saveloader");
	Rectangles_Access.Saveloader = { 0, 0, 640.0f * Settings_Access.Screen_Size,
		360.0f * Settings_Access.Screen_Size };
	Textures_Access.Help_Sidebutton = Preload_Sidebutton("Help",
		Rectangles_Access.Help, 60);
	Textures_Access.Save_Sidebutton = Preload_Sidebutton("Save",
		Rectangles_Access.Save, 84);
	Textures_Access.Recipe_Sidebutton = Preload_Sidebutton("Recipe",
		Rectangles_Access.Recipe, 108);
	Textures_Access.Exit_Sidebutton = Preload_Sidebutton("Exit",
		Rectangles_Access.Exit, 132);
	Textures_Access.Quirk.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 4));
	Textures_Access.Quirk_Label.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 4));
	Textures_Access.Quirk.Length = 4;
	Textures_Access.Quirk_Label.Length = 4;
	SDL_DestroySurface(Carrying_Surface);
	Textures_Access.Quirk.Data[0] = Preload_Texture("UI/Quirks/No_Rotation");
	Textures_Access.Quirk.Data[1] = Preload_Texture("UI/Quirks/Modular");
	Textures_Access.Quirk.Data[2] = Preload_Texture("UI/Quirks/Interactable");
	Textures_Access.Quirk.Data[3] = Preload_Texture("UI/Quirks/All_Direction");
	std::string Quirk_Texts[4] = { "Non-Rotatable", "Modular", "Interactable", "Omnidirectional" };
	for (int Counter = 0; Counter < 4; Counter++) {
		Carrying_Surface = TTF_RenderText_Blended(Fonts_Access.Subtext_Font, Quirk_Texts[Counter].c_str(),
			Quirk_Texts[Counter].size(), Colors_Access.Abyss_Black);
		Textures_Access.Quirk_Label.Data[Counter] = SDL_GenerateTextureFromSurface(
			Core_Access.Application_Renderer, Carrying_Surface);
		SDL_DestroySurface(Carrying_Surface);
	}
	Textures_Access.RFlash = Preload_Texture("Effects/Light");
	Rectangles_Access.RFlash = { 0, 0, 40.0f * Settings_Access
		.Screen_Size, 40.0f * Settings_Access.Screen_Size };
	Textures_Access.R_Pump = Load_Animated("Machines/R_Pump", 1, false, { 2, 3, 4 });
	Textures_Access.Incinerator = Load_Animated_Rotational("Machines/Incinerator", 1, true, { });
	Textures_Access.P_Generator = Preload_Texture("Machines/P_Generator");
	Textures_Access.F_Plant = Load_Animated("Machines/F_Plant", 3, true, { });
	Textures_Access.B_Generator = Load_Animated_Rotational("Machines/B_Generator", 3, true, { });
	Textures_Access.Distillery = Load_Animated_Rotational("Machines/Distillery", 2, false, { });
	Textures_Access.G_Bed = Load_Animated_Rotational("Machines/G_Bed", 3, true, { });
	Textures_Access.B_Scrubber = Load_Rotational("Machines/B_Scrubber");
	Textures_Access.MS_Controller = Preload_Texture("Machines/MS_Controller");
	Textures_Access.MS_Output = Preload_Texture("Machines/MS_Output");
	Textures_Access.MS_Input = Preload_Texture("Machines/MS_Input");
	Textures_Access.E_Plant = Load_Rotational("Machines/E_Plant");
	Textures_Access.F_Mixer = Load_Animated_Rotational("Machines/F_Mixer", 3, true, { });
	Textures_Access.Flowerpot = Preload_Texture("Machines/Flowerpot");
	Textures_Access.C_Node = Preload_Texture("Machines/C_Node");
	Textures_Access.G_Well = Load_Rotational("Machines/G_Well");
	Textures_Access.H_Exchanger= Load_Rotational("Machines/H_Exchanger");
	Textures_Access.C_Platform = Load_Rotational("Machines/C_Platform");
	Textures_Access.T_Tower = Load_Rotational("Machines/T_Tower");
	Textures_Access.A_Shelf = Load_Rotational("Machines/A_Shelf");
	Textures_Access.P_Wood = Preload_Texture("Tiles/P_Wood");
	Textures_Access.B_Tile = Preload_Texture("Tiles/B_Tile");
	Textures_Access.S_Carpet = Preload_Texture("Tiles/S_Carpet");
	Textures_Access.H_Strip = Preload_Texture("Tiles/H_Strip");
	Textures_Access.M_Generator = Preload_Texture("Cheats/M_Generator");
	Textures_Access.F_Generator = Preload_Texture("Cheats/F_Generator");
	Textures_Access.R_Intersection = Load_Rotational("Machines/R_Intersection");
	Textures_Access.L_Intersection = Load_Rotational("Machines/L_Intersection");
	Textures_Access.SC_Input = Load_Rotational("Machines/SC_Input");
	Textures_Access.SCH_Sink = Load_Rotational("Machines/SCH_Sink");
	Textures_Access.SC_Transferor = Load_Rotational("Machines/SC_Transferor");
	Textures_Access.SC_Output = Load_Rotational("Machines/SC_Output");
	Textures_Access.ST_Input = Load_Rotational("Machines/ST_Input");
	Textures_Access.STIT_Block = Load_Animated_Rotational("Machines/STIT_Block", 3, true, { });
	Textures_Access.ST_Output = Load_Animated_Rotational("Machines/ST_Output", 2, true, { });
	Textures_Access.Scrap = Preload_Texture("Tiles/Scrap");
	Textures_Access.Return= Load_Button(Fonts_Access.Subtext_Font,
		"Back", Rectangles_Access.Return);
	Textures_Access.New_Game = Load_Button(Fonts_Access.Text_Font,
		"Play", Rectangles_Access.New_Game);
	Textures_Access.Settings = Load_Button(Fonts_Access.Text_Font,
		"Settings", Rectangles_Access.Settings);
	Textures_Access.Update_Logs = Load_Button(Fonts_Access.Text_Font,
		"Changelog", Rectangles_Access.Update_Logs);
	Textures_Access.Credits = Load_Button(Fonts_Access.Text_Font,
		"Credits", Rectangles_Access.Credits);
	Textures_Access.Quit_Game = Load_Button(Fonts_Access.Text_Font,
		"Quit", Rectangles_Access.Quit_Game);
	Textures_Access.Apply = Load_Button(Fonts_Access.Subtext_Font,
		"Apply", Rectangles_Access.Apply);
	Textures_Access.Cancel = Load_Button(Fonts_Access.Subtext_Font,
		"Cancel", Rectangles_Access.Cancel);
	Textures_Access.Next_Day = Load_Button(Fonts_Access.Subtext_Font,
		"Proceed", Rectangles_Access.Next_Day);
	Carrying_Surface = IMG_Load("Assets/Core/Images/Other/Submarine.png");
	Textures_Access.Submarine.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 2));
	Textures_Access.Submarine.Length = 2;
	for (int Counter = 0; Counter < 2; Counter++) {
		SDL_Surface* Dividing_Surface = SDL_CreateSurface(Carrying_Surface->w / 2,
			Carrying_Surface->h, Carrying_Surface->format);
		SDL_Rect Dividing_Rectangle = { (Carrying_Surface->w / 2) * Counter, 0,
			Carrying_Surface->w / 2, Carrying_Surface->h };
		SDL_BlitSurface(Carrying_Surface, &Dividing_Rectangle, Dividing_Surface, NULL);
		Textures_Access.Submarine.Data[Counter] = SDL_GenerateTextureFromSurface(
			Core_Access.Application_Renderer, Dividing_Surface);
		SDL_DestroySurface(Dividing_Surface);
	}
	SDL_DestroySurface(Carrying_Surface);
	SDL_GetTextureSize(Textures_Access.Submarine.Data[0], &Rectangles_Access
		.Submarine.w, &Rectangles_Access.Submarine.h);
	Rectangles_Access.Submarine.w = static_cast<int>(((double)Rectangles_Access
		.Submarine.w / 3) * Settings_Access.Screen_Size);
	Rectangles_Access.Submarine.h = static_cast<int>(((double)Rectangles_Access
		.Submarine.h / 6) * Settings_Access.Screen_Size);
	Metadata_Access.Machine_Sprites = {
		Textures_Access.R_Pipe.Data[1], Textures_Access.R_Pump.Data[0], Textures_Access.Incinerator
		.Data[0].Data[0], Textures_Access.P_Generator, Textures_Access.Tile_Texture, Textures_Access
		.S_Dock.Data[0], Textures_Access.F_Plant.Data[0], Textures_Access.B_Generator.Data[0].Data[0],
		Textures_Access.MS_Pool.Data[0], Textures_Access.Distillery.Data[0].Data[0], Textures_Access
		.G_Bed.Data[0].Data[0], Textures_Access.C_Platform.Data[0], Textures_Access.B_Scrubber.Data[0], Textures_Access
		.MS_Controller, Textures_Access.MS_Output, Textures_Access.MS_Input, Textures_Access.E_Plant
		.Data[0], Textures_Access.F_Mixer.Data[0].Data[0], Textures_Access.T_Tower.Data[0],
		Textures_Access.Flowerpot, Textures_Access.A_Shelf.Data[0], Textures_Access.C_Node, Textures_Access
		.G_Well.Data[0], Textures_Access.L_Pipe.Data[1], Textures_Access.H_Exchanger.Data[0], Textures_Access
		.P_Wood, Textures_Access.B_Tile, Textures_Access.S_Carpet, Textures_Access.M_Generator, Textures_Access
		.F_Generator, Textures_Access.R_Intersection.Data[0], Textures_Access.L_Intersection.Data[0],
		Textures_Access.H_Strip, Textures_Access.SC_Input.Data[0], Textures_Access.SCH_Sink.Data[0],
		Textures_Access.SC_Transferor.Data[0], Textures_Access.SC_Output.Data[0], Textures_Access.ST_Input.Data[0],
		Textures_Access.STIT_Block.Data[0].Data[0], Textures_Access.ST_Output.Data[0].Data[0]
	};
	Metadata_Access.Machine_Rectangles = {
		Rectangles_Access.Tile_1x1, Rectangles_Access.Tile_1x1, Rectangles_Access.Tile_1x1,
		Rectangles_Access.Tile_1x1, Rectangles_Access.Tile_1x1, Rectangles_Access.Tile_6x4,
		Rectangles_Access.Tile_2x3, Rectangles_Access.Tile_3x3,	Rectangles_Access.Tile_1x1,
		Rectangles_Access.Tile_2x2, Rectangles_Access.Tile_2x3,	Rectangles_Access.Tile_8x6,
		Rectangles_Access.Tile_2x2, Rectangles_Access.Tile_1x1,	Rectangles_Access.Tile_1x1,
		Rectangles_Access.Tile_1x1, Rectangles_Access.Tile_3x2,	Rectangles_Access.Tile_3x3,
		Rectangles_Access.Tile_3x3, Rectangles_Access.Tile_1x1,	Rectangles_Access.Tile_2x1,
		Rectangles_Access.Tile_1x1, Rectangles_Access.Tile_2x3,	Rectangles_Access.Tile_1x1,
		Rectangles_Access.Tile_4x3, Rectangles_Access.Tile_1x1,	Rectangles_Access.Tile_1x1,
		Rectangles_Access.Tile_1x1, Rectangles_Access.Tile_1x1,	Rectangles_Access.Tile_1x1,
		Rectangles_Access.Tile_3x3, Rectangles_Access.Tile_3x3,	Rectangles_Access.Tile_1x1,
		Rectangles_Access.Tile_2x1, Rectangles_Access.Tile_2x1,	Rectangles_Access.Tile_2x3,
		Rectangles_Access.Tile_2x1, Rectangles_Access.Tile_2x3, Rectangles_Access.Tile_2x3,
		Rectangles_Access.Tile_2x2
	};
	UI_Access.Log_Heights.clear();
	UI_Access.Log_Heights.resize(3);
	Cache_Access.Log_Rectangles.clear();
	Cache_Access.Log_Rectangles.resize(3);
	Cache_Access.Log_Cache.Data = static_cast<Texture_Array*>(
		malloc(sizeof(Texture_Array) * 3));
	Cache_Access.Log_Cache.Length = 3;
	for (int Counter1 = 0; Counter1 < Metadata_Access.Logs.size(); Counter1++) {
		int Height = Render_Rich_Text(Fonts_Access.Halftext_Font, Metadata_Access.Logs[Counter1],
			0, 0, Temporary_Access.Log_Inversions[Counter1], true) - (210 * Settings_Access.Screen_Size);
		UI_Access.Log_Heights[Counter1] = Height;
		Cache_Access.Log_Rectangles[Counter1].clear();
		int Cap = std::ceil((double)Height / (682 / 2 * Settings_Access.Screen_Size));
		Cache_Access.Log_Cache.Data[Counter1].Data = static_cast<SDL_Texture**>(
			malloc(sizeof(SDL_Texture*) * Cap));
		Cache_Access.Log_Cache.Data[Counter1].Length = Cap;
		for (int Counter2 = 0; Counter2 < Cap; Counter2++) {
			Cache_Access.Log_Cache.Data[Counter1].Data[Counter2] =
				SDL_GenerateTexture(Core_Access.Application_Renderer,
				SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 640 *
				Settings_Access.Screen_Size, 1000 * Settings_Access.Screen_Size);
			SDL_FRect New_Rectangle = { 0, Counter2 * Settings_Access.Screen_Size * 1000.0f,
				640.0f * Settings_Access.Screen_Size, 1000.0f * Settings_Access.Screen_Size };
			SDL_SetTextureBlendMode(Cache_Access.Log_Cache.Data[
				Counter1].Data[Counter2], SDL_BLENDMODE_BLEND);
			SDL_SetRenderTarget(Core_Access.Application_Renderer, Cache_Access
				.Log_Cache.Data[Counter1].Data[Counter2]);
			Render_Rich_Text(Fonts_Access.Halftext_Font, Metadata_Access.Logs[Counter1],
				52, 52 - (New_Rectangle.y / Settings_Access.Screen_Size),
				Temporary_Access.Log_Inversions[Counter1], false);
			SDL_SetRenderTarget(Core_Access.Application_Renderer, NULL);
			Cache_Access.Log_Rectangles[Counter1].push_back(New_Rectangle);			
		}
	}
	Cache_Access.Wire_Cache.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 4));
	Cache_Access.Wire_Cache.Length = 4;
	for (int Counter = 0; Counter < 4; Counter++) {
		Cache_Access.Wire_Cache.Data[Counter] = SDL_GenerateTexture(
			Core_Access.Application_Renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, 20 * LDE_GRIDSIZE * Settings_Access.Screen_Size, 20 *
			LDE_GRIDSIZE * Settings_Access.Screen_Size);
		SDL_SetTextureBlendMode(Cache_Access.Wire_Cache.Data[Counter], SDL_BLENDMODE_BLEND);
	}
	Cache_Access.Wire_Box = { 0, 0, 20.0f * LDE_GRIDSIZE * Settings_Access.Screen_Size,
		20.0f *	LDE_GRIDSIZE * Settings_Access.Screen_Size };
	std::string Labels[2] = { "Apply", "Cancel" };
	Rectangles_Access.Confirmation.Length = 2;
	Rectangles_Access.Confirmation.Data = static_cast<
		Rect_Array*>(malloc(sizeof(Rect_Array) * 2));
	Textures_Access.Confirmation.Data = static_cast<
		Texture_Array*>(malloc(sizeof(Texture_Array) * 2));
	Textures_Access.Confirmation.Length = 2;
	for (int Counter1 = 0; Counter1 < 2; Counter1++) {
		Rectangles_Access.Confirmation.Data[Counter1].Length = 2;
		Rectangles_Access.Confirmation.Data[Counter1].Data =
			static_cast<SDL_FRect*>(calloc(2, sizeof(SDL_FRect)));
		Textures_Access.Confirmation.Data[Counter1] = Load_Button(Fonts_Access.Halftext_Font,
			Labels[Counter1], Rectangles_Access.Confirmation.Data[Counter1]);
		for (int Counter2 = 0; Counter2 < 2; Counter2++) {
			Rectangles_Access.Confirmation.Data[Counter1].Data[Counter2].x =
				(((Counter1 * 320) + 160) *	Settings_Access.Screen_Size) -
				(Rectangles_Access.Confirmation.Data[Counter1].Data[Counter2].w / 2);
			Rectangles_Access.Confirmation.Data[Counter1].Data[Counter2].y = 260 * Settings_Access.Screen_Size;
		}
	}
	Textures_Access.Pyramid.Data = static_cast<SDL_Texture**>(
		malloc(sizeof(SDL_Texture*) * 4));
	Textures_Access.Pyramid.Length = 4;
	float Full_Width = ((LDE_GRIDSIZE * 40) + (LDE_BUFFERSIZE * 2)) *
		Settings_Access.Screen_Size;
	int Candidate_Length = Full_Width * 0.25;
	if (evn_i(Candidate_Length)) {
		Candidate_Length--;
	}
	const int Resolution = 2001;
	SDL_Surface* Mesh_Surface = SDL_CreateSurface(Resolution, Resolution, SDL_PIXELFORMAT_RGBA8888);
	const SDL_PixelFormatDetails* Pixel_Format = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
	SDL_LockSurface(Mesh_Surface);
	uint32_t Empty = SDL_MapRGBA(Pixel_Format, NULL, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
	uint32_t Light = SDL_MapRGBA(Pixel_Format, NULL, Colors_Access.Mid_Grey.r,
		Colors_Access.Mid_Grey.g, Colors_Access.Mid_Grey.b, SDL_ALPHA_OPAQUE);
	uint32_t* Pixels = static_cast<uint32_t*>(Mesh_Surface->pixels);
	for (int Counter = 0; Counter < sqr_i(Resolution); Counter++) {
		if (evn_i(Counter) && static_cast<int>(Counter & 3) == 0) {
				Pixels[Counter] = Light;
		} else {
			Pixels[Counter] = Empty;
		}
	}
	SDL_UnlockSurface(Mesh_Surface);
	Textures_Access.Mesh = SDL_GenerateTextureFromSurface(
		Core_Access.Application_Renderer, Mesh_Surface);
	SDL_SetTextureScaleMode(Textures_Access.Mesh, SDL_SCALEMODE_NEAREST);
	SDL_DestroySurface(Mesh_Surface);
	for (int Counter = 0; Counter < 4; Counter++) {
		Textures_Access.Pyramid.Data[Counter] = SDL_GenerateTexture(
			Core_Access.Application_Renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET, Full_Width * 0.25, Full_Width * 0.25);
		SDL_SetTextureBlendMode(Textures_Access.Pyramid.Data[Counter], SDL_BLENDMODE_BLEND);
		SDL_SetTextureScaleMode(Textures_Access.Pyramid.Data[Counter], SDL_SCALEMODE_NEAREST);
	}
	SDL_Color Pyramid_Color = Colors_Access.Reinforced_Grey;
	Pyramid_Color.a = SDL_ALPHA_OPAQUE;
	Set_Renderer_Color(Pyramid_Color);
	float Subwidth = ((LDE_GRIDSIZE + 2) * Settings_Access.Screen_Size * 40.0f) * 0.5f;
	for (int X = 0; X < 2; X++) {
		for (int Y = 0; Y < 2; Y++) {
			SDL_SetRenderTarget(Core_Access.Application_Renderer,
				Textures_Access.Pyramid.Data[(X * 2) + Y]);
			SDL_FRect Subrectangle = {
				((LDE_BUFFERSIZE - 280.0f) * Settings_Access.Screen_Size) - (X * Subwidth),
				((LDE_BUFFERSIZE - 280.0f) * Settings_Access.Screen_Size) - (Y * Subwidth),
				500.0f * Settings_Access.Screen_Size,
				500.0f * Settings_Access.Screen_Size
			};
			SDL_RenderFillRect(Core_Access.Application_Renderer, &Subrectangle);
			Subrectangle.x -= Settings_Access.Screen_Size * 5.0f;
			Subrectangle.y -= Settings_Access.Screen_Size * 5.0f;
			Subrectangle.w += Settings_Access.Screen_Size * 10.0f;
			Subrectangle.h += Settings_Access.Screen_Size * 10.0f;
			for (int Counter = 0; Counter < 5 * Settings_Access.Screen_Size; Counter++) {
				Subrectangle.x--;
				Subrectangle.y--;
				Subrectangle.w += 2;
				Subrectangle.h += 2;
				SDL_SetRenderDrawBlendMode(Core_Access.Application_Renderer, SDL_BLENDMODE_BLEND);
				SDL_RenderRect(Core_Access.Application_Renderer, &Subrectangle);
			}
		}
	}
	SDL_SetRenderTarget(Core_Access.Application_Renderer, NULL);
	Clear_Renderer();
}

void Cleanup_Assets() {
	SDL_DestroyTexture(Core_Access.Game_Texture);
	Audio_Access.Free(&Audio_Access.Primary_Ambience);
	Audio_Access.Free(&Audio_Access.Filtration_Loop);
	Audio_Access.Free(&Audio_Access.Ram_Loop);
	Audio_Access.Free(&Audio_Access.Click);
	TTF_CloseFont(Fonts_Access.Logo_Font);
	TTF_CloseFont(Fonts_Access.Large_Font);
	TTF_CloseFont(Fonts_Access.Text_Font);
	TTF_CloseFont(Fonts_Access.Halftext_Font);
	TTF_CloseFont(Fonts_Access.Subtext_Font);
	TTF_CloseFont(Fonts_Access.Microtext_Font);
	TTF_CloseFont(Fonts_Access.Terminal_Font);
	Clear_Texture_Array(Textures_Access.Tool);
	Clear_Texture_Array(Textures_Access.Help_Content);
	Clear_Texture_Array(Textures_Access.Door);
	SDL_DestroyTexture(Textures_Access.Recipe_Content);
	Clear_Texture3_Array(Textures_Access.Item_Labels);
	Clear_Rect3_Array(Rectangles_Access.Item_Labels);
	Clear_Texture3_Array(Textures_Access.Subcategories);
	Clear_Rect3_Array(Rectangles_Access.Subcategories);
	Clear_Texture3_Array(Textures_Access.Subcontents);
	Clear_Rect3_Array(Rectangles_Access.Subcontents);
	Clear_Texture2_Array(Textures_Access.Tutorials);
	Clear_Rect2_Array(Rectangles_Access.Tutorials);
	Clear_Rect_Array(Rectangles_Access.Tutorial_Hitbox);
	Clear_Texture2_Array(Textures_Access.Cheats);
	Clear_Rect2_Array(Rectangles_Access.Cheats);
	Clear_Texture2_Array(Textures_Access.Cap_Button);
	Clear_Rect_Array(Rectangles_Access.Cap_Hitbox);
	Clear_Texture2_Array(Textures_Access.New);
	Clear_Rect2_Array(Rectangles_Access.New);
	Clear_Texture2_Array(Textures_Access.Load);
	Clear_Rect2_Array(Rectangles_Access.Load);
	Clear_Texture2_Array(Textures_Access.Clear);
	Clear_Rect2_Array(Rectangles_Access.Clear);
	Clear_Texture2_Array(Textures_Access.Categories);
	Clear_Rect2_Array(Rectangles_Access.Categories);
	Clear_Texture_Array(Textures_Access.Error_Exit);
	Clear_Rect_Array(Rectangles_Access.Error_Exit);
	Clear_Texture2_Array(Textures_Access.MSP_Buttons);
	Clear_Rect2_Array(Rectangles_Access.MSP_Buttons);
	Clear_Texture2_Array(Textures_Access.SD_Buttons);
	Clear_Rect2_Array(Rectangles_Access.SD_Buttons);
	Clear_Texture2_Array(Textures_Access.HX_Buttons);
	Clear_Rect2_Array(Rectangles_Access.HX_Buttons);
	Clear_Texture3_Array(Textures_Access.TT_Buttons);
	Clear_Rect3_Array(Rectangles_Access.TT_Buttons);
	Clear_Texture2_Array(Textures_Access.MT_Buttons);
	Clear_Rect2_Array(Rectangles_Access.MT_Buttons);
	Clear_Texture2_Array(Textures_Access.Anti_Aliasing);
	Clear_Rect2_Array(Rectangles_Access.Anti_Aliasing);
	Clear_Texture2_Array(Textures_Access.V_Sync);
	Clear_Rect2_Array(Rectangles_Access.V_Sync);
	Clear_Texture2_Array(Textures_Access.Sort);
	Clear_Rect2_Array(Rectangles_Access.Sort);
	Clear_Texture2_Array(Textures_Access.TBW_Texture);
	Clear_Rect2_Array(Rectangles_Access.TBW_Rectangle);
	Clear_Texture_Array(Textures_Access.Clear_Tutorial);
	Clear_Rect_Array(Rectangles_Access.Clear_Tutorial);
	Clear_Texture_Array(Textures_Access.Settings_Label);
	Clear_Rect_Array(Rectangles_Access.Settings_Label);
	Clear_Texture_Array(Textures_Access.Save_Settings);
	Clear_Rect_Array(Rectangles_Access.Save_Settings);
	Clear_Texture_Array(Textures_Access.Cap);
	Clear_Texture_Array(Textures_Access.R_Pipe);
	Clear_Texture_Array(Textures_Access.L_Pipe);
	Clear_Texture_Array(Textures_Access.MS_Pool);
	Clear_Texture_Array(Textures_Access.Arrow);
	Clear_Texture_Array(Textures_Access.S_Dock);
	Clear_Texture_Array(Textures_Access.Tunnel);
	Clear_Rect_Array(Rectangles_Access.Tunnel);
	Clear_Texture_Array(Textures_Access.Return);
	Clear_Rect_Array(Rectangles_Access.Return);
	Clear_Texture_Array(Textures_Access.New_Game);
	Clear_Rect_Array(Rectangles_Access.New_Game);
	Clear_Texture_Array(Textures_Access.Settings);
	Clear_Rect_Array(Rectangles_Access.Settings);
	Clear_Texture_Array(Textures_Access.Update_Logs);
	Clear_Rect_Array(Rectangles_Access.Update_Logs);
	Clear_Texture_Array(Textures_Access.Credits);
	Clear_Rect_Array(Rectangles_Access.Credits);
	Clear_Texture_Array(Textures_Access.Quit_Game);
	Clear_Rect_Array(Rectangles_Access.Quit_Game);
	Clear_Texture_Array(Textures_Access.Apply);
	Clear_Rect_Array(Rectangles_Access.Apply);
	Clear_Texture_Array(Textures_Access.Cancel);
	Clear_Rect_Array(Rectangles_Access.Cancel);
	Clear_Texture_Array(Textures_Access.Next_Day);
	Clear_Rect_Array(Rectangles_Access.Next_Day);
	Clear_Texture_Array(Textures_Access.Quirk);
	Clear_Texture_Array(Textures_Access.Quirk_Label);
	SDL_DestroyTexture(Textures_Access.Logo);
	SDL_DestroyTexture(Textures_Access.Crosshair);
	SDL_DestroyTexture(Textures_Access.Cursor_Core);
	SDL_DestroyTexture(Textures_Access.Sapling);
	SDL_DestroyTexture(Textures_Access.Node);
	SDL_DestroyTexture(Textures_Access.Log_Background);
	SDL_DestroyTexture(Textures_Access.Saveloader);
	SDL_DestroyTexture(Textures_Access.Help_Sidebutton);
	SDL_DestroyTexture(Textures_Access.Save_Sidebutton);
	SDL_DestroyTexture(Textures_Access.Recipe_Sidebutton);
	SDL_DestroyTexture(Textures_Access.Exit_Sidebutton);
	SDL_DestroyTexture(Textures_Access.RFlash);
	SDL_DestroyTexture(Textures_Access.Floor_Texture);
	SDL_DestroyTexture(Textures_Access.Frame_Texture);
	SDL_DestroyTexture(Textures_Access.Tile_Texture);
	Clear_Texture_Array(Textures_Access.R_Pump);
	Clear_Texture2_Array(Textures_Access.Incinerator);
	SDL_DestroyTexture(Textures_Access.P_Generator);
	Clear_Texture_Array(Textures_Access.F_Plant);
	Clear_Texture2_Array(Textures_Access.B_Generator);
	Clear_Texture2_Array(Textures_Access.Distillery);
	Clear_Texture2_Array(Textures_Access.G_Bed);
	Clear_Texture_Array(Textures_Access.C_Platform);
	Clear_Texture_Array(Textures_Access.B_Scrubber);
	SDL_DestroyTexture(Textures_Access.MS_Controller);
	SDL_DestroyTexture(Textures_Access.MS_Output);
	SDL_DestroyTexture(Textures_Access.MS_Input);
	Clear_Texture_Array(Textures_Access.E_Plant);
	Clear_Texture2_Array(Textures_Access.F_Mixer);
	Clear_Texture_Array(Textures_Access.T_Tower);
	SDL_DestroyTexture(Textures_Access.Flowerpot);
	Clear_Texture_Array(Textures_Access.A_Shelf);
	Clear_Texture_Array(Textures_Access.Submarine);
	SDL_DestroyTexture(Textures_Access.C_Node);
	Clear_Texture_Array(Textures_Access.G_Well);
	Clear_Texture_Array(Textures_Access.H_Exchanger);
	SDL_DestroyTexture(Textures_Access.P_Wood);
	SDL_DestroyTexture(Textures_Access.B_Tile);
	SDL_DestroyTexture(Textures_Access.S_Carpet);
	SDL_DestroyTexture(Textures_Access.H_Strip);
	SDL_DestroyTexture(Textures_Access.M_Generator);
	SDL_DestroyTexture(Textures_Access.F_Generator);
	Clear_Texture_Array(Textures_Access.R_Intersection);
	Clear_Texture_Array(Textures_Access.L_Intersection);
	Clear_Texture_Array(Textures_Access.SC_Input);
	Clear_Texture_Array(Textures_Access.SCH_Sink);
	Clear_Texture_Array(Textures_Access.SC_Transferor);
	Clear_Texture_Array(Textures_Access.SC_Output);
	Clear_Texture_Array(Textures_Access.ST_Input);
	Clear_Texture2_Array(Textures_Access.STIT_Block);
	Clear_Texture2_Array(Textures_Access.ST_Output);
	SDL_DestroyTexture(Textures_Access.Scrap);
	Clear_Texture2_Array(Textures_Access.Confirmation);
	Clear_Rect2_Array(Rectangles_Access.Confirmation);
	Clear_Texture_Array(Textures_Access.Pyramid);
	SDL_DestroyTexture(Textures_Access.Mesh);
	Clear_Texture_Array(Textures_Access.Fire);
	Clear_Texture_Array(Textures_Access.None);
	Clear_Texture_Array(Cache_Access.Wire_Cache);
	SDL_DestroyTexture(Cache_Access.Blueprint_Cache);
	Clear_Texture2_Array(Cache_Access.Log_Cache);
}

void Render_Dynamic_Text(TTF_Font* Selected_Font, std::string Text, SDL_Color Color, int X, int Y) {
	SDL_Surface* Text_Surface = TTF_RenderText_Blended(Selected_Font, Text.c_str(), Text.size(), Color);
	SDL_Texture* Text_Texture = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Text_Surface);
	int Multiplier = Settings_Access.Screen_Size;
	if (X == LDE_INVALID) {
		X = (320 * Settings_Access.Screen_Size) - (Text_Surface->w / 2);
		Multiplier = 1;
	}
	SDL_FRect Text_Rectangle = { static_cast<float>(X * Multiplier),
		static_cast<float>(Y * Settings_Access.Screen_Size),
		static_cast<float>(Text_Surface->w), static_cast<float>(Text_Surface->h) };
	SDL_RenderTexture(Core_Access.Application_Renderer, Text_Texture, NULL, &Text_Rectangle);
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
			Counter1)].size(), Colors_Access.Abyss_Black);
		SDL_FRect Fragment_Rectangle = { static_cast<float>(X * Settings_Access.Screen_Size),
			static_cast<float>(Y * Settings_Access.Screen_Size) + Offset, static_cast<float>(
			Fragment_Surface->w), static_cast<float>(Fragment_Surface->h) };
		if (!Disabled) {
			SDL_Texture* Fragment_Texture = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Fragment_Surface);
			SDL_RenderTexture(Core_Access.Application_Renderer, Fragment_Texture, NULL, &Fragment_Rectangle);
			SDL_DestroyTexture(Fragment_Texture);
		}
		SDL_DestroySurface(Fragment_Surface);
		Offset = Offset + Fragment_Rectangle.h;
	}
	return Offset;
}

void Render_Outline(SDL_FRect Rectangle, SDL_Color Color, int Multiplier) {
	Set_Renderer_Color(Color);
	for (int Counter = 0; Counter < LDE_BORDERWIDTH * Settings_Access.Screen_Size * Multiplier; Counter++) {
		SDL_RenderRect(Core_Access.Application_Renderer, &Rectangle);
		Rectangle.x++;
		Rectangle.y++;
		Rectangle.w -= 2;
		Rectangle.h -= 2;
	}
	Clear_Renderer();
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

int Visual_To_ID(const int Identifier) {
	if (Identifier > 0 && Identifier < 17) {
		return Reinforced_Pipe;
	} else if (Identifier > 16 && Identifier < 24) {
		return Identifier - 16;
	} else if (Identifier > 23 && Identifier < 41) {
		return Spawning_Pool;
	} else if (Identifier > 40 && Identifier < 52) {
		return Identifier - 32;
	} else if (Identifier > 51 && Identifier < 56) {
		return Ammunition_Shelf;
	} else if (Identifier > 55 && Identifier < 59) {
		return Command_Platform;
	} else if (Identifier > 59 && Identifier < 63) {
		return Signal_Tower;
	} else if (Identifier > 62 && Identifier < 64) {
		return Identifier - 42;
	} else if (Identifier > 63 && Identifier < 67) {
		return Basic_Scrubber;
	} else if (Identifier > 66 && Identifier < 71) {
		return Geo_Well;
	} else if (Identifier > 70 && Identifier < 87) {
		return Large_Pipe;
	} else if (Identifier > 86 && Identifier < 91) {
		return Heat_Exchanger;
	} else if (Identifier > 90 && Identifier < 96) {
		return Identifier - 66;
	} else if (Identifier > 95 && Identifier < 99) {
		return Electrolytic_Cell;
	} else if (Identifier > 98 && Identifier < 102) {
		return Fluid_Mixer;
	} else if (Identifier > 101 && Identifier < 105) {
		return Bio_Generator;
	} else if (Identifier > 104 && Identifier < 109) {
		return R_Intersection;
	} else if (Identifier > 108 && Identifier < 113) {
		return L_Intersection;
	} else if (Identifier == 113) {
		return Hazard_Strip;
	} else if (Identifier > 113 && Identifier < 117) {
		return Incinerator;
	} else if (Identifier > 116 && Identifier < 120) {
		return Distillery;
	} else if (Identifier > 119 && Identifier < 124) {
		return Turbine_Input;
	} else if (Identifier > 123 && Identifier < 128) {
		return Turbine_Impulse;
	} else if (Identifier > 127 && Identifier < 132) {
		return Turbine_Output;
	} else if (Identifier > 131 && Identifier < 135) {
		return Algae_Bed;
	}
	return LDE_INVALID;
}

int Visual_To_Rotation(const int Identifier) {
	if (Identifier > 52 && Identifier < 56) {
		return Identifier - 52;
	} else if (Identifier > 55 && Identifier < 59) {
		return Identifier - 55;
	} else if (Identifier > 59 && Identifier < 63) {
		return Identifier - 59;
	} else if (Identifier > 63 && Identifier < 67) {
		return Identifier - 63;
	} else if (Identifier > 67 && Identifier < 71) {
		return Identifier - 67;
	} else if (Identifier > 87 && Identifier < 91) {
		return Identifier - 87;
	} else if (Identifier > 95 && Identifier < 99) {
		return Identifier - 95;
	} else if (Identifier > 98 && Identifier < 102) {
		return Identifier - 98;
	} else if (Identifier > 101 && Identifier < 105) {
		return Identifier - 101;
	} else if (Identifier > 105 && Identifier < 109) {
		return Identifier - 105;
	} else if (Identifier > 109 && Identifier < 113) {
		return Identifier - 109;
	} else if (Identifier > 113 && Identifier < 117) {
		return Identifier - 113;
	} else if (Identifier > 116 && Identifier < 120) {
		return Identifier - 116;
	} else if (Identifier > 120 && Identifier < 124) {
		return Identifier - 120;
	} else if (Identifier > 124 && Identifier < 128) {
		return Identifier - 124;
	} else if (Identifier > 128 && Identifier < 132) {
		return Identifier - 128;
	} else if (Identifier > 131 && Identifier < 135) {
		return Identifier - 131;
	}
	return 0;
}

void ID_To_Size(const int ID, const int Rotation, int &X, int &Y) {
	X = 1;
	Y = 1;
	switch (ID) {
	case Ammunition_Shelf:
		if (evn_i(Rotation)) {
			X = 2;
		} else {
			Y = 2;
		}
		break;
	case Distillery:
	case Basic_Scrubber:
	case Turbine_Output:
		X = 2;
		Y = 2;
		break;
	case Filtration_Plant:
	case Algae_Bed:
		if (evn_i(Rotation)) {
			X = 2;
			Y = 3;
		} else {
			X = 3;
			Y = 2;
		}
		break;
	case Electrolytic_Cell:
		if (evn_i(Rotation)) {
			X = 3;
			Y = 2;
		} else {
			X = 2;
			Y = 3;
		}
		break;
	case Bio_Generator:
	case Fluid_Mixer:
	case Signal_Tower:
	case R_Intersection:
	case L_Intersection:
		X = 3;
		Y = 3;
		break;
	case Submarine_Dock:
		X = 6;
		Y = 4;
		break;
	case Command_Platform:
		if (evn_i(Rotation)) {
			X = 8;
			Y = 6;
		} else {
			X = 6;
			Y = 8;
		}
		break;
	case Geo_Well:
	case Turbine_Input:
	case Turbine_Impulse:
		if (evn_i(Rotation)) {
			X = 2;
			Y = 3;
		} else {
			X = 3;
			Y = 2;
		}
		break;
	case Heat_Exchanger:
		if (evn_i(Rotation)) {
			X = 4;
			Y = 3;
		} else {
			X = 3;
			Y = 4;
		}
		break;
	default:
		break;
	}
}

void Render_Box(int X, int Y, int W, int H, SDL_Color Inner_Color, SDL_Color Outer_Color) {
	SDL_FRect External_Rectangle = { static_cast<float>(X - 4) * Settings_Access.Screen_Size,
		static_cast<float>(Y - 4) * Settings_Access.Screen_Size, static_cast<float>(W + 8) *
		Settings_Access.Screen_Size, static_cast<float>(H + 8) * Settings_Access.Screen_Size };
	Set_Renderer_Color(Outer_Color);
	SDL_RenderFillRect(Core_Access.Application_Renderer, &External_Rectangle);
	SDL_FRect Internal_Rectangle = { static_cast<float>(X * Settings_Access.Screen_Size),
		static_cast<float>(Y * Settings_Access.Screen_Size), static_cast<float>(W *
		Settings_Access.Screen_Size), static_cast<float>(H * Settings_Access.Screen_Size) };
	Set_Renderer_Color(Inner_Color);
	SDL_RenderFillRect(Core_Access.Application_Renderer, &Internal_Rectangle);
	Clear_Renderer();
}