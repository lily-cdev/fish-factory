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
	for (int Column = 0; Column < ktn_grid_size; Column++) {
		Rects.Tile_1x1.x = ktn_fscale((Column * ktn_tile_size) - Core.Camera.X);
		for (int Row = 0; Row < ktn_grid_size; Row++) {
			Rects.Tile_1x1.y = ktn_fscale((Row * ktn_tile_size) - Core.Camera.Y);
			if (!Detect_Mouse_Collision(Rects.Tile_1x1)) {
				continue;
			}
			int End = Pipes.Length - 1;
			if (Pipes.Length > 0 && !Pipes.Data[End].Filled) {
				bool Is_Adjacent = false;
				if ((Column < ktn_grid_size && Pipes.Data[End].X1 == Column + 1) || (Column >= 0 && Pipes.Data[End].X1 == Column -
					1)) {
					Is_Adjacent = true;
				} else if ((Row < ktn_grid_size && Pipes.Data[End].Y1 == Row + 1) || (Row >= 0 && Pipes.Data[End].Y1 == Row -
					1)) {
					Is_Adjacent = true;
				}
				bool Is_Pipe_Adjacent = false;
				if (Is_Adjacent) {
					if (Data.Plumbing_Grid[Column][Row] == Any) {
						Is_Pipe_Adjacent = true;
					} else if (Data.Plumbing_Grid[Column][Row] == Left && Column > 0 && Pipes.Data[End].X1 == Column - 1) {
						Is_Pipe_Adjacent = true;
					} else if (Data.Plumbing_Grid[Column][Row] == Up && Row > 0 && Pipes.Data[End].Y1 == Row - 1) {
						Is_Pipe_Adjacent = true;
					} else if (Data.Plumbing_Grid[Column][Row] == Right && Column < ktn_grid_size && Pipes.Data[End].X1 ==
						Column + 1) {
						Is_Pipe_Adjacent = true;
					} else if (Data.Plumbing_Grid[Column][Row] == Down && Row < ktn_grid_size && Pipes.Data[End].Y1 == Row + 1) {
						Is_Pipe_Adjacent = true;
					}
				}
				if (Is_Pipe_Adjacent && Data.Plumbing_Grid[Column][Row] != ktn_invalid && (Data.Settings_Grid[Column][Row][0] ==
					F_In || Data.Settings_Grid[Column][Row][0] == F_Either)) {
					Pipes.Data[End].X2 = Column;
					Pipes.Data[End].Y2 = Row;
					Pipes.Data[End].Filled = true;
					Orient_Pipe(&Pipes.Data[End]);
					for (int C1 = 0; C1 < End; C1++) {
						if ((Pipes.Data[C1].X1 == Pipes.Data[End].X1 && Pipes.Data[C1].Y1 == Pipes.Data[End].Y1 && Pipes.Data[
							C1].X2 == Pipes.Data[End].X2 && Pipes.Data[C1].Y2 == Pipes.Data[End].Y2) || (Pipes.Data[C1].X1 ==
							Pipes.Data[End].X2 && Pipes.Data[C1].Y1 == Pipes.Data[End].Y2 && Pipes.Data[C1].X2 == Pipes.Data[
							End].X1 && Pipes.Data[C1].Y2 == Pipes.Data[End].Y1)) {
							Pull_Bridge(&Pipes, C1);
							Pull_Bridge(&Pipes, End);
							break;
						}
					}
				} else {
					Pull_Bridge(&Pipes, End);
				}
			} else {
				if ((Data.Plumbing_Grid[Column][Row] > ktn_invalid) && (Data.Settings_Grid[Column][Row][0] == F_Out ||
					Data.Settings_Grid[Column][Row][0] == F_Either)) {
					Bridge Pipe = { };
					Pipe.X1 = Column;
					Pipe.Y1 = Row;
					Push_Bridge(&Pipes, Pipe);
				}
			}
		}
	}
}

void Render_Pipes() {
	for (int C1 = 0; C1 < Pipes.Length; C1++) {
		if (Pipes.Data[C1].Filled) {
			Rects.Tile_1x1.x = (int)((Pipes.Data[C1].X1 * ktn_tile_size) + Pipes.Data[C1].X_Offset - Core.Camera.X) *
				Settings.Scalar;
			Rects.Tile_1x1.y = (int)((Pipes.Data[C1].Y1 * ktn_tile_size) + Pipes.Data[C1].Y_Offset - Core.Camera.Y) *
				Settings.Scalar;
			Render_Texture(Textures.Arrow.Data[Pipes.Data[C1].Orienation], &Rects.Tile_1x1);
		} else {
			Rects.Sapling.x = ktn_fscale((Pipes.Data[C1].X1 * ktn_tile_size) - Core.Camera.X);
			Rects.Sapling.y = ktn_fscale((Pipes.Data[C1].Y1 * ktn_tile_size) - Core.Camera.Y);
			Render_Texture(Textures.Sapling, &Rects.Sapling);
		}
	}
}

void Update_Pipes() {
	for (int C1 = 0; C1 < Pipes.Length; C1++) {
		Bridge Pipe = Pipes.Data[C1];
		if (!Pipe.Filled) {
			continue;
		}
		float Volume = Data.Data_Grid[Pipe.X1][Pipe.Y1][Stored_Fluids];
		Volume = min(Volume, Data.Data_Grid[Pipe.X2][Pipe.Y2][Fluid_Cap] - Data.Data_Grid[Pipe.X2][Pipe.Y2][Stored_Fluids]);
		Data.Data_Grid[Pipe.X1][Pipe.Y1][Stored_Fluids] -= Volume;
		Data.Data_Grid[Pipe.X2][Pipe.Y2][Stored_Fluids] += Volume;
		Update_Item((Point){ Pipe.X2, Pipe.Y2 }, Data.Items_Grid[Pipe.X1][Pipe.Y1], Data.Temperature_Grid[Pipe.X1][Pipe.Y1]);
	}
}