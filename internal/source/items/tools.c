#include <items.h>

Item_Ptr Get_Item(const char* Index) {
	if (ktn_stricmp(Metadata.Null_Item.Index, Index)) {
		return &Metadata.Null_Item;
	}
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
				strncpy(Data.Items_Grid[Column][Row], Metadata.Null_Item.Index, 64);
				Data.Temperature_Grid[Column][Row] = ktn_room_temp;
			}
		}
	}
}

void Update_Item(Point Pos, char Identifier[64], int Temperature) {
	strncpy(Data.Items_Grid[pt(Pos)], Identifier, 64);
	Data.Temperature_Grid[pt(Pos)] = Temperature;
}