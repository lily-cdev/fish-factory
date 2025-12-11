#include <Core.h>

#include <Preloader.h>
#include <Items.h>
#include <Connectables.h>
#include <Grid_Handler.h>
#include <Data_Handler.h>

void Clear_Grid(int Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], int Placeholder) {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Grid[Column][Row] = Placeholder;
		}
	}
}

Point Find_Linked(int Identifier, int Parent_X, int Parent_Y) {
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			if (Visual_To_ID(Data_Access.Visual_Grid[X][Y]) == Identifier &&
				Data_Access.Settings_Grid[X][Y][3] == Parent_X &&
				Data_Access.Settings_Grid[X][Y][4] == Parent_Y) {
				return { X, Y };
			}
		}
	}
	return { LDE_INVALID, LDE_INVALID };
}

void Clear_Vector_Grid(std::vector<double> Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], std::vector<double> Placeholder) {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Grid[Column][Row] = Placeholder;
		}
	}
}

int Modular_Detection(int Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], int Plumbing_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE],
	int Behaviour_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], int X, int Y, int Universal_Target, int Local_Target,
	int Grid_Target, bool Is_Pipe) {
	if (Universal_Target == LDE_INVALID) {
		Universal_Target = -2;
	}
	if (Local_Target == LDE_INVALID) {
		Local_Target = -2;
	}
	if (Grid_Target == LDE_INVALID) {
		Grid_Target = -2;
	}
	if ((X > 0 && (Grid[X - 1][Y] == Universal_Target || Grid[X - 1][Y] == Local_Target) ||
		(Plumbing_Grid[X - 1][Y] == 3 && Is_Pipe) || Behaviour_Grid[X - 1][Y] == Grid_Target) &&
		(X < (LDE_GRIDSIZE - 1) && (Grid[X + 1][Y] == Universal_Target || Grid[X + 1][Y] == Local_Target ||
			(Plumbing_Grid[X + 1][Y] == 1 && Is_Pipe) || Behaviour_Grid[X + 1][Y] == Grid_Target)) &&
		(Y > 0 && (Grid[X][Y - 1] == Universal_Target || Grid[X][Y - 1] == Local_Target ||
			(Plumbing_Grid[X][Y - 1] == 4 && Is_Pipe) || Behaviour_Grid[X][Y - 1] == Grid_Target)) &&
		(Y < (LDE_GRIDSIZE - 1) && (Grid[X][Y + 1] == Universal_Target || Grid[X][Y + 1] == Local_Target ||
			(Plumbing_Grid[X][Y + 1] == 2 && Is_Pipe) || Behaviour_Grid[X][Y + 1] == Grid_Target))) {
		return 1;
	} else if ((X < (LDE_GRIDSIZE - 1) && (Grid[X + 1][Y] == Universal_Target || Grid[X + 1][Y] == Local_Target ||
		(Plumbing_Grid[X + 1][Y] == 1 && Is_Pipe) || Behaviour_Grid[X + 1][Y] == Grid_Target)) &&
		(Y > 0 && (Grid[X][Y - 1] == Universal_Target || Grid[X][Y - 1] == Local_Target ||
			(Plumbing_Grid[X][Y - 1] == 4 && Is_Pipe) || Behaviour_Grid[X][Y - 1] == Grid_Target)) &&
		(Y < (LDE_GRIDSIZE - 1) && (Grid[X][Y + 1] == Universal_Target || Grid[X][Y + 1] == Local_Target ||
			(Plumbing_Grid[X][Y + 1] == 2 && Is_Pipe) || Behaviour_Grid[X][Y + 1] == Grid_Target))) {
		return 2;
	} else if ((X > 0 && (Grid[X - 1][Y] == Universal_Target || Grid[X - 1][Y] == Local_Target ||
		(Plumbing_Grid[X - 1][Y] == 3 && Is_Pipe) || Behaviour_Grid[X - 1][Y] == Grid_Target)) &&
		(Y > 0 && (Grid[X][Y - 1] == Universal_Target || Grid[X][Y - 1] == Local_Target ||
			(Plumbing_Grid[X][Y - 1] == 4 && Is_Pipe) || Behaviour_Grid[X][Y - 1] == Grid_Target)) &&
		(Y < (LDE_GRIDSIZE - 1) && (Grid[X][Y + 1] == Universal_Target || Grid[X][Y + 1] == Local_Target ||
			(Plumbing_Grid[X][Y + 1] == 2 && Is_Pipe) || Behaviour_Grid[X][Y + 1] == Grid_Target))) {
		return 3;
	} else if ((X > 0 && (Grid[X - 1][Y] == Universal_Target || Grid[X - 1][Y] == Local_Target ||
		(Plumbing_Grid[X - 1][Y] == 3 && Is_Pipe) || Behaviour_Grid[X - 1][Y] == Grid_Target)) &&
		(X < (LDE_GRIDSIZE - 1) && (Grid[X + 1][Y] == Universal_Target || Grid[X + 1][Y] == Local_Target ||
			(Plumbing_Grid[X + 1][Y] == 1 && Is_Pipe) || Behaviour_Grid[X + 1][Y] == Grid_Target)) &&
		(Y < (LDE_GRIDSIZE - 1) && (Grid[X][Y + 1] == Universal_Target || Grid[X][Y + 1] == Local_Target ||
			(Plumbing_Grid[X][Y + 1] == 2 && Is_Pipe) || Behaviour_Grid[X][Y + 1] == Grid_Target))) {
		return 4;
	} else if ((X > 0 && (Grid[X - 1][Y] == Universal_Target || Grid[X - 1][Y] == Local_Target ||
		(Plumbing_Grid[X - 1][Y] == 3 && Is_Pipe) || Behaviour_Grid[X - 1][Y] == Grid_Target)) &&
		(X < (LDE_GRIDSIZE - 1) && (Grid[X + 1][Y] == Universal_Target || Grid[X + 1][Y] == Local_Target ||
			(Plumbing_Grid[X + 1][Y] == 1 && Is_Pipe) || Behaviour_Grid[X + 1][Y] == Grid_Target)) &&
		(Y > 0 && (Grid[X][Y - 1] == Universal_Target || Grid[X][Y - 1] == Local_Target ||
			(Plumbing_Grid[X][Y - 1] == 4 && Is_Pipe) || Behaviour_Grid[X][Y - 1] == Grid_Target))) {
		return 5;
	} else if ((Y > 0 && (Grid[X][Y - 1] == Universal_Target || Grid[X][Y - 1] == Local_Target ||
		(Plumbing_Grid[X][Y - 1] == 4 && Is_Pipe) || Behaviour_Grid[X][Y - 1] == Grid_Target)) &&
		(Y < (LDE_GRIDSIZE - 1) && (Grid[X][Y + 1] == Universal_Target || Grid[X][Y + 1] == Local_Target ||
			(Plumbing_Grid[X][Y + 1] == 2 && Is_Pipe) || Behaviour_Grid[X][Y + 1] == Grid_Target))) {
		return 6;
	} else if ((X > 0 && (Grid[X - 1][Y] == Universal_Target || Grid[X - 1][Y] == Local_Target ||
		(Plumbing_Grid[X - 1][Y] == 3 && Is_Pipe) || Behaviour_Grid[X - 1][Y] == Grid_Target)) &&
		(X < (LDE_GRIDSIZE - 1) && (Grid[X + 1][Y] == Universal_Target || Grid[X + 1][Y] == Local_Target ||
			(Plumbing_Grid[X + 1][Y] == 1 && Is_Pipe) || Behaviour_Grid[X + 1][Y] == Grid_Target))) {
		return 7;
	} else if ((X < (LDE_GRIDSIZE - 1) && (Grid[X + 1][Y] == Universal_Target || Grid[X + 1][Y] == Local_Target ||
		(Plumbing_Grid[X + 1][Y] == 1 && Is_Pipe) || Behaviour_Grid[X + 1][Y] == Grid_Target)) &&
		(Y < (LDE_GRIDSIZE - 1) && (Grid[X][Y + 1] == Universal_Target || Grid[X][Y + 1] == Local_Target ||
			(Plumbing_Grid[X][Y + 1] == 2 && Is_Pipe) || Behaviour_Grid[X][Y + 1] == Grid_Target))) {
		return 8;
	} else if ((X > 0 && (Grid[X - 1][Y] == Universal_Target || Grid[X - 1][Y] == Local_Target ||
		(Plumbing_Grid[X - 1][Y] == 3 && Is_Pipe) || Behaviour_Grid[X - 1][Y] == Grid_Target)) &&
		(Y < (LDE_GRIDSIZE - 1) && (Grid[X][Y + 1] == Universal_Target || Grid[X][Y + 1] == Local_Target ||
			(Plumbing_Grid[X][Y + 1] == 2 && Is_Pipe) || Behaviour_Grid[X][Y + 1] == Grid_Target))) {
		return 9;
	} else if ((X > 0 && (Grid[X - 1][Y] == Universal_Target || Grid[X - 1][Y] == Local_Target ||
		(Plumbing_Grid[X - 1][Y] == 3 && Is_Pipe) || Behaviour_Grid[X - 1][Y] == Grid_Target)) &&
		(Y > 0 && (Grid[X][Y - 1] == Universal_Target || Grid[X][Y - 1] == Local_Target ||
			(Plumbing_Grid[X][Y - 1] == 4 && Is_Pipe) || Behaviour_Grid[X][Y - 1] == Grid_Target))) {
		return 10;
	} else if ((X < (LDE_GRIDSIZE - 1) && (Grid[X + 1][Y] == Universal_Target || Grid[X + 1][Y] == Local_Target ||
		(Plumbing_Grid[X + 1][Y] == 1 && Is_Pipe) || Behaviour_Grid[X + 1][Y] == Grid_Target)) &&
		(Y > 0 && (Grid[X][Y - 1] == Universal_Target || Grid[X][Y - 1] == Local_Target ||
			(Plumbing_Grid[X][Y - 1] == 4 && Is_Pipe) || Behaviour_Grid[X][Y - 1] == Grid_Target))) {
		return 11;
	} else if (Y < (LDE_GRIDSIZE - 1) && (Grid[X][Y + 1] == Universal_Target || Grid[X][Y + 1] == Local_Target ||
		(Plumbing_Grid[X][Y + 1] == 2 && Is_Pipe) || Behaviour_Grid[X][Y + 1] == Grid_Target)) {
		return 12;
	} else if (X > 0 && (Grid[X - 1][Y] == Universal_Target || Grid[X - 1][Y] == Local_Target ||
		(Plumbing_Grid[X - 1][Y] == 3 && Is_Pipe) || Behaviour_Grid[X - 1][Y] == Grid_Target)) {
		return 13;
	} else if (Y > 0 && (Grid[X][Y - 1] == Universal_Target || Grid[X][Y - 1] == Local_Target ||
		(Plumbing_Grid[X][Y - 1] == 4 && Is_Pipe) || Behaviour_Grid[X][Y - 1] == Grid_Target)) {
		return 14;
	} else if (X < (LDE_GRIDSIZE - 1) && (Grid[X + 1][Y] == Universal_Target || Grid[X + 1][Y] == Local_Target ||
		(Plumbing_Grid[X + 1][Y] == 1 && Is_Pipe) || Behaviour_Grid[X + 1][Y] == Grid_Target)) {
		return 15;
	}
	return 0;
}

