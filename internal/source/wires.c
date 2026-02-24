#include <connectables.h>

Wires Wires_List = { };

void Push_Wire(Wire Input) {
	Wires_List.Length++;
	if (Wires_List.Length >= Wires_List.Full_Size) {
		Wire* Buffer = malloc(sizeof(Wire) * Wires_List.Length);
		memcpy_c(Buffer, Wires_List.Data, sizeof(Wire) * Wires_List.Length);
		free_c(Wires_List.Data);
		Wires_List.Full_Size += 16;
		Wires_List.Data = malloc(sizeof(Wire) * Wires_List.Full_Size);
		memcpy_c(Wires_List.Data, Buffer, sizeof(Wire) * Wires_List.Length);
		free_c(Buffer);
	}
	Wires_List.Data[Wires_List.Length - 1] = Input;
}

void Pull_Wire(int Position) {
	if (Wires_List.Length > 0) {
		for (int C1 = 0; C1 < Wires_List.Length - Position - 1; C1++) {
			Wires_List.Data[Position + C1] = Wires_List.Data[Position + C1 + 1];
		}
		Wires_List.Length--;
	}
}

void Clear_Wires() {
	Wires_List.Full_Size = 0;
	Wires_List.Length = 0;
	free_c(Wires_List.Data);
}

void Clear_Unconnected_Wires() {
	int Index = 0;
	while (Index < Wires_List.Length) {
		if (!Wires_List.Data[Index].Filled) {
			Pull_Wire(Index);
		} else {
			Index++;
		}
	}
	Interface.Node_Cycle = 0;
}

