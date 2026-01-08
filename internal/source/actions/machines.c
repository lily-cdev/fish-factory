#include <interface.h>

void Handle_Spawning_Pool(int X, int Y) {
	if (Data.Settings_Grid[X][Y][3] > 3) {
		if (Interface.Engagement == 0) {
			Forward_Essentials(Rects.MSP_Buttons.Length, 1);
			if (Interface.UI_Selection == 3) {
				char Subbuffer[64];
				Abbreviate_Number(Data.Settings_Grid[X][Y][3] * 90, Subbuffer, sizeof(Subbuffer));
				snprintf(Buffers.JSON[0], sizeof(Buffers.JSON[0]), "volume\", \"%sL", Subbuffer);
				Abbreviate_Number(Data.Settings_Grid[X][Y][4], Subbuffer, sizeof(Subbuffer));
				snprintf(Buffers.JSON[1], sizeof(Buffers.JSON[1]), "food\", \"%sg", Subbuffer);
				strcpy(Buffers.JSON[2], NULLSTRING);
				Print_JSON();
			} else if (Interface.UI_Selection == 4) {
				if (Data.Settings_Grid[X][Y][5] > 0) {
					char Buffer[64];
					Get_Phase_Name(Buffer, sizeof(Buffer), (int)(Data.Settings_Grid[X][Y][6]),
						(int)(Data.Settings_Grid[X][Y][7]), (int)(Data.Settings_Grid[X][Y][5]));
					snprintf(Buffers.JSON[0], sizeof(Buffers.JSON[0]), "type\", \"%s %s", Fish_Catalog[(int)(Data
						.Settings_Grid[X][Y][6])].Name, Buffer);
					snprintf(Buffers.JSON[1], sizeof(Buffers.JSON[1]), "quantity\", \"%i", (int)Data.Settings_Grid[X][Y][5]);
					strcpy(Buffers.JSON[2], NULLSTRING);
					Print_JSON();
				} else {
					Print_Error(No_File);
				}
			} else if (Interface.UI_Selection == 5) {
				if (Data.Settings_Grid[X][Y][5] > 0) {
					Print_Error(Fish_Present);
				} else {
					int Added_Fish = (int)(Data.Settings_Grid[X][Y][3] * 1.125f);
					char Buffer[64];
					snprintf(Buffer, sizeof(Buffer), "added %i fish", Added_Fish);
					Print_Response(Buffer);
					Data.Settings_Grid[X][Y][5] = Added_Fish;
				}
			} else if (Interface.UI_Selection == 6) {
				if (Data.Settings_Grid[X][Y][5] > 0) {
					char Buffer[64];
					snprintf(Buffer, sizeof(Buffer), "released %i fish", (int)Data.Settings_Grid[X][Y][5]);
					Print_Response(Buffer);
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
}

void Handle_Dock(int X, int Y) {
	Forward_Essentials(Rects.SD_Buttons.Length, 0);
	if (Interface.UI_Selection == 3) {
		if (Transition.Submarine_Position.X == X &&
			Transition.Submarine_Position.Y == Y &&
			Transition.Submarine_Phase == 2) {
			int Issues[2] = { 0, 0 };
			for (int Counter1 = 0; Counter1 < 2; Counter1++) {
				if (ID_To_Item((int)(Data.Settings_Grid[X][Y][Counter1 + 5])).Value < 1 && Data.Settings_Grid[X][Y][
					Counter1 + 5] != LDE_INVALID) {
					Issues[Counter1] = 1;
				}
				if (Data.Settings_Grid[X][Y][Counter1 + 5] == LDE_INVALID) {
					Issues[Counter1] = 2;
				}
			}
			if (Issues[0] == 0 || Issues[1] == 0) {
				for (int Counter2 = 0; Counter2 < 2; Counter2++) {
					if (Issues[Counter2] == 0) {
						Data.Funds += Data.Settings_Grid[X][Y][Counter2 + 3] * ID_To_Item((int)(Data.Settings_Grid[X][Y][
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
		int Index = 0;
		for (int Counter1 = 0; Counter1 < 2; Counter1++) {
			char Carrier1[32] = "none";
			if (Data.Settings_Grid[X][Y][Counter1 + 5] != LDE_INVALID && ID_To_Item((int)(Data.Settings_Grid[X][Y][
				Counter1 + 5])).Value < 1) {
				strcpy(Carrier1, "low_value");
			}
			char Subbuffer1[64];
			Truncate(fabs(Data.Settings_Grid[X][Y][Counter1 + 3]), Get_Depth(LDE_DOCKCAPACITY), Subbuffer1, sizeof(Subbuffer1));
			char Subbuffer2[64];
			Abbreviate_Number(LDE_DOCKCAPACITY, Subbuffer2, sizeof(Subbuffer2));
			snprintf(Buffers.JSON[Index], sizeof(Buffers.JSON[Index]), "capacity_%d\", \"%s/%sL", Counter1 + 1,
				Subbuffer1, Subbuffer2);
			Index++;
			snprintf(Buffers.JSON[Index], sizeof(Buffers.JSON[Index]), "flags_%i\", \"%s", Counter1 + 1, Carrier1);
			Index++;
			char Carrier2[32] = "none";
			if (Data.Settings_Grid[X][Y][Counter1 + 5] != LDE_INVALID) {
				strcpy(Carrier2, ID_To_Item((int)(Data.Settings_Grid[X][Y][Counter1 + 5])).Display_Name);
				for (int Counter2 = 0; Counter2 < strlen(Carrier2); Counter2++) {
					Carrier2[Counter2] = (char)(tolower(Carrier2[Counter2]));
					if (Carrier2[Counter2] == ' ') {
						Carrier2[Counter2] = '_';
					}
				}
			}
			snprintf(Buffers.JSON[Index], sizeof(Buffers.JSON[Index]), "item_%i\", \"%s", Counter1 + 1, Carrier2);
			Index++;
		}
		strcpy(Buffers.JSON[Index], NULLSTRING);
		Print_JSON();
	} else if (Interface.UI_Selection == 5 || Interface.UI_Selection == 6) {
		char Buffer[64];
		char Subbuffer[64];
		Abbreviate_Number(Data.Settings_Grid[X][Y][Interface.UI_Selection - 2], Subbuffer, sizeof(Subbuffer));
		snprintf(Buffer, sizeof(Buffer), "%s liters drained from tank_%i", Subbuffer, Interface.UI_Selection - 4);
		Print_Response(Buffer);
		Data.Settings_Grid[X][Y][Interface.UI_Selection - 2] = 0;
		Data.Settings_Grid[X][Y][Interface.UI_Selection] = LDE_INVALID;
	}
	Backward_Essentials();
}

void Handle_Exchanger(int X, int Y) {
    if (Interface.Engagement == 0) {
		char Buffer1[128];
		char Buffer2[128];
		Forward_Essentials(Rects.HX_Buttons.Length, 2);
		switch (Interface.UI_Selection) {
		case 3:
			snprintf(Buffers.JSON[0], sizeof(Buffers.JSON[0]), "primary_valve\", \"%iL/s", (int)Data.Settings_Grid[X][Y][3]);
			snprintf(Buffers.JSON[1], sizeof(Buffers.JSON[1]), "feedwater_valve\", \"%iL/s", (int)Data.Settings_Grid[X][Y][4]);
			Abbreviate_Number(Data.Settings_Grid[X][Y][5], Buffer1, sizeof(Buffer1));
			Truncate(LDE_HXCAPACITY, 0, Buffer2, sizeof(Buffer2));
			snprintf(Buffers.JSON[2], sizeof(Buffers.JSON[2]), "primary_loop\", \"%s/%sL", Buffer1, Buffer2);
			Abbreviate_Number(Data.Settings_Grid[X][Y][6], Buffer1, sizeof(Buffer1));
			Truncate(LDE_HXCAPACITY, 0, Buffer2, sizeof(Buffer2));
			snprintf(Buffers.JSON[3], sizeof(Buffers.JSON[3]), "feedwater_loop\", \"%s/%sL", Buffer1, Buffer2);
			Abbreviate_Number(Data.Settings_Grid[X][Y][7], Buffer1, sizeof(Buffer1));
			snprintf(Buffers.JSON[4], sizeof(Buffers.JSON[4]), "primary_temp\", \"%s °F", Buffer1);
			Abbreviate_Number(Data.Settings_Grid[X][Y][8], Buffer1, sizeof(Buffer1)); 
			snprintf(Buffers.JSON[5], sizeof(Buffers.JSON[5]), "feedwater_temp\", \"%s °F", Buffer1);
			strcpy(Buffers.JSON[6], NULLSTRING);
			Print_JSON();
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
}

void Handle_Turbine(int X, int Y) {
	Forward_Essentials(Rects.MT_Buttons.Length, 0);
	if (Interface.UI_Selection == 3) {
		char Buffer[256];
		Truncate((Data.Settings_Grid[X][Y][3] * 1.5) + 0.5 + ((bool)(Data.Settings_Grid[X][Y][4]) ? 0.5 : 0), 0, Buffer,
			sizeof(Buffer));
		snprintf(Buffers.JSON[0], sizeof(Buffers.JSON[0]), "length\", \"%sm", Buffer);
		strcpy(Buffers.JSON[1], NULLSTRING);
		Print_JSON();
	}
	Backward_Essentials();
}