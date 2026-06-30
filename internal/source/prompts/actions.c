#include <ui.h>
#include <tutorials.h>

void Spawn_Cheat(Parameter Type, Parameter Unused) {
	const char* Subitems[3] = { "money_cheat", "fluid_cheat", "power_cheat" };
	Interface.Item = Get_Machine(Subitems[Type.Integer]);
	Cache_Blueprint();
	Cache_Price();
	Interface.Prompt_Identifier = P_None;
	Interface.Tool = T_Building;
}

void Cancel_Tutorial(Parameter Unused, Parameter Unused2) {
	memset(Tutorial_Stack, 0, sizeof(Tutorial_Stack));
	Temporary.Tutorial_Step = ktn_invalid;
}

void CMD_Tutorial(Parameter Unused, Parameter Unused2) {
	Tutorial_Step Template[256] = {
		{ T_Key, 4, 0, "", 0, { ktn_null_point }, NULL, "enable the build tool" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "open the catalog" },
		{ T_Button, 0, 7, "special", 0, { ktn_null_point }, NULL, "open the \"special\" category" },
		{ T_Button, 0, 0, "command platform", 0, { ktn_null_point }, NULL, "select the \"command platform\" item" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "close the catalog" },
		{ 6, 4, 200, "", 0, { ktn_null_point }, NULL, "put the placement site into view" },
		{ T_Placement, 0, 0, "", 43, { { 3, 10 }, ktn_null_point }, NULL, "allow time to progress" },
		{ T_Key, 4, 0, "", 0, { ktn_null_point }, NULL, "disable the build tool" },
		{ T_Terminator }
	};
	ktn_memcpy(Tutorial_Stack, Template, sizeof(Template));
	Temporary.Tutorial_Size = (Point){ 320, 240 };
	Temporary.Tutorial_Offset = (Point){ 0, 280 };
	Temporary.Tutorial_Step = 0;
	Interface.Prompt_Identifier = P_None;
}

