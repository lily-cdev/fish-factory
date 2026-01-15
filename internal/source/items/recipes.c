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
				for (int Counter = 0; Counter < Output_Locations.Length; Counter++) {
					if (Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data
						[Counter].Y][Stored_Fluids] + Selected_Recipe.Output_Counts[Counter] <
						Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data
						[Counter].Y][Fluid_Cap]) {
						return false;
					}
				}
			}
			Data.Data_Grid[X][Y][Stored_Power] -= Selected_Recipe.Power;
			for (int Counter = 0; Counter < Output_Locations.Length; Counter++) {
				Update_Item(Output_Locations.Data[Counter].X, Output_Locations.Data[Counter].Y,
					Selected_Recipe.Output_Items[Counter].Identifier, LDE_ROOMTEMP);
			}
			for (int Counter = 0; Counter < Output_Locations.Length; Counter++) {
				Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data[Counter].Y][Stored_Fluids] =
					min(Selected_Recipe.Output_Counts[Counter], Data.Data_Grid[Output_Locations.Data[Counter].X][
					Output_Locations.Data[Counter].Y][Fluid_Cap]);
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
				for (int Counter = 0; Counter < Input_Locations.Length; Counter++) {
					if (Data.Data_Grid[Input_Locations.Data[Counter].X][Input_Locations.Data[
						Counter].Y][Stored_Fluids] < Selected_Recipe.Input_Counts[Counter]) {
						return false;
					}
				}
				for (int Counter = 0; Counter < Selected_Recipe.Inputs; Counter++) {
					if (Data.Items_Grid[Input_Locations.Data[Counter].X][Input_Locations.Data[
						Counter].Y] !=	Selected_Recipe.Input_Items[Counter].Identifier) {
						return false;
					}
				}
				if (!Selected_Recipe.Voiding_Excess) {
					for (int Counter = 0; Counter < Output_Locations.Length; Counter++) {
						if (Data.Data_Grid[Output_Locations.Data[Counter].X][
							Output_Locations.Data[Counter].Y][Stored_Fluids] >
							Data.Data_Grid[Output_Locations.Data[Counter].X][
							Output_Locations.Data[Counter].Y][Fluid_Cap] -
							Selected_Recipe.Output_Counts[Counter]) {
							return false;
						}
					}
				}
				for (int Counter = 0; Counter < Input_Locations.Length; Counter++) {
					Data.Data_Grid[Input_Locations.Data[Counter].X][Input_Locations.Data[
						Counter].Y][Stored_Fluids] -= Selected_Recipe.Input_Counts[Counter];
				}
				for (int Counter = 0; Counter < Output_Locations.Length; Counter++) {
					Update_Item(Output_Locations.Data[Counter].X, Output_Locations.Data[Counter].Y,
						Selected_Recipe.Output_Items[Counter].Identifier, LDE_ROOMTEMP);
				}
				for (int Counter = 0; Counter < Output_Locations.Length; Counter++) {
					Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data[Counter].Y][Stored_Fluids] =
						min(Selected_Recipe.Output_Counts[Counter], Data.Data_Grid[Output_Locations.Data[Counter].X][
						Output_Locations.Data[Counter].Y][Fluid_Cap]);
				}
			} else {
				int* Inputs = malloc(sizeof(int) * (Input_Locations.Length + 1));
				int* Positions = malloc(sizeof(int) * (Input_Locations.Length + 1));
				for (int Counter = 0; Counter < Input_Locations.Length; Counter++) {
					Inputs[Counter] = Data.Items_Grid[Input_Locations.Data[Counter].X][Input_Locations.Data[Counter].Y];
				}
				Inputs[Input_Locations.Length] = LDE_TERMINATOR;
				int Index = 0;
				for (int Counter1 = 0; Counter1 < Selected_Recipe.Inputs; Counter1++) {
					bool Unsatiated = true;
					for (int Counter2 = 0; Counter2 < intlen(Inputs); Counter2++) {
						if (Selected_Recipe.Input_Items[Counter1].Identifier == Inputs[Counter2]) {
							Unsatiated = false;
							Inputs[Counter2] = LDE_INVALID;
							Positions[Index] = Counter2;
							Index++;
						}
					}
					if (Unsatiated) {
						return false;
					}
				}
				Positions[Index] = LDE_TERMINATOR;
				for (int Counter = 0; Counter < intlen(Inputs); Counter++) {
					if (Inputs[Counter] != LDE_INVALID) {
						return false;
					}
				}
				for (int Counter = 0; Counter < intlen(Positions); Counter++) {
					if (Data.Data_Grid[Input_Locations.Data[Positions[Counter]].X][Input_Locations.Data[
						Positions[Counter]].Y][Stored_Fluids] < Selected_Recipe.Input_Counts[Counter]) {
						return false;
					}
				}
				if (!Selected_Recipe.Voiding_Excess) {
					for (int Counter = 0; Counter < Selected_Recipe.Outputs; Counter++) {
						if (Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data[Counter].Y][Stored_Fluids] >
							Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data[Counter].Y][Fluid_Cap] -
							Selected_Recipe.Output_Counts[Counter]) {
							return false;
						}
					}
				}
				for (int Counter = 0; Counter < intlen(Positions); Counter++) {
					Data.Data_Grid[Input_Locations.Data[Positions[Counter]].X][Input_Locations.Data[
						Positions[Counter]].Y][Stored_Fluids] -= Selected_Recipe.Input_Counts[Counter];
				}
				for (int Counter = 0; Counter < Selected_Recipe.Outputs; Counter++) {
					Update_Item(Output_Locations.Data[Counter].X, Output_Locations.Data[Counter].Y,
						Selected_Recipe.Output_Items[Counter].Identifier, LDE_ROOMTEMP);
				}
				for (int Counter = 0; Counter < Selected_Recipe.Outputs; Counter++) {
					Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data[Counter].Y][Stored_Fluids] =
						min(Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data[Counter].Y][
						Stored_Fluids] + Selected_Recipe.Output_Counts[Counter], Data.Data_Grid[Output_Locations.Data[
						Counter].X][Output_Locations.Data[Counter].Y][Fluid_Cap]);
				}
			}
			Data.Data_Grid[X][Y][Stored_Power] -= Selected_Recipe.Power;
			return true;
		}
	} else {
		if (Data.Settings_Grid[X][Y][1] <= 0) {
			if (Data.Data_Grid[X][Y][Stored_Power] > Selected_Recipe.Power * Selected_Recipe.Time) {
				if (Selected_Recipe.Shuffling_Barred) {
					for (int Counter = 0; Counter < Input_Locations.Length; Counter++) {
						if (Data.Data_Grid[Input_Locations.Data[Counter].X][Input_Locations.Data[Counter].Y][Stored_Fluids] <
							Selected_Recipe.Input_Counts[Counter]) {
							return false;
						}
					}
					for (int Counter = 0; Counter < Selected_Recipe.Inputs; Counter++) {
						if (Data.Items_Grid[Input_Locations.Data[Counter].X][Input_Locations.Data[Counter].Y] !=
							Selected_Recipe.Input_Items[Counter].Identifier) {
							return false;
						}
					}
					if (!Selected_Recipe.Voiding_Excess) {
						for (int Counter = 0; Counter < Output_Locations.Length; Counter++) {
							if (Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data[Counter].Y][
								Stored_Fluids] > Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data[
								Counter].Y][Fluid_Cap] - Selected_Recipe.Output_Counts[Counter]) {
								return false;
							}
						}
					}
					for (int Counter = 0; Counter < Input_Locations.Length; Counter++) {
						Data.Data_Grid[Input_Locations.Data[Counter].X][Input_Locations.Data[Counter].Y][Stored_Fluids] -=
							Selected_Recipe.Input_Counts[Counter];
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
		for (int Counter = 0; Counter < Selected_Recipe.Outputs; Counter++) {
			Update_Item(Nodes.Data[Counter].X, Nodes.Data[Counter].Y, Selected_Recipe.Output_Items[Counter].Identifier,
				LDE_ROOMTEMP);
		}
		for (int Counter = 0; Counter < Selected_Recipe.Outputs; Counter++) {
			Data.Data_Grid[Nodes.Data[Counter].X][Nodes.Data[Counter].Y][Stored_Fluids] = min(Data.Data_Grid[Nodes.Data[
				Counter].X][Nodes.Data[Counter].Y][Stored_Fluids] + Selected_Recipe.Output_Counts[Counter], Data.Data_Grid[
				Nodes.Data[Counter].X][Nodes.Data[Counter].Y][Fluid_Cap]);
		}
	}
	free_c(Nodes.Data);
}