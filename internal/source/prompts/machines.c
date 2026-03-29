#include <ui.h>

void Render_MSP_Controller(Point Pos) {
	Render_Backing();
	if (Data.Settings_Grid[pt(Pos)][3] > 3) {
		UI_Link Links[LDE_PERMBUTTONS + 4] = {
			(UI_Link){ MSP_TInfo, .Param.Pos = Pos },
			(UI_Link){ MSP_FInfo, .Param.Pos = Pos },
			(UI_Link){ MSP_Fill, .Param.Pos = Pos },
			(UI_Link){ MSP_Empty, .Param.Pos = Pos }
		};
		Render_Sidebuttons(&Textures.MSP_Buttons, &Rects.MSP_Buttons, Links);
		Render_Slider(Interface.Slider_Texts[1], 1, 2, 9, &Interface.Slider_Positions[1], (Point){ 475, 210 }, 110,
			Colors.Cherry_Blossom, Colors.Pure_White, false);
		if (Interface.Engagement == 0) {
			char* Parameters[5][4] = {
				{ "tank_info", NULLSTRING },
				{ "fish_info", NULLSTRING },
				{ "fill_pool", NULLSTRING },
				{ "drain_pool", NULLSTRING },
				{ NULLSTRING }
			};
			for (int C1 = 0; C1 < 5; C1++) {
				for (int C2 = 0; C2 < veclen(Parameters[C2]) + 1; C2++) {
					strncpy(Buffers.Parameters[C1][C2], Parameters[C1][C2], sizeof(Buffers.Parameters[C1][C2]));
				}
			}
			int Command_Types[5] = {
				Get_Data,
				Get_Data,
				Execute,
				Execute,
				LDE_TERMINATOR
			};
			memcpy_c(Buffers.Commands, Command_Types, sizeof(Command_Types));
			Process_Commands();
		} else {
			char Parameters[4][LDE_PARAMMAX] = { "set_fish" };
			strcpy(Parameters[1], Interface.Slider_Texts[1][Interface.Slider_Positions[1]]);
			strcpy(Parameters[2], NULLSTRING);
			Return_Command(Execute, 4, Parameters);
			Tick_Input(1, true);
		}
		Render_Necessities("modular_spawning_pool", "pool");
	} else if (Data.Settings_Grid[pt(Pos)][3] == -6) {
		Print_Fatal_Error(Too_Many_Inputs);
	} else if (Data.Settings_Grid[pt(Pos)][3] == -5) {
		Print_Fatal_Error(Missing_Input);
	} else if (Data.Settings_Grid[pt(Pos)][3] == -4) {
		Print_Fatal_Error(Too_Many_Outputs);
	} else if (Data.Settings_Grid[pt(Pos)][3] == -3) {
		Print_Fatal_Error(Missing_Output);
	} else if (Data.Settings_Grid[pt(Pos)][3] == -2) {
		Print_Fatal_Error(Too_Many_Controllers);
	} else if (Data.Settings_Grid[pt(Pos)][3] < 4) {
		Print_Fatal_Error(Missing_Pool);					
	}
}

void Render_T_Tower(Point Pos) {
	Render_Backing();
	UI_Link* Links = malloc(sizeof(UI_Link) * (LDE_PERMBUTTONS + Temporary.Docks.Length));
	for (int C1 = 0; C1 < Temporary.Docks.Length; C1++) {
		Links[C1] = (UI_Link){ TT_Call_Sub, .Param.Integer = C1 };
	}
	Render_Sidebuttons(&Textures.TT_Buttons, &Rects.TT_Buttons, Links);
	int Limiter = min(Temporary.Docks.Length, LDE_CMDMAX - 1);
	for (int C1 = 0; C1 < Limiter; C1++) {
		Buffers.Commands[C1] = Execute;
		char Buffer[32];
		snprintf(Buffer, sizeof(Buffer), "SEND_DOCK_%i", C1 + 1);
		strncpy(Buffers.Parameters[C1][0], Buffer, sizeof(Buffers.Parameters[C1][0]));
		strncpy(Buffers.Parameters[C1][1], NULLSTRING, sizeof(Buffers.Parameters[C1][1]));
	}
	Buffers.Commands[Limiter] = LDE_TERMINATOR;
	strncpy(Buffers.Parameters[Limiter][0], NULLSTRING, sizeof(Buffers.Parameters[Limiter][0]));
	Process_Commands();
	Render_Necessities("transmitter", "tower");
	free_c(Links);
}

