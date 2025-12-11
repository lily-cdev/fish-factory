#include <Core.h>
#include <Preloader.h>
#include <Connectables.h>

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
	UI_Access.Node_Cycle = 0;
}

void Render_Wire(int Counter, int X_Offset, int Y_Offset, int X_Offset2, int Y_Offset2) {
	SDL_RenderLine(Core_Access.Application_Renderer,
		static_cast<float>((((Wires_List[Counter].First_X * 40) * Settings_Access.Screen_Size) + (Data_Access.Data_Grid
		[Wires_List[Counter].First_X][Wires_List[Counter].First_Y][5] * Settings_Access.Screen_Size) - X_Offset) - X_Offset2),
		static_cast<float>((((Wires_List[Counter].First_Y * 40) * Settings_Access.Screen_Size) + (Data_Access.Data_Grid
		[Wires_List[Counter].First_X][Wires_List[Counter].First_Y][6] * Settings_Access.Screen_Size) - Y_Offset) - Y_Offset2),
		static_cast<float>((((Wires_List[Counter].Second_X * 40) * Settings_Access.Screen_Size) + (Data_Access.Data_Grid
		[Wires_List[Counter].Second_X][Wires_List[Counter].Second_Y][5] * Settings_Access.Screen_Size) - X_Offset) - X_Offset2),
		static_cast<float>((((Wires_List[Counter].Second_Y * 40) * Settings_Access.Screen_Size) + (Data_Access.Data_Grid
		[Wires_List[Counter].Second_X][Wires_List[Counter].Second_Y][6] * Settings_Access.Screen_Size) - Y_Offset) - Y_Offset2));
}

void Render_Wires() {
	for (int Counter1 = 0; Counter1 < 4; Counter1++) {
		SDL_SetRenderTarget(Core_Access.Application_Renderer, Cache_Access.Wire_Cache.Data[Counter1]);
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
		Offset_X *= 20 * LDE_GRIDSIZE * Settings_Access.Screen_Size;
		Offset_Y *= 20 * LDE_GRIDSIZE * Settings_Access.Screen_Size;
		SDL_RenderClear(Core_Access.Application_Renderer);
		Set_Renderer_Color(Colors_Access.Copper_Wire);
		for (int Counter2 = 0; Counter2 < Wires_List.size(); Counter2++) {
			if (Wires_List[Counter2].Filled) {
				for (int X = 0; X < static_cast<int>(std::ceil(Settings_Access.Screen_Size / 2.0f)); X++) {
					for (int Y = 0; Y < static_cast<int>(std::ceil(Settings_Access.Screen_Size / 2.0f)); Y++) {
						Render_Wire(Counter2, X, Y, Offset_X, Offset_Y);
					}
				}
			} else {
				Rectangles_Access.Node.x = static_cast<int>((Wires_List[Counter2].First_X * 40) -
					UI_Access.Camera_X) * Settings_Access.Screen_Size;
				Rectangles_Access.Node.y = static_cast<int>((Wires_List[Counter2].First_Y * 40) -
					UI_Access.Camera_Y) * Settings_Access.Screen_Size;
				SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Node,
					NULL, &Rectangles_Access.Node);
			}
		}
		Clear_Renderer();
	}
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Core_Access.Game_Texture);
}

void Render_Wire_Nodes() {
	for (int Counter = 0; Counter < Wires_List.size(); Counter++) {
		if (!Wires_List[Counter].Filled) {
			UI_Access.Node_Cycle += 60.0 / UI_Access.Frame_Rate;
			if (UI_Access.Node_Cycle > 360) {
				UI_Access.Node_Cycle = 0;
			}
			SDL_FPoint Centerpoint = { Settings_Access.Screen_Size * 20.0f,
				Settings_Access.Screen_Size * 20.0f };
			Rectangles_Access.Node.x = static_cast<int>((Wires_List[Counter].First_X * 40) +
				(Data_Access.Data_Grid[Wires_List[Counter].First_X][Wires_List[Counter].First_Y][5]) -
				UI_Access.Camera_X - 20) * Settings_Access.Screen_Size;
			Rectangles_Access.Node.y = static_cast<int>((Wires_List[Counter].First_Y * 40) +
				(Data_Access.Data_Grid[Wires_List[Counter].First_X][Wires_List[Counter].First_Y][6]) -
				UI_Access.Camera_Y - 20) * Settings_Access.Screen_Size;
			SDL_RenderTextureRotated(Core_Access.Application_Renderer, Textures_Access.Node,
				NULL, &Rectangles_Access.Node, UI_Access.Node_Cycle, &Centerpoint, SDL_FLIP_NONE);
		}
	}
}

