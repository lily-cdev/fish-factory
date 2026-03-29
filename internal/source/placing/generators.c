#include <grid.h>

bool Place_RTG(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = (Interface.Rotation == 0) ? 19 : Interface.Rotation + 134;
	Data.Data_Grid[pt(Pos)][Power_Cap] = 5;
	Data.Data_Grid[pt(Pos)][5] = 20;
	Data.Data_Grid[pt(Pos)][6] = 20;
	Data.Wiring_Grid[pt(Pos)] = F_Out;
	return true;
}

bool Place_Bio_Generator(Point Pos) {
    if (Check_Clearance(Pos, 3, 3)) {
		Fill_Clearance(LDE_INVALID, Pos, 3, 3);
		Data.Visual_Grid[pt(Pos)] = (Interface.Rotation == 0) ? 23 : Interface.Rotation + 101;
		Data.Animation_Grid[pt(Pos)][1] = 45;
		Data.Wiring_Grid[pt(Pos)] = F_Out;
		Data.Data_Grid[pt(Pos)][Power_Cap] = 9500;
		Data.Data_Grid[pt(Pos)][5] = 60;
		Data.Data_Grid[pt(Pos)][6] = 60;
		Node Nodes = { };
		Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.BG_Inputs);
		Data.Data_Grid[pt(Nodes.Data[0])][1] = 4;
		Data.Settings_Grid[pt(Nodes.Data[0])][0] = 1;
		int Orientation = Interface.Rotation + Down;
		Orientation = ((Orientation + 3) & 3) + 1;
		Data.Plumbing_Grid[pt(Nodes.Data[0])] = Orientation;
		free_c(Nodes.Data);
	} else {
		return false;
	}
	return true;
}

bool Place_Geo_Well(Point Pos) {
	bool Placed = false;
	if (evn(Interface.Rotation)) {
		if (Check_Clearance(Pos, 2, 3)) {
			Fill_Clearance(LDE_INVALID, Pos, 2, 3);
			Placed = true;
			Data.Data_Grid[pt(Pos)][6] = 60;
			for (int C1 = 0; C1 < 2; C1++) {
				if (Interface.Rotation == C1 * 2) {
					Data.Data_Grid[Pos.X + C1][Pos.Y][Fluid_Cap] = 10;
					Data.Data_Grid[Pos.X + C1][Pos.Y + 2][Fluid_Cap] = 10;
					Data.Settings_Grid[Pos.X + C1][Pos.Y][0] = 2 - C1;
					Data.Settings_Grid[Pos.X + C1][Pos.Y + 2][0] = C1 + 1;
					Data.Plumbing_Grid[Pos.X + C1][Pos.Y] = Up;
					Data.Plumbing_Grid[Pos.X + C1][Pos.Y + 2] = Down;
					Data.Data_Grid[pt(Pos)][5] = abs((C1 * 80) - 28);
				}
			}
		}
	} else {
		if (Check_Clearance(Pos, 3, 2)) {
			Fill_Clearance(LDE_INVALID, Pos, 3, 2);
			Placed = true;
			Data.Data_Grid[pt(Pos)][5] = 60;
			for (int C1 = 0; C1 < 2; C1++) {
				if (Interface.Rotation == (C1 * 2) + 1) {
					Data.Data_Grid[Pos.X][Pos.Y + C1][Fluid_Cap] = 10;
					Data.Data_Grid[Pos.X + 2][Pos.Y + C1][Fluid_Cap] = 10;
					Data.Settings_Grid[Pos.X][Pos.Y + C1][0] = 2 - C1;
					Data.Settings_Grid[Pos.X + 2][Pos.Y + C1][0] = C1 + 1;
					Data.Plumbing_Grid[Pos.X][Pos.Y + C1] = Left;
					Data.Plumbing_Grid[Pos.X + 2][Pos.Y + C1] = Right;
					Data.Data_Grid[pt(Pos)][6] = abs((C1 * 80) - 28);
				}
			}
		}
	}
	if (Placed) {
		Data.Visual_Grid[pt(Pos)] = Interface.Rotation + 67;
		Data.Data_Grid[pt(Pos)][Power_Cap] = 3000;
		Data.Wiring_Grid[pt(Pos)] = F_In;
	} else {
		return false;
	}
	return true;
}

