#include <grid.h>

void Cycle_RTG(Point Pos, const int Rotation) {
	Data.Data_Grid[pt(Pos)][Stored_Power] = min(Data.Data_Grid[pt(Pos)][Stored_Power] + 500, Data.Data_Grid[pt(Pos)][Power_Cap]);
}

void Cycle_Furnace(Point Pos, const int Rotation) {
    Point Offset = { 0, 2 };
	switch (Visual_To_Rotation(Data.Visual_Grid[pt(Pos)])) {
	case 1:
		Offset.Y = 0;
		break;
	case 2:
		Offset.X = 2;
		Offset.Y = 0;
		break;
	case 3:
		Offset.X = 2;
		break;
	}
	Item_Ptr Target = Get_ID_Item(Data.Items_Grid[Pos.X + Offset.X][Pos.Y + Offset.Y]);
	Data.Animation_Grid[pt(Pos)][0] = 0;
	if (Target->Chem_Energy > 0 && Data.Data_Grid[Pos.X + Offset.X][Pos.Y + Offset.Y][Stored_Fluids] >= 2) {
		Data.Data_Grid[Pos.X + Offset.X][Pos.Y + Offset.Y][Stored_Fluids] -= 2;
		Data.Data_Grid[pt(Pos)][Stored_Power] = min(Data.Data_Grid[pt(Pos)][Stored_Power] + (Target->Chem_Energy * 0.9f),
			Data.Data_Grid[pt(Pos)][Power_Cap]);
		Data.Animation_Grid[pt(Pos)][0] = 1;
	}
}

void Cycle_Geo_Well(Point Pos, const int Rotation) {
	bool Conditional = true;
	Node Inputs = { };
	Node Outputs = { };
	if (Data.Data_Grid[pt(Pos)][Stored_Power] < 2500) {
		Conditional = false;
	}
	Return_Nodes(&Inputs, Pos, Rotation, Preconfigs.GW_Inputs);
	Return_Nodes(&Outputs, Pos, Rotation, Preconfigs.GW_Outputs);
	if (Data.Data_Grid[pt(Inputs.Data[0])][Stored_Fluids] < 8 || Data.Data_Grid[pt(Outputs.Data[0])][Stored_Fluids] > 0) {
		Conditional = false;
	}
	if (!Get_ID_Item(Data.Items_Grid[pt(Outputs.Data[0])])->Coolant) {
		Conditional = false;
	}
	Data.Animation_Grid[pt(Pos)][0] = 0;
	if (Conditional) {
		Data.Data_Grid[pt(Pos)][Stored_Power] -= 2500;
		Data.Data_Grid[pt(Inputs.Data[0])][Stored_Fluids] -= 8;
		Data.Data_Grid[pt(Outputs.Data[0])][Stored_Fluids] += 8;
		int Temperature = Data.Temperature_Grid[pt(Inputs.Data[0])];
		if (Temperature == 328) {
			Temperature = 327;
		}
		float Benchmark = log10f((328.0f - Temperature) / 263.0f) / log10f(0.64f);
		Update_Item(Outputs.Data[Rotation], Data.Items_Grid[pt(Inputs.Data[0])], (-263.0f * powf(0.64f, Benchmark + 1.0f)) + 328);
		Data.Animation_Grid[pt(Pos)][0] = 1;
	}
	ktn_free(Inputs.Data);
	ktn_free(Outputs.Data);
}