int Recursive_Detect(int X, int Y, int Target, int Self, bool Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], bool Self_Accounted,
	int First_Target, int Second_Target);

int Recursive_Detect(int X, int Y, int Target, int Self, bool Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], bool Self_Accounted,
	int First_Target, int Second_Target) {
	bool Progressing = false;
	if (X >= 0 && Y >= 0 && X < LDE_GRIDSIZE && Y < LDE_GRIDSIZE && !Grid[X][Y]) {
		if (Visual_To_ID(Data_Access.Visual_Grid[X][Y]) == Target) {
			Progressing = true;
		} else if (Visual_To_ID(Data_Access.Visual_Grid[X][Y]) == Self) {
			if (Self_Accounted) {
				return -LDE_INFINITY;
			} else {
				Self_Accounted = true;
				Progressing = true;
			}
		} else if (Visual_To_ID(Data_Access.Visual_Grid[X][Y]) == First_Target) {
			Temporary_Access.First_Modular_Requirement++;
			Data_Access.Settings_Grid[X][Y][3] = Temporary_Access.First_Coordinate[0];
			Data_Access.Settings_Grid[X][Y][4] = Temporary_Access.First_Coordinate[1];
			Progressing = true;
		} else if (Visual_To_ID(Data_Access.Visual_Grid[X][Y]) == Second_Target) {
			Temporary_Access.Second_Modular_Requirement++;
			Data_Access.Settings_Grid[X][Y][3] = Temporary_Access.First_Coordinate[0];
			Data_Access.Settings_Grid[X][Y][4] = Temporary_Access.First_Coordinate[1];
			Progressing = true;
		}
	}
	if (Progressing) {
		Grid[X][Y] = true;
		return 1 + Recursive_Detect(X + 1, Y, Target, Self, Grid, Self_Accounted, First_Target, Second_Target) +
			Recursive_Detect(X - 1, Y, Target, Self, Grid, Self_Accounted, First_Target, Second_Target) +
			Recursive_Detect(X, Y + 1, Target, Self, Grid, Self_Accounted, First_Target, Second_Target) +
			Recursive_Detect(X, Y - 1, Target, Self, Grid, Self_Accounted, First_Target, Second_Target);
	}
	return 0;
}

int Find_Modular_Size(int X, int Y, int Target, int Self, int First_Target, int Second_Target) {
	bool Self_Accounted = false;
	bool Checked_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	for (int X2 = 0; X2 < LDE_GRIDSIZE; X2++) {
		for (int Y2 = 0; Y2 < LDE_GRIDSIZE; Y2++) {
			Checked_Grid[X2][Y2] = false;
		}
	}
	return Recursive_Detect(X, Y, Target, Self, Checked_Grid, Self_Accounted, First_Target, Second_Target);
}

void Update_Grid() {
	int Temporary_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE];
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Temporary_Grid[Column][Row] = Data_Access.Visual_Grid[Column][Row];
		}
	}
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			if (Visual_To_ID(Data_Access.Visual_Grid[Column][Row]) == Reinforced_Pipe) {
				Temporary_Grid[Column][Row] = 1 + Modular_Detection(
					Data_Access.Connection_Grid, Data_Access.Plumbing_Grid,
					Data_Access.Behaviour_Grid, Column, Row, 0, 1, LDE_INVALID, true);
			} else if (Data_Access.Visual_Grid[Column][Row] > 23 && Data_Access.Visual_Grid[Column][Row] < 41) {
				Temporary_Grid[Column][Row] = 24 + Modular_Detection(
					Data_Access.Connection_Grid, Data_Access.Plumbing_Grid,
					Data_Access.Behaviour_Grid, Column, Row, LDE_INVALID, LDE_INVALID, 0, false);
			} else if (Data_Access.Visual_Grid[Column][Row] == 45) {
				Temporary_Access.First_Coordinate = { Column, Row };
				Data_Access.Settings_Grid[Column][Row][3] = Find_Modular_Size(Column, Row, 8, 13, 14, 15);
				if (Data_Access.Settings_Grid[Column][Row][3] < 0) {
					Data_Access.Settings_Grid[Column][Row][3] = -2;
				}
				if (Temporary_Access.First_Modular_Requirement < 1) {
					Data_Access.Settings_Grid[Column][Row][3] = -3;
				} else if (Temporary_Access.First_Modular_Requirement > 1) {
					Data_Access.Settings_Grid[Column][Row][3] = -4;
				}
				if (Temporary_Access.Second_Modular_Requirement < 1) {
					Data_Access.Settings_Grid[Column][Row][3] = -5;
				} else if (Temporary_Access.Second_Modular_Requirement > 1) {
					Data_Access.Settings_Grid[Column][Row][3] = -6;
				}
				Temporary_Access.First_Modular_Requirement = 0;
				Temporary_Access.Second_Modular_Requirement = 0;
			} else if (Visual_To_ID(Data_Access.Visual_Grid[Column][Row]) == Large_Pipe) {
				Temporary_Grid[Column][Row] = Modular_Detection(
					Data_Access.Connection_Grid, Data_Access.Plumbing_Grid,
					Data_Access.Behaviour_Grid, Column, Row, 0, 1, LDE_INVALID, true) + 71;
			}
		}
	}
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Data_Access.Visual_Grid[Column][Row] = Temporary_Grid[Column][Row];
		}
	}
}

