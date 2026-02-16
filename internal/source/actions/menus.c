#include <interface.h>

void Handle_Help(int X, int Y) {
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
			switch (Interface.UI_Selection) {
			case 2:
				memset(Tutorial_Stack, 0, sizeof(Tutorial_Stack));
				Temporary.Tutorial_Step = LDE_INVALID;
				break;
			case 3:
				{
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
					memcpy(Tutorial_Stack, Template, sizeof(Template));
				}
				Temporary.Tutorial_Size = (Point){ 320, 240 };
				Temporary.Tutorial_Offset = (Point){ 0, 200 };
				break;
			case 4:
				{
					Tutorial_Step Template[256] = {
						{ T_Key, 4, 0, "", 0, { NULLPOINT }, false, "enable the build tool" },
						{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "open the catalog" },
						{ T_Button, 0, 4, "Extraction", 0, { NULLPOINT }, false, "open the \"Extraction\" category" },
						{ T_Button, 0, 3, "Ram Pump", 0, { NULLPOINT }, false, "select the \"Ram Pump\" item" },
						{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "close the catalog" },
						{ 2, 0, 0, "", 17, { { 4, 5 }, { 3, 6 }, { 4, 7 }, NULLPOINT }, false,
							"pump in water for the Filtration Plant" },
						{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "open the catalog" },
						{ T_Button, 0, 6, "Processing", 0, { NULLPOINT }, false, "open the \"Processing\" category" },
						{ T_Button, 0, 3, "Filtration Plant", 0, { NULLPOINT }, false,
							"select the \"Filtration Plant\" item" },
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
						{ 2, 0, 0, "", 0, { { 4, 6 }, { 7, 6 }, { 8, 6 }, NULLPOINT }, true,
							"transport fluids between machines" },
						{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "open the catalog" },
						{ T_Button, 0, 3, "Logistics", 0, { NULLPOINT }, false, "open the \"Logistics\" category" },
						{ T_Button, 0, 5, "Cable Node", 0, { NULLPOINT }, false, "select the \"Cable Node\" item" },
						{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "close the catalog" },
						{ 2, 0, 0, "", 63, { { 8, 7 }, NULLPOINT }, false, "transport power between machines" },
						{ T_Key, 8, 0, "", 0, { NULLPOINT }, false, "enable the plumbing tool" },
						{ 3, 0, 0, "", 0, { { 4, 7 }, { 4, 6 }, { 4, 5 }, { 4, 6 }, { 3, 6 }, { 4, 6 }, { 6, 6 }, { 7, 6 },
							{ 7, 6 }, { 8, 6 }, { 4, 6 }, { 5, 6 }, { 6, 5 }, { 7, 5 }, { 6, 7 }, { 7, 7 }, { 8, 6 }, { 8, 5 },
							NULLPOINT }, false, "allow fluids to flow" },
						{ T_Key, 7, 0, "", 0, { NULLPOINT }, false, "enable the wiring tool" },
						{ 4, 0, 0, "", 0, { { 8, 7 }, { 3, 6 }, { 8, 7 }, { 4, 5 }, { 8, 7 }, { 4, 7 }, { 8, 7 }, { 5, 5 },
							NULLPOINT }, false, "allow power to be distributed" },
						{ T_Key, 4, 0, "", 0, { NULLPOINT }, false, "enable the build tool" },
						{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "open the catalog" },
						{ T_Button, 0, 7, "Generation", 0, { NULLPOINT }, false, "open the \"Generation\" category" },
						{ 1, 0, 3, "Piezoelectric Generator", 0, { NULLPOINT }, false,
							"select the \"Piezoelectric Generator\" item" },
						{ T_Key, 9, 0, "", 0, { NULLPOINT }, false, "close the catalog" },
						{ 2, 0, 0, "", 19, { { 3, 3 }, { 4, 3 }, { 5, 3 }, { 6, 3 }, { 7, 3 }, { 3, 4 }, { 4, 4 }, { 5, 4 },
							{ 6, 4 }, { 7, 4 }, NULLPOINT }, false, "generate a temporary supply of power" },
						{ T_Key, 7, 0, "", 0, { NULLPOINT }, false, "enable the wiring tool" },
						{ 4, 0, 0, "", 0, { { 3, 3 }, { 8, 7 }, { 4, 3 }, { 8, 7 }, { 5, 3 }, { 8, 7 }, { 6, 3 }, { 8, 7 },
							{ 7, 3 }, { 8, 7 }, { 3, 4 }, { 8, 7 }, { 4, 4 }, { 8, 7 }, { 5, 4 }, { 8, 7 }, { 6, 4 }, { 8, 7 },
							{ 7, 4 }, { 8, 7 }, NULLPOINT }, false, "jumpstart the setup" },
						{ 5, 0, 60, "", 0, { NULLPOINT }, false, "allow the first cycle to begin" },
						{ T_Key, 5, 0, "", 0, { NULLPOINT }, false, "enable the delete tool" },
						{ 2, 0, 0, "", 0, { { 3, 3 }, { 4, 3 }, { 5, 3 }, { 6, 3 }, { 7, 3 }, { 3, 4 }, { 4, 4 }, { 5, 4 },
							{ 6, 4 }, { 7, 4 }, NULLPOINT }, false, "remove the jumpstarting equipment" },
						{ T_Key, 7, 0, "", 0, { NULLPOINT }, false, "enable the wiring tool" },
						{ 4, 0, 0, "", 0, { { 8, 3 }, { 8, 7 }, NULLPOINT }, false, "make the setup self-sustaining" },
						{ T_Key, 7, 0, "", 0, { NULLPOINT }, false, "disable the wiring tool" },
						{ T_Terminator }
					};
					memcpy(Tutorial_Stack, Template, sizeof(Template));
				}
				Temporary.Tutorial_Size = (Point){ 320, 200 };
				Temporary.Tutorial_Offset = (Point){ 0, 0 };
				break;
			case 5:
				Temporary.Tutorial_Step = LDE_INVALID;
				//here
				break;
			default:
				break;
			}
			break;
		case 2:
			switch (Interface.UI_Selection) {
			case 2:
				Interface.Item = Money_Generator + 1;
				break;
			case 3:
				Interface.Item = Fluid_Generator + 1;
				break;
			default:
				break;
			}
			if (Interface.UI_Selection > 1 && Interface.UI_Selection < 4) {
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

void Handle_Shop(int X, int Y) {
	if (Interface.Subtab == 0) {
		if (Interface.UI_Selection > 2 && Interface.UI_Selection < 11) {
			Interface.Subtab = Interface.UI_Selection - 2;
		}
	} else if (Interface.Subtab > 0) {
		if (Interface.Subtab < 9) {
			if (Interface.UI_Selection > 2) {
				if (Interface.UI_Selection > intlen(Metadata.Subcategory_Positions[Interface.Subtab - 1]) + 2) {
					Interface.Item = Metadata.Item_Labels[Interface.Subtab - 1][Interface.UI_Selection - intlen(
						Metadata.Subcategory_Positions[Interface.Subtab - 1]) - 3] + 1;
					Cache_Blueprint();
				} else {
					Interface.Subtab = Metadata.Subcategory_Positions[Interface.Subtab - 1][Interface.UI_Selection - 3] + 9;
				}
			}
		} else if (Interface.UI_Selection > 2) {
			Interface.Item = Metadata.Subcontents[Interface.Subtab - 9][Interface.UI_Selection - 3] + 1;
			Cache_Blueprint();
		}
	}
}

void Handle_Daily_Report(int X, int Y) {
	if (Interface.UI_Selection == 1) {
		Close_Prompt();
		Data.Time = 0;
		if (Data.Day < 6) {
			Data.Day++;
		} else {
			Data.Day = 0;
		}
	}
}

void Handle_Catalog(int X, int Y) {
	if (Interface.UI_Selection > 3) {
		Interface.Subprompt_Identifier = Interface.UI_Selection - 3;
	}
}