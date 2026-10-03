#include <grid.h>

void Cycle_RTG(Point Pos, const int Rotation) {
	Data.Data_Grid[pt(Pos)][Stored_Power] = fminf(Data.Data_Grid[pt(Pos)][Stored_Power] + 2500, Data.Data_Grid[pt(Pos)][Power_Cap]);
}

void Cycle_Furnace(Point Pos, const int Rotation) {
	Point Input_Pos = Get_Transformed(Get_Machine("furnace")->Inputs[0], Pos);
	Item_Ptr Target = Get_Item(Data.Items_Grid[pt(Input_Pos)]);
	Data.Animation_Grid[pt(Pos)][0] = 0;
	if (Target->Chem_Energy > 0 && Data.Data_Grid[pt(Input_Pos)][Stored_Fluids] >= 1) {
		Data.Data_Grid[pt(Input_Pos)][Stored_Fluids]--;
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
	if (!ktn_stricmp(Get_Item(Data.Items_Grid[pt(Input)])->Index, "water")) {
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
	if (Data.Settings_Grid[pt(Pos)][8]/*exchanger pool temperature*/ >= ktn_water_boil_pt) {
		Boiling = true;
	}
	Point Feedwater_Intake = Get_Transformed(Get_Machine("hx")->Inputs[0], Pos);
	Point Hmed_Intake = Get_Transformed(Get_Machine("hx")->Inputs[1], Pos);
	Point Feedwater_Yield = Get_Transformed(Get_Machine("hx")->Outputs[0], Pos);
	Point Hmed_Yield = Get_Transformed(Get_Machine("hx")->Outputs[1], Pos);
	float Pot_Water = fminf(Data.Data_Grid[pt(Hmed_Intake)][Stored_Fluids], Data.Data_Grid[pt(Hmed_Yield)][Fluid_Cap] - Data.Data_Grid[pt(Hmed_Yield)][Stored_Fluids]);
	Pot_Water = fminf(Data.Settings_Grid[pt(Pos)][3], Pot_Water);
	if (Pot_Water > 0) {
		float Hot_In = Data.Temperature_Grid[pt(Hmed_Intake)];
		float Hot_Out = Hot_In - (Hot_In - Data.Settings_Grid[pt(Pos)][8]) * 0.8f;
		float Q2P = (Hot_In - Hot_Out) * Pot_Water * ktn_c_water;
		Data.Settings_Grid[pt(Pos)][8] += Q2P / (ktn_hx_pool_mass * ktn_c_water);
		Data.Data_Grid[pt(Hmed_Intake)][Stored_Fluids] -= Pot_Water;
		Data.Data_Grid[pt(Hmed_Yield)][Stored_Fluids] += Pot_Water;
		Update_Item(Hmed_Yield, "water", Hot_Out);
	}
	float Pot_Steam = fminf(Data.Data_Grid[pt(Feedwater_Intake)][Stored_Fluids], Data.Data_Grid[pt(Feedwater_Yield)][Fluid_Cap] - Data.Data_Grid[pt(Feedwater_Yield)][
		Stored_Fluids]);
	Pot_Steam = fminf(Data.Settings_Grid[pt(Pos)][4], Pot_Steam);
	if (Pot_Steam > 0 && Boiling) {
		float QPlb = (fmaxf(ktn_water_boil_pt - Data.Temperature_Grid[pt(Feedwater_Intake)], 0) * ktn_c_water) + ktn_h_fg;
		float Q_Ava = (Data.Settings_Grid[pt(Pos)][8] - ktn_water_boil_pt) * ktn_hx_pool_mass * ktn_c_water;
		float Steam = fminf(Pot_Steam, Q_Ava / QPlb);
		if (Steam > 0) {
			Data.Settings_Grid[pt(Pos)][8] -= (Steam * QPlb) / (ktn_hx_pool_mass * ktn_c_water);
			Data.Data_Grid[pt(Feedwater_Intake)][Stored_Fluids] -= Steam;
			Data.Data_Grid[pt(Feedwater_Yield)][Stored_Fluids] += Steam;
			Update_Item(Feedwater_Yield, "steam", Data.Settings_Grid[pt(Pos)][8]);
		}
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