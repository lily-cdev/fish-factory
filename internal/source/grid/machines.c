#include <grid.h>

bool (*Placing_Functions[40])(int X, int Y) = {
	Place_Reinforced_Pipe, Place_Ram_Pump,
	Place_Incinerator, Place_RTG,
	Place_Decoration, Place_Submarine_Dock,
	Place_Filtration_Plant, Place_Bio_Generator,
	Place_Spawning_Pool, Place_Distillery,
	Place_Algae_Bed, Place_Command_Platform,
	Place_Basic_Scrubber, Place_Spawning_Controller,
	Place_Spawning_Output, Place_Spawning_Input,
	Place_Electrolytic_Cell, Place_Fluid_Mixer,
	Place_Signal_Tower, Place_Flowerpot,
	Place_Ammunition_Shelf, Place_Cable_Node,
	Place_Geo_Well, Place_Large_Pipe,
	Place_Heat_Exchanger, Place_Petrified_Wood,
	Place_Basalt_Tile, Place_Silicone_Carpet,
	Place_Money_Generator, Place_Fluid_Generator,
	Place_RL_Intersection, Place_RL_Intersection,
	Place_Hazard_Strip, Place_Condenser_Input,
	Place_Condenser_Transferor, Place_Condenser_Heatsink,
	Place_Condenser_Output, Place_Turbine_Input,
	Place_Turbine_Impulse, Place_Turbine_Output
};

Point Find_Linked(int Identifier, int Parent_X, int Parent_Y) {
	Point Yield = { LDE_INVALID, LDE_INVALID };
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Identifier && Data.Settings_Grid[X][Y][3] == Parent_X &&
				Data.Settings_Grid[X][Y][4] == Parent_Y) {
				Yield.X = X;
				Yield.Y = Y;
				return Yield;
			}
		}
	}
	return Yield;
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

int Recursive_Detect(int X, int Y, int Target, int Self, bool Grid[LDE_GRIDSIZE][LDE_GRIDSIZE],
	bool Self_Accounted, int Target1, int Target2);

int Recursive_Detect(int X, int Y, int Target, int Self, bool Grid[LDE_GRIDSIZE][LDE_GRIDSIZE],
	bool Self_Accounted, int Target1, int Target2) {
	bool Progressing = false;
	if (X >= 0 && Y >= 0 && X < LDE_GRIDSIZE && Y < LDE_GRIDSIZE && !Grid[X][Y]) {
		if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Target) {
			Progressing = true;
		} else if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Self) {
			if (Self_Accounted) {
				return -9999;
			} else {
				Self_Accounted = true;
				Progressing = true;
			}
		} else if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Target1) {
			Temporary.Modular1_Requirement++;
			Data.Settings_Grid[X][Y][3] = Temporary.First_Coordinate.X;
			Data.Settings_Grid[X][Y][4] = Temporary.First_Coordinate.Y;
			Progressing = true;
		} else if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Target2) {
			Temporary.Modular2_Requirement++;
			Data.Settings_Grid[X][Y][3] = Temporary.First_Coordinate.X;
			Data.Settings_Grid[X][Y][4] = Temporary.First_Coordinate.Y;
			Progressing = true;
		}
	}
	if (Progressing) {
		Grid[X][Y] = true;
		return 1 + Recursive_Detect(X + 1, Y, Target, Self, Grid, Self_Accounted, Target1, Target2) +
			Recursive_Detect(X - 1, Y, Target, Self, Grid, Self_Accounted, Target1, Target2) +
			Recursive_Detect(X, Y + 1, Target, Self, Grid, Self_Accounted, Target1, Target2) +
			Recursive_Detect(X, Y - 1, Target, Self, Grid, Self_Accounted, Target1, Target2);
	}
	return 0;
}

int Find_Modular_Size(int X, int Y, int Target, int Self, int Target1, int Target2) {
	bool Self_Accounted = false;
	bool Checked_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	for (int X2 = 0; X2 < LDE_GRIDSIZE; X2++) {
		for (int Y2 = 0; Y2 < LDE_GRIDSIZE; Y2++) {
			Checked_Grid[X2][Y2] = false;
		}
	}
	return Recursive_Detect(X, Y, Target, Self, Checked_Grid, Self_Accounted, Target1, Target2);
}

void Restore_Cache() {
	Temporary.Docks.Length = 0;
	Temporary.Docks.Full_Size = 0;
	free_c(Temporary.Docks.Data);
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			if (Visual_To_ID(Data.Visual_Grid[X][Y]) == 5) {
				Point Location = { X, Y };
				Push_Docks(Location);
			}
		}
	}
	Recache_TT_Commands();
}