void Gen_Tutorial(Parameter Unused, Parameter Unused2) {
	Tutorial_Step Template[256] = {
		{ T_Key, 4, 0, "", 0, { ktn_null_point }, NULL, "enable the build tool" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "open the catalog" },
		{ T_Button, 0, 2, "cultivation", 0, { ktn_null_point }, NULL, "open the \"cultivation\" category" },
		{ T_Button, 0, 0, "algae bed", 0, { ktn_null_point }, NULL, "select the \"algae bed\" item" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "close the catalog" },
		{ T_Placement, 0, 0, "", 42, { { 5, 3 }, { 3, 3 }, { 7, 3 }, { 9, 3 }, { 11, 3 }, ktn_null_point }, NULL,
			"pump in algae for the filtration plant" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "open the catalog" },
		{ T_Button, 0, 3, "processing", 0, { ktn_null_point }, NULL, "open the \"processing\" category" },
		{ T_Button, 0, 0, "filtration plant", 0, { ktn_null_point }, NULL, "select the \"filtration plant\" item" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "close the catalog" },
		{ T_Placement, 0, 0, "", 22, { { 4, 7 }, ktn_null_point }, NULL, "filter water into fuel" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "open the catalog" },
		{ T_Button, 0, 6, "other", 0, { ktn_null_point }, NULL, "open the \"other\" category" },
		{ T_Button, 0, 0, "incinerator", 0, { ktn_null_point }, NULL, "select the \"incinerator\" item" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "close the catalog" },
		{ T_Placement, 0, 0, "", 18, { { 6, 9 }, ktn_null_point }, NULL, "dispose of unwanted byproducts" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "open the catalog" },
		{ T_Button, 0, 4, "generation", 0, { ktn_null_point }, NULL, "open the \"generation\" category" },
		{ T_Button, 0, 1, "furnace", 0, { ktn_null_point }, NULL, "select the \"furnace\" item" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "close the catalog" },
		{ T_Key, 11, 0, "", 0, { ktn_null_point }, NULL, "rotate the machine" },
		{ T_Placement, 0, 0, "", 102, { { 7, 7 }, ktn_null_point }, NULL, "burn fuel for electricity" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "open the catalog" },
		{ T_Button, 0, 0, "logistics", 0, { ktn_null_point }, NULL, "open the \"logistics\" category" },
		{ T_Button, 0, ktn_categories, "reinforced", 0, { ktn_null_point }, NULL, "open the \"reinforced\" subcategory" },
		{ T_Button, 0, 0, "reinforced pipe", 0, { ktn_null_point }, NULL, "select the \"reinforced pipe\" item" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "close the catalog" },
		{ T_Placement, 0, 0, "", 0, { { 3, 6 }, { 3, 7 }, { 3, 8 }, { 4, 6 }, { 5, 6 }, { 6, 6 }, { 7, 6 }, { 8, 6 },
			{ 9, 6 }, { 10, 6 }, { 11, 6 }, { 12, 6 }, { 6, 7 }, ktn_null_point }, Get_Machine("heavy_pipe"),
			"transport fluids between machines" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "open the catalog" },
		{ T_Button, 0, 0, "logistics", 0, { ktn_null_point }, NULL, "open the \"logistics\" category" },
		{ T_Button, 0, 1, "cable node", 0, { ktn_null_point }, NULL, "select the \"cable node\" item" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "close the catalog" },
		{ T_Placement, 0, 0, "", 63, { { 6, 8 }, ktn_null_point }, NULL, "transport power between machines" },
		{ T_Key, 8, 0, "", 0, { ktn_null_point }, NULL, "enable the plumbing tool" },
		{ 3, 0, 0, "", 0, { { 3, 5 }, { 3, 6 }, { 4, 5 }, { 4, 6 }, { 5, 5 }, { 5, 6 }, { 6, 5 }, { 6, 6 }, { 7, 5 }, { 7, 6 },
			{ 8, 5 }, { 8, 6 }, { 9, 5 }, { 9, 6 }, { 10, 5 }, { 10, 6 }, { 11, 5 }, { 11, 6 }, { 12, 5 }, { 12, 6 }, { 3, 6 },
			{ 3, 7 }, { 3, 7 }, { 3, 8 }, { 12, 6 }, { 11, 6 }, { 11, 6 }, { 10, 6 }, { 10, 6 }, { 9, 6 }, { 9, 6 }, { 8, 6 },
			{ 8, 6 }, { 7, 6 }, { 7, 6 }, { 6, 6 }, { 6, 6 }, { 5, 6 }, { 5, 6 }, { 4, 6 }, { 4, 6 }, { 3, 6 }, { 3, 8 },
			{ 4, 8 }, { 5, 7 }, { 6, 7 }, { 6, 7 }, { 7, 7 }, { 5, 9 }, { 6, 9 },
			ktn_null_point }, NULL, "allow fluids to flow" },
		{ T_Key, 7, 0, "", 0, { ktn_null_point }, NULL, "enable the wiring tool" },
		{ 4, 0, 0, "", 0, { { 6, 8 }, { 3, 3 }, { 6, 8 }, { 5, 3 }, { 6, 8 }, { 7, 3 }, { 6, 8 }, { 9, 3 }, { 6, 8 }, { 11, 3 },
			{ 6, 8 }, { 4, 7 }, ktn_null_point },
			NULL, "allow power to be distributed" },
		{ T_Key, 4, 0, "", 0, { ktn_null_point }, NULL, "enable the build tool" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "open the catalog" },
		{ T_Button, 0, 4, "generation", 0, { ktn_null_point }, NULL, "open the \"generation\" category" },
		{ T_Button, 0, 0, "radioisotopic generator", 0, { ktn_null_point }, NULL, "select the \"radioisotopic generator\" item" },
		{ T_Key, 9, 0, "", 0, { ktn_null_point }, NULL, "close the catalog" },//end
		{ T_Placement, 0, 0, "", 19, { { 10, 7 }, { 11, 7 }, { 12, 7 }, ktn_null_point }, NULL, "generate a supply of power" },
		{ T_Key, 7, 0, "", 0, { ktn_null_point }, NULL, "enable the wiring tool" },
		{ 4, 0, 0, "", 0, { { 10, 7 }, { 6, 8 }, { 11, 7 }, { 6, 8 }, { 12, 7 }, { 6, 8 }, ktn_null_point }, NULL,
			"power the setup" },
		{ T_Key, 7, 0, "", 0, { ktn_null_point }, NULL, "disable the wiring tool" },
		{ T_Terminator }
	};
	ktn_memcpy(Tutorial_Stack, Template, sizeof(Template));
	Temporary.Tutorial_Size = (Point){ 400, 280 };
	Temporary.Tutorial_Offset = (Point){ 0, 0 };
	Temporary.Tutorial_Step = 0;
	Interface.Prompt_Identifier = P_None;
}

void Fish_Tutorial(Parameter Unused, Parameter Unused2) {
	Temporary.Tutorial_Step = ktn_invalid;
}

void Apply_M_Cheat(Parameter Machine, Parameter Unused) {
	Interface.Slider_Positions[8] = Data.Settings_Grid[pt(Machine.Pos)][3];
}

