#include <grid.h>

bool (*Placing_Functions[40])(int X, int Y) = {
	Place_Reinforced_Pipe, Place_Ram_Pump,
	Place_Incinerator, Place_Piezo_Generator,
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
			if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Identifier &&
				Data.Settings_Grid[X][Y][3] == Parent_X &&
				Data.Settings_Grid[X][Y][4] == Parent_Y) {
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
				return -LDE_INFINITY;
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
				Temporary_Grid[Column][Row] = 1 + Modular_Detection(
					Data.Connection_Grid, Data.Plumbing_Grid,
					Data.Behaviour_Grid, Column, Row, 0, 1, LDE_INVALID, true);
			} else if (Data.Visual_Grid[Column][Row] > 23 && Data.Visual_Grid[Column][Row] < 41) {
				Temporary_Grid[Column][Row] = 24 + Modular_Detection(
					Data.Connection_Grid, Data.Plumbing_Grid,
					Data.Behaviour_Grid, Column, Row, LDE_INVALID, LDE_INVALID, 0, false);
			} else if (Data.Visual_Grid[Column][Row] == 45) {
				Temporary.First_Coordinate = { Column, Row };
				Data.Settings_Grid[Column][Row][3] = Find_Modular_Size(Column, Row, 8, 13, 14, 15);
				if (Data.Settings_Grid[Column][Row][3] < 0) {
					Data.Settings_Grid[Column][Row][3] = -2;
				}
				if (Temporary.Modular1_Requirement < 1) {
					Data.Settings_Grid[Column][Row][3] = -3;
				} else if (Temporary.Modular1_Requirement > 1) {
					Data.Settings_Grid[Column][Row][3] = -4;
				}
				if (Temporary.Modular2_Requirement < 1) {
					Data.Settings_Grid[Column][Row][3] = -5;
				} else if (Temporary.Modular2_Requirement > 1) {
					Data.Settings_Grid[Column][Row][3] = -6;
				}
				Temporary.Modular1_Requirement = 0;
				Temporary.Modular2_Requirement = 0;
			} else if (Visual_To_ID(Data.Visual_Grid[Column][Row]) == Large_Pipe) {
				Temporary_Grid[Column][Row] = Modular_Detection(
					Data.Connection_Grid, Data.Plumbing_Grid,
					Data.Behaviour_Grid, Column, Row, 0, 1, LDE_INVALID, true) + 71;
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
		Rects.Tile_1x1.x = static_cast<int>(((Column * 40) -
			Interface.Camera_X) * Settings.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = static_cast<int>(((Row * 40) -
				Interface.Camera_Y) * Settings.Screen_Size);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Data.Visual_Grid[Column][Row] == 0) {
					if (Placing_Functions[Interface.Placing_Item - 1](Column, Row)) {
						Data.Funds -= Interface.Queried_Price;
					}
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
			if (Visual_To_ID(Data.Visual_Grid[X][Y]) == 5) {
				Temporary.Docks.push_back({ X, Y });
			}
		}
	}
	Recache_TT_Commands();
}

void Destroy_Clearance(int X, int Y, int Width, int Height) {
	for (int Counter1 = 0; Counter1 < Width; Counter1++) {
		for (int Counter2 = 0; Counter2 < Height; Counter2++) {
			Data.Visual_Grid[X + Counter1][Y + Counter2] = 0;
			Data.Connection_Grid[X + Counter1][Y + Counter2] = LDE_INVALID;
			Data.Wiring_Grid[X + Counter1][Y + Counter2] = LDE_INVALID;
			Data.Plumbing_Grid[X + Counter1][Y + Counter2] = LDE_INVALID;
			Data.Behaviour_Grid[X + Counter1][Y + Counter2] = LDE_INVALID;
			Data.Data_Grid[X + Counter1][Y + Counter2] = { 0, 0, 0, 0, LDE_INVALID, 0, 0 };
			Data.Settings_Grid[X + Counter1][Y + Counter2] = { LDE_INVALID, LDE_INVALID, LDE_INVALID,
				LDE_INVALID, LDE_INVALID, LDE_INVALID, LDE_INVALID, LDE_INVALID };
			Data.Animation_Grid[X + Counter1][Y + Counter2] = { LDE_INVALID, LDE_INVALID };
			Update_Item(X + Counter1, Y + Counter2, LDE_INVALID);
		}
	}
}

