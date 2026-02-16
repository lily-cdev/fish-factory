#include <grid.h>

void Cycle_RTG(const int X, const int Y, const int Rotation) {
	Data.Data_Grid[X][Y][Stored_Power] = min(Data.Data_Grid[X][Y][Stored_Power] + 0.5, Data.Data_Grid[X][Y][Power_Cap]);
}

void Cycle_Bio_Gen(const int X, const int Y, const int Rotation) {
    Point Offset = { 0, 2 };
	switch (Visual_To_Rotation(Data.Visual_Grid[X][Y])) {
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
	Item_Stack Target_Item = Get_Item(X + Offset.X, Y + Offset.Y);
	Data.Animation_Grid[X][Y][0] = 0;
	if (Check_Category(Target_Item.Identifier, Preset_Categories.Biomass) > 0 && Data.Data_Grid[X + Offset.X][Y + Offset.Y][
		Stored_Fluids] >= 2) {
		Data.Data_Grid[X + Offset.X][Y + Offset.Y][Stored_Fluids] -= 2;
		Data.Data_Grid[X][Y][Stored_Power] = min(Data.Data_Grid[X][Y][Stored_Power] + (Target_Item.Chemical_Energy / 100),
			Data.Data_Grid[X][Y][Power_Cap]);
		Data.Animation_Grid[X][Y][0] = 1;
	}
}

void Cycle_Geo_Well(const int X, const int Y, const int Rotation) {
	bool Conditional = true;
	Node Inputs = { };
	Node Outputs = { };
	if (Data.Data_Grid[X][Y][Stored_Power] < 2500) {
		Conditional = false;
	}
	Return_Nodes(&Inputs, X, Y, Rotation, Preconfigs.GW_Inputs);
	Return_Nodes(&Outputs, X, Y, Rotation, Preconfigs.GW_Outputs);
	if (Data.Data_Grid[Inputs.Data[Rotation].X][Inputs.Data[Rotation].Y][Stored_Fluids] < 8 || Data.Data_Grid[
		Outputs.Data[Rotation].X][Outputs.Data[Rotation].Y][Stored_Fluids] > 0) {
		Conditional = false;
	}
	if (Check_Category(Data.Items_Grid[Outputs.Data[Rotation].X][Outputs.Data[Rotation].Y], Preset_Categories.Coolant)) {
		Conditional = false;
	}
	if (Conditional) {
		Data.Data_Grid[X][Y][Stored_Power] -= 2500;
		Data.Data_Grid[Inputs.Data[Rotation].X][Inputs.Data[Rotation].Y][Stored_Fluids] -= 8;
		Data.Data_Grid[Outputs.Data[Rotation].X][Outputs.Data[Rotation].Y][Stored_Fluids] += 8;
		int Temperature = Data.Temperature_Grid[Inputs.Data[Rotation].X][Inputs.Data[Rotation].Y];
		if (Temperature == 328) {
			Temperature = 327;
		}
		float Benchmark = log10((float)(328 - Temperature) / 263) / log10(0.64);
		Update_Item(Outputs.Data[Rotation].X, Outputs.Data[Rotation].Y, Data.Items_Grid[Inputs.Data[Rotation].X][
			Inputs.Data[Rotation].Y], (-263 * pow(0.64, Benchmark + 1)) + 328);
	}
	free_c(Inputs.Data);
	free_c(Outputs.Data);
}

void Cycle_HX(const int X, const int Y, const int Rotation) {
	bool Boiling = false;
	if (Data.Settings_Grid[Interface.Tile.X][Interface.Tile.Y][8] >= LDE_WATERBOILPOINT) {
		Boiling = true;
	}
	Point Outputs[2][4] = {
		{ { X + 3, Y }, { X + 2, Y + 3 }, { X, Y + 2 }, { X, Y } },
		{ { X, Y }, { X + 2, Y }, { X + 3, Y + 2 }, { X, Y + 3 } }
	};
	for (int C1 = 0; C1 < 2; C1++) {
		Point Output_Pos = Outputs[C1][Visual_To_Rotation(Data.Visual_Grid[X][Y])];
		if ((Data.Items_Grid[Output_Pos.X][Output_Pos.Y] == LDE_INVALID || (Data.Settings_Grid[X][Y][C1 + 9] ==
			Data.Items_Grid[Output_Pos.X][Output_Pos.Y] && !Boiling) || (Data.Items_Grid[Output_Pos.X][Output_Pos.Y] ==
			Preset_Items.Steam.Identifier && Boiling && C1 == 1)) && Data.Settings_Grid[X][Y][C1 + 5] > 0) {
			Data.Items_Grid[Output_Pos.X][Output_Pos.Y] = (Boiling && C1 == 1) ? Preset_Items.Steam.Identifier :
				Data.Settings_Grid[X][Y][C1 + 9];
			float Draining_Amount = min(Data.Settings_Grid[X][Y][C1 + 3], Data.Settings_Grid[X][Y][C1 + 5]);
			Draining_Amount = min(Draining_Amount, Data.Data_Grid[Output_Pos.X][Output_Pos.Y][Fluid_Cap] - Data.Data_Grid[
				Output_Pos.X][Output_Pos.Y][Stored_Fluids]);
			Data.Data_Grid[Output_Pos.X][Output_Pos.Y][Stored_Fluids] += Draining_Amount;
			Data.Settings_Grid[X][Y][C1 + 5] -= Draining_Amount;
		}
	}
	Point Inputs[2][4] = {
		{ { X + 3, Y + 2 }, { X, Y + 3 }, { X, Y }, { X + 2, Y } },
		{ { X, Y + 2 }, { X, Y }, { X + 3, Y }, { X + 2, Y + 3 } }
	};
	Item_Category Categories[2] = {
		Preset_Categories.Coolant,
		Preset_Categories.Feedwater
	};
	for (int C1 = 0; C1 < 2; C1++) {
		Point Input_Pos = Inputs[C1][Visual_To_Rotation(Data.Visual_Grid[X][Y])];
		if (Check_Category(ID_To_Item(Data.Items_Grid[Input_Pos.X][Input_Pos.Y]).Identifier, Categories[C1]) && (
			Data.Settings_Grid[X][Y][C1 + 9] == LDE_INVALID || Data.Settings_Grid[X][Y][C1 + 9] == Data.Items_Grid[
			Input_Pos.X][Input_Pos.Y])) {
			Data.Settings_Grid[X][Y][C1 + 9] = Data.Items_Grid[Input_Pos.X][Input_Pos.Y];
			int Volume = Data.Settings_Grid[X][Y][C1 + 5], Intake = 0;
			if (Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids] > 0 && Volume < LDE_HXCAPACITY) {
				if (Volume + Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids] > LDE_HXCAPACITY) {
					Intake = LDE_HXCAPACITY - Volume;
					Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids] -= Intake;
					Data.Settings_Grid[X][Y][C1 + 5] = LDE_HXCAPACITY;
				} else {
					Intake = Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids];
					Data.Settings_Grid[X][Y][C1 + 5] += Intake;
					Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids] = 0;
				}
			}
			if (Volume + Intake != 0) {
				Data.Settings_Grid[X][Y][C1 + 7] = ((Data.Settings_Grid[X][Y][C1 + 7] * Volume) + (Data.Temperature_Grid[
					Input_Pos.X][Input_Pos.Y] * Intake)) / (Volume + Intake);
			}
		}
	}
	float Temp_Equil = ((Data.Settings_Grid[X][Y][6] * Data.Settings_Grid[X][Y][8]) + (Data.Settings_Grid[X][Y][5] *
		Data.Settings_Grid[X][Y][7])) / (Data.Settings_Grid[X][Y][6] + Data.Settings_Grid[X][Y][5]);
	float Difference = Data.Settings_Grid[X][Y][7] - Data.Settings_Grid[X][Y][8];
	float Remaining = pow(M_E, (-1 * ((LDE_HXEFFICIENCY * (Data.Settings_Grid[X][Y][6] + Data.Settings_Grid[X][Y][5])) / (
		4.186 * Data.Settings_Grid[X][Y][6] * Data.Settings_Grid[X][Y][5]))));
	float FW_Yield = Temp_Equil - (((Data.Settings_Grid[X][Y][5] / (Data.Settings_Grid[X][Y][6] + Data.Settings_Grid[X][Y][
		5])) * Difference) * Remaining);
	float HM_Yield = Temp_Equil + (((Data.Settings_Grid[X][Y][6] / (Data.Settings_Grid[X][Y][6] + Data.Settings_Grid[X][Y][
		5])) * Difference) * Remaining);
	if (HM_Yield > 0 && FW_Yield > 0) {
		Data.Settings_Grid[X][Y][7] = HM_Yield;
		Data.Settings_Grid[X][Y][8] = FW_Yield;
	}
}

