#include <grid.h>

void Cycle_RTG(Point Pos, const int Rotation) {
	Data.Data_Grid[pt(Pos)][Stored_Power] = fminf(Data.Data_Grid[pt(Pos)][Stored_Power] + 500, Data.Data_Grid[pt(Pos)][Power_Cap]);
}

void Cycle_Furnace(Point Pos, const int Rotation) {
	Point Input_Pos = Get_Transformed(Get_Machine("furnace")->Inputs[0], Pos);
	Item_Ptr Target = Get_Item(Data.Items_Grid[pt(Input_Pos)]);
	Data.Animation_Grid[pt(Pos)][0] = 0;
	if (Target->Chem_Energy > 0 && Data.Data_Grid[pt(Input_Pos)][Stored_Fluids] >= 2) {
		Data.Data_Grid[pt(Input_Pos)][Stored_Fluids] -= 2;
		Data.Data_Grid[pt(Pos)][Stored_Power] = fminf(Data.Data_Grid[pt(Pos)][Stored_Power] + (Target->Chem_Energy * 0.9f), Data.Data_Grid[pt(Pos)][Power_Cap]);
		Data.Animation_Grid[pt(Pos)][0] = 1;
	}
}

void Cycle_Geo_Well(Point Pos, const int Rotation) {
	Data.Animation_Grid[pt(Pos)][0] = 0;
	if (Data.Data_Grid[pt(Pos)][Stored_Power] < 2500) {
		return;
	}
	Point Input = Get_Transformed(Get_Machine("geo_well")->Inputs[0], Pos);
	Point Output = Get_Transformed(Get_Machine("geo_well")->Outputs[0], Pos);
	if (Data.Data_Grid[pt(Input)][Stored_Fluids] < 10 || Data.Data_Grid[pt(Output)][Stored_Fluids] > 2) {
		return;
	}
	if (!Get_Item(Data.Items_Grid[pt(Input)])->Coolant) {
		return;
	}
	Data.Data_Grid[pt(Pos)][Stored_Power] -= 2500;
	Data.Data_Grid[pt(Input)][Stored_Fluids] -= 10;
	Data.Data_Grid[pt(Output)][Stored_Fluids] += 10;
	int Temperature = Data.Temperature_Grid[pt(Input)];
	if (Temperature == 328) {
		Temperature = 327;
	}
	float Benchmark = log10f((328.0f - Temperature) / 263.0f) / log10f(0.64f);
	Update_Item(Output, Data.Items_Grid[pt(Input)], (-263.0f * powf(0.64f, Benchmark + 1.0f)) + 328);
	Data.Animation_Grid[pt(Pos)][0] = 1;
}