void Connect_Wire(int X, int Y) {
	if (Wires_List.size() > 0 && !Wires_List[Wires_List.size() - 1].Filled) {
		if (Data_Access.Wiring_Grid[X][Y] == 0 || Data_Access.Wiring_Grid[X][Y] == 2) {
			Wires_List[Wires_List.size() - 1].Second_X = X;
			Wires_List[Wires_List.size() - 1].Second_Y = Y;
			Wires_List[Wires_List.size() - 1].Filled = true;
			Cache_Access.Wire_State = Recache;
			for (int Counter = 0; Counter < Wires_List.size() - 1; Counter++) {
				if ((Wires_List[Counter].First_X == Wires_List[Wires_List.size() - 1].First_X &&
					Wires_List[Counter].First_Y == Wires_List[Wires_List.size() - 1].First_Y &&
					Wires_List[Counter].Second_X == Wires_List[Wires_List.size() - 1].Second_X &&
					Wires_List[Counter].Second_Y == Wires_List[Wires_List.size() - 1].Second_Y) ||
					(Wires_List[Counter].First_X == Wires_List[Wires_List.size() - 1].Second_X &&
					Wires_List[Counter].First_Y == Wires_List[Wires_List.size() - 1].Second_Y &&
					Wires_List[Counter].Second_X == Wires_List[Wires_List.size() - 1].First_X &&
					Wires_List[Counter].Second_Y == Wires_List[Wires_List.size() - 1].First_Y)) {
					Wires_List.erase(Wires_List.begin() + Counter);
					Wires_List.pop_back();
					break;
				}
			}
		} else {
			Wires_List.pop_back();
		}
	} else {
		if (Data_Access.Wiring_Grid[X][Y] == 1 || Data_Access.Wiring_Grid[X][Y] == 2) {
			Wire New_Wire;
			New_Wire.First_X = X;
			New_Wire.First_Y = Y;
			Wires_List.push_back(New_Wire);
		}
	}
}

void Place_Wire() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rectangles_Access.Tile_1x1.x = static_cast<int>((Column * 40) -
			UI_Access.Camera_X) * Settings_Access.Screen_Size;
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rectangles_Access.Tile_1x1.y = static_cast<int>((Row * 40) -
				UI_Access.Camera_Y) * Settings_Access.Screen_Size;
			if (Detect_Mouse_Collision(Rectangles_Access.Tile_1x1)) {
				if (Data_Access.Visual_Grid[Column][Row] == LDE_INVALID) {
					Connect_Wire(static_cast<int>(Data_Access.Settings_Grid[Column][Row][1]),
						static_cast<int>(Data_Access.Settings_Grid[Column][Row][2]));
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
		double Remaining_Power = Data_Access.Data_Grid[Grouped_List[Counter1][0].First_X]
			[Grouped_List[Counter1][0].First_Y][Stored_Power];
		double Used_Power = 0;
		for (int Counter2 = 0; Counter2 < Grouped_List[Counter1].size(); Counter2++) {
			double Minimum = std::min(Remaining_Power, Data_Access.Data_Grid[Grouped_List[Counter1][Counter2].Second_X]
				[Grouped_List[Counter1][Counter2].Second_Y][Power_Cap] - Data_Access.Data_Grid[Grouped_List[Counter1]
				[Counter2].Second_X][Grouped_List[Counter1][Counter2].Second_Y][Stored_Power]);
			Data_Access.Data_Grid[Grouped_List[Counter1][Counter2].Second_X][Grouped_List
				[Counter1][Counter2].Second_Y][Stored_Power] =
				Data_Access.Data_Grid[Grouped_List[Counter1][Counter2].Second_X]
				[Grouped_List[Counter1][Counter2].Second_Y][Stored_Power] + Minimum;
			Remaining_Power = Remaining_Power - Minimum;
			Used_Power = Used_Power + Minimum;
		}
		Data_Access.Data_Grid[Grouped_List[Counter1][0].First_X][Grouped_List
			[Counter1][0].First_Y][Stored_Power] = Data_Access.Data_Grid[Grouped_List
			[Counter1][0].First_X][Grouped_List[Counter1][0].First_Y][Stored_Power] - Used_Power;
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
						if (Temporary_Wire.First_X == Grouped_List[Counter2][0].First_X &&
							Temporary_Wire.First_Y == Grouped_List[Counter2][0].First_Y) {
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