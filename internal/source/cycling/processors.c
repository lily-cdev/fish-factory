#include <grid.h>

void Cycle_Distillery(const int X, const int Y, const int Rotation) {
	Node Inputs = { };
	Node Outputs = { };	
	Return_Nodes(&Inputs, X, Y, Visual_To_Rotation(Data.Visual_Grid[X][Y]), Preconfigs.D_Inputs);
	Return_Nodes(&Outputs, X, Y, Visual_To_Rotation(Data.Visual_Grid[X][Y]), Preconfigs.D_Outputs);
	Process_Recipe(Preset_IO_Recipes.D_Water, X, Y, Inputs, Outputs);
	free_c(Inputs.Data);
	free_c(Outputs.Data);
}

void Cycle_Electrolytic_Cell(const int X, const int Y, const int Rotation) {
	Node Inputs = { };
	Node Outputs = { };
	Recipe Selected_Recipes[3] = {
		Preset_IO_Recipes.EP_Saltwater,
		Preset_IO_Recipes.EP_Water,
		Preset_IO_Recipes.EP_Salt
	};
	Return_Nodes(&Inputs, X, Y, Visual_To_Rotation(Data.Visual_Grid[X][Y]), Preconfigs.EP_Inputs);
	Return_Nodes(&Outputs, X, Y, Visual_To_Rotation(Data.Visual_Grid[X][Y]), Preconfigs.EP_Outputs);
	for (int C1 = 0; C1 < 3; C1++) {
		Process_Recipe(Selected_Recipes[C1], X, Y, Inputs, Outputs);
	}
	free_c(Inputs.Data);
	free_c(Outputs.Data);
}

void Cycle_Fluid_Mixer(const int X, const int Y, const int Rotation) {
	Recipe Selected_Recipes[4] = {
		Preset_IO_Recipes.FM_Drillmud_1, Preset_IO_Recipes.FM_Drillmud_2,
		Preset_IO_Recipes.FM_Hydrogen_Chloride, Preset_IO_Recipes.FM_Hydrochloric_Acid
	};
	for (int C1 = 0; C1 < 4; C1++) {
		Data.Animation_Grid[X][Y][0] = 0;
		Node Subinputs = { };
		Node Suboutputs = { };
		Return_Nodes(&Subinputs, X, Y, Visual_To_Rotation(Data.Visual_Grid[X][Y]), Preconfigs.FM_Inputs);
		Return_Nodes(&Suboutputs, X, Y, Visual_To_Rotation(Data.Visual_Grid[X][Y]), Preconfigs.FM_Outputs);
		if (Process_Recipe(Selected_Recipes[C1], X, Y, Subinputs, Suboutputs)) {
			Data.Animation_Grid[X][Y][0] = 1;
			break;
		}
		free_c(Subinputs.Data);
		free_c(Suboutputs.Data);
	}
}