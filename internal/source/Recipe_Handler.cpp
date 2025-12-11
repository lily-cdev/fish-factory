#include <Core.h>
#include <Preloader.h>
#include <Items.h>

void Process_I_Recipe() {
//do
}

void Extend_I_Recipe() {
	//do
}

bool Process_O_Recipe(Recipe Selected_Recipe, int X, int Y, std::vector<Point> Output_Locations) {
	if (Selected_Recipe.Time == 1) {
		if (Data_Access.Data_Grid[X][Y][Stored_Power] >= Selected_Recipe.Power) {
			if (Selected_Recipe.Voiding_Excess) {
				for (int Counter = 0; Counter < Output_Locations.size(); Counter++) {
					if (Data_Access.Data_Grid[Output_Locations[Counter].X][Output_Locations
						[Counter].Y][Stored_Fluids] + Selected_Recipe.Output_Counts[Counter] <
						Data_Access.Data_Grid[Output_Locations[Counter].X][Output_Locations
						[Counter].Y][Fluid_Cap]) {
						return false;
					}
				}
			}
			Data_Access.Data_Grid[X][Y][Stored_Power] -= Selected_Recipe.Power;
			for (int Counter = 0; Counter < Output_Locations.size(); Counter++) {
				Update_Item(Output_Locations[Counter].X, Output_Locations[Counter].Y,
					Selected_Recipe.Output_Items[Counter].Identifier);
			}
			for (int Counter = 0; Counter < Output_Locations.size(); Counter++) {
				Data_Access.Data_Grid[Output_Locations[Counter].X][Output_Locations[Counter].Y][Stored_Fluids] =
					std::min(Selected_Recipe.Output_Counts[Counter], Data_Access.Data_Grid[Output_Locations[Counter].X]
					[Output_Locations[Counter].Y][Fluid_Cap]);
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

bool Process_Recipe(Recipe Selected_Recipe, int X, int Y, std::vector<Point> Input_Locations,
	std::vector<Point> Output_Locations) {
	if (Selected_Recipe.Time == 1) {
		if (Data_Access.Data_Grid[X][Y][Stored_Power] >= Selected_Recipe.Power) {
			if (Selected_Recipe.Shuffling_Barred) {
				for (int Counter = 0; Counter < Input_Locations.size(); Counter++) {
					if (Data_Access.Data_Grid[Input_Locations[Counter].X][Input_Locations
						[Counter].Y][Stored_Fluids] < Selected_Recipe.Input_Counts[Counter]) {
						return false;
					}
				}
				for (int Counter = 0; Counter < Selected_Recipe.Input_Items.size(); Counter++) {
					if (Data_Access.Items_Grid[Input_Locations[Counter].X][Input_Locations
						[Counter].Y] !=	Selected_Recipe.Input_Items[Counter].Identifier) {
						return false;
					}
				}
				if (!Selected_Recipe.Voiding_Excess) {
					for (int Counter = 0; Counter < Output_Locations.size(); Counter++) {
						if (Data_Access.Data_Grid[Output_Locations[Counter].X]
							[Output_Locations[Counter].Y][Stored_Fluids] >
							Data_Access.Data_Grid[Output_Locations[Counter].X]
							[Output_Locations[Counter].Y][Fluid_Cap] -
							Selected_Recipe.Output_Counts[Counter]) {
							return false;
						}
					}
				}
				for (int Counter = 0; Counter < Input_Locations.size(); Counter++) {
					Data_Access.Data_Grid[Input_Locations[Counter].X][Input_Locations
						[Counter].Y][Stored_Fluids] -= Selected_Recipe.Input_Counts[Counter];
				}
				for (int Counter = 0; Counter < Output_Locations.size(); Counter++) {
					Update_Item(Output_Locations[Counter].X, Output_Locations[Counter].Y,
						Selected_Recipe.Output_Items[Counter].Identifier);
				}
				for (int Counter = 0; Counter < Output_Locations.size(); Counter++) {
					Data_Access.Data_Grid[Output_Locations[Counter].X][Output_Locations[Counter].Y][Stored_Fluids] =
						std::min(Selected_Recipe.Output_Counts[Counter], Data_Access.Data_Grid[Output_Locations[Counter].X]
						[Output_Locations[Counter].Y][Fluid_Cap]);
				}
			} else {
				std::vector<int> Inputs = { };
				std::vector<int> Positions = { };
				for (int Counter = 0; Counter < Input_Locations.size(); Counter++) {
					Inputs.push_back(Data_Access.Items_Grid[Input_Locations[Counter].X][Input_Locations[Counter].Y]);
				}
				for (int First_Counter = 0; First_Counter < Selected_Recipe.Input_Items.size(); First_Counter++) {
					bool Unsatiated = true;
					for (int Second_Counter = 0; Second_Counter < Inputs.size(); Second_Counter++) {
						if (Selected_Recipe.Input_Items[First_Counter].Identifier == Inputs[Second_Counter]) {
							Unsatiated = false;
							Inputs[Second_Counter] = LDE_INVALID;
							Positions.push_back(Second_Counter);
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
					if (Data_Access.Data_Grid[Input_Locations[Positions[Counter]].X]
						[Input_Locations[Positions[Counter]].Y][Stored_Fluids] <
						Selected_Recipe.Input_Counts[Counter]) {
						return false;
					}
				}
				if (!Selected_Recipe.Voiding_Excess) {
					for (int Counter = 0; Counter < Selected_Recipe.Output_Counts.size(); Counter++) {
						if (Data_Access.Data_Grid[Output_Locations[Counter].X][Output_Locations[Counter].Y][Stored_Fluids] >
							Data_Access.Data_Grid[Output_Locations[Counter].X][Output_Locations[Counter].Y][Fluid_Cap] -
							Selected_Recipe.Output_Counts[Counter]) {
							return false;
						}
					}
				}
				for (int Counter = 0; Counter < Positions.size(); Counter++) {
					Data_Access.Data_Grid[Input_Locations[Positions[Counter]].X]
						[Input_Locations[Positions[Counter]].Y][Stored_Fluids] -= Selected_Recipe.Input_Counts[Counter];
				}
				for (int Counter = 0; Counter < Selected_Recipe.Output_Counts.size(); Counter++) {
					Update_Item(Output_Locations[Counter].X, Output_Locations[Counter].Y,
						Selected_Recipe.Output_Items[Counter].Identifier);
				}
				for (int Counter = 0; Counter < Selected_Recipe.Output_Counts.size(); Counter++) {
					Data_Access.Data_Grid[Output_Locations[Counter].X][Output_Locations
						[Counter].Y][Stored_Fluids] = std::min(Data_Access.Data_Grid
						[Output_Locations[Counter].X][Output_Locations[Counter].Y][Stored_Fluids] +
						Selected_Recipe.Output_Counts[Counter], Data_Access.Data_Grid
						[Output_Locations[Counter].X][Output_Locations[Counter].Y][Fluid_Cap]);
				}
			}
			Data_Access.Data_Grid[X][Y][Stored_Power] -= Selected_Recipe.Power;
			return true;
		}
	} else {
		if (Data_Access.Settings_Grid[X][Y][1] <= 0) {
			if (Data_Access.Data_Grid[X][Y][Stored_Power] > Selected_Recipe.Power * Selected_Recipe.Time) {
				if (Selected_Recipe.Shuffling_Barred) {
					for (int Counter = 0; Counter < Input_Locations.size(); Counter++) {
						if (Data_Access.Data_Grid[Input_Locations[Counter].X]
							[Input_Locations[Counter].Y][Stored_Fluids] < Selected_Recipe.Input_Counts[Counter]) {
							return false;
						}
					}
					for (int Counter = 0; Counter < Selected_Recipe.Input_Items.size(); Counter++) {
						if (Data_Access.Items_Grid[Input_Locations[Counter].X][Input_Locations[Counter].Y] !=
							Selected_Recipe.Input_Items[Counter].Identifier) {
							return false;
						}
					}
					if (!Selected_Recipe.Voiding_Excess) {
						for (int Counter = 0; Counter < Output_Locations.size(); Counter++) {
							if (Data_Access.Data_Grid[Output_Locations[Counter].X]
								[Output_Locations[Counter].Y][Stored_Fluids] >
								Data_Access.Data_Grid[Output_Locations[Counter].X]
								[Output_Locations[Counter].Y][Fluid_Cap] -
								Selected_Recipe.Output_Counts[Counter]) {
								return false;
							}
						}
					}
					for (int Counter = 0; Counter < Input_Locations.size(); Counter++) {
						Data_Access.Data_Grid[Input_Locations[Counter].X][Input_Locations[Counter].Y]
							[Stored_Fluids] -= Selected_Recipe.Input_Counts[Counter];
					}
					Data_Access.Settings_Grid[X][Y][1] = Selected_Recipe.Time;
					Data_Access.Settings_Grid[X][Y][2] = Selected_Recipe.ID;
				}
				return true;
			}
		}
	}
	return false;
}

void Extend_Recipe(Recipe Selected_Recipe, int X, int Y,
	const std::vector<Point> (&Preconfiguration)[4]) {
	std::vector<Point> Nodes = Return_Nodes(X, Y, Visual_To_Rotation(
		Data_Access.Visual_Grid[X][Y]), Preconfiguration);
	Data_Access.Data_Grid[X][Y][Stored_Power] -= Selected_Recipe.Power;
	if (Data_Access.Settings_Grid[X][Y][1] <= 0) {
		Data_Access.Settings_Grid[X][Y][1] = 0;
		for (int Counter = 0; Counter < Selected_Recipe.Output_Counts.size(); Counter++) {
			Update_Item(Nodes[Counter].X, Nodes[Counter].Y,
				Selected_Recipe.Output_Items[Counter].Identifier);
		}
		for (int Counter = 0; Counter < Selected_Recipe.Output_Counts.size(); Counter++) {
			Data_Access.Data_Grid[Nodes[Counter].X][Nodes[Counter].Y][Stored_Fluids] =
				std::min(Data_Access.Data_Grid[Nodes[Counter].X][Nodes[Counter].Y][Stored_Fluids] +
				Selected_Recipe.Output_Counts[Counter], Data_Access.Data_Grid[Nodes[Counter].X]
				[Nodes[Counter].Y][Fluid_Cap]);
		}
	}
}

std::vector<std::vector<Recipe*>> I_Recipes;
std::vector<std::vector<Recipe*>> O_Recipes;
std::vector<std::vector<Recipe*>> IO_Recipes;
std::vector<std::vector<Recipe*>> All_Recipes[3];

void Preload_Recipes() {
	I_Recipes.resize(Metadata_Access.Machine_Count);
	O_Recipes.resize(Metadata_Access.Machine_Count);
	IO_Recipes.resize(Metadata_Access.Machine_Count);
	O_Recipes[Ram_Pump] = {
		&Preset_O_Recipes_Access.RP_Saltwater
	};
	IO_Recipes[Filtration_Plant] = {
		&Preset_IO_Recipes_Access.FP_Saltwater,
		&Preset_IO_Recipes_Access.FP_Biopaste
	};
	IO_Recipes[Fluid_Mixer] = {
		&Preset_IO_Recipes_Access.FM_Drillmud_1,
		&Preset_IO_Recipes_Access.FM_Drillmud_2,
		&Preset_IO_Recipes_Access.FM_Hydrogen_Chloride,
		&Preset_IO_Recipes_Access.FM_Hydrochloric_Acid
	};
	IO_Recipes[Distillery] = {
		&Preset_IO_Recipes_Access.D_Water
	};
	IO_Recipes[Electrolytic_Cell] = {
		&Preset_IO_Recipes_Access.EP_Water,
		&Preset_IO_Recipes_Access.EP_Saltwater,
		&Preset_IO_Recipes_Access.EP_Salt
	};
	All_Recipes[0] = I_Recipes;
	All_Recipes[1] = O_Recipes;
	All_Recipes[2] = IO_Recipes;
}