bool Place_Heat_Exchanger(Point Pos) {
	bool Placed = false;
	if (evn(Interface.Rotation)) {
		if (Check_Clearance(Pos, 4, 3)) {
			Fill_Clearance(LDE_INVALID, Pos, 4, 3);
			Placed = true;
			for (int C1 = 0; C1 < 2; C1++) {
				for (int C2 = 0; C2 < 2; C2++) {
					Data.Plumbing_Grid[(C2 * 3) + Pos.X][(C1 * 2) + Pos.Y] = Up + (C1 * 2);
					Data.Data_Grid[(C2 * 3) + Pos.X][(C1 * 2) + Pos.Y][Fluid_Cap] = 300;
					Data.Settings_Grid[(C2 * 3) + Pos.X][Pos.Y][0] = 2 - (Interface.Rotation * 0.5);
					Data.Settings_Grid[(C2 * 3) + Pos.X][Pos.Y + 2][0] = 1 + (Interface.Rotation * 0.5);
				}
			}
		}
	} else {
		if (Check_Clearance(Pos, 3, 4)) {
			Fill_Clearance(LDE_INVALID, Pos, 3, 4);
			Placed = true;
			for (int C1 = 0; C1 < 2; C1++) {
				for (int C2 = 0; C2 < 2; C2++) {
					Data.Plumbing_Grid[(C1 * 2) + Pos.X][Pos.Y + (C2 * 3)] = (C1 * 2) + Left;
					Data.Data_Grid[(C1 * 2) + Pos.X][Pos.Y + (C2 * 3)][Fluid_Cap] = 300;
					Data.Settings_Grid[Pos.X][(C2 * 3) + Pos.Y][0] = (Interface.Rotation * 0.5) + 1;
					Data.Settings_Grid[Pos.X + 2][(C2 * 3) + Pos.Y][0] = 2 - (Interface.Rotation * 0.5);
				}
			}
		}
	}
	if (Placed) {
		Data.Visual_Grid[pt(Pos)] = Interface.Rotation + 87;
		for (int C1 = 0; C1 < 4; C1++) {
			Data.Settings_Grid[pt(Pos)][C1 + 3] = 0;
		}
		for (int C1 = 0; C1 < 2; C1++) {
			Data.Settings_Grid[pt(Pos)][C1 + 7] = LDE_ROOMTEMP;
		}
		for (int C1 = 0; C1 < 2; C1++) {
			Data.Settings_Grid[pt(Pos)][C1 + 9] = LDE_INVALID;
		}
	} else {
		return false;
	}
	return true;
}

bool Place_Turbine_Input(Point Pos) {
	bool Placed = false;
	if (Check_Clearance(Pos, 2, 3) && evn(Interface.Rotation)) {
		Fill_Clearance(LDE_INVALID, Pos, 2, 3);
		Placed = true;
	} else if (Check_Clearance(Pos, 3, 2) && !evn(Interface.Rotation)) {
		Fill_Clearance(LDE_INVALID, Pos, 3, 2);
		Placed = true;
	}
	if (Placed) {
		Data.Visual_Grid[pt(Pos)] = Interface.Rotation + 120;
		Node Nodes = { };
		Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.STI_Inputs);
		Data.Settings_Grid[pt(Interface.Tile)][3] = 0;
		Data.Settings_Grid[pt(Interface.Tile)][4] = 0;
		Data.Data_Grid[pt(Nodes.Data[0])][Fluid_Cap] = LDE_LARGECAP;
		Data.Settings_Grid[pt(Nodes.Data[0])][0] = F_In;
		Data.Plumbing_Grid[pt(Nodes.Data[0])] = Interface.Rotation + Left;
		free_c(Nodes.Data);
	} else {
		return false;
	}
	return true;
}

bool Place_Turbine_Impulse(Point Pos) {
	bool Placed = false;
	if (Check_Clearance(Pos, 2, 3) && evn(Interface.Rotation)) {
		Fill_Clearance(LDE_INVALID, Pos, 2, 3);
		Placed = true;
	} else if (Check_Clearance(Pos, 3, 2) && !evn(Interface.Rotation)) {
		Fill_Clearance(LDE_INVALID, Pos, 3, 2);
		Placed = true;
	}
	if (Placed) {
		Data.Visual_Grid[pt(Pos)] = Interface.Rotation + 124;
		Data.Settings_Grid[pt(Pos)][3] = 0;
	} else {
		return false;
	}
	return true;
}

bool Place_Turbine_Output(Point Pos) {
	if (Check_Clearance(Pos, 2, 2)) {
		Fill_Clearance(LDE_INVALID, Pos, 2, 2);
		Data.Visual_Grid[pt(Pos)] = Interface.Rotation + 128;
		Node Nodes = { };
		Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.STO_Outputs);
		Data.Data_Grid[pt(Nodes.Data[0])][Fluid_Cap] = LDE_LARGECAP;
		Data.Settings_Grid[pt(Nodes.Data[0])][0] = F_Out;
		Data.Plumbing_Grid[pt(Nodes.Data[0])] = Interface.Rotation + Left;
		//do outputZ!
		free_c(Nodes.Data);
	} else {
		Data.Settings_Grid[pt(Pos)][3] = 0;
		return false;
	}
	return true;
}