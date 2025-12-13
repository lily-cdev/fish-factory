#include <Core.h>
#include <Preloader.h>
#include <Items.h>

Item_Stack Get_Item(int X, int Y) {
	for (int Counter = 0; Counter < Preset_Items_Access.Item_List.size(); Counter++) {
		if (Preset_Items_Access.Item_List[Counter].Identifier == Data_Access.Items_Grid[X][Y]) {
			Item_Stack Selected_Item = Preset_Items_Access.Item_List[Counter];
			Selected_Item.Temperature = Data_Access.Temperature_Grid[X][Y];
			return Selected_Item;
		}
	}
	Item_Stack Blank_Item;
	Blank_Item.Display_Name = "[none]";
	Blank_Item.Identifier = LDE_INVALID;
	Blank_Item.Temperature = LDE_ROOMTEMP;
	return Blank_Item;
}

Item_Stack ID_To_Item(const int ID) {
	for (int Counter = 0; Counter < Preset_Items_Access.Item_List.size(); Counter++) {
		if (Preset_Items_Access.Item_List[Counter].Identifier == ID) {
			return Preset_Items_Access.Item_List[Counter];
		}
	}
	Item_Stack Blank_Item;
	Blank_Item.Display_Name = "[none]";
	Blank_Item.Identifier = LDE_INVALID;
	Blank_Item.Temperature = LDE_ROOMTEMP;
	return Blank_Item;
}

Item_Stack Get_Item_Stack_Data() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rectangles_Access.Tile_1x1.x = static_cast<int>(((Column * 40) - UI_Access.Camera_X) * Settings_Access.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rectangles_Access.Tile_1x1.y = static_cast<int>(((Row * 40) - UI_Access.Camera_Y) * Settings_Access.Screen_Size);
			if (Detect_Mouse_Collision(Rectangles_Access.Tile_1x1)) {
				return Get_Item(Column, Row);
			}
		}
	}
	Item_Stack Blank_Stack;
	return Blank_Stack;
}

void Purge_Items() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			if (Data_Access.Data_Grid[Column][Row][Stored_Fluids] < 0.1) {
				Data_Access.Items_Grid[Column][Row] = LDE_INVALID;
				Data_Access.Temperature_Grid[Column][Row] = LDE_ROOMTEMP;
			}
		}
	}
}

void Update_Item(int X, int Y, int Identifier, int Temperature) {
	Data_Access.Items_Grid[X][Y] = Identifier;
	Data_Access.Temperature_Grid[X][Y] = Temperature;
}

bool Check_Category(int Item, Item_Category Category) {
	for (int Counter = 0; Counter < Category.Contents.size(); Counter++) {
		if (Item == Category.Contents[Counter].Identifier) {
			return true;
		}
	}
	return false;
}

double Calculate_Pressure(int Temperature, double Boiling_Point, double H_Vaporisation) {
	double Temperature_K = (Temperature + 459.67) / 1.8;
	if (Boiling_Point == LDE_INVALID && H_Vaporisation == LDE_INVALID) {
		return LDE_INVALID;
	} else if (Boiling_Point == -2 && H_Vaporisation == -2) {
		return -2;
	} else {
		double Boiling_Point_K = (Boiling_Point + 459.67) / 1.8;
		double Pressure_ATM = std::pow(M_E, ((H_Vaporisation * -1000) / 8.314462618) *
			((1 / Temperature_K) - (1 / Boiling_Point_K)));
		return Pressure_ATM * 1.01325;
	}
}