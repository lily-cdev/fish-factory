#include <Legacy_Interface.hpp>

void Handle_Money_Generator(int X, int Y) {
    if (Interface.Engagement == 0) {
        switch (Interface.UI_Selection) {
        case 2:
            Interface.Engagement = 1;
            break;
        case 3:
            Data.Settings_Grid[X][Y][3] = Interface.Slider_Positions[8];
            Data.Settings_Grid[X][Y][4] = sgn(Interface.Slider_Positions[8] -
                5) * std::pow(1000, std::abs(Interface.Slider_Positions[8] - 5) - 1);
            break;
        case 4:
            Interface.Slider_Positions[8] = Data.Settings_Grid[X][Y][3];
            break;
        default:
            break;
        }
    } else {
        Interface.Engagement = 0;
    }
}

void Handle_Fluid_Generator(int X, int Y) {
	if (Interface.Engagement == 0) {
		if (Interface.UI_Selection > 1 && Interface.UI_Selection < 5) {
			Interface.Engagement = Interface.UI_Selection - 1;
		} else if (Interface.UI_Selection == 5) {
			Data.Settings_Grid[X][Y][3] = Interface.Slider_Positions[9];
			Data.Settings_Grid[X][Y][4] = Interface.Slider_Positions[10] * 5;
			Data.Settings_Grid[X][Y][5] = Interface.Valve300_Postions[Interface.Slider_Positions[11]];
		} else if (Interface.UI_Selection == 6) {
			Interface.Slider_Positions[9] = Data.Settings_Grid[X][Y][3];
			Interface.Slider_Positions[10] = Data.Settings_Grid[X][Y][4] / 5;
			for (int Counter = 0; Counter < LDE_VALVE300LENGTH; Counter++) {
				if (Data.Settings_Grid[X][Y][5] == Interface.Valve300_Postions[Counter]) {
					Interface.Slider_Positions[11] = Counter;
					break;
				}
			}
		}
	} else {
		Interface.Engagement = 0;
	}
}