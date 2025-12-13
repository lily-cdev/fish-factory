#include <Core.h>
#include <Preloader.h>
#include <Items.h>
#include <Connectables.h>

std::vector<Pipe> Pipes_List = { };

void Clear_Pipes() {
	Pipes_List.clear();
}

void Clear_Unconnected_Pipes() {
	for (int Counter = 0; Counter < Pipes_List.size(); Counter++) {
		if (!Pipes_List[Counter].Filled) {
			Pipes_List.erase(Pipes_List.begin() + Counter);
		}
	}
}

void Place_Pipe() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rectangles_Access.Tile_1x1.x = static_cast<int>((Column * 40) -
			UI_Access.Camera_X) * Settings_Access.Screen_Size;
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rectangles_Access.Tile_1x1.y = static_cast<int>((Row * 40) -
				UI_Access.Camera_Y) * Settings_Access.Screen_Size;
			if (Detect_Mouse_Collision(Rectangles_Access.Tile_1x1)) {
				if (Pipes_List.size() > 0 && !Pipes_List[Pipes_List.size() - 1].Filled) {
					bool Is_Adjacent = false;
					if ((Column < LDE_GRIDSIZE && Pipes_List[Pipes_List.size() - 1].First_X == Column + 1) ||
						(Column > 0 && Pipes_List[Pipes_List.size() - 1].First_X == Column - 1)) {
						Is_Adjacent = true;
					} else if ((Row < LDE_GRIDSIZE &&Pipes_List[Pipes_List.size() - 1].First_Y == Row + 1) ||
						(Row > 0 && Pipes_List[Pipes_List.size() - 1].First_Y == Row - 1)) {
						Is_Adjacent = true;
					}
					bool Is_Pipe_Adjacent = false;
					if (Is_Adjacent) {
						if (Data_Access.Plumbing_Grid[Column][Row] == 0) {
							Is_Pipe_Adjacent = true;
						} else if ((Data_Access.Plumbing_Grid[Column][Row] == 1 ||
							Data_Access.Plumbing_Grid[Column][Row] == 5) && Column > 0 &&
							Pipes_List[Pipes_List.size() - 1].First_X == Column - 1) {
							Is_Pipe_Adjacent = true;
						} else if ((Data_Access.Plumbing_Grid[Column][Row] == 2 ||
							Data_Access.Plumbing_Grid[Column][Row] == 6) && Row > 0 &&
							Pipes_List[Pipes_List.size() - 1].First_Y == Row - 1) {
							Is_Pipe_Adjacent = true;
						} else if ((Data_Access.Plumbing_Grid[Column][Row] == 3 ||
							Data_Access.Plumbing_Grid[Column][Row] == 7) && Column < LDE_GRIDSIZE &&
							Pipes_List[Pipes_List.size() - 1].First_X == Column + 1) {
							Is_Pipe_Adjacent = true;
						} else if ((Data_Access.Plumbing_Grid[Column][Row] == 4 ||
							Data_Access.Plumbing_Grid[Column][Row] == 8) && Row < LDE_GRIDSIZE &&
							Pipes_List[Pipes_List.size() - 1].First_Y == Row + 1) {
							Is_Pipe_Adjacent = true;
						}
					}
					if (Is_Pipe_Adjacent && (Data_Access.Connection_Grid[Column][Row] != LDE_INVALID ||
						Data_Access.Plumbing_Grid[Column][Row] != LDE_INVALID) &&
						(Data_Access.Settings_Grid[Column][Row][0] == 0 ||
						Data_Access.Settings_Grid[Column][Row][0] == 1)) {
						Pipes_List[Pipes_List.size() - 1].Second_X = Column;
						Pipes_List[Pipes_List.size() - 1].Second_Y = Row;
						Pipes_List[Pipes_List.size() - 1].Filled = true;
						Pipes_List[Pipes_List.size() - 1].Determine_Orientation();
						for (int Counter = 0; Counter < Pipes_List.size() - 1; Counter++) {
							if ((Pipes_List[Counter].First_X == Pipes_List[Pipes_List.size() - 1].First_X &&
								Pipes_List[Counter].First_Y == Pipes_List[Pipes_List.size() - 1].First_Y &&
								Pipes_List[Counter].Second_X == Pipes_List[Pipes_List.size() - 1].Second_X &&
								Pipes_List[Counter].Second_Y == Pipes_List[Pipes_List.size() - 1].Second_Y) ||
								(Pipes_List[Counter].First_X == Pipes_List[Pipes_List.size() - 1].Second_X &&
									Pipes_List[Counter].First_Y == Pipes_List[Pipes_List.size() - 1].Second_Y &&
									Pipes_List[Counter].Second_X == Pipes_List[Pipes_List.size() - 1].First_X &&
									Pipes_List[Counter].Second_Y == Pipes_List[Pipes_List.size() - 1].First_Y)) {
								Pipes_List.erase(Pipes_List.begin() + Counter);
								Pipes_List.pop_back();
								break;
							}
						}
					} else {
						Pipes_List.pop_back();
					}
				} else {
					if ((Data_Access.Connection_Grid[Column][Row] != LDE_INVALID ||
						Data_Access.Plumbing_Grid[Column][Row] > LDE_INVALID) &&
						(Data_Access.Settings_Grid[Column][Row][0] == 0 ||
						Data_Access.Settings_Grid[Column][Row][0] == 2)) {
						Pipe New_Pipe;
						New_Pipe.First_X = Column;
						New_Pipe.First_Y = Row;
						Pipes_List.push_back(New_Pipe);
					}
				}
			}
		}
	}
}

