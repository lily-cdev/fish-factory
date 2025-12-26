#include <grid.h>

bool Place_Piezo_Generator(int X, int Y) {
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
		if (Interface.Placing_Rotation == 0) {
			Data.Visual_Grid[X][Y] = 23;
		} else {
			Data.Visual_Grid[X][Y] = Interface.Placing_Rotation + 101;
		}
		Data.Animation_Grid[X][Y][1] = 45;
		Data.Wiring_Grid[X][Y] = 1;
		Data.Data_Grid[X][Y][Power_Cap] = 9500;
		Data.Data_Grid[X][Y][5] = 60;
		Data.Data_Grid[X][Y][6] = 60;
		std::vector<Point> Nodes = Return_Nodes(X, Y, Interface.Placing_Rotation,
			Preconfigurations.BG_Inputs);
		Data.Data_Grid[Nodes[0].X][Nodes[0].Y][1] = 4;
		Data.Settings_Grid[Nodes[0].X][Nodes[0].Y][0] = 1;
		{
			int Orientation = Interface.Placing_Rotation + Down;
			Orientation = ((Orientation + 3) & 3) + 1;
			Data.Plumbing_Grid[Nodes[0].X][Nodes[0].Y] = Orientation;
		}
	} else {
		return false;
	}
	return true;
}

bool Place_Geo_Well(int X, int Y) {
	bool Placed = false;
	if (evn_i(Interface.Placing_Rotation)) {
		if (Check_Clearance(X, Y, 2, 3)) {
			Fill_Clearance(LDE_INVALID, X, Y, 2, 3);
			Placed = true;
			Data.Data_Grid[X][Y][6] = 60;
			for (int Counter = 0; Counter < 2; Counter++) {
				if (Interface.Placing_Rotation == Counter * 2) {
					Data.Data_Grid[X + Counter][Y][Fluid_Cap] = 10;
					Data.Data_Grid[X + Counter][Y + 2][Fluid_Cap] = 10;
					Data.Settings_Grid[X + Counter][Y][0] = 2 - Counter;
					Data.Settings_Grid[X + Counter][Y + 2][0] = Counter + 1;
					Data.Plumbing_Grid[X + Counter][Y] = Up;
					Data.Plumbing_Grid[X + Counter][Y + 2] = Down;
					Data.Data_Grid[X][Y][5] = std::abs((Counter * 80) - 28);
				}
			}
		}
	} else {
		if (Check_Clearance(X, Y, 3, 2)) {
			Fill_Clearance(LDE_INVALID, X, Y, 3, 2);
			Placed = true;
			Data.Data_Grid[X][Y][5] = 60;
			for (int Counter = 0; Counter < 2; Counter++) {
				if (Interface.Placing_Rotation == (Counter * 2) + 1) {
					Data.Data_Grid[X][Y + Counter][Fluid_Cap] = 10;
					Data.Data_Grid[X + 2][Y + Counter][Fluid_Cap] = 10;
					Data.Settings_Grid[X][Y + Counter][0] = 2 - Counter;
					Data.Settings_Grid[X + 2][Y + Counter][0] = Counter + 1;
					Data.Plumbing_Grid[X][Y + Counter] = Left;
					Data.Plumbing_Grid[X + 2][Y + Counter] = Right;
					Data.Data_Grid[X][Y][6] = std::abs((Counter * 80) - 28);
				}
			}
		}
	}
	if (Placed) {
		Data.Visual_Grid[X][Y] = Interface.Placing_Rotation + 67;
		Data.Data_Grid[X][Y][Power_Cap] = 3000;
		Data.Wiring_Grid[X][Y] = 0;
	} else {
		return false;
	}
	return true;
}

