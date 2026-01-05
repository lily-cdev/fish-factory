#include <prepping.h>

bool Detect_Mouse_Collision(const SDL_FRect Target) {
	return (Core.Mouse.X >= Target.x && Core.Mouse.X <= Target.x + Target.w &&
		Core.Mouse.Y >= Target.y && Core.Mouse.Y <= Target.y + Target.h);
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

void Render_Button(const Texture_Array Button, const Rect_Array Hitbox,
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

void Push_Docks(Point Input) {
	if (Temporary.Docks.Length >= Temporary.Docks.Full_Size) {
		Point* Buffer = malloc(sizeof(Point) * Temporary.Docks.Length);
		memcpy(Buffer, Temporary.Docks.Data, sizeof(Point) * Temporary.Docks.Length);
		free_c(Temporary.Docks.Data);
		Temporary.Docks.Full_Size += 16;
		Temporary.Docks.Data = malloc(sizeof(Point) * Temporary.Docks.Full_Size);
		memcpy(Temporary.Docks.Data, Buffer, sizeof(Point) * Temporary.Docks.Length);
		free_c(Buffer);
	}
	Temporary.Docks.Data[Temporary.Docks.Length] = Input;
	Temporary.Docks.Length++;
}

void Pull_Docks(int Position) {
	if (Temporary.Docks.Length > 0) {
		for (int Counter = 0; Counter < Temporary.Docks.Length - Position - 1; Counter++) {
			Temporary.Docks.Data[Position + Counter] = Temporary.Docks.Data[Position + Counter + 1];
		}
		Temporary.Docks.Length--;
	}
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
				Data.Settings_Grid[X + Counter1][Y + Counter2][1] = X;
				Data.Settings_Grid[X + Counter1][Y + Counter2][2] = Y;
			}
		}
	}
}

int Render_Rich_Text(TTF_Font* Selected_Font, char* Raw_Text, int X, int Y, bool Inverted, bool Disabled) {
	int Offset = 0;
	int Fragment_Count = 1;
	size_t Start = 0;
	size_t End = 0;
	char* Yield;
	while ((Yield = strchr(Raw_Text + Start, '|')) != NULL) {
		End = Yield - Raw_Text;
		Fragment_Count++;
		Start = End + 1;
	}
	char** Fragments = malloc(sizeof(char*) * Fragment_Count);
	for (int Counter = 0; Counter < Fragment_Count; Counter++) {
		Fragments[Counter] = malloc(sizeof(char) * (strlen(Raw_Text) + 1));
	}
	Start = 0;
	End = 0;
	int Index = 0;
	while ((Yield = strchr(Raw_Text + Start, '|')) != NULL) {
		End = Yield - Raw_Text;
		int Length = End - Start;
		memcpy(Fragments[Index], Raw_Text + Start, Length);
		Fragments[Index][Length] = '\0';
		Index++;
		Start = End + 1;
	}
	strcpy(Fragments[Index], Raw_Text + Start);
	int Multiplier = LDE_INVALID;
	int Subtractor = 0;
	if (Inverted) {
		Multiplier = 1;
		Subtractor = Fragment_Count - 1;
	}
	for (size_t Counter = 0; Counter < Fragment_Count; Counter++) {
		char* Position;
		while ((Position = strstr(Fragments[Counter], "[c]")) != NULL) {
			memmove(Position, Position + 3, strlen(Position + 3) + 1);
			strncpy(Position, "    ", 4);
		}
	}
	for (size_t Counter1 = 0; Counter1 < Fragment_Count; Counter1++) {
		int Type = LDE_INVALID;
		char Targets[2][4] = { "[a]", "[b]" };
		for (int Counter2 = 0; Counter2 < 2; Counter2++) {
			bool Matched = true;
			if (strcmp(Fragments[Multiplier * (Subtractor - Counter1)], " ") == 0) {
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
			char* Subfragment = Fragments[Multiplier * (Subtractor - Counter1)];
			memmove(Subfragment, Subfragment + 3, strlen(Subfragment + 3) + 1);
		}
		SDL_Surface* Fragment_Surface = TTF_RenderText_Blended(Selected_Font, Fragments[Multiplier * (Subtractor - Counter1)],
			strlen(Fragments[Multiplier * (Subtractor - Counter1)]), Colors.Abyss_Black);
		SDL_FRect Fragment_Rectangle = {
			(float)(X * Settings.Screen_Size),
			(float)(Y * Settings.Screen_Size) + Offset,
			(float)(Fragment_Surface->w),
			(float)(Fragment_Surface->h)
		};
		if (!Disabled) {
			SDL_Texture* Fragment_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Fragment_Surface);
			SDL_RenderTexture(Core.Renderer, Fragment_Texture, NULL, &Fragment_Rectangle);
			SDL_DestroyTexture(Fragment_Texture);
		}
		SDL_DestroySurface(Fragment_Surface);
		Offset = Offset + Fragment_Rectangle.h;
	}
	for (int Counter = 0; Counter < Fragment_Count; Counter++) {
		free_c(Fragments[Counter]);
	}
	free_c(Fragments);
	return Offset;
}

void Render_Dynamic_Text(TTF_Font* Selected_Font, const char* Text, SDL_Color Color, int X, int Y) {
	SDL_Surface* Text_Surface = TTF_RenderText_Blended(Selected_Font, Text, strlen(Text), Color);
	SDL_Texture* Text_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Text_Surface);
	int Multiplier = Settings.Screen_Size;
	if (X == LDE_INVALID) {
		X = (320 * Settings.Screen_Size) - (Text_Surface->w * 0.5);
		Multiplier = 1;
	}
	SDL_FRect Text_Rectangle = {
		(float)(X * Multiplier),
		(float)(Y * Settings.Screen_Size),
		(float)(Text_Surface->w),
		(float)(Text_Surface->h)
	};
	SDL_RenderTexture(Core.Renderer, Text_Texture, NULL, &Text_Rectangle);
	SDL_DestroySurface(Text_Surface);
	SDL_DestroyTexture(Text_Texture);
}