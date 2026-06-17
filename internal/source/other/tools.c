#include <prepping.h>

bool Detect_Mouse_Collision(const SDL_FRect Target) {
	return (Core.Mouse.X >= Target.x && Core.Mouse.X <= Target.x + Target.w &&
		Core.Mouse.Y >= Target.y && Core.Mouse.Y <= Target.y + Target.h);
}

bool Compare_Colors(const SDL_Color Color1, const SDL_Color Color2) {
	return (Color1.r == Color2.r && Color1.g == Color2.g && Color1.b == Color2.b && Color1.a == Color2.a);
}

void Update_Tilestack(bool X_Lock, int X, bool Y_Lock, int Y) {
	X *= Settings.Scalar;
	Y *= Settings.Scalar;
	if (!X_Lock) {
		Rects.Tile_1x1.x = X;
		Rects.Tile_2x2.x = X;
		Rects.Tile_2x3.x = X;
		Rects.Tile_3x2.x = X;
		Rects.Tile_3x3.x = X;
		Rects.Tile_6x4.x = X;
		Rects.Tile_3x3.x = X;
	}
	if (!Y_Lock) {
		Rects.Tile_1x1.y = Y;
		Rects.Tile_2x2.y = Y;
		Rects.Tile_2x3.y = Y;
		Rects.Tile_3x2.y = Y;
		Rects.Tile_3x3.y = Y;
		Rects.Tile_6x4.y = Y;
		Rects.Tile_3x3.y = Y;
	}
}

