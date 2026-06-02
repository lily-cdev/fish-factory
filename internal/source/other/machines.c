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
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		if (Metadata.Machines[C1].Visual_Type == I_Rot) {
			for (int C2 = 1; C2 < 4; C2++) {
				if (Metadata.Machines[C1].Visual_ID4[C2] == Identifier) {
					return C2;
				}
			}
		}
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