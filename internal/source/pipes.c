#include <connectables.h>

Pipes Pipes_List = { };

void Push_Pipe(Pipe Input) {
	Pipes_List.Length++;
	if (Pipes_List.Length >= Pipes_List.Full_Size) {
		Pipe* Buffer = malloc(sizeof(Pipe) * Pipes_List.Length);
		memcpy_c(Buffer, Pipes_List.Data, sizeof(Pipe) * Pipes_List.Length);
		free_c(Pipes_List.Data);
		Pipes_List.Full_Size += 16;
		Pipes_List.Data = malloc(sizeof(Pipe) * Pipes_List.Full_Size);
		memcpy_c(Pipes_List.Data, Buffer, sizeof(Pipe) * Pipes_List.Length);
		free_c(Buffer);
	}
	Pipes_List.Data[Pipes_List.Length - 1] = Input;
}

void Pull_Pipe(int Position) {
	if (Pipes_List.Length > 0) {
		for (int C1 = 0; C1 < Pipes_List.Length - Position - 1; C1++) {
			Pipes_List.Data[Position + C1] = Pipes_List.Data[Position + C1 + 1];
		}
		Pipes_List.Length--;
	}
}

void Orient_Pipe(Pipe* Input) {
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

void Clear_Pipes() {
	Pipes_List.Length = 0;
	Pipes_List.Full_Size = 0;
	free_c(Pipes_List.Data);
}

void Clear_Unconnected_Pipes() {
	for (int C1 = 0; C1 < Pipes_List.Length; C1++) {
		if (!Pipes_List.Data[C1].Filled) {
			Pull_Pipe(C1);
		}
	}
}

void Place_Pipe() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Pipes_List.Length > 0 && !Pipes_List.Data[Pipes_List.Length - 1].Filled) {
					bool Is_Adjacent = false;
					if ((Column < LDE_GRIDSIZE && Pipes_List.Data[Pipes_List.Length - 1].X1 == Column + 1) ||
						(Column >= 0 && Pipes_List.Data[Pipes_List.Length - 1].X1 == Column - 1)) {
						Is_Adjacent = true;
					} else if ((Row < LDE_GRIDSIZE && Pipes_List.Data[Pipes_List.Length - 1].Y1 == Row + 1) ||
						(Row >= 0 && Pipes_List.Data[Pipes_List.Length - 1].Y1 == Row - 1)) {
						Is_Adjacent = true;
					}
					bool Is_Pipe_Adjacent = false;
					if (Is_Adjacent) {
						if (Data.Plumbing_Grid[Column][Row] == 0) {
							Is_Pipe_Adjacent = true;
						} else if ((Data.Plumbing_Grid[Column][Row] == 1 || Data.Plumbing_Grid[Column][Row] == 5) &&
							Column > 0 && Pipes_List.Data[Pipes_List.Length - 1].X1 == Column - 1) {
							Is_Pipe_Adjacent = true;
						} else if ((Data.Plumbing_Grid[Column][Row] == 2 || Data.Plumbing_Grid[Column][Row] == 6) &&
							Row > 0 && Pipes_List.Data[Pipes_List.Length - 1].Y1 == Row - 1) {
							Is_Pipe_Adjacent = true;
						} else if ((Data.Plumbing_Grid[Column][Row] == 3 || Data.Plumbing_Grid[Column][Row] == 7) &&
							Column < LDE_GRIDSIZE && Pipes_List.Data[Pipes_List.Length - 1].X1 == Column + 1) {
							Is_Pipe_Adjacent = true;
						} else if ((Data.Plumbing_Grid[Column][Row] == 4 || Data.Plumbing_Grid[Column][Row] == 8) &&
							Row < LDE_GRIDSIZE && Pipes_List.Data[Pipes_List.Length - 1].Y1 == Row + 1) {
							Is_Pipe_Adjacent = true;
						}
					}
					if (Is_Pipe_Adjacent && Data.Plumbing_Grid[Column][Row] != LDE_INVALID && (Data.Settings_Grid[Column][
							Row][0] == 0 || Data.Settings_Grid[Column][Row][0] == 1)) {
						Pipes_List.Data[Pipes_List.Length - 1].X2 = Column;
						Pipes_List.Data[Pipes_List.Length - 1].Y2 = Row;
						Pipes_List.Data[Pipes_List.Length - 1].Filled = true;
						Orient_Pipe(&Pipes_List.Data[Pipes_List.Length - 1]);
						for (int C1 = 0; C1 < Pipes_List.Length - 1; C1++) {
							int End = Pipes_List.Length - 1;
							if ((Pipes_List.Data[C1].X1 == Pipes_List.Data[End].X1 && Pipes_List.Data[C1].Y1 ==
								Pipes_List.Data[End].Y1 && Pipes_List.Data[C1].X2 == Pipes_List.Data[End].X2 &&
								Pipes_List.Data[C1].Y2 == Pipes_List.Data[End].Y2) || (Pipes_List.Data[C1].X1 ==
								Pipes_List.Data[End].X2 && Pipes_List.Data[C1].Y1 == Pipes_List.Data[End].Y2 &&
								Pipes_List.Data[C1].X2 == Pipes_List.Data[End].X1 && Pipes_List.Data[C1].Y2 ==
								Pipes_List.Data[End].Y1)) {
								Pull_Pipe(C1);
								Pull_Pipe(Pipes_List.Length - 1);
								break;
							}
						}
					} else {
						Pull_Pipe(Pipes_List.Length - 1);
					}
				} else {
					if ((Data.Plumbing_Grid[Column][Row] > LDE_INVALID) && (Data.Settings_Grid[Column][Row][0] == 0 ||
							Data.Settings_Grid[Column][Row][0] == 2)) {
						Pipe New_Pipe = { };
						New_Pipe.X1 = Column;
						New_Pipe.Y1 = Row;
						Push_Pipe(New_Pipe);
					}
				}
			}
		}
	}
}

