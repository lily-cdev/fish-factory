#include <grid.h>

bool Place_RTG(int X, int Y) {
	Data.Visual_Grid[X][Y] = 19;
	Data.Data_Grid[X][Y][Power_Cap] = 5;
	Data.Data_Grid[X][Y][5] = 20;
	Data.Data_Grid[X][Y][6] = 20;
	Data.Wiring_Grid[X][Y] = 1;
	return true;
}

bool Place_Bio_Generator(int X, int Y) {
    if (Check_Clearance(X, Y, 3, 3)) {
		Fill_Clearance(LDE_INVALID, X, Y, 3, 3);
		Data.Visual_Grid[X][Y] = (Interface.Rotation == 0) ? 23 : Interface.Rotation + 101;
		Data.Animation_Grid[X][Y][1] = 45;
		Data.Wiring_Grid[X][Y] = 1;
		Data.Data_Grid[X][Y][Power_Cap] = 9500;
		Data.Data_Grid[X][Y][5] = 60;
		Data.Data_Grid[X][Y][6] = 60;
		Node Nodes;
		Return_Nodes(&Nodes, X, Y, Interface.Rotation, Preconfigs.BG_Inputs);
		Data.Data_Grid[Nodes.Data[0].X][Nodes.Data[0].Y][1] = 4;
		Data.Settings_Grid[Nodes.Data[0].X][Nodes.Data[0].Y][0] = 1;
		int Orientation = Interface.Rotation + Down;
		Orientation = ((Orientation + 3) & 3) + 1;
		Data.Plumbing_Grid[Nodes.Data[0].X][Nodes.Data[0].Y] = Orientation;
		free_c(Nodes.Data);
	} else {
		return false;
	}
	return true;
}

bool Place_Geo_Well(int X, int Y) {
	bool Placed = false;
	if (evn_i(Interface.Rotation)) {
		if (Check_Clearance(X, Y, 2, 3)) {
			Fill_Clearance(LDE_INVALID, X, Y, 2, 3);
			Placed = true;
			Data.Data_Grid[X][Y][6] = 60;
			for (int C1 = 0; C1 < 2; C1++) {
				if (Interface.Rotation == C1 * 2) {
					Data.Data_Grid[X + C1][Y][Fluid_Cap] = 10;
					Data.Data_Grid[X + C1][Y + 2][Fluid_Cap] = 10;
					Data.Settings_Grid[X + C1][Y][0] = 2 - C1;
					Data.Settings_Grid[X + C1][Y + 2][0] = C1 + 1;
					Data.Plumbing_Grid[X + C1][Y] = Up;
					Data.Plumbing_Grid[X + C1][Y + 2] = Down;
					Data.Data_Grid[X][Y][5] = abs((C1 * 80) - 28);
				}
			}
		}
	} else {
		if (Check_Clearance(X, Y, 3, 2)) {
			Fill_Clearance(LDE_INVALID, X, Y, 3, 2);
			Placed = true;
			Data.Data_Grid[X][Y][5] = 60;
			for (int C1 = 0; C1 < 2; C1++) {
				if (Interface.Rotation == (C1 * 2) + 1) {
					Data.Data_Grid[X][Y + C1][Fluid_Cap] = 10;
					Data.Data_Grid[X + 2][Y + C1][Fluid_Cap] = 10;
					Data.Settings_Grid[X][Y + C1][0] = 2 - C1;
					Data.Settings_Grid[X + 2][Y + C1][0] = C1 + 1;
					Data.Plumbing_Grid[X][Y + C1] = Left;
					Data.Plumbing_Grid[X + 2][Y + C1] = Right;
					Data.Data_Grid[X][Y][6] = abs((C1 * 80) - 28);
				}
			}
		}
	}
	if (Placed) {
		Data.Visual_Grid[X][Y] = Interface.Rotation + 67;
		Data.Data_Grid[X][Y][Power_Cap] = 3000;
		Data.Wiring_Grid[X][Y] = 0;
	} else {
		return false;
	}
	return true;
}