void Build_Grid(int Item) {
	std::vector<Point> Nodes;
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rectangles_Access.Tile_1x1.x = static_cast<int>(((Column * 40) -
			UI_Access.Camera_X) * Settings_Access.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rectangles_Access.Tile_1x1.y = static_cast<int>(((Row * 40) -
				UI_Access.Camera_Y) * Settings_Access.Screen_Size);
			if (Detect_Mouse_Collision(Rectangles_Access.Tile_1x1)) {
				if (Data_Access.Visual_Grid[Column][Row] == 0) {
					bool Placed = false;
					int Queried_Price = UI_Access.Queried_Price;
					switch (Item - 1) {
					case Reinforced_Pipe:
						Data_Access.Visual_Grid[Column][Row] = 1;
						Data_Access.Connection_Grid[Column][Row] = 1;
						Data_Access.Data_Grid[Column][Row][Fluid_Cap] = LDE_REINFORCEDCAP;
						Data_Access.Settings_Grid[Column][Row][0] = 0;
						Data_Access.Plumbing_Grid[Column][Row] = 0;
						break;
					case Ram_Pump:
						Data_Access.Visual_Grid[Column][Row] = 17;
						Data_Access.Connection_Grid[Column][Row] = 0;
						Data_Access.Wiring_Grid[Column][Row] = 0;
						Data_Access.Data_Grid[Column][Row][Fluid_Cap] = 3;
						Data_Access.Data_Grid[Column][Row][Power_Cap] = 10;
						Data_Access.Data_Grid[Column][Row][5] = 20;
						Data_Access.Data_Grid[Column][Row][6] = 20;
						Data_Access.Plumbing_Grid[Column][Row] = 0;
						Data_Access.Settings_Grid[Column][Row][0] = 2;
						break;
					case Incinerator:
						if (UI_Access.Placing_Rotation == 0) {
							Data_Access.Visual_Grid[Column][Row] = 18;
						} else {
							Data_Access.Visual_Grid[Column][Row] =
								UI_Access.Placing_Rotation + 113;
						}
						Data_Access.Connection_Grid[Column][Row] = 0;
						Data_Access.Data_Grid[Column][Row][Fluid_Cap] = 12;
						Data_Access.Plumbing_Grid[Column][Row] = 0;
						Data_Access.Settings_Grid[Column][Row][0] = 1;
						Data_Access.Animation_Grid[Column][Row][0] = 0;
						break;
					case Piezo_Generator:
						Data_Access.Visual_Grid[Column][Row] = 19;
						Data_Access.Data_Grid[Column][Row][Power_Cap] = 5;
						Data_Access.Data_Grid[Column][Row][5] = 20;
						Data_Access.Data_Grid[Column][Row][6] = 20;
						Data_Access.Wiring_Grid[Column][Row] = 1;
						break;
					case Decoration:
						Data_Access.Visual_Grid[Column][Row] = 20;
						break;
					case Submarine_Dock:
						if (Check_Clearance(Column, Row, 6, 4) && Row == 0) {
							Fill_Clearance(LDE_INVALID, Column, Row, 6, 4);
							Data_Access.Visual_Grid[Column][Row] = 21;
							Data_Access.Plumbing_Grid[Column][Row + 3] = Down;
							Data_Access.Plumbing_Grid[Column + 1][Row + 3] = Down;
							Data_Access.Settings_Grid[Column][Row + 3][0] = 1;
							Data_Access.Settings_Grid[Column + 1][Row + 3][0] = 1;
							Data_Access.Data_Grid[Column][Row + 3][Fluid_Cap] = 200;
							Data_Access.Data_Grid[Column + 1][Row + 3][Fluid_Cap] = 200;
							Data_Access.Settings_Grid[Column][Row][3] = 0;
							Data_Access.Settings_Grid[Column][Row][4] = 0;
							Data_Access.Settings_Grid[Column][Row][5] = LDE_INVALID;
							Data_Access.Settings_Grid[Column][Row][6] = LDE_INVALID;
							Temporary_Access.Docks.push_back({ Column, Row });
							Recache_TT_Commands();
						} else {
							Queried_Price = 0;
						}
						break;
					case Filtration_Plant:
						if (Check_Clearance(Column, Row, 2, 3)) {
							Fill_Clearance(LDE_INVALID, Column, Row, 2, 3);
							Data_Access.Visual_Grid[Column][Row] = 22;
							Data_Access.Plumbing_Grid[Column][Row + 1] = Left;
							Data_Access.Plumbing_Grid[Column + 1][Row] = Right;
							Data_Access.Plumbing_Grid[Column + 1][Row + 1] = Right;
							Data_Access.Plumbing_Grid[Column + 1][Row + 2] = Right;
							Data_Access.Wiring_Grid[Column][Row] = 0;
							Data_Access.Data_Grid[Column][Row][Power_Cap] = 95;
							Data_Access.Data_Grid[Column][Row][4] = 5;
							Data_Access.Data_Grid[Column][Row][5] = 12;
							Data_Access.Data_Grid[Column][Row][6] = 100;
							Data_Access.Data_Grid[Column][Row + 1][Fluid_Cap] = 16;
							Data_Access.Data_Grid[Column + 1][Row][Fluid_Cap] = 12;
							for (int Counter = 1; Counter < 3; Counter++) {
								Data_Access.Data_Grid[Column + 1][Row + Counter][Fluid_Cap] = 4;
								Data_Access.Settings_Grid[Column + 1][Row + Counter][0] = 2;
							}
							Data_Access.Settings_Grid[Column][Row + 1][0] = 1;
							Data_Access.Settings_Grid[Column + 1][Row][0] = 2;
						} else {
							Queried_Price = 0;
						}
						break;
					case Bio_Generator:
						if (Check_Clearance(Column, Row, 3, 3)) {
							Fill_Clearance(LDE_INVALID, Column, Row, 3, 3);
							if (UI_Access.Placing_Rotation == 0) {
								Data_Access.Visual_Grid[Column][Row] = 23;
							} else {
								Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 101;
							}
							Data_Access.Animation_Grid[Column][Row][1] = 45;
							Data_Access.Wiring_Grid[Column][Row] = 1;
							Data_Access.Data_Grid[Column][Row][Power_Cap] = 9500;
							Data_Access.Data_Grid[Column][Row][5] = 60;
							Data_Access.Data_Grid[Column][Row][6] = 60;
							Nodes = Return_Nodes(Column, Row, UI_Access.Placing_Rotation,
								Preconfigurations_Access.BG_Inputs);
							Data_Access.Data_Grid[Nodes[0].X][Nodes[0].Y][1] = 4;
							Data_Access.Settings_Grid[Nodes[0].X][Nodes[0].Y][0] = 1;
							{
								int Orientation = UI_Access.Placing_Rotation + Down;
								Orientation = ((Orientation + 3) & 3) + 1;
								Data_Access.Plumbing_Grid[Nodes[0].X][Nodes[0].Y] = Orientation;
							}
						} else {
							Queried_Price = 0;
						}
						break;
					case Spawning_Pool:
						Data_Access.Visual_Grid[Column][Row] = 24;
						Data_Access.Behaviour_Grid[Column][Row] = 0;
						break;
					case Distillery:
						if (Check_Clearance(Column, Row, 2, 2)) {
							Fill_Clearance(LDE_INVALID, Column, Row, 2, 2);
							if (UI_Access.Placing_Rotation == 0) {
								Data_Access.Visual_Grid[Column][Row] = 41;
							} else {
								Data_Access.Visual_Grid[Column][Row] =
									UI_Access.Placing_Rotation + 116;
							}
							Data_Access.Data_Grid[Column][Row][5] = 24;
							Data_Access.Data_Grid[Column][Row][6] = 56;
							if (UI_Access.Placing_Rotation == 2 || UI_Access.Placing_Rotation == 3) {
								Data_Access.Data_Grid[Column][Row][5] = 56;
							}
							if (UI_Access.Placing_Rotation == 1 || UI_Access.Placing_Rotation == 2) {
								Data_Access.Data_Grid[Column][Row][6] = 24;
							}
							Data_Access.Wiring_Grid[Column][Row] = 0;
							Data_Access.Data_Grid[Column][Row][Power_Cap] = 2500;
							Data_Access.Animation_Grid[Column][Row][0] = 0;
							Nodes = Return_Nodes(Column, Row, UI_Access.Placing_Rotation,
								Preconfigurations_Access.D_Inputs);
							for (int Counter = 0; Counter < Nodes.size(); Counter++) {
								Data_Access.Settings_Grid[Nodes[Counter].X][Nodes[Counter].Y][0] = 1;
								Data_Access.Data_Grid[Nodes[Counter].X][Nodes[Counter].Y][Fluid_Cap] = 6;
								Data_Access.Plumbing_Grid[Nodes[Counter].X][Nodes[Counter].Y] =
									UI_Access.Placing_Rotation + Left;
							}
							Nodes = Return_Nodes(Column, Row, UI_Access.Placing_Rotation,
								Preconfigurations_Access.D_Outputs);
							for (int Counter = 0; Counter < Nodes.size(); Counter++) {
								Data_Access.Settings_Grid[Nodes[Counter].X][Nodes[Counter].Y][0] = 2;
								Data_Access.Data_Grid[Nodes[Counter].X][Nodes[Counter].Y][Fluid_Cap] = 4;
								Data_Access.Plumbing_Grid[Nodes[Counter].X][Nodes[Counter].Y] =
									(UI_Access.Placing_Rotation + Right == 4) ? 4 :
									((UI_Access.Placing_Rotation + Right) & 3);
							}
						} else {
							Queried_Price = 0;
						}
						break;
					case Algae_Bed:
						Placed = false;
						if (evn_i(UI_Access.Placing_Rotation)) {
							if (Check_Clearance(Column, Row, 2, 3)) {
								Fill_Clearance(LDE_INVALID, Column, Row, 2, 3);
								Placed = true;
								Data_Access.Data_Grid[Column][Row][5] = 52;
								Data_Access.Data_Grid[Column][Row][6] = 32;
								if (UI_Access.Placing_Rotation == 0) {
									Data_Access.Data_Grid[Column][Row][5] = 28;
									Data_Access.Data_Grid[Column][Row][6] = 88;
								}
							}
						} else {
							if (Check_Clearance(Column, Row, 3, 2)) {
								Fill_Clearance(LDE_INVALID, Column, Row, 3, 2);
								Placed = true;
								Data_Access.Data_Grid[Column][Row][5] = 88;
								Data_Access.Data_Grid[Column][Row][6] = 52;
								if (UI_Access.Placing_Rotation == 1) {
									Data_Access.Data_Grid[Column][Row][5] = 32;
									Data_Access.Data_Grid[Column][Row][6] = 28;
								}
							}
						}
						if (Placed) {
							std::vector<Point> Nodes = Return_Nodes(Column, Row,
								UI_Access.Placing_Rotation, Preconfigurations_Access.GB_Outputs);
							for (int Counter = 0; Counter < Nodes.size(); Counter++) {
								Data_Access.Settings_Grid[Nodes[Counter].X][Nodes[Counter].Y][0] = 2;
								Data_Access.Data_Grid[Nodes[Counter].X][Nodes[Counter].Y][Fluid_Cap] = 3;
								Data_Access.Plumbing_Grid[Nodes[Counter].X][Nodes[Counter].Y] =
									(UI_Access.Placing_Rotation + Down == 4) ? 4 :
									((UI_Access.Placing_Rotation + Down) & 3);
							}
							if (UI_Access.Placing_Rotation == 0) {
								Data_Access.Visual_Grid[Column][Row] = 42;
							} else {
								Data_Access.Visual_Grid[Column][Row] =
									UI_Access.Placing_Rotation + 131;
							}
							Data_Access.Wiring_Grid[Column][Row] = 0;
							Data_Access.Data_Grid[Column][Row][Power_Cap] = 200;
						} else {
							Queried_Price = 0;
						}
						break;
					case Command_Platform:
						Placed = false;
						if (!Data_Access.CMD_Placed) {
							switch (UI_Access.Placing_Rotation) {
							case 0:
								if (Check_Clearance(Column, Row, 8, 6)) {
									Fill_Clearance(LDE_INVALID, Column, Row, 8, 6);
									Data_Access.Visual_Grid[Column][Row] = 43;
									Placed = true;
								}
								break;
							case 1:
								if (Check_Clearance(Column, Row, 6, 8)) {
									Fill_Clearance(LDE_INVALID, Column, Row, 6, 8);
									Data_Access.Visual_Grid[Column][Row] = 56;
									Placed = true;
								}
								break;
							case 2:
								if (Check_Clearance(Column, Row, 8, 6)) {
									Fill_Clearance(LDE_INVALID, Column, Row, 8, 6);
									Data_Access.Visual_Grid[Column][Row] = 57;
									Placed = true;
								}
								break;
							case 3:
								if (Check_Clearance(Column, Row, 6, 8)) {
									Fill_Clearance(LDE_INVALID, Column, Row, 6, 8);
									Data_Access.Visual_Grid[Column][Row] = 58;
									Placed = true;
								}
								break;
							default:
								break;
							}
						}
						if (Placed) {
							Data_Access.CMD_Placed = true;
						} else {
							Queried_Price = 0;
						}
						break;
					case Basic_Scrubber:
						if (Check_Clearance(Column, Row, 2, 2)) {
							Fill_Clearance(LDE_INVALID, Column, Row, 2, 2);
							if (UI_Access.Placing_Rotation == 0) {
								Data_Access.Visual_Grid[Column][Row] = 44;
							} else {
								Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 63;
							}
						} else {
							Queried_Price = 0;
						}
						break;
					case Spawning_Controller:
						Data_Access.Visual_Grid[Column][Row] = 45;
						Data_Access.Settings_Grid[Column][Row][4] = 0;
						Data_Access.Settings_Grid[Column][Row][5] = 0;
						Data_Access.Settings_Grid[Column][Row][6] = 0;
						Data_Access.Settings_Grid[Column][Row][7] = 0;
						Data_Access.Behaviour_Grid[Column][Row] = 0;
						break;
					case Spawning_Output:
						Data_Access.Visual_Grid[Column][Row] = 46;
						Data_Access.Data_Grid[Column][Row][Fluid_Cap] = 50;
						Data_Access.Plumbing_Grid[Column][Row] = Down;
						Data_Access.Behaviour_Grid[Column][Row] = 0;
						Data_Access.Settings_Grid[Column][Row][0] = 2;
						break;
					case Spawning_Input:
						Data_Access.Visual_Grid[Column][Row] = 47;
						Data_Access.Data_Grid[Column][Row][Fluid_Cap] = 12;
						Data_Access.Plumbing_Grid[Column][Row] = Down;
						Data_Access.Behaviour_Grid[Column][Row] = 0;
						Data_Access.Settings_Grid[Column][Row][0] = 1;
						break;
					case Electrolytic_Cell:
						Placed = false;
						if (evn_i(UI_Access.Placing_Rotation)) {
							if (Check_Clearance(Column, Row, 3, 2)) {
								Fill_Clearance(LDE_INVALID, Column, Row, 3, 2);
								for (int Counter = 0; Counter < 3; Counter++) {
									Data_Access.Data_Grid[Column + Counter][static_cast<int>(
										UI_Access.Placing_Rotation * 0.5) + Row][Fluid_Cap] = 20;
									Data_Access.Plumbing_Grid[Column + Counter][static_cast<int>(
										UI_Access.Placing_Rotation * 0.5) + Row] = UI_Access.Placing_Rotation + Up;
									Data_Access.Settings_Grid[Column + Counter][static_cast<int>(
										UI_Access.Placing_Rotation * 0.5) + Row][0] = 2;
								}
								Data_Access.Data_Grid[Column + 1][Row - static_cast<int>
									(UI_Access.Placing_Rotation * 0.5) + 1][Fluid_Cap] = 16;
								Data_Access.Plumbing_Grid[Column + 1][Row - static_cast<int>
									(UI_Access.Placing_Rotation * 0.5) + 1] = Down - UI_Access.Placing_Rotation;
								Data_Access.Settings_Grid[Column + 1][Row - static_cast<int>
									(UI_Access.Placing_Rotation * 0.5) + 1][0] = 1;
								if (UI_Access.Placing_Rotation == 0) {
									Data_Access.Data_Grid[Column][Row][5] = 44;
									Data_Access.Data_Grid[Column][Row][6] = 67;
								} else {
									Data_Access.Data_Grid[Column][Row][5] = 76;
									Data_Access.Data_Grid[Column][Row][6] = 13;
								}
								Placed = true;
							}
						} else {
							if (Check_Clearance(Column, Row, 2, 3)) {
								Fill_Clearance(LDE_INVALID, Column, Row, 2, 3);
								for (int Counter = 0; Counter < 3; Counter++) {
									Data_Access.Data_Grid[Column - static_cast<int>(
										(UI_Access.Placing_Rotation - 1) * 0.5) +
										1][Row + Counter][Fluid_Cap] = 20;
									Data_Access.Plumbing_Grid[Column - static_cast<int>(
										(UI_Access.Placing_Rotation - 1) * 0.5) + 1][Row +
										Counter] = Right - (UI_Access.Placing_Rotation - 1);
									Data_Access.Settings_Grid[Column - static_cast<int>(
										(UI_Access.Placing_Rotation - 1) * 0.5) + 1][Row + Counter][0] = 2;
								}
								Data_Access.Data_Grid[Column + static_cast<int>((UI_Access
									.Placing_Rotation - 1) * 0.5)][Row + 1][Fluid_Cap] = 16;
								Data_Access.Plumbing_Grid[Column + static_cast<int>((UI_Access.Placing_Rotation -
									1) * 0.5)][Row + 1] = (UI_Access.Placing_Rotation - 1) + Left;
								Data_Access.Settings_Grid[Column + static_cast<int>((UI_Access.Placing_Rotation -
									1) * 0.5)][Row + 1][0] = 1;
								if (UI_Access.Placing_Rotation == 1) {
									Data_Access.Data_Grid[Column][Row][5] = 13;
									Data_Access.Data_Grid[Column][Row][6] = 44;
								} else {
									Data_Access.Data_Grid[Column][Row][5] = 67;
									Data_Access.Data_Grid[Column][Row][6] = 76;
								}
								Placed = true;
							}							
						}
						if (Placed) {
							Data_Access.Data_Grid[Column][Row][Power_Cap] = 70000;
							Data_Access.Wiring_Grid[Column][Row] = 0;
							if (UI_Access.Placing_Rotation == 0) {
								Data_Access.Visual_Grid[Column][Row] = 48;
							} else {
								Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 95;
							}
						} else {
							Queried_Price = 0;
						}
						break;
					case Fluid_Mixer:
						if (Check_Clearance(Column, Row, 3, 3)) {
							Fill_Clearance(LDE_INVALID, Column, Row, 3, 3);
							Nodes = Return_Nodes(Column, Row, UI_Access.Placing_Rotation,
								Preconfigurations_Access.FM_Inputs);
							for (int Counter = 0; Counter < Nodes.size(); Counter++) {
								int Orientation = static_cast<int>(std::floor(Counter / 3.0f) * 2) + Left;
								Orientation -= UI_Access.Placing_Rotation;
								Orientation = ((Orientation + 3) & 3) + 1;
								Data_Access.Data_Grid[Nodes[Counter].X][Nodes[Counter].Y][Fluid_Cap] = 24;
								Data_Access.Settings_Grid[Nodes[Counter].X][Nodes[Counter].Y][0] = 1;
								Data_Access.Plumbing_Grid[Nodes[Counter].X][Nodes[Counter].Y] = Orientation;
							}
							Nodes = Return_Nodes(Column, Row, UI_Access.Placing_Rotation,
								Preconfigurations_Access.FM_Outputs);
							for (int Counter = 0; Counter < Nodes.size(); Counter++) {
								int Orientation = (Counter * 2) + Up;
								Orientation -= UI_Access.Placing_Rotation;
								Orientation = ((Orientation + 3) & 3) + 1;
								Data_Access.Data_Grid[Nodes[Counter].X][Nodes[Counter].Y][Fluid_Cap] = 36;
								Data_Access.Settings_Grid[Nodes[Counter].X][Nodes[Counter].Y][0] = 2;
								Data_Access.Plumbing_Grid[Nodes[Counter].X][Nodes[Counter].Y] = Orientation;
							}
							if (UI_Access.Placing_Rotation == 0) {
								Data_Access.Visual_Grid[Column][Row] = 49;
							} else {
								Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 98;
							}
							Data_Access.Animation_Grid[Column][Row][1] = 0;
							Data_Access.Data_Grid[Column][Row][Power_Cap] = 800;
							Data_Access.Wiring_Grid[Column][Row] = 0;
							Data_Access.Data_Grid[Column][Row][5] = 60;
							Data_Access.Data_Grid[Column][Row][6] = 60;
						} else {
							Queried_Price = 0;
						}
						break;
					case Signal_Tower:
						if (Check_Clearance(Column, Row, 3, 3)) {
							Fill_Clearance(LDE_INVALID, Column, Row, 3, 3);
							if (UI_Access.Placing_Rotation == 0) {
								Data_Access.Visual_Grid[Column][Row] = 50;
							} else {
								Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 59;
							}
							Data_Access.Settings_Grid[Column][Row][3] = 0;
						} else {
							Queried_Price = 0;
						}
						break;
					case Flowerpot:
						Data_Access.Visual_Grid[Column][Row] = 51;
						break;
					case Ammunition_Shelf:
						Placed = false;
						if (evn_i(UI_Access.Placing_Rotation)) {
							if (Check_Clearance(Column, Row, 2, 1)) {
								Fill_Clearance(LDE_INVALID, Column, Row, 2, 1);
								Placed = true;
							}
						} else {
							if (Check_Clearance(Column, Row, 1, 2)) {
								Fill_Clearance(LDE_INVALID, Column, Row, 1, 2);
								Placed = true;
							}
						}
						if (Placed) {
							Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 52;
						} else {
							Queried_Price = 0;
						}
						break;
					case Cable_Node:
						Data_Access.Visual_Grid[Column][Row] = 63;
						Data_Access.Wiring_Grid[Column][Row] = 2;
						Data_Access.Data_Grid[Column][Row][Power_Cap] = 12000;
						Data_Access.Data_Grid[Column][Row][5] = 20;
						Data_Access.Data_Grid[Column][Row][6] = 20;
						break;
					case Geo_Well:
						Placed = false;
						if (evn_i(UI_Access.Placing_Rotation)) {
							if (Check_Clearance(Column, Row, 2, 3)) {
								Fill_Clearance(LDE_INVALID, Column, Row, 2, 3);
								Placed = true;
								Data_Access.Data_Grid[Column][Row][6] = 60;
								for (int Counter = 0; Counter < 2; Counter++) {
									if (UI_Access.Placing_Rotation == Counter * 2) {
										Data_Access.Data_Grid[Column + Counter][Row][Fluid_Cap] = 10;
										Data_Access.Data_Grid[Column + Counter][Row + 2][Fluid_Cap] = 10;
										Data_Access.Settings_Grid[Column + Counter][Row][0] = 2 - Counter;
										Data_Access.Settings_Grid[Column + Counter][Row + 2][0] = Counter + 1;
										Data_Access.Plumbing_Grid[Column + Counter][Row] = Up;
										Data_Access.Plumbing_Grid[Column + Counter][Row + 2] = Down;
										Data_Access.Data_Grid[Column][Row][5] = std::abs((Counter * 80) - 28);
									}
								}
							}
						} else {
							if (Check_Clearance(Column, Row, 3, 2)) {
								Fill_Clearance(LDE_INVALID, Column, Row, 3, 2);
								Placed = true;
								Data_Access.Data_Grid[Column][Row][5] = 60;
								for (int Counter = 0; Counter < 2; Counter++) {
									if (UI_Access.Placing_Rotation == (Counter * 2) + 1) {
										Data_Access.Data_Grid[Column][Row + Counter][Fluid_Cap] = 10;
										Data_Access.Data_Grid[Column + 2][Row + Counter][Fluid_Cap] = 10;
										Data_Access.Settings_Grid[Column][Row + Counter][0] = 2 - Counter;
										Data_Access.Settings_Grid[Column + 2][Row + Counter][0] = Counter + 1;
										Data_Access.Plumbing_Grid[Column][Row + Counter] = Left;
										Data_Access.Plumbing_Grid[Column + 2][Row + Counter] = Right;
										Data_Access.Data_Grid[Column][Row][6] = std::abs((Counter * 80) - 28);
									}
								}
							}
						}
						if (Placed) {
							Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 67;
							Data_Access.Data_Grid[Column][Row][Power_Cap] = 3000;
							Data_Access.Wiring_Grid[Column][Row] = 0;
						} else {
							Queried_Price = 0;
						}
						break;
					case Large_Pipe:
						Data_Access.Visual_Grid[Column][Row] = 71;
						Data_Access.Connection_Grid[Column][Row] = 1;
						Data_Access.Data_Grid[Column][Row][Fluid_Cap] = LDE_LARGECAP;
						Data_Access.Settings_Grid[Column][Row][0] = 0;
						Data_Access.Plumbing_Grid[Column][Row] = 0;
						break;
					case Heat_Exchanger:
						Placed = false;
						if (evn_i(UI_Access.Placing_Rotation)) {
							if (Check_Clearance(Column, Row, 4, 3)) {
								Fill_Clearance(LDE_INVALID, Column, Row, 4, 3);
								Placed = true;
								for (int Counter1 = 0; Counter1 < 2; Counter1++) {
									for (int Counter2 = 0; Counter2 < 2; Counter2++) {
										Data_Access.Plumbing_Grid[Column + (Counter2 * 3)]
											[Row + (Counter1 * 2)] = Up + (Counter1 * 2);
										Data_Access.Data_Grid[Column + (Counter2 * 3)]
											[Row + (Counter1 * 2)][Fluid_Cap] = 300;
										Data_Access.Settings_Grid[Column + (Counter2 * 3)]
											[Row][0] = 2 - (UI_Access.Placing_Rotation * 0.5);
										Data_Access.Settings_Grid[Column + (Counter2 * 3)]
											[Row + 2][0] = 1 + (UI_Access.Placing_Rotation * 0.5);
										
									}
								}
							}
						} else {
							if (Check_Clearance(Column, Row, 3, 4)) {
								Fill_Clearance(LDE_INVALID, Column, Row, 3, 4);
								Placed = true;
								for (int Counter1 = 0; Counter1 < 2; Counter1++) {
									for (int Counter2 = 0; Counter2 < 2; Counter2++) {
										Data_Access.Plumbing_Grid[Column + (Counter1 * 2)][
											Row + (Counter2 * 3)] = (Counter1 * 2) + Left;
										Data_Access.Data_Grid[(Counter1 * 2) + Column][
											Row + (Counter2 * 3)][Fluid_Cap] = 300;
										Data_Access.Settings_Grid[Column][(Counter2 * 3) +
											Row][0] = (UI_Access.Placing_Rotation * 0.5) + 1;
										Data_Access.Settings_Grid[Column + 2][(Counter2 * 3) +
											Row][0] = 2 - (UI_Access.Placing_Rotation * 0.5);
									}
								}
							}
						}
						if (Placed) {
							Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 87;
							for (int Counter = 0; Counter < 4; Counter++) {
								Data_Access.Settings_Grid[Column][Row][Counter + 3] = 0;
							}
							for (int Counter = 0; Counter < 2; Counter++) {
								Data_Access.Settings_Grid[Column][Row][Counter + 7] = LDE_ROOMTEMP;
							}
							for (int Counter = 0; Counter < 2; Counter++) {
								Data_Access.Settings_Grid[Column][Row][Counter + 9] = LDE_INVALID;
							}
						} else {
							Queried_Price = 0;
						}
						break;
					case Petrified_Wood:
						Data_Access.Visual_Grid[Column][Row] = 91;
						break;
					case Basalt_Tile:
						Data_Access.Visual_Grid[Column][Row] = 92;
						break;
					case Silicone_Carpet:
						Data_Access.Visual_Grid[Column][Row] = 93;
						break;
					case Money_Generator:
						Data_Access.Visual_Grid[Column][Row] = 94;
						Data_Access.Settings_Grid[Column][Row][3] = 5;
						Data_Access.Settings_Grid[Column][Row][4] = 0;
						break;
					case Fluid_Generator:
						Data_Access.Visual_Grid[Column][Row] = 95;
						Data_Access.Settings_Grid[Column][Row][0] = 2;
						Data_Access.Settings_Grid[Column][Row][3] = 0;
						Data_Access.Settings_Grid[Column][Row][4] = LDE_ROOMTEMP;
						Data_Access.Settings_Grid[Column][Row][5] = 0;
						Data_Access.Plumbing_Grid[Column][Row] = 0;
						Data_Access.Data_Grid[Column][Row][Fluid_Cap] = 900;
						break;
					case R_Intersection:
					case L_Intersection:
						if (Check_Clearance(Column, Row, 3, 3)) {
							Fill_Clearance(LDE_INVALID, Column, Row, 3, 3);
							if (Item - 1 == R_Intersection) {
								Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 105;
							} else {
								Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 109;
							}
							std::vector<Point> Nodes = Return_Nodes(Column, Row,
								0, Preconfigurations_Access.I_Inputs);
							for (int Counter = 0; Counter < 2; Counter++) {
								Nodes.push_back(Return_Nodes(Column, Row, 0,
									Preconfigurations_Access.I_Outputs)[Counter]);
							}
							for (int Counter = 0; Counter < 4; Counter++) {
								Data_Access.Plumbing_Grid[Nodes[Counter].X][
									Nodes[Counter].Y] = Counter + 1;
							}
							Nodes = Return_Nodes(Column, Row, UI_Access.Placing_Rotation,
								Preconfigurations_Access.I_Inputs);
							for (int Counter1 = 0; Counter1 < 2; Counter1++) {
								if (Counter1 == 1) {
									Nodes = Return_Nodes(Column, Row, UI_Access.Placing_Rotation,
										Preconfigurations_Access.I_Outputs);
								}
								for (int Counter2 = 0; Counter2 < 2; Counter2++) {
									if (Item - 1 == R_Intersection) {
										Data_Access.Data_Grid[Nodes[Counter2].X][
											Nodes[Counter2].Y][Fluid_Cap] = LDE_REINFORCEDCAP;
									} else {
										Data_Access.Data_Grid[Nodes[Counter2].X][
											Nodes[Counter2].Y][Fluid_Cap] = LDE_LARGECAP;
									}
									Data_Access.Settings_Grid[Nodes[Counter2].X][
										Nodes[Counter2].Y][0] = Counter1 + 1;
								}
							}
						} else {
							Queried_Price = 0;
						}
						break;
					case Hazard_Strip:
						Data_Access.Visual_Grid[Column][Row] = 113;
						break;
					case Turbine_Input:
						if (Check_Clearance(Column, Row, 2, 3) && evn_i(UI_Access.Placing_Rotation)) {
							Fill_Clearance(LDE_INVALID, Column, Row, 2, 3);
							Placed = true;
						} else if (Check_Clearance(Column, Row, 3, 2) && !evn_i(UI_Access.Placing_Rotation)) {
							Fill_Clearance(LDE_INVALID, Column, Row, 3, 2);
							Placed = true;
						}
						if (Placed) {
							Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 120;
							Point Node = Return_Nodes(Column, Row, UI_Access.Placing_Rotation,
								Preconfigurations_Access.STI_Inputs)[0];
							Data_Access.Settings_Grid[UI_Access.Target_Tile.X][
								UI_Access.Target_Tile.Y][3] = 0;
							Data_Access.Settings_Grid[UI_Access.Target_Tile.X][
								UI_Access.Target_Tile.Y][4] = 0;
							Data_Access.Data_Grid[Node.X][Node.Y][Fluid_Cap] = LDE_REINFORCEDCAP;
							Data_Access.Settings_Grid[Node.X][Node.Y][0] = 1;
							Data_Access.Plumbing_Grid[Node.X][Node.Y] = UI_Access.Placing_Rotation + Left;
						} else {
							Queried_Price = 0;
						}
						break;
					case Turbine_Impulse:
						if (Check_Clearance(Column, Row, 2, 3) && evn_i(UI_Access.Placing_Rotation)) {
							Fill_Clearance(LDE_INVALID, Column, Row, 2, 3);
							Placed = true;
						} else if (Check_Clearance(Column, Row, 3, 2) && !evn_i(UI_Access.Placing_Rotation)) {
							Fill_Clearance(LDE_INVALID, Column, Row, 3, 2);
							Placed = true;
						}
						if (Placed) {
							Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 124;
							Data_Access.Settings_Grid[Column][Row][3] = 0;
						} else {
							Queried_Price = 0;
						}
						break;
					case Turbine_Output:
						if (Check_Clearance(Column, Row, 2, 2)) {
							Fill_Clearance(LDE_INVALID, Column, Row, 2, 2);
							Data_Access.Visual_Grid[Column][Row] = UI_Access.Placing_Rotation + 128;
							//do outputZ!
						} else {
							Data_Access.Settings_Grid[Column][Row][3] = 0;
							Queried_Price = 0;
						}
						break;
					default:
						break;
					}
					Data_Access.Funds = Data_Access.Funds - Queried_Price;
					Recast_Machines();
				}
				return;
			}
		}
	}
}

