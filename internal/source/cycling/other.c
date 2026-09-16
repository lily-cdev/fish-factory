#include <grid.h>

void Cycle_Incinerator(Point Pos, const int Rotation) {
	if (Data.Data_Grid[pt(Pos)][Stored_Fluids] > ktn_epsilon) {
		Data.Animation_Grid[pt(Pos)][0] = 1.0f;
	} else {
		Data.Animation_Grid[pt(Pos)][0] = 0.0f;
	}
	Data.Data_Grid[pt(Pos)][Stored_Fluids] = fmaxf(Data.Data_Grid[pt(Pos)][Stored_Fluids] - 8.0, 0.0);
}

void Cycle_Drydock_Intake(Point Pos, const int Rotation) {
	Machine_Ptr Machine = Get_Machine("signal_tower");
	for (int C1 = 0; C1 < Machine->Input_Ct; C1++) {
		Point Subpos = Get_Transformed(Machine->Inputs[C1], Pos);
		if (Data.Data_Grid[pt(Subpos)][Stored_Fluids] > ktn_epsilon) {
			float Amount = Data.Data_Grid[pt(Subpos)][Stored_Fluids];
			Data.Data_Grid[pt(Subpos)][Stored_Fluids] = 0;
			for (int C2 = 0; C2 < Data.Objective_Ct[Data.Objective_Phase]; C2++) {
				if (ktn_stricmp(Data.Items_Grid[pt(Subpos)], Data.Objectives[Data.Objective_Phase][C2])) {
					Data.Objective_Progress[C2] = fminf(Data.Objective_Progress[C2] + Amount, (float)Data.Objective_Amounts[Data.Objective_Phase][C2]);
				}
			}
		}
	}
	bool Finished = true;
	for (int C1 = 0; C1 < Data.Objective_Ct[Data.Objective_Phase]; C1++) {
		if (Data.Objective_Progress[C1] < Data.Objective_Amounts[Data.Objective_Phase][C1] - ktn_epsilon) {
			Finished = false;
			break;
		}
	}
	if (Finished && Data.Objective_Phase < 1) {
		Data.Objective_Phase++;
		for (int C1 = 0; C1 < 8; C1++) {
			Data.Objective_Progress[C1] = 0;
		}
	}
	//process inputs
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