bool Place_Heat_Exchanger(int X, int Y) {
	bool Placed = false;
	if (evn_i(Interface.Rotation)) {
		if (Check_Clearance(X, Y, 4, 3)) {
			Fill_Clearance(LDE_INVALID, X, Y, 4, 3);
			Placed = true;
			for (int C1 = 0; C1 < 2; C1++) {
				for (int C2 = 0; C2 < 2; C2++) {
					Data.Plumbing_Grid[X + (C2 * 3)][Y + (C1 * 2)] = Up + (C1 * 2);
					Data.Data_Grid[X + (C2 * 3)][Y + (C1 * 2)][Fluid_Cap] = 300;
					Data.Settings_Grid[X + (C2 * 3)][Y][0] = 2 - (Interface.Rotation * 0.5);
					Data.Settings_Grid[X + (C2 * 3)][Y + 2][0] = 1 + (Interface.Rotation * 0.5);
				}
			}
		}
	} else {
		if (Check_Clearance(X, Y, 3, 4)) {
			Fill_Clearance(LDE_INVALID, X, Y, 3, 4);
			Placed = true;
			for (int C1 = 0; C1 < 2; C1++) {
				for (int C2 = 0; C2 < 2; C2++) {
					Data.Plumbing_Grid[X + (C1 * 2)][Y + (C2 * 3)] = (C1 * 2) + Left;
					Data.Data_Grid[(C1 * 2) + X][Y + (C2 * 3)][Fluid_Cap] = 300;
					Data.Settings_Grid[X][(C2 * 3) + Y][0] = (Interface.Rotation * 0.5) + 1;
					Data.Settings_Grid[X + 2][(C2 * 3) + Y][0] = 2 - (Interface.Rotation * 0.5);
				}
			}
		}
	}
	if (Placed) {
		Data.Visual_Grid[X][Y] = Interface.Rotation + 87;
		for (int C1 = 0; C1 < 4; C1++) {
			Data.Settings_Grid[X][Y][C1 + 3] = 0;
		}
		for (int C1 = 0; C1 < 2; C1++) {
			Data.Settings_Grid[X][Y][C1 + 7] = LDE_ROOMTEMP;
		}
		for (int C1 = 0; C1 < 2; C1++) {
			Data.Settings_Grid[X][Y][C1 + 9] = LDE_INVALID;
		}
	} else {
		return false;
	}
	return true;
}

bool Place_Turbine_Input(int X, int Y) {
	bool Placed = false;
	if (Check_Clearance(X, Y, 2, 3) && evn_i(Interface.Rotation)) {
		Fill_Clearance(LDE_INVALID, X, Y, 2, 3);
		Placed = true;
	} else if (Check_Clearance(X, Y, 3, 2) && !evn_i(Interface.Rotation)) {
		Fill_Clearance(LDE_INVALID, X, Y, 3, 2);
		Placed = true;
	}
	if (Placed) {
		Data.Visual_Grid[X][Y] = Interface.Rotation + 120;
		Node Nodes;
		Return_Nodes(&Nodes, X, Y, Interface.Rotation, Preconfigs.STI_Inputs);
		Data.Settings_Grid[Interface.Tile.X][Interface.Tile.Y][3] = 0;
		Data.Settings_Grid[Interface.Tile.X][Interface.Tile.Y][4] = 0;
		Data.Data_Grid[Nodes.Data[0].X][Nodes.Data[0].Y][Fluid_Cap] = LDE_LARGECAP;
		Data.Settings_Grid[Nodes.Data[0].X][Nodes.Data[0].Y][0] = F_In;
		Data.Plumbing_Grid[Nodes.Data[0].X][Nodes.Data[0].Y] = Interface.Rotation + Left;
		free_c(Nodes.Data);
	} else {
		return false;
	}
	return true;
}

bool Place_Turbine_Impulse(int X, int Y) {
	bool Placed = false;
	if (Check_Clearance(X, Y, 2, 3) && evn_i(Interface.Rotation)) {
		Fill_Clearance(LDE_INVALID, X, Y, 2, 3);
		Placed = true;
	} else if (Check_Clearance(X, Y, 3, 2) && !evn_i(Interface.Rotation)) {
		Fill_Clearance(LDE_INVALID, X, Y, 3, 2);
		Placed = true;
	}
	if (Placed) {
		Data.Visual_Grid[X][Y] = Interface.Rotation + 124;
		Data.Settings_Grid[X][Y][3] = 0;
	} else {
		return false;
	}
	return true;
}

bool Place_Turbine_Output(int X, int Y) {
	if (Check_Clearance(X, Y, 2, 2)) {
		Fill_Clearance(LDE_INVALID, X, Y, 2, 2);
		Data.Visual_Grid[X][Y] = Interface.Rotation + 128;
		Node Nodes;
		Return_Nodes(&Nodes, X, Y, Interface.Rotation, Preconfigs.STO_Outputs);
		Data.Data_Grid[Nodes.Data[0].X][Nodes.Data[0].Y][Fluid_Cap] = LDE_LARGECAP;
		Data.Settings_Grid[Nodes.Data[0].X][Nodes.Data[0].Y][0] = F_Out;
		Data.Plumbing_Grid[Nodes.Data[0].X][Nodes.Data[0].Y] = Interface.Rotation + Left;
		//do outputZ!
		free_c(Nodes.Data);
	} else {
		Data.Settings_Grid[X][Y][3] = 0;
		return false;
	}
	return true;
}