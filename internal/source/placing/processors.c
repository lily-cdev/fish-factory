#include <grid.h>

bool Place_Filtration_Plant(int X, int Y) {
	if (Check_Clearance(X, Y, 2, 3)) {
		Fill_Clearance(LDE_INVALID, X, Y, 2, 3);
		Data.Visual_Grid[X][Y] = 22;
		Data.Plumbing_Grid[X][Y + 1] = Left;
		Data.Plumbing_Grid[X + 1][Y] = Right;
		Data.Plumbing_Grid[X + 1][Y + 1] = Right;
		Data.Plumbing_Grid[X + 1][Y + 2] = Right;
		Data.Wiring_Grid[X][Y] = F_In;
		Data.Data_Grid[X][Y][Power_Cap] = 95;
		Data.Data_Grid[X][Y][4] = 5;
		Data.Data_Grid[X][Y][5] = 12;
		Data.Data_Grid[X][Y][6] = 100;
		Data.Data_Grid[X][Y + 1][Fluid_Cap] = 16;
		Data.Data_Grid[X + 1][Y][Fluid_Cap] = 12;
		for (int C1 = 1; C1 < 3; C1++) {
			Data.Data_Grid[X + 1][Y + C1][Fluid_Cap] = 4;
			Data.Settings_Grid[X + 1][Y + C1][0] = 2;
		}
		Data.Settings_Grid[X][Y + 1][0] = 1;
		Data.Settings_Grid[X + 1][Y][0] = 2;
	} else {
		return false;
	}
	return true;
}

bool Place_Distillery(int X, int Y) {
    if (Check_Clearance(X, Y, 2, 2)) {
		Fill_Clearance(LDE_INVALID, X, Y, 2, 2);
		Data.Visual_Grid[X][Y] = (Interface.Rotation == 0) ? 41 : Interface.Rotation + 116;
		Data.Data_Grid[X][Y][5] = 24;
		Data.Data_Grid[X][Y][6] = 56;
		if (Interface.Rotation == 2 || Interface.Rotation == 3) {
			Data.Data_Grid[X][Y][5] = 56;
		}
		if (Interface.Rotation == 1 || Interface.Rotation == 2) {
			Data.Data_Grid[X][Y][6] = 24;
		}
		Data.Wiring_Grid[X][Y] = F_In;
		Data.Data_Grid[X][Y][Power_Cap] = 2500;
		Data.Animation_Grid[X][Y][0] = 0;
		Node Nodes = { };
		Return_Nodes(&Nodes, X, Y, Interface.Rotation, Preconfigs.D_Inputs);
		for (int C1 = 0; C1 < Nodes.Length; C1++) {
			Data.Settings_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y][0] = 1;
			Data.Data_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y][Fluid_Cap] = 6;
			Data.Plumbing_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y] = Interface.Rotation + Left;
		}
		Return_Nodes(&Nodes, X, Y, Interface.Rotation, Preconfigs.D_Outputs);
		for (int C1 = 0; C1 < Nodes.Length; C1++) {
			Data.Settings_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y][0] = 2;
			Data.Data_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y][Fluid_Cap] = 4;
			Data.Plumbing_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y] = (Interface.Rotation + Right == 4) ? 4 :
				((Interface.Rotation + Right) & 3);
		}
		free_c(Nodes.Data);
	} else {
		return false;
	}
    return true;
}

