#include <grid.h>

bool Place_Ram_Pump(Point Pos) {
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = 3;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	Data.Settings_Grid[pt(Pos)][0] = F_Out;
	return true;
}