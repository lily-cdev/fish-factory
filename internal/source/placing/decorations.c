#include <grid.h>

bool Place_Ammunition_Shelf(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = Interface.Rotation + 52;
	return true;
}