bool Place_Electrolytic_Cell(int X, int Y) {
	bool Placed = false;
	if (evn(Interface.Rotation)) {
		if (Check_Clearance(X, Y, 3, 2)) {
			Fill_Clearance(LDE_INVALID, X, Y, 3, 2);
			for (int C1 = 0; C1 < 3; C1++) {
				Data.Data_Grid[X + C1][(int)(Interface.Rotation * 0.5) + Y][Fluid_Cap] = 20;
				Data.Plumbing_Grid[X + C1][(int)(Interface.Rotation * 0.5) + Y] = Interface.Rotation + Up;
				Data.Settings_Grid[X + C1][(int)(Interface.Rotation * 0.5) + Y][0] = 2;
			}
			Data.Data_Grid[X + 1][Y - (int)(Interface.Rotation * 0.5) + 1][Fluid_Cap] = 16;
			Data.Plumbing_Grid[X + 1][Y - (int)(Interface.Rotation * 0.5) + 1] = Down - Interface.Rotation;
			Data.Settings_Grid[X + 1][Y - (int)(Interface.Rotation * 0.5) + 1][0] = 1;
			if (Interface.Rotation == 0) {
				Data.Data_Grid[X][Y][5] = 44;
				Data.Data_Grid[X][Y][6] = 67;
			} else {
				Data.Data_Grid[X][Y][5] = 76;
				Data.Data_Grid[X][Y][6] = 13;
			}
			Placed = true;
		}
	} else {
		if (Check_Clearance(X, Y, 2, 3)) {
			Fill_Clearance(LDE_INVALID, X, Y, 2, 3);
			for (int C1 = 0; C1 < 3; C1++) {
				Data.Data_Grid[X - (int)((Interface.Rotation - 1) * 0.5) + 1][Y + C1][Fluid_Cap] = 20;
				Data.Plumbing_Grid[X - (int)((Interface.Rotation - 1) * 0.5) + 1][Y + C1] = Right - (Interface.Rotation -
					1);
				Data.Settings_Grid[X - (int)((Interface.Rotation - 1) * 0.5) + 1][Y + C1][0] = 2;
			}
			Data.Data_Grid[X + (int)((Interface.Rotation - 1) * 0.5)][Y + 1][Fluid_Cap] = 16;
			Data.Plumbing_Grid[X + (int)((Interface.Rotation - 1) * 0.5)][Y + 1] = (Interface.Rotation - 1) + Left;
			Data.Settings_Grid[X + (int)((Interface.Rotation - 1) * 0.5)][Y + 1][0] = 1;
			if (Interface.Rotation == 1) {
				Data.Data_Grid[X][Y][5] = 13;
				Data.Data_Grid[X][Y][6] = 44;
			} else {
				Data.Data_Grid[X][Y][5] = 67;
				Data.Data_Grid[X][Y][6] = 76;
			}
			Placed = true;
		}							
	}
	if (Placed) {
		Data.Data_Grid[X][Y][Power_Cap] = 70000;
		Data.Wiring_Grid[X][Y] = F_In;
		Data.Visual_Grid[X][Y] = (Interface.Rotation == 0) ? 48 : Interface.Rotation + 95;
	} else {
		return false;
	}
	return true;
}

bool Place_Fluid_Mixer(int X, int Y) {
	if (Check_Clearance(X, Y, 3, 3)) {
		Fill_Clearance(LDE_INVALID, X, Y, 3, 3);
		Node Nodes = { };
		Return_Nodes(&Nodes, X, Y, Interface.Rotation, Preconfigs.FM_Inputs);
		for (int C1 = 0; C1 < Nodes.Length; C1++) {
			int Orientation = (int)(floor(C1 / 3.0f) * 2) + Left;
			Orientation -= Interface.Rotation;
			Orientation = ((Orientation + 3) & 3) + 1;
			Data.Data_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y][Fluid_Cap] = 24;
			Data.Settings_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y][0] = F_In;
			Data.Plumbing_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y] = Orientation;
		}
		Return_Nodes(&Nodes, X, Y, Interface.Rotation, Preconfigs.FM_Outputs);
		for (int C1 = 0; C1 < Nodes.Length; C1++) {
			int Orientation = (C1 * 2) + Up;
			Orientation -= Interface.Rotation;
			Orientation = ((Orientation + 3) & 3) + 1;
			Data.Data_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y][Fluid_Cap] = 36;
			Data.Settings_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y][0] = F_Out;
			Data.Plumbing_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y] = Orientation;
		}
		Data.Visual_Grid[X][Y] = (Interface.Rotation == 0) ? 49 : Interface.Rotation + 98;
		Data.Animation_Grid[X][Y][1] = 0;
		Data.Data_Grid[X][Y][Power_Cap] = 800;
		Data.Wiring_Grid[X][Y] = F_In;
		Data.Data_Grid[X][Y][5] = 60;
		Data.Data_Grid[X][Y][6] = 60;
		free_c(Nodes.Data);
	} else {
		return false;
	}
	return true;
}

bool Place_Condenser_Input(int X, int Y) {
	return true;
}

bool Place_Condenser_Transferor(int X, int Y) {
	return true;
}

bool Place_Condenser_Heatsink(int X, int Y) {
	return true;
}

bool Place_Condenser_Output(int X, int Y) {
	return true;
}