void Set_M_Cheat(Parameter Machine, Parameter Unused) {
	Data.Settings_Grid[pt(Machine.Pos)][3] = Interface.Slider_Positions[8];
	Data.Settings_Grid[pt(Machine.Pos)][4] = ktn_sgn(Interface.Slider_Positions[8] - 5) * powf(1000.0f, fabsf(
		Interface.Slider_Positions[8] - 5.0f) - 1);	
}

void Apply_F_Cheat(Parameter Machine, Parameter Unused) {
	Interface.Slider_Positions[9] = Data.Settings_Grid[pt(Machine.Pos)][3];
	Interface.Slider_Positions[10] = (int)(Data.Settings_Grid[pt(Machine.Pos)][4] * 0.2f);
	for (int C1 = 0; C1 < ktn_valve300_len; C1++) {
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
	Interface.Slider_Positions[14] = (Data.Settings_Grid[pt(Machine.Pos)][3] == 0) ? 0 : log10f(Data.Settings_Grid[
		pt(Machine.Pos)][3]) + 1.0f;
}

void Set_P_Cheat(Parameter Machine, Parameter Unused) {
	Data.Settings_Grid[pt(Machine.Pos)][3] = (Interface.Slider_Positions[14] == 0) ? 0 : powf(10.0f, Interface.Slider_Positions[
		14] - 1.0f);
}

void Forward_Day(Parameter Unused, Parameter Unused2) {
	Interface.Prompt_Identifier = P_None;
	Interface.Subprompt_Identifier = ktn_invalid;
	Data.Time = 0;
	if (Data.Day < 6) {
		Data.Day++;
	} else {
		Data.Day = 0;
	}
}

void Machine_Exit(Parameter Unused, Parameter Unused2) {
	Interface.Prompt_Identifier = P_None;
	Interface.Subprompt_Identifier = ktn_invalid;
	memset(Interface.Terminal_Logs, 0, ktn_log_max * ktn_param_max);
	Interface.Terminal_Length = 0;
	Temporary.Ticker_Position = 0;
	Temporary.Ticker_Frames = 0;
}

void HX_Diagnostics(Parameter Pos, Parameter Unused) {
	Print_Input();
	char Buffer1[128];
	char Buffer2[128];
	snprintf(Buffers.JSON[0], sizeof(Buffers.JSON[0]), "primary_valve\", \"%i "ktn_unit"/s", (int)Data.Settings_Grid[pt(Pos.Pos)][3]);
	snprintf(Buffers.JSON[1], sizeof(Buffers.JSON[1]), "feedwater_valve\", \"%i "ktn_unit"/s", (int)Data.Settings_Grid[pt(Pos.Pos)][4]);
	Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][5], Buffer1, sizeof(Buffer1));
	Truncate(ktn_hx_cap, 0, Buffer2, sizeof(Buffer2));
	snprintf(Buffers.JSON[2], sizeof(Buffers.JSON[2]), "primary_loop\", \"%s/%s "ktn_unit, Buffer1, Buffer2);
	Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][6], Buffer1, sizeof(Buffer1));
	Truncate(ktn_hx_cap, 0, Buffer2, sizeof(Buffer2));
	snprintf(Buffers.JSON[3], sizeof(Buffers.JSON[3]), "feedwater_loop\", \"%s/%s "ktn_unit, Buffer1, Buffer2);
	Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][7], Buffer1, sizeof(Buffer1));
	snprintf(Buffers.JSON[4], sizeof(Buffers.JSON[4]), "primary_temp\", \"%sF", Buffer1);
	Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][8], Buffer1, sizeof(Buffer1)); 
	snprintf(Buffers.JSON[5], sizeof(Buffers.JSON[5]), "feedwater_temp\", \"%sF", Buffer1);
	strncpy(Buffers.JSON[6], ktn_null_string, sizeof(Buffers.JSON[6]));
	Print_JSON();
}

void MT_Diagnostics(Parameter Pos, Parameter Unused) {
	Print_Input();
	char Buffer[256];
	Truncate((Data.Settings_Grid[pt(Pos.Pos)][3] * 1.5f) + 0.5f + ((bool)(Data.Settings_Grid[pt(Pos.Pos)][4]) ? 0.5f : 0), 0,
		Buffer, sizeof(Buffer));
	snprintf(Buffers.JSON[0], sizeof(Buffers.JSON[0]), "length\", \"%sm", Buffer);
	for (int C1 = 0; C1 < 2; C1++) {
		Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][C1 + 8], Buffer, sizeof(Buffer));
		snprintf(Buffers.JSON[C1 + 1], sizeof(Buffers.JSON[C1 + 1]), "%s\", \"%sW", (C1 == 0) ? "target" : "yield", Buffer);
	}
	strcpy(Buffers.JSON[3], ktn_null_string);
	Print_JSON();
}