void Restore_Cache() {
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			if (Visual_To_ID(Data_Access.Visual_Grid[X][Y]) == 5) {
				Temporary_Access.Docks.push_back({ X, Y });
			}
		}
	}
	Recache_TT_Commands();
}

void Destroy_Clearance(int X, int Y, int Width, int Height) {
	for (int First_Counter = 0; First_Counter < Width; First_Counter++) {
		for (int Second_Counter = 0; Second_Counter < Height; Second_Counter++) {
			Data_Access.Visual_Grid[X + First_Counter][Y + Second_Counter] = 0;
			Data_Access.Connection_Grid[X + First_Counter][Y + Second_Counter] = LDE_INVALID;
			Data_Access.Wiring_Grid[X + First_Counter][Y + Second_Counter] = LDE_INVALID;
			Data_Access.Plumbing_Grid[X + First_Counter][Y + Second_Counter] = LDE_INVALID;
			Data_Access.Behaviour_Grid[X + First_Counter][Y + Second_Counter] = LDE_INVALID;
			Data_Access.Data_Grid[X + First_Counter][Y + Second_Counter] = { 0, 0, 0, 0, LDE_INVALID, 0, 0 };
			Data_Access.Settings_Grid[X + First_Counter][Y + Second_Counter] = { LDE_INVALID, LDE_INVALID, LDE_INVALID,
				LDE_INVALID, LDE_INVALID, LDE_INVALID, LDE_INVALID, LDE_INVALID };
			Data_Access.Animation_Grid[X + First_Counter][Y + Second_Counter] = { LDE_INVALID, LDE_INVALID };
			Update_Item(X + First_Counter, Y + Second_Counter, LDE_INVALID);
		}
	}
}