void Cycle_Turbine_Input(const int X, const int Y, const int Rotation) {
	Data.Settings_Grid[X][Y][7] = 0;
	Node Inputs = { };
	Node Outputs = { };
	Return_Nodes(&Inputs, X, Y, Visual_To_Rotation(Data.Visual_Grid[X][Y]), Preconfigs.STI_Inputs);
	Return_Nodes(&Outputs, Data.Settings_Grid[X][Y][5], Data.Settings_Grid[X][Y][6], Visual_To_Rotation(Data.Visual_Grid[
		(int)(Data.Settings_Grid[X][Y][5])][(int)(Data.Settings_Grid[X][Y][6])]), Preconfigs.STO_Outputs);
	if (Data.Settings_Grid[X][Y][3] > 0 && Data.Settings_Grid[X][Y][4] == 1 && Data.Items_Grid[Inputs.Data[0].X][
		Inputs.Data[0].Y] == Preset_Items.Steam.Identifier && Data.Items_Grid[Outputs.Data[0].X][Outputs.Data[0].Y] ==
		Preset_Items.Steam.Identifier) {
		float Transferred = Data.Data_Grid[Outputs.Data[0].X][Outputs.Data[0].Y][Fluid_Cap] - Data.Data_Grid[Outputs.Data[
			0].X][Outputs.Data[0].Y][Stored_Fluids];
		Transferred = min(Transferred, Data.Data_Grid[Inputs.Data[0].X][Inputs.Data[0].Y][Stored_Fluids]);
		if (Transferred > 0) {
			Data.Data_Grid[Inputs.Data[0].X][Inputs.Data[0].Y][Stored_Fluids] -= Transferred;
			Data.Data_Grid[Outputs.Data[0].X][Outputs.Data[0].Y][Stored_Fluids] += Transferred;
			float Generated = Transferred * LDE_TURBINECOEFFICIENT * log(sqr(Data.Temperature_Grid[Inputs.Data[0].X][
				Inputs.Data[0].Y])) * log(Data.Settings_Grid[X][Y][3] * 1.5f);
			Update_Item(Outputs.Data[0].X, Outputs.Data[0].Y, Preset_Items.Steam.Identifier, (Data.Temperature_Grid[
				Inputs.Data[0].X][Inputs.Data[0].Y] * 0.1) + 32);
			if (Data.Temperature_Grid[Inputs.Data[0].X][Inputs.Data[0].Y] < 200) {
				Generated = 0;
			}
			Data.Settings_Grid[X][Y][7] = Generated;
			Data.Data_Grid[X][Y][Stored_Power] = min(Data.Data_Grid[X][Y][Power_Cap], Data.Data_Grid[X][Y][Stored_Power] +
				Generated);
		}
	}
	free_c(Inputs.Data);
	free_c(Outputs.Data);
}