void Destroy_Clearance(int X, int Y, int Width, int Height) {
	for (int C1 = 0; C1 < Width; C1++) {
		for (int C2 = 0; C2 < Height; C2++) {
			Data.Visual_Grid[X + C1][Y + C2] = 0;
			Data.Connection_Grid[X + C1][Y + C2] = LDE_INVALID;
			Data.Wiring_Grid[X + C1][Y + C2] = LDE_INVALID;
			Data.Plumbing_Grid[X + C1][Y + C2] = LDE_INVALID;
			Data.Behavior_Grid[X + C1][Y + C2] = LDE_INVALID;
			memset(Data.Data_Grid[X + C1][Y + C2], 0, sizeof(Data.Data_Grid[X + C1][Y + C2]));
			Data.Data_Grid[X + C1][Y + C2][4] = LDE_INVALID;
			memset(Data.Settings_Grid[X + C1][Y + C2], LDE_INVALID, sizeof(Data.Settings_Grid[X + C1][
				Y + C2]));
			memset(Data.Animation_Grid[X + C1][Y + C2], LDE_INVALID, sizeof(Data.Animation_Grid[X + C1][
				Y + C2]));
			Update_Item(X + C1, Y + C2, LDE_INVALID, LDE_ROOMTEMP);
		}
	}
}

void Update_Grid() {
	int Temporary_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE];
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Temporary_Grid[Column][Row] = Data.Visual_Grid[Column][Row];
		}
	}
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			if (Visual_To_ID(Data.Visual_Grid[Column][Row]) == Reinforced_Pipe) {
				Temporary_Grid[Column][Row] = Modular_Detection(Data.Connection_Grid, Data.Plumbing_Grid, Data.Behavior_Grid,
					Column, Row, 0, 1, LDE_INVALID, true) + 1;
			} else if (Data.Visual_Grid[Column][Row] > 23 && Data.Visual_Grid[Column][Row] < 41) {
				Temporary_Grid[Column][Row] = Modular_Detection(Data.Connection_Grid, Data.Plumbing_Grid, Data.Behavior_Grid,
					Column, Row, LDE_INVALID, LDE_INVALID, 0, false) + 24;
			} else if (Data.Visual_Grid[Column][Row] == 45) {
				Temporary.First_Coordinate.X = Column;
				Temporary.First_Coordinate.Y = Row;
				Data.Settings_Grid[Column][Row][3] = Find_Modular_Size(Column, Row, 8, 13, 14, 15);
				if (Data.Settings_Grid[Column][Row][3] < 0) {
					Data.Settings_Grid[Column][Row][3] = -2;
				}
				Data.Settings_Grid[Column][Row][3] = (Temporary.Modular1_Requirement < 1) ? -3 : -4;
				Data.Settings_Grid[Column][Row][3] = (Temporary.Modular2_Requirement < 1) ? -5 : -6;
				Temporary.Modular1_Requirement = 0;
				Temporary.Modular2_Requirement = 0;
			} else if (Visual_To_ID(Data.Visual_Grid[Column][Row]) == Large_Pipe) {
				Temporary_Grid[Column][Row] = Modular_Detection(
					Data.Connection_Grid, Data.Plumbing_Grid,
					Data.Behavior_Grid, Column, Row, 0, 1, LDE_INVALID, true) + 71;
			}
		}
	}
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Data.Visual_Grid[Column][Row] = Temporary_Grid[Column][Row];
		}
	}
}

void Build_Grid() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Data.Visual_Grid[Column][Row] == 0) {
					if (Placing_Functions[Interface.Item - 1](Column, Row)) {
						Data.Funds -= Interface.Queried_Price;
					}
					Recast_Machines();
				}
				return;
			}
		}
	}
}

