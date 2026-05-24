#include <items.h>

void Process_I_Recipe() {
//do
}

void Extend_I_Recipe() {
	//do
}

bool Process_O_Recipe(Recipe Chosen, Point Pos, Point* Outputs) {
	int Output_Ct = Chosen.Machine->Output_Ct;
	Outputs = malloc(sizeof(Point) * Output_Ct);
	for (int C1 = 0; C1 < Output_Ct; C1++) {
		Outputs[C1] = (Point){ Chosen.Machine->Outputs[C1].Pos.X + Pos.X, Chosen.Machine->Outputs[C1].Pos.Y + Pos.Y };
	}
	if (Chosen.Time == 1) {
		if (Data.Data_Grid[pt(Pos)][Stored_Power] >= Chosen.Power) {
			if (!Chosen.Voiding_Excess) {
				for (int C1 = 0; C1 < Output_Ct; C1++) {
					if (Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] + Chosen.Output_Counts[C1] < Data.Data_Grid[pt(Outputs[
						C1])][Fluid_Cap]) {
						return false;
					}
				}
			}
			Data.Data_Grid[pt(Pos)][Stored_Power] -= Chosen.Power;
			for (int C1 = 0; C1 < Output_Ct; C1++) {
				Update_Item(Outputs[C1], Chosen.Output_Items[C1]->ID, ktn_room_temp);
			}
			for (int C1 = 0; C1 < Output_Ct; C1++) {
				Point Pos = Outputs[C1];
				Data.Data_Grid[pt(Pos)][Stored_Fluids] = min(Data.Data_Grid[pt(Pos)][Stored_Fluids] + Chosen.Output_Counts[C1],
					Data.Data_Grid[pt(Pos)][Fluid_Cap]);
			}
			return true;
		}
	} else {
		if (Data.Settings_Grid[pt(Pos)][S_Time] <= 0) {
			if (Data.Data_Grid[pt(Pos)][Stored_Power] > Chosen.Power * Chosen.Time) {
				if (!Chosen.Voiding_Excess) {
					for (int C1 = 0; C1 < Output_Ct; C1++) {
						if (Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] > Data.Data_Grid[pt(Outputs[C1])][Fluid_Cap] -
							Chosen.Output_Counts[C1]) {
							return false;
						}
					}
				}
				Data.Settings_Grid[pt(Pos)][S_Time] = Chosen.Time;
				Data.Settings_Grid[pt(Pos)][2] = Chosen.ID;
				return true;
			}
		}
	}
	return false;
}

