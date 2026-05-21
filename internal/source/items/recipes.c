#include <items.h>

void Process_I_Recipe() {
//do
}

void Extend_I_Recipe() {
	//do
}

bool Process_O_Recipe(Recipe Selected_Recipe, Point Pos, Node Output_Locations) {
	if (Selected_Recipe.Time == 1) {
		if (Data.Data_Grid[pt(Pos)][Stored_Power] >= Selected_Recipe.Power) {
			if (!Selected_Recipe.Voiding_Excess) {
				for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
					if (Data.Data_Grid[pt(Output_Locations.Data[C1])][Stored_Fluids] + Selected_Recipe.Output_Counts[C1] <
						Data.Data_Grid[pt(Output_Locations.Data[C1])][Fluid_Cap]) {
						return false;
					}
				}
			}
			Data.Data_Grid[pt(Pos)][Stored_Power] -= Selected_Recipe.Power;
			for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
				Update_Item(Output_Locations.Data[C1], Selected_Recipe.Output_Items[C1].Identifier, ktn_room_temp);
			}
			for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
				Point Pos = Output_Locations.Data[C1];
				Data.Data_Grid[pt(Pos)][Stored_Fluids] = min(Data.Data_Grid[pt(Pos)][Stored_Fluids] +
					Selected_Recipe.Output_Counts[C1], Data.Data_Grid[pt(Pos)][Fluid_Cap]);
			}
			return true;
		}
	} else {
		if (Data.Settings_Grid[pt(Pos)][S_Time] <= 0) {
			if (Data.Data_Grid[pt(Pos)][Stored_Power] > Selected_Recipe.Power * Selected_Recipe.Time) {
				if (!Selected_Recipe.Voiding_Excess) {
					for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
						if (Data.Data_Grid[pt(Output_Locations.Data[C1])][Stored_Fluids] > Data.Data_Grid[pt(
							Output_Locations.Data[C1])][Fluid_Cap] - Selected_Recipe.Output_Counts[C1]) {
							return false;
						}
					}
				}
				Data.Settings_Grid[pt(Pos)][S_Time] = Selected_Recipe.Time;
				Data.Settings_Grid[pt(Pos)][2] = Selected_Recipe.ID;
				return true;
			}
		}
	}
	return false;
}

