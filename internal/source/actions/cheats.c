#include <interface.h>

void Handle_Money_Generator(Point Pos) {
	if (Interface.Engagement == 0) {
		if (Interface.UI_Selection == 2) {
			Interface.Engagement = 1;
		}
	} else {
		Interface.Engagement = 0;
	}
}

void Handle_Fluid_Generator(Point Pos) {
	if (Interface.Engagement == 0) {
		if (Interface.UI_Selection > 1 && Interface.UI_Selection < 5) {
			Interface.Engagement = Interface.UI_Selection - 1;
		}
	} else {
		Interface.Engagement = 0;
	}
}

void Handle_Power_Generator(Point Pos) {
	if (Interface.Engagement == 0) {
		if (Interface.UI_Selection == 2) {
			Interface.Engagement = 1;
		}
	} else {
		Interface.Engagement = 0;
	}
}