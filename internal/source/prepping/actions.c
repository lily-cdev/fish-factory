#include <ui.h>

void Load_Save(Parameter Slot, Parameter Unused) {
	Core.Selected_Save = Slot.Integer;
	if (Load_Data(Slot.Integer)) {
		Save_Data(Slot.Integer);
		Find_Effect();
		Restore_Cache();
		Cache.Wire_State = Deep_Recache;
	}
	Start_Transition(0);
	Wipe_Grid();
	Cache_Price();
	Cache_Blueprint();
}

void Free_Save(Parameter Slot, Parameter Unused) {
	char Buffer[256];
	snprintf(Buffer, sizeof(Buffer), "slot%d.pkg", Slot.Integer);
	Clear_File(Buffer);
	Get_Filesizes();
}

void New_Save(Parameter Slot, Parameter Unused) {
	Core.Selected_Save = Slot.Integer;
	Reset_Statistics();
	Find_Effect();
	Start_Transition(0);
	Wipe_Grid();
	Restore_Cache();
	Cache_Price();
	Cache_Blueprint();
	Cache.Wire_State = Deep_Recache;
}