#include <connectables.h>

Bridges Wires = { };

void Render_Wire(int C1, int X_Offset, int Y_Offset, int X_Offset2, int Y_Offset2) {
	SDL_RenderLine(
		Core.Renderer,
		(float)((((Wires.Data[C1].X1 * LDE_TILESIZE) * Settings.Screen_Size) + (Data.Data_Grid[Wires.Data[C1].X1][
		Wires.Data[C1].Y1][5] * Settings.Screen_Size) - X_Offset) - X_Offset2),
		(float)((((Wires.Data[C1].Y1 * LDE_TILESIZE) * Settings.Screen_Size) + (Data.Data_Grid[Wires.Data[C1].X1][
		Wires.Data[C1].Y1][6] * Settings.Screen_Size) - Y_Offset) - Y_Offset2),
		(float)((((Wires.Data[C1].X2 * LDE_TILESIZE) * Settings.Screen_Size) + (Data.Data_Grid[Wires.Data[C1].X2][
		Wires.Data[C1].Y2][5] * Settings.Screen_Size) - X_Offset) - X_Offset2),
		(float)((((Wires.Data[C1].Y2 * LDE_TILESIZE) * Settings.Screen_Size) + (Data.Data_Grid[Wires.Data[C1].X2][
		Wires.Data[C1].Y2][6] * Settings.Screen_Size) - Y_Offset) - Y_Offset2)
	);
}

void Render_Wires() {
	for (int C1 = 0; C1 < 4; C1++) {
		SDL_SetRenderTarget(Core.Renderer, Cache.Wire_Cache.Data[C1]);
		int Offset_X = 0;
		int Offset_Y = 0;
		switch (C1) {
		case 1:
			Offset_X = 1;
			break;
		case 2:
			Offset_X = 1;
			Offset_Y = 1;
			break;
		case 3:
			Offset_Y = 1;
			break;
		default:
			break;
		}
		Offset_X *= LDE_GRIDSIZE * Settings.Screen_Size * 20;
		Offset_Y *= LDE_GRIDSIZE * Settings.Screen_Size * 20;
		SDL_RenderClear(Core.Renderer);
		Set_Renderer_Color(Colors.Copper_Wire);
		for (int C2 = 0; C2 < Wires.Length; C2++) {
			if (Wires.Data[C2].Filled) {
				for (int X = 0; X < (int)(ceil(Settings.Screen_Size * 0.5f)); X++) {
					for (int Y = 0; Y < (int)(ceil(Settings.Screen_Size * 0.5f)); Y++) {
						Render_Wire(C2, X, Y, Offset_X, Offset_Y);
					}
				}
			} else {
				Rects.Node.x = (int)((Wires.Data[C2].X1 * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
				Rects.Node.y = (int)((Wires.Data[C2].Y1 * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
				Render_Texture(Textures.Node, &Rects.Node);
			}
		}
		Clear_Renderer();
	}
	SDL_SetRenderTarget(Core.Renderer, Core.Game_Texture);
}

void Render_Wire_Nodes() {
	for (int C1 = 0; C1 < Wires.Length; C1++) {
		if (!Wires.Data[C1].Filled) {
			Interface.Node_Cycle += 60.0 / Interface.Frame_Rate;
			if (Interface.Node_Cycle > 360) {
				Interface.Node_Cycle = 0;
			}
			SDL_FPoint Centerpoint = {
				Settings.Screen_Size * LDE_TILESIZE * 0.5f,
				Settings.Screen_Size * LDE_TILESIZE * 0.5f
			};
			Rects.Node.x = (int)((Wires.Data[C1].X1 * LDE_TILESIZE) + (Data.Data_Grid[Wires.Data[C1].X1][Wires.Data[
				C1].Y1][5]) - Core.Camera.X - (LDE_TILESIZE * 0.5)) * Settings.Screen_Size;
			Rects.Node.y = (int)((Wires.Data[C1].Y1 * LDE_TILESIZE) + (Data.Data_Grid[Wires.Data[C1].X1][Wires.Data[
				C1].Y1][6]) - Core.Camera.Y - (LDE_TILESIZE * 0.5)) * Settings.Screen_Size;
			SDL_RenderTextureRotated(Core.Renderer, Textures.Node, NULL, &Rects.Node, Interface.Node_Cycle, &Centerpoint,
				SDL_FLIP_NONE);
		}
	}
}

void Connect_Wire(int X, int Y) {
	if (Wires.Length > 0 && !Wires.Data[Wires.Length - 1].Filled) {
		if (Data.Wiring_Grid[X][Y] == 0 || Data.Wiring_Grid[X][Y] == 2) {
			Wires.Data[Wires.Length - 1].X2 = X;
			Wires.Data[Wires.Length - 1].Y2 = Y;
			Wires.Data[Wires.Length - 1].Filled = true;
			Cache.Wire_State = Recache;
			for (int C1 = 0; C1 <= Wires.Length; C1++) {
				int End = Wires.Length - 1;
				if ((Wires.Data[C1].X1 == Wires.Data[End].X1 && Wires.Data[C1].Y1 == Wires.Data[End].Y1 && Wires.Data[
					C1].X2 == Wires.Data[End].X2 && Wires.Data[C1].Y2 == Wires.Data[End].Y2) || (Wires.Data[C1].X1 ==
					Wires.Data[End].X2 && Wires.Data[C1].Y1 == Wires.Data[End].Y2 && Wires.Data[C1].X2 == Wires.Data[
					End].X1 && Wires.Data[C1].Y2 == Wires.Data[End].Y1)) {
					Pull_Bridge(&Wires, C1);
					Pull_Bridge(&Wires, Wires.Length - 1);
					break;
				}
			}
		} else {
			Pull_Bridge(&Wires, Wires.Length - 1);
		}
	} else {
		if (Data.Wiring_Grid[X][Y] == 1 || Data.Wiring_Grid[X][Y] == 2) {
			Bridge Wire = { };
			Wire.X1 = X;
			Wire.Y1 = Y;
			Push_Bridge(&Wires, Wire);
		}
	}
}

void Place_Wire() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Data.Visual_Grid[Column][Row] == LDE_INVALID) {
					Connect_Wire((int)(Data.Settings_Grid[Column][Row][1]), (int)(Data.Settings_Grid[Column][Row][2]));
				} else {
					Connect_Wire(Column, Row);
				}
				return;
			}
		}
	}
}

