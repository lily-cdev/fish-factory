#include <Legacy_Connectables.hpp>

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
		Rects.Tile_1x1.x = static_cast<int>((Column * 40) -
			Core.Camera.X) * Settings.Screen_Size;
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = static_cast<int>((Row * 40) -
				Core.Camera.Y) * Settings.Screen_Size;
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Pipes_List.size() > 0 && !Pipes_List[Pipes_List.size() - 1].Filled) {
					bool Is_Adjacent = false;
					if ((Column < LDE_GRIDSIZE && Pipes_List[Pipes_List.size() - 1].X1 == Column + 1) ||
						(Column > 0 && Pipes_List[Pipes_List.size() - 1].X1 == Column - 1)) {
						Is_Adjacent = true;
					} else if ((Row < LDE_GRIDSIZE &&Pipes_List[Pipes_List.size() - 1].Y1 == Row + 1) ||
						(Row > 0 && Pipes_List[Pipes_List.size() - 1].Y1 == Row - 1)) {
						Is_Adjacent = true;
					}
					bool Is_Pipe_Adjacent = false;
					if (Is_Adjacent) {
						if (Data.Plumbing_Grid[Column][Row] == 0) {
							Is_Pipe_Adjacent = true;
						} else if ((Data.Plumbing_Grid[Column][Row] == 1 ||
							Data.Plumbing_Grid[Column][Row] == 5) && Column > 0 &&
							Pipes_List[Pipes_List.size() - 1].X1 == Column - 1) {
							Is_Pipe_Adjacent = true;
						} else if ((Data.Plumbing_Grid[Column][Row] == 2 ||
							Data.Plumbing_Grid[Column][Row] == 6) && Row > 0 &&
							Pipes_List[Pipes_List.size() - 1].Y1 == Row - 1) {
							Is_Pipe_Adjacent = true;
						} else if ((Data.Plumbing_Grid[Column][Row] == 3 ||
							Data.Plumbing_Grid[Column][Row] == 7) && Column < LDE_GRIDSIZE &&
							Pipes_List[Pipes_List.size() - 1].X1 == Column + 1) {
							Is_Pipe_Adjacent = true;
						} else if ((Data.Plumbing_Grid[Column][Row] == 4 ||
							Data.Plumbing_Grid[Column][Row] == 8) && Row < LDE_GRIDSIZE &&
							Pipes_List[Pipes_List.size() - 1].Y1 == Row + 1) {
							Is_Pipe_Adjacent = true;
						}
					}
					if (Is_Pipe_Adjacent && (Data.Connection_Grid[Column][Row] != LDE_INVALID ||
						Data.Plumbing_Grid[Column][Row] != LDE_INVALID) &&
						(Data.Settings_Grid[Column][Row][0] == 0 ||
						Data.Settings_Grid[Column][Row][0] == 1)) {
						Pipes_List[Pipes_List.size() - 1].X2 = Column;
						Pipes_List[Pipes_List.size() - 1].Y2 = Row;
						Pipes_List[Pipes_List.size() - 1].Filled = true;
						Pipes_List[Pipes_List.size() - 1].Determine_Orientation();
						for (int Counter = 0; Counter < Pipes_List.size() - 1; Counter++) {
							if ((Pipes_List[Counter].X1 == Pipes_List[Pipes_List.size() - 1].X1 &&
								Pipes_List[Counter].Y1 == Pipes_List[Pipes_List.size() - 1].Y1 &&
								Pipes_List[Counter].X2 == Pipes_List[Pipes_List.size() - 1].X2 &&
								Pipes_List[Counter].Y2 == Pipes_List[Pipes_List.size() - 1].Y2) ||
								(Pipes_List[Counter].X1 == Pipes_List[Pipes_List.size() - 1].X2 &&
									Pipes_List[Counter].Y1 == Pipes_List[Pipes_List.size() - 1].Y2 &&
									Pipes_List[Counter].X2 == Pipes_List[Pipes_List.size() - 1].X1 &&
									Pipes_List[Counter].Y2 == Pipes_List[Pipes_List.size() - 1].Y1)) {
								Pipes_List.erase(Pipes_List.begin() + Counter);
								Pipes_List.pop_back();
								break;
							}
						}
					} else {
						Pipes_List.pop_back();
					}
				} else {
					if ((Data.Connection_Grid[Column][Row] != LDE_INVALID ||
						Data.Plumbing_Grid[Column][Row] > LDE_INVALID) &&
						(Data.Settings_Grid[Column][Row][0] == 0 ||
						Data.Settings_Grid[Column][Row][0] == 2)) {
						Pipe New_Pipe;
						New_Pipe.X1 = Column;
						New_Pipe.Y1 = Row;
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
			Rects.Tile_1x1.x = static_cast<int>((Pipes_List[Counter].X1 * 40) +
				Pipes_List[Counter].X_Offset - Core.Camera.X) * Settings.Screen_Size;
			Rects.Tile_1x1.y = static_cast<int>((Pipes_List[Counter].Y1 * 40) +
				Pipes_List[Counter].Y_Offset - Core.Camera.Y) * Settings.Screen_Size;
			SDL_RenderTexture(Core.Renderer, Textures.Arrow
				.Data[Pipes_List[Counter].Orienation], NULL, &Rects.Tile_1x1);
		} else {
			Rects.Sapling.x = static_cast<int>((Pipes_List[Counter].X1 * 40) -
				Core.Camera.X) * Settings.Screen_Size;
			Rects.Sapling.y = static_cast<int>((Pipes_List[Counter].Y1 * 40) -
				Core.Camera.Y) * Settings.Screen_Size;
			SDL_RenderTexture(Core.Renderer, Textures.Sapling, NULL,
				&Rects.Sapling);
		}
	}
}

