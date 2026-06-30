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
	snprintf(Buffer, sizeof(Buffer), "assets/data/slot%d.pkg", Slot.Integer);
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

void Click_Sidebar(Parameter Bar, Parameter Unused) {
	switch (Bar.Integer) {
	case 0:
		Interface.Prompt_Identifier = P_Help;
		break;
	case 1:
		if (Interface.Save_Frames < 1) {
			Interface.Save_Frames = Interface.Frame_Rate * 2;
			Save_Data(Core.Selected_Save);
		}
		break;
	case 2:
		Interface.Prompt_Identifier = P_Catalog;
		break;
	case 3:
		Interface.Prompt_Identifier = P_Genetics;
		break;
	case 4:
		if (Interface.Tool == T_Building) {
			Interface.Rotation = 0;
			Clear_Unconnected_Bridges(&Wires);
			Clear_Unconnected_Bridges(&Pipes);
			Update_Grid();
			Cache_Blueprint();
		}
		if (Interface.Tool == ktn_invalid) {
			Save_Data(Core.Selected_Save);
			Wires.Length = 0;
			Wires.Full_Size = 0;
			ktn_free(Wires.Data);
			Pipes.Length = 0;
			Pipes.Full_Size = 0;
			ktn_free(Pipes.Data);
			memset(Tutorial_Stack, 0, sizeof(Tutorial_Stack));
			Temporary.Tutorial_Step = ktn_invalid;
			Start_Transition(2);
			Core.Selected_Save = ktn_invalid;
			Get_Filesizes();
			Interface.Item = Get_Machine("heavy_pipe");
			Cache_Blueprint();
		} else {
			if (Interface.Tool < 4) {
				Interface.Tool++;
			} else {
				Interface.Tool = 0;
			}
		}
		break;
	default:
		break;
	}
}