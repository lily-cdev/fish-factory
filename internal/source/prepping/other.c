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

void Abbreviate_Number(long double Number, char* Buffer, int Size) {
	int Marker = 0;
	for (int Counter = 0; Counter < LDE_SUFFIXES - 1; Counter++) {
		if (Number >= 1000) {
			Marker++;
			Number = Number / 1000;
		} else {
			break;
		}
	}
	int Length = snprintf(Buffer, Size, "%.2Lf", Number);
	if (Core.Suffixes[Marker] != 'J') {
		Buffer[Length] = Core.Suffixes[Marker];
		Buffer[Length + 1] = '\0';
	}
}

void Truncate(double Number, int Depth, char* Buffer, int Size) {
	if (Depth == LDE_INVALID) {
		for (int Counter = 0; Counter < LDE_SUFFIXES - 1; Counter++) {
			if (Number > 1000) {
				Number = Number / 1000;
			} else {
				break;
			}
		}
	} else {
		Number = Number / pow(1000, Depth);
	}
	snprintf(Buffer, Size, "%.2f", Number);
}