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

void Render_Button(const Texture_Array* Button, const Rect_Array* Hitbox, UI_Link Link, SDL_Color Underline_Color) {
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
	} else {
		Render_Texture(Button->Data[0], &Hitbox->Data[0]);
	}
}

void Push_Docks(Point Input) {
	if (Temporary.Docks.Length >= Temporary.Docks.Full_Size) {
		Point* Buffer = malloc(sizeof(Point) * Temporary.Docks.Length);
		memcpy_c(Buffer, Temporary.Docks.Data, sizeof(Point) * Temporary.Docks.Length);
		free_c(Temporary.Docks.Data);
		Temporary.Docks.Full_Size += 16;
		Temporary.Docks.Data = malloc(sizeof(Point) * Temporary.Docks.Full_Size);
		memcpy_c(Temporary.Docks.Data, Buffer, sizeof(Point) * Temporary.Docks.Length);
		free_c(Buffer);
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
	if (Pos.X + W > LDE_GRIDSIZE || Pos.Y + H > LDE_GRIDSIZE) {
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
		jump(I_Render_Failed, Carrier);
	}
	SDL_RenderTexture(Core.Renderer, Texture, NULL, Rect);
}

int Render_Rich_Text(Font_Index Font, char* Raw_Text, Point Pos, bool Inverted, bool Disabled) {
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
	int* Lengths = malloc(sizeof(int) * Fragment_Count);
	for (int C1 = 0; C1 < Fragment_Count; C1++) {
		Lengths[C1] = strlen(Raw_Text) + 1;
		Fragments[C1] = malloc(sizeof(char) * Lengths[C1]);
	}
	Start = 0;
	End = 0;
	int Index = 0;
	while ((Yield = strchr(Raw_Text + Start, '|')) != NULL) {
		End = Yield - Raw_Text;
		int Length = End - Start;
		memcpy_c(Fragments[Index], Raw_Text + Start, Length);
		Fragments[Index][Length] = '\0';
		Index++;
		Start = End + 1;
	}
	strncpy(Fragments[Index], Raw_Text + Start, Lengths[Index]);
	int Multiplier = LDE_INVALID;
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
		int Type = LDE_INVALID;
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
		} else if (Type != LDE_INVALID) {
			char* Subfragment = Fragments[Multiplier * (Subtractor - C1)];
			memmove(Subfragment, Subfragment + 3, strlen(Subfragment + 3) + 1);
		}
		SDL_Texture* Fragment_Texture = Render_Text(Font, Fragments[Multiplier * (Subtractor - C1)], Colors.Abyss_Black);
		if (Fragment_Texture != NULL) {
			SDL_FRect Fragment_Rectangle = {
				(float)(Pos.X * Settings.Scalar),
				(float)(Pos.Y * Settings.Scalar) + Offset,
				(float)Fragment_Texture->w,
				(float)Fragment_Texture->h
			};
			if (!Disabled) {
				Render_Texture(Fragment_Texture, &Fragment_Rectangle);
			}
			Offset += Fragment_Rectangle.h;
		}
		free_texture(Fragment_Texture);
	}
	for (int C1 = 0; C1 < Fragment_Count; C1++) {
		free_c(Fragments[C1]);
	}
	free_c(Fragments);
	free_c(Lengths);
	return Offset;
}

void Tick_State() {
	Core.State = (Core.State * 2891336453u) + 747796405u;
	Core.State ^= Core.State >> 16;
}

void Reseed_State() {
	struct timespec Spec;
	timespec_get(&Spec, TIME_UTC);
	Core.State = (uint32_t)(Spec.tv_nsec / 1000000);
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
	return (Input.X >= 0 && Input.Y >= 0 && Input.X < LDE_GRIDSIZE && Input.Y < LDE_GRIDSIZE);
}

bool Check_Glyph(char Character, Font_Index Font) {
	return Fonts.Glyphs[Font][(int)Character].Allocated;
}

void Apply_Glyph(char Character, Font_Index Font) {
	FT_Face Selection = Fonts.Faces[Font];
	if (FT_Load_Char(Selection, (FT_ULong)Character, FT_LOAD_RENDER) != 0) {
		return;
	}
	FT_GlyphSlot Slot = Selection->glyph;
	Glyph Subglyph = { };
	Subglyph.Allocated = true;
	Subglyph.Key = Character;
	Subglyph.Bounds = (Point){ Slot->bitmap.width, Slot->bitmap.rows };
	Subglyph.Bearing = (Point){ Slot->bitmap_left, Slot->bitmap_top };
	Subglyph.Advance = Slot->advance.x >> 6;
	SDL_Surface* Carrier = SDL_CreateSurface(Subglyph.Bounds.X, Subglyph.Bounds.Y, SDL_PIXELFORMAT_RGBA8888);
	SDL_LockSurface(Carrier);
	const SDL_PixelFormatDetails* Details = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA8888);
	const uint32_t White = SDL_MapRGBA(Details, NULL, 255, 255, 255, SDL_ALPHA_OPAQUE);
	uint32_t* Pixels = (uint32_t*)Carrier->pixels;
	memset(Pixels, 0, Carrier->h * Carrier->pitch);
	for (int Y = 0; Y < Subglyph.Bounds.Y; Y++) {
		for (int X = 0; X < Subglyph.Bounds.X; X++) {
			uint8_t Alpha = Slot->bitmap.buffer[(Slot->bitmap.pitch * Y) + X];
			uint32_t* Target = &Pixels[((Carrier->pitch / sizeof(uint32_t)) * Y) + X];
			if (Settings.Anti_Aliasing) {
				if (Alpha == 255) {
					*Target = White;
				} else if (Alpha > 0) {
					*Target = SDL_MapRGBA(Details, NULL, 255, 255, 255, Alpha);
				}
			} else {
				if (Alpha > 127) {
					*Target = White;
				}
			}
		}
	}
	SDL_UnlockSurface(Carrier);
	Subglyph.Data = Surface_To_Texture(Core.Renderer, Carrier);
	Fonts.Glyphs[Font][(int)Character] = Subglyph;
	SDL_DestroySurface(Carrier);
}

SDL_Texture* Render_Text(Font_Index Font, const char* Text, SDL_Color Color) {
	FT_Face Selection = Fonts.Faces[Font];
	int Length = strlen(Text);
	Point Bounds = { };
	for (int C1 = 0; C1 < Length; C1++) {
		if (!Check_Glyph(Text[C1], Font)) {
			Apply_Glyph(Text[C1], Font);
		}
		Bounds.X += Fonts.Glyphs[Font][(int)Text[C1]].Advance;
	}
	int Ascender = Selection->size->metrics.ascender >> 6;
	int Descender = Selection->size->metrics.descender >> 6;
	Bounds.Y = Ascender - Descender;
	if (Bounds.X <= 0 || Bounds.Y <= 0) {
		return NULL;
	}
	SDL_Texture* Yield = New_Texture(Core.Renderer, Bounds.X, Bounds.Y);
	int Cursor = 0;
	for (int C1 = 0; C1 < Length; C1++) {
		Glyph Carrier = Fonts.Glyphs[Font][(int)Text[C1]];
		//render to yield
	}
	return Yield;
}

int Get_Height(Font_Index Font) {
	return Fonts.Faces[Font]->size->metrics.height >> 6;
}