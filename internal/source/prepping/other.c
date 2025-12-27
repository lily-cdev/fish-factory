#include <prepping.h>

int Get_Depth(double Number) {
	for (int Counter = 0; Counter < LDE_SUFFIXES - 1; Counter++) {
		if (Number > 1000) {
			Number = Number / 1000;
		} else {
			return Counter;
		}
	}
	return LDE_INVALID;
}