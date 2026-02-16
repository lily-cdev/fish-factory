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
		Point Location = { X, Y };
		Push_Docks(Location);
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
		Data.Visual_Grid[X][Y] = Interface.Rotation + ((Interface.Item - 1 == R_Intersection) ? 105 : 109);
		Node Nodes = { };
		Return_Nodes(&Nodes, X, Y, 0, Preconfigs.I_Inputs);
		for (int C1 = 0; C1 < 2; C1++) {
			Data.Plumbing_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y] = C1 + 1;
		}
		Return_Nodes(&Nodes, X, Y, 0, Preconfigs.I_Outputs);
		for (int C1 = 0; C1 < 2; C1++) {
			Data.Plumbing_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y] = C1 + 3;
		}
		for (int C1 = 0; C1 < 2; C1++) {
			if (C1 == 1) {
				Return_Nodes(&Nodes, X, Y, Interface.Rotation, Preconfigs.I_Outputs);
			} else {
				Return_Nodes(&Nodes, X, Y, Interface.Rotation, Preconfigs.I_Inputs);
			}
			for (int C2 = 0; C2 < 2; C2++) {
				Data.Data_Grid[Nodes.Data[C2].X][Nodes.Data[C2].Y][Fluid_Cap] = (Interface.Item - 1 == R_Intersection) ?
					LDE_REINFORCEDCAP : LDE_LARGECAP;
				Data.Settings_Grid[Nodes.Data[C2].X][Nodes.Data[C2].Y][0] = C1 + 1;
			}
		}
		free_c(Nodes.Data);
	} else {
		return false;
	}
	return true;
}