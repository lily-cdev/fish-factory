#include <grid.h>

bool (*Placing_Functions[])(Point Pos) = {
	Place_Reinforced_Pipe, Place_Ram_Pump, Place_Incinerator, Place_RTG, Place_Decoration, Place_Submarine_Dock,
	Place_Filtration_Plant, Place_Bio_Generator, Place_Spawning_Pool, Place_Distillery, Place_Algae_Bed,
	Place_Command_Platform, Place_Battery, Place_Spawning_Controller, Place_Spawning_Output, Place_Spawning_Input,
	Place_Electrolytic_Cell, Place_Fluid_Mixer, Place_Signal_Tower, Place_Flowerpot, Place_Ammunition_Shelf,
	Place_Cable_Node, Place_Geo_Well, Place_Large_Pipe, Place_Heat_Exchanger, Place_Petrified_Wood, Place_Basalt_Tile,
	Place_Silicone_Carpet, Place_Money_Generator, Place_Fluid_Generator, Place_RL_Intersection, Place_RL_Intersection,
	NULL, Place_Condenser_Input, Place_Condenser_Transferor, Place_Condenser_Heatsink, Place_Condenser_Output,
	Place_Turbine_Input, Place_Turbine_Impulse, Place_Turbine_Output, Place_Power_Generator
};

Point Find_Linked(int Identifier, Point Parent) {
	Point Pos;
	for (Pos.X = 0; Pos.X < LDE_GRIDSIZE; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < LDE_GRIDSIZE; Pos.Y++) {
			if (Visual_To_ID(Data.Visual_Grid[pt(Pos)]) == Identifier && Data.Settings_Grid[pt(Pos)][3] == Parent.X &&
				Data.Settings_Grid[pt(Pos)][4] == Parent.Y) {
				return Pos;
			}
		}
	}
	return (Point){ LDE_INVALID, LDE_INVALID };
}

bool Match(Point Pos, Point Og, int Direction, int Target, bool Is_Pipe) {
	bool Yield = (Is_Bound(Pos) && ((Is_Pipe && (Data.Plumbing_Grid[pt(Pos)] == Direction || Data.Plumbing_Grid[
		pt(Pos)] == Any)) || Data.Behavior_Grid[pt(Pos)] == Target));
	bool Unconnected = true;
	for (int C1 = 0; C1 < Pipes.Length; C1++) {
		if ((Pipes.Data[C1].X1 == Pos.X || Pipes.Data[C1].X2 == Pos.X) && (Pipes.Data[C1].Y1 == Pos.Y || Pipes.Data[
			C1].Y2 == Pos.Y) && (Pipes.Data[C1].X1 == Og.X || Pipes.Data[C1].X2 == Og.X) && (Pipes.Data[C1].Y1 == Og.Y ||
			Pipes.Data[C1].Y2 == Og.Y)) {
			Unconnected = false;
			break;
		}
	}
	return (Unconnected) ? false : Yield;
}

#define Param(XM, YM, Direction) (Point){ Pos.X + (XM), Pos.Y + (YM) }, Pos, Direction, Target, Is_Pipe
int Modular_Detection(Point Pos, int Target, bool Is_Pipe) {
	if (Target == LDE_INVALID) {
		Target = -2;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(1, 0, Left)) && Match(Param(0, 1, Up)) && Match(Param(0, -1, Down))) {
		return C_Omni;
	}
	if (Match(Param(1, 0, Left)) && Match(Param(0, 1, Up)) && Match(Param(0, -1, Down))) {
		return C_LeftT;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(0, -1, Up)) && Match(Param(0, 1, Down))) {
		return C_RightT;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(1, 0, Left)) && Match(Param(0, 1, Up))) {
		return C_UpT;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(1, 0, Left)) && Match(Param(0, -1, Down))) {
		return C_DownT;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(1, 0, Left))) {
		return C_Horizontal;
	}
	if (Match(Param(0, 1, Up)) && Match(Param(0, -1, Down))) {
		return C_Vertical;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(0, -1, Down))) {
		return C_LeftTop;
	}
	if (Match(Param(1, 0, Left)) && Match(Param(0, -1, Down))) {
		return C_TopRight;
	}
	if (Match(Param(1, 0, Left)) && Match(Param(0, 1, Up))) {
		return C_RightBottom;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(0, 1, Up))) {
		return C_BottomLeft;
	}
	if (Match(Param(-1, 0, Right))) {
		return C_Left;
	}
	if (Match(Param(0, -1, Down))) {
		return C_Top;
	}
	if (Match(Param(1, 0, Left))) {
		return C_Right;
	}
	if (Match(Param(0, 1, Up))) {
		return C_Bottom;
	}
	return C_None;
}
#undef Param

