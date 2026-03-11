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

void Render_Cable(Bridge Chosen) {
	SDL_RenderLine(
		Core.Renderer,
		((Chosen.X1 * LDE_TILESIZE) * Settings.Screen_Size) + (Data.Data_Grid[Chosen.X1][Chosen.Y1][5] *
			Settings.Screen_Size),
		((Chosen.Y1 * LDE_TILESIZE) * Settings.Screen_Size) + (Data.Data_Grid[Chosen.X1][Chosen.Y1][6] *
			Settings.Screen_Size),
		((Chosen.X2 * LDE_TILESIZE) * Settings.Screen_Size) + (Data.Data_Grid[Chosen.X2][Chosen.Y2][5] *
			Settings.Screen_Size),
		((Chosen.Y2 * LDE_TILESIZE) * Settings.Screen_Size) + (Data.Data_Grid[Chosen.X2][Chosen.Y2][6] *
			Settings.Screen_Size)
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
						//Render_Wire(C2, X, Y, Offset_X, Offset_Y);
					}
				}
				Render_Cable(Wires.Data[C2]);
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
			Interface.Node_Cycle += 60.0f / Interface.Frame_Rate;
			if (Interface.Node_Cycle >= 360.0f) {
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

#define Compare1(Victim) (Wires.Data[C1].Victim == Wires.Data[End].Victim)
#define Compare2(A, B) (Wires.Data[C1].A == Wires.Data[End].B)
void Connect_Wire(int X, int Y) {
	int End = Wires.Length - 1;
	if (Wires.Length > 0 && !Wires.Data[End].Filled) {
		if (Data.Wiring_Grid[X][Y] == F_In || Data.Wiring_Grid[X][Y] == F_Either) {
			Wires.Data[End].X2 = X;
			Wires.Data[End].Y2 = Y;
			Wires.Data[End].Filled = true;
			Cache.Wire_State = Recache;
			for (int C1 = 0; C1 < End; C1++) {
				if ((Compare1(X1) && Compare1(Y1) && Compare1(X2) && Compare1(Y2)) || (Compare2(X1, X2) &&
					Compare2(Y1, Y2) && Compare2(X2, X1) && Compare2(Y2, Y1))) {
					Pull_Bridge(&Wires, End);
					Pull_Bridge(&Wires, C1);
					break;
				}
			}
		} else {
			Pull_Bridge(&Wires, Wires.Length - 1);
		}
	} else {
		if (Data.Wiring_Grid[X][Y] == F_Out || Data.Wiring_Grid[X][Y] == F_Either) {
			Bridge Wire = { };
			Wire.X1 = X;
			Wire.Y1 = Y;
			Push_Bridge(&Wires, Wire);
		}
	}
}
#undef Compare1
#undef Compare2

void Place_Wire() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Data.Visual_Grid[Column][Row] == LDE_INVALID) {
					Connect_Wire((int)(Data.Settings_Grid[Column][Row][S_ParentX]), (int)(Data.Settings_Grid[Column][Row][
						S_ParentY]));
				} else {
					Connect_Wire(Column, Row);
				}
				return;
			}
		}
	}
}

void Update_Power() {
	for (int C1 = 0; C1 < Wires.Length; C1++) {
		Bridge Wire = Wires.Data[C1];
		if (Wire.Filled) {
			float Volume = Data.Data_Grid[Wire.X1][Wire.Y1][Stored_Power];
			Volume = min(Volume, Data.Data_Grid[Wire.X2][Wire.Y2][Power_Cap] - Data.Data_Grid[Wire.X2][Wire.Y2][
				Stored_Power]);
			Data.Data_Grid[Wire.X1][Wire.Y1][Stored_Power] -= Volume;
			Data.Data_Grid[Wire.X2][Wire.Y2][Stored_Power] += Volume;
		}
	}
}