void Remove_Machine(int X, int Y) {
	Data_Access.Funds = Data_Access.Funds + Metadata_Access.Machine_Prices[
		Visual_To_ID(Data_Access.Visual_Grid[X][Y])];
	int Width;
	int Height;
	ID_To_Size(Visual_To_ID(Data_Access.Visual_Grid[X][Y]),
		Visual_To_Rotation(Data_Access.Visual_Grid[X][Y]), Width, Height);
	if (Width == 1 && Height == 1) {
		Data_Access.Visual_Grid[X][Y] = 0;
		Data_Access.Connection_Grid[X][Y] = LDE_INVALID;
		Data_Access.Wiring_Grid[X][Y] = LDE_INVALID;
		Data_Access.Plumbing_Grid[X][Y] = LDE_INVALID;
		Data_Access.Behaviour_Grid[X][Y] = LDE_INVALID;
		Data_Access.Data_Grid[X][Y] = { 0, 0, 0, 0, LDE_INVALID, 0, 0 };
		Data_Access.Settings_Grid[X][Y] = { LDE_INVALID, LDE_INVALID, LDE_INVALID,
			LDE_INVALID, LDE_INVALID, LDE_INVALID, LDE_INVALID, LDE_INVALID };
		Data_Access.Animation_Grid[X][Y] = { LDE_INVALID, LDE_INVALID };
		Update_Item(X, Y, LDE_INVALID);
	} else {
		if (Visual_To_ID(Data_Access.Visual_Grid[X][Y]) == Submarine_Dock) {
			for (int Counter = 0; Counter < Temporary_Access.Docks.size(); Counter++) {
				if (Temporary_Access.Docks[Counter][0] == X && Temporary_Access.Docks[Counter][1] == Y) {
					Temporary_Access.Docks.erase(Temporary_Access.Docks.begin() + Counter);
				}
			}
			if (Temporary_Access.Submarine_Position[0] == X && Temporary_Access.Submarine_Position[1] == Y) {
				Temporary_Access.Submarine_Phase = 3;
			}
			Recache_TT_Commands();
		} else if (Visual_To_ID(Data_Access.Visual_Grid[X][Y]) == Command_Platform) {
			Data_Access.CMD_Placed = false;
		}
		Destroy_Clearance(X, Y, Width, Height);
	}
	for (int Counter = 0; Counter < Wires_List.size(); Counter++) {
		if ((Wires_List[Counter].First_X == X && Wires_List[Counter].First_Y == Y) ||
			(Wires_List[Counter].Second_X == X && Wires_List[Counter].Second_Y == Y)) {
			Wires_List[Counter].Filled = false;
		}
	}
	for (int Counter = 0; Counter < Pipes_List.size(); Counter++) {
		if ((Pipes_List[Counter].First_X == X && Pipes_List[Counter].First_Y == Y) ||
			(Pipes_List[Counter].Second_X == X && Pipes_List[Counter].Second_Y == Y)) {
			Pipes_List[Counter].Filled = false;
		}
	}
}

