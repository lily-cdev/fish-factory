#include <items.h>

Item_Stack Get_Item(Point Pos) {
	for (int C1 = 0; C1 < LDE_ITEMS; C1++) {
		if (Preset_Items.Item_List[C1].Identifier == Data.Items_Grid[pt(Pos)]) {
			Item_Stack Selected_Item = Preset_Items.Item_List[C1];
			Selected_Item.Temperature = Data.Temperature_Grid[pt(Pos)];
			return Selected_Item;
		}
	}
	Item_Stack Blank_Item;
	strncpy(Blank_Item.Display_Name, "[none]", sizeof(Blank_Item.Display_Name));
	Blank_Item.Identifier = LDE_INVALID;
	Blank_Item.Temperature = LDE_ROOMTEMP;
	return Blank_Item;
}

Item_Stack ID_To_Item(const int ID) {
	for (int C1 = 0; C1 < LDE_ITEMS; C1++) {
		if (Preset_Items.Item_List[C1].Identifier == ID) {
			return Preset_Items.Item_List[C1];
		}
	}
	Item_Stack Blank_Item;
	strncpy(Blank_Item.Display_Name, "[none]", sizeof(Blank_Item.Display_Name));
	Blank_Item.Identifier = LDE_INVALID;
	Blank_Item.Temperature = LDE_ROOMTEMP;
	return Blank_Item;
}

Item_Stack Get_Item_Stack_Data() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				return Get_Item((Point){ Column, Row });
			}
		}
	}
	Item_Stack Blank_Stack;
	return Blank_Stack;
}

void Purge_Items() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			if (Data.Data_Grid[Column][Row][Stored_Fluids] < 0.1) {
				Data.Items_Grid[Column][Row] = LDE_INVALID;
				Data.Temperature_Grid[Column][Row] = LDE_ROOMTEMP;
			}
		}
	}
}

bool Check_Category(int Item, Item_Category Category) {
	for (int C1 = 0; C1 < Category.Length; C1++) {
		if (Item == Category.Contents[C1].Identifier) {
			return true;
		}
	}
	return false;
}

float Calculate_Pressure(int Temperature, float Boiling_Point, float H_Vaporisation) {
	float Temperature_K = (Temperature + 459.67f) / 1.8f;
	if (Boiling_Point == LDE_INVALID && H_Vaporisation == LDE_INVALID) {
		return LDE_INVALID;
	} else if (Boiling_Point == -2 && H_Vaporisation == -2) {
		return -2;
	} else {
		float Boiling_Point_K = (Boiling_Point + 459.67f) / 1.8f;
		float ATM = pow(M_E, ((H_Vaporisation * -1000) / 8.314462618) * ((1 / Temperature_K) - (1 / Boiling_Point_K)));
		return ATM * 1.01325f;
	}
}

void Update_Item(Point Pos, int Identifier, int Temperature) {
	Data.Items_Grid[pt(Pos)] = Identifier;
	Data.Temperature_Grid[pt(Pos)] = Temperature;
}