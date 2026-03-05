#include <grid.h>

bool Place_Decoration(int X, int Y) {
    Data.Visual_Grid[X][Y] = 20;
    return true;
}

bool Place_Flowerpot(int X, int Y) {
    Data.Visual_Grid[X][Y] = 51;
    return true;
}

bool Place_Ammunition_Shelf(int X, int Y) {
    bool Placed = false;
	if (evn(Interface.Rotation)) {
		if (Check_Clearance(X, Y, 2, 1)) {
			Fill_Clearance(LDE_INVALID, X, Y, 2, 1);
			Placed = true;
		}
	} else {
		if (Check_Clearance(X, Y, 1, 2)) {
			Fill_Clearance(LDE_INVALID, X, Y, 1, 2);
			Placed = true;
		}
	}
	if (Placed) {
		Data.Visual_Grid[X][Y] = Interface.Rotation + 52;
	} else {
		return false;
	}
	return true;
}

bool Place_Petrified_Wood(int X, int Y) {
	Data.Visual_Grid[X][Y] = 91;
    return true;
}

bool Place_Basalt_Tile(int X, int Y) {
	Data.Visual_Grid[X][Y] = 92;
    return true;
}

bool Place_Silicone_Carpet(int X, int Y) {
	Data.Visual_Grid[X][Y] = 93;
    return true;
}

bool Place_Hazard_Strip(int X, int Y) {
	Data.Visual_Grid[X][Y] = 113;
	return true;
}