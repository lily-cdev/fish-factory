#include <grid.h>

void Cycle_Incinerator(Point Pos, const int Rotation) {
	Data.Data_Grid[pt(Pos)][Stored_Fluids] = max(Data.Data_Grid[pt(Pos)][Stored_Fluids] - 8.0, 0.0);
}

void Cycle_Signal_Tower(Point Pos, const int Rotation) {
	Data.Settings_Grid[pt(Pos)][3] = (int)(!((bool)Data.Settings_Grid[pt(Pos)][3]));
}

void Cycle_Money_Generator(Point Pos, const int Rotation) {
	Data.Funds = max(Data.Funds + (float)(Data.Settings_Grid[pt(Pos)][4]), 0.0f);
}

void Cycle_Fluid_Generator(Point Pos, const int Rotation) {
	Item_Ptr Item = &Metadata.Items[(int)Data.Settings_Grid[pt(Pos)][3]];
	if (Data.Items_Grid[pt(Pos)] != Item->ID || Data.Temperature_Grid[pt(Pos)] != Data.Settings_Grid[pt(Pos)][4]) {
		Data.Data_Grid[pt(Pos)][Stored_Fluids] = 0;
		Data.Items_Grid[pt(Pos)] = Item->ID;
		Data.Temperature_Grid[pt(Pos)] = Data.Settings_Grid[pt(Pos)][4];
	}
	Data.Data_Grid[pt(Pos)][Stored_Fluids] = min(Data.Settings_Grid[pt(Pos)][5] + Data.Data_Grid[pt(Pos)][Stored_Fluids],
		Data.Data_Grid[pt(Pos)][Fluid_Cap]);
}

void Cycle_Power_Generator(Point Pos, const int Rotation) {
	Data.Data_Grid[pt(Pos)][Stored_Power] = min(Data.Data_Grid[pt(Pos)][Power_Cap], Data.Data_Grid[pt(Pos)][Stored_Power] +
		(float)(Data.Settings_Grid[pt(Pos)][3]));
}