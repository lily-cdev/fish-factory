#include <connectables.h>

Pipes Pipes_List = { };

void Push_Pipe(Pipe Input) {
	Pipes_List.Length++;
	if (Pipes_List.Length >= Pipes_List.Full_Size) {
		Pipe* Buffer = malloc(sizeof(Pipe) * Pipes_List.Length);
		memcpy(Buffer, Pipes_List.Data, sizeof(Pipe) * Pipes_List.Length);
		free_c(Pipes_List.Data);
		Pipes_List.Full_Size += 16;
		Pipes_List.Data = malloc(sizeof(Pipe) * Pipes_List.Full_Size);
		memcpy(Pipes_List.Data, Buffer, sizeof(Pipe) * Pipes_List.Length);
		free_c(Buffer);
	}
	Pipes_List.Data[Pipes_List.Length] = Input;
}

void Pull_Pipe(int Position) {
	if (Pipes_List.Length > 0) {
		for (int Counter = 0; Counter < Pipes_List.Length - Position - 1; Counter++) {
			Pipes_List.Data[Position + Counter] = Pipes_List.Data[Position + Counter + 1];
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
	for (int Counter = 0; Counter < Pipes_List.Length; Counter++) {
		if (!Pipes_List.Data[Counter].Filled) {
			Pull_Pipe(Counter);
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
						(Column > 0 && Pipes_List.Data[Pipes_List.Length - 1].X1 == Column - 1)) {
						Is_Adjacent = true;
					} else if ((Row < LDE_GRIDSIZE &&Pipes_List.Data[Pipes_List.Length - 1].Y1 == Row + 1) ||
						(Row > 0 && Pipes_List.Data[Pipes_List.Length - 1].Y1 == Row - 1)) {
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
					if (Is_Pipe_Adjacent && (Data.Connection_Grid[Column][Row] != LDE_INVALID || Data.Plumbing_Grid[Column][
						Row] != LDE_INVALID) && (Data.Settings_Grid[Column][Row][0] == 0 || Data.Settings_Grid[Column][
						Row][0] == 1)) {
						Pipes_List.Data[Pipes_List.Length - 1].X2 = Column;
						Pipes_List.Data[Pipes_List.Length - 1].Y2 = Row;
						Pipes_List.Data[Pipes_List.Length - 1].Filled = true;
						Orient_Pipe(&Pipes_List.Data[Pipes_List.Length - 1]);
						for (int Counter = 0; Counter < Pipes_List.Length - 1; Counter++) {
							int End = Pipes_List.Length - 1;
							if ((Pipes_List.Data[Counter].X1 == Pipes_List.Data[End].X1 && Pipes_List.Data[Counter].Y1 ==
								Pipes_List.Data[End].Y1 && Pipes_List.Data[Counter].X2 == Pipes_List.Data[End].X2 &&
								Pipes_List.Data[Counter].Y2 == Pipes_List.Data[End].Y2) || (Pipes_List.Data[Counter].X1 ==
								Pipes_List.Data[End].X2 && Pipes_List.Data[Counter].Y1 == Pipes_List.Data[End].Y2 &&
								Pipes_List.Data[Counter].X2 == Pipes_List.Data[End].X1 && Pipes_List.Data[Counter].Y2 ==
								Pipes_List.Data[End].Y1)) {
								Pull_Pipe(Counter);
								Pull_Pipe(Pipes_List.Length - 1);
								break;
							}
						}
					} else {
						Pull_Pipe(Pipes_List.Length - 1);
					}
				} else {
					if ((Data.Connection_Grid[Column][Row] != LDE_INVALID || Data.Plumbing_Grid[Column][Row] > LDE_INVALID) &&
						(Data.Settings_Grid[Column][Row][0] == 0 || Data.Settings_Grid[Column][Row][0] == 2)) {
						Pipe New_Pipe;
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
	for (int Counter = 0; Counter < Pipes_List.Length; Counter++) {
		if (Pipes_List.Data[Counter].Filled) {
			Rects.Tile_1x1.x = (int)((Pipes_List.Data[Counter].X1 * LDE_TILESIZE) + Pipes_List.Data[Counter].X_Offset -
				Core.Camera.X) * Settings.Screen_Size;
			Rects.Tile_1x1.y = (int)((Pipes_List.Data[Counter].Y1 * LDE_TILESIZE) + Pipes_List.Data[Counter].Y_Offset -
				Core.Camera.Y) * Settings.Screen_Size;
			Render_Texture(Textures.Arrow.Data[Pipes_List.Data[Counter].Orienation], &Rects.Tile_1x1);
		} else {
			Rects.Sapling.x = (float)((Pipes_List.Data[Counter].X1 * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
			Rects.Sapling.y = (float)((Pipes_List.Data[Counter].Y1 * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
			Render_Texture(Textures.Sapling, &Rects.Sapling);
		}
	}
}

void Distribute_Fluid(Pipe** Grouped_List, int Grouped, int* Sizes) {
	for (int Counter1 = 0; Counter1 < Grouped; Counter1++) {
		float Remaining_Fluid = Data.Data_Grid[Grouped_List[Counter1][0].X1][Grouped_List[Counter1][0].Y1][Stored_Fluids];
		float Used_Fluid = 0;
		for (int Counter2 = 0; Counter2 < Sizes[Counter1]; Counter2++) {
			if (Data.Items_Grid[Grouped_List[Counter1][Counter2].X2][Grouped_List[Counter1][Counter2].Y2] == LDE_INVALID ||
				Data.Items_Grid[Grouped_List[Counter1][Counter2].X1][Grouped_List[Counter1][Counter2].Y1] == Data.Items_Grid[
				Grouped_List[Counter1][Counter2].X2][Grouped_List[Counter1][Counter2].Y2]) {
				float Minimum = min(Remaining_Fluid, Data.Data_Grid[Grouped_List[Counter1][Counter2].X2][Grouped_List[
					Counter1][Counter2].Y2][1] - Data.Data_Grid[Grouped_List[Counter1][Counter2].X2][Grouped_List[Counter1][
					Counter2].Y2][Stored_Fluids]);
				Data.Data_Grid[Grouped_List[Counter1][Counter2].X2][Grouped_List[Counter1][Counter2].Y2][Stored_Fluids] =
					Data.Data_Grid[Grouped_List[Counter1][Counter2].X2][Grouped_List[Counter1][Counter2].Y2][Stored_Fluids] +
					Minimum;
				Update_Item(Grouped_List[Counter1][Counter2].X2, Grouped_List[Counter1][Counter2].Y2, Data.Items_Grid[
					Grouped_List[Counter1][Counter2].X1][Grouped_List[Counter1][Counter2].Y1], Data.Temperature_Grid[
					Grouped_List[Counter1][Counter2].X1][Grouped_List[Counter1][Counter2].Y1]);
				Remaining_Fluid = Remaining_Fluid - Minimum;
				Used_Fluid = Used_Fluid + Minimum;
			}
		}
		Data.Data_Grid[Grouped_List[Counter1][0].X1][Grouped_List[Counter1][0].Y1][Stored_Fluids] = Data.Data_Grid[
			Grouped_List[Counter1][0].X1][Grouped_List[Counter1][0].Y1][Stored_Fluids] - Used_Fluid;
	}
}

void Update_Pipes() {
	Pipe** Grouped_List = calloc(Pipes_List.Length, sizeof(Pipe*));
	int* Sizes = calloc(Pipes_List.Length, sizeof(int));
	int Grouped = 0;
    if (Pipes_List.Length > 0) {
		for (int Counter1 = 0; Counter1 < Pipes_List.Length; Counter1++) {
			if (Pipes_List.Data[Counter1].Filled) {
				Pipe Temporary_Pipe = Pipes_List.Data[Counter1];
				if (Grouped > 0) {
					bool Uncategorized = true;
					for (int Counter2 = 0; Counter2 < Grouped; Counter2++) {
						if (Temporary_Pipe.X1 == Grouped_List[Counter2][0].X1 && Temporary_Pipe.Y1 == Grouped_List[
							Counter2][0].Y1) {
							Grouped_List[Counter2] = realloc(Grouped_List[Counter2], sizeof(Pipe) * (Counter2 + 1));
							Grouped_List[Counter2][Counter2] = Temporary_Pipe;
							Sizes[Counter2] = Counter2 + 1;
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
	for (int Counter = 0; Counter < Grouped; Counter++) {
		free_c(Grouped_List[Counter]);
	}
	free_c(Grouped_List);
	free_c(Sizes);
}