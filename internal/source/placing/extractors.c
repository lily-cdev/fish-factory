#include <grid.h>

bool Place_Ram_Pump(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 17;
	Data.Wiring_Grid[pt(Pos)] = F_In;
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = 3;
	Data.Data_Grid[pt(Pos)][Power_Cap] = 10;
	Data.Data_Grid[pt(Pos)][5] = 20;
	Data.Data_Grid[pt(Pos)][6] = 20;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	Data.Settings_Grid[pt(Pos)][0] = F_Out;
	return true;
}