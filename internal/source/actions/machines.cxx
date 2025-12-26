#include <interface.h>

void Handle_Spawning_Pool(int X, int Y) {
	if (Data.Settings_Grid[X][Y][3] > 3) {
		if (Interface.Engagement == 0) {
			Forward_Essentials(Rects.MSP_Buttons.Length, 1);
			if (Interface.UI_Selection == 3) {
				Print_JSON({ "volume\", \"" + Abbreviate_Number(Data.Settings_Grid[X]
					[Y][3] * 90) + "L", "food\", \"" + Abbreviate_Number(
					Data.Settings_Grid[X][Y][4]) + "g" });
			} else if (Interface.UI_Selection == 4) {
				if (Data.Settings_Grid[X][Y][5] > 0) {
					Print_JSON({ "type\", \"" + Fish_Catalog[static_cast<int>(Data
						.Settings_Grid[X][Y][6])].Name + " " + Get_Phase_Name(
						static_cast<int>(Data.Settings_Grid[X]
						[Y][6]), static_cast<int>(Data.Settings_Grid
						[X][Y][7]), static_cast<int>(Data.Settings_Grid[X][Y][5])),
						"quantity\", \"" + std::to_string(static_cast<int>(
						Data.Settings_Grid[X][Y][5])) });
				} else {
					Print_Error(No_File);
				}
			} else if (Interface.UI_Selection == 5) {
				if (Data.Settings_Grid[X][Y][5] > 0) {
					Print_Error(Fish_Present);
				} else {
					int Added_Fish = static_cast<int>(Data
						.Settings_Grid[X][Y][3] * 1.125);
					Print_Response("added " + std::to_string(Added_Fish) + " fish");
					Data.Settings_Grid[X][Y][5] = Added_Fish;
				}
			} else if (Interface.UI_Selection == 6) {
				if (Data.Settings_Grid[X][Y][5] > 0) {
					Print_Response("released " + std::to_string(static_cast<int>(
						Data.Settings_Grid[X][Y][5])) + " fish");
					Data.Settings_Grid[X][Y][5] = 0;
					Data.Settings_Grid[X][Y][7] = 0;
				} else {
					Print_Error(No_Fish);
				}
			} else if (Interface.UI_Selection == 9) {
				Interface.Engagement = 1;
			}
			Backward_Essentials();
		} else {
			Interface.Engagement = 0;
		}
	} else {
		Process_Exit();
	}
	Purge_Excess();
}

void Handle_Transmitter(int X, int Y) {
	Forward_Essentials(Rects.TT_Buttons.Data[
		Temporary.Dialogue_Position].Length, 0);
	switch (Temporary.Dialogue_Position) {
	case 0:
		if (Interface.UI_Selection == 3) {
			Print_Response("input docking position");
			Temporary.Dialogue_Position = 1;
		}
		break;
	case 1:
		if (Interface.UI_Selection == 3) {
			Print_Response("transmission disconnected");
			Temporary.Dialogue_Position = 0;
		} else if (Interface.UI_Selection > 3 && Interface.UI_Selection <
			Temporary.Docks.size() + 4) {
			if (Temporary.Submarine_Position.X == LDE_INVALID &&
				Temporary.Submarine_Position.Y == LDE_INVALID) {
				Print_Response("submarine sent");
				Temporary.Submarine_Position = Temporary.Docks
					[Interface.UI_Selection - 4];
				Temporary.Submarine_Phase = 0;
				Temporary.Submarine_Offset = 3000;
				Temporary.Submarine_Vertical = 105;
			} else {
				Print_Error(Docked_Sub);
			}
		}
		break;
	default:
		break;
	}
	Backward_Essentials();
	Purge_Excess();
}