void Cycle_HX(Point Pos, const int Rotation) {
	bool Boiling = false;
	if (Data.Settings_Grid[pt(Interface.Tile)][8] >= ktn_water_boil_pt) {
		Boiling = true;
	}
	Point Outputs[2][4] = {
		{ { Pos.X + 3, Pos.Y }, { Pos.X + 2, Pos.Y + 3 }, { Pos.X, Pos.Y + 2 }, Pos },
		{ Pos, { Pos.X + 2, Pos.Y }, { Pos.X + 3, Pos.Y + 2 }, { Pos.X, Pos.Y + 3 } }
	};
	for (int C1 = 0; C1 < 2; C1++) {
		Point Output_Pos = Outputs[C1][Visual_To_Rotation(Data.Visual_Grid[pt(Pos)])];
		if ((Data.Items_Grid[pt(Output_Pos)] == ktn_invalid || (Data.Settings_Grid[pt(Pos)][C1 + 9] == Data.Items_Grid[
			pt(Output_Pos)] && !Boiling) || (Data.Items_Grid[pt(Output_Pos)] == Get_Item("steam")->ID && Boiling &&
			C1 == 1)) && Data.Settings_Grid[pt(Pos)][C1 + 5] > 0) {
			Data.Items_Grid[pt(Output_Pos)] = (Boiling && C1 == 1) ? Get_Item("steam")->ID : Data.Settings_Grid[pt(Pos)][C1 + 9];
			float Draining_Amount = min(Data.Settings_Grid[pt(Pos)][C1 + 3], Data.Settings_Grid[pt(Pos)][C1 + 5]);
			Draining_Amount = min(Draining_Amount, Data.Data_Grid[pt(Output_Pos)][Fluid_Cap] - Data.Data_Grid[pt(Output_Pos)][
				Stored_Fluids]);
			Data.Data_Grid[pt(Output_Pos)][Stored_Fluids] += Draining_Amount;
			Data.Settings_Grid[pt(Pos)][C1 + 5] -= Draining_Amount;
		}
	}
	Point Inputs[2][4] = {
		{ { Pos.X + 3, Pos.Y + 2 }, { Pos.X, Pos.Y + 3 }, Pos, { Pos.X + 2, Pos.Y } },
		{ { Pos.X, Pos.Y + 2 }, Pos, { Pos.X + 3, Pos.Y }, { Pos.X + 2, Pos.Y + 3 } }
	};
	for (int C1 = 0; C1 < 2; C1++) {
		Point Input_Pos = Inputs[C1][Visual_To_Rotation(Data.Visual_Grid[pt(Pos)])];
		if (Get_ID_Item(Data.Items_Grid[pt(Input_Pos)])->Coolant && (Data.Settings_Grid[pt(Pos)][C1 + 9] == ktn_invalid ||
			Data.Settings_Grid[pt(Pos)][C1 + 9] == Data.Items_Grid[pt(Input_Pos)])) {
			Data.Settings_Grid[pt(Pos)][C1 + 9] = Data.Items_Grid[pt(Input_Pos)];
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
	float Remaining = powf(M_E, (-1 * ((ktn_hx_efficiency * (Data.Settings_Grid[pt(Pos)][6] + Data.Settings_Grid[pt(Pos)][5])) / (
		4.186 * Data.Settings_Grid[pt(Pos)][6] * Data.Settings_Grid[pt(Pos)][5]))));
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
	if (Data.Settings_Grid[pt(Pos)][4] < ktn_epsilon) {
		return;
	}
	Machine_Ptr Machine = Get_Machine("turbine_input");
	Point Input = Get_Transformed(Machine, Machine->Inputs[0], Pos);
	if (Data.Data_Grid[pt(Input)][Stored_Fluids] > 2) {
		Machine_Ptr Submachine = Get_Machine("turbine_output");
		Data.Data_Grid[pt(Input)][Stored_Fluids] -= 2;
		Point End = {
			Data.Settings_Grid[pt(Pos)][5],
			Data.Settings_Grid[pt(Pos)][6]
		};
		Point Output = Get_Transformed(Submachine, Submachine->Outputs[0], End);
		Data.Data_Grid[pt(Output)][Stored_Fluids] = min(Data.Data_Grid[pt(Output)][Stored_Fluids] + 2, Data.Data_Grid[
			pt(Output)][Fluid_Cap]);//broken
		Recast_Machines();
	}
}