bool Render_Button(const Texture_Array* Button, const Rect_Array* Hitbox, UI_Link Link, SDL_Color Underline_Color) {
	if (Detect_Mouse_Collision(Hitbox->Data[0])) {
		Interface.UI_Query = Link;
		SDL_FRect Underline_Rectangle = {
			Hitbox->Data[0].x,
			Hitbox->Data[0].y + Hitbox->Data[0].h + 2.0f,
			Hitbox->Data[0].w,
			Hitbox->Data[0].h * 0.1f
		};
		SDL_SetRenderDrawColor(Core.Renderer, Underline_Color.r, Underline_Color.g, Underline_Color.b, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(Core.Renderer, &Underline_Rectangle);
		Clear_Renderer();
		Render_Texture(Button->Data[1], &Hitbox->Data[1]);
		return true;
	}
	Render_Texture(Button->Data[0], &Hitbox->Data[0]);
	return false;
}

void Push_Docks(Point Input) {
	if (Temporary.Docks.Length >= Temporary.Docks.Full_Size) {
		Point* Buffer = malloc(sizeof(Point) * Temporary.Docks.Length);
		ktn_memcpy(Buffer, Temporary.Docks.Data, sizeof(Point) * Temporary.Docks.Length);
		ktn_free(Temporary.Docks.Data);
		Temporary.Docks.Full_Size += 16;
		Temporary.Docks.Data = malloc(sizeof(Point) * Temporary.Docks.Full_Size);
		ktn_memcpy(Temporary.Docks.Data, Buffer, sizeof(Point) * Temporary.Docks.Length);
		ktn_free(Buffer);
	}
	Temporary.Docks.Data[Temporary.Docks.Length] = Input;
	Temporary.Docks.Length++;
}

void Pull_Docks(int Position) {
	if (Temporary.Docks.Length > 0) {
		for (int C1 = 0; C1 < Temporary.Docks.Length - Position - 1; C1++) {
			Temporary.Docks.Data[Position + C1] = Temporary.Docks.Data[Position + C1 + 1];
		}
		Temporary.Docks.Length--;
	}
}

bool Check_Clearance(Point Pos, const int W, const int H) {
	if (Pos.X + W > ktn_grid_size || Pos.Y + H > ktn_grid_size) {
		return false;
	} 
	for (int C1 = 0; C1 < W; C1++) {
		for (int C2 = 0; C2 < H; C2++) {
			if (Data.Visual_Grid[Pos.X + C1][Pos.Y + C2] != 0) {
				return false;
			}
		}
	}
	return true;
}

void Fill_Clearance(const int Identifier, Point Pos, const int W, const int H) {
	for (int C1 = 0; C1 < W; C1++) {
		for (int C2 = 0; C2 < H; C2++) {
			Data.Visual_Grid[Pos.X + C1][Pos.Y + C2] = Identifier;
			if (C1 > 0 || C2 > 0) {
				Data.Settings_Grid[Pos.X + C1][Pos.Y + C2][1] = Pos.X;
				Data.Settings_Grid[Pos.X + C1][Pos.Y + C2][2] = Pos.Y;
			}
		}
	}
}

void Render_Texture(SDL_Texture* Texture, SDL_FRect* Rect) {
	if (Texture == NULL) {
		char Carrier[512];
		snprintf(Carrier, sizeof(Carrier), "could not render texture; %s", SDL_GetError());
		ktn_jump(I_Render_Failed, Carrier);
	}
	SDL_RenderTexture(Core.Renderer, Texture, NULL, Rect);
}

int Render_Rich_Text(Font_Index Font, char* Raw_Text, Point Pos, bool Inverted, bool Disabled) {
	int Offset = 0;
	int Fragment_Count = 1;
	size_t Start = 0;
	size_t End = 0;
	char* Yield;
	while ((Yield = strchr(Raw_Text + Start, '|'))) {
		End = Yield - Raw_Text;
		Fragment_Count++;
		Start = End + 1;
	}
	char** Fragments = malloc(sizeof(char*) * Fragment_Count);
	int* Lengths = malloc(sizeof(int) * Fragment_Count);
	for (int C1 = 0; C1 < Fragment_Count; C1++) {
		Lengths[C1] = strlen(Raw_Text) + 1;
		Fragments[C1] = malloc(Lengths[C1]);
	}
	Start = 0;
	End = 0;
	int Index = 0;
	while ((Yield = strchr(Raw_Text + Start, '|'))) {
		End = Yield - Raw_Text;
		int Length = End - Start;
		ktn_memcpy(Fragments[Index], Raw_Text + Start, Length);
		Fragments[Index][Length] = '\0';
		Index++;
		Start = End + 1;
	}
	strncpy(Fragments[Index], Raw_Text + Start, Lengths[Index]);
	int Multiplier = ktn_invalid;
	int Subtractor = 0;
	if (Inverted) {
		Multiplier = 1;
		Subtractor = Fragment_Count - 1;
	}
	for (size_t C1 = 0; C1 < Fragment_Count; C1++) {
		for (int C2 = 0; C2 < strlen(Fragments[C1]); C2++) {
			char Candidate[8];
			strncpy(Candidate, Fragments[C1] + C2, 3);
			Candidate[3] = '\0';
			if (strcmp(Candidate, "[c]") == 0) {
				memmove(Fragments[C1] + C2 + 1, Fragments[C1] + C2, strlen(Fragments[C1]) + 1);
				strncpy(Fragments[C1] + C2, "    ", 4);
				C1--;
				break;
			}
		}
	}
	for (size_t C1 = 0; C1 < Fragment_Count; C1++) {
		int Type = ktn_invalid;
		char Targets[2][4] = { "[a]", "[b]" };
		for (int C2 = 0; C2 < 2; C2++) {
			bool Matched = true;
			if (strcmp(Fragments[Multiplier * (Subtractor - C1)], " ") == 0) {
				Matched = false;
			} else {
				for (int C3 = 0; C3 < 3; C3++) {
					if (Fragments[Multiplier * (Subtractor - C1)][C3] != Targets[C2][C3]) {
						Matched = false;
					}
				}
			}
			if (Matched) {
				Type = C2;
				break;
			}
		}
		if ((Type == 0 && Inverted) || (Type == 1 && !Inverted)) {
			continue;
		} else if (Type != ktn_invalid) {
			char* Subfragment = Fragments[Multiplier * (Subtractor - C1)];
			memmove(Subfragment, Subfragment + 3, strlen(Subfragment + 3) + 1);
		}
		SDL_Texture* Fragment_Texture = Render_Text(Font, Fragments[Multiplier * (Subtractor - C1)], Colors.Abyss_Black);
		if (Fragment_Texture) {
			SDL_FRect Fragment_Rectangle = {
				ktn_fscale(Pos.X),
				ktn_fscale(Pos.Y) + Offset,
				(float)Fragment_Texture->w,
				(float)Fragment_Texture->h
			};
			if (!Disabled) {
				Render_Texture(Fragment_Texture, &Fragment_Rectangle);
			}
			Offset += Fragment_Rectangle.h;
		}
		ktn_free_texture(Fragment_Texture);
	}
	for (int C1 = 0; C1 < Fragment_Count; C1++) {
		ktn_free(Fragments[C1]);
	}
	ktn_free(Fragments);
	ktn_free(Lengths);
	return Offset;
}

void Reseed_State() {
	struct timespec Spec;
	timespec_get(&Spec, TIME_UTC);
	Core.State = (uint32_t)Spec.tv_nsec;
}

SDL_FRect Inline_Rect(SDL_FRect Input, const int Border) {
	return (SDL_FRect){
		Input.x += (Settings.Scalar * Border),
		Input.y += (Settings.Scalar * Border),
		Input.w -= (Settings.Scalar * Border * 2.0f),
		Input.h -= (Settings.Scalar * Border * 2.0f)
	};
}

bool Is_Bound(Point Input) {
	return (Input.X >= 0 && Input.Y >= 0 && Input.X < ktn_grid_size && Input.Y < ktn_grid_size);
}

SDL_Texture* Render_Text(Font_Index Font, const char* Text, SDL_Color Color) {
	SDL_Surface* Carrier;
	if (Settings.Anti_Aliasing) {
		Carrier = TTF_RenderText_Blended(Fonts.Faces[Font], Text, strlen(Text), Color);
	} else {
		Carrier = TTF_RenderText_Solid(Fonts.Faces[Font], Text, strlen(Text), Color);
	}
	SDL_Texture* Yield = Surface_To_Texture(Carrier);
	return Yield;
}

SDL_Texture* New_Texture(int Width, int Height) {
	SDL_Texture* Texture = SDL_CreateTexture(Core.Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width, Height);
	if (Texture == NULL) {
		ktn_jump(I_No_Texture, "could not create texture");
	}
	SDL_SetTextureScaleMode(Texture, Scaling_Quality);
	SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);
	void* Pixels = calloc(Width * Height, 4);
	SDL_UpdateTexture(Texture, NULL, Pixels, Width * 4);
	ktn_free(Pixels);
	return Texture;
}