void Handle_Dock(int X, int Y) {
	Forward_Essentials(Rects.SD_Buttons.Length, 0);
	if (Interface.UI_Selection == 3) {
		if (Temporary.Submarine_Position.X == X &&
			Temporary.Submarine_Position.Y == Y &&
			Temporary.Submarine_Phase == 2) {
			int Issues[2] = { 0, 0 };
			for (int Counter1 = 0; Counter1 < 2; Counter1++) {
				if (ID_To_Item(static_cast<int>(Data.Settings_Grid[X]
					[Y][Counter1 + 5])).Value < 1 && Data.Settings_Grid
					[X][Y][Counter1 + 5] != LDE_INVALID) {
					Issues[Counter1] = 1;
				}
				if (Data.Settings_Grid[X][Y][Counter1 + 5] == LDE_INVALID) {
					Issues[Counter1] = 2;
				}
			}
			if (Issues[0] == 0 || Issues[1] == 0) {
				for (int Counter2 = 0; Counter2 < 2; Counter2++) {
					if (Issues[Counter2] == 0) {
						Data.Funds += Data.Settings_Grid[X]
							[Y][Counter2 + 3] * ID_To_Item(static_cast<int>(
							Data.Settings_Grid[X][Y]
							[Counter2 + 5])).Sale_Value;
						Data.Settings_Grid[X][Y][Counter2 + 3] = 0;
						Data.Settings_Grid[X][Y][Counter2 + 5] = LDE_INVALID;
					}
				}
				Print_Response("Items sold");
				Temporary.Submarine_Phase = 3;
			} else {
				int Errors[2] = { Low_Value, Empty_Target };
				for (int Counter2 = 0; Counter2 < 2; Counter2++) {
					Print_Error(Errors[Issues[Counter2] - 1]);
				}
			}
		} else {
			Print_Error(No_Docked_Sub);
		}
	} else if (Interface.UI_Selection == 4) {
		std::vector<std::string> JSON = { };
		for (int Counter1 = 0; Counter1 < 2; Counter1++) {
			std::string Carrier1 = "none";
			if (Data.Settings_Grid[X][Y][Counter1 + 5] !=
				LDE_INVALID && ID_To_Item(static_cast<int>(
				Data.Settings_Grid[X][Y][Counter1 + 5])).Value < 1) {
				Carrier1 = "low_value";
			}
			JSON.push_back("capacity_" + std::to_string(Counter1 + 1) + "\", \"" +
				Truncate(std::abs(Data.Settings_Grid[X][Y][Counter1 + 3]),
				Get_Depth(LDE_DOCKCAPACITY)) + "/" + Abbreviate_Number(LDE_DOCKCAPACITY) + "L");
				JSON.push_back("flags_" + std::to_string(Counter1 + 1) + "\", \"" + Carrier1);
			std::string Carrier2 = "none";
			if (Data.Settings_Grid[X][Y][Counter1 + 5] != LDE_INVALID) {
				Carrier2 = ID_To_Item(static_cast<int>(Data.Settings_Grid[
					X][Y][Counter1 + 5])).Display_Name;
				for (int Counter2 = 0; Counter2 < Carrier2.size(); Counter2++) {
					Carrier2[Counter2] = static_cast<char>(std::tolower(Carrier2[Counter2]));
					if (Carrier2[Counter2] == ' ') {
						Carrier2[Counter2] = '_';
					}
				}
			}
			JSON.push_back("item_" + std::to_string(Counter1 + 1) + "\", \"" + Carrier2);
		}
		Print_JSON(JSON);
	} else if (Interface.UI_Selection == 5 || Interface.UI_Selection == 6) {
		Print_Response(Abbreviate_Number(Data.Settings_Grid[X][
			Y][Interface.UI_Selection - 2]) + " liters drained from tank_" +
			std::to_string(Interface.UI_Selection - 4));
		Data.Settings_Grid[X][Y][Interface.UI_Selection - 2] = 0;
		Data.Settings_Grid[X][Y][Interface.UI_Selection] = LDE_INVALID;
	}
	Backward_Essentials();
	Purge_Excess();
}

void Handle_Exchanger(int X, int Y) {
    if (Interface.Engagement == 0) {
		std::string Position;
		Forward_Essentials(Rects.HX_Buttons.Length, 2);
		switch (Interface.UI_Selection) {
		case 3:
			Print_JSON({
				"primary_valve\", \"" + std::to_string(static_cast<int>(
				Data.Settings_Grid[X][Y][3])) + "L/s",
				"feedwater_valve\", \"" + std::to_string(static_cast<int>(
				Data.Settings_Grid[X][Y][4])) + "L/s",
				"primary_loop\", \"" + Abbreviate_Number(Data.Settings_Grid
					[X][Y][5]) + "/" + Truncate(LDE_HXCAPACITY, 0) + "L",
				"feedwater_loop\", \"" + Abbreviate_Number(Data.Settings_Grid
					[X][Y][6]) + "/" + Truncate(LDE_HXCAPACITY, 0) + "L",
				"primary_temp\", \"" + Abbreviate_Number(Data.Settings_Grid[
					X][Y][7]) + " °F", "feedwater_temp\", \"" + Abbreviate_Number(
					Data.Settings_Grid[X][Y][8]) + " °F"
			});
			break;
        case 6:
            Interface.Engagement = 3;
            break;
        case 7:
            Interface.Engagement = 2;
            break;
        default:
            break;
        }
		Backward_Essentials();
	} else {
		Interface.Engagement = 0;
	}
	Purge_Excess();
}

void Handle_Turbine(int X, int Y) {
	Forward_Essentials(Rects.MT_Buttons.Length, 0);
	if (Interface.UI_Selection == 3) {
		Print_JSON({
			"length\", \"" + Truncate((Data.Settings_Grid[
			X][Y][3] * 1.5) + 0.5 + (static_cast<bool>(Data
			.Settings_Grid[X][Y][4]) ? 0.5 : 0), 0) + "m"
		});
	}
	Backward_Essentials();
}