int Recursive_Detect(Point Pos, int Target, int Self, bool Grid[LDE_GRIDSIZE][LDE_GRIDSIZE],
	bool Self_Accounted, int Target1, int Target2);

int Recursive_Detect(Point Pos, int Target, int Self, bool Grid[LDE_GRIDSIZE][LDE_GRIDSIZE],
	bool Self_Accounted, int Target1, int Target2) {
	bool Progressing = false;
	if (Pos.X >= 0 && Pos.Y >= 0 && Pos.X < LDE_GRIDSIZE && Pos.Y < LDE_GRIDSIZE && !Grid[pt(Pos)]) {
		if (Visual_To_ID(Data.Visual_Grid[pt(Pos)]) == Target) {
			Progressing = true;
		} else if (Visual_To_ID(Data.Visual_Grid[pt(Pos)]) == Self) {
			if (Self_Accounted) {
				return -9999;
			} else {
				Self_Accounted = true;
				Progressing = true;
			}
		} else if (Visual_To_ID(Data.Visual_Grid[pt(Pos)]) == Target1) {
			Temporary.Modular1_Requirement++;
			Data.Settings_Grid[pt(Pos)][3] = Temporary.First_Coordinate.X;
			Data.Settings_Grid[pt(Pos)][4] = Temporary.First_Coordinate.Y;
			Progressing = true;
		} else if (Visual_To_ID(Data.Visual_Grid[pt(Pos)]) == Target2) {
			Temporary.Modular2_Requirement++;
			Data.Settings_Grid[pt(Pos)][3] = Temporary.First_Coordinate.X;
			Data.Settings_Grid[pt(Pos)][4] = Temporary.First_Coordinate.Y;
			Progressing = true;
		}
	}
	if (Progressing) {
		Grid[pt(Pos)] = true;
		return 1 + Recursive_Detect((Point){ Pos.X + 1, Pos.Y }, Target, Self, Grid, Self_Accounted, Target1, Target2) +
			Recursive_Detect((Point){ Pos.X - 1, Pos.Y }, Target, Self, Grid, Self_Accounted, Target1, Target2) +
			Recursive_Detect((Point){ Pos.X, Pos.Y + 1 }, Target, Self, Grid, Self_Accounted, Target1, Target2) +
			Recursive_Detect((Point){ Pos.X, Pos.Y - 1 }, Target, Self, Grid, Self_Accounted, Target1, Target2);
	}
	return 0;
}

int Find_Modular_Size(Point Pos, int Target, int Self, int Target1, int Target2) {
	bool Self_Accounted = false;
	bool Checked_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
	for (int X2 = 0; X2 < LDE_GRIDSIZE; X2++) {
		for (int Y2 = 0; Y2 < LDE_GRIDSIZE; Y2++) {
			Checked_Grid[X2][Y2] = false;
		}
	}
	return Recursive_Detect(Pos, Target, Self, Checked_Grid, Self_Accounted, Target1, Target2);
}

void Restore_Cache() {
	Temporary.Docks.Length = 0;
	Temporary.Docks.Full_Size = 0;
	free_c(Temporary.Docks.Data);
	Point Pos;
	for (Pos.X = 0; Pos.X < LDE_GRIDSIZE; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < LDE_GRIDSIZE; Pos.Y++) {
			if (Visual_To_ID(Data.Visual_Grid[pt(Pos)]) == 5) {
				Push_Docks(Pos);
			}
		}
	}
	Recache_TT_Commands();
}

void Destroy_Clearance(Point Pos, int Width, int Height) {
	for (int C1 = 0; C1 < Width; C1++) {
		for (int C2 = 0; C2 < Height; C2++) {
			Reset_Tile((Point){ Pos.X + C1, Pos.Y + C2 });
		}
	}
}