void Render_Wire(int C1, int X_Offset, int Y_Offset, int X_Offset2, int Y_Offset2) {
	SDL_RenderLine(
		Core.Renderer,
		(float)((((Wires_List.Data[C1].X1 * LDE_TILESIZE) * Settings.Screen_Size) + (Data.Data_Grid[Wires_List.Data[
		C1].X1][Wires_List.Data[C1].Y1][5] * Settings.Screen_Size) - X_Offset) - X_Offset2),
		(float)((((Wires_List.Data[C1].Y1 * LDE_TILESIZE) * Settings.Screen_Size) + (Data.Data_Grid[Wires_List.Data[
		C1].X1][Wires_List.Data[C1].Y1][6] * Settings.Screen_Size) - Y_Offset) - Y_Offset2),
		(float)((((Wires_List.Data[C1].X2 * LDE_TILESIZE) * Settings.Screen_Size) + (Data.Data_Grid[Wires_List.Data[
		C1].X2][Wires_List.Data[C1].Y2][5] * Settings.Screen_Size) - X_Offset) - X_Offset2),
		(float)((((Wires_List.Data[C1].Y2 * LDE_TILESIZE) * Settings.Screen_Size) + (Data.Data_Grid[Wires_List.Data[
		C1].X2][Wires_List.Data[C1].Y2][6] * Settings.Screen_Size) - Y_Offset) - Y_Offset2)
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
		for (int C2 = 0; C2 < Wires_List.Length; C2++) {
			if (Wires_List.Data[C2].Filled) {
				for (int X = 0; X < (int)(ceil(Settings.Screen_Size * 0.5f)); X++) {
					for (int Y = 0; Y < (int)(ceil(Settings.Screen_Size * 0.5f)); Y++) {
						Render_Wire(C2, X, Y, Offset_X, Offset_Y);
					}
				}
			} else {
				Rects.Node.x = (int)((Wires_List.Data[C2].X1 * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
				Rects.Node.y = (int)((Wires_List.Data[C2].Y1 * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
				Render_Texture(Textures.Node, &Rects.Node);
			}
		}
		Clear_Renderer();
	}
	SDL_SetRenderTarget(Core.Renderer, Core.Game_Texture);
}

void Render_Wire_Nodes() {
	for (int C1 = 0; C1 < Wires_List.Length; C1++) {
		if (!Wires_List.Data[C1].Filled) {
			Interface.Node_Cycle += 60.0 / Interface.Frame_Rate;
			if (Interface.Node_Cycle > 360) {
				Interface.Node_Cycle = 0;
			}
			SDL_FPoint Centerpoint = {
				Settings.Screen_Size * LDE_TILESIZE * 0.5f,
				Settings.Screen_Size * LDE_TILESIZE * 0.5f
			};
			Rects.Node.x = (int)((Wires_List.Data[C1].X1 * LDE_TILESIZE) + (Data.Data_Grid[Wires_List.Data[C1].X1][
				Wires_List.Data[C1].Y1][5]) - Core.Camera.X - (LDE_TILESIZE * 0.5)) * Settings.Screen_Size;
			Rects.Node.y = (int)((Wires_List.Data[C1].Y1 * LDE_TILESIZE) + (Data.Data_Grid[Wires_List.Data[C1].X1][
				Wires_List.Data[C1].Y1][6]) - Core.Camera.Y - (LDE_TILESIZE * 0.5)) * Settings.Screen_Size;
			SDL_RenderTextureRotated(Core.Renderer, Textures.Node, NULL, &Rects.Node, Interface.Node_Cycle, &Centerpoint,
				SDL_FLIP_NONE);
		}
	}
}

void Connect_Wire(int X, int Y) {
	if (Wires_List.Length > 0 && !Wires_List.Data[Wires_List.Length - 1].Filled) {
		if (Data.Wiring_Grid[X][Y] == 0 || Data.Wiring_Grid[X][Y] == 2) {
			Wires_List.Data[Wires_List.Length - 1].X2 = X;
			Wires_List.Data[Wires_List.Length - 1].Y2 = Y;
			Wires_List.Data[Wires_List.Length - 1].Filled = true;
			Cache.Wire_State = Recache;
			for (int C1 = 0; C1 <= Wires_List.Length; C1++) {
				int End = Wires_List.Length - 1;
				if ((Wires_List.Data[C1].X1 == Wires_List.Data[End].X1 && Wires_List.Data[C1].Y1 == Wires_List.Data[
					End].Y1 && Wires_List.Data[C1].X2 == Wires_List.Data[End].X2 && Wires_List.Data[C1].Y2 ==
					Wires_List.Data[End].Y2) || (Wires_List.Data[C1].X1 == Wires_List.Data[End].X2 && Wires_List.Data[
					C1].Y1 == Wires_List.Data[End].Y2 && Wires_List.Data[C1].X2 == Wires_List.Data[End].X1 &&
					Wires_List.Data[C1].Y2 == Wires_List.Data[End].Y1)) {
					Pull_Wire(C1);
					Pull_Wire(Wires_List.Length - 1);
					break;
				}
			}
		} else {
			Pull_Wire(Wires_List.Length - 1);
		}
	} else {
		if (Data.Wiring_Grid[X][Y] == 1 || Data.Wiring_Grid[X][Y] == 2) {
			Wire New_Wire = { };
			New_Wire.X1 = X;
			New_Wire.Y1 = Y;
			Push_Wire(New_Wire);
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

void Distribute_Power(Wire** Grouped_List, int Grouped, int* Sizes) {
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
	Wire** Grouped_List = calloc(Wires_List.Length, sizeof(Wire*));
	int* Sizes = calloc(Wires_List.Length, sizeof(int));
	int Grouped = 0;
    if (Wires_List.Length > 0) {
		for (int C1 = 0; C1 < Wires_List.Length; C1++) {
			if (Wires_List.Data[C1].Filled) {
				Wire Temporary_Wire = Wires_List.Data[C1];
				if (Grouped > 0) {
					bool Uncategorized = true;
					for (int C2 = 0; C2 < Grouped; C2++) {
						if (Temporary_Wire.X1 == Grouped_List[C2][0].X1 &&
							Temporary_Wire.Y1 == Grouped_List[C2][0].Y1) {
							Grouped_List[C2] = realloc(Grouped_List[C2], sizeof(Wire) * (C2 + 1));
							Grouped_List[C2][C2] = Temporary_Wire;
							Sizes[C2] = C2 + 1;
							Uncategorized = false;
							break;
						}
					}
					if (Uncategorized) {
						Grouped_List[Grouped] = malloc(sizeof(Wire));
						Grouped_List[Grouped][0] = Temporary_Wire;
						Sizes[Grouped] = 1;
						Grouped++;
					}
				} else {
					Grouped_List[Grouped] = malloc(sizeof(Wire));
					Grouped_List[Grouped][0] = Temporary_Wire;
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