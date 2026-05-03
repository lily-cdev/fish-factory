#include <grid.h>

void Cycle_Ram_Pump(Point Pos, const int Rotation) {
	Node Outputs = { };
	Return_Nodes(&Outputs, Pos, Rotation, Preconfigs.RP_Outputs);
	if (Process_O_Recipe(Preset_O_Recipes.RP_Saltwater, Pos, Outputs)) {
		Data.Animation_Grid[pt(Pos)][0] = 0;
		Play_Sound(Ram1, false);
	} else if (Data.Animation_Grid[pt(Pos)][0] == 0) {
		Data.Animation_Grid[pt(Pos)][0] = ktn_invalid;
	}
	ktn_free(Outputs.Data);
}