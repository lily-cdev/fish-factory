#include <Legacy_Connectables.hpp>

std::vector<Wire> Wires_List = { };

void Clear_Wires() {
	Wires_List.clear();
}

void Clear_Unconnected_Wires() {
	int Index = 0;
	while (Index < Wires_List.size()) {
		if (!Wires_List[Index].Filled) {
			Wires_List.erase(Wires_List.begin() + Index);
		} else {
			Index++;
		}
	}
	Interface.Node_Cycle = 0;
}

void Render_Wire(int Counter, int X_Offset, int Y_Offset, int X_Offset2, int Y_Offset2) {
	SDL_RenderLine(Core.Renderer,
		static_cast<float>((((Wires_List[Counter].X1 * 40) *
		Settings.Screen_Size) + (Data.Data_Grid[Wires_List[
		Counter].X1][Wires_List[Counter].Y1][5] *
		Settings.Screen_Size) - X_Offset) - X_Offset2),
		static_cast<float>((((Wires_List[Counter].Y1 * 40) *
		Settings.Screen_Size) + (Data.Data_Grid[Wires_List[
		Counter].X1][Wires_List[Counter].Y1][6] *
		Settings.Screen_Size) - Y_Offset) - Y_Offset2),
		static_cast<float>((((Wires_List[Counter].X2 * 40) *
		Settings.Screen_Size) + (Data.Data_Grid[Wires_List[
		Counter].X2][Wires_List[Counter].Y2][5] *
		Settings.Screen_Size) - X_Offset) - X_Offset2),
		static_cast<float>((((Wires_List[Counter].Y2 * 40) *
		Settings.Screen_Size) + (Data.Data_Grid[Wires_List[
		Counter].X2][Wires_List[Counter].Y2][6] *
		Settings.Screen_Size) - Y_Offset) - Y_Offset2));
}

void Render_Wires() {
	for (int Counter1 = 0; Counter1 < 4; Counter1++) {
		SDL_SetRenderTarget(Core.Renderer, Cache.Wire_Cache.Data[Counter1]);
		int Offset_X = 0;
		int Offset_Y = 0;
		switch (Counter1) {
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
		Offset_X *= 20 * LDE_GRIDSIZE * Settings.Screen_Size;
		Offset_Y *= 20 * LDE_GRIDSIZE * Settings.Screen_Size;
		SDL_RenderClear(Core.Renderer);
		Set_Renderer_Color(Colors.Copper_Wire);
		for (int Counter2 = 0; Counter2 < Wires_List.size(); Counter2++) {
			if (Wires_List[Counter2].Filled) {
				for (int X = 0; X < static_cast<int>(std::ceil(Settings.Screen_Size * 0.5f)); X++) {
					for (int Y = 0; Y < static_cast<int>(std::ceil(Settings.Screen_Size * 0.5f)); Y++) {
						Render_Wire(Counter2, X, Y, Offset_X, Offset_Y);
					}
				}
			} else {
				Rects.Node.x = static_cast<int>((Wires_List[Counter2].X1 * 40) -
					Core.Camera.X) * Settings.Screen_Size;
				Rects.Node.y = static_cast<int>((Wires_List[Counter2].Y1 * 40) -
					Core.Camera.Y) * Settings.Screen_Size;
				SDL_RenderTexture(Core.Renderer, Textures.Node,
					NULL, &Rects.Node);
			}
		}
		Clear_Renderer();
	}
	SDL_SetRenderTarget(Core.Renderer, Core.Game_Texture);
}

void Render_Wire_Nodes() {
	for (int Counter = 0; Counter < Wires_List.size(); Counter++) {
		if (!Wires_List[Counter].Filled) {
			Interface.Node_Cycle += 60.0 / Interface.Frame_Rate;
			if (Interface.Node_Cycle > 360) {
				Interface.Node_Cycle = 0;
			}
			SDL_FPoint Centerpoint = {
				Settings.Screen_Size * LDE_TILESIZE * 0.5f,
				Settings.Screen_Size * LDE_TILESIZE * 0.5f
			};
			Rects.Node.x = static_cast<int>((Wires_List[Counter].X1 * LDE_TILESIZE) +
				(Data.Data_Grid[Wires_List[Counter].X1][Wires_List[Counter].Y1][5]) -
				Core.Camera.X - (LDE_TILESIZE * 0.5)) * Settings.Screen_Size;
			Rects.Node.y = static_cast<int>((Wires_List[Counter].Y1 * LDE_TILESIZE) +
				(Data.Data_Grid[Wires_List[Counter].X1][Wires_List[Counter].Y1][6]) -
				Core.Camera.Y - (LDE_TILESIZE * 0.5)) * Settings.Screen_Size;
			SDL_RenderTextureRotated(Core.Renderer, Textures.Node,
				NULL, &Rects.Node, Interface.Node_Cycle, &Centerpoint, SDL_FLIP_NONE);
		}
	}
}

void Connect_Wire(int X, int Y) {
	if (Wires_List.size() > 0 && !Wires_List[Wires_List.size() - 1].Filled) {
		if (Data.Wiring_Grid[X][Y] == 0 || Data.Wiring_Grid[X][Y] == 2) {
			Wires_List[Wires_List.size() - 1].X2 = X;
			Wires_List[Wires_List.size() - 1].Y2 = Y;
			Wires_List[Wires_List.size() - 1].Filled = true;
			Cache.Wire_State = Recache;
			for (int Counter = 0; Counter <= Wires_List.size(); Counter++) {
				int End = Wires_List.size() - 1;
				if ((Wires_List[Counter].X1 == Wires_List[End].X1 &&
					Wires_List[Counter].Y1 == Wires_List[End].Y1 &&
					Wires_List[Counter].X2 == Wires_List[End].X2 &&
					Wires_List[Counter].Y2 == Wires_List[End].Y2) ||
					(Wires_List[Counter].X1 == Wires_List[End].X2 &&
					Wires_List[Counter].Y1 == Wires_List[End].Y2 &&
					Wires_List[Counter].X2 == Wires_List[End].X1 &&
					Wires_List[Counter].Y2 == Wires_List[End].Y1)) {
					Wires_List.erase(Wires_List.begin() + Counter);
					Wires_List.pop_back();
					break;
				}
			}
		} else {
			Wires_List.pop_back();
		}
	} else {
		if (Data.Wiring_Grid[X][Y] == 1 || Data.Wiring_Grid[X][Y] == 2) {
			Wire New_Wire;
			New_Wire.X1 = X;
			New_Wire.Y1 = Y;
			Wires_List.push_back(New_Wire);
		}
	}
}

void Place_Wire() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = static_cast<int>((Column * 40) -
			Core.Camera.X) * Settings.Screen_Size;
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = static_cast<int>((Row * 40) -
				Core.Camera.Y) * Settings.Screen_Size;
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Data.Visual_Grid[Column][Row] == LDE_INVALID) {
					Connect_Wire(static_cast<int>(Data.Settings_Grid[Column][Row][1]),
						static_cast<int>(Data.Settings_Grid[Column][Row][2]));
				} else {
					Connect_Wire(Column, Row);
				}
				return;
			}
		}
	}
}