void Render_Pipes() {
	for (int Counter = 0; Counter < Pipes_List.size(); Counter++) {
		if (Pipes_List[Counter].Filled) {
			Rectangles_Access.Tile_1x1.x = static_cast<int>((Pipes_List[Counter].First_X * 40) +
				Pipes_List[Counter].X_Offset - UI_Access.Camera_X) * Settings_Access.Screen_Size;
			Rectangles_Access.Tile_1x1.y = static_cast<int>((Pipes_List[Counter].First_Y * 40) +
				Pipes_List[Counter].Y_Offset - UI_Access.Camera_Y) * Settings_Access.Screen_Size;
			SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Arrow
				.Data[Pipes_List[Counter].Orienation], NULL, &Rectangles_Access.Tile_1x1);
		} else {
			Rectangles_Access.Sapling.x = static_cast<int>((Pipes_List[Counter].First_X * 40) -
				UI_Access.Camera_X) * Settings_Access.Screen_Size;
			Rectangles_Access.Sapling.y = static_cast<int>((Pipes_List[Counter].First_Y * 40) -
				UI_Access.Camera_Y) * Settings_Access.Screen_Size;
			SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Sapling, NULL,
				&Rectangles_Access.Sapling);
		}
	}
}

void Distribute_Fluid(std::vector<std::vector<Pipe>> &Grouped_List) {
	for (int Counter1 = 0; Counter1 < Grouped_List.size(); Counter1++) {
		double Remaining_Fluid = Data_Access.Data_Grid[Grouped_List
			[Counter1][0].First_X][Grouped_List[Counter1][0].First_Y][Stored_Fluids];
		double Used_Fluid = 0;
		for (int Counter2 = 0; Counter2 < Grouped_List[Counter1].size(); Counter2++) {
			if (Data_Access.Items_Grid[Grouped_List[Counter1][Counter2].Second_X]
				[Grouped_List[Counter1][Counter2].Second_Y] == LDE_INVALID ||
				Data_Access.Items_Grid[Grouped_List[Counter1][Counter2].First_X]
				[Grouped_List[Counter1][Counter2].First_Y] == Data_Access.Items_Grid
				[Grouped_List[Counter1][Counter2].Second_X][Grouped_List[Counter1]
				[Counter2].Second_Y]) {
				double Minimum = std::min(Remaining_Fluid, Data_Access.Data_Grid[Grouped_List[Counter1]
					[Counter2].Second_X][Grouped_List[Counter1][Counter2].Second_Y][1]
					- Data_Access.Data_Grid[Grouped_List[Counter1][Counter2].Second_X][Grouped_List
					[Counter1][Counter2].Second_Y][Stored_Fluids]);
				Data_Access.Data_Grid[Grouped_List[Counter1][Counter2].Second_X][Grouped_List[Counter1]
					[Counter2].Second_Y][Stored_Fluids] = Data_Access.Data_Grid[Grouped_List[Counter1][Counter2].Second_X]
					[Grouped_List[Counter1][Counter2].Second_Y][Stored_Fluids] + Minimum;
				Update_Item(Grouped_List[Counter1][Counter2].Second_X, Grouped_List[Counter1]
					[Counter2].Second_Y, Data_Access.Items_Grid[Grouped_List[Counter1]
					[Counter2].First_X][Grouped_List[Counter1][Counter2].First_Y],
					Data_Access.Temperature_Grid[Grouped_List[Counter1][Counter2].First_X]
					[Grouped_List[Counter1][Counter2].First_Y]);
				Remaining_Fluid = Remaining_Fluid - Minimum;
				Used_Fluid = Used_Fluid + Minimum;
			}
		}
		Data_Access.Data_Grid[Grouped_List[Counter1][0].First_X]
			[Grouped_List[Counter1][0].First_Y][Stored_Fluids] =
			Data_Access.Data_Grid[Grouped_List[Counter1][0].First_X]
			[Grouped_List[Counter1][0].First_Y][Stored_Fluids] - Used_Fluid;
	}
}

void Update_Pipes() {
	std::vector<std::vector<Pipe>> Grouped_List = { };
	if (Pipes_List.size() > 0) {
		for (int Counter1 = 0; Counter1 < Pipes_List.size(); Counter1++) {
			if (Pipes_List[Counter1].Filled) {
				Pipe Temporary_Pipe = Pipes_List[Counter1];
				if (Grouped_List.size() > 0) {
					bool Categorised = false;
					for (int Counter2 = 0; Counter2 < Grouped_List.size(); Counter2++) {
						if (Temporary_Pipe.First_X == Grouped_List[Counter2][0].First_X &&
							Temporary_Pipe.First_Y == Grouped_List[Counter2][0].First_Y) {
							Grouped_List[Counter2].push_back(Temporary_Pipe);
							Categorised = true;
						}
					}
					if (!Categorised) {
						Grouped_List.push_back({ Temporary_Pipe });
					}
				}
				else {
					Grouped_List.push_back({ Temporary_Pipe });
				}
			}
		}
		Distribute_Fluid(Grouped_List);
	}
}