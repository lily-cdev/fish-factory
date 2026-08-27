#include <grid.h>

void Cycle_Incinerator(Point Pos, const int Rotation) {
	if (Data.Data_Grid[pt(Pos)][Stored_Fluids] > ktn_epsilon) {
		Data.Animation_Grid[pt(Pos)][0] = 1.0f;
	} else {
		Data.Animation_Grid[pt(Pos)][0] = 0.0f;
	}
	Data.Data_Grid[pt(Pos)][Stored_Fluids] = fmaxf(Data.Data_Grid[pt(Pos)][Stored_Fluids] - 8.0, 0.0);
}

void Cycle_Signal_Tower(Point Pos, const int Rotation) {
	Data.Settings_Grid[pt(Pos)][3] = (int)(!((bool)Data.Settings_Grid[pt(Pos)][3]));
}

void Cycle_Money_Generator(Point Pos, const int Rotation) {
	Data.Funds = fmaxf(Data.Funds + (float)(Data.Settings_Grid[pt(Pos)][4]), 0.0f);
}

void Cycle_Fluid_Generator(Point Pos, const int Rotation) {
	Item_Ptr Item = &Metadata.Items[(int)Data.Settings_Grid[pt(Pos)][3]];
	if (!ktn_stricmp(Data.Items_Grid[pt(Pos)], Item->Index) || Data.Temperature_Grid[pt(Pos)] != Data.Settings_Grid[pt(Pos)][4]) {
		Data.Data_Grid[pt(Pos)][Stored_Fluids] = 0;
		strncpy(Data.Items_Grid[pt(Pos)], Item->Index, 64);
		Data.Temperature_Grid[pt(Pos)] = Data.Settings_Grid[pt(Pos)][4];
	}
	Data.Data_Grid[pt(Pos)][Stored_Fluids] = fminf(Data.Settings_Grid[pt(Pos)][5] + Data.Data_Grid[pt(Pos)][Stored_Fluids], Data.Data_Grid[pt(Pos)][Fluid_Cap]);
}

void Cycle_Power_Generator(Point Pos, const int Rotation) {
	Data.Data_Grid[pt(Pos)][Stored_Power] = fminf(Data.Data_Grid[pt(Pos)][Power_Cap], Data.Data_Grid[pt(Pos)][Stored_Power] + (float)(Data.Settings_Grid[pt(Pos)][3]));
}