void Distribute_Power(std::vector<std::vector<Wire>> &Grouped_List) {
	for (int Counter1 = 0; Counter1 < Grouped_List.size(); Counter1++) {
		double Remaining_Power = Data.Data_Grid[Grouped_List[Counter1][0].X1]
			[Grouped_List[Counter1][0].Y1][Stored_Power];
		double Used_Power = 0;
		for (int Counter2 = 0; Counter2 < Grouped_List[Counter1].size(); Counter2++) {
			double Minimum = std::min(Remaining_Power, Data.Data_Grid[Grouped_List[Counter1][Counter2].X2][
				Grouped_List[Counter1][Counter2].Y2][Power_Cap] - Data.Data_Grid[Grouped_List[Counter1][
				Counter2].X2][Grouped_List[Counter1][Counter2].Y2][Stored_Power]);
			Data.Data_Grid[Grouped_List[Counter1][Counter2].X2][Grouped_List[
				Counter1][Counter2].Y2][Stored_Power] =
				Data.Data_Grid[Grouped_List[Counter1][Counter2].X2][
				Grouped_List[Counter1][Counter2].Y2][Stored_Power] + Minimum;
			Remaining_Power = Remaining_Power - Minimum;
			Used_Power = Used_Power + Minimum;
		}
		Data.Data_Grid[Grouped_List[Counter1][0].X1][Grouped_List[
			Counter1][0].Y1][Stored_Power] = Data.Data_Grid[Grouped_List[
			Counter1][0].X1][Grouped_List[Counter1][0].Y1][Stored_Power] - Used_Power;
	}
}

void Update_Power() {
	std::vector<std::vector<Wire>> Grouped_List = { };
	if (Wires_List.size() > 0) {
		for (int Counter1 = 0; Counter1 < Wires_List.size(); Counter1++) {
			if (Wires_List[Counter1].Filled) {
				Wire Temporary_Wire = Wires_List[Counter1];
				if (Grouped_List.size() > 0) {
					bool Categorised = false;
					for (int Counter2 = 0; Counter2 < Grouped_List.size(); Counter2++) {
						if (Temporary_Wire.X1 == Grouped_List[Counter2][0].X1 &&
							Temporary_Wire.Y1 == Grouped_List[Counter2][0].Y1) {
							Grouped_List[Counter2].push_back(Temporary_Wire);
							Categorised = true;
						}
					}
					if (!Categorised) {
						Grouped_List.push_back({ Temporary_Wire });
					}
				} else {
					Grouped_List.push_back({ Temporary_Wire });
				}
			}
		}
		Distribute_Power(Grouped_List);
	}
}