void Cycle_HX(Point Pos, const int Rotation) {
	bool Boiling = false;
	if (Data.Settings_Grid[pt(Interface.Tile)][8] >= ktn_water_boil_pt) {
		Boiling = true;
	}
	for (int C1 = 0; C1 < 2; C1++) {
		Point Output_Pos = Get_Transformed(Get_Machine("hx")->Outputs[C1], Pos);
		if ((strncpy(Data.Items_Grid[pt(Output_Pos)], Metadata.Null_Item.Index, 64) || (Data.Settings_Grid[pt(Pos)][C1 + 9] == Get_Item(Data.Items_Grid[
			pt(Output_Pos)])->ID && !Boiling) || (ktn_stricmp(Data.Items_Grid[pt(Output_Pos)], Get_Item("steam")->Index) && Boiling && C1 == 1)) && Data.Settings_Grid[
			pt(Pos)][C1 + 5] > 0) {
			strncpy(Data.Items_Grid[pt(Output_Pos)], (Boiling && C1 == 1) ? Get_Item("steam")->Index : Get_ID_Item(Data.Settings_Grid[pt(Pos)][C1 + 9])->Index, 64);
			float Draining_Amount = fminf(Data.Settings_Grid[pt(Pos)][C1 + 3], Data.Settings_Grid[pt(Pos)][C1 + 5]);
			Draining_Amount = fminf(Draining_Amount, Data.Data_Grid[pt(Output_Pos)][Fluid_Cap] - Data.Data_Grid[pt(Output_Pos)][Stored_Fluids]);
			Data.Data_Grid[pt(Output_Pos)][Stored_Fluids] += Draining_Amount;
			Data.Settings_Grid[pt(Pos)][C1 + 5] -= Draining_Amount;
		}
	}
	for (int C1 = 0; C1 < 2; C1++) {
		Point Input_Pos = Get_Transformed(Get_Machine("hx")->Inputs[C1], Pos);
		if (Get_Item(Data.Items_Grid[pt(Input_Pos)])->Coolant && (Data.Settings_Grid[pt(Pos)][C1 + 9] == ktn_invalid || Data.Settings_Grid[pt(Pos)][C1 + 9] ==
			Get_Item(Data.Items_Grid[pt(Input_Pos)])->ID)) {
			Data.Settings_Grid[pt(Pos)][C1 + 9] = Get_Item(Data.Items_Grid[pt(Input_Pos)])->ID;
			int Volume = Data.Settings_Grid[pt(Pos)][C1 + 5], Intake = 0;
			if (Data.Data_Grid[pt(Input_Pos)][Stored_Fluids] > 0 && Volume < ktn_hx_cap) {
				if (Volume + Data.Data_Grid[pt(Input_Pos)][Stored_Fluids] > ktn_hx_cap) {
					Intake = ktn_hx_cap - Volume;
					Data.Data_Grid[pt(Input_Pos)][Stored_Fluids] -= Intake;
					Data.Settings_Grid[pt(Pos)][C1 + 5] = ktn_hx_cap;
				} else {
					Intake = Data.Data_Grid[pt(Input_Pos)][Stored_Fluids];
					Data.Settings_Grid[pt(Pos)][C1 + 5] += Intake;
					Data.Data_Grid[pt(Input_Pos)][Stored_Fluids] = 0;
				}
			}
			if (Volume + Intake != 0) {
				Data.Settings_Grid[pt(Pos)][C1 + 7] = ((Data.Settings_Grid[pt(Pos)][C1 + 7] * Volume) + (Data.Temperature_Grid[
					pt(Input_Pos)] * Intake)) / (Volume + Intake);
			}
		}
	}
	float Temp_Equil = ((Data.Settings_Grid[pt(Pos)][6] * Data.Settings_Grid[pt(Pos)][8]) + (Data.Settings_Grid[pt(Pos)][5] *
		Data.Settings_Grid[pt(Pos)][7])) / (Data.Settings_Grid[pt(Pos)][6] + Data.Settings_Grid[pt(Pos)][5]);
	float Difference = Data.Settings_Grid[pt(Pos)][7] - Data.Settings_Grid[pt(Pos)][8];
	float Remaining = powf(M_E, (-1 * ((ktn_hx_efficiency * (Data.Settings_Grid[pt(Pos)][6] + Data.Settings_Grid[pt(Pos)][5])) /
		(4.186f * Data.Settings_Grid[pt(Pos)][6] * Data.Settings_Grid[pt(Pos)][5]))));
	float FW_Yield = Temp_Equil - (((Data.Settings_Grid[pt(Pos)][5] / (Data.Settings_Grid[pt(Pos)][6] + Data.Settings_Grid[
		pt(Pos)][5])) * Difference) * Remaining);
	float HM_Yield = Temp_Equil + (((Data.Settings_Grid[pt(Pos)][6] / (Data.Settings_Grid[pt(Pos)][6] + Data.Settings_Grid[
		pt(Pos)][5])) * Difference) * Remaining);
	if (HM_Yield > 0 && FW_Yield > 0) {
		Data.Settings_Grid[pt(Pos)][7] = HM_Yield;
		Data.Settings_Grid[pt(Pos)][8] = FW_Yield;
	}
}

void Cycle_Turbine_Input(Point Pos, const int Rotation) {
	float Delta = 750000;
	Data.Settings_Grid[pt(Pos)][8] = 0;
	if (Data.Settings_Grid[pt(Pos)][4] < ktn_epsilon) {
		Data.Settings_Grid[pt(Pos)][9] = fmaxf(0, Data.Settings_Grid[pt(Pos)][9] - Delta);
		return;
	}
	Point Input = Get_Transformed(Get_Machine("turbine_input")->Inputs[0], Pos);
	if (ktn_stricmp(Data.Items_Grid[pt(Input)], Get_Item("steam")->Index)) {
		Data.Settings_Grid[pt(Pos)][9] = fmaxf(0, Data.Settings_Grid[pt(Pos)][9] - Delta);
		return;
	}
	if (Data.Data_Grid[pt(Input)][Stored_Fluids] < 20) {
		Data.Settings_Grid[pt(Pos)][9] = fmaxf(0, Data.Settings_Grid[pt(Pos)][9] - Delta);
		return;
	}
	Data.Data_Grid[pt(Input)][Stored_Fluids] -= 20;
	Point End = { Data.Settings_Grid[pt(Pos)][5], Data.Settings_Grid[pt(Pos)][6] };
	Point Output = Get_Transformed(Get_Machine("turbine_output")->Outputs[0], End);
	float Temp = Data.Temperature_Grid[pt(Input)];
	float Target = ((((fminf(Data.Settings_Grid[pt(Pos)][3], 5) * 0.1f) + 1.0f) * 120000000.0f) * Temp) / 600.0f;
	Data.Settings_Grid[pt(Pos)][8] = Target;
	float Current = Data.Settings_Grid[pt(Pos)][9];
	Data.Settings_Grid[pt(Pos)][9] = (Current > Target) ? fmaxf(Current - Delta, Target) : fminf(Current + Delta, Target);
	Data.Data_Grid[pt(Pos)][Stored_Power] = fminf(Data.Data_Grid[pt(Pos)][Stored_Power] + Data.Settings_Grid[pt(Pos)][9], Data.Data_Grid[pt(Pos)][Power_Cap]);
	Data.Data_Grid[pt(Output)][Stored_Fluids] = fminf(Data.Data_Grid[pt(Output)][Stored_Fluids] + 20, Data.Data_Grid[pt(Output)][Fluid_Cap]);
	Update_Item(Output, Get_Item("water")->Index, fminf(Temp, 90));
}