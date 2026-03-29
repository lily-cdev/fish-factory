#include <interface.h>

void Handle_Help(Point Pos) {
	if (Interface.Engagement == 0) {
		if (Interface.UI_Selection == 1) {
			Interface.Engagement = 1;
		}
		switch (Interface.Slider_Positions[3]) {
		case 1:
			if (Interface.UI_Selection > 2 && Interface.UI_Selection < 5) {
				Temporary.Tutorial_Step = 0;
				Close_Prompt();
			}
		case 2:
			if (Interface.UI_Selection > 1 && Interface.UI_Selection < 5) {
				Interface.Tool = T_Building;
				Close_Prompt();
				Cache_Blueprint();
				Cache_Price();
			}
			break;
		default:
			break;
		}
	} else {
		Interface.Engagement = 0;
	}
}

void Handle_Catalog(Point Pos) {
	if (Interface.UI_Selection > 3) {
		Interface.Subprompt_Identifier = Interface.UI_Selection - 3;
	}
}