void Update_Grid() {
	int Temporary_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE];
	Point Pos;
	for (Pos.X = 0; Pos.X < LDE_GRIDSIZE; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < LDE_GRIDSIZE; Pos.Y++) {
			Temporary_Grid[pt(Pos)] = Data.Visual_Grid[pt(Pos)];
		}
	}
	for (Pos.X = 0; Pos.X < LDE_GRIDSIZE; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < LDE_GRIDSIZE; Pos.Y++) {
			if (Visual_To_ID(Data.Visual_Grid[pt(Pos)]) == Reinforced_Pipe) {
				Temporary_Grid[pt(Pos)] = Modular_Detection(Pos, LDE_INVALID, true) + 1;
			} else if (Data.Visual_Grid[pt(Pos)] > 23 && Data.Visual_Grid[pt(Pos)] < 41) {
				Temporary_Grid[pt(Pos)] = Modular_Detection(Pos, 0, false) + 24;
			} else if (Data.Visual_Grid[pt(Pos)] == 45) {
				Temporary.First_Coordinate = Pos;
				Data.Settings_Grid[pt(Pos)][3] = Find_Modular_Size(Pos, 8, 13, 14, 15);
				if (Data.Settings_Grid[pt(Pos)][3] < 0) {
					Data.Settings_Grid[pt(Pos)][3] = -2;
				}
				Data.Settings_Grid[pt(Pos)][3] = (Temporary.Modular1_Requirement < 1) ? -3 : -4;
				Data.Settings_Grid[pt(Pos)][3] = (Temporary.Modular2_Requirement < 1) ? -5 : -6;
				Temporary.Modular1_Requirement = 0;
				Temporary.Modular2_Requirement = 0;
			} else if (Visual_To_ID(Data.Visual_Grid[pt(Pos)]) == Large_Pipe) {
				Temporary_Grid[pt(Pos)] = Modular_Detection(Pos, LDE_INVALID, true) + 71;
			}
		}
	}
	for (Pos.X = 0; Pos.X < LDE_GRIDSIZE; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < LDE_GRIDSIZE; Pos.Y++) {
			Data.Visual_Grid[pt(Pos)] = Temporary_Grid[pt(Pos)];
		}
	}
}

void Build_Grid() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Scalar);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Scalar);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Data.Visual_Grid[Column][Row] == 0) {
					if (Placing_Functions[Interface.Item - 1] && !Placing_Functions[Interface.Item - 1]((Point){ Column, Row })) {
						return;
					}
					Data.Funds -= Interface.Queried_Price;
					if (Metadata.Machines[Interface.Item - 1].Single_ID) {
						Data.Visual_Grid[Column][Row] = Metadata.Machines[Interface.Item - 1].Visual_ID1;
					}
					Update_Grid();
					Recast_Machines();
					Find_Effect();
				}
				return;
			}
		}
	}
}

void Remove_Machine(Point Pos) {
	Data.Funds += (int)(floor(Metadata.Machines[Visual_To_ID(Data.Visual_Grid[pt(Pos)])].Price * 0.75f));
	int Width;
	int Height;
	ID_To_Size(Visual_To_ID(Data.Visual_Grid[pt(Pos)]), Visual_To_Rotation(Data.Visual_Grid[pt(Pos)]), &Width, &Height);
	if (Width == 1 && Height == 1) {
		Wipe_Tile(Pos);
		Data.Visual_Grid[pt(Pos)] = 0;
		Data.Wiring_Grid[pt(Pos)] = LDE_INVALID;
		Data.Plumbing_Grid[pt(Pos)] = LDE_INVALID;
		Data.Behavior_Grid[pt(Pos)] = LDE_INVALID;
		memset(Data.Data_Grid[pt(Pos)], 0, sizeof(Data.Data_Grid[pt(Pos)]));
		Data.Data_Grid[pt(Pos)][4] = LDE_INVALID;
		for (int C1 = 0; C1 < sizeof(Data.Settings_Grid[pt(Pos)]) / sizeof(Data.Settings_Grid[pt(Pos)][0]); C1++) {
			Data.Settings_Grid[pt(Pos)][C1] = LDE_INVALID;
		}
		for (int C1 = 0; C1 < sizeof(Data.Animation_Grid[pt(Pos)]) / sizeof(Data.Animation_Grid[pt(Pos)][0]); C1++) {
			Data.Animation_Grid[pt(Pos)][C1] = LDE_INVALID;
		}
		Update_Item(Pos, LDE_INVALID, LDE_ROOMTEMP);
	} else {
		if (Visual_To_ID(Data.Visual_Grid[pt(Pos)]) == Submarine_Dock) {
			for (int C1 = 0; C1 < Temporary.Docks.Length; C1++) {
				if (Temporary.Docks.Data[C1].X == Pos.X && Temporary.Docks.Data[C1].Y == Pos.Y) {
					Pull_Docks(C1);
				}
			}
			if (Transition.Sub_Pos.X == Pos.X && Transition.Sub_Pos.X == Pos.Y) {
				Transition.Sub_Phase = 3;
			}
			Recache_TT_Commands();
		} else if (Visual_To_ID(Data.Visual_Grid[pt(Pos)]) == Command_Platform) {
			Data.CMD_Placed = false;
		}
		Destroy_Clearance(Pos, Width, Height);
	}
	for (int C1 = 0; C1 < Wires.Length; C1++) {
		if ((Wires.Data[C1].X1 == Pos.X && Wires.Data[C1].Y1 == Pos.Y) || (Wires.Data[C1].X2 == Pos.X &&
			Wires.Data[C1].Y2 == Pos.Y)) {
			Wires.Data[C1].Filled = false;
		}
	}
	for (int C1 = 0; C1 < Pipes.Length; C1++) {
		if ((Pipes.Data[C1].X1 == Pos.X && Pipes.Data[C1].Y1 == Pos.Y) || (Pipes.Data[C1].X2 == Pos.X &&
			Pipes.Data[C1].Y2 == Pos.Y)) {
			Pipes.Data[C1].Filled = false;
		}
	}
}

