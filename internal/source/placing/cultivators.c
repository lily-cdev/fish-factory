#include <grid.h>

bool Place_Spawning_Pool(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 24;
	Data.Behavior_Grid[pt(Pos)] = 0;
	return true;
}

bool Place_Spawning_Controller(Point Pos) {
	if (Pool_Ct >= 16) {
		return false;
	}
	Pool_Ct++;
	Data.Visual_Grid[pt(Pos)] = 45;
	Data.Settings_Grid[pt(Pos)][4] = 0;
	for (int C1 = 0; C1 < 16; C1++) {
		if (!Fishlinks[C1].Allocated) {
			Data.Settings_Grid[pt(Pos)][5] = C1;
			Fishlinks[C1] = (struct Fishlink){
				.Allocated = true,
				.Type = Get_Fish(0)
			};
			break;
		}
	}
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