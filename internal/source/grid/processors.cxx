#include <grid.h>

bool Place_Filtration_Plant(int X, int Y) {
	if (Check_Clearance(X, Y, 2, 3)) {
		Fill_Clearance(LDE_INVALID, X, Y, 2, 3);
		Data.Visual_Grid[X][Y] = 22;
		Data.Plumbing_Grid[X][Y + 1] = Left;
		Data.Plumbing_Grid[X + 1][Y] = Right;
		Data.Plumbing_Grid[X + 1][Y + 1] = Right;
		Data.Plumbing_Grid[X + 1][Y + 2] = Right;
		Data.Wiring_Grid[X][Y] = 0;
		Data.Data_Grid[X][Y][Power_Cap] = 95;
		Data.Data_Grid[X][Y][4] = 5;
		Data.Data_Grid[X][Y][5] = 12;
		Data.Data_Grid[X][Y][6] = 100;
		Data.Data_Grid[X][Y + 1][Fluid_Cap] = 16;
		Data.Data_Grid[X + 1][Y][Fluid_Cap] = 12;
		for (int Counter = 1; Counter < 3; Counter++) {
			Data.Data_Grid[X + 1][Y + Counter][Fluid_Cap] = 4;
			Data.Settings_Grid[X + 1][Y + Counter][0] = 2;
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
		if (Interface.Placing_Rotation == 0) {
			Data.Visual_Grid[X][Y] = 41;
		} else {
			Data.Visual_Grid[X][Y] =
				Interface.Placing_Rotation + 116;
		}
		Data.Data_Grid[X][Y][5] = 24;
		Data.Data_Grid[X][Y][6] = 56;
		if (Interface.Placing_Rotation == 2 || Interface.Placing_Rotation == 3) {
			Data.Data_Grid[X][Y][5] = 56;
		}
		if (Interface.Placing_Rotation == 1 || Interface.Placing_Rotation == 2) {
			Data.Data_Grid[X][Y][6] = 24;
		}
		Data.Wiring_Grid[X][Y] = 0;
		Data.Data_Grid[X][Y][Power_Cap] = 2500;
		Data.Animation_Grid[X][Y][0] = 0;
		std::vector<Point> Nodes = Return_Nodes(X, Y, Interface.Placing_Rotation,
			Preconfigurations.D_Inputs);
		for (int Counter = 0; Counter < Nodes.size(); Counter++) {
			Data.Settings_Grid[Nodes[Counter].X][Nodes[Counter].Y][0] = 1;
			Data.Data_Grid[Nodes[Counter].X][Nodes[Counter].Y][Fluid_Cap] = 6;
			Data.Plumbing_Grid[Nodes[Counter].X][Nodes[Counter].Y] =
				Interface.Placing_Rotation + Left;
		}
		Nodes = Return_Nodes(X, Y, Interface.Placing_Rotation,
			Preconfigurations.D_Outputs);
		for (int Counter = 0; Counter < Nodes.size(); Counter++) {
			Data.Settings_Grid[Nodes[Counter].X][Nodes[Counter].Y][0] = 2;
			Data.Data_Grid[Nodes[Counter].X][Nodes[Counter].Y][Fluid_Cap] = 4;
			Data.Plumbing_Grid[Nodes[Counter].X][Nodes[Counter].Y] =
				(Interface.Placing_Rotation + Right == 4) ? 4 :
				((Interface.Placing_Rotation + Right) & 3);
		}
	} else {
		return false;
	}
    return true;
}

bool Place_Electrolytic_Cell(int X, int Y) {
	bool Placed = false;
	if (evn_i(Interface.Placing_Rotation)) {
		if (Check_Clearance(X, Y, 3, 2)) {
			Fill_Clearance(LDE_INVALID, X, Y, 3, 2);
			for (int Counter = 0; Counter < 3; Counter++) {
				Data.Data_Grid[X + Counter][static_cast<int>(
					Interface.Placing_Rotation * 0.5) + Y][Fluid_Cap] = 20;
				Data.Plumbing_Grid[X + Counter][static_cast<int>(
					Interface.Placing_Rotation * 0.5) + Y] = Interface.Placing_Rotation + Up;
				Data.Settings_Grid[X + Counter][static_cast<int>(
					Interface.Placing_Rotation * 0.5) + Y][0] = 2;
			}
			Data.Data_Grid[X + 1][Y - static_cast<int>
				(Interface.Placing_Rotation * 0.5) + 1][Fluid_Cap] = 16;
			Data.Plumbing_Grid[X + 1][Y - static_cast<int>
				(Interface.Placing_Rotation * 0.5) + 1] = Down - Interface.Placing_Rotation;
			Data.Settings_Grid[X + 1][Y - static_cast<int>
				(Interface.Placing_Rotation * 0.5) + 1][0] = 1;
			if (Interface.Placing_Rotation == 0) {
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
			for (int Counter = 0; Counter < 3; Counter++) {
				Data.Data_Grid[X - static_cast<int>(
					(Interface.Placing_Rotation - 1) * 0.5) +
					1][Y + Counter][Fluid_Cap] = 20;
				Data.Plumbing_Grid[X - static_cast<int>(
					(Interface.Placing_Rotation - 1) * 0.5) + 1][Y +
					Counter] = Right - (Interface.Placing_Rotation - 1);
				Data.Settings_Grid[X - static_cast<int>(
					(Interface.Placing_Rotation - 1) * 0.5) + 1][Y + Counter][0] = 2;
			}
			Data.Data_Grid[X + static_cast<int>((Interface
				.Placing_Rotation - 1) * 0.5)][Y + 1][Fluid_Cap] = 16;
			Data.Plumbing_Grid[X + static_cast<int>((Interface.Placing_Rotation -
				1) * 0.5)][Y + 1] = (Interface.Placing_Rotation - 1) + Left;
			Data.Settings_Grid[X + static_cast<int>((Interface.Placing_Rotation -
				1) * 0.5)][Y + 1][0] = 1;
			if (Interface.Placing_Rotation == 1) {
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
		Data.Wiring_Grid[X][Y] = 0;
		if (Interface.Placing_Rotation == 0) {
			Data.Visual_Grid[X][Y] = 48;
		} else {
			Data.Visual_Grid[X][Y] = Interface.Placing_Rotation + 95;
		}
	} else {
		return false;
	}
	return true;
}

bool Place_Fluid_Mixer(int X, int Y) {
	if (Check_Clearance(X, Y, 3, 3)) {
		Fill_Clearance(LDE_INVALID, X, Y, 3, 3);
		std::vector<Point> Nodes = Return_Nodes(X, Y, Interface.Placing_Rotation,
			Preconfigurations.FM_Inputs);
		for (int Counter = 0; Counter < Nodes.size(); Counter++) {
			int Orientation = static_cast<int>(std::floor(Counter / 3.0f) * 2) + Left;
			Orientation -= Interface.Placing_Rotation;
			Orientation = ((Orientation + 3) & 3) + 1;
			Data.Data_Grid[Nodes[Counter].X][Nodes[Counter].Y][Fluid_Cap] = 24;
			Data.Settings_Grid[Nodes[Counter].X][Nodes[Counter].Y][0] = F_In;
			Data.Plumbing_Grid[Nodes[Counter].X][Nodes[Counter].Y] = Orientation;
		}
		Nodes = Return_Nodes(X, Y, Interface.Placing_Rotation,
			Preconfigurations.FM_Outputs);
		for (int Counter = 0; Counter < Nodes.size(); Counter++) {
			int Orientation = (Counter * 2) + Up;
			Orientation -= Interface.Placing_Rotation;
			Orientation = ((Orientation + 3) & 3) + 1;
			Data.Data_Grid[Nodes[Counter].X][Nodes[Counter].Y][Fluid_Cap] = 36;
			Data.Settings_Grid[Nodes[Counter].X][Nodes[Counter].Y][0] = F_Out;
			Data.Plumbing_Grid[Nodes[Counter].X][Nodes[Counter].Y] = Orientation;
		}
		if (Interface.Placing_Rotation == 0) {
			Data.Visual_Grid[X][Y] = 49;
		} else {
			Data.Visual_Grid[X][Y] = Interface.Placing_Rotation + 98;
		}
		Data.Animation_Grid[X][Y][1] = 0;
		Data.Data_Grid[X][Y][Power_Cap] = 800;
		Data.Wiring_Grid[X][Y] = 0;
		Data.Data_Grid[X][Y][5] = 60;
		Data.Data_Grid[X][Y][6] = 60;
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