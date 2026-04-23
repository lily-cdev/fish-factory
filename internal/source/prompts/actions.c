#include <ui.h>
#include <tutorials.h>

void Spawn_Cheat(Parameter Type, Parameter Unused) {
	int Subitems[3] = { Money_Generator, Fluid_Generator, Power_Generator };
	Interface.Item = Subitems[Type.Integer] + 1;
}

void Cancel_Tutorial(Parameter Unused, Parameter Unused2) {
	memset(Tutorial_Stack, 0, sizeof(Tutorial_Stack));
	Temporary.Tutorial_Step = LDE_INVALID;
}

void CMD_Tutorial(Parameter Unused, Parameter Unused2) {
	Tutorial_Step Template[256] = {
		{ T_Key, 4, 0, "", 0, { NULLPOINT }, false, "enable the build tool" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "open the catalog" },
		{ T_Button, 0, 10, "Special", 0, { NULLPOINT }, false, "open the \"Special\" category" },
		{ T_Button, 0, 3, "Command Platform", 0, { NULLPOINT }, false,
			"select the \"Command Platform\" item" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "close the catalog" },
		{ 6, 4, 200, "", 0, { NULLPOINT }, false, "put the placement site into view" },
		{ 2, 0, 0, "", 43, { { 3, 8 }, NULLPOINT }, false, "allow time to progress" },
		{ T_Key, 4, 0, "", 0, { NULLPOINT }, false, "disable the build tool" },
		{ T_Terminator }
	};
	memcpy_c(Tutorial_Stack, Template, sizeof(Template));
	Temporary.Tutorial_Size = (Point){ 320, 240 };
	Temporary.Tutorial_Offset = (Point){ 0, 200 };
}

