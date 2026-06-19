#include <items.h>

#define check_output() if (Chosen.Output_Items[C1]->ID == Metadata.Null_Item.ID) { continue; }

Point Get_Transformed(Machine_Ptr Machine, Node_Data Node, Point Pos) {
	Point Yield = Rotate_Pt(Node.Pos, Machine->Size, Visual_To_Rotation(Data.Visual_Grid[pt(Pos)]));
	Yield.X += Pos.X;
	Yield.Y += Pos.Y;
	return Yield;
}

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
		Outputs[C1] = Get_Transformed(Chosen.Machine, Chosen.Machine->Outputs[C1], Pos);
	}
	if (Chosen.Time == 1) {
		if (Data.Data_Grid[pt(Pos)][Stored_Power] >= Chosen.Power) {
			if (!Chosen.Voiding_Excess) {
				for (int C1 = 0; C1 < Output_Ct; C1++) {
					if (Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] + Chosen.Output_Counts[C1] > Data.Data_Grid[pt(Outputs[
						C1])][Fluid_Cap]) {
						return false;
					}
				}
			}
			Data.Data_Grid[pt(Pos)][Stored_Power] -= Chosen.Power;
			for (int C1 = 0; C1 < Output_Ct; C1++) {
				check_output();
				Update_Item(Outputs[C1], Chosen.Output_Items[C1]->ID, ktn_room_temp);
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
		Inputs[C1] = Get_Transformed(Chosen.Machine, Chosen.Machine->Inputs[C1], Pos);
	}
	for (int C1 = 0; C1 < Output_Ct; C1++) {
		Outputs[C1] = Get_Transformed(Chosen.Machine, Chosen.Machine->Outputs[C1], Pos);
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
			for (int C1 = 0; C1 < Chosen.Machine->Input_Ct; C1++) {
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
				check_output();
				Update_Item(Outputs[C1], Chosen.Output_Items[C1]->ID, ktn_room_temp);
				Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] = min(Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] +
					Chosen.Output_Counts[C1], Data.Data_Grid[pt(Outputs[C1])][Fluid_Cap]);
			}
		} else {
			Point* Subinputs = malloc(sizeof(Point) * Input_Ct);
			for (int C1 = 0; C1 < Input_Ct; C1++) {
				bool Found = false;
				for (int C2 = 0; C2 < Input_Ct; C2++) {
					if (Chosen.Input_Items[C1]->ID == Data.Items_Grid[pt(Inputs[C2])]) {
						Found = true;
						Subinputs[C1] = Inputs[C2];
						break;
					}
				}
				if (!Found || Data.Data_Grid[pt(Subinputs[C1])][Stored_Fluids] < Chosen.Input_Counts[C1]) {
					ktn_free(Subinputs);
					return false;
				}
			}
			if (!Chosen.Voiding_Excess) {
				for (int C1 = 0; C1 < Output_Ct; C1++) {
					if (Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] > Data.Data_Grid[pt(Outputs[C1])][Fluid_Cap] -
						Chosen.Output_Counts[C1]) {
						ktn_free(Subinputs);
						return false;
					}
				}
			}
			for (int C1 = 0; C1 < Input_Ct; C1++) {
				Data.Data_Grid[pt(Subinputs[C1])][Stored_Fluids] -= Chosen.Input_Counts[C1];
			}
			for (int C1 = 0; C1 < Output_Ct; C1++) {
				check_output();
				Update_Item(Outputs[C1], Chosen.Output_Items[C1]->ID, ktn_room_temp);
				Point Pos = Outputs[C1];
				Data.Data_Grid[pt(Pos)][Stored_Fluids] = min(Data.Data_Grid[pt(Pos)][Stored_Fluids] + Chosen.Output_Counts[C1],
					Data.Data_Grid[pt(Pos)][Fluid_Cap]);
			}
			ktn_free(Subinputs);
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
			for (int C1 = 0; C1 < Chosen.Machine->Input_Ct; C1++) {
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
		Outputs[C1] = Get_Transformed(Chosen.Machine, Chosen.Machine->Outputs[C1], Pos);
	}
	Data.Data_Grid[pt(Pos)][Stored_Power] -= Chosen.Power;
	if (Data.Settings_Grid[pt(Pos)][S_Time] < ktn_epsilon) {
		Data.Settings_Grid[pt(Pos)][S_Time] = 0;
		Data.Animation_Grid[pt(Pos)][0] = 0.0f;
		for (int C1 = 0; C1 < Output_Ct; C1++) {
			check_output();
			Update_Item(Outputs[C1], Chosen.Output_Items[C1]->ID, ktn_room_temp);
			Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] = min(Data.Data_Grid[pt(Outputs[C1])][Stored_Fluids] +
				Chosen.Output_Counts[C1], Data.Data_Grid[pt(Outputs[C1])][Fluid_Cap]);
		}
		return true;
	}
	return false;
}
#undef check_output