#include <interface.h>

void Handle_None(int X, int Y) {
    switch (Interface.UI_Tab) {
    case 0:
        switch (Interface.UI_Selection) {
        case 0:
            if (Interface.Tool == Building) {
                Interface.Building = true;
            } else if (Interface.Tool == Deleting) {
                Destroy_Grid();
                Update_Grid();
            } else if (Interface.Tool == Wiring) {
                Place_Wire();
            } else if (Interface.Tool == Plumbing) {
                Place_Pipe();
            }
            break;
        case 1:
            Interface.Prompt_Identifier = P_Help;
            break;
        case 2:
            if (Interface.Save_Frames < 1) {
                Interface.Save_Frames = Interface.Frame_Rate * 2;
                Save_Data(Core.Selected_Save);
            }
            break;
        case 3:
            Interface.Prompt_Identifier = P_Catalog;
            break;
        case 4:
            if (Interface.Tool == Building) {
                Interface.Placing_Rotation = 0;
                Clear_Unconnected_Wires();
                Clear_Unconnected_Pipes();
                Cache_Blueprint();
            }
            if (Interface.Tool == LDE_INVALID) {
                Save_Data(Core.Selected_Save);
                Tutorial_Stack.clear();
                Temporary.Tutorial_Step = LDE_INVALID;
                Start_Transition(2);
                Core.Selected_Save = LDE_INVALID;
                Get_Filesizes();
                Interface.Placing_Item = 1;
                Cache_Blueprint();
            } else {
                if (Interface.Tool < 4) {
                    Interface.Tool++;
                } else {
                    Interface.Tool = 0;
                }
            }
            break;
        case 5:
            if (Interface.Tool == 0) {
                Interface.Placing_Rotation = 0;
                Clear_Unconnected_Wires();
                Clear_Unconnected_Pipes();
                Cache_Blueprint();
            }
            if (Interface.Tool > 0) {
                Interface.Tool--;
            } else {
                Interface.Tool = 4;
            }
            break;
        default:
            break;
        }
        break;
    case 1:
        switch (Interface.UI_Selection) {
        case 1:
            Start_Transition(2);
            Core.Selected_Save = LDE_INVALID;
            Get_Filesizes();
            break;
        case 2:
            Start_Transition(3);
            break;
        case 3:
            Start_Transition(4);
            break;
        case 4:
            Start_Transition(5);
            break;
        case 5:
            Core.Is_Running = false;
            break;
        default:
            break;
        }
        break;
    case 2:
        if (Interface.UI_Selection == 1) {
            Start_Transition(1);
        } else if (Interface.UI_Selection > 1 && Interface.UI_Selection < 6) {
            Core.Selected_Save = Interface.UI_Selection - 1;
            Reset_Statistics();
            Find_Effect();
            Start_Transition(0);
            Restore_Cache();
            Cache_Price();
            Cache_Blueprint();
            Cache.Wire_State = Deep_Recache;
        } else if (Interface.UI_Selection > 5 && Interface.UI_Selection < 10) {
            Core.Selected_Save = Interface.UI_Selection - 5;
            if (Load_Data(Interface.UI_Selection - 5)) {
                Save_Data(Interface.UI_Selection - 5);
                Find_Effect();
                Restore_Cache();
                Cache.Wire_State = Deep_Recache;
            }
            Start_Transition(0);
            Cache_Price();
            Cache_Blueprint();
        } else if (Interface.UI_Selection > 9 && Interface.UI_Selection < 14) {
            Clear_File("Assets/Data/Slot" + std::to_string(Interface.UI_Selection - 9));
            Get_Filesizes();
        }
        break;
    case 3:
        if (Interface.Engagement == 0 && Interface.Registering_Keybind == LDE_INVALID) {
            if (Interface.UI_Selection == 1) {
                Start_Transition(1);
            } else if (Interface.UI_Selection == 2) {
                Recalibrate_Settings();
                Temporary.Settings_Changed = true;
            } else if (Interface.UI_Selection == 3) {
                Clear_Settings();
            } else if (Interface.UI_Selection == 4) {
                Interface.Engagement = 1;
            } else if (Interface.UI_Selection == 5) {
                Settings.AA_Temporary = !Settings.AA_Temporary;
            } else if (Interface.UI_Selection > 5 && Interface.UI_Selection < 20) {
                Interface.Registering_Keybind = Interface.UI_Selection - 6;
            } else if (Interface.UI_Selection == 20) {
                Interface.Engagement = 2;
            } else if (Interface.UI_Selection == 21) {
                Interface.Engagement = 3;
            } else if (Interface.UI_Selection == 22) {
                Interface.Engagement = 4;
            } else if (Interface.UI_Selection == 23) {
                if (Save_Settings()) {
                    Temporary.Settings_Changed = false;
                }
            } else if (Interface.UI_Selection == 24) {
                Settings.VS_Temporary = !Settings.VS_Temporary;
            }
        } else {
            Interface.Engagement = 0;
        }
        break;
    case 4:
        switch (Interface.UI_Selection) {
        case 1:
            Start_Transition(1);
            break;
        case 2:
            Temporary.Log_Inversions[Changelog] = !Temporary.Log_Inversions[Changelog];
            Reload_All();
            break;
        case 3:
            Temporary.Scroll_Percent = 100;
            Interface.Log_Offset = Interface.Log_Heights[Changelog];
            break;
        case 4:
            Temporary.Scroll_Percent = 0;
            Interface.Log_Offset = 0;
            break;
        }
        break;
    case 5:
        if (Interface.Engagement == 0) {
            switch (Interface.UI_Selection) {
            case 1:
                Start_Transition(1);
                break;
            case 2:
                Interface.Engagement = 1;
                break;
            default:
                break;
            }
        } else {
            Interface.Engagement = 0;
        }
        break;
    default:
        break;
    }
}