void Render_Pipes() {
	for (int C1 = 0; C1 < Pipes_List.Length; C1++) {
		if (Pipes_List.Data[C1].Filled) {
			Rects.Tile_1x1.x = (int)((Pipes_List.Data[C1].X1 * LDE_TILESIZE) + Pipes_List.Data[C1].X_Offset -
				Core.Camera.X) * Settings.Screen_Size;
			Rects.Tile_1x1.y = (int)((Pipes_List.Data[C1].Y1 * LDE_TILESIZE) + Pipes_List.Data[C1].Y_Offset -
				Core.Camera.Y) * Settings.Screen_Size;
			Render_Texture(Textures.Arrow.Data[Pipes_List.Data[C1].Orienation], &Rects.Tile_1x1);
		} else {
			Rects.Sapling.x = (float)((Pipes_List.Data[C1].X1 * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
			Rects.Sapling.y = (float)((Pipes_List.Data[C1].Y1 * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
			Render_Texture(Textures.Sapling, &Rects.Sapling);
		}
	}
}

void Distribute_Fluid(Pipe** Grouped_List, int Grouped, int* Sizes) {
	for (int C1 = 0; C1 < Grouped; C1++) {
		float Remaining_Fluid = Data.Data_Grid[Grouped_List[C1][0].X1][Grouped_List[C1][0].Y1][Stored_Fluids];
		float Used_Fluid = 0;
		for (int C2 = 0; C2 < Sizes[C1]; C2++) {
			if (Data.Items_Grid[Grouped_List[C1][C2].X2][Grouped_List[C1][C2].Y2] == LDE_INVALID ||
				Data.Items_Grid[Grouped_List[C1][C2].X1][Grouped_List[C1][C2].Y1] == Data.Items_Grid[
				Grouped_List[C1][C2].X2][Grouped_List[C1][C2].Y2]) {
				float Minimum = min(Remaining_Fluid, Data.Data_Grid[Grouped_List[C1][C2].X2][Grouped_List[
					C1][C2].Y2][1] - Data.Data_Grid[Grouped_List[C1][C2].X2][Grouped_List[C1][
					C2].Y2][Stored_Fluids]);
				Data.Data_Grid[Grouped_List[C1][C2].X2][Grouped_List[C1][C2].Y2][Stored_Fluids] =
					Data.Data_Grid[Grouped_List[C1][C2].X2][Grouped_List[C1][C2].Y2][Stored_Fluids] +
					Minimum;
				Update_Item(Grouped_List[C1][C2].X2, Grouped_List[C1][C2].Y2, Data.Items_Grid[
					Grouped_List[C1][C2].X1][Grouped_List[C1][C2].Y1], Data.Temperature_Grid[
					Grouped_List[C1][C2].X1][Grouped_List[C1][C2].Y1]);
				Remaining_Fluid = Remaining_Fluid - Minimum;
				Used_Fluid = Used_Fluid + Minimum;
			}
		}
		Data.Data_Grid[Grouped_List[C1][0].X1][Grouped_List[C1][0].Y1][Stored_Fluids] = Data.Data_Grid[
			Grouped_List[C1][0].X1][Grouped_List[C1][0].Y1][Stored_Fluids] - Used_Fluid;
	}
}

void Update_Pipes() {
	Pipe** Grouped_List = calloc(Pipes_List.Length, sizeof(Pipe*));
	int* Sizes = calloc(Pipes_List.Length, sizeof(int));
	int Grouped = 0;
    if (Pipes_List.Length > 0) {
		for (int C1 = 0; C1 < Pipes_List.Length; C1++) {
			if (Pipes_List.Data[C1].Filled) {
				Pipe Temporary_Pipe = Pipes_List.Data[C1];
				if (Grouped > 0) {
					bool Uncategorized = true;
					for (int C2 = 0; C2 < Grouped; C2++) {
						if (Temporary_Pipe.X1 == Grouped_List[C2][0].X1 && Temporary_Pipe.Y1 == Grouped_List[
							C2][0].Y1) {
							Grouped_List[C2] = realloc(Grouped_List[C2], sizeof(Pipe) * (C2 + 1));
							Grouped_List[C2][C2] = Temporary_Pipe;
							Sizes[C2] = C2 + 1;
							Uncategorized = false;
							break;
						}
					}
					if (Uncategorized) {
						Grouped_List[Grouped] = malloc(sizeof(Pipe));
						Grouped_List[Grouped][0] = Temporary_Pipe;
						Sizes[Grouped] = 1;
						Grouped++;
					}
				} else {
					Grouped_List[Grouped] = malloc(sizeof(Pipe));
					Grouped_List[Grouped][0] = Temporary_Pipe;
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