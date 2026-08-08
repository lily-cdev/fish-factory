#include <prepping.h>

Machine_Ptr Get_Machine(const char* Index) {
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		if (ktn_stricmp(Metadata.Machines[C1].Index, Index)) {
			return &Metadata.Machines[C1];
		}
	}
	return NULL;
}

Machine_Ptr Visual_To_Machine(const char* Identifier) {
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		if (Metadata.Machines[C1].Visual_Type == I_Single && ktn_stricmp(Metadata.Machines[C1].Visual_ID1, Identifier)) {
			return &Metadata.Machines[C1];
		} else if (Metadata.Machines[C1].Visual_Type == I_Rot) {
			for (int C2 = 0; C2 < 4; C2++) {
				if (ktn_stricmp(Metadata.Machines[C1].Visual_ID4[C2], Identifier)) {
					return &Metadata.Machines[C1];
				}
			}
		} else if (Metadata.Machines[C1].Visual_Type == I_Mod) {
			for (int C2 = 0; C2 < 17; C2++) {
				if (ktn_stricmp(Metadata.Machines[C1].Visual_ID17[C2], Identifier)) {
					return &Metadata.Machines[C1];
				}
			}
		}
	}
	return NULL;
}

int Visual_To_Rotation(const char* Identifier) {
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		if (Metadata.Machines[C1].Visual_Type == I_Rot) {
			for (int C2 = 1; C2 < 4; C2++) {
				if (ktn_stricmp(Metadata.Machines[C1].Visual_ID4[C2], Identifier)) {
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