bool Destroy_Grid() {
	Point Pos;
	for (Pos.X = 0; Pos.X < LDE_GRIDSIZE; Pos.X++) {
		Rects.Tile_1x1.x = (int)(((Pos.X * LDE_TILESIZE) - Core.Camera.X) * Settings.Scalar);
		for (Pos.Y = 0; Pos.Y < LDE_GRIDSIZE; Pos.Y++) {
			Rects.Tile_1x1.y = (int)(((Pos.Y * LDE_TILESIZE) - Core.Camera.Y) * Settings.Scalar);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Data.Visual_Grid[pt(Pos)] != 0) {
					Cache.Wire_State = Deep_Recache;
					if (Data.Visual_Grid[pt(Pos)] == LDE_INVALID) {
						Remove_Machine((Point){ (int)(Data.Settings_Grid[pt(Pos)][S_ParentX]), (int)(Data.Settings_Grid[
							pt(Pos)][S_ParentY]) });
					} else {
						Remove_Machine(Pos);
					}
					Clear_Unconnected_Bridges(&Wires);
					Clear_Unconnected_Bridges(&Pipes);
					Update_Grid();
					Recast_Machines();
					Find_Effect();
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
			case Turbine_Input:
				{
					Data.Settings_Grid[Column][Row][3] = 0;
					Data.Settings_Grid[Column][Row][4] = 0;
					bool Chaining = true;
					int Chain_X = Column;
					int Chain_Y = Row;
					int Rotation = Visual_To_Rotation(Data.Visual_Grid[Column][Row]);
					while (Chaining) {
						switch (Rotation) {
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
							if (Rotation == Visual_To_Rotation(Data.Visual_Grid[Chain_X][Chain_Y])) {
								Data.Settings_Grid[Column][Row][3]++;
								Data.Settings_Grid[Chain_X][Chain_Y][3] = 1;
							} else {
								Chaining = false;
							}
						} else {
							Point End_Pos = { Chain_X - ((Rotation == 3) ? -1 : 0), Chain_Y - ((Rotation == 0) ? 1 : 0) };
							if (End_Pos.X < 0 || End_Pos.Y < 0 || End_Pos.X >= LDE_GRIDSIZE || End_Pos.Y >= LDE_GRIDSIZE) {
								Chaining = false;
							}
							if (Visual_To_ID(Data.Visual_Grid[pt(End_Pos)]) == Turbine_Output && Rotation ==
								Visual_To_Rotation(Data.Visual_Grid[pt(End_Pos)])) {
								Data.Settings_Grid[Column][Row][4] = 1;
								Data.Settings_Grid[pt(End_Pos)][3] = 1;
								Data.Settings_Grid[Column][Row][5] = End_Pos.X;
								Data.Settings_Grid[Column][Row][6] = End_Pos.Y;
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
		Rects.Tile_1x1.x = (int)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Scalar);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Scalar);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				return Grid[Column][Row];
			}
		}
	}
	return Neutral;
}

void Find_Effect() {
	Interface.Effects[E_Heat] = 0;
	Interface.Effects[E_Radiation] = 0;
	Point Pos;
	for (Pos.X = 0; Pos.X < LDE_GRIDSIZE; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < LDE_GRIDSIZE; Pos.Y++) {
			for (int C1 = 0; C1 < intlen(Metadata.Heating_Machines); C1++) {
				if (Visual_To_ID(Data.Visual_Grid[pt(Pos)]) == Metadata.Heating_Machines[C1] && Pos.X * LDE_TILESIZE >
					Core.Camera.X && Pos.Y * LDE_TILESIZE > Core.Camera.Y && Pos.X * LDE_TILESIZE < Core.Camera.X + 640 &&
					Pos.Y * LDE_TILESIZE < Core.Camera.Y + 360) {
					Interface.Effects[E_Heat] += 0.1;
					return;
				}
			}
			for (int C1 = 0; C1 < intlen(Metadata.Irradiating_Machines); C1++) {
				if (Visual_To_ID(Data.Visual_Grid[pt(Pos)]) == Metadata.Irradiating_Machines[C1]) {
					float A = ((Core.Camera.X + 320) - (Pos.X * LDE_TILESIZE)) * Settings.Scalar;
					float B = ((Core.Camera.Y + 180) - (Pos.Y * LDE_TILESIZE)) * Settings.Scalar;
					float Distance = sqrtf(sqr(A) + sqr(B));
					Interface.Effects[E_Radiation] += fmax(35.0f - (Distance * 0.05f), 0.0f);
				}
			}
		}
	}
}