bool Destroy_Grid() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rectangles_Access.Tile_1x1.x = static_cast<int>(((Column * 40) - UI_Access.Camera_X) * Settings_Access.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rectangles_Access.Tile_1x1.y = static_cast<int>(((Row * 40) - UI_Access.Camera_Y) * Settings_Access.Screen_Size);
			if (Detect_Mouse_Collision(Rectangles_Access.Tile_1x1)) {
				if (Data_Access.Visual_Grid[Column][Row] != 0) {
					Cache_Access.Wire_State = Deep_Recache;
					if (Data_Access.Visual_Grid[Column][Row] == LDE_INVALID) {
						Remove_Machine(static_cast<int>(Data_Access.Settings_Grid[Column][Row][1]),
							static_cast<int>(Data_Access.Settings_Grid[Column][Row][2]));
					} else {
						Remove_Machine(Column, Row);
					}
					Clear_Unconnected_Wires();
					Clear_Unconnected_Pipes();
					Recast_Machines();
					return true;
				}
			}
		}
	}
	return false;
}

void Update_Machines() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			int Rotation = Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row]);
			if (Data_Access.Visual_Grid[Column][Row] > 0) {
				if (Data_Access.Settings_Grid[Column][Row][1] > 0) {
					Data_Access.Settings_Grid[Column][Row][1]--;
					switch (Visual_To_ID(Data_Access.Visual_Grid[Column][Row])) {
					case Distillery:
						Extend_Recipe(Preset_IO_Recipes_Access.D_Water, Column, Row,
							Preconfigurations_Access.D_Outputs);
						break;
					case Electrolytic_Cell:
						if (Data_Access.Settings_Grid[Column][Row][2] == 1) {
							Extend_Recipe(Preset_IO_Recipes_Access.EP_Water, Column, Row,
								Preconfigurations_Access.EP_Outputs);
						} else if (Data_Access.Settings_Grid[Column][Row][2] == 2) {
							Extend_Recipe(Preset_IO_Recipes_Access.EP_Saltwater, Column, Row,
								Preconfigurations_Access.EP_Outputs);
						} else {
							Extend_Recipe(Preset_IO_Recipes_Access.EP_Salt, Column, Row,
								Preconfigurations_Access.EP_Outputs);
						}
						break;
					case Algae_Bed:
						Extend_Recipe(Preset_O_Recipes_Access.GB_Algae, Column, Row,
							Preconfigurations_Access.GB_Outputs);
						break;
					default:
						break;
					}
				}
			}
			std::vector<Point> Inputs;
			std::vector<Point> Outputs;
			std::vector<Recipe> Selected_Recipes;
			bool Conditional;
			switch (Visual_To_ID(Data_Access.Visual_Grid)) {
			case Incinerator:
				{
					double Resulting_Fluid = std::max(Data_Access.Data_Grid[
						Column][Row][Stored_Fluids] - 8.0, 0.0);
					Data_Access.Data_Grid[Column][Row][Stored_Fluids] = Resulting_Fluid;
				}
				break;
			case  Bio_Generator:
				{
					std::vector<int> Offset = { 0, 2 };
					switch (Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row])) {
					case 1:
						Offset[1] = 0;
						break;
					case 2:
						Offset[0] = 2;
						Offset[1] = 0;
						break;
					case 3:
						Offset[0] = 2;
						break;
					}
					Item_Stack Target_Item = Get_Item(Column + Offset[0], Row + Offset[1]);
					Data_Access.Animation_Grid[Column][Row][0] = 0;
					if (Check_Category(Target_Item.Identifier, Preset_Categories_Access.Biomass) > 0 &&
						Data_Access.Data_Grid[Column + Offset[0]][Row + Offset[1]][Stored_Fluids] >= 2) {
						Data_Access.Data_Grid[Column + Offset[0]][Row + Offset[1]][Stored_Fluids] -= 2;
						Data_Access.Data_Grid[Column][Row][Stored_Power] = std::min(Data_Access.Data_Grid[
							Column][Row][Stored_Power] + (Target_Item.Chemical_Energy / 100),
							Data_Access.Data_Grid[Column][Row][Power_Cap]);
						Data_Access.Animation_Grid[Column][Row][0] = 1;
					}
				}
				break;
			case Distillery:
				Inputs = Return_Nodes(Column, Row, Visual_To_Rotation(
					Data_Access.Visual_Grid[Column][Row]), Preconfigurations_Access.D_Inputs);
				Outputs = Return_Nodes(Column, Row, Visual_To_Rotation(
					Data_Access.Visual_Grid[Column][Row]), Preconfigurations_Access.D_Outputs);
				Process_Recipe(Preset_IO_Recipes_Access.D_Water, Column, Row, Inputs, Outputs);
				break;
			case Algae_Bed:
				if (Data_Access.Data_Grid[Column][Row][Stored_Power] > 120 && Data_Access.Data_Grid
					[Column][Row + 2][Stored_Fluids] <= 2 && Data_Access.Data_Grid
					[Column + 1][Row + 2][Stored_Fluids] <= 2 && Data_Access.Settings_Grid[Column][Row][1] <= 0) {
					Data_Access.Settings_Grid[Column][Row][1] = 2;
				}
				Outputs = Return_Nodes(Column, Row, Visual_To_Rotation(
					Data_Access.Visual_Grid[Column][Row]), Preconfigurations_Access.GB_Outputs);
				Process_Recipe(Preset_O_Recipes_Access.GB_Algae, Column, Row, { }, Outputs);
				break;
			case Electrolytic_Cell:
					Selected_Recipes = {
						Preset_IO_Recipes_Access.EP_Saltwater,
						Preset_IO_Recipes_Access.EP_Water,
						Preset_IO_Recipes_Access.EP_Salt
					};
					Outputs = Return_Nodes(Column, Row,
						Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row]),
						Preconfigurations_Access.EP_Outputs);
					for (int Counter = 0; Counter < Selected_Recipes.size(); Counter++) {
						if (Selected_Recipes[Counter].ID == Preset_IO_Recipes_Access.EP_Water.ID) {
							Outputs.erase(Outputs.begin() + 1);
						}
						Process_Recipe(Selected_Recipes[Counter], Column, Row, Return_Nodes(Column, Row,
						Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row]),
						Preconfigurations_Access.EP_Inputs), Outputs);
					}
				break;
			case Fluid_Mixer:
				Selected_Recipes = {
					Preset_IO_Recipes_Access.FM_Drillmud_1,
					Preset_IO_Recipes_Access.FM_Drillmud_2,
					Preset_IO_Recipes_Access.FM_Hydrogen_Chloride,
					Preset_IO_Recipes_Access.FM_Hydrochloric_Acid
				};
				for (int Counter = 0; Counter < Selected_Recipes.size(); Counter++) {
					Data_Access.Animation_Grid[Column][Row][0] = 0;
					if (Process_Recipe(Selected_Recipes[Counter], Column, Row, Return_Nodes(Column, Row,
						Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row]), Preconfigurations_Access.FM_Inputs),
						Return_Nodes(Column, Row, Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row]),
						Preconfigurations_Access.FM_Outputs))) {
						Data_Access.Animation_Grid[Column][Row][0] = 1;
						break;
					}
				}
				break;
			case Signal_Tower:
				if (Data_Access.Settings_Grid[Column][Row][3] == 0) {
					Data_Access.Settings_Grid[Column][Row][3] = 1;
				} else {
					Data_Access.Settings_Grid[Column][Row][3] = 0;
				}
				break;
			case Geo_Well:
				Conditional = true;
				if (Data_Access.Data_Grid[Column][Row][Stored_Power] < 2500) {
					Conditional = false;
				}
				Inputs = { { 0, 2 }, { 2, 0 }, { 1, 0 }, { 0, 1 } };
				Outputs = { { 0, 0 }, { 0, 0 }, { 1, 2 }, { 2, 1 } };
				if (Data_Access.Data_Grid[Column + Inputs[Rotation].X][
					Row + Inputs[Rotation].Y][Stored_Fluids] < 8 ||
					Data_Access.Data_Grid[Column + Outputs[Rotation].X][
					Row + Outputs[Rotation].Y][Stored_Fluids] > 0) {
					Conditional = false;
				}
				if (Check_Category(Data_Access.Items_Grid[Column + Outputs[Rotation].X][
					Row + Outputs[Rotation].Y], Preset_Categories_Access.Coolant)) {
					Conditional = false;
				}
				if (Conditional) {
					Data_Access.Data_Grid[Column][Row][Stored_Power] -= 2500;
					Data_Access.Data_Grid[Column + Inputs[Rotation].X][Row + Inputs[Rotation].Y][Stored_Fluids] -= 8;
					Data_Access.Data_Grid[Column + Outputs[Rotation].X][Row + Outputs[Rotation].Y][Stored_Fluids] += 8;
					int Temperature = Data_Access.Temperature_Grid
						[Column + Inputs[Rotation].X][Row + Inputs[Rotation].Y];
					if (Temperature == 328) {
						Temperature = 327;
					}
					double Benchmark = std::log10((double)(328 - Temperature) / 263) / std::log10(0.64);
					Update_Item(Column + Outputs[Rotation].X, Row + Outputs[Rotation].Y, Data_Access.Items_Grid
						[Column + Inputs[Rotation].X][Row + Inputs[Rotation].Y],
						(-263 * std::pow(0.64, Benchmark + 1)) + 328);
				}
				break;
			case Large_Pipe:
				if (Get_Item(Column, Row).Hazard > Harmless) {
					//if hazard then go boom
				}
				break;
			case Money_Generator:
				Data_Access.Funds = std::max(Data_Access.Funds +
					static_cast<long double>(Data_Access.Settings_Grid[
					Column][Row][4]), static_cast<long double>(0));
				break;
			case Fluid_Generator:
				if (Data_Access.Items_Grid[Column][Row] != Data_Access
					.Settings_Grid[Column][Row][3] || Data_Access
					.Temperature_Grid[Column][Row] != Data_Access
					.Settings_Grid[Column][Row][4]) {
					Data_Access.Data_Grid[Column][Row][Stored_Fluids] = 0;
					Data_Access.Items_Grid[Column][Row] = Data_Access.Settings_Grid[Column][Row][3];
					Data_Access.Temperature_Grid[Column][Row] = Data_Access.Settings_Grid[Column][Row][4];
				}
				Data_Access.Data_Grid[Column][Row][Stored_Fluids] = std::min(
					Data_Access.Settings_Grid[Column][Row][5] +
					Data_Access.Data_Grid[Column][Row][Stored_Fluids],
					Data_Access.Data_Grid[Column][Row][Fluid_Cap]);
				break;
			case R_Intersection:
			case L_Intersection:
				//check4hazard!
				Inputs = Return_Nodes(Column, Row, Visual_To_Rotation(
					Data_Access.Visual_Grid[Column][Row]),
					Preconfigurations_Access.I_Inputs);
				Outputs = Return_Nodes(Column, Row, Visual_To_Rotation(
					Data_Access.Visual_Grid[Column][Row]),
					Preconfigurations_Access.I_Outputs);
				for (int Counter = 0; Counter < 2; Counter++) {
					int OX = Outputs[Counter].X;
					int OY = Outputs[Counter].Y;
					int IX = Inputs[Counter].X;
					int IY = Inputs[Counter].Y;
					double Difference = Data_Access.Data_Grid[OX][OY][Fluid_Cap] -
						Data_Access.Data_Grid[OX][OY][Stored_Fluids];
					Difference = std::min(Difference, Data_Access.Data_Grid[IX][IY][Stored_Fluids]);
					if (Difference > 0 && (Data_Access.Items_Grid[IX][IY] ==
						Data_Access.Items_Grid[OX][OY] ||
						Data_Access.Items_Grid[OX][OY] == LDE_INVALID)) {
						Data_Access.Data_Grid[OX][OY][Stored_Fluids] += Difference;
						Data_Access.Data_Grid[IX][IY][Stored_Fluids] -= Difference;
						Update_Item(Outputs[Counter].X, OY, Data_Access.Items_Grid[IX][IY],
							Data_Access.Temperature_Grid[IX][IY]);
					}
				}
				break;
			case Turbine_Input:
				Inputs = Return_Nodes(Column, Row, Visual_To_Rotation(
					Data_Access.Visual_Grid[Column][Row]),
					Preconfigurations_Access.STI_Inputs);
				Outputs = Return_Nodes();
				if (Data_Access.Settings_Grid[Column][Row][3] > 0 &&
					Data_Access.Settings_Grid[Column][Row][4] == 1) {
					//store end x&y
					double Transferred = Data_Access.Data_Grid[Outputs[0].X][
							Outputs[0].Y][Fluid_Cap] - Data_Access.Data_Grid[
							Outputs[0].X][Outputs[0].Y][Stored_Fluids];
					Transferred = std::min(Transferred, Data_Access.Data_Grid[
						Inputs[0].X][Inputs[0].Y][Stored_Fluids]);
					if (Transferred > 0) {
						Data_Access.Data_Grid[Inputs[0].X][Inputs[0].Y][
							Stored_Fluids] -= Transferred;
						Data_Access.Data_Grid[Outputs[0].X][Outputs[0].Y][
							Stored_Fluids] += Transferred;
						
						//power gen
					}
				}
				break;
			default:
				break;
			}
			if (Data_Access.Visual_Grid[Column][Row] == 17) {
				if (Process_O_Recipe(Preset_O_Recipes_Access.RP_Saltwater, Column, Row, { { Column, Row } })) {
					Data_Access.Animation_Grid[Column][Row][0] = 0;
					Audio_Access.Play(&Audio_Access.Ram_Loop, false);
				} else if (Data_Access.Animation_Grid[Column][Row][0] == 0) {
					Data_Access.Animation_Grid[Column][Row][0] = LDE_INVALID;
				}
			} else if (Data_Access.Visual_Grid[Column][Row] == 19) {
				Data_Access.Data_Grid[Column][Row][Stored_Power] = std::min(Data_Access.Data_Grid
					[Column][Row][Stored_Power] + 0.5, Data_Access.Data_Grid[Column][Row][Power_Cap]);
			} else if (Data_Access.Visual_Grid[Column][Row] == 21) {
				for (int Counter = 0; Counter < 2; Counter++) {
					if (Data_Access.Data_Grid[Column + Counter][Row + 3][Stored_Fluids] > 0) {
						if (Data_Access.Settings_Grid[Column][Row][Counter + 5] == Get_Item(Column + Counter, Row + 3).Identifier ||
							Data_Access.Settings_Grid[Column][Row][Counter + 5] == LDE_INVALID) {
							Data_Access.Settings_Grid[Column][Row][Counter + 3] = std::min(Data_Access.Settings_Grid
								[Column][Row][Counter + 3] + Data_Access.Data_Grid
								[Column + Counter][Row + 3][Stored_Fluids], LDE_DOCKCAPACITY);
							Data_Access.Data_Grid[Column + Counter][Row + 3][Stored_Fluids] = 0;
							Data_Access.Settings_Grid[Column][Row][Counter + 5] = Get_Item(Column + Counter, Row + 3).Identifier;
						}
					}
				}
			} else if (Data_Access.Visual_Grid[Column][Row] == 22) {
				bool First_Running = Process_Recipe(Preset_IO_Recipes_Access.FP_Saltwater,
					Column, Row, { { Column, Row + 1 } }, { { Column + 1, Row },
					{ Column + 1, Row + 1 }, { Column + 1, Row + 2 } });
				bool Second_Running = Process_Recipe(Preset_IO_Recipes_Access.FP_Biopaste,
					Column, Row, { { Column, Row + 1 } }, { { Column + 1, Row },
					{ Column + 1, Row + 1 }, { Column + 1, Row + 2 } });
				Data_Access.Animation_Grid[Column][Row][0] = 0;
				Data_Access.Animation_Grid[Column][Row][1] = 0;
				if (First_Running || Second_Running) {
					Audio_Access.Play(&Audio_Access.Filtration_Loop, false);
				} else if (Data_Access.Animation_Grid[Column][Row][0] == 0) {
					Data_Access.Animation_Grid[Column][Row][0] = LDE_INVALID;
					Data_Access.Animation_Grid[Column][Row][1] = 0;
				}
			} else if (Data_Access.Visual_Grid[Column][Row] == 45) {
				if (Data_Access.Settings_Grid[Column][Row][5] != 0) {
					if (Data_Access.Settings_Grid[Column][Row][4] >= Data_Access.Settings_Grid[Column][Row][5] *
						Fish_Catalog[static_cast<int>(Data_Access.Settings_Grid[Column][Row][6])].Food_Consumption) {
						Data_Access.Settings_Grid[Column][Row][4] -= Data_Access.Settings_Grid[Column][Row][5] *
							Fish_Catalog[static_cast<int>(Data_Access.Settings_Grid[Column][Row][6])].Food_Consumption;
					} else {
						if (Data_Access.Settings_Grid[Column][Row][5] > 1) {
							Data_Access.Settings_Grid[Column][Row][5]--;
						} else {
							Data_Access.Settings_Grid[Column][Row][5] = 0;
							Data_Access.Settings_Grid[Column][Row][7] = 0;
						}
					}
					if (Data_Access.Settings_Grid[Column][Row][7] >= Fish_Catalog[static_cast<int>(
						Data_Access.Settings_Grid[Column][Row][6])].Maximum_Growth) {
						Data_Access.Settings_Grid[Column][Row][7] = 0;
						Point Coordinate = Find_Linked(14, Column, Row);
						Item_Stack Fish = Get_Fish_Item(static_cast<int>(Data_Access.Settings_Grid[Column][Row][6]));
						Update_Item(Coordinate.X, Coordinate.Y, Fish.Identifier);
						Data_Access.Data_Grid[Coordinate.X][Coordinate.Y][0] = std::min(
							Data_Access.Settings_Grid[Column][Row][5],
							Data_Access.Data_Grid[Coordinate.X][Coordinate.Y][Fluid_Cap]);
					}
					Data_Access.Settings_Grid[Column][Row][7] += 1;
				}
			} else if (Data_Access.Visual_Grid[Column][Row] == 47) {
				int Parent_X = static_cast<int>(Data_Access.Settings_Grid[Column][Row][3]);
				int Parent_Y = static_cast<int>(Data_Access.Settings_Grid[Column][Row][4]);
				double Food_Multiplier = 0;
				if (Data_Access.Items_Grid[Column][Row] == Preset_Items_Access.Marine_Snow.Identifier) {
					Food_Multiplier = 0.35;
				} else if (Data_Access.Items_Grid[Column][Row] == Preset_Items_Access.Raw_Algae.Identifier) {
					Food_Multiplier = 0.5;
				} else if (Data_Access.Items_Grid[Column][Row] == Preset_Items_Access.Biopaste.Identifier) {
					Food_Multiplier = 0.65;
				}
				if (Data_Access.Data_Grid[Column][Row][Stored_Fluids] > 0 && Food_Multiplier > 0) {
					Data_Access.Settings_Grid[Parent_X][Parent_Y][4] += Data_Access.Data_Grid[
						Column][Row][Stored_Fluids] * Food_Multiplier;
					Data_Access.Data_Grid[Column][Row][Stored_Fluids] = 0;
				}
			} else if (Visual_To_ID(Data_Access.Visual_Grid[Column][Row]) == Heat_Exchanger) {
				bool Boiling = false;
				if (Data_Access.Settings_Grid[UI_Access.Target_Tile.X][
					UI_Access.Target_Tile.Y][8] >= LDE_WATERBOILPOINT) {
					Boiling = true;
				}
				std::vector<Point> Outputs[2] = {
					{
						{ Column + 3, Row },
						{ Column + 2, Row + 3 },
						{ Column, Row + 2 },
						{ Column, Row }
					},
					{
						{ Column, Row },
						{ Column + 2, Row },
						{ Column + 3, Row + 2 },
						{ Column, Row + 3 }
					}
				};
				for (int Counter = 0; Counter < 2; Counter++) {
					Point Output_Pos = Outputs[Counter]
						[Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row])];
					if ((Data_Access.Items_Grid[Output_Pos.X][Output_Pos.Y] == LDE_INVALID || (
						Data_Access.Settings_Grid[Column][Row][Counter + 9] == Data_Access.Items_Grid
						[Output_Pos.X][Output_Pos.Y] && !Boiling) || (Data_Access.Items_Grid
						[Output_Pos.X][Output_Pos.Y] == Preset_Items_Access.Steam.Identifier &&
						Boiling && Counter == 1)) &&
						Data_Access.Settings_Grid[Column][Row][Counter + 5] > 0) {
						if (Boiling && Counter == 1) {
							Data_Access.Items_Grid[Output_Pos.X][Output_Pos.Y] =
								Preset_Items_Access.Steam.Identifier;
						} else {
							Data_Access.Items_Grid[Output_Pos.X][Output_Pos.Y] =
								Data_Access.Settings_Grid[Column][Row][Counter + 9];
						}
						double Draining_Amount = std::min(Data_Access.Settings_Grid[Column][Row][Counter + 3],
							Data_Access.Settings_Grid[Column][Row][Counter + 5]);
						Draining_Amount = std::min(Draining_Amount, Data_Access.Data_Grid
							[Output_Pos.X][Output_Pos.Y][Fluid_Cap] - Data_Access.Data_Grid
							[Output_Pos.X][Output_Pos.Y][Stored_Fluids]);
						Data_Access.Data_Grid[Output_Pos.X][Output_Pos.Y][Stored_Fluids] += Draining_Amount;
						Data_Access.Settings_Grid[Column][Row][Counter + 5] -= Draining_Amount;
					}
				}
				std::vector<Point> Inputs[2] = {
					{
						{ Column + 3, Row + 2 },
						{ Column, Row + 3 },
						{ Column, Row },
						{ Column + 2, Row }
					},
					{
						{ Column, Row + 2 },
						{ Column, Row },
						{ Column + 3, Row },
						{ Column + 2, Row + 3 }
					}
				};
				Item_Category Categories[2] = {
					Preset_Categories_Access.Coolant,
					Preset_Categories_Access.Feedwater
				};
				for (int Counter = 0; Counter < 2; Counter++) {
					Point Input_Pos = Inputs[Counter][Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row])];
					if (Check_Category(ID_To_Item(Data_Access.Items_Grid[Input_Pos.X]
						[Input_Pos.Y]).Identifier, Categories[Counter]) && (Data_Access.Settings_Grid[Column]
						[Row][Counter + 9] == LDE_INVALID || Data_Access.Settings_Grid[Column]
						[Row][Counter + 9] == Data_Access.Items_Grid[Input_Pos.X][Input_Pos.Y])) {
						Data_Access.Settings_Grid[Column][Row][Counter + 9] = Data_Access.Items_Grid
							[Input_Pos.X][Input_Pos.Y];
						int Volume = Data_Access.Settings_Grid[Column][Row][Counter + 5];
						int Intake = 0;
						if (Data_Access.Data_Grid[Input_Pos.X][Input_Pos.Y]
							[Stored_Fluids] > 0 && Volume < LDE_HXCAPACITY) {
							if (Volume + Data_Access.Data_Grid
								[Input_Pos.X][Input_Pos.Y][Stored_Fluids] > LDE_HXCAPACITY) {
								Intake = LDE_HXCAPACITY - Volume;
								Data_Access.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids] -= Intake;
								Data_Access.Settings_Grid[Column][Row][Counter + 5] = LDE_HXCAPACITY;
							} else {
								Intake = Data_Access.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids];
								Data_Access.Settings_Grid[Column][Row][Counter + 5] += Intake;
								Data_Access.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids] = 0;
							}
						}
						if (Volume + Intake != 0) {
							Data_Access.Settings_Grid[Column][Row][Counter + 7] = ((Data_Access.Settings_Grid
								[Column][Row][Counter + 7] * Volume) + (Data_Access.Temperature_Grid
								[Input_Pos.X][Input_Pos.Y] * Intake)) / (Volume + Intake);
						}
					}
				}
				double Temp_Equil = ((Data_Access.Settings_Grid[Column][Row][6] * Data_Access.Settings_Grid
					[Column][Row][8]) + (Data_Access.Settings_Grid[Column][Row][5] * Data_Access.Settings_Grid[Column]
					[Row][7])) / (Data_Access.Settings_Grid[Column][Row][6] + Data_Access.Settings_Grid[Column][Row][5]);
				double Difference = Data_Access.Settings_Grid[Column][Row][7] -	Data_Access.Settings_Grid[Column][Row][8];
				double Remaining = std::pow(M_E, (-1 * ((LDE_HXEFFICIENCY * (Data_Access.Settings_Grid[Column]
					[Row][6] + Data_Access.Settings_Grid[Column][Row][5])) / (4.186 *
					Data_Access.Settings_Grid[Column][Row][6] *	Data_Access.Settings_Grid[Column][Row][5]))));
				double FW_Yield = Temp_Equil - (((Data_Access.Settings_Grid[Column][Row][5] /
					(Data_Access.Settings_Grid[Column][Row][6] + Data_Access.Settings_Grid[Column]
					[Row][5])) * Difference) * Remaining);
				double HM_Yield = Temp_Equil + (((Data_Access.Settings_Grid[Column][Row][6] /
					(Data_Access.Settings_Grid[Column][Row][6] + Data_Access.Settings_Grid[Column]
					[Row][5])) * Difference) * Remaining);
				if (HM_Yield > 0 && FW_Yield > 0) {
					Data_Access.Settings_Grid[Column][Row][7] = HM_Yield;
					Data_Access.Settings_Grid[Column][Row][8] = FW_Yield;
				}
			}
		}
	}
}