void SD_Link(Parameter Pos, Parameter Unused) {
	Print_Input();
	if (Transition.Sub_Pos.X == Pos.Pos.X && Transition.Sub_Pos.Y == Pos.Pos.Y && Transition.Sub_Phase == 2) {
		int Issues[2] = { 0, 0 };
		for (int C1 = 0; C1 < 2; C1++) {
			if (Get_ID_Item((int)(Data.Settings_Grid[pt(Pos.Pos)][C1 + 5]))->Worth == Worthless && Data.Settings_Grid[pt(
				Pos.Pos)][C1 + 5] != ktn_invalid) {
				Issues[C1] = 1;
			}
			if (Data.Settings_Grid[pt(Pos.Pos)][C1 + 5] == ktn_invalid) {
				Issues[C1] = 2;
			}
		}
		if (Issues[0] == 0 || Issues[1] == 0) {
			for (int C2 = 0; C2 < 2; C2++) {
				if (Issues[C2] == 0) {
					Data.Funds += Data.Settings_Grid[pt(Pos.Pos)][C2 + 3] * Get_ID_Item((int)(Data.Settings_Grid[pt(Pos.Pos)][C2 +
						5]))->Price;
					Data.Settings_Grid[pt(Pos.Pos)][C2 + 3] = 0;
					Data.Settings_Grid[pt(Pos.Pos)][C2 + 5] = ktn_invalid;
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
	Print_Input();
	int Index = 0;
	for (int C1 = 0; C1 < 2; C1++) {
		char Carrier1[32] = "none";
		if (Data.Settings_Grid[pt(Pos.Pos)][C1 + 5] != ktn_invalid && Get_ID_Item((int)(Data.Settings_Grid[pt(Pos.Pos)][C1 +
			5]))->Worth < 1) {
			strncpy(Carrier1, "low_value", sizeof(Carrier1));
		}
		char Subbuffer1[64];
		Truncate(fabsf(Data.Settings_Grid[pt(Pos.Pos)][C1 + 3]), Get_Depth(ktn_dock_cap), Subbuffer1, sizeof(Subbuffer1));
		char Subbuffer2[64];
		Abbreviate_Number(ktn_dock_cap, Subbuffer2, sizeof(Subbuffer2));
		snprintf(Buffers.JSON[Index], sizeof(Buffers.JSON[Index]), "capacity_%d\", \"%s/%s "ktn_unit, C1 + 1, Subbuffer1, Subbuffer2);
		Index++;
		snprintf(Buffers.JSON[Index], sizeof(Buffers.JSON[Index]), "flags_%i\", \"%s", C1 + 1, Carrier1);
		Index++;
		char Carrier2[32] = "none";
		if (Data.Settings_Grid[pt(Pos.Pos)][C1 + 5] != ktn_invalid) {
			strncpy(Carrier2, Get_ID_Item((int)(Data.Settings_Grid[pt(Pos.Pos)][C1 + 5]))->Name, sizeof(Carrier2));
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
	strncpy(Buffers.JSON[Index], ktn_null_string, sizeof(Buffers.JSON[Index]));
	Print_JSON();
}

void SD_Drain(Parameter Pos, Parameter Tank) {
	Print_Input();
	char Buffer[64];
	char Subbuffer[64];
	Abbreviate_Number(Data.Settings_Grid[pt(Pos.Pos)][Tank.Integer + 3], Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "%s liters drained from tank_%i", Subbuffer, Tank.Integer + 1);
	Print_Response(Buffer);
	Data.Settings_Grid[pt(Pos.Pos)][Tank.Integer + 3] = 0;
	Data.Settings_Grid[pt(Pos.Pos)][Tank.Integer + 5] = ktn_invalid;
}

void MSP_TInfo(Parameter Pos, Parameter Unused) {
	Print_Input();
	char Subbuffer[64];
	int ID = Data.Settings_Grid[pt(Pos.Pos)][5];
	Abbreviate_Number(Fishlinks[ID].Size * 0.9f, Subbuffer, sizeof(Subbuffer));
	snprintf(Buffers.JSON[0], sizeof(Buffers.JSON[0]), "volume\", \"%s "ktn_unit, Subbuffer);
	Abbreviate_Number(Fishlinks[ID].Nutrition, Subbuffer, sizeof(Subbuffer));
	snprintf(Buffers.JSON[1], sizeof(Buffers.JSON[1]), "food\", \"%suNI", Subbuffer);
	strncpy(Buffers.JSON[2], ktn_null_string, sizeof(Buffers.JSON[2]));
	Print_JSON();
}

void MSP_FInfo(Parameter Pos, Parameter Unused) {
	Print_Input();
	int ID = Data.Settings_Grid[pt(Pos.Pos)][5];
	if (Fishlinks[ID].Fish_Ct > 0) {
		char Buffer[64];
		int Alive = 0;
		int Injured = 0;
		int Dead = 0;
		int Max_Growth = 0;
		for (int C1 = 0; C1 < Fishlinks[ID].Fish_Ct; C1++) {
			if (Fishlinks[ID].Fish[C1].Damage >= ktn_health) {
				Dead++;
			} else if (Fishlinks[ID].Fish[C1].Damage > ktn_health * 0.5f) {
				Injured++;
			} else {
				Alive++;
			}
			Max_Growth = ktn_max(Fishlinks[ID].Fish[C1].Growth, Max_Growth);
		}
		Get_Phase_Name(Buffer, sizeof(Buffer), Fishlinks[ID].Type, Max_Growth, Fishlinks[ID].Fish_Ct);
		snprintf(Buffers.JSON[0], sizeof(Buffers.JSON[0]), "oldest_type\", \"%s %s", Fishlinks[ID].Type->Name, Buffer);
		snprintf(Buffers.JSON[1], sizeof(Buffers.JSON[1]), "quantity_live\", \"%i", Alive);
		snprintf(Buffers.JSON[2], sizeof(Buffers.JSON[2]), "quantity_hurt\", \"%i", Injured);
		snprintf(Buffers.JSON[3], sizeof(Buffers.JSON[3]), "quantity_dead\", \"%i", Dead);
		strncpy(Buffers.JSON[4], ktn_null_string, sizeof(Buffers.JSON[2]));
		Print_JSON();
	} else {
		Print_Error(No_File);
	}
}

void MSP_Fill(Parameter Pos, Parameter Unused) {
	Print_Input();
	int ID = Data.Settings_Grid[pt(Pos.Pos)][5];
	Print_Response((Fishlinks[ID].Autofill) ? "autofill off" : "autofill on");
	Fishlinks[ID].Autofill = !Fishlinks[ID].Autofill;
}

void MSP_Empty(Parameter Pos, Parameter Unused) {
	Print_Input();
	int ID = Data.Settings_Grid[pt(Pos.Pos)][5];
	if (Fishlinks[ID].Fish_Ct > 0) {
		char Buffer[64];
		snprintf(Buffer, sizeof(Buffer), "released %i fish", Fishlinks[ID].Fish_Ct);
		Print_Response(Buffer);
		Fishlinks[ID].Fish_Ct = 0;
		Data.Settings_Grid[pt(Pos.Pos)][7] = 0;
	} else {
		Print_Error(No_Fish);
	}
}

void TT_Call_Sub(Parameter Dock, Parameter Unused) {
	Print_Input();
	if (Transition.Sub_Pos.X == ktn_invalid && Transition.Sub_Pos.Y == ktn_invalid) {
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
	if (Category.Integer >= 0 && Category.Integer < ktn_categories && In_Shop) {
		Interface.Subtab = Category.Integer + 1;
		Temporary.Tutorial_Buffer = Category.Integer;
	}
}

void Shop_Item(Parameter Subcategory, Parameter Unused) {
	if (In_Shop) {
		Interface.Item = Get_Machine(Metadata.Subcontents[Interface.Subtab - ktn_categories - 1][Subcategory.Integer]);
		Temporary.Tutorial_Buffer = Subcategory.Integer;
		Cache_Blueprint();
	}
}

void Shop_Subcategory(Parameter Selection, Parameter Unused) {
	if (In_Shop) {
		Interface.Subtab = Metadata.Subcategory_Positions[Interface.Subtab - 1][Selection.Integer] + ktn_categories + 1;
		Temporary.Tutorial_Buffer = ktn_categories + Selection.Integer;
	}
}

void Shop_Subitem(Parameter Selection, Parameter Unused) {
	if (In_Shop) {
		Interface.Item = Get_Machine(Metadata.Item_Labels[Interface.Subtab - 1][Selection.Integer]);
		Cache_Blueprint();
		Cache_Price();
		Temporary.Tutorial_Buffer = Selection.Integer;
	}
}
#undef In_Shop