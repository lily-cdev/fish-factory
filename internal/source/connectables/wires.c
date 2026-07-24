#include <connectables.h>

Bridges Wires = { };

void Render_Subcable(Bridge Chosen, Point Pos, Point Offset) {
	SDL_RenderLine(Core.Renderer,
		ktn_fscale(Chosen.X1 * ktn_tile_size) + ktn_fscale(Data.Data_Grid[Chosen.X1][Chosen.Y1][5]) + (float)(Pos.X + Offset.X),
		ktn_fscale(Chosen.Y1 * ktn_tile_size) + ktn_fscale(Data.Data_Grid[Chosen.X1][Chosen.Y1][6]) + (float)(Pos.Y + Offset.Y),
		ktn_fscale(Chosen.X2 * ktn_tile_size) + ktn_fscale(Data.Data_Grid[Chosen.X2][Chosen.Y2][5]) + (float)(Pos.X + Offset.X),
		ktn_fscale(Chosen.Y2 * ktn_tile_size) + ktn_fscale(Data.Data_Grid[Chosen.X2][Chosen.Y2][6]) + (float)(Pos.Y + Offset.Y)
	);
}

void Render_Cable(Bridge Chosen, Point Offset) {
	float Radius = Settings.Scalar * 1.5f;
	for (int X = -Radius; X <= Radius; X++) {
		for (int Y = -Radius; Y <= Radius; Y++) {
			if ((float)sqrtf(ktn_sqr(X) + ktn_sqr(Y)) <= Radius) {
				Render_Subcable(Chosen, (Point){ X, Y }, Offset);
			}
		}
	}
}

void Render_Wires() {
	for (int C1 = 0; C1 < 4; C1++) {
		SDL_SetRenderTarget(Core.Renderer, Cache.Wire_Cache.Data[C1]);
		int Offset_X = (C1 == 1 || C1 == 2) ? ktn_scale(ktn_grid_size * 20) : 0;
		int Offset_Y = (C1 == 2 || C1 == 3) ? ktn_scale(ktn_grid_size * 20) : 0;
		SDL_RenderClear(Core.Renderer);
		Set_Renderer_Color(Colors.Copper_Wire);
		for (int C2 = 0; C2 < Wires.Length; C2++) {
			if (Wires.Data[C2].Filled) {
				Render_Cable(Wires.Data[C2], (Point){ -Offset_X, -Offset_Y });
			} else {
				Rects.Node.x = ktn_fscale((Wires.Data[C2].X1 * ktn_tile_size) - Core.Camera.X);
				Rects.Node.y = ktn_fscale((Wires.Data[C2].Y1 * ktn_tile_size) - Core.Camera.Y);
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
				Settings.Scalar * ktn_tile_size * 0.5f,
				Settings.Scalar * ktn_tile_size * 0.5f
			};
			Rects.Node.x = ktn_fscale((Wires.Data[C1].X1 * ktn_tile_size) + (Data.Data_Grid[Wires.Data[C1].X1][Wires.Data[C1].Y1][5]) -
				Core.Camera.X - (ktn_tile_size * 0.5f));
			Rects.Node.y = ktn_fscale((Wires.Data[C1].Y1 * ktn_tile_size) + (Data.Data_Grid[Wires.Data[C1].X1][Wires.Data[C1].Y1][6]) -
				Core.Camera.Y - (ktn_tile_size * 0.5f));
			SDL_RenderTextureRotated(Core.Renderer, Textures.Node, NULL, &Rects.Node, Interface.Node_Cycle, &Centerpoint,
				SDL_FLIP_NONE);
		}
	}
}

#define Compare1(Victim) (Wires.Data[C1].Victim == Wires.Data[End].Victim)
#define Compare2(A, B) (Wires.Data[C1].A == Wires.Data[End].B)
void Connect_Wire(Point Pos) {
	int End = Wires.Length - 1;
	if (Wires.Length > 0 && !Wires.Data[End].Filled) {
		if (Data.Wiring_Grid[pt(Pos)] == F_In || Data.Wiring_Grid[pt(Pos)] == F_Either) {
			Wires.Data[End].X2 = Pos.X;
			Wires.Data[End].Y2 = Pos.Y;
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
		if (Data.Wiring_Grid[pt(Pos)] == F_Out || Data.Wiring_Grid[pt(Pos)] == F_Either) {
			Bridge Wire = { };
			Wire.X1 = Pos.X;
			Wire.Y1 = Pos.Y;
			Push_Bridge(&Wires, Wire);
		}
	}
}
#undef Compare1
#undef Compare2

void Place_Wire() {
	for (int Column = 0; Column < ktn_grid_size; Column++) {
		Rects.Tile_1x1.x = ktn_fscale((Column * ktn_tile_size) - Core.Camera.X);
		for (int Row = 0; Row < ktn_grid_size; Row++) {
			Rects.Tile_1x1.y = ktn_fscale((Row * ktn_tile_size) - Core.Camera.Y);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Data.Visual_Grid[Column][Row] == ktn_invalid) {
					Connect_Wire((Point){
						(int)(Data.Settings_Grid[Column][Row][S_ParentX]),
						(int)(Data.Settings_Grid[Column][Row][S_ParentY])
					});
				} else {
					Connect_Wire((Point){ Column, Row });
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
			Volume = min(Volume, Data.Data_Grid[Wire.X2][Wire.Y2][Power_Cap] - Data.Data_Grid[Wire.X2][Wire.Y2][Stored_Power]);
			Data.Data_Grid[Wire.X1][Wire.Y1][Stored_Power] -= Volume;
			Data.Data_Grid[Wire.X2][Wire.Y2][Stored_Power] += Volume;
		}
	}
}