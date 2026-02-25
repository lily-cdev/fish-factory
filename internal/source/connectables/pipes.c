#include <connectables.h>

Bridges Pipes = { };

void Orient_Pipe(Bridge* Input) {
	if (Input->X1 == Input->X2 - 1) {
		Input->Orienation = 0;
		Input->X_Offset = 20;
	} else if (Input->X1 == Input->X2 + 1) {
		Input->Orienation = 2;
		Input->X_Offset = -20;
	} else if (Input->Y1 == Input->Y2 - 1) {
		Input->Orienation = 1;
		Input->Y_Offset = 20;
	} else {
		Input->Orienation = 3;
		Input->Y_Offset = -20;
	}
}

void Place_Pipe() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Pipes.Length > 0 && !Pipes.Data[Pipes.Length - 1].Filled) {
					bool Is_Adjacent = false;
					if ((Column < LDE_GRIDSIZE && Pipes.Data[Pipes.Length - 1].X1 == Column + 1) || (Column >= 0 &&
						Pipes.Data[Pipes.Length - 1].X1 == Column - 1)) {
						Is_Adjacent = true;
					} else if ((Row < LDE_GRIDSIZE && Pipes.Data[Pipes.Length - 1].Y1 == Row + 1) || (Row >= 0 &&
						Pipes.Data[Pipes.Length - 1].Y1 == Row - 1)) {
						Is_Adjacent = true;
					}
					bool Is_Pipe_Adjacent = false;
					if (Is_Adjacent) {
						if (Data.Plumbing_Grid[Column][Row] == 0) {
							Is_Pipe_Adjacent = true;
						} else if ((Data.Plumbing_Grid[Column][Row] == 1 || Data.Plumbing_Grid[Column][Row] == 5) &&
							Column > 0 && Pipes.Data[Pipes.Length - 1].X1 == Column - 1) {
							Is_Pipe_Adjacent = true;
						} else if ((Data.Plumbing_Grid[Column][Row] == 2 || Data.Plumbing_Grid[Column][Row] == 6) && Row >
							0 && Pipes.Data[Pipes.Length - 1].Y1 == Row - 1) {
							Is_Pipe_Adjacent = true;
						} else if ((Data.Plumbing_Grid[Column][Row] == 3 || Data.Plumbing_Grid[Column][Row] == 7) &&
							Column < LDE_GRIDSIZE && Pipes.Data[Pipes.Length - 1].X1 == Column + 1) {
							Is_Pipe_Adjacent = true;
						} else if ((Data.Plumbing_Grid[Column][Row] == 4 || Data.Plumbing_Grid[Column][Row] == 8) && Row <
							LDE_GRIDSIZE && Pipes.Data[Pipes.Length - 1].Y1 == Row + 1) {
							Is_Pipe_Adjacent = true;
						}
					}
					if (Is_Pipe_Adjacent && Data.Plumbing_Grid[Column][Row] != LDE_INVALID && (Data.Settings_Grid[Column][
							Row][0] == 0 || Data.Settings_Grid[Column][Row][0] == 1)) {
						Pipes.Data[Pipes.Length - 1].X2 = Column;
						Pipes.Data[Pipes.Length - 1].Y2 = Row;
						Pipes.Data[Pipes.Length - 1].Filled = true;
						Orient_Pipe(&Pipes.Data[Pipes.Length - 1]);
						for (int C1 = 0; C1 < Pipes.Length - 1; C1++) {
							int End = Pipes.Length - 1;
							if ((Pipes.Data[C1].X1 == Pipes.Data[End].X1 && Pipes.Data[C1].Y1 ==
								Pipes.Data[End].Y1 && Pipes.Data[C1].X2 == Pipes.Data[End].X2 &&
								Pipes.Data[C1].Y2 == Pipes.Data[End].Y2) || (Pipes.Data[C1].X1 ==
								Pipes.Data[End].X2 && Pipes.Data[C1].Y1 == Pipes.Data[End].Y2 &&
								Pipes.Data[C1].X2 == Pipes.Data[End].X1 && Pipes.Data[C1].Y2 ==
								Pipes.Data[End].Y1)) {
								Pull_Bridge(&Pipes, C1);
								Pull_Bridge(&Pipes, Pipes.Length - 1);
								break;
							}
						}
					} else {
						Pull_Bridge(&Pipes, Pipes.Length - 1);
					}
				} else {
					if ((Data.Plumbing_Grid[Column][Row] > LDE_INVALID) && (Data.Settings_Grid[Column][Row][0] == 0 ||
							Data.Settings_Grid[Column][Row][0] == 2)) {
						Bridge Pipe = { };
						Pipe.X1 = Column;
						Pipe.Y1 = Row;
						Push_Bridge(&Pipes, Pipe);
					}
				}
			}
		}
	}
}

