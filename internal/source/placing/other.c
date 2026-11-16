#include <grid.h>

bool Place_Money_Generator(Point Pos) {
	Data.Settings_Grid[pt(Pos)][3] = 5;
	Data.Settings_Grid[pt(Pos)][4] = 0;
	return true;
}

bool Place_Fluid_Generator(Point Pos) {
	Data.Settings_Grid[pt(Pos)][0] = F_Out;
	Data.Settings_Grid[pt(Pos)][3] = 0;
	Data.Settings_Grid[pt(Pos)][4] = ktn_room_temp;
	Data.Settings_Grid[pt(Pos)][5] = 0;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = 30;
	Data.Types_Grid[pt(Pos)] = T_Any;
	return true;
}

bool Place_Power_Generator(Point Pos) {
	Data.Settings_Grid[pt(Pos)][3] = 0;
	return true;
}

bool Place_CNC(Point Pos) {
	Data.Animation_Grid[pt(Pos)][2] = 60;
	Data.Animation_Grid[pt(Pos)][3] = 60;
	Data.Animation_Grid[pt(Pos)][4] = 0;
	Data.Animation_Grid[pt(Pos)][5] = 0;
	Data.Animation_Grid[pt(Pos)][6] = 1;
	Data.Animation_Grid[pt(Pos)][7] = 1;
	Data.Animation_Grid[pt(Pos)][8] = 1;
	Data.Animation_Grid[pt(Pos)][9] = 1;
	return true;
}