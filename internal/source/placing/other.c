#include <grid.h>

bool Place_Incinerator(int X, int Y) {
	Data.Visual_Grid[X][Y] = (Interface.Rotation == 0) ? 18 : Interface.Rotation + 113;
	Data.Connection_Grid[X][Y] = 0;
	Data.Data_Grid[X][Y][Fluid_Cap] = 12;
	Data.Plumbing_Grid[X][Y] = Any;
	Data.Settings_Grid[X][Y][0] = F_In;
	Data.Animation_Grid[X][Y][0] = 0;
	return true;
}

bool Place_Command_Platform(int X, int Y) {
	bool Placed = false;
	if (!Data.CMD_Placed) {
		switch (Interface.Rotation) {
		case 0:
			if (Check_Clearance(X, Y, 8, 6)) {
				Fill_Clearance(LDE_INVALID, X, Y, 8, 6);
				Data.Visual_Grid[X][Y] = 43;
				Placed = true;
			}
			break;
		case 1:
			if (Check_Clearance(X, Y, 6, 8)) {
				Fill_Clearance(LDE_INVALID, X, Y, 6, 8);
				Data.Visual_Grid[X][Y] = 56;
				Placed = true;
			}
			break;
		case 2:
			if (Check_Clearance(X, Y, 8, 6)) {
				Fill_Clearance(LDE_INVALID, X, Y, 8, 6);
				Data.Visual_Grid[X][Y] = 57;
				Placed = true;
			}
			break;
		case 3:
			if (Check_Clearance(X, Y, 6, 8)) {
				Fill_Clearance(LDE_INVALID, X, Y, 6, 8);
				Data.Visual_Grid[X][Y] = 58;
				Placed = true;
			}
			break;
		default:
			break;
		}
	}
	if (!Placed) {
		return false;
	}
	Data.CMD_Placed = true;
	return true;
}

bool Place_Basic_Scrubber(int X, int Y) {
	if (Check_Clearance(X, Y, 2, 2)) {
		Fill_Clearance(LDE_INVALID, X, Y, 2, 2);
		Data.Visual_Grid[X][Y] = (Interface.Rotation == 0) ? 44 : Interface.Rotation + 63;
	} else {
		return false;
	}
	return true;
}

bool Place_Signal_Tower(int X, int Y) {
	if (Check_Clearance(X, Y, 3, 3)) {
		Fill_Clearance(LDE_INVALID, X, Y, 3, 3);
		Data.Visual_Grid[X][Y] = (Interface.Rotation == 0) ? 50 : Interface.Rotation + 59;
		Data.Settings_Grid[X][Y][3] = 0;
	} else {
		return false;
	}
	return true;
}

bool Place_Money_Generator(int X, int Y) {
	Data.Visual_Grid[X][Y] = 94;
	Data.Settings_Grid[X][Y][3] = 5;
	Data.Settings_Grid[X][Y][4] = 0;
	return true;
}

bool Place_Fluid_Generator(int X, int Y) {
	Data.Visual_Grid[X][Y] = 95;
	Data.Settings_Grid[X][Y][0] = F_Out;
	Data.Settings_Grid[X][Y][3] = 0;
	Data.Settings_Grid[X][Y][4] = LDE_ROOMTEMP;
	Data.Settings_Grid[X][Y][5] = 0;
	Data.Plumbing_Grid[X][Y] = Any;
	Data.Data_Grid[X][Y][Fluid_Cap] = 900;
	return true;
}