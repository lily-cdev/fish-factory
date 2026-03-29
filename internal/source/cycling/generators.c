#include <grid.h>

void Cycle_RTG(Point Pos, const int Rotation) {
	Data.Data_Grid[pt(Pos)][Stored_Power] = min(Data.Data_Grid[pt(Pos)][Stored_Power] + 0.5, Data.Data_Grid[pt(Pos)][Power_Cap]);
}

void Cycle_Bio_Gen(Point Pos, const int Rotation) {
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
	Item_Stack Target_Item = Get_Item((Point){ Pos.X + Offset.X, Pos.Y + Offset.Y });
	Data.Animation_Grid[pt(Pos)][0] = 0;
	if (Check_Category(Target_Item.Identifier, Preset_Categories.Biomass) > 0 && Data.Data_Grid[Pos.X + Offset.X][
		Pos.Y + Offset.Y][Stored_Fluids] >= 2) {
		Data.Data_Grid[Pos.X + Offset.X][Pos.Y + Offset.Y][Stored_Fluids] -= 2;
		Data.Data_Grid[pt(Pos)][Stored_Power] = min(Data.Data_Grid[pt(Pos)][Stored_Power] + (Target_Item.Chemical_Energy / 100),
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
	if (Data.Data_Grid[pt(Inputs.Data[Rotation])][Stored_Fluids] < 8 || Data.Data_Grid[pt(Outputs.Data[Rotation])][
		Stored_Fluids] > 0) {
		Conditional = false;
	}
	if (Check_Category(Data.Items_Grid[pt(Outputs.Data[Rotation])], Preset_Categories.Coolant)) {
		Conditional = false;
	}
	if (Conditional) {
		Data.Data_Grid[pt(Pos)][Stored_Power] -= 2500;
		Data.Data_Grid[pt(Inputs.Data[Rotation])][Stored_Fluids] -= 8;
		Data.Data_Grid[pt(Outputs.Data[Rotation])][Stored_Fluids] += 8;
		int Temperature = Data.Temperature_Grid[pt(Inputs.Data[Rotation])];
		if (Temperature == 328) {
			Temperature = 327;
		}
		float Benchmark = log10((float)(328 - Temperature) / 263) / log10(0.64);
		Update_Item(Outputs.Data[Rotation], Data.Items_Grid[pt(Inputs.Data[Rotation])], (-263 * pow(0.64, Benchmark + 1)) + 328);
	}
	free_c(Inputs.Data);
	free_c(Outputs.Data);
}

void Cycle_HX(Point Pos, const int Rotation) {
	bool Boiling = false;
	if (Data.Settings_Grid[pt(Interface.Tile)][8] >= LDE_WATERBOILPOINT) {
		Boiling = true;
	}
	Point Outputs[2][4] = {
		{ { Pos.X + 3, Pos.Y }, { Pos.X + 2, Pos.Y + 3 }, { Pos.X, Pos.Y + 2 }, Pos },
		{ Pos, { Pos.X + 2, Pos.Y }, { Pos.X + 3, Pos.Y + 2 }, { Pos.X, Pos.Y + 3 } }
	};
	for (int C1 = 0; C1 < 2; C1++) {
		Point Output_Pos = Outputs[C1][Visual_To_Rotation(Data.Visual_Grid[pt(Pos)])];
		if ((Data.Items_Grid[pt(Output_Pos)] == LDE_INVALID || (Data.Settings_Grid[pt(Pos)][C1 + 9] == Data.Items_Grid[
			pt(Output_Pos)] && !Boiling) || (Data.Items_Grid[pt(Output_Pos)] == Preset_Items.Steam.Identifier && Boiling &&
			C1 == 1)) && Data.Settings_Grid[pt(Pos)][C1 + 5] > 0) {
			Data.Items_Grid[pt(Output_Pos)] = (Boiling && C1 == 1) ? Preset_Items.Steam.Identifier : Data.Settings_Grid[
				pt(Pos)][C1 + 9];
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
	Item_Category Categories[2] = {
		Preset_Categories.Coolant,
		Preset_Categories.Feedwater
	};
	for (int C1 = 0; C1 < 2; C1++) {
		Point Input_Pos = Inputs[C1][Visual_To_Rotation(Data.Visual_Grid[pt(Pos)])];
		if (Check_Category(ID_To_Item(Data.Items_Grid[pt(Input_Pos)]).Identifier, Categories[C1]) && (Data.Settings_Grid[
			pt(Pos)][C1 + 9] == LDE_INVALID || Data.Settings_Grid[pt(Pos)][C1 + 9] == Data.Items_Grid[pt(Input_Pos)])) {
			Data.Settings_Grid[pt(Pos)][C1 + 9] = Data.Items_Grid[pt(Input_Pos)];
			int Volume = Data.Settings_Grid[pt(Pos)][C1 + 5], Intake = 0;
			if (Data.Data_Grid[pt(Input_Pos)][Stored_Fluids] > 0 && Volume < LDE_HXCAPACITY) {
				if (Volume + Data.Data_Grid[pt(Input_Pos)][Stored_Fluids] > LDE_HXCAPACITY) {
					Intake = LDE_HXCAPACITY - Volume;
					Data.Data_Grid[pt(Input_Pos)][Stored_Fluids] -= Intake;
					Data.Settings_Grid[pt(Pos)][C1 + 5] = LDE_HXCAPACITY;
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
	float Remaining = pow(M_E, (-1 * ((LDE_HXEFFICIENCY * (Data.Settings_Grid[pt(Pos)][6] + Data.Settings_Grid[pt(Pos)][5])) / (
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
	if (Data.Settings_Grid[pt(Pos)][5] == LDE_INVALID || Data.Settings_Grid[pt(Pos)][6] == LDE_INVALID) {
		return;
	}
	Data.Settings_Grid[pt(Pos)][7] = 0;
	Node Nodes = { };
	Return_Nodes(&Nodes, Pos, Visual_To_Rotation(Data.Visual_Grid[pt(Pos)]), Preconfigs.STI_Inputs);
	Point Input = Nodes.Data[0];
	Return_Nodes(&Nodes, (Point){ Data.Settings_Grid[pt(Pos)][5], Data.Settings_Grid[pt(Pos)][6] }, Visual_To_Rotation(
		Data.Visual_Grid[(int)(Data.Settings_Grid[pt(Pos)][5])][(int)(Data.Settings_Grid[pt(Pos)][6])]), Preconfigs.STO_Outputs);
	Point Output = Nodes.Data[0];
	free_c(Nodes.Data);
	if (Data.Settings_Grid[pt(Pos)][3] > 0 && Data.Settings_Grid[pt(Pos)][4] == 1 && Data.Items_Grid[pt(Input)] ==
		Preset_Items.Steam.Identifier && Data.Items_Grid[pt(Output)] == Preset_Items.Steam.Identifier) {
		float Transferred = Data.Data_Grid[pt(Output)][Fluid_Cap] - Data.Data_Grid[pt(Output)][Stored_Fluids];
		Transferred = min(Transferred, Data.Data_Grid[pt(Input)][Stored_Fluids]);
		if (Transferred > 0) {
			Data.Data_Grid[pt(Input)][Stored_Fluids] -= Transferred;
			Data.Data_Grid[pt(Output)][Stored_Fluids] += Transferred;
			float Generated = Transferred * LDE_TURBINECOEFFICIENT * log(sqr(Data.Temperature_Grid[pt(Input)])) * log(
				Data.Settings_Grid[pt(Pos)][3] * 1.5f);
			Update_Item(Output, Preset_Items.Steam.Identifier, (Data.Temperature_Grid[pt(Input)] * 0.1f) + 32);
			if (Data.Temperature_Grid[pt(Input)] < 200) {
				Generated = 0;
			}
			Data.Settings_Grid[pt(Pos)][7] = Generated;
			Data.Data_Grid[pt(Pos)][Stored_Power] = min(Data.Data_Grid[pt(Pos)][Power_Cap], Data.Data_Grid[pt(Pos)][
				Stored_Power] + Generated);
		}
	}
}