void Gen_Tutorial(Parameter Unused, Parameter Unused2) {
	Tutorial_Step Template[256] = {
		{ T_Key, 4, 0, "", 0, { NULLPOINT }, false, "enable the build tool" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "open the catalog" },
		{ T_Button, 0, 4, "Extraction", 0, { NULLPOINT }, false, "open the \"Extraction\" category" },
		{ T_Button, 0, 3, "Ram Pump", 0, { NULLPOINT }, false, "select the \"Ram Pump\" item" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "close the catalog" },
		{ 2, 0, 0, "", 17, { { 4, 5 }, { 3, 6 }, { 4, 7 }, NULLPOINT }, false, "pump in water for the Filtration Plant" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "open the catalog" },
		{ T_Button, 0, 6, "Processing", 0, { NULLPOINT }, false, "open the \"Processing\" category" },
		{ T_Button, 0, 3, "Filtration Plant", 0, { NULLPOINT }, false, "select the \"Filtration Plant\" item" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "close the catalog" },
		{ 2, 0, 0, "", 22, { { 5, 5 }, NULLPOINT }, false, "filter water into fuel" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "open the catalog" },
		{ T_Button, 0, 9, "Other", 0, { NULLPOINT }, false, "open the \"Other\" category" },
		{ T_Button, 0, 3, "Incinerator", 0, { NULLPOINT }, false, "select the \"Incinerator\" item" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "close the catalog" },
		{ 2, 0, 0, "", 18, { { 7, 5 }, { 7, 7 }, NULLPOINT }, false, "dispose of unwanted byproducts" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "open the catalog" },
		{ T_Button, 0, 7, "Generation", 0, { NULLPOINT }, false, "open the \"Generation\" category" },
		{ T_Button, 0, 4, "Compact Firebox", 0, { NULLPOINT }, false, "select the \"Compact Firebox\" item" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "close the catalog" },
		{ 2, 0, 0, "", 23, { { 8, 3 }, NULLPOINT }, false, "burn fuel for electricity" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "open the catalog" },
		{ T_Button, 0, 3, "Logistics", 0, { NULLPOINT }, false, "open the \"Logistics\" category" },
		{ T_Button, 0, 3, "Reinforced Pipe", 0, { NULLPOINT }, false, "select the \"Reinforced Pipe\" item" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "close the catalog" },
		{ 2, 0, 0, "", 0, { { 4, 6 }, { 7, 6 }, { 8, 6 }, NULLPOINT }, true, "transport fluids between machines" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "open the catalog" },
		{ T_Button, 0, 3, "Logistics", 0, { NULLPOINT }, false, "open the \"Logistics\" category" },
		{ T_Button, 0, 5, "Cable Node", 0, { NULLPOINT }, false, "select the \"Cable Node\" item" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "close the catalog" },
		{ 2, 0, 0, "", 63, { { 8, 7 }, NULLPOINT }, false, "transport power between machines" },
		{ T_Key, 8, 0, "", 0, { NULLPOINT }, false, "enable the plumbing tool" },
		{ 3, 0, 0, "", 0, { { 4, 7 }, { 4, 6 }, { 4, 5 }, { 4, 6 }, { 3, 6 }, { 4, 6 }, { 6, 6 }, { 7, 6 }, { 7, 6 },
			{ 8, 6 }, { 4, 6 }, { 5, 6 }, { 6, 5 }, { 7, 5 }, { 6, 7 }, { 7, 7 }, { 8, 6 }, { 8, 5 }, NULLPOINT }, false,
			"allow fluids to flow" },
		{ T_Key, 7, 0, "", 0, { NULLPOINT }, false, "enable the wiring tool" },
		{ 4, 0, 0, "", 0, { { 8, 7 }, { 3, 6 }, { 8, 7 }, { 4, 5 }, { 8, 7 }, { 4, 7 }, { 8, 7 }, { 5, 5 }, NULLPOINT },
			false, "allow power to be distributed" },
		{ T_Key, 4, 0, "", 0, { NULLPOINT }, false, "enable the build tool" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "open the catalog" },
		{ T_Button, 0, 7, "Generation", 0, { NULLPOINT }, false, "open the \"Generation\" category" },
		{ 1, 0, 3, "Piezoelectric Generator", 0, { NULLPOINT }, false, "select the \"Piezoelectric Generator\" item" },
		{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "close the catalog" },
		{ 2, 0, 0, "", 19, { { 3, 3 }, { 4, 3 }, { 5, 3 }, { 6, 3 }, { 7, 3 }, { 3, 4 }, { 4, 4 }, { 5, 4 }, { 6, 4 },
			{ 7, 4 }, NULLPOINT }, false, "generate a temporary supply of power" },
		{ T_Key, 7, 0, "", 0, { NULLPOINT }, false, "enable the wiring tool" },
		{ 4, 0, 0, "", 0, { { 3, 3 }, { 8, 7 }, { 4, 3 }, { 8, 7 }, { 5, 3 }, { 8, 7 }, { 6, 3 }, { 8, 7 }, { 7, 3 },
			{ 8, 7 }, { 3, 4 }, { 8, 7 }, { 4, 4 }, { 8, 7 }, { 5, 4 }, { 8, 7 }, { 6, 4 }, { 8, 7 },
			{ 7, 4 }, { 8, 7 }, NULLPOINT }, false, "jumpstart the setup" },
		{ 5, 0, 60, "", 0, { NULLPOINT }, false, "allow the first cycle to begin" },
		{ T_Key, 5, 0, "", 0, { NULLPOINT }, false, "enable the delete tool" },
		{ 2, 0, 0, "", 0, { { 3, 3 }, { 4, 3 }, { 5, 3 }, { 6, 3 }, { 7, 3 }, { 3, 4 }, { 4, 4 }, { 5, 4 }, { 6, 4 },
			{ 7, 4 }, NULLPOINT }, false, "remove the jumpstarting equipment" },
		{ T_Key, 7, 0, "", 0, { NULLPOINT }, false, "enable the wiring tool" },
		{ 4, 0, 0, "", 0, { { 8, 3 }, { 8, 7 }, NULLPOINT }, false, "make the setup self-sustaining" },
		{ T_Key, 7, 0, "", 0, { NULLPOINT }, false, "disable the wiring tool" },
		{ T_Terminator }
	};
	memcpy_c(Tutorial_Stack, Template, sizeof(Template));
	Temporary.Tutorial_Size = (Point){ 320, 200 };
	Temporary.Tutorial_Offset = (Point){ 0, 0 };
}

void Fish_Tutorial(Parameter Unused, Parameter Unused2) {
	Temporary.Tutorial_Step = LDE_INVALID;
}

void Apply_M_Cheat(Parameter Machine, Parameter Unused) {
	Interface.Slider_Positions[8] = Data.Settings_Grid[pt(Machine.Pos)][3];
}

void Set_M_Cheat(Parameter Machine, Parameter Unused) {
	Data.Settings_Grid[pt(Machine.Pos)][3] = Interface.Slider_Positions[8];
	Data.Settings_Grid[pt(Machine.Pos)][4] = sgn(Interface.Slider_Positions[8] - 5) * powf(1000, fabsf(Interface.Slider_Positions[
		8] - 5.0f) - 1);	
}

