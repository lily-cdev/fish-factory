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
		if (Interface.Engagement == 0 && Interface.Registering_Keybind == ktn_invalid) {
			if (Interface.UI_Selection > 5 && Interface.UI_Selection < 20) {
				Interface.Registering_Keybind = Interface.UI_Selection - 6;
			}
		} else {
			Interface.Engagement = 0;
		}
		break;
	default:
		break;
	}
}