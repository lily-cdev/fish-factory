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
	Data.Visual_Grid[pt(Pos)] = Interface.Rotation + 52;
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