bool Place_Heat_Exchanger(int X, int Y) {
	bool Placed = false;
	if (evn_i(Interface.Placing_Rotation)) {
		if (Check_Clearance(X, Y, 4, 3)) {
			Fill_Clearance(LDE_INVALID, X, Y, 4, 3);
			Placed = true;
			for (int Counter1 = 0; Counter1 < 2; Counter1++) {
				for (int Counter2 = 0; Counter2 < 2; Counter2++) {
					Data.Plumbing_Grid[X + (Counter2 * 3)]
						[Y + (Counter1 * 2)] = Up + (Counter1 * 2);
					Data.Data_Grid[X + (Counter2 * 3)]
						[Y + (Counter1 * 2)][Fluid_Cap] = 300;
					Data.Settings_Grid[X + (Counter2 * 3)]
						[Y][0] = 2 - (Interface.Placing_Rotation * 0.5);
					Data.Settings_Grid[X + (Counter2 * 3)]
						[Y + 2][0] = 1 + (Interface.Placing_Rotation * 0.5);
					
				}
			}
		}
	} else {
		if (Check_Clearance(X, Y, 3, 4)) {
			Fill_Clearance(LDE_INVALID, X, Y, 3, 4);
			Placed = true;
			for (int Counter1 = 0; Counter1 < 2; Counter1++) {
				for (int Counter2 = 0; Counter2 < 2; Counter2++) {
					Data.Plumbing_Grid[X + (Counter1 * 2)][
						Y + (Counter2 * 3)] = (Counter1 * 2) + Left;
					Data.Data_Grid[(Counter1 * 2) + X][
						Y + (Counter2 * 3)][Fluid_Cap] = 300;
					Data.Settings_Grid[X][(Counter2 * 3) +
						Y][0] = (Interface.Placing_Rotation * 0.5) + 1;
					Data.Settings_Grid[X + 2][(Counter2 * 3) +
						Y][0] = 2 - (Interface.Placing_Rotation * 0.5);
				}
			}
		}
	}
	if (Placed) {
		Data.Visual_Grid[X][Y] = Interface.Placing_Rotation + 87;
		for (int Counter = 0; Counter < 4; Counter++) {
			Data.Settings_Grid[X][Y][Counter + 3] = 0;
		}
		for (int Counter = 0; Counter < 2; Counter++) {
			Data.Settings_Grid[X][Y][Counter + 7] = LDE_ROOMTEMP;
		}
		for (int Counter = 0; Counter < 2; Counter++) {
			Data.Settings_Grid[X][Y][Counter + 9] = LDE_INVALID;
		}
	} else {
		return false;
	}
	return true;
}

bool Place_Turbine_Input(int X, int Y) {
	bool Placed = false;
	if (Check_Clearance(X, Y, 2, 3) && evn_i(Interface.Placing_Rotation)) {
		Fill_Clearance(LDE_INVALID, X, Y, 2, 3);
		Placed = true;
	} else if (Check_Clearance(X, Y, 3, 2) && !evn_i(Interface.Placing_Rotation)) {
		Fill_Clearance(LDE_INVALID, X, Y, 3, 2);
		Placed = true;
	}
	if (Placed) {
		Data.Visual_Grid[X][Y] = Interface.Placing_Rotation + 120;
		Point Node = Return_Nodes(X, Y, Interface.Placing_Rotation,
			Preconfigurations.STI_Inputs)[0];
		Data.Settings_Grid[Interface.Target_Tile.X][
			Interface.Target_Tile.Y][3] = 0;
		Data.Settings_Grid[Interface.Target_Tile.X][
			Interface.Target_Tile.Y][4] = 0;
		Data.Data_Grid[Node.X][Node.Y][Fluid_Cap] = LDE_LARGECAP;
		Data.Settings_Grid[Node.X][Node.Y][0] = F_In;
		Data.Plumbing_Grid[Node.X][Node.Y] = Interface.Placing_Rotation + Left;
	} else {
		return false;
	}
	return true;
}

bool Place_Turbine_Impulse(int X, int Y) {
	bool Placed = false;
	if (Check_Clearance(X, Y, 2, 3) && evn_i(Interface.Placing_Rotation)) {
		Fill_Clearance(LDE_INVALID, X, Y, 2, 3);
		Placed = true;
	} else if (Check_Clearance(X, Y, 3, 2) && !evn_i(Interface.Placing_Rotation)) {
		Fill_Clearance(LDE_INVALID, X, Y, 3, 2);
		Placed = true;
	}
	if (Placed) {
		Data.Visual_Grid[X][Y] = Interface.Placing_Rotation + 124;
		Data.Settings_Grid[X][Y][3] = 0;
	} else {
		return false;
	}
	return true;
}

bool Place_Turbine_Output(int X, int Y) {
	if (Check_Clearance(X, Y, 2, 2)) {
		Fill_Clearance(LDE_INVALID, X, Y, 2, 2);
		Data.Visual_Grid[X][Y] = Interface.Placing_Rotation + 128;
		Point Node = Return_Nodes(X, Y, Interface.Placing_Rotation,
			Preconfigurations.STO_Outputs)[0];
		Data.Data_Grid[Node.X][Node.Y][Fluid_Cap] = LDE_LARGECAP;
		Data.Settings_Grid[Node.X][Node.Y][0] = F_Out;
		Data.Plumbing_Grid[Node.X][Node.Y] = Interface.Placing_Rotation + Left;
		//do outputZ!
	} else {
		Data.Settings_Grid[X][Y][3] = 0;
		return false;
	}
	return true;
}