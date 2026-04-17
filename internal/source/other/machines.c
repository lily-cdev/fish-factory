#include <prepping.h>

int Visual_To_ID(const int Identifier) {
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		if (Metadata.Machines[C1].Single_ID && Metadata.Machines[C1].Visual_ID1 == Identifier) {
			return C1;
		}
	}
	if (Identifier > 0 && Identifier < 17) {
		return Reinforced_Pipe;
	} else if (Identifier > 17 && Identifier < 24 && Identifier != 20 && Identifier != 22) {
		return Identifier - 16;
	} else if (Identifier > 23 && Identifier < 41) {
		return Spawning_Pool;
	} else if (Identifier > 40 && Identifier < 51) {
		return Identifier - 32;
	} else if (Identifier > 51 && Identifier < 56) {
		return Ammunition_Shelf;
	} else if (Identifier > 55 && Identifier < 59) {
		return Command_Platform;
	} else if (Identifier > 59 && Identifier < 63) {
		return Signal_Tower;
	} else if (Identifier > 63 && Identifier < 67) {
		return Battery;
	} else if (Identifier > 66 && Identifier < 71) {
		return Geo_Well;
	} else if (Identifier > 70 && Identifier < 87) {
		return Large_Pipe;
	} else if (Identifier > 86 && Identifier < 91) {
		return Heat_Exchanger;
	} else if (Identifier > 95 && Identifier < 99) {
		return Electrolytic_Cell;
	} else if (Identifier > 98 && Identifier < 102) {
		return Fluid_Mixer;
	} else if (Identifier > 101 && Identifier < 105) {
		return Bio_Generator;
	} else if (Identifier > 104 && Identifier < 109) {
		return R_Intersection;
	} else if (Identifier > 108 && Identifier < 113) {
		return L_Intersection;
	} else if (Identifier > 113 && Identifier < 117) {
		return Incinerator;
	} else if (Identifier > 116 && Identifier < 120) {
		return Distillery;
	} else if (Identifier > 119 && Identifier < 124) {
		return Turbine_Input;
	} else if (Identifier > 123 && Identifier < 128) {
		return Turbine_Impulse;
	} else if (Identifier > 127 && Identifier < 132) {
		return Turbine_Output;
	} else if (Identifier > 131 && Identifier < 135) {
		return Algae_Bed;
	} else if (Identifier > 134 && Identifier < 138) {
		return RTG;
	}
	return LDE_INVALID;
}

int Visual_To_Rotation(const int Identifier) {
	if (Identifier > 52 && Identifier < 56) {
		return Identifier - 52;
	} else if (Identifier > 55 && Identifier < 59) {
		return Identifier - 55;
	} else if (Identifier > 59 && Identifier < 63) {
		return Identifier - 59;
	} else if (Identifier > 63 && Identifier < 67) {
		return Identifier - 63;
	} else if (Identifier > 67 && Identifier < 71) {
		return Identifier - 67;
	} else if (Identifier > 87 && Identifier < 91) {
		return Identifier - 87;
	} else if (Identifier > 95 && Identifier < 99) {
		return Identifier - 95;
	} else if (Identifier > 98 && Identifier < 102) {
		return Identifier - 98;
	} else if (Identifier > 101 && Identifier < 105) {
		return Identifier - 101;
	} else if (Identifier > 105 && Identifier < 109) {
		return Identifier - 105;
	} else if (Identifier > 109 && Identifier < 113) {
		return Identifier - 109;
	} else if (Identifier > 113 && Identifier < 117) {
		return Identifier - 113;
	} else if (Identifier > 116 && Identifier < 120) {
		return Identifier - 116;
	} else if (Identifier > 120 && Identifier < 124) {
		return Identifier - 120;
	} else if (Identifier > 124 && Identifier < 128) {
		return Identifier - 124;
	} else if (Identifier > 128 && Identifier < 132) {
		return Identifier - 128;
	} else if (Identifier > 131 && Identifier < 135) {
		return Identifier - 131;
	} else if (Identifier > 134 && Identifier < 138) {
		return Identifier - 134;
	}
	return 0;
}

void ID_To_Size(const int ID, const int Rotation, int* W, int* H) {
	int X = 1;
	int Y = 1;
	switch (ID) {
	case Ammunition_Shelf:
		if (evn(Rotation)) {
			X = 2;
		} else {
			Y = 2;
		}
		break;
	case Distillery:
	case Battery:
	case Turbine_Output:
		X = 2;
		Y = 2;
		break;
	case Filtration_Plant:
	case Algae_Bed:
		if (evn(Rotation)) {
			X = 2;
			Y = 3;
		} else {
			X = 3;
			Y = 2;
		}
		break;
	case Electrolytic_Cell:
		if (evn(Rotation)) {
			X = 3;
			Y = 2;
		} else {
			X = 2;
			Y = 3;
		}
		break;
	case Bio_Generator:
	case Fluid_Mixer:
	case Signal_Tower:
	case R_Intersection:
	case L_Intersection:
		X = 3;
		Y = 3;
		break;
	case Submarine_Dock:
		X = 6;
		Y = 4;
		break;
	case Command_Platform:
		if (evn(Rotation)) {
			X = 8;
			Y = 6;
		} else {
			X = 6;
			Y = 8;
		}
		break;
	case Geo_Well:
	case Turbine_Input:
	case Turbine_Impulse:
		if (evn(Rotation)) {
			X = 2;
			Y = 3;
		} else {
			X = 3;
			Y = 2;
		}
		break;
	case Heat_Exchanger:
		if (evn(Rotation)) {
			X = 4;
			Y = 3;
		} else {
			X = 3;
			Y = 4;
		}
		break;
	default:
		break;
	}
	*W = X;
	*H = Y;
}