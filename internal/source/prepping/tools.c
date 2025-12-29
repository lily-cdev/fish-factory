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