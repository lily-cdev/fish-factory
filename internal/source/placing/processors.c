#include <grid.h>

bool Place_Filtration_Plant(Point Pos) {
	Data.Plumbing_Grid[Pos.X][Pos.Y + 1] = Left;
	Data.Plumbing_Grid[Pos.X + 1][Pos.Y] = Right;
	Data.Plumbing_Grid[Pos.X + 1][Pos.Y + 1] = Right;
	Data.Plumbing_Grid[Pos.X + 1][Pos.Y + 2] = Right;
	Data.Data_Grid[pt(Pos)][4] = 5;
	Data.Data_Grid[Pos.X][Pos.Y + 1][Fluid_Cap] = 16;
	Data.Data_Grid[Pos.X + 1][Pos.Y][Fluid_Cap] = 12;
	for (int C1 = 1; C1 < 3; C1++) {
		Data.Data_Grid[Pos.X + 1][Pos.Y + C1][Fluid_Cap] = 4;
		Data.Settings_Grid[Pos.X + 1][Pos.Y + C1][0] = 2;
	}
	Data.Settings_Grid[Pos.X][Pos.Y + 1][0] = 1;
	Data.Settings_Grid[Pos.X + 1][Pos.Y][0] = 2;
	return true;
}

bool Place_Condenser_Input(Point Pos) {
	return true;
}

bool Place_Condenser_Transferor(Point Pos) {
	return true;
}

bool Place_Condenser_Heatsink(Point Pos) {
	return true;
}

bool Place_Condenser_Output(Point Pos) {
	return true;
}