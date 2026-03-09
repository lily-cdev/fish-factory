#include <grid.h>

void Cycle_Algae_Bed(const int X, const int Y, const int Rotation) {
	Node Outputs = { };
	Return_Nodes(&Outputs, X, Y, Visual_To_Rotation(Data.Visual_Grid[X][Y]), Preconfigs.GB_Outputs);
	if (Process_O_Recipe(Preset_O_Recipes.GB_Algae, X, Y, Outputs)) {
		Data.Animation_Grid[X][Y][0] = 0;
		Data.Animation_Grid[X][Y][1] = 1;
	}
	free_c(Outputs.Data);
}