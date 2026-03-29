#include <grid.h>

bool Place_Decoration(Point Pos) {
    Data.Visual_Grid[pt(Pos)] = 20;
    return true;
}

bool Place_Flowerpot(Point Pos) {
    Data.Visual_Grid[pt(Pos)] = 51;
    return true;
}

bool Place_Ammunition_Shelf(Point Pos) {
    bool Placed = false;
	if (evn(Interface.Rotation)) {
		if (Check_Clearance(Pos, 2, 1)) {
			Fill_Clearance(LDE_INVALID, Pos, 2, 1);
			Placed = true;
		}
	} else {
		if (Check_Clearance(Pos, 1, 2)) {
			Fill_Clearance(LDE_INVALID, Pos, 1, 2);
			Placed = true;
		}
	}
	if (Placed) {
		Data.Visual_Grid[pt(Pos)] = Interface.Rotation + 52;
	} else {
		return false;
	}
	return true;
}

bool Place_Petrified_Wood(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 91;
    return true;
}

bool Place_Basalt_Tile(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 92;
    return true;
}

bool Place_Silicone_Carpet(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 93;
    return true;
}

bool Place_Hazard_Strip(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 113;
	return true;
}