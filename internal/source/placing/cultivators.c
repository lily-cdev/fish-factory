#include <grid.h>

bool Place_Spawning_Pool(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 24;
	Data.Behavior_Grid[pt(Pos)] = 0;
	return true;
}

bool Place_Spawning_Controller(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 45;
	Data.Settings_Grid[pt(Pos)][4] = 0;
	Data.Settings_Grid[pt(Pos)][5] = 0;
	Data.Settings_Grid[pt(Pos)][6] = 0;
	Data.Settings_Grid[pt(Pos)][7] = 0;
	Data.Behavior_Grid[pt(Pos)] = 0;
	return true;
}

bool Place_Spawning_Output(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 46;
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = 50;
	Data.Plumbing_Grid[pt(Pos)] = Down;
	Data.Behavior_Grid[pt(Pos)] = 0;
	Data.Settings_Grid[pt(Pos)][0] = F_Out;
	return true;
}

bool Place_Spawning_Input(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 47;
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = 12;
	Data.Plumbing_Grid[pt(Pos)] = Down;
	Data.Behavior_Grid[pt(Pos)] = 0;
	Data.Settings_Grid[pt(Pos)][0] = F_In;
	return true;
}