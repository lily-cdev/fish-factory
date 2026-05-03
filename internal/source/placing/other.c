#include <grid.h>

bool Place_Incinerator(Point Pos) {
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = 12;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	Data.Settings_Grid[pt(Pos)][0] = F_In;
	return true;
}

bool Place_Signal_Tower(Point Pos) {
	Data.Settings_Grid[pt(Pos)][3] = 0;
	return true;
}

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
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = 900;
	return true;
}

bool Place_Power_Generator(Point Pos) {
	Data.Settings_Grid[pt(Pos)][3] = 0;
	return true;
}