void Distribute_Power(Bridge** Grouped_List, int Grouped, int* Sizes) {
	for (int C1 = 0; C1 < Grouped; C1++) {
		float Remaining_Power = Data.Data_Grid[Grouped_List[C1][0].X1][Grouped_List[C1][0].Y1][Stored_Power];
		float Used_Power = 0;
		for (int C2 = 0; C2 < Sizes[C1]; C2++) {
			float Minimum = min(Remaining_Power, Data.Data_Grid[Grouped_List[C1][C2].X2][Grouped_List[C1][C2].Y2][
				Power_Cap] - Data.Data_Grid[Grouped_List[C1][C2].X2][Grouped_List[C1][C2].Y2][Stored_Power]);
			Data.Data_Grid[Grouped_List[C1][C2].X2][Grouped_List[C1][C2].Y2][Stored_Power] = Data.Data_Grid[Grouped_List[
				C1][C2].X2][Grouped_List[C1][C2].Y2][Stored_Power] + Minimum;
			Remaining_Power = Remaining_Power - Minimum;
			Used_Power = Used_Power + Minimum;
		}
		Data.Data_Grid[Grouped_List[C1][0].X1][Grouped_List[C1][0].Y1][Stored_Power] = Data.Data_Grid[Grouped_List[C1][
			0].X1][Grouped_List[C1][0].Y1][Stored_Power] - Used_Power;
	}
}

void Update_Power() {
	Bridge** Grouped_List = calloc(Wires.Length, sizeof(Bridge*));
	int* Sizes = calloc(Wires.Length, sizeof(int));
	int Grouped = 0;
    if (Wires.Length > 0) {
		for (int C1 = 0; C1 < Wires.Length; C1++) {
			if (Wires.Data[C1].Filled) {
				Bridge Wire = Wires.Data[C1];
				if (Grouped > 0) {
					bool Uncategorized = true;
					for (int C2 = 0; C2 < Grouped; C2++) {
						if (Wire.X1 == Grouped_List[C2][0].X1 &&
							Wire.Y1 == Grouped_List[C2][0].Y1) {
							Grouped_List[C2] = realloc(Grouped_List[C2], sizeof(Wire) * (C2 + 1));
							Grouped_List[C2][C2] = Wire;
							Sizes[C2] = C2 + 1;
							Uncategorized = false;
							break;
						}
					}
					if (Uncategorized) {
						Grouped_List[Grouped] = malloc(sizeof(Wire));
						Grouped_List[Grouped][0] = Wire;
						Sizes[Grouped] = 1;
						Grouped++;
					}
				} else {
					Grouped_List[Grouped] = malloc(sizeof(Wire));
					Grouped_List[Grouped][0] = Wire;
					Sizes[Grouped] = 1;
					Grouped++;
				}
			}
		}
		Distribute_Power(Grouped_List, Grouped, Sizes);
	}
	for (int C1 = 0; C1 < Grouped; C1++) {
		free_c(Grouped_List[C1]);
	}
	free_c(Grouped_List);
	free_c(Sizes);
}