bool Process_IO_Recipe(Recipe Chosen, Point Pos, Point* Inputs, Point* Outputs) {
	int Input_Ct = Chosen.Machine->Input_Ct;
	Inputs = malloc(sizeof(Point) * Input_Ct);
	int Output_Ct = Chosen.Machine->Output_Ct;
	Outputs = malloc(sizeof(Point) * Output_Ct);
	for (int C1 = 0; C1 < Input_Ct; C1++) {
		Inputs[C1] = (Point){ Chosen.Machine->Inputs[C1].Pos.X + Pos.X, Chosen.Machine->Inputs[C1].Pos.Y + Pos.Y };
	}
	for (int C1 = 0; C1 < Output_Ct; C1++) {
		Outputs[C1] = (Point){ Chosen.Machine->Outputs[C1].Pos.X + Pos.X, Chosen.Machine->Outputs[C1].Pos.Y + Pos.Y };
	}
	if (Chosen.Time == 1) {
		if (Data.Data_Grid[pt(Pos)][Stored_Power] < Chosen.Power) {
			return false;
		}
		if (Chosen.Shuffling_Barred) {
			for (int C1 = 0; C1 < Input_Ct; C1++) {
				if (Data.Data_Grid[pt(Inputs[C1])][Stored_Fluids] < Chosen.Input_Counts[C1]) {
					return false;
				}
			}
			for (int C1 = 0; C1 < Chosen.Inputs; C1++) {
				if (Data.Items_Grid[pt(Inputs[C1])] != Chosen.Input_Items[C1]->ID) {
					return false;
				}
			}
			if (!Chosen.Voiding_Excess) {
				for (int C1 = 0; C1 < Output_Ct; C1++) {
					if (Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] > Data.Data_Grid[pt(Outputs[C1])][Fluid_Cap] -
						Chosen.Output_Counts[C1]) {
						return false;
					}
				}
			}
			for (int C1 = 0; C1 < Input_Ct; C1++) {
				Data.Data_Grid[pt(Inputs[C1])][Stored_Fluids] -= Chosen.Input_Counts[C1];
			}
			for (int C1 = 0; C1 < Output_Ct; C1++) {
				Update_Item(Outputs[C1], Chosen.Output_Items[C1]->ID, ktn_room_temp);
			}
			for (int C1 = 0; C1 < Output_Ct; C1++) {
				Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] = min(Chosen.Output_Counts[C1], Data.Data_Grid[pt(Outputs[C1])][
					Fluid_Cap]);
			}
		} else {
			//later
		}
		Data.Data_Grid[pt(Pos)][Stored_Power] -= Chosen.Power;
		return true;
	} else {
		if (Data.Settings_Grid[pt(Pos)][S_Time] > 0 || Data.Data_Grid[pt(Pos)][Stored_Power] < Chosen.Power * Chosen.Time) {
			return false;
		}
		if (Chosen.Shuffling_Barred) {
			for (int C1 = 0; C1 < Input_Ct; C1++) {
				if (Data.Data_Grid[pt(Inputs[C1])][Stored_Fluids] < Chosen.Input_Counts[C1]) {
					return false;
				}
			}
			for (int C1 = 0; C1 < Chosen.Inputs; C1++) {
				if (Data.Items_Grid[pt(Inputs[C1])] != Chosen.Input_Items[C1]->ID) {
					return false;
				}
			}
			if (!Chosen.Voiding_Excess) {
				for (int C1 = 0; C1 < Output_Ct; C1++) {
					if (Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] > Data.Data_Grid[pt(Outputs[C1])][Fluid_Cap] -
						Chosen.Output_Counts[C1]) {
						return false;
					}
				}
			}
			for (int C1 = 0; C1 < Input_Ct; C1++) {
				Data.Data_Grid[pt(Inputs[C1])][Stored_Fluids] -= Chosen.Input_Counts[C1];
			}
			Data.Settings_Grid[pt(Pos)][S_Time] = Chosen.Time;
			Data.Settings_Grid[pt(Pos)][2] = Chosen.ID;
		} else {
			//later
		}
		return true;
	}
	return false;
}

bool Extend_Recipe(Recipe Chosen, Point Pos, Point* Outputs) {
	int Output_Ct = Chosen.Machine->Output_Ct;
	Outputs = malloc(sizeof(Point) * Output_Ct);
	for (int C1 = 0; C1 < Output_Ct; C1++) {
		Outputs[C1] = (Point){ Chosen.Machine->Outputs[C1].Pos.X + Pos.X, Chosen.Machine->Outputs[C1].Pos.Y + Pos.Y };
	}
	Data.Data_Grid[pt(Pos)][Stored_Power] -= Chosen.Power;
	if (Data.Settings_Grid[pt(Pos)][S_Time] <= 0) {
		Data.Settings_Grid[pt(Pos)][S_Time] = 0;
		for (int C1 = 0; C1 < Output_Ct; C1++) {
			Update_Item(Outputs[C1], Chosen.Output_Items[C1]->ID, ktn_room_temp);
		}
		for (int C1 = 0; C1 < Output_Ct; C1++) {
			Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] = min(Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] +
				Chosen.Output_Counts[C1], Data.Data_Grid[pt(Outputs[C1])][Fluid_Cap]);
		}
		return true;
	}
	return false;
}