SDL_Texture* Surface_To_Texture(SDL_Surface* Surface) {
	SDL_Texture* Texture = SDL_CreateTextureFromSurface(Core.Renderer, Surface);
	if (Texture == NULL) {
		ktn_jump(I_No_Surface_Texture, "could not create texture from surface");
	}
	SDL_SetTextureScaleMode(Texture, Scaling_Quality);
	return Texture;
}

SDL_Texture* IMG_To_Texture(const char* Path) {
	SDL_Surface* Surface;
	ktn_load_bmp(Surface, Path);
	SDL_Texture* Texture = Surface_To_Texture(Surface);
	SDL_DestroySurface(Surface);
	return Texture;
}

Point Rotate_Internal(Point Input, Point Size, int Rot, int Subtraction) {
	for (int C1 = 0; C1 < 4; C1++) {
		if (C1 == Rot) {
			return Input;
		}
		Point Carrier = Input;
		Input.X = Size.Y - Subtraction - Carrier.Y;
		Input.Y = Carrier.X;
		int Subcarrier = Size.X;
		Size.X = Size.Y;
		Size.Y = Subcarrier;
	}
	return (Point){ };
}

Point Rotate_Pt(Point Input, Point Size, int Rot) {
	return Rotate_Internal(Input, Size, Rot, 1);
}

Point Rotate_Px(Point Input, Point Size, int Rot) {
	return Rotate_Internal(Input, Size, Rot, 0);
}