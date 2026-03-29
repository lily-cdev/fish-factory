#include <interface.h>

void Handle_Spawning_Pool(Point Pos) {
	if (Data.Settings_Grid[pt(Pos)][3] > 3) {
		if (Interface.Engagement == 0) {
			Forward_Essentials(Rects.MSP_Buttons.Length, 1);
			if (Interface.UI_Selection == 9) {
				Interface.Engagement = 1;
			}
		} else {
			Interface.Engagement = 0;
		}
	}
}

void Handle_Transmitter(Point Pos) {
	Forward_Essentials(Rects.TT_Buttons.Length, 0);
}

void Handle_Dock(Point Pos) {
	Forward_Essentials(Rects.SD_Buttons.Length, 0);
}

void Handle_Exchanger(Point Pos) {
    if (Interface.Engagement == 0) {
		Forward_Essentials(Rects.HX_Buttons.Length, 2);
		switch (Interface.UI_Selection) {
        case 6:
            Interface.Engagement = 3;
            break;
        case 7:
            Interface.Engagement = 2;
            break;
        default:
            break;
        }
	} else {
		Interface.Engagement = 0;
	}
}

void Handle_Turbine(Point Pos) {
	Forward_Essentials(Rects.MT_Buttons.Length, 0);
}