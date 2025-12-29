#include <Legacy_Items.hpp>

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
					Selected_Recipe.Output_Items[Counter].Identifier);
			}
			for (int Counter = 0; Counter < Output_Locations.Length; Counter++) {
				Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data[Counter].Y][Stored_Fluids] =
					std::min(Selected_Recipe.Output_Counts[Counter], Data.Data_Grid[Output_Locations.Data[Counter].X][
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
				for (int Counter = 0; Counter < Selected_Recipe.Input_Items.size(); Counter++) {
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
						Selected_Recipe.Output_Items[Counter].Identifier);
				}
				for (int Counter = 0; Counter < Output_Locations.Length; Counter++) {
					Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data[Counter].Y][Stored_Fluids] =
						std::min(Selected_Recipe.Output_Counts[Counter], Data.Data_Grid[Output_Locations.Data[Counter].X][
						Output_Locations.Data[Counter].Y][Fluid_Cap]);
				}
			} else {
				std::vector<int> Inputs = { };
				std::vector<int> Positions = { };
				for (int Counter = 0; Counter < Input_Locations.Length; Counter++) {
					Inputs.push_back(Data.Items_Grid[Input_Locations.Data[Counter].X][Input_Locations.Data[Counter].Y]);
				}
				for (int Counter1 = 0; Counter1 < Selected_Recipe.Input_Items.size(); Counter1++) {
					bool Unsatiated = true;
					for (int Counter2 = 0; Counter2 < Inputs.size(); Counter2++) {
						if (Selected_Recipe.Input_Items[Counter1].Identifier == Inputs[Counter2]) {
							Unsatiated = false;
							Inputs[Counter2] = LDE_INVALID;
							Positions.push_back(Counter2);
						}
					}
					if (Unsatiated) {
						return false;
					}
				}
				for (int Counter = 0; Counter < Inputs.size(); Counter++) {
					if (Inputs[Counter] != LDE_INVALID) {
						return false;
					}
				}
				for (int Counter = 0; Counter < Positions.size(); Counter++) {
					if (Data.Data_Grid[Input_Locations.Data[Positions[Counter]].X][
						Input_Locations.Data[Positions[Counter]].Y][Stored_Fluids] <
						Selected_Recipe.Input_Counts[Counter]) {
						return false;
					}
				}
				if (!Selected_Recipe.Voiding_Excess) {
					for (int Counter = 0; Counter < Selected_Recipe.Output_Counts.size(); Counter++) {
						if (Data.Data_Grid[Output_Locations.Data[Counter].X][
							Output_Locations.Data[Counter].Y][Stored_Fluids] >
							Data.Data_Grid[Output_Locations.Data[Counter].X][
							Output_Locations.Data[Counter].Y][Fluid_Cap] -
							Selected_Recipe.Output_Counts[Counter]) {
							return false;
						}
					}
				}
				for (int Counter = 0; Counter < Positions.size(); Counter++) {
					Data.Data_Grid[Input_Locations.Data[Positions[Counter]].X][
						Input_Locations.Data[Positions[Counter]].Y][Stored_Fluids] -=
						Selected_Recipe.Input_Counts[Counter];
				}
				for (int Counter = 0; Counter < Selected_Recipe.Output_Counts.size(); Counter++) {
					Update_Item(Output_Locations.Data[Counter].X, Output_Locations.Data[Counter].Y,
						Selected_Recipe.Output_Items[Counter].Identifier);
				}
				for (int Counter = 0; Counter < Selected_Recipe.Output_Counts.size(); Counter++) {
					Data.Data_Grid[Output_Locations.Data[Counter].X][Output_Locations.Data[
						Counter].Y][Stored_Fluids] = std::min(Data.Data_Grid[
						Output_Locations.Data[Counter].X][Output_Locations.Data[Counter].Y][Stored_Fluids] +
						Selected_Recipe.Output_Counts[Counter], Data.Data_Grid[
						Output_Locations.Data[Counter].X][Output_Locations.Data[Counter].Y][Fluid_Cap]);
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
						if (Data.Data_Grid[Input_Locations.Data[Counter].X][Input_Locations
							.Data[Counter].Y][Stored_Fluids] < Selected_Recipe.Input_Counts[Counter]) {
							return false;
						}
					}
					for (int Counter = 0; Counter < Selected_Recipe.Input_Items.size(); Counter++) {
						if (Data.Items_Grid[Input_Locations.Data[Counter].X][Input_Locations.Data[
							Counter].Y] != Selected_Recipe.Input_Items[Counter].Identifier) {
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
	Return_Nodes(Nodes, X, Y, Visual_To_Rotation(Data.Visual_Grid[X][Y]), Preconfiguration);
	Data.Data_Grid[X][Y][Stored_Power] -= Selected_Recipe.Power;
	if (Data.Settings_Grid[X][Y][1] <= 0) {
		Data.Settings_Grid[X][Y][1] = 0;
		for (int Counter = 0; Counter < Selected_Recipe.Output_Counts.size(); Counter++) {
			Update_Item(Nodes.Data[Counter].X, Nodes.Data[Counter].Y,
				Selected_Recipe.Output_Items[Counter].Identifier);
		}
		for (int Counter = 0; Counter < Selected_Recipe.Output_Counts.size(); Counter++) {
			Data.Data_Grid[Nodes.Data[Counter].X][Nodes.Data[Counter].Y][Stored_Fluids] =
				std::min(Data.Data_Grid[Nodes.Data[Counter].X][Nodes.Data[Counter].Y][Stored_Fluids] +
				Selected_Recipe.Output_Counts[Counter], Data.Data_Grid[Nodes.Data[Counter].X][
				Nodes.Data[Counter].Y][Fluid_Cap]);
		}
	}
	Free_Node(Nodes);
}

std::vector<std::vector<Recipe*>> I_Recipes;
std::vector<std::vector<Recipe*>> O_Recipes;
std::vector<std::vector<Recipe*>> IO_Recipes;
std::vector<std::vector<Recipe*>> All_Recipes[3];

void Preload_Recipes() {
	I_Recipes.resize(LDE_MACHINES);
	O_Recipes.resize(LDE_MACHINES);
	IO_Recipes.resize(LDE_MACHINES);
	O_Recipes[Ram_Pump] = {
		&Preset_O_Recipes.RP_Saltwater
	};
	IO_Recipes[Filtration_Plant] = {
		&Preset_IO_Recipes.FP_Saltwater,
		&Preset_IO_Recipes.FP_Biopaste
	};
	IO_Recipes[Fluid_Mixer] = {
		&Preset_IO_Recipes.FM_Drillmud_1,
		&Preset_IO_Recipes.FM_Drillmud_2,
		&Preset_IO_Recipes.FM_Hydrogen_Chloride,
		&Preset_IO_Recipes.FM_Hydrochloric_Acid
	};
	IO_Recipes[Distillery] = {
		&Preset_IO_Recipes.D_Water
	};
	IO_Recipes[Electrolytic_Cell] = {
		&Preset_IO_Recipes.EP_Water,
		&Preset_IO_Recipes.EP_Saltwater,
		&Preset_IO_Recipes.EP_Salt
	};
	All_Recipes[0] = I_Recipes;
	All_Recipes[1] = O_Recipes;
	All_Recipes[2] = IO_Recipes;
}