void Remove_Machine(int X, int Y) {
	Data.Funds = Data.Funds + Metadata.Machine_Prices[
		Visual_To_ID(Data.Visual_Grid[X][Y])];
	int Width;
	int Height;
	ID_To_Size(Visual_To_ID(Data.Visual_Grid[X][Y]),
		Visual_To_Rotation(Data.Visual_Grid[X][Y]), Width, Height);
	if (Width == 1 && Height == 1) {
		Data.Visual_Grid[X][Y] = 0;
		Data.Connection_Grid[X][Y] = LDE_INVALID;
		Data.Wiring_Grid[X][Y] = LDE_INVALID;
		Data.Plumbing_Grid[X][Y] = LDE_INVALID;
		Data.Behaviour_Grid[X][Y] = LDE_INVALID;
		Data.Data_Grid[X][Y] = { 0, 0, 0, 0, LDE_INVALID, 0, 0 };
		Data.Settings_Grid[X][Y] = { LDE_INVALID, LDE_INVALID, LDE_INVALID,
			LDE_INVALID, LDE_INVALID, LDE_INVALID, LDE_INVALID, LDE_INVALID };
		Data.Animation_Grid[X][Y] = { LDE_INVALID, LDE_INVALID };
		Update_Item(X, Y, LDE_INVALID);
	} else {
		if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Submarine_Dock) {
			for (int Counter = 0; Counter < Temporary.Docks.size(); Counter++) {
				if (Temporary.Docks[Counter].X == X && Temporary.Docks[Counter].Y == Y) {
					Temporary.Docks.erase(Temporary.Docks.begin() + Counter);
				}
			}
			if (Temporary.Submarine_Position.X == X && Temporary.Submarine_Position.X == Y) {
				Temporary.Submarine_Phase = 3;
			}
			Recache_TT_Commands();
		} else if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Command_Platform) {
			Data.CMD_Placed = false;
		}
		Destroy_Clearance(X, Y, Width, Height);
	}
	for (int Counter = 0; Counter < Wires_List.size(); Counter++) {
		if ((Wires_List[Counter].X1 == X && Wires_List[Counter].Y1 == Y) ||
			(Wires_List[Counter].X2 == X && Wires_List[Counter].Y2 == Y)) {
			Wires_List[Counter].Filled = false;
		}
	}
	for (int Counter = 0; Counter < Pipes_List.size(); Counter++) {
		if ((Pipes_List[Counter].X1 == X && Pipes_List[Counter].Y1 == Y) ||
			(Pipes_List[Counter].X2 == X && Pipes_List[Counter].Y2 == Y)) {
			Pipes_List[Counter].Filled = false;
		}
	}
}

