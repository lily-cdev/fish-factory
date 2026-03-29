#include <interface.h>

void Handle_None(Point Pos) {
	switch (Interface.UI_Tab) {
	case 0:
		switch (Interface.UI_Selection) {
		case 0:
			if (Interface.Tool == T_Building && Interface.Prompt_Identifier == P_None) {
				Interface.Building = true;
			} else if (Interface.Tool == T_Deleting) {
				Destroy_Grid();
				Update_Grid();
			} else if (Interface.Tool == T_Wiring) {
				Place_Wire();
			} else if (Interface.Tool == T_Plumbing) {
				Place_Pipe();
				Update_Grid();
			}
			break;
		case 1:
			Interface.Prompt_Identifier = P_Help;
			break;
		case 2:
			if (Interface.Save_Frames < 1) {
				Interface.Save_Frames = Interface.Frame_Rate * 2;
				Save_Data(Core.Selected_Save);
			}
			break;
		case 3:
			Interface.Prompt_Identifier = P_Catalog;
			break;
		case 4:
			if (Interface.Tool == T_Building) {
				Interface.Rotation = 0;
				Clear_Unconnected_Bridges(&Wires);
				Clear_Unconnected_Bridges(&Pipes);
				Update_Grid();
				Cache_Blueprint();
			}
			if (Interface.Tool == LDE_INVALID) {
				Save_Data(Core.Selected_Save);
                memset(Tutorial_Stack, 0, sizeof(Tutorial_Stack));
				Temporary.Tutorial_Step = LDE_INVALID;
				Start_Transition(2);
				Core.Selected_Save = LDE_INVALID;
				Get_Filesizes();
				Interface.Item = 1;
				Cache_Blueprint();
			} else {
				if (Interface.Tool < 4) {
					Interface.Tool++;
				} else {
					Interface.Tool = 0;
				}
			}
			break;
		case 5:
			if (Interface.Tool == T_Building) {
				Interface.Rotation = 0;
				Clear_Unconnected_Bridges(&Wires);
				Clear_Unconnected_Bridges(&Pipes);
				Update_Grid();
				Cache_Blueprint();
			}
			if (Interface.Tool > 0) {
				Interface.Tool--;
			} else {
				Interface.Tool = 4;
			}
			break;
		default:
			break;
		}
		break;
	case 3:
		if (Interface.Engagement == 0 && Interface.Registering_Keybind == LDE_INVALID) {
			if (Interface.UI_Selection == 4) {
				Interface.Engagement = 1;
			} else if (Interface.UI_Selection > 5 && Interface.UI_Selection < 20) {
				Interface.Registering_Keybind = Interface.UI_Selection - 6;
			} else if (Interface.UI_Selection == 20) {
				Interface.Engagement = 2;
			} else if (Interface.UI_Selection == 21) {
				Interface.Engagement = 3;
			} else if (Interface.UI_Selection == 22) {
				Interface.Engagement = 4;
			}
		} else {
			Interface.Engagement = 0;
		}
		break;
	case 5:
		if (Interface.Engagement == 0) {
			switch (Interface.UI_Selection) {
			case 1:
				Start_Transition(1);
				break;
			case 2:
				Interface.Engagement = 1;
				break;
			default:
				break;
			}
		} else {
			Interface.Engagement = 0;
		}
		break;
	default:
		break;
	}
}