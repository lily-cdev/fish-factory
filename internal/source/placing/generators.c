#include <grid.h>

bool Place_Heat_Exchanger(Point Pos) {
	for (int C1 = 0; C1 < 4; C1++) {
		Data.Settings_Grid[pt(Pos)][C1 + 3] = 0;
	}
	for (int C1 = 0; C1 < 2; C1++) {
		Data.Settings_Grid[pt(Pos)][C1 + 7] = ktn_room_temp;
	}
	return true;
}

bool Place_Turbine_Input(Point Pos) {
	Data.Settings_Grid[pt(Interface.Tile)][3] = 0;
	Data.Settings_Grid[pt(Interface.Tile)][4] = 0;
	Data.Settings_Grid[pt(Interface.Tile)][9] = 0;
	return true;
}

bool Place_Turbine_Impulse(Point Pos) {
	Data.Settings_Grid[pt(Pos)][3] = 0;
	return true;
}