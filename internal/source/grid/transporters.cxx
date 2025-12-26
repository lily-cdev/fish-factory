#include <grid.h>

bool Place_Reinforced_Pipe(int X, int Y) {
	Data.Visual_Grid[X][Y] = 1;
	Data.Connection_Grid[X][Y] = 1;
	Data.Data_Grid[X][Y][Fluid_Cap] = LDE_REINFORCEDCAP;
	Data.Settings_Grid[X][Y][0] = F_Either;
	Data.Plumbing_Grid[X][Y] = Any;
	return true;
}

bool Place_Submarine_Dock(int X, int Y) {
	if (Check_Clearance(X, Y, 6, 4) && Y == 0) {
		Fill_Clearance(LDE_INVALID, X, Y, 6, 4);
		Data.Visual_Grid[X][Y] = 21;
		Data.Plumbing_Grid[X][Y + 3] = Down;
		Data.Plumbing_Grid[X + 1][Y + 3] = Down;
		Data.Settings_Grid[X][Y + 3][0] = F_In;
		Data.Settings_Grid[X + 1][Y + 3][0] = F_In;
		Data.Data_Grid[X][Y + 3][Fluid_Cap] = 200;
		Data.Data_Grid[X + 1][Y + 3][Fluid_Cap] = 200;
		Data.Settings_Grid[X][Y][3] = 0;
		Data.Settings_Grid[X][Y][4] = 0;
		Data.Settings_Grid[X][Y][5] = LDE_INVALID;
		Data.Settings_Grid[X][Y][6] = LDE_INVALID;
		Temporary.Docks.push_back({ X, Y });
		Recache_TT_Commands();
	} else {
		return false;
	}
	return true;
}

bool Place_Cable_Node(int X, int Y) {
	Data.Visual_Grid[X][Y] = 63;
	Data.Wiring_Grid[X][Y] = 2;
	Data.Data_Grid[X][Y][Power_Cap] = 12000;
	Data.Data_Grid[X][Y][5] = 20;
	Data.Data_Grid[X][Y][6] = 20;
	return true;
}

bool Place_Large_Pipe(int X, int Y) {
	Data.Visual_Grid[X][Y] = 71;
	Data.Connection_Grid[X][Y] = 1;
	Data.Data_Grid[X][Y][Fluid_Cap] = LDE_LARGECAP;
	Data.Settings_Grid[X][Y][0] = F_Either;
	Data.Plumbing_Grid[X][Y] = Any;
	return true;
}

bool Place_RL_Intersection(int X, int Y) {
    if (Check_Clearance(X, Y, 3, 3)) {
		Fill_Clearance(LDE_INVALID, X, Y, 3, 3);
		if (Interface.Placing_Item - 1 == R_Intersection) {
			Data.Visual_Grid[X][Y] = Interface.Placing_Rotation + 105;
		} else {
			Data.Visual_Grid[X][Y] = Interface.Placing_Rotation + 109;
		}
		std::vector<Point> Nodes = Return_Nodes(X, Y,
			0, Preconfigurations.I_Inputs);
		for (int Counter = 0; Counter < 2; Counter++) {
			Nodes.push_back(Return_Nodes(X, Y, 0,
				Preconfigurations.I_Outputs)[Counter]);
		}
		for (int Counter = 0; Counter < 4; Counter++) {
			Data.Plumbing_Grid[Nodes[Counter].X][
				Nodes[Counter].Y] = Counter + 1;
		}
		Nodes = Return_Nodes(X, Y, Interface.Placing_Rotation,
			Preconfigurations.I_Inputs);
		for (int Counter1 = 0; Counter1 < 2; Counter1++) {
			if (Counter1 == 1) {
				Nodes = Return_Nodes(X, Y, Interface.Placing_Rotation,
					Preconfigurations.I_Outputs);
			}
			for (int Counter2 = 0; Counter2 < 2; Counter2++) {
				if (Interface.Placing_Item - 1 == R_Intersection) {
					Data.Data_Grid[Nodes[Counter2].X][
						Nodes[Counter2].Y][Fluid_Cap] = LDE_REINFORCEDCAP;
				} else {
					Data.Data_Grid[Nodes[Counter2].X][
						Nodes[Counter2].Y][Fluid_Cap] = LDE_LARGECAP;
				}
				Data.Settings_Grid[Nodes[Counter2].X][
					Nodes[Counter2].Y][0] = Counter1 + 1;
			}
		}
	} else {
		return false;
	}
	return true;
}