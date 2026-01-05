#include <grid.h>

bool Place_Algae_Bed(int X, int Y) {
    bool Placed = false;
	if (evn_i(Interface.Placing_Rotation)) {
		if (Check_Clearance(X, Y, 2, 3)) {
			Fill_Clearance(LDE_INVALID, X, Y, 2, 3);
			Placed = true;
			Data.Data_Grid[X][Y][5] = 52;
			Data.Data_Grid[X][Y][6] = 32;
			if (Interface.Placing_Rotation == 0) {
				Data.Data_Grid[X][Y][5] = 28;
				Data.Data_Grid[X][Y][6] = 88;
			}
		}
	} else {
		if (Check_Clearance(X, Y, 3, 2)) {
			Fill_Clearance(LDE_INVALID, X, Y, 3, 2);
			Placed = true;
			Data.Data_Grid[X][Y][5] = 88;
			Data.Data_Grid[X][Y][6] = 52;
			if (Interface.Placing_Rotation == 1) {
				Data.Data_Grid[X][Y][5] = 32;
				Data.Data_Grid[X][Y][6] = 28;
			}
		}
	}
	if (Placed) {
		Node Nodes;
		Return_Nodes(Nodes, X, Y, Interface.Placing_Rotation, Preconfigs.GB_Outputs);
		for (int Counter = 0; Counter < Nodes.Length; Counter++) {
			Data.Settings_Grid[Nodes.Data[Counter].X][Nodes.Data[Counter].Y][0] = F_Out;
			Data.Data_Grid[Nodes.Data[Counter].X][Nodes.Data[Counter].Y][Fluid_Cap] = 3;
			Data.Plumbing_Grid[Nodes.Data[Counter].X][Nodes.Data[Counter].Y] =
				(Interface.Placing_Rotation + Down == 4) ? 4 :
				((Interface.Placing_Rotation + Down) & 3);
		}
		if (Interface.Placing_Rotation == 0) {
			Data.Visual_Grid[X][Y] = 42;
		} else {
			Data.Visual_Grid[X][Y] =
				Interface.Placing_Rotation + 131;
		}
		Data.Wiring_Grid[X][Y] = 0;
		Data.Data_Grid[X][Y][Power_Cap] = 200;
		Free_Node(Nodes);
	} else {
		return false;
	}
	return true;
}

bool Place_Spawning_Pool(int X, int Y) {
	Data.Visual_Grid[X][Y] = 24;
	Data.Behavior_Grid[X][Y] = 0;
	return true;
}

bool Place_Spawning_Controller(int X, int Y) {
	Data.Visual_Grid[X][Y] = 45;
	Data.Settings_Grid[X][Y][4] = 0;
	Data.Settings_Grid[X][Y][5] = 0;
	Data.Settings_Grid[X][Y][6] = 0;
	Data.Settings_Grid[X][Y][7] = 0;
	Data.Behavior_Grid[X][Y] = 0;
	return true;
}

bool Place_Spawning_Output(int X, int Y) {
	Data.Visual_Grid[X][Y] = 46;
	Data.Data_Grid[X][Y][Fluid_Cap] = 50;
	Data.Plumbing_Grid[X][Y] = Down;
	Data.Behavior_Grid[X][Y] = 0;
	Data.Settings_Grid[X][Y][0] = F_Out;
	return true;
}

bool Place_Spawning_Input(int X, int Y) {
	Data.Visual_Grid[X][Y] = 47;
	Data.Data_Grid[X][Y][Fluid_Cap] = 12;
	Data.Plumbing_Grid[X][Y] = Down;
	Data.Behavior_Grid[X][Y] = 0;
	Data.Settings_Grid[X][Y][0] = F_In;
	return true;
}