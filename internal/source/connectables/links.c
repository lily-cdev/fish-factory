#include <connectables.h>

Bridges Links = { };

void Orient_Link(Bridge* Input) {
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

void Place_Link() {
	/*for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
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
	}*/
}

void Render_Links() {
	for (int C1 = 0; C1 < Links.Length; C1++) {
		if (Links.Data[C1].Filled) {
            //fix
			/*
			Rects.Tile_1x1.x = (int)((Pipes_List.Data[C1].X1 * LDE_TILESIZE) + Pipes_List.Data[C1].X_Offset -
				Core.Camera.X) * Settings.Screen_Size;
			Rects.Tile_1x1.y = (int)((Pipes_List.Data[C1].Y1 * LDE_TILESIZE) + Pipes_List.Data[C1].Y_Offset -
				Core.Camera.Y) * Settings.Screen_Size;
			Render_Texture(Textures.Arrow.Data[Pipes_List.Data[C1].Orienation], &Rects.Tile_1x1);*/
		} else {
            //fix
			/*
			Rects.Sapling.x = (float)((Pipes_List.Data[C1].X1 * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
			Rects.Sapling.y = (float)((Pipes_List.Data[C1].Y1 * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
			Render_Texture(Textures.Sapling, &Rects.Sapling);*/
		}
	}
}