void Recast_Machines() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			switch (Visual_To_ID(Data_Access.Visual_Grid[Column][Row])) {
			case Turbine_Input: {
				Data_Access.Settings_Grid[Column][Row][3] = 0;
				Data_Access.Settings_Grid[Column][Row][4] = 0;
				bool Chaining = true;
				int Chain_X = Column;
				int Chain_Y = Row;
					while (Chaining) {
						switch (Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row])) {
						case 0:
							(Chain_Y - 3 >= 0) ? Chain_Y -= 3 : Chaining = false;
							break;
						case 1:
							(Chain_X + 3 < LDE_GRIDSIZE) ? Chain_X += 3 : Chaining = false;
							break;
						case 2:
							(Chain_Y + 3 < LDE_GRIDSIZE) ? Chain_Y += 3 : Chaining = false;
							break;
						case 3:
							(Chain_X - 3 >= 0) ? Chain_X -= 3 : Chaining = false;
							break;
						default:
							break;
						}
						if (!Chaining) {
							break;
						}
						if (Visual_To_ID(Data_Access.Visual_Grid[Chain_X][Chain_Y]) == Turbine_Impulse) {
							if (Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row]) ==
								Visual_To_Rotation(Data_Access.Visual_Grid[Chain_X][Chain_Y])) {
								Data_Access.Settings_Grid[Column][Row][3]++;
								Data_Access.Settings_Grid[Chain_X][Chain_Y][3] = 1;
							} else {
								Chaining = false;
							}
						} else {
							Point Offset = { 0, 0 };
							if (Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row]) == 0) {
								Offset = { 0, -1 };
							} else if (Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row]) == 3) {
								Offset = { -1, 0 };
							}
							if (Visual_To_ID(Data_Access.Visual_Grid[Chain_X -
								Offset.X][Chain_Y - Offset.Y]) == Turbine_Output &&
								Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row]) ==
								Visual_To_Rotation(Data_Access.Visual_Grid[
								Chain_X - Offset.X][Chain_Y - Offset.Y])) {
								Data_Access.Settings_Grid[Column][Row][4] = 1;
								Data_Access.Settings_Grid[Chain_X - Offset.X][
									Chain_Y - Offset.Y][3] = 1;
								Data_Access.Settings_Grid[Column][Row][5] = Chain_X - Offset.X;
								Data_Access.Settings_Grid[Column][Row][6] = Chain_Y - Offset.Y;
							}
							Chaining = false;
						}
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

