#include <items.h>

void Process_I_Recipe() {
//do
}

void Extend_I_Recipe() {
	//do
}

bool Process_O_Recipe(Recipe Selected_Recipe, int X, int Y, Node Output_Locations) {
	if (Selected_Recipe.Time == 1) {
		if (Data.Data_Grid[X][Y][Stored_Power] >= Selected_Recipe.Power) {
			if (Selected_Recipe.Voiding_Excess) {
				for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
					if (Data.Data_Grid[Output_Locations.Data[C1].X][Output_Locations.Data
						[C1].Y][Stored_Fluids] + Selected_Recipe.Output_Counts[C1] <
						Data.Data_Grid[Output_Locations.Data[C1].X][Output_Locations.Data
						[C1].Y][Fluid_Cap]) {
						return false;
					}
				}
			}
			Data.Data_Grid[X][Y][Stored_Power] -= Selected_Recipe.Power;
			for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
				Update_Item(Output_Locations.Data[C1].X, Output_Locations.Data[C1].Y,
					Selected_Recipe.Output_Items[C1].Identifier, LDE_ROOMTEMP);
			}
			for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
				Data.Data_Grid[Output_Locations.Data[C1].X][Output_Locations.Data[C1].Y][Stored_Fluids] =
					min(Selected_Recipe.Output_Counts[C1], Data.Data_Grid[Output_Locations.Data[C1].X][
					Output_Locations.Data[C1].Y][Fluid_Cap]);
			}
			return true;
		}
	} else {
		//do
	}
	return false;
}

void Extend_O_Recipe() {
//do
}

