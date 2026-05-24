#include <items.h>

Item_Ptr Get_Item(const char* Index) {
	for (int C1 = 0; C1 < Core.Items; C1++) {
		if (ktn_stricmp(Metadata.Items[C1].Index, Index)) {
			return &Metadata.Items[C1];
		}
	}
	return &Metadata.Null_Item;
}

Item_Ptr Get_ID_Item(const int ID) {
	for (int C1 = 0; C1 < Core.Items; C1++) {
		if (Metadata.Items[C1].ID == ID) {
			return &Metadata.Items[C1];
		}
	}
	return &Metadata.Null_Item;
}

void Purge_Items() {
	for (int Column = 0; Column < ktn_grid_size; Column++) {
		for (int Row = 0; Row < ktn_grid_size; Row++) {
			if (Data.Data_Grid[Column][Row][Stored_Fluids] < ktn_epsilon) {
				Data.Items_Grid[Column][Row] = ktn_invalid;
				Data.Temperature_Grid[Column][Row] = ktn_room_temp;
			}
		}
	}
}

float Calculate_Pressure(int Temperature, float Boiling_Point, float H_Vaporisation) {
	float Temperature_K = (Temperature + 459.67f) / 1.8f;
	if (Boiling_Point == ktn_invalid && H_Vaporisation == ktn_invalid) {
		return ktn_invalid;
	} else if (Boiling_Point == -2 && H_Vaporisation == -2) {
		return -2;
	} else {
		float Boiling_Point_K = (Boiling_Point + 459.67f) / 1.8f;
		float ATM = powf(M_E, ((H_Vaporisation * -1000.0f) / 8.314462618f) * ((1.0f / Temperature_K) - (1.0f / Boiling_Point_K)));
		return ATM * 1.01325f;
	}
}

void Update_Item(Point Pos, int Identifier, int Temperature) {
	Data.Items_Grid[pt(Pos)] = Identifier;
	Data.Temperature_Grid[pt(Pos)] = Temperature;
}