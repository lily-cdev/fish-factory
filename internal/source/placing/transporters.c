#include <grid.h>

bool Place_Reinforced_Pipe(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 1;
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = ktn_reinforced_cap;
	Data.Settings_Grid[pt(Pos)][0] = F_Either;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	return true;
}

bool Place_Submarine_Dock(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 21;
	Data.Settings_Grid[pt(Pos)][3] = 0;
	Data.Settings_Grid[pt(Pos)][4] = 0;
	Push_Docks(Pos);
	Recache_TT_Commands();
	return true;
}

bool Place_Large_Pipe(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 71;
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = ktn_large_cap;
	Data.Settings_Grid[pt(Pos)][0] = F_Either;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	return true;
}