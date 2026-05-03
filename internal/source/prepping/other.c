#include <prepping.h>

int Get_Depth(float Number) {
	for (int C1 = 0; C1 < ktn_suffixes - 1; C1++) {
		if (Number > 1000) {
			Number = Number / 1000;
		} else {
			return C1;
		}
	}
	return ktn_invalid;
}

void Abbreviate_Number(float Number, char* Buffer, int Size) {
	int Marker = 0;
	for (int C1 = 0; C1 < ktn_suffixes - 1; C1++) {
		if (Number >= 1000) {
			Marker++;
			Number = Number / 1000;
		} else {
			break;
		}
	}
	int Length = snprintf(Buffer, Size, "%.2f", Number);
	if (Core.Suffixes[Marker] != 'J' && Length < Size) {
		Buffer[Length] = Core.Suffixes[Marker];
		Buffer[Length + 1] = '\0';
	}
}

void Truncate(float Number, int Depth, char* Buffer, int Size) {
	if (Depth == ktn_invalid) {
		for (int C1 = 0; C1 < ktn_suffixes - 1; C1++) {
			if (Number > 1000) {
				Number /= 1000;
			} else {
				break;
			}
		}
	} else {
		Number /= powf(1000.0f, (float)Depth);
	}
	snprintf(Buffer, Size, "%.2f", Number);
}