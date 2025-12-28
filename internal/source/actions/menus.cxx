#include <Legacy_Interface.hpp>

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
                Tutorial_Stack.clear();
                Temporary.Tutorial_Step = LDE_INVALID;
                break;
            case 3:
                Tutorial_Stack = {
                    Tutorial_Step{ 0, 4, 0, "", 0, { }, false, "enable the build tool" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
                    Tutorial_Step{ 1, 0, 10, "Special", 0, { }, false, "open the \"Special\" category" },
                    Tutorial_Step{ 1, 0, 3, "Command Platform", 0, { }, false,
                        "select the \"Command Platform\" item" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
                    Tutorial_Step{ 6, 4, 200, "", 0, { }, false, "put the placement site into view" },
                    Tutorial_Step{ 2, 0, 0, "", 43, { { 3, 8 } }, false, "allow time to progress" },
                    Tutorial_Step{ 0, 4, 0, "", 0, { }, false, "disable the build tool" }
                };
                Temporary.Tutorial_Size = { 320, 240 };
                Temporary.Tutorial_Offset = { 0, 200 };
                break;
            case 4:
                Tutorial_Stack = {
                    Tutorial_Step{ 0, 4, 0, "", 0, { }, false, "enable the build tool" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
                    Tutorial_Step{ 1, 0, 4, "Extraction", 0, { }, false, "open the \"Extraction\" category" },
                    Tutorial_Step{ 1, 0, 3, "Ram Pump", 0, { }, false, "select the \"Ram Pump\" item" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
                    Tutorial_Step{ 2, 0, 0, "", 17, { { 4, 5 }, { 3, 6 }, { 4, 7 } }, false,
                        "pump in water for the Filtration Plant" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
                    Tutorial_Step{ 1, 0, 6, "Processing", 0, { }, false, "open the \"Processing\" category" },
                    Tutorial_Step{ 1, 0, 3, "Filtration Plant", 0, { }, false,
                        "select the \"Filtration Plant\" item" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
                    Tutorial_Step{ 2, 0, 0, "", 22, { { 5, 5 } }, false, "filter water into fuel" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
                    Tutorial_Step{ 1, 0, 9, "Other", 0, { }, false, "open the \"Other\" category" },
                    Tutorial_Step{ 1, 0, 3, "Incinerator", 0, { }, false, "select the \"Incinerator\" item" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
                    Tutorial_Step{ 2, 0, 0, "", 18, { { 7, 5 }, { 7, 7 } }, false,
                        "dispose of unwanted byproducts" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
                    Tutorial_Step{ 1, 0, 7, "Generation", 0, { }, false, "open the \"Generation\" category" },
                    Tutorial_Step{ 1, 0, 4, "Compact Firebox", 0, { }, false,
                        "select the \"Compact Firebox\" item" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
                    Tutorial_Step{ 2, 0, 0, "", 23, { { 8, 3 } }, false, "burn fuel for electricity" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
                    Tutorial_Step{ 1, 0, 3, "Logistics", 0, { }, false, "open the \"Logistics\" category" },
                    Tutorial_Step{ 1, 0, 3, "Reinforced Pipe", 0, { }, false,
                        "select the \"Reinforced Pipe\" item" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
                    Tutorial_Step{ 2, 0, 0, "", 0, { { 4, 6 }, { 7, 6 }, { 8, 6 } }, true,
                        "transport fluids between machines" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
                    Tutorial_Step{ 1, 0, 3, "Logistics", 0, { }, false, "open the \"Logistics\" category" },
                    Tutorial_Step{ 1, 0, 5, "Cable Node", 0, { }, false, "select the \"Cable Node\" item" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
                    Tutorial_Step{ 2, 0, 0, "", 63, { { 8, 7 } }, false, "transport power between machines" },
                    Tutorial_Step{ 0, 8, 0, "", 0, { }, false, "enable the plumbing tool" },
                    Tutorial_Step{ 3, 0, 0, "", 0, { { 4, 7 }, { 4, 6 }, { 4, 5 }, { 4, 6 }, { 3, 6 }, { 4, 6 },
                        { 6, 6 }, { 7, 6 }, { 7, 6 }, { 8, 6 }, { 4, 6 }, { 5, 6 }, { 6, 5 }, { 7, 5 }, { 6, 7 },
                        { 7, 7 }, { 8, 6 }, { 8, 5 } }, false, "allow fluids to flow" },
                    Tutorial_Step{ 0, 7, 0, "", 0, { }, false, "enable the wiring tool" },
                    Tutorial_Step{ 4, 0, 0, "", 0, { { 8, 7 }, { 3, 6 }, { 8, 7 }, { 4, 5 }, { 8, 7 }, { 4, 7 },
                        { 8, 7 }, { 5, 5 } }, false, "allow power to be distributed" },
                    Tutorial_Step{ 0, 4, 0, "", 0, { }, false, "enable the build tool" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
                    Tutorial_Step{ 1, 0, 7, "Generation", 0, { }, false,
                        "open the \"Generation\" category" },
                    Tutorial_Step{ 1, 0, 3, "Piezoelectric Generator", 0, { }, false,
                        "select the \"Piezoelectric Generator\" item" },
                    Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
                    Tutorial_Step{ 2, 0, 0, "", 19, { { 3, 3 }, { 4, 3 },
                        { 5, 3 }, { 6, 3 }, { 7, 3 }, { 3, 4 },
                        { 4, 4 }, { 5, 4 }, { 6, 4 }, { 7, 4 } }, false,
                        "generate a temporary supply of power" },
                    Tutorial_Step{ 0, 7, 0, "", 0, { }, false, "enable the wiring tool" },
                    Tutorial_Step{ 4, 0, 0, "", 0, { { 3, 3 }, { 8, 7 }, { 4, 3 }, { 8, 7 }, { 5, 3 }, { 8, 7 },
                    { 6, 3 }, { 8, 7 }, { 7, 3 }, { 8, 7 }, { 3, 4 }, { 8, 7 }, { 4, 4 }, { 8, 7 }, { 5, 4 },
                    { 8, 7 }, { 6, 4 }, { 8, 7 }, { 7, 4 }, { 8, 7 } }, false, "jumpstart the setup" },
                    Tutorial_Step{ 5, 0, 60, "", 0, { }, false, "allow the first cycle to begin" },
                    Tutorial_Step{ 0, 5, 0, "", 0, { }, false, "enable the delete tool" },
                    Tutorial_Step{ 2, 0, 0, "", 0, { { 3, 3 }, { 4, 3 }, { 5, 3 }, { 6, 3 }, { 7, 3 }, { 3, 4 },
                    { 4, 4 }, { 5, 4 }, { 6, 4 }, { 7, 4 } }, false, "remove the jumpstarting equipment" },
                    Tutorial_Step{ 0, 7, 0, "", 0, { }, false, "enable the wiring tool" },
                    Tutorial_Step{ 4, 0, 0, "", 0, { { 8, 3 }, { 8, 7 } }, false,
                        "make the setup self-sustaining" },
                    Tutorial_Step{ 0, 7, 0, "", 0, { }, false, "disable the wiring tool" }
                };
                Temporary.Tutorial_Size = { 320, 200 };
                Temporary.Tutorial_Offset = { 0, 0 };
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
                Interface.Placing_Item = Money_Generator + 1;
                break;
            case 3:
                Interface.Placing_Item = Fluid_Generator + 1;
                break;
            default:
                break;
            }
            if (Interface.UI_Selection > 1 && Interface.UI_Selection < 4) {
                Interface.Tool = Building;
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
                if (Interface.UI_Selection > Metadata_L.Subcategory_Positions[
                    Interface.Subtab - 1].size() + 2) {
                    Interface.Placing_Item = Metadata_L.Item_Labels[
                        Interface.Subtab - 1][Interface.UI_Selection -
                        Metadata_L.Subcategory_Positions[
                        Interface.Subtab - 1].size() - 3] + 1;
                    Cache_Blueprint();
                } else {
                    Interface.Subtab = Metadata_L.Subcategory_Positions[
                        Interface.Subtab - 1][Interface.UI_Selection - 3] + 9;
                }
            }
        } else if (Interface.UI_Selection > 2) {
            Interface.Placing_Item = Metadata_L.Subcontents[
                Interface.Subtab - 9][Interface.UI_Selection - 3] + 1;
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