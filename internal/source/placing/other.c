#include <grid.h>

bool Place_Incinerator(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = (Interface.Rotation == 0) ? 18 : Interface.Rotation + 113;
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = 12;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	Data.Settings_Grid[pt(Pos)][0] = F_In;
	Data.Animation_Grid[pt(Pos)][0] = 0;
	return true;
}

bool Place_Command_Platform(Point Pos) {
	bool Placed = false;
	if (!Data.CMD_Placed) {
		switch (Interface.Rotation) {
		case 0:
			if (Check_Clearance(Pos, 8, 6)) {
				Fill_Clearance(LDE_INVALID, Pos, 8, 6);
				Data.Visual_Grid[pt(Pos)] = 43;
				Placed = true;
			}
			break;
		case 1:
			if (Check_Clearance(Pos, 6, 8)) {
				Fill_Clearance(LDE_INVALID, Pos, 6, 8);
				Data.Visual_Grid[pt(Pos)] = 56;
				Placed = true;
			}
			break;
		case 2:
			if (Check_Clearance(Pos, 8, 6)) {
				Fill_Clearance(LDE_INVALID, Pos, 8, 6);
				Data.Visual_Grid[pt(Pos)] = 57;
				Placed = true;
			}
			break;
		case 3:
			if (Check_Clearance(Pos, 6, 8)) {
				Fill_Clearance(LDE_INVALID, Pos, 6, 8);
				Data.Visual_Grid[pt(Pos)] = 58;
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

bool Place_Battery(Point Pos) {
	if (Check_Clearance(Pos, 2, 2)) {
		Fill_Clearance(LDE_INVALID, Pos, 2, 2);
		Data.Visual_Grid[pt(Pos)] = (Interface.Rotation == 0) ? 44 : Interface.Rotation + 63;
	} else {
		return false;
	}
	return true;
}

bool Place_Signal_Tower(Point Pos) {
	if (Check_Clearance(Pos, 3, 3)) {
		Fill_Clearance(LDE_INVALID, Pos, 3, 3);
		Data.Visual_Grid[pt(Pos)] = (Interface.Rotation == 0) ? 50 : Interface.Rotation + 59;
		Data.Settings_Grid[pt(Pos)][3] = 0;
	} else {
		return false;
	}
	return true;
}

bool Place_Money_Generator(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 94;
	Data.Settings_Grid[pt(Pos)][3] = 5;
	Data.Settings_Grid[pt(Pos)][4] = 0;
	return true;
}

bool Place_Fluid_Generator(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 95;
	Data.Settings_Grid[pt(Pos)][0] = F_Out;
	Data.Settings_Grid[pt(Pos)][3] = 0;
	Data.Settings_Grid[pt(Pos)][4] = LDE_ROOMTEMP;
	Data.Settings_Grid[pt(Pos)][5] = 0;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = 900;
	return true;
}

bool Place_Power_Generator(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 138;
	Data.Data_Grid[pt(Pos)][Power_Cap] = 24000;
	Data.Settings_Grid[pt(Pos)][3] = 0;
	Data.Wiring_Grid[pt(Pos)] = F_Out;
	return true;
}