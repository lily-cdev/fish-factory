#include <grid.h>

bool Place_Ram_Pump(int X, int Y) {
	Data.Visual_Grid[X][Y] = 17;
	Data.Connection_Grid[X][Y] = 0;
	Data.Wiring_Grid[X][Y] = 0;
	Data.Data_Grid[X][Y][Fluid_Cap] = 3;
	Data.Data_Grid[X][Y][Power_Cap] = 10;
	Data.Data_Grid[X][Y][5] = 20;
	Data.Data_Grid[X][Y][6] = 20;
	Data.Plumbing_Grid[X][Y] = Any;
	Data_L.Settings_Grid[X][Y][0] = F_Out;
	return true;
}