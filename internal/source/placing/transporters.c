#include <grid.h>

bool Place_Reinforced_Pipe(Point Pos) {
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = ktn_reinforced_cap;
	Data.Settings_Grid[pt(Pos)][0] = F_Either;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	Data.Types_Grid[pt(Pos)] = T_Liquid;
	return true;
}

bool Place_Submarine_Dock(Point Pos) {
	if (Dock_Ct >= ktn_docklinks) {
		return false;
	}
	Dock_Ct++;
	for (int C1 = 0; C1 < ktn_docklinks; C1++) {
		if (!Docklinks[C1].Allocated) {
			Data.Settings_Grid[pt(Pos)][5] = C1;
			Docklinks[C1].Allocated = true;
			strcpy(Docklinks[C1].Items[0], ktn_strnull);
			strcpy(Docklinks[C1].Items[1], ktn_strnull);
			break;
		}
	}
	Data.Settings_Grid[pt(Pos)][3] = 0;
	Data.Settings_Grid[pt(Pos)][4] = 0;
	Push_Docks(Pos);
	return true;
}

bool Place_Large_Pipe(Point Pos) {
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = ktn_large_cap;
	Data.Settings_Grid[pt(Pos)][0] = F_Either;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	Data.Types_Grid[pt(Pos)] = T_Liquid;
	return true;
}

bool Place_Belt(Point Pos) {
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = 60;
	Data.Settings_Grid[pt(Pos)][0] = F_Either;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	Data.Types_Grid[pt(Pos)] = T_Solid;
	return true;
}