void Remove_Machine(int X, int Y) {
	Data.Funds += Metadata.Machine_Prices[Visual_To_ID(Data.Visual_Grid[X][Y])];
	int Width;
	int Height;
	ID_To_Size(Visual_To_ID(Data.Visual_Grid[X][Y]),
		Visual_To_Rotation(Data.Visual_Grid[X][Y]), &Width, &Height);
	if (Width == 1 && Height == 1) {
		Data.Visual_Grid[X][Y] = 0;
		Data.Connection_Grid[X][Y] = LDE_INVALID;
		Data.Wiring_Grid[X][Y] = LDE_INVALID;
		Data.Plumbing_Grid[X][Y] = LDE_INVALID;
		Data.Behavior_Grid[X][Y] = LDE_INVALID;
		memset(Data.Data_Grid[X][Y], 0, sizeof(Data.Data_Grid[X][Y]));
		Data.Data_Grid[X][Y][4] = LDE_INVALID;
		memset(Data.Settings_Grid[X][Y], LDE_INVALID, sizeof(Data.Settings_Grid[X][Y]));
		memset(Data.Animation_Grid[X][Y], LDE_INVALID, sizeof(Data.Animation_Grid[X][Y]));
		Update_Item(X, Y, LDE_INVALID, LDE_ROOMTEMP);
	} else {
		if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Submarine_Dock) {
			for (int C1 = 0; C1 < Temporary.Docks.Length; C1++) {
				if (Temporary.Docks.Data[C1].X == X && Temporary.Docks.Data[C1].Y == Y) {
					Pull_Docks(C1);
				}
			}
			if (Transition.Sub_Pos.X == X && Transition.Sub_Pos.X == Y) {
				Transition.Sub_Phase = 3;
			}
			Recache_TT_Commands();
		} else if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Command_Platform) {
			Data.CMD_Placed = false;
		}
		Destroy_Clearance(X, Y, Width, Height);
	}
	for (int C1 = 0; C1 < Wires_List.Length; C1++) {
		if ((Wires_List.Data[C1].X1 == X && Wires_List.Data[C1].Y1 == Y) ||
			(Wires_List.Data[C1].X2 == X && Wires_List.Data[C1].Y2 == Y)) {
			Wires_List.Data[C1].Filled = false;
		}
	}
	for (int C1 = 0; C1 < Pipes_List.Length; C1++) {
		if ((Pipes_List.Data[C1].X1 == X && Pipes_List.Data[C1].Y1 == Y) ||
			(Pipes_List.Data[C1].X2 == X && Pipes_List.Data[C1].Y2 == Y)) {
			Pipes_List.Data[C1].Filled = false;
		}
	}
}

bool Destroy_Grid() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Data.Visual_Grid[Column][Row] != 0) {
					Cache.Wire_State = Deep_Recache;
					if (Data.Visual_Grid[Column][Row] == LDE_INVALID) {
						Remove_Machine((int)(Data.Settings_Grid[Column][Row][1]), (int)(Data.Settings_Grid[Column][Row][2]));
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

void Recast_Machines() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			switch (Visual_To_ID(Data.Visual_Grid[Column][Row])) {
			case Turbine_Input: {
				Data.Settings_Grid[Column][Row][3] = 0;
				Data.Settings_Grid[Column][Row][4] = 0;
				bool Chaining = true;
				int Chain_X = Column;
				int Chain_Y = Row;
					while (Chaining) {
						switch (Visual_To_Rotation(Data.Visual_Grid[Column][Row])) {
						case 0:
							(Chain_Y - 3 >= 0) ? (Chain_Y -= 3) : (Chaining = false);
							break;
						case 1:
							(Chain_X + 3 < LDE_GRIDSIZE) ? (Chain_X += 3) : (Chaining = false);
							break;
						case 2:
							(Chain_Y + 3 < LDE_GRIDSIZE) ? (Chain_Y += 3) : (Chaining = false);
							break;
						case 3:
							(Chain_X - 3 >= 0) ? (Chain_X -= 3) : (Chaining = false);
							break;
						default:
							break;
						}
						if (!Chaining) {
							break;
						}
						if (Visual_To_ID(Data.Visual_Grid[Chain_X][Chain_Y]) == Turbine_Impulse) {
							if (Visual_To_Rotation(Data.Visual_Grid[Column][Row]) ==
								Visual_To_Rotation(Data.Visual_Grid[Chain_X][Chain_Y])) {
								Data.Settings_Grid[Column][Row][3]++;
								Data.Settings_Grid[Chain_X][Chain_Y][3] = 1;
							} else {
								Chaining = false;
							}
						} else {
							Point Offset = { 0, 0 };
							if (Visual_To_Rotation(Data.Visual_Grid[Column][Row]) == 0) {
								Offset.X = 0;
								Offset.Y = -1;
							} else if (Visual_To_Rotation(Data.Visual_Grid[Column][Row]) == 3) {
								Offset.X = -1;
								Offset.Y = 0;
							}
							if (Visual_To_ID(Data.Visual_Grid[Chain_X - Offset.X][Chain_Y - Offset.Y]) == Turbine_Output &&
								Visual_To_Rotation(Data.Visual_Grid[Column][Row]) == Visual_To_Rotation(Data.Visual_Grid[
								Chain_X - Offset.X][Chain_Y - Offset.Y])) {
								Data.Settings_Grid[Column][Row][4] = 1;
								Data.Settings_Grid[Chain_X - Offset.X][Chain_Y - Offset.Y][3] = 1;
								Data.Settings_Grid[Column][Row][5] = Chain_X - Offset.X;
								Data.Settings_Grid[Column][Row][6] = Chain_Y - Offset.Y;
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

int Get_Simple_Grid_Tile(int Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], int Neutral) {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				return Grid[Column][Row];
			}
		}
	}
	return Neutral;
}