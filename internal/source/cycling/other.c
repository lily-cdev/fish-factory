#include <grid.h>

void Cycle_Incinerator(const int X, const int Y, const int Rotation) {
	Data.Data_Grid[X][Y][Stored_Fluids] = max(Data.Data_Grid[X][Y][Stored_Fluids] - 8.0, 0.0);
}

void Cycle_Signal_Tower(const int X, const int Y, const int Rotation) {
	Data.Settings_Grid[X][Y][3] = (int)(!((bool)Data.Settings_Grid[X][Y][3]));
}

void Cycle_Money_Generator(const int X, const int Y, const int Rotation) {
	Data.Funds = max(Data.Funds + (float)(Data.Settings_Grid[X][Y][4]), 0.0f);
}

void Cycle_Fluid_Generator(const int X, const int Y, const int Rotation) {
	if (Data.Items_Grid[X][Y] != Data.Settings_Grid[X][Y][3] || Data.Temperature_Grid[X][Y] != Data.Settings_Grid[X][Y][
		4]) {
		Data.Data_Grid[X][Y][Stored_Fluids] = 0;
		Data.Items_Grid[X][Y] = Data.Settings_Grid[X][Y][3];
		Data.Temperature_Grid[X][Y] = Data.Settings_Grid[X][Y][4];
	}
	Data.Data_Grid[X][Y][Stored_Fluids] = min(Data.Settings_Grid[X][Y][5] + Data.Data_Grid[X][Y][Stored_Fluids],
		Data.Data_Grid[X][Y][Fluid_Cap]);
}

void Cycle_Power_Generator(const int X, const int Y, const int Rotation) {
	//todo (settings 3)
	Data.Data_Grid[X][Y][Stored_Power] = min(Data.Data_Grid[X][Y][Power_Cap], Data.Data_Grid[X][Y][Stored_Power] + (float)(
		Data.Settings_Grid[X][Y][3]));
}