void Render_S_Dock(Point Pos) {
	Render_Backing();
	UI_Link Links[LDE_PERMBUTTONS + 4] = {
		(UI_Link){ SD_Link, .Param.Pos = Pos },
		(UI_Link){ SD_Manifest, .Param.Pos = Pos },
		(UI_Link){ SD_Drain, .Param.Pos = Pos, .Param2.Integer = 0 },
		(UI_Link){ SD_Drain, .Param.Pos = Pos, .Param2.Integer = 1 }
	};
	Render_Sidebuttons(&Textures.SD_Buttons, &Rects.SD_Buttons, Links);
	char* Parameters[5][4] = {
		{ "link", NULLSTRING },
		{ "manifest", NULLSTRING },
		{ "drain_silo", "1", NULLSTRING },
		{ "drain_silo", "2", NULLSTRING },
		{ NULLSTRING }
	};
	for (int C1 = 0; C1 < 5; C1++) {
		for (int C2 = 0; C2 < veclen(Parameters[C1]) + 1; C2++) {
			strncpy(Buffers.Parameters[C1][C2], Parameters[C1][C2], sizeof(Buffers.Parameters[C1][C2]));
		}
	}
	int Command_Types[5] = {
		Execute,
		Get_Data,
		Execute,
		Execute,
		LDE_TERMINATOR
	};
	memcpy_c(Buffers.Commands, Command_Types, sizeof(Command_Types));
	Process_Commands();
	Render_Necessities("submarine_dock", "dock");
}

void Render_H_Exchanger(Point Pos) {
	Render_Backing();
	UI_Link Links[LDE_PERMBUTTONS + 1] = {
		(UI_Link){ HX_Diagnostics, .Param.Pos = Pos }
	};
	Render_Sidebuttons(&Textures.HX_Buttons, &Rects.HX_Buttons, Links);
	Render_Slider(Interface.Slider_Texts[13], 3, LDE_VALVE300LENGTH - 1, 6, &Interface.Slider_Positions[13],
		(Point){ 475, 190 }, 110, Colors.Cherry_Blossom, Colors.Pure_White, false);
	Render_Slider(Interface.Slider_Texts[7], 2, LDE_VALVE300LENGTH - 1, 7, &Interface.Slider_Positions[7],
		(Point){ 475, 150 }, 110, Colors.Cherry_Blossom, Colors.Pure_White, false);
	if (Interface.Engagement == 0) {
		strncpy(Buffers.Parameters[0][0], "diagnostics", sizeof(Buffers.Parameters[0][0]));
		strncpy(Buffers.Parameters[0][1], NULLSTRING, sizeof(Buffers.Parameters[0][1]));
		Buffers.Commands[0] = Get_Data;
		Buffers.Commands[1] = LDE_TERMINATOR;
		Process_Commands();
	} else if (Interface.Engagement == 2) {
		char Buffer[64];
		snprintf(Buffer, sizeof(Buffer), "%i", (int)Interface.Valve300_Postions[Interface.Slider_Positions[7]]);
		char Subparameters[4][LDE_PARAMMAX] = { "set_primary_valve" };
		strcpy(Subparameters[1], Buffer);
		strcpy(Subparameters[1], NULLSTRING);
		Return_Command(Execute, 4, Subparameters);
		Tick_Input(2, true);
	} else {
		char Buffer[64];
		snprintf(Buffer, sizeof(Buffer), "%i", (int)Interface.Valve300_Postions[Interface.Slider_Positions[13]]);
		char Subparameters[4][LDE_PARAMMAX] = { "set_feedwater_valve" };
		strcpy(Subparameters[1], Buffer);
		strcpy(Subparameters[1], NULLSTRING);
		Return_Command(Execute, 4, Subparameters);
		Tick_Input(3, true);
	}
	Render_Necessities("heat_exchanger", "exchanger");
}

void Render_MT_Input(Point Pos) {
	Render_Backing();
	UI_Link Links[LDE_PERMBUTTONS + 1] = {
		(UI_Link){ MT_Diagnostics, .Param.Pos = Pos }
	};
	Render_Sidebuttons(&Textures.MT_Buttons, &Rects.MT_Buttons, Links);
	strncpy(Buffers.Parameters[0][0], "diagnostics", sizeof(Buffers.Parameters[0][0]));
	strncpy(Buffers.Parameters[0][1], NULLSTRING, sizeof(Buffers.Parameters[0][1]));
	Buffers.Commands[0] = Get_Data;
	Buffers.Commands[1] = LDE_TERMINATOR;
	Process_Commands();
	Render_Necessities("modular_turbine", "turbine");
}