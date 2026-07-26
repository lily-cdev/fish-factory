#include <ui.h>

void Back(Parameter Unused, Parameter Unused2) {
	if (Interface.Engagement == 0 && Interface.Registering_Keybind == ktn_invalid) {
		Start_Transition(1);
	}
}

void Swap_AA(Parameter Unused, Parameter Unused2) {
	if (Interface.Engagement == 0 && Interface.Registering_Keybind == ktn_invalid) {
		Settings.AA_Temporary = !Settings.AA_Temporary;
	}
}

void Quit(Parameter Unused, Parameter Unused2) {
    Core.Is_Running = false;
}

void Tab_Saveloader(Parameter Unused, Parameter Unused2) {
	Start_Transition(2);
	Core.Selected_Save = ktn_invalid;
	Get_Filesizes();	
}

void Switch_Tab(Parameter Tab, Parameter Unused) {
	Start_Transition(Tab.Integer);
}

void Update_Settings(Parameter Unused, Parameter Unused2) {
	if (Save_Settings()) {
		Temporary.Settings_Changed = false;
	}
}

void Invert_Changelog(Parameter Unused, Parameter Unused2) {
	Temporary.Log_Inversions[Changelog] = !Temporary.Log_Inversions[Changelog];
}

void Jump_Changelog(Parameter Halfway, Parameter Unused) {
	if (Halfway.Integer == 0) {
		Temporary.Scroll_Percent = 100;
		Interface.Log_Offset = Interface.Log_Heights[Changelog];
	} else {
		Temporary.Scroll_Percent = 0;
		Interface.Log_Offset = 0;
	}
}

void Swap_VS(Parameter Unused, Parameter Unused2) {
	Settings.VS_Temporary = !Settings.VS_Temporary;
}

void Clear_Configs(Parameter Unused, Parameter Unused2) {
	if (Interface.Engagement == 0 && Interface.Registering_Keybind == ktn_invalid) {
		Clear_Settings();
	}
}

void Apply_Configs(Parameter Unused, Parameter Unused2) {
	if (Interface.Engagement == 0 && Interface.Registering_Keybind == ktn_invalid) {	
		Recalibrate_Settings();
		Temporary.Settings_Changed = true;
	}
}

void Loop_Back(Parameter Unused, Parameter Unused2) {
	Interface.Looper.Y--;
	int Max = ktn_veclen(Metadata.Subcontents[Interface.Looper.X]) - 1;
	if (Interface.Looper.Y < 0) {
		Interface.Looper.Y = Max;
	}
	Interface.Item = Get_Machine(Metadata.Subcontents[pt(Interface.Looper)]);
	Cache_Price();
	Cache_Blueprint();
}

void Loop_Forward(Parameter Unused, Parameter Unused2) {
	Interface.Looper.Y++;
	int Max = ktn_veclen(Metadata.Subcontents[Interface.Looper.X]);
	if (Interface.Looper.Y >= Max) {
		Interface.Looper.Y = 0;
	}
	Interface.Item = Get_Machine(Metadata.Subcontents[pt(Interface.Looper)]);
	Cache_Price();
	Cache_Blueprint();
}

void Set_Tool(Parameter Tool, Parameter Unused) {
	if (Tool.Integer >= T_Building && Tool.Integer <= T_Plumbing) {
		Interface.Tool = Tool.Integer;
		Update_Cursor();
	}
}

void Set_Keybind(Parameter Index, Parameter Unused) {
	if (Interface.Registering_Keybind == ktn_invalid) {
		Interface.Registering_Keybind = Index.Integer;
	}
}