void Render_Pipes() {
	for (int C1 = 0; C1 < Pipes.Length; C1++) {
		if (Pipes.Data[C1].Filled) {
			Rects.Tile_1x1.x = (int)((Pipes.Data[C1].X1 * LDE_TILESIZE) + Pipes.Data[C1].X_Offset - Core.Camera.X) *
				Settings.Screen_Size;
			Rects.Tile_1x1.y = (int)((Pipes.Data[C1].Y1 * LDE_TILESIZE) + Pipes.Data[C1].Y_Offset - Core.Camera.Y) *
				Settings.Screen_Size;
			Render_Texture(Textures.Arrow.Data[Pipes.Data[C1].Orienation], &Rects.Tile_1x1);
		} else {
			Rects.Sapling.x = (float)((Pipes.Data[C1].X1 * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
			Rects.Sapling.y = (float)((Pipes.Data[C1].Y1 * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
			Render_Texture(Textures.Sapling, &Rects.Sapling);
		}
	}
}

void Distribute_Fluid(Bridge** Grouped_List, int Grouped, int* Sizes) {
	for (int C1 = 0; C1 < Grouped; C1++) {
		float Remaining_Fluid = Data.Data_Grid[Grouped_List[C1][0].X1][Grouped_List[C1][0].Y1][Stored_Fluids];
		float Used_Fluid = 0;
		for (int C2 = 0; C2 < Sizes[C1]; C2++) {
			if (Data.Items_Grid[Grouped_List[C1][C2].X2][Grouped_List[C1][C2].Y2] == LDE_INVALID || Data.Items_Grid[
				Grouped_List[C1][C2].X1][Grouped_List[C1][C2].Y1] == Data.Items_Grid[Grouped_List[C1][C2].X2][Grouped_List[
				C1][C2].Y2]) {
				float Minimum = min(Remaining_Fluid, Data.Data_Grid[Grouped_List[C1][C2].X2][Grouped_List[C1][C2].Y2][1] -
					Data.Data_Grid[Grouped_List[C1][C2].X2][Grouped_List[C1][C2].Y2][Stored_Fluids]);
				Data.Data_Grid[Grouped_List[C1][C2].X2][Grouped_List[C1][C2].Y2][Stored_Fluids] = Data.Data_Grid[
					Grouped_List[C1][C2].X2][Grouped_List[C1][C2].Y2][Stored_Fluids] + Minimum;
				Update_Item(Grouped_List[C1][C2].X2, Grouped_List[C1][C2].Y2, Data.Items_Grid[Grouped_List[C1][C2].X1][
					Grouped_List[C1][C2].Y1], Data.Temperature_Grid[Grouped_List[C1][C2].X1][Grouped_List[C1][C2].Y1]);
				Remaining_Fluid = Remaining_Fluid - Minimum;
				Used_Fluid = Used_Fluid + Minimum;
			}
		}
		Data.Data_Grid[Grouped_List[C1][0].X1][Grouped_List[C1][0].Y1][Stored_Fluids] = Data.Data_Grid[Grouped_List[C1][
			0].X1][Grouped_List[C1][0].Y1][Stored_Fluids] - Used_Fluid;
	}
}

void Update_Pipes() {
	Bridge** Grouped_List = calloc(Pipes.Length, sizeof(Bridge*));
	int* Sizes = calloc(Pipes.Length, sizeof(int));
	int Grouped = 0;
    if (Pipes.Length > 0) {
		for (int C1 = 0; C1 < Pipes.Length; C1++) {
			if (Pipes.Data[C1].Filled) {
				Bridge Pipe = Pipes.Data[C1];
				if (Grouped > 0) {
					bool Uncategorized = true;
					for (int C2 = 0; C2 < Grouped; C2++) {
						if (Pipe.X1 == Grouped_List[C2][0].X1 && Pipe.Y1 == Grouped_List[C2][0].Y1) {
							Grouped_List[C2] = realloc(Grouped_List[C2], sizeof(Bridge) * (C2 + 1));
							Grouped_List[C2][C2] = Pipe;
							Sizes[C2] = C2 + 1;
							Uncategorized = false;
							break;
						}
					}
					if (Uncategorized) {
						Grouped_List[Grouped] = malloc(sizeof(Bridge));
						Grouped_List[Grouped][0] = Pipe;
						Sizes[Grouped] = 1;
						Grouped++;
					}
				} else {
					Grouped_List[Grouped] = malloc(sizeof(Bridge));
					Grouped_List[Grouped][0] = Pipe;
					Sizes[Grouped] = 1;
					Grouped++;
				}
			}
		}
		Distribute_Fluid(Grouped_List, Grouped, Sizes);
	}
	for (int C1 = 0; C1 < Grouped; C1++) {
		free_c(Grouped_List[C1]);
	}
	free_c(Grouped_List);
	free_c(Sizes);
}