void Distribute_Fluid(std::vector<std::vector<Pipe>> &Grouped_List) {
	for (int Counter1 = 0; Counter1 < Grouped_List.size(); Counter1++) {
		double Remaining_Fluid = Data.Data_Grid[Grouped_List
			[Counter1][0].X1][Grouped_List[Counter1][0].Y1][Stored_Fluids];
		double Used_Fluid = 0;
		for (int Counter2 = 0; Counter2 < Grouped_List[Counter1].size(); Counter2++) {
			if (Data.Items_Grid[Grouped_List[Counter1][Counter2].X2][
				Grouped_List[Counter1][Counter2].Y2] == LDE_INVALID ||
				Data.Items_Grid[Grouped_List[Counter1][Counter2].X1][
				Grouped_List[Counter1][Counter2].Y1] == Data.Items_Grid[
				Grouped_List[Counter1][Counter2].X2][Grouped_List[Counter1][
				Counter2].Y2]) {
				double Minimum = std::min(Remaining_Fluid, Data.Data_Grid[Grouped_List[Counter1][
					Counter2].X2][Grouped_List[Counter1][Counter2].Y2][1] -
					Data.Data_Grid[Grouped_List[Counter1][Counter2].X2][Grouped_List[
					Counter1][Counter2].Y2][Stored_Fluids]);
				Data.Data_Grid[Grouped_List[Counter1][Counter2].X2][Grouped_List[Counter1][
					Counter2].Y2][Stored_Fluids] = Data.Data_Grid[Grouped_List[Counter1][Counter2].X2][
					Grouped_List[Counter1][Counter2].Y2][Stored_Fluids] + Minimum;
				Update_Item(Grouped_List[Counter1][Counter2].X2, Grouped_List[Counter1][
					Counter2].Y2, Data.Items_Grid[Grouped_List[Counter1][
					Counter2].X1][Grouped_List[Counter1][Counter2].Y1],
					Data.Temperature_Grid[Grouped_List[Counter1][Counter2].X1][
					Grouped_List[Counter1][Counter2].Y1]);
				Remaining_Fluid = Remaining_Fluid - Minimum;
				Used_Fluid = Used_Fluid + Minimum;
			}
		}
		Data.Data_Grid[Grouped_List[Counter1][0].X1][
			Grouped_List[Counter1][0].Y1][Stored_Fluids] =
			Data.Data_Grid[Grouped_List[Counter1][0].X1][
			Grouped_List[Counter1][0].Y1][Stored_Fluids] - Used_Fluid;
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
						if (Temporary_Pipe.X1 == Grouped_List[Counter2][0].X1 &&
							Temporary_Pipe.Y1 == Grouped_List[Counter2][0].Y1) {
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