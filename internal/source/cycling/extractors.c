#include <grid.h>

void Cycle_Ram_Pump(const int X, const int Y, const int Rotation) {
	Node Outputs = { };
	Return_Nodes(&Outputs, X, Y, Rotation, Preconfigs.RP_Outputs);
	if (Process_O_Recipe(Preset_O_Recipes.RP_Saltwater, X, Y, Outputs)) {
		Data.Animation_Grid[X][Y][0] = 0;
		Play_Sound(Ram1, false);
	} else if (Data.Animation_Grid[X][Y][0] == 0) {
		Data.Animation_Grid[X][Y][0] = LDE_INVALID;
	}
	free_c(Outputs.Data);
}