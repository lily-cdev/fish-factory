#include <prepping.h>

Machine_Ptr Get_Machine(const char* Index) {
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		if (ktn_stricmp(Metadata.Machines[C1].Index, Index)) {
			return &Metadata.Machines[C1];
		}
	}
	return NULL;
}

Machine_Ptr Visual_To_Machine(const int Identifier) {
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		if (Metadata.Machines[C1].Visual_Type == I_Single && Metadata.Machines[C1].Visual_ID1 == Identifier) {
			return &Metadata.Machines[C1];
		} else if (Metadata.Machines[C1].Visual_Type == I_Rot) {
			for (int C2 = 0; C2 < 4; C2++) {
				if (Metadata.Machines[C1].Visual_ID4[C2] == Identifier) {
					return &Metadata.Machines[C1];
				}
			}
		}
	}
	if (Identifier > 0 && Identifier < 17) {
		return Get_Machine("heavy_pipe");
	} else if (Identifier == 21) {
		return Get_Machine("sub_dock");
	} else if (Identifier > 23 && Identifier < 41) {
		return Get_Machine("spawning_pool");
	} else if (Identifier == 45) {
		return Get_Machine("spawning_controller");
	} else if (Identifier == 46) {
		return Get_Machine("spawning_output");
	} else if (Identifier == 47) {
		return Get_Machine("spawning_input");
	} else if (Identifier > 70 && Identifier < 87) {
		return Get_Machine("large_pipe");
	}
	return NULL;
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

void ID_To_Size(Machine_Ptr Machine, const int Rotation, int* W, int* H) {
	if (!Machine) {
		*W = 0;
		*H = 0;
		return;
	}
	*W = (ktn_evn(Rotation)) ? (*Machine).Size.X : (*Machine).Size.Y;
	*H = (ktn_evn(Rotation)) ? (*Machine).Size.Y : (*Machine).Size.X;
}