bool Destroy_Grid() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = static_cast<int>(((Column * 40) - Interface.Camera_X) * Settings.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = static_cast<int>(((Row * 40) - Interface.Camera_Y) * Settings.Screen_Size);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Data.Visual_Grid[Column][Row] != 0) {
					Cache.Wire_State = Deep_Recache;
					if (Data.Visual_Grid[Column][Row] == LDE_INVALID) {
						Remove_Machine(static_cast<int>(Data.Settings_Grid[Column][Row][1]),
							static_cast<int>(Data.Settings_Grid[Column][Row][2]));
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
			int Rotation = Visual_To_Rotation(Data.Visual_Grid[Column][Row]);
			if (Data.Visual_Grid[Column][Row] > 0) {
				if (Data.Settings_Grid[Column][Row][1] > 0) {
					Data.Settings_Grid[Column][Row][1]--;
					switch (Visual_To_ID(Data.Visual_Grid[Column][Row])) {
					case Distillery:
						Extend_Recipe(Preset_IO_Recipes.D_Water, Column, Row,
							Preconfigurations.D_Outputs);
						break;
					case Electrolytic_Cell:
						if (Data.Settings_Grid[Column][Row][2] == 1) {
							Extend_Recipe(Preset_IO_Recipes.EP_Water, Column, Row,
								Preconfigurations.EP_Outputs);
						} else if (Data.Settings_Grid[Column][Row][2] == 2) {
							Extend_Recipe(Preset_IO_Recipes.EP_Saltwater, Column, Row,
								Preconfigurations.EP_Outputs);
						} else {
							Extend_Recipe(Preset_IO_Recipes.EP_Salt, Column, Row,
								Preconfigurations.EP_Outputs);
						}
						break;
					case Algae_Bed:
						Extend_Recipe(Preset_O_Recipes.GB_Algae, Column, Row,
							Preconfigurations.GB_Outputs);
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
			switch (Visual_To_ID(Data.Visual_Grid[Column][Row])) {
			case Incinerator:
				{
					double Resulting_Fluid = std::max(Data.Data_Grid[
						Column][Row][Stored_Fluids] - 8.0, 0.0);
					Data.Data_Grid[Column][Row][Stored_Fluids] = Resulting_Fluid;
				}
				break;
			case Bio_Generator:
				{
					std::vector<int> Offset = { 0, 2 };
					switch (Visual_To_Rotation(Data.Visual_Grid[Column][Row])) {
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
					Data.Animation_Grid[Column][Row][0] = 0;
					if (Check_Category(Target_Item.Identifier, Preset_Categories.Biomass) > 0 &&
						Data.Data_Grid[Column + Offset[0]][Row + Offset[1]][Stored_Fluids] >= 2) {
						Data.Data_Grid[Column + Offset[0]][Row + Offset[1]][Stored_Fluids] -= 2;
						Data.Data_Grid[Column][Row][Stored_Power] = std::min(Data.Data_Grid[
							Column][Row][Stored_Power] + (Target_Item.Chemical_Energy / 100),
							Data.Data_Grid[Column][Row][Power_Cap]);
						Data.Animation_Grid[Column][Row][0] = 1;
					}
				}
				break;
			case Distillery:
				Inputs = Return_Nodes(Column, Row, Visual_To_Rotation(
					Data.Visual_Grid[Column][Row]), Preconfigurations.D_Inputs);
				Outputs = Return_Nodes(Column, Row, Visual_To_Rotation(
					Data.Visual_Grid[Column][Row]), Preconfigurations.D_Outputs);
				Process_Recipe(Preset_IO_Recipes.D_Water, Column, Row, Inputs, Outputs);
				break;
			case Algae_Bed:
				if (Data.Data_Grid[Column][Row][Stored_Power] > 120 && Data.Data_Grid
					[Column][Row + 2][Stored_Fluids] <= 2 && Data.Data_Grid
					[Column + 1][Row + 2][Stored_Fluids] <= 2 && Data.Settings_Grid[Column][Row][1] <= 0) {
					Data.Settings_Grid[Column][Row][1] = 2;
				}
				Outputs = Return_Nodes(Column, Row, Visual_To_Rotation(
					Data.Visual_Grid[Column][Row]), Preconfigurations.GB_Outputs);
				Process_Recipe(Preset_O_Recipes.GB_Algae, Column, Row, { }, Outputs);
				break;
			case Electrolytic_Cell:
					Selected_Recipes = {
						Preset_IO_Recipes.EP_Saltwater,
						Preset_IO_Recipes.EP_Water,
						Preset_IO_Recipes.EP_Salt
					};
					Outputs = Return_Nodes(Column, Row,
						Visual_To_Rotation(Data.Visual_Grid[Column][Row]),
						Preconfigurations.EP_Outputs);
					for (int Counter = 0; Counter < Selected_Recipes.size(); Counter++) {
						if (Selected_Recipes[Counter].ID == Preset_IO_Recipes.EP_Water.ID) {
							Outputs.erase(Outputs.begin() + 1);
						}
						Process_Recipe(Selected_Recipes[Counter], Column, Row, Return_Nodes(Column, Row,
						Visual_To_Rotation(Data.Visual_Grid[Column][Row]),
						Preconfigurations.EP_Inputs), Outputs);
					}
				break;
			case Fluid_Mixer:
				Selected_Recipes = {
					Preset_IO_Recipes.FM_Drillmud_1,
					Preset_IO_Recipes.FM_Drillmud_2,
					Preset_IO_Recipes.FM_Hydrogen_Chloride,
					Preset_IO_Recipes.FM_Hydrochloric_Acid
				};
				for (int Counter = 0; Counter < Selected_Recipes.size(); Counter++) {
					Data.Animation_Grid[Column][Row][0] = 0;
					if (Process_Recipe(Selected_Recipes[Counter], Column, Row, Return_Nodes(Column, Row,
						Visual_To_Rotation(Data.Visual_Grid[Column][Row]), Preconfigurations.FM_Inputs),
						Return_Nodes(Column, Row, Visual_To_Rotation(Data.Visual_Grid[Column][Row]),
						Preconfigurations.FM_Outputs))) {
						Data.Animation_Grid[Column][Row][0] = 1;
						break;
					}
				}
				break;
			case Signal_Tower:
				if (Data.Settings_Grid[Column][Row][3] == 0) {
					Data.Settings_Grid[Column][Row][3] = 1;
				} else {
					Data.Settings_Grid[Column][Row][3] = 0;
				}
				break;
			case Geo_Well:
				Conditional = true;
				if (Data.Data_Grid[Column][Row][Stored_Power] < 2500) {
					Conditional = false;
				}
				Inputs = { { 0, 2 }, { 2, 0 }, { 1, 0 }, { 0, 1 } };
				Outputs = { { 0, 0 }, { 0, 0 }, { 1, 2 }, { 2, 1 } };
				if (Data.Data_Grid[Column + Inputs[Rotation].X][
					Row + Inputs[Rotation].Y][Stored_Fluids] < 8 ||
					Data.Data_Grid[Column + Outputs[Rotation].X][
					Row + Outputs[Rotation].Y][Stored_Fluids] > 0) {
					Conditional = false;
				}
				if (Check_Category(Data.Items_Grid[Column + Outputs[Rotation].X][
					Row + Outputs[Rotation].Y], Preset_Categories.Coolant)) {
					Conditional = false;
				}
				if (Conditional) {
					Data.Data_Grid[Column][Row][Stored_Power] -= 2500;
					Data.Data_Grid[Column + Inputs[Rotation].X][Row + Inputs[Rotation].Y][Stored_Fluids] -= 8;
					Data.Data_Grid[Column + Outputs[Rotation].X][Row + Outputs[Rotation].Y][Stored_Fluids] += 8;
					int Temperature = Data.Temperature_Grid
						[Column + Inputs[Rotation].X][Row + Inputs[Rotation].Y];
					if (Temperature == 328) {
						Temperature = 327;
					}
					double Benchmark = std::log10((double)(328 - Temperature) / 263) / std::log10(0.64);
					Update_Item(Column + Outputs[Rotation].X, Row + Outputs[Rotation].Y, Data.Items_Grid
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
				Data.Funds = std::max(Data.Funds +
					static_cast<long double>(Data.Settings_Grid[
					Column][Row][4]), static_cast<long double>(0));
				break;
			case Fluid_Generator:
				if (Data.Items_Grid[Column][Row] != Data
					.Settings_Grid[Column][Row][3] || Data
					.Temperature_Grid[Column][Row] != Data
					.Settings_Grid[Column][Row][4]) {
					Data.Data_Grid[Column][Row][Stored_Fluids] = 0;
					Data.Items_Grid[Column][Row] = Data.Settings_Grid[Column][Row][3];
					Data.Temperature_Grid[Column][Row] = Data.Settings_Grid[Column][Row][4];
				}
				Data.Data_Grid[Column][Row][Stored_Fluids] = std::min(
					Data.Settings_Grid[Column][Row][5] +
					Data.Data_Grid[Column][Row][Stored_Fluids],
					Data.Data_Grid[Column][Row][Fluid_Cap]);
				break;
			case R_Intersection:
			case L_Intersection:
				//check4hazard!
				Inputs = Return_Nodes(Column, Row, Visual_To_Rotation(
					Data.Visual_Grid[Column][Row]),
					Preconfigurations.I_Inputs);
				Outputs = Return_Nodes(Column, Row, Visual_To_Rotation(
					Data.Visual_Grid[Column][Row]),
					Preconfigurations.I_Outputs);
				for (int Counter = 0; Counter < 2; Counter++) {
					int OX = Outputs[Counter].X;
					int OY = Outputs[Counter].Y;
					int IX = Inputs[Counter].X;
					int IY = Inputs[Counter].Y;
					double Difference = Data.Data_Grid[OX][OY][Fluid_Cap] -
						Data.Data_Grid[OX][OY][Stored_Fluids];
					Difference = std::min(Difference, Data.Data_Grid[IX][IY][Stored_Fluids]);
					if (Difference > 0 && (Data.Items_Grid[IX][IY] ==
						Data.Items_Grid[OX][OY] ||
						Data.Items_Grid[OX][OY] == LDE_INVALID)) {
						Data.Data_Grid[OX][OY][Stored_Fluids] += Difference;
						Data.Data_Grid[IX][IY][Stored_Fluids] -= Difference;
						Update_Item(Outputs[Counter].X, OY, Data.Items_Grid[IX][IY],
							Data.Temperature_Grid[IX][IY]);
					}
				}
				break;
			case Turbine_Input:
				Data.Settings_Grid[Column][Row][7] = 0;
				Inputs = Return_Nodes(Column, Row, Visual_To_Rotation(
					Data.Visual_Grid[Column][Row]),
					Preconfigurations.STI_Inputs);
				Outputs = Return_Nodes(Data.Settings_Grid[Column][Row][5],
					Data.Settings_Grid[Column][Row][6], Visual_To_Rotation(
					Data.Visual_Grid[static_cast<int>(Data.Settings_Grid[
					Column][Row][5])][static_cast<int>(Data.Settings_Grid[
					Column][Row][6])]), Preconfigurations.STO_Outputs);
				if (Data.Settings_Grid[Column][Row][3] > 0 &&
					Data.Settings_Grid[Column][Row][4] == 1 &&
					Data.Items_Grid[Inputs[0].X][Inputs[0].Y] ==
					Preset_Items.Steam.Identifier &&
					Data.Items_Grid[Outputs[0].X][Outputs[0].Y] ==
					Preset_Items.Steam.Identifier) {
					double Transferred = Data.Data_Grid[Outputs[0].X][
						Outputs[0].Y][Fluid_Cap] - Data.Data_Grid[
						Outputs[0].X][Outputs[0].Y][Stored_Fluids];
					Transferred = std::min(Transferred, Data.Data_Grid[
						Inputs[0].X][Inputs[0].Y][Stored_Fluids]);
					if (Transferred > 0) {
						Data.Data_Grid[Inputs[0].X][Inputs[0].Y][
							Stored_Fluids] -= Transferred;
						Data.Data_Grid[Outputs[0].X][Outputs[0].Y][
							Stored_Fluids] += Transferred;
						double Generated = Transferred * LDE_TURBINECOEFFICIENT *
							log(sqr_d(Data.Temperature_Grid[Inputs[0].X][Inputs[0].Y])) *
							log(Data.Settings_Grid[Column][Row][3] * 1.5);
						Update_Item(Outputs[0].X, Outputs[0].Y, Preset_Items
							.Steam.Identifier, (Data.Temperature_Grid[Inputs[
							0].X][Inputs[0].Y] * 0.1) + 32);
						if (Data.Temperature_Grid[Inputs[0].X][Inputs[0].Y] < 200) {
							Generated = 0;
						}
						Data.Settings_Grid[Column][Row][7] = Generated;
						Data.Data_Grid[Column][Row][Stored_Power] = std::min(
							Data.Data_Grid[Column][Row][Power_Cap], Data
							.Data_Grid[Column][Row][Stored_Power] + Generated);
					}
				}
				break;
			default:
				break;
			}
			if (Data.Visual_Grid[Column][Row] == 17) {
				if (Process_O_Recipe(Preset_O_Recipes.RP_Saltwater, Column, Row, { { Column, Row } })) {
					Data.Animation_Grid[Column][Row][0] = 0;
					Play_Sound(&Audio.Ram_Loop, false);
				} else if (Data.Animation_Grid[Column][Row][0] == 0) {
					Data.Animation_Grid[Column][Row][0] = LDE_INVALID;
				}
			} else if (Data.Visual_Grid[Column][Row] == 19) {
				Data.Data_Grid[Column][Row][Stored_Power] = std::min(Data.Data_Grid
					[Column][Row][Stored_Power] + 0.5, Data.Data_Grid[Column][Row][Power_Cap]);
			} else if (Data.Visual_Grid[Column][Row] == 21) {
				for (int Counter = 0; Counter < 2; Counter++) {
					if (Data.Data_Grid[Column + Counter][Row + 3][Stored_Fluids] > 0) {
						if (Data.Settings_Grid[Column][Row][Counter + 5] == Get_Item(Column + Counter, Row + 3).Identifier ||
							Data.Settings_Grid[Column][Row][Counter + 5] == LDE_INVALID) {
							Data.Settings_Grid[Column][Row][Counter + 3] = std::min(Data.Settings_Grid
								[Column][Row][Counter + 3] + Data.Data_Grid
								[Column + Counter][Row + 3][Stored_Fluids], LDE_DOCKCAPACITY);
							Data.Data_Grid[Column + Counter][Row + 3][Stored_Fluids] = 0;
							Data.Settings_Grid[Column][Row][Counter + 5] = Get_Item(Column + Counter, Row + 3).Identifier;
						}
					}
				}
			} else if (Data.Visual_Grid[Column][Row] == 22) {
				bool First_Running = Process_Recipe(Preset_IO_Recipes.FP_Saltwater,
					Column, Row, { { Column, Row + 1 } }, { { Column + 1, Row },
					{ Column + 1, Row + 1 }, { Column + 1, Row + 2 } });
				bool Second_Running = Process_Recipe(Preset_IO_Recipes.FP_Biopaste,
					Column, Row, { { Column, Row + 1 } }, { { Column + 1, Row },
					{ Column + 1, Row + 1 }, { Column + 1, Row + 2 } });
				Data.Animation_Grid[Column][Row][0] = 0;
				Data.Animation_Grid[Column][Row][1] = 0;
				if (First_Running || Second_Running) {
					Play_Sound(&Audio.Filtration_Loop, false);
				} else if (Data.Animation_Grid[Column][Row][0] == 0) {
					Data.Animation_Grid[Column][Row][0] = LDE_INVALID;
					Data.Animation_Grid[Column][Row][1] = 0;
				}
			} else if (Data.Visual_Grid[Column][Row] == 45) {
				if (Data.Settings_Grid[Column][Row][5] != 0) {
					if (Data.Settings_Grid[Column][Row][4] >= Data.Settings_Grid[Column][Row][5] *
						Fish_Catalog[static_cast<int>(Data.Settings_Grid[Column][Row][6])].Food_Consumption) {
						Data.Settings_Grid[Column][Row][4] -= Data.Settings_Grid[Column][Row][5] *
							Fish_Catalog[static_cast<int>(Data.Settings_Grid[Column][Row][6])].Food_Consumption;
					} else {
						if (Data.Settings_Grid[Column][Row][5] > 1) {
							Data.Settings_Grid[Column][Row][5]--;
						} else {
							Data.Settings_Grid[Column][Row][5] = 0;
							Data.Settings_Grid[Column][Row][7] = 0;
						}
					}
					if (Data.Settings_Grid[Column][Row][7] >= Fish_Catalog[static_cast<int>(
						Data.Settings_Grid[Column][Row][6])].Maximum_Growth) {
						Data.Settings_Grid[Column][Row][7] = 0;
						Point Coordinate = Find_Linked(14, Column, Row);
						Item_Stack Fish = Get_Fish_Item(static_cast<int>(Data.Settings_Grid[Column][Row][6]));
						Update_Item(Coordinate.X, Coordinate.Y, Fish.Identifier);
						Data.Data_Grid[Coordinate.X][Coordinate.Y][0] = std::min(
							Data.Settings_Grid[Column][Row][5],
							Data.Data_Grid[Coordinate.X][Coordinate.Y][Fluid_Cap]);
					}
					Data.Settings_Grid[Column][Row][7] += 1;
				}
			} else if (Data.Visual_Grid[Column][Row] == 47) {
				int Parent_X = static_cast<int>(Data.Settings_Grid[Column][Row][3]);
				int Parent_Y = static_cast<int>(Data.Settings_Grid[Column][Row][4]);
				double Food_Multiplier = 0;
				if (Data.Items_Grid[Column][Row] == Preset_Items.Marine_Snow.Identifier) {
					Food_Multiplier = 0.35;
				} else if (Data.Items_Grid[Column][Row] == Preset_Items.Raw_Algae.Identifier) {
					Food_Multiplier = 0.5;
				} else if (Data.Items_Grid[Column][Row] == Preset_Items.Biopaste.Identifier) {
					Food_Multiplier = 0.65;
				}
				if (Data.Data_Grid[Column][Row][Stored_Fluids] > 0 && Food_Multiplier > 0) {
					Data.Settings_Grid[Parent_X][Parent_Y][4] += Data.Data_Grid[
						Column][Row][Stored_Fluids] * Food_Multiplier;
					Data.Data_Grid[Column][Row][Stored_Fluids] = 0;
				}
			} else if (Visual_To_ID(Data.Visual_Grid[Column][Row]) == Heat_Exchanger) {
				bool Boiling = false;
				if (Data.Settings_Grid[Interface.Target_Tile.X][
					Interface.Target_Tile.Y][8] >= LDE_WATERBOILPOINT) {
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
						[Visual_To_Rotation(Data.Visual_Grid[Column][Row])];
					if ((Data.Items_Grid[Output_Pos.X][Output_Pos.Y] == LDE_INVALID || (
						Data.Settings_Grid[Column][Row][Counter + 9] == Data.Items_Grid
						[Output_Pos.X][Output_Pos.Y] && !Boiling) || (Data.Items_Grid
						[Output_Pos.X][Output_Pos.Y] == Preset_Items.Steam.Identifier &&
						Boiling && Counter == 1)) &&
						Data.Settings_Grid[Column][Row][Counter + 5] > 0) {
						if (Boiling && Counter == 1) {
							Data.Items_Grid[Output_Pos.X][Output_Pos.Y] =
								Preset_Items.Steam.Identifier;
						} else {
							Data.Items_Grid[Output_Pos.X][Output_Pos.Y] =
								Data.Settings_Grid[Column][Row][Counter + 9];
						}
						double Draining_Amount = std::min(Data.Settings_Grid[Column][Row][Counter + 3],
							Data.Settings_Grid[Column][Row][Counter + 5]);
						Draining_Amount = std::min(Draining_Amount, Data.Data_Grid
							[Output_Pos.X][Output_Pos.Y][Fluid_Cap] - Data.Data_Grid
							[Output_Pos.X][Output_Pos.Y][Stored_Fluids]);
						Data.Data_Grid[Output_Pos.X][Output_Pos.Y][Stored_Fluids] += Draining_Amount;
						Data.Settings_Grid[Column][Row][Counter + 5] -= Draining_Amount;
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
					Preset_Categories.Coolant,
					Preset_Categories.Feedwater
				};
				for (int Counter = 0; Counter < 2; Counter++) {
					Point Input_Pos = Inputs[Counter][Visual_To_Rotation(Data.Visual_Grid[Column][Row])];
					if (Check_Category(ID_To_Item(Data.Items_Grid[Input_Pos.X]
						[Input_Pos.Y]).Identifier, Categories[Counter]) && (Data.Settings_Grid[Column]
						[Row][Counter + 9] == LDE_INVALID || Data.Settings_Grid[Column]
						[Row][Counter + 9] == Data.Items_Grid[Input_Pos.X][Input_Pos.Y])) {
						Data.Settings_Grid[Column][Row][Counter + 9] = Data.Items_Grid
							[Input_Pos.X][Input_Pos.Y];
						int Volume = Data.Settings_Grid[Column][Row][Counter + 5];
						int Intake = 0;
						if (Data.Data_Grid[Input_Pos.X][Input_Pos.Y]
							[Stored_Fluids] > 0 && Volume < LDE_HXCAPACITY) {
							if (Volume + Data.Data_Grid
								[Input_Pos.X][Input_Pos.Y][Stored_Fluids] > LDE_HXCAPACITY) {
								Intake = LDE_HXCAPACITY - Volume;
								Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids] -= Intake;
								Data.Settings_Grid[Column][Row][Counter + 5] = LDE_HXCAPACITY;
							} else {
								Intake = Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids];
								Data.Settings_Grid[Column][Row][Counter + 5] += Intake;
								Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids] = 0;
							}
						}
						if (Volume + Intake != 0) {
							Data.Settings_Grid[Column][Row][Counter + 7] = ((Data.Settings_Grid
								[Column][Row][Counter + 7] * Volume) + (Data.Temperature_Grid
								[Input_Pos.X][Input_Pos.Y] * Intake)) / (Volume + Intake);
						}
					}
				}
				double Temp_Equil = ((Data.Settings_Grid[Column][Row][6] * Data.Settings_Grid
					[Column][Row][8]) + (Data.Settings_Grid[Column][Row][5] * Data.Settings_Grid[Column]
					[Row][7])) / (Data.Settings_Grid[Column][Row][6] + Data.Settings_Grid[Column][Row][5]);
				double Difference = Data.Settings_Grid[Column][Row][7] - Data.Settings_Grid[Column][Row][8];
				double Remaining = std::pow(M_E, (-1 * ((LDE_HXEFFICIENCY * (Data.Settings_Grid[Column]
					[Row][6] + Data.Settings_Grid[Column][Row][5])) / (4.186 *
					Data.Settings_Grid[Column][Row][6] *	Data.Settings_Grid[Column][Row][5]))));
				double FW_Yield = Temp_Equil - (((Data.Settings_Grid[Column][Row][5] /
					(Data.Settings_Grid[Column][Row][6] + Data.Settings_Grid[Column]
					[Row][5])) * Difference) * Remaining);
				double HM_Yield = Temp_Equil + (((Data.Settings_Grid[Column][Row][6] /
					(Data.Settings_Grid[Column][Row][6] + Data.Settings_Grid[Column]
					[Row][5])) * Difference) * Remaining);
				if (HM_Yield > 0 && FW_Yield > 0) {
					Data.Settings_Grid[Column][Row][7] = HM_Yield;
					Data.Settings_Grid[Column][Row][8] = FW_Yield;
				}
			}
		}
	}
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
								Offset = { 0, -1 };
							} else if (Visual_To_Rotation(Data.Visual_Grid[Column][Row]) == 3) {
								Offset = { -1, 0 };
							}
							if (Visual_To_ID(Data.Visual_Grid[Chain_X -
								Offset.X][Chain_Y - Offset.Y]) == Turbine_Output &&
								Visual_To_Rotation(Data.Visual_Grid[Column][Row]) ==
								Visual_To_Rotation(Data.Visual_Grid[
								Chain_X - Offset.X][Chain_Y - Offset.Y])) {
								Data.Settings_Grid[Column][Row][4] = 1;
								Data.Settings_Grid[Chain_X - Offset.X][
									Chain_Y - Offset.Y][3] = 1;
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

std::vector<double> Get_Grid_Data(std::vector<double> Grid[LDE_GRIDSIZE][LDE_GRIDSIZE]) {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = static_cast<int>(((Column * 40) - Interface.Camera_X) * Settings.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = static_cast<int>(((Row * 40) - Interface.Camera_Y) * Settings.Screen_Size);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				return Grid[Column][Row];
			}
		}
	}
	return { 0, 0, 0, 0, LDE_INVALID, 0, 0 };
}

int Get_Simple_Grid_Tile(int Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], int Neutral) {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = static_cast<int>(((Column * 40) - Interface.Camera_X) * Settings.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = static_cast<int>(((Row * 40) - Interface.Camera_Y) * Settings.Screen_Size);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				return Grid[Column][Row];
			}
		}
	}
	return Neutral;
}

void Reset_Statistics() {
	Data.Funds = 750;
	Data.CMD_Placed = false;
	Clear_Grid(Data.Visual_Grid, 0);
	Clear_Grid(Data.Connection_Grid, LDE_INVALID);
	Clear_Grid(Data.Behaviour_Grid, LDE_INVALID);
	Clear_Grid(Data.Wiring_Grid, LDE_INVALID);
	Clear_Grid(Data.Plumbing_Grid, LDE_INVALID);
	Clear_Grid(Data.Items_Grid, LDE_ROOMTEMP);
	Clear_Grid(Data.Temperature_Grid, LDE_INVALID);
	std::vector<double> Empty_Data = { 0, 0, 0, 0, LDE_INVALID, 0, 0 };
	Clear_Vector_Grid(Data.Data_Grid, Empty_Data);
	Empty_Data.resize(16, LDE_INVALID);
	Clear_Vector_Grid(Data.Settings_Grid, Empty_Data);
	Clear_Wires();
	Clear_Pipes();
	Preclear_Temporaries();
	Save_Data(Core.Selected_Save);
}