std::vector<double> Get_Grid_Data(std::vector<double> Grid[LDE_GRIDSIZE][LDE_GRIDSIZE]) {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rectangles_Access.Tile_1x1.x = static_cast<int>(((Column * 40) - UI_Access.Camera_X) * Settings_Access.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rectangles_Access.Tile_1x1.y = static_cast<int>(((Row * 40) - UI_Access.Camera_Y) * Settings_Access.Screen_Size);
			if (Detect_Mouse_Collision(Rectangles_Access.Tile_1x1)) {
				return Grid[Column][Row];
			}
		}
	}
	return { 0, 0, 0, 0, LDE_INVALID, 0, 0 };
}

int Get_Simple_Grid_Tile(int Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], int Neutral) {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rectangles_Access.Tile_1x1.x = static_cast<int>(((Column * 40) - UI_Access.Camera_X) * Settings_Access.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rectangles_Access.Tile_1x1.y = static_cast<int>(((Row * 40) - UI_Access.Camera_Y) * Settings_Access.Screen_Size);
			if (Detect_Mouse_Collision(Rectangles_Access.Tile_1x1)) {
				return Grid[Column][Row];
			}
		}
	}
	return Neutral;
}

void Reset_Statistics() {
	Data_Access.Funds = 750;
	Data_Access.CMD_Placed = false;
	Clear_Grid(Data_Access.Visual_Grid, 0);
	Clear_Grid(Data_Access.Connection_Grid, LDE_INVALID);
	Clear_Grid(Data_Access.Behaviour_Grid, LDE_INVALID);
	Clear_Grid(Data_Access.Wiring_Grid, LDE_INVALID);
	Clear_Grid(Data_Access.Plumbing_Grid, LDE_INVALID);
	Clear_Grid(Data_Access.Items_Grid, LDE_ROOMTEMP);
	Clear_Grid(Data_Access.Temperature_Grid, LDE_INVALID);
	std::vector<double> Empty_Data = { 0, 0, 0, 0, LDE_INVALID, 0, 0 };
	Clear_Vector_Grid(Data_Access.Data_Grid, Empty_Data);
	Empty_Data.resize(16, LDE_INVALID);
	Clear_Vector_Grid(Data_Access.Settings_Grid, Empty_Data);
	Clear_Wires();
	Clear_Pipes();
	Preclear_Temporaries();
	Save_Data(Core_Access.Selected_Save);
}