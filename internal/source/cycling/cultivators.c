#include <grid.h>

void Cycle_Algae_Bed(Point Pos, const int Rotation) {
	Node Outputs = { };
	Return_Nodes(&Outputs, Pos, Visual_To_Rotation(Data.Visual_Grid[pt(Pos)]), Preconfigs.GB_Outputs);
	if (Process_O_Recipe(Preset_O_Recipes.GB_Algae, Pos, Outputs)) {
		Data.Animation_Grid[pt(Pos)][0] = 0;
		Data.Animation_Grid[pt(Pos)][1] = 1;
	}
	ktn_free(Outputs.Data);
}