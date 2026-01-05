#include <Legacy_Interface.hpp>

void Handle_Spawning_Pool(int X, int Y) {
	if (Data.Settings_Grid[X][Y][3] > 3) {
		if (Interface.Engagement == 0) {
			Forward_Essentials(Rects.MSP_Buttons.Length, 1);
			if (Interface.UI_Selection == 3) {
				char Buffer1[64];
				char Subbuffer[64];
				Abbreviate_Number(Data.Settings_Grid[X][Y][3] * 90, Subbuffer, sizeof(Subbuffer));
				snprintf(Buffer1, sizeof(Buffer1), "volume\", \"%sL", Subbuffer);
				char Buffer2[64];
				Abbreviate_Number(Data.Settings_Grid[X][Y][4], Subbuffer, sizeof(Subbuffer));
				snprintf(Buffer2, sizeof(Buffer2), "food\", \"%sg", Subbuffer);
				std::string tmp1 = Buffer1;
				std::string tmp2 = Buffer2;
				Print_JSON({ tmp1, tmp2 });
			} else if (Interface.UI_Selection == 4) {
				if (Data.Settings_Grid[X][Y][5] > 0) {
					char Buffer[64];
					char Subbuffer[64];
					Get_Phase_Name(Subbuffer, sizeof(Subbuffer), (int)(Data.Settings_Grid[X][Y][6]),
						(int)(Data.Settings_Grid[X][Y][7]), static_cast<int>(Data.Settings_Grid[X][Y][5]));
					snprintf(Buffer, sizeof(Buffer), "type\", \"%s %s", Fish_Catalog[static_cast<int>(Data
						.Settings_Grid[X][Y][6])].Name, Subbuffer);
					std::string tmp = Buffer;
					Print_JSON({ Buffer, "quantity\", \"" + std::to_string(static_cast<int>(
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
	Forward_Essentials(Rects.TT_Buttons.Length, 0);
	if (Interface.UI_Selection > 3 && Interface.UI_Selection <
		Temporary.Docks.Length + 4) {
		if (Transition.Submarine_Position.X == LDE_INVALID &&
			Transition.Submarine_Position.Y == LDE_INVALID) {
			Print_Response("submarine sent");
			Transition.Submarine_Position = Temporary.Docks.Data[
				Interface.UI_Selection - 4];
			Transition.Submarine_Phase = 0;
			Transition.Submarine_Offset = 3000;
			Transition.Submarine_Vertical = 105;
		} else {
			Print_Error(Docked_Sub);
		}
	}
	Backward_Essentials();
	Purge_Excess();
}

void Handle_Dock(int X, int Y) {
	Forward_Essentials(Rects.SD_Buttons.Length, 0);
	if (Interface.UI_Selection == 3) {
		if (Transition.Submarine_Position.X == X &&
			Transition.Submarine_Position.Y == Y &&
			Transition.Submarine_Phase == 2) {
			int Issues[2] = { 0, 0 };
			for (int Counter1 = 0; Counter1 < 2; Counter1++) {
				if (ID_To_Item(static_cast<int>(Data.Settings_Grid[X][
					Y][Counter1 + 5])).Value < 1 && Data.Settings_Grid[
					X][Y][Counter1 + 5] != LDE_INVALID) {
					Issues[Counter1] = 1;
				}
				if (Data.Settings_Grid[X][Y][Counter1 + 5] == LDE_INVALID) {
					Issues[Counter1] = 2;
				}
			}
			if (Issues[0] == 0 || Issues[1] == 0) {
				for (int Counter2 = 0; Counter2 < 2; Counter2++) {
					if (Issues[Counter2] == 0) {
						Data.Funds += Data.Settings_Grid[X][
							Y][Counter2 + 3] * ID_To_Item(static_cast<int>(
							Data.Settings_Grid[X][Y][
							Counter2 + 5])).Sale_Value;
						Data.Settings_Grid[X][Y][Counter2 + 3] = 0;
						Data.Settings_Grid[X][Y][Counter2 + 5] = LDE_INVALID;
					}
				}
				Print_Response("Items sold");
				Transition.Submarine_Phase = 3;
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
			char Buffer[128];
			char Subbuffer1[64];
			Truncate(std::abs(Data.Settings_Grid[X][Y][Counter1 + 3]),
				Get_Depth(LDE_DOCKCAPACITY), Subbuffer1, sizeof(Subbuffer1));
			char Subbuffer2[64];
			Abbreviate_Number(LDE_DOCKCAPACITY, Subbuffer2, sizeof(Subbuffer2));
			snprintf(Buffer, sizeof(Buffer), "capacity_%d\", \"%s/%sL", Counter1 + 1, Subbuffer1, Subbuffer2);
			std::string tmp = Buffer;
			JSON.push_back(tmp);
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
		char Buffer[64];
		char Subbuffer[64];
		Abbreviate_Number(Data.Settings_Grid[X][Y][Interface.UI_Selection - 2], Subbuffer, sizeof(Subbuffer));
		snprintf(Buffer, sizeof(Buffer), "%s liters drained from tank_%i", Subbuffer, Interface.UI_Selection - 4);
		std::string tmp = Buffer;
		Print_Response(tmp);
		Data.Settings_Grid[X][Y][Interface.UI_Selection - 2] = 0;
		Data.Settings_Grid[X][Y][Interface.UI_Selection] = LDE_INVALID;
	}
	Backward_Essentials();
	Purge_Excess();
}

void Handle_Exchanger(int X, int Y) {
    if (Interface.Engagement == 0) {
		std::string Position;
		char Buffer[256];
		std::string tmp1;
		std::string tmp2;
		std::string tmp3;
		std::string tmp0;
		std::string tmp4;
		std::string tmp5;
		Forward_Essentials(Rects.HX_Buttons.Length, 2);
		switch (Interface.UI_Selection) {
		case 3:
			Abbreviate_Number(Data.Settings_Grid
				[X][Y][5], Buffer, sizeof(Buffer));
			tmp1 = Buffer;
			tmp1 = tmp1 + "/";
			Truncate(LDE_HXCAPACITY, 0, Buffer, sizeof(Buffer));;
			tmp0 = Buffer;
			tmp1 = tmp1 + tmp0;
			Abbreviate_Number(Data.Settings_Grid
					[X][Y][6], Buffer, sizeof(Buffer));
			tmp2 = Buffer;
			tmp2 += "/";
			Truncate(LDE_HXCAPACITY, 0, Buffer, sizeof(Buffer));
			tmp0 = Buffer;
			tmp2 += tmp0;
			Abbreviate_Number(Data.Settings_Grid[
					X][Y][7], Buffer, sizeof(Buffer));
			tmp4 = Buffer;
			Abbreviate_Number(
					Data.Settings_Grid[X][Y][8], Buffer, sizeof(Buffer)); 
			tmp5 = Buffer;
			Print_JSON({
				"primary_valve\", \"" + std::to_string(static_cast<int>(
				Data.Settings_Grid[X][Y][3])) + "L/s",
				"feedwater_valve\", \"" + std::to_string(static_cast<int>(
				Data.Settings_Grid[X][Y][4])) + "L/s",
				"primary_loop\", \"" + tmp1 + "L",
				"feedwater_loop\", \"" + tmp2 + "L",
				"primary_temp\", \"" + tmp4 + " °F",
				"feedwater_temp\", \"" + tmp5+ " °F"
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
		char Buffer[256];
		Truncate((Data.Settings_Grid[X][Y][3] * 1.5) + 0.5 +
		(static_cast<bool>(Data.Settings_Grid[X][Y][4]) ? 0.5 : 0), 0, Buffer, sizeof(Buffer));
		std::string tmp = Buffer;
		Print_JSON({
			"length\", \"" + tmp + "m"
		});
	}
	Backward_Essentials();
}