bool Process_IO_Recipe(Recipe Selected_Recipe, Point Pos, Node Input_Locations, Node Output_Locations) {
	if (Selected_Recipe.Time == 1) {
		if (Data.Data_Grid[pt(Pos)][Stored_Power] < Selected_Recipe.Power) {
			return false;
		}
		if (Selected_Recipe.Shuffling_Barred) {
			for (int C1 = 0; C1 < Input_Locations.Length; C1++) {
				if (Data.Data_Grid[pt(Input_Locations.Data[C1])][Stored_Fluids] < Selected_Recipe.Input_Counts[C1]) {
					return false;
				}
			}
			for (int C1 = 0; C1 < Selected_Recipe.Inputs; C1++) {
				if (Data.Items_Grid[pt(Input_Locations.Data[C1])] != Selected_Recipe.Input_Items[C1].Identifier) {
					return false;
				}
			}
			if (!Selected_Recipe.Voiding_Excess) {
				for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
					if (Data.Data_Grid[pt(Output_Locations.Data[C1])][Stored_Fluids] > Data.Data_Grid[pt(
						Output_Locations.Data[C1])][Fluid_Cap] - Selected_Recipe.Output_Counts[C1]) {
						return false;
					}
				}
			}
			for (int C1 = 0; C1 < Input_Locations.Length; C1++) {
				Data.Data_Grid[pt(Input_Locations.Data[C1])][Stored_Fluids] -= Selected_Recipe.Input_Counts[C1];
			}
			for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
				Update_Item(Output_Locations.Data[C1], Selected_Recipe.Output_Items[C1].Identifier, ktn_room_temp);
			}
			for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
				Data.Data_Grid[pt(Output_Locations.Data[C1])][Stored_Fluids] = min(Selected_Recipe.Output_Counts[C1],
					Data.Data_Grid[pt(Output_Locations.Data[C1])][Fluid_Cap]);
			}
		} else {
			int* Inputs = malloc(sizeof(int) * (Input_Locations.Length + 1));
			int* Positions = malloc(sizeof(int) * (Input_Locations.Length + 1));
			for (int C1 = 0; C1 < Input_Locations.Length; C1++) {
				Inputs[C1] = Data.Items_Grid[pt(Input_Locations.Data[C1])];
			}
			Inputs[Input_Locations.Length] = ktn_terminator;
			int Index = 0;
			for (int C1 = 0; C1 < Selected_Recipe.Inputs; C1++) {
				bool Unsatiated = true;
				for (int C2 = 0; C2 < ktn_intlen(Inputs); C2++) {
					if (Selected_Recipe.Input_Items[C1].Identifier == Inputs[C2]) {
						Unsatiated = false;
						Inputs[C2] = ktn_invalid;
						Positions[Index] = C2;
						Index++;
					}
				}
				if (Unsatiated) {
					return false;
				}
			}
			Positions[Index] = ktn_terminator;
			for (int C1 = 0; C1 < ktn_intlen(Inputs); C1++) {
				if (Inputs[C1] != ktn_invalid) {
					return false;
				}
			}
			for (int C1 = 0; C1 < ktn_intlen(Positions); C1++) {
				if (Data.Data_Grid[pt(Input_Locations.Data[Positions[C1]])][Stored_Fluids] < Selected_Recipe.Input_Counts[C1]) {
					return false;
				}
			}
			if (!Selected_Recipe.Voiding_Excess) {
				for (int C1 = 0; C1 < Selected_Recipe.Outputs; C1++) {
					if (Data.Data_Grid[pt(Output_Locations.Data[C1])][Stored_Fluids] > Data.Data_Grid[pt(Output_Locations.Data[
						C1])][Fluid_Cap] - Selected_Recipe.Output_Counts[C1]) {
						return false;
					}
				}
			}
			for (int C1 = 0; C1 < ktn_intlen(Positions); C1++) {
				Data.Data_Grid[pt(Input_Locations.Data[Positions[C1]])][Stored_Fluids] -= Selected_Recipe.Input_Counts[C1];
			}
			for (int C1 = 0; C1 < Selected_Recipe.Outputs; C1++) {
				Update_Item(Output_Locations.Data[C1], Selected_Recipe.Output_Items[C1].Identifier, ktn_room_temp);
			}
			for (int C1 = 0; C1 < Selected_Recipe.Outputs; C1++) {
				Data.Data_Grid[pt(Output_Locations.Data[C1])][Stored_Fluids] = min(Data.Data_Grid[
					pt(Output_Locations.Data[C1])][Stored_Fluids] + Selected_Recipe.Output_Counts[C1], Data.Data_Grid[
					pt(Output_Locations.Data[C1])][Fluid_Cap]);
			}
			ktn_free(Inputs);
			ktn_free(Positions);
		}
		Data.Data_Grid[pt(Pos)][Stored_Power] -= Selected_Recipe.Power;
		return true;
	} else {
		if (Data.Settings_Grid[pt(Pos)][S_Time] > 0 || Data.Data_Grid[pt(Pos)][Stored_Power] < Selected_Recipe.Power *
			Selected_Recipe.Time) {
			return false;
		}
		if (Selected_Recipe.Shuffling_Barred) {
			for (int C1 = 0; C1 < Input_Locations.Length; C1++) {
				if (Data.Data_Grid[pt(Input_Locations.Data[C1])][Stored_Fluids] < Selected_Recipe.Input_Counts[
					C1]) {
					return false;
				}
			}
			for (int C1 = 0; C1 < Selected_Recipe.Inputs; C1++) {
				if (Data.Items_Grid[pt(Input_Locations.Data[C1])] != Selected_Recipe.Input_Items[C1].Identifier) {
					return false;
				}
			}
			if (!Selected_Recipe.Voiding_Excess) {
				for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
					if (Data.Data_Grid[pt(Output_Locations.Data[C1])][Stored_Fluids] > Data.Data_Grid[
						pt(Output_Locations.Data[C1])][Fluid_Cap] - Selected_Recipe.Output_Counts[C1]) {
						return false;
					}
				}
			}
			for (int C1 = 0; C1 < Input_Locations.Length; C1++) {
				Data.Data_Grid[pt(Input_Locations.Data[C1])][Stored_Fluids] -= Selected_Recipe.Input_Counts[C1];
			}
			Data.Settings_Grid[pt(Pos)][S_Time] = Selected_Recipe.Time;
			Data.Settings_Grid[pt(Pos)][2] = Selected_Recipe.ID;
		} else {
			//later
		}
		return true;
	}
	return false;
}

bool Extend_Recipe(Recipe Selected_Recipe, Point Pos, Node Preconfiguration[4]) {
	Data.Data_Grid[pt(Pos)][Stored_Power] -= Selected_Recipe.Power;
	if (Data.Settings_Grid[pt(Pos)][S_Time] <= 0) {
		Node Nodes = { };
		Return_Nodes(&Nodes, Pos, Visual_To_Rotation(Data.Visual_Grid[pt(Pos)]), Preconfiguration);
		Data.Settings_Grid[pt(Pos)][S_Time] = 0;
		for (int C1 = 0; C1 < Selected_Recipe.Outputs; C1++) {
			Update_Item(Nodes.Data[C1], Selected_Recipe.Output_Items[C1].Identifier, ktn_room_temp);
		}
		for (int C1 = 0; C1 < Selected_Recipe.Outputs; C1++) {
			Data.Data_Grid[pt(Nodes.Data[C1])][Stored_Fluids] = min(Data.Data_Grid[pt(Nodes.Data[C1])][Stored_Fluids] +
				Selected_Recipe.Output_Counts[C1], Data.Data_Grid[pt(Nodes.Data[C1])][Fluid_Cap]);
		}
		ktn_free(Nodes.Data);
		return true;
	}
	return false;
}