bool Process_Recipe(Recipe Selected_Recipe, int X, int Y, Node Input_Locations, Node Output_Locations) {
	if (Selected_Recipe.Time == 1) {
		if (Data.Data_Grid[X][Y][Stored_Power] >= Selected_Recipe.Power) {
			if (Selected_Recipe.Shuffling_Barred) {
				for (int C1 = 0; C1 < Input_Locations.Length; C1++) {
					if (Data.Data_Grid[Input_Locations.Data[C1].X][Input_Locations.Data[
						C1].Y][Stored_Fluids] < Selected_Recipe.Input_Counts[C1]) {
						return false;
					}
				}
				for (int C1 = 0; C1 < Selected_Recipe.Inputs; C1++) {
					if (Data.Items_Grid[Input_Locations.Data[C1].X][Input_Locations.Data[
						C1].Y] !=	Selected_Recipe.Input_Items[C1].Identifier) {
						return false;
					}
				}
				if (!Selected_Recipe.Voiding_Excess) {
					for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
						if (Data.Data_Grid[Output_Locations.Data[C1].X][
							Output_Locations.Data[C1].Y][Stored_Fluids] >
							Data.Data_Grid[Output_Locations.Data[C1].X][
							Output_Locations.Data[C1].Y][Fluid_Cap] -
							Selected_Recipe.Output_Counts[C1]) {
							return false;
						}
					}
				}
				for (int C1 = 0; C1 < Input_Locations.Length; C1++) {
					Data.Data_Grid[Input_Locations.Data[C1].X][Input_Locations.Data[
						C1].Y][Stored_Fluids] -= Selected_Recipe.Input_Counts[C1];
				}
				for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
					Update_Item(Output_Locations.Data[C1].X, Output_Locations.Data[C1].Y,
						Selected_Recipe.Output_Items[C1].Identifier, LDE_ROOMTEMP);
				}
				for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
					Data.Data_Grid[Output_Locations.Data[C1].X][Output_Locations.Data[C1].Y][Stored_Fluids] =
						min(Selected_Recipe.Output_Counts[C1], Data.Data_Grid[Output_Locations.Data[C1].X][
						Output_Locations.Data[C1].Y][Fluid_Cap]);
				}
			} else {
				int* Inputs = malloc(sizeof(int) * (Input_Locations.Length + 1));
				int* Positions = malloc(sizeof(int) * (Input_Locations.Length + 1));
				for (int C1 = 0; C1 < Input_Locations.Length; C1++) {
					Inputs[C1] = Data.Items_Grid[Input_Locations.Data[C1].X][Input_Locations.Data[C1].Y];
				}
				Inputs[Input_Locations.Length] = LDE_TERMINATOR;
				int Index = 0;
				for (int C1 = 0; C1 < Selected_Recipe.Inputs; C1++) {
					bool Unsatiated = true;
					for (int C2 = 0; C2 < intlen(Inputs); C2++) {
						if (Selected_Recipe.Input_Items[C1].Identifier == Inputs[C2]) {
							Unsatiated = false;
							Inputs[C2] = LDE_INVALID;
							Positions[Index] = C2;
							Index++;
						}
					}
					if (Unsatiated) {
						return false;
					}
				}
				Positions[Index] = LDE_TERMINATOR;
				for (int C1 = 0; C1 < intlen(Inputs); C1++) {
					if (Inputs[C1] != LDE_INVALID) {
						return false;
					}
				}
				for (int C1 = 0; C1 < intlen(Positions); C1++) {
					if (Data.Data_Grid[Input_Locations.Data[Positions[C1]].X][Input_Locations.Data[
						Positions[C1]].Y][Stored_Fluids] < Selected_Recipe.Input_Counts[C1]) {
						return false;
					}
				}
				if (!Selected_Recipe.Voiding_Excess) {
					for (int C1 = 0; C1 < Selected_Recipe.Outputs; C1++) {
						if (Data.Data_Grid[Output_Locations.Data[C1].X][Output_Locations.Data[C1].Y][Stored_Fluids] >
							Data.Data_Grid[Output_Locations.Data[C1].X][Output_Locations.Data[C1].Y][Fluid_Cap] -
							Selected_Recipe.Output_Counts[C1]) {
							return false;
						}
					}
				}
				for (int C1 = 0; C1 < intlen(Positions); C1++) {
					Data.Data_Grid[Input_Locations.Data[Positions[C1]].X][Input_Locations.Data[
						Positions[C1]].Y][Stored_Fluids] -= Selected_Recipe.Input_Counts[C1];
				}
				for (int C1 = 0; C1 < Selected_Recipe.Outputs; C1++) {
					Update_Item(Output_Locations.Data[C1].X, Output_Locations.Data[C1].Y,
						Selected_Recipe.Output_Items[C1].Identifier, LDE_ROOMTEMP);
				}
				for (int C1 = 0; C1 < Selected_Recipe.Outputs; C1++) {
					Data.Data_Grid[Output_Locations.Data[C1].X][Output_Locations.Data[C1].Y][Stored_Fluids] =
						min(Data.Data_Grid[Output_Locations.Data[C1].X][Output_Locations.Data[C1].Y][
						Stored_Fluids] + Selected_Recipe.Output_Counts[C1], Data.Data_Grid[Output_Locations.Data[
						C1].X][Output_Locations.Data[C1].Y][Fluid_Cap]);
				}
			}
			Data.Data_Grid[X][Y][Stored_Power] -= Selected_Recipe.Power;
			return true;
		}
	} else {
		if (Data.Settings_Grid[X][Y][1] <= 0) {
			if (Data.Data_Grid[X][Y][Stored_Power] > Selected_Recipe.Power * Selected_Recipe.Time) {
				if (Selected_Recipe.Shuffling_Barred) {
					for (int C1 = 0; C1 < Input_Locations.Length; C1++) {
						if (Data.Data_Grid[Input_Locations.Data[C1].X][Input_Locations.Data[C1].Y][Stored_Fluids] <
							Selected_Recipe.Input_Counts[C1]) {
							return false;
						}
					}
					for (int C1 = 0; C1 < Selected_Recipe.Inputs; C1++) {
						if (Data.Items_Grid[Input_Locations.Data[C1].X][Input_Locations.Data[C1].Y] !=
							Selected_Recipe.Input_Items[C1].Identifier) {
							return false;
						}
					}
					if (!Selected_Recipe.Voiding_Excess) {
						for (int C1 = 0; C1 < Output_Locations.Length; C1++) {
							if (Data.Data_Grid[Output_Locations.Data[C1].X][Output_Locations.Data[C1].Y][
								Stored_Fluids] > Data.Data_Grid[Output_Locations.Data[C1].X][Output_Locations.Data[
								C1].Y][Fluid_Cap] - Selected_Recipe.Output_Counts[C1]) {
								return false;
							}
						}
					}
					for (int C1 = 0; C1 < Input_Locations.Length; C1++) {
						Data.Data_Grid[Input_Locations.Data[C1].X][Input_Locations.Data[C1].Y][Stored_Fluids] -=
							Selected_Recipe.Input_Counts[C1];
					}
					Data.Settings_Grid[X][Y][1] = Selected_Recipe.Time;
					Data.Settings_Grid[X][Y][2] = Selected_Recipe.ID;
				}
				return true;
			}
		}
	}
	return false;
}

void Extend_Recipe(Recipe Selected_Recipe, int X, int Y, Node Preconfiguration[4]) {
	Node Nodes;
	Return_Nodes(&Nodes, X, Y, Visual_To_Rotation(Data.Visual_Grid[X][Y]), Preconfiguration);
	Data.Data_Grid[X][Y][Stored_Power] -= Selected_Recipe.Power;
	if (Data.Settings_Grid[X][Y][1] <= 0) {
		Data.Settings_Grid[X][Y][1] = 0;
		for (int C1 = 0; C1 < Selected_Recipe.Outputs; C1++) {
			Update_Item(Nodes.Data[C1].X, Nodes.Data[C1].Y, Selected_Recipe.Output_Items[C1].Identifier,
				LDE_ROOMTEMP);
		}
		for (int C1 = 0; C1 < Selected_Recipe.Outputs; C1++) {
			Data.Data_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y][Stored_Fluids] = min(Data.Data_Grid[Nodes.Data[
				C1].X][Nodes.Data[C1].Y][Stored_Fluids] + Selected_Recipe.Output_Counts[C1], Data.Data_Grid[
				Nodes.Data[C1].X][Nodes.Data[C1].Y][Fluid_Cap]);
		}
	}
	free_c(Nodes.Data);
}