void Apply_F_Cheat(Parameter Machine, Parameter Unused) {
	Interface.Slider_Positions[9] = Data.Settings_Grid[pt(Machine.Pos)][3];
	Interface.Slider_Positions[10] = (int)(Data.Settings_Grid[pt(Machine.Pos)][4] * 0.2f);
	for (int C1 = 0; C1 < LDE_VALVE300LENGTH; C1++) {
		if (Data.Settings_Grid[pt(Machine.Pos)][5] == Interface.Valve300_Postions[C1]) {
			Interface.Slider_Positions[11] = C1;
			break;
		}
	}
}

void Set_F_Cheat(Parameter Machine, Parameter Unused) {
	Data.Settings_Grid[pt(Machine.Pos)][3] = Interface.Slider_Positions[9];
	Data.Settings_Grid[pt(Machine.Pos)][4] = Interface.Slider_Positions[10] * 5;
	Data.Settings_Grid[pt(Machine.Pos)][5] = Interface.Valve300_Postions[Interface.Slider_Positions[11]];
}

void Apply_P_Cheat(Parameter Machine, Parameter Unused) {
	Interface.Slider_Positions[14] = Data.Settings_Grid[pt(Machine.Pos)][3];
}

void Set_P_Cheat(Parameter Machine, Parameter Unused) {
	Data.Settings_Grid[pt(Machine.Pos)][3] = (Interface.Slider_Positions[14] == 0) ? 0 : powf(10.0f, Interface.Slider_Positions[
		14] - 1.0f);
}

void Forward_Day(Parameter Unused, Parameter Unused2) {
	Interface.Prompt_Identifier = P_None;
	Interface.Subprompt_Identifier = LDE_INVALID;
	Data.Time = 0;
	if (Data.Day < 6) {
		Data.Day++;
	} else {
		Data.Day = 0;
	}
}

void Machine_Exit(Parameter Unused, Parameter Unused2) {
	Interface.Prompt_Identifier = LDE_INVALID;
	Interface.Subprompt_Identifier = LDE_INVALID;
}

void HX_Diagnostics(Parameter Pos, Parameter Unused) {
	char Buffer1[128];
	char Buffer2[128];
	snprintf(Buffers.JSON[0], sizeof(Buffers.JSON[0]), "primary_valve\", \"%iL/s", (int)Data.Settings_Grid[pt(Pos.Pos)][3]);
	snprintf(Buffers.JSON[1], sizeof(Buffers.JSON[1]), "feedwater_valve\", \"%iL/s", (int)Data.Settings_Grid[pt(Pos.Pos)][4]);
	Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][5], Buffer1, sizeof(Buffer1));
	Truncate(LDE_HXCAPACITY, 0, Buffer2, sizeof(Buffer2));
	snprintf(Buffers.JSON[2], sizeof(Buffers.JSON[2]), "primary_loop\", \"%s/%sL", Buffer1, Buffer2);
	Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][6], Buffer1, sizeof(Buffer1));
	Truncate(LDE_HXCAPACITY, 0, Buffer2, sizeof(Buffer2));
	snprintf(Buffers.JSON[3], sizeof(Buffers.JSON[3]), "feedwater_loop\", \"%s/%sL", Buffer1, Buffer2);
	Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][7], Buffer1, sizeof(Buffer1));
	snprintf(Buffers.JSON[4], sizeof(Buffers.JSON[4]), "primary_temp\", \"%s °F", Buffer1);
	Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][8], Buffer1, sizeof(Buffer1)); 
	snprintf(Buffers.JSON[5], sizeof(Buffers.JSON[5]), "feedwater_temp\", \"%s °F", Buffer1);
	strncpy(Buffers.JSON[6], NULLSTRING, sizeof(Buffers.JSON[6]));
	Print_JSON();
}

void MT_Diagnostics(Parameter Pos, Parameter Unused) {
	char Buffer[256];
	Truncate((Data.Settings_Grid[pt(Pos.Pos)][3] * 1.5f) + 0.5f + ((bool)(Data.Settings_Grid[pt(Pos.Pos)][4]) ? 0.5f : 0), 0,
		Buffer, sizeof(Buffer));
	snprintf(Buffers.JSON[0], sizeof(Buffers.JSON[0]), "length\", \"%sm", Buffer);
	strncpy(Buffers.JSON[1], NULLSTRING, sizeof(Buffers.JSON[1]));
	Print_JSON();
}

void SD_Link(Parameter Pos, Parameter Unused) {
	if (Transition.Sub_Pos.X == Pos.Pos.X && Transition.Sub_Pos.Y == Pos.Pos.Y && Transition.Sub_Phase == 2) {
		int Issues[2] = { 0, 0 };
		for (int C1 = 0; C1 < 2; C1++) {
			if (ID_To_Item((int)(Data.Settings_Grid[pt(Pos.Pos)][C1 + 5])).Value < 1 && Data.Settings_Grid[pt(Pos.Pos)][C1 + 5] !=
				LDE_INVALID) {
				Issues[C1] = 1;
			}
			if (Data.Settings_Grid[pt(Pos.Pos)][C1 + 5] == LDE_INVALID) {
				Issues[C1] = 2;
			}
		}
		if (Issues[0] == 0 || Issues[1] == 0) {
			for (int C2 = 0; C2 < 2; C2++) {
				if (Issues[C2] == 0) {
					Data.Funds += Data.Settings_Grid[pt(Pos.Pos)][C2 + 3] * ID_To_Item((int)(Data.Settings_Grid[pt(Pos.Pos)][
						C2 + 5])).Sale_Value;
					Data.Settings_Grid[pt(Pos.Pos)][C2 + 3] = 0;
					Data.Settings_Grid[pt(Pos.Pos)][C2 + 5] = LDE_INVALID;
				}
			}
			Print_Response("Items sold");
			Transition.Sub_Phase = 3;
		} else {
			int Errors[2] = { Low_Value, Empty_Target };
			for (int C2 = 0; C2 < 2; C2++) {
				Print_Error(Errors[Issues[C2] - 1]);
			}
		}
	} else {
		Print_Error(No_Docked_Sub);
	}
}

void SD_Manifest(Parameter Pos, Parameter Unused) {
	int Index = 0;
	for (int C1 = 0; C1 < 2; C1++) {
		char Carrier1[32] = "none";
		if (Data.Settings_Grid[pt(Pos.Pos)][C1 + 5] != LDE_INVALID && ID_To_Item((int)(Data.Settings_Grid[pt(Pos.Pos)][
			C1 + 5])).Value < 1) {
			strncpy(Carrier1, "low_value", sizeof(Carrier1));
		}
		char Subbuffer1[64];
		Truncate(fabsf(Data.Settings_Grid[pt(Pos.Pos)][C1 + 3]), Get_Depth(LDE_DOCKCAPACITY), Subbuffer1, sizeof(Subbuffer1));
		char Subbuffer2[64];
		Abbreviate_Number(LDE_DOCKCAPACITY, Subbuffer2, sizeof(Subbuffer2));
		snprintf(Buffers.JSON[Index], sizeof(Buffers.JSON[Index]), "capacity_%d\", \"%s/%sL", C1 + 1, Subbuffer1,
			Subbuffer2);
		Index++;
		snprintf(Buffers.JSON[Index], sizeof(Buffers.JSON[Index]), "flags_%i\", \"%s", C1 + 1, Carrier1);
		Index++;
		char Carrier2[32] = "none";
		if (Data.Settings_Grid[pt(Pos.Pos)][C1 + 5] != LDE_INVALID) {
			strncpy(Carrier2, ID_To_Item((int)(Data.Settings_Grid[pt(Pos.Pos)][C1 + 5])).Display_Name, sizeof(Carrier2));
			for (int C2 = 0; C2 < strlen(Carrier2); C2++) {
				Carrier2[C2] = (char)(tolower(Carrier2[C2]));
				if (Carrier2[C2] == ' ') {
					Carrier2[C2] = '_';
				}
			}
		}
		snprintf(Buffers.JSON[Index], sizeof(Buffers.JSON[Index]), "item_%i\", \"%s", C1 + 1, Carrier2);
		Index++;
	}
	strncpy(Buffers.JSON[Index], NULLSTRING, sizeof(Buffers.JSON[Index]));
	Print_JSON();
}

void SD_Drain(Parameter Pos, Parameter Tank) {
	char Buffer[64];
	char Subbuffer[64];
	Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][Tank.Integer + 3], Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "%s liters drained from tank_%i", Subbuffer, Tank.Integer + 1);
	Print_Response(Buffer);
	Data.Settings_Grid[pt(Pos.Pos)][Tank.Integer + 3] = 0;
	Data.Settings_Grid[pt(Pos.Pos)][Tank.Integer + 5] = LDE_INVALID;
}

void MSP_TInfo(Parameter Pos, Parameter Unused) {
	char Subbuffer[64];
	Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][3] * 90, Subbuffer, sizeof(Subbuffer));
	snprintf(Buffers.JSON[0], sizeof(Buffers.JSON[0]), "volume\", \"%sL", Subbuffer);
	Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][4], Subbuffer, sizeof(Subbuffer));
	snprintf(Buffers.JSON[1], sizeof(Buffers.JSON[1]), "food\", \"%sg", Subbuffer);
	strncpy(Buffers.JSON[2], NULLSTRING, sizeof(Buffers.JSON[2]));
	Print_JSON();
}

void MSP_FInfo(Parameter Pos, Parameter Unused) {
	if (Data.Settings_Grid[pt(Pos.Pos)][5] > 0) {
		char Buffer[64];
		Get_Phase_Name(Buffer, sizeof(Buffer), (int)(Data.Settings_Grid[pt(Pos.Pos)][6]),
			(int)(Data.Settings_Grid[pt(Pos.Pos)][7]), (int)(Data.Settings_Grid[pt(Pos.Pos)][5]));
		snprintf(Buffers.JSON[0], sizeof(Buffers.JSON[0]), "type\", \"%s %s", Fish_Catalog[(int)(Data.Settings_Grid[pt(Pos.Pos)][
			6])].Name, Buffer);
		snprintf(Buffers.JSON[1], sizeof(Buffers.JSON[1]), "quantity\", \"%i", (int)Data.Settings_Grid[pt(Pos.Pos)][5]);
		strncpy(Buffers.JSON[2], NULLSTRING, sizeof(Buffers.JSON[2]));
		Print_JSON();
	} else {
		Print_Error(No_File);
	}
}

void MSP_Fill(Parameter Pos, Parameter Unused) {
	if (Data.Settings_Grid[pt(Pos.Pos)][5] > 0) {
		Print_Error(Fish_Present);
	} else {
		int Added_Fish = (int)(Data.Settings_Grid[pt(Pos.Pos)][3] * 1.125f);
		char Buffer[64];
		snprintf(Buffer, sizeof(Buffer), "added %i fish", Added_Fish);
		Print_Response(Buffer);
		Data.Settings_Grid[pt(Pos.Pos)][5] = Added_Fish;
	}
}

void MSP_Empty(Parameter Pos, Parameter Unused) {
	if (Data.Settings_Grid[pt(Pos.Pos)][5] > 0) {
		char Buffer[64];
		snprintf(Buffer, sizeof(Buffer), "released %i fish", (int)Data.Settings_Grid[pt(Pos.Pos)][5]);
		Print_Response(Buffer);
		Data.Settings_Grid[pt(Pos.Pos)][5] = 0;
		Data.Settings_Grid[pt(Pos.Pos)][7] = 0;
	} else {
		Print_Error(No_Fish);
	}
}

void TT_Call_Sub(Parameter Dock, Parameter Unused) {
	if (Transition.Sub_Pos.X == LDE_INVALID && Transition.Sub_Pos.Y == LDE_INVALID) {
		Print_Response("submarine sent");
		Transition.Sub_Pos = Temporary.Docks.Data[Dock.Integer];
		Transition.Sub_Phase = 0;
		Transition.Sub_Offset = 3000;
		Transition.Sub_Vertical = 105;
	} else {
		Print_Error(Docked_Sub);
	}
}

#define In_Shop (Interface.Engagement == 0 && Interface.Prompt_Identifier == P_Shop)
void Shop_Category(Parameter Category, Parameter Unused) {
	if (Category.Integer >= 0 && Category.Integer < LDE_CATEGORIES && In_Shop) {
		Interface.Subtab = Category.Integer + 1;
	}
}

void Shop_Item(Parameter Subcategory, Parameter Unused) {
	if (In_Shop) {
		Interface.Item = Metadata.Subcontents[Interface.Subtab - LDE_CATEGORIES - 1][Subcategory.Integer] + 1;
		Cache_Blueprint();
	}
}

void Shop_Subcategory(Parameter Selection, Parameter Unused) {
	if (In_Shop) {
		Interface.Subtab = Metadata.Subcategory_Positions[Interface.Subtab - 1][Selection.Integer] + LDE_CATEGORIES + 1;
	}
}

void Shop_Subitem(Parameter Selection, Parameter Unused) {
	if (In_Shop) {
		Interface.Item = Metadata.Item_Labels[Interface.Subtab - 1][Selection.Integer] + 1;
		Cache_Blueprint();
	}
}
#undef In_Shop