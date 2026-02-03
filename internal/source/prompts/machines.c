#include <ui.h>

void Render_MSP_Controller(int X, int Y) {
	Render_Backing();
	if (Data.Settings_Grid[X][Y][3] > 3) {
		Render_Sidebuttons(&Textures.MSP_Buttons, &Rects.MSP_Buttons);
		Render_Slider(Interface.Slider_Texts[1], 1, 2, 9, &Interface.Slider_Positions[1], 475, 210, 110,
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
					strcpy(Buffers.Parameters[C1][C2], Parameters[C1][C2]);
				}
			}
			int Command_Types[5] = {
				Get_Data,
				Get_Data,
				Execute,
				Execute,
				LDE_TERMINATOR
			};
			memcpy(Buffers.Commands, Command_Types, sizeof(Command_Types));
			Process_Commands();
		} else {
			const char* Parameters[4] = {
				"set_fish",
				Interface.Slider_Texts[1][Interface.Slider_Positions[1]],
				NULLSTRING
			};
			Return_Command(Execute, Parameters, Interface.Terminal_Entry);
			Tick_Input(1, true);
		}
		Render_Necessities("modular_spawning_pool", "pool");
	} else if (Data.Settings_Grid[X][Y][3] == -6) {
		Print_Fatal_Error(Too_Many_Inputs);
	} else if (Data.Settings_Grid[X][Y][3] == -5) {
		Print_Fatal_Error(Missing_Input);
	} else if (Data.Settings_Grid[X][Y][3] == -4) {
		Print_Fatal_Error(Too_Many_Outputs);
	} else if (Data.Settings_Grid[X][Y][3] == -3) {
		Print_Fatal_Error(Missing_Output);
	} else if (Data.Settings_Grid[X][Y][3] == -2) {
		Print_Fatal_Error(Too_Many_Controllers);
	} else if (Data.Settings_Grid[X][Y][3] < 4) {
		Print_Fatal_Error(Missing_Pool);					
	}
}

void Render_T_Tower(int X, int Y) {
	Render_Backing();
	Render_Sidebuttons(&Textures.TT_Buttons, &Rects.TT_Buttons);
	int Limiter = min(Temporary.Docks.Length, LDE_CMDMAX - 1);
	for (int C1 = 0; C1 < Limiter; C1++) {
		Buffers.Commands[C1] = Execute;
		char Buffer[32];
		snprintf(Buffer, sizeof(Buffer), "SEND_DOCK_%i", C1 + 1);
		strcpy(Buffers.Parameters[C1][0], Buffer);
		strcpy(Buffers.Parameters[C1][1], NULLSTRING);
	}
	Buffers.Commands[Limiter] = LDE_TERMINATOR;
	Buffers.Parameters[Limiter][0] = NULLSTRING;
	Process_Commands();
	Render_Necessities("transmitter", "tower");
}

void Render_S_Dock(int X, int Y) {
	Render_Backing();
	Render_Sidebuttons(&Textures.SD_Buttons, &Rects.SD_Buttons);
	char* Parameters[5][4] = {
		{ "link", NULLSTRING },
		{ "manifest", NULLSTRING },
		{ "drain_silo", "1", NULLSTRING },
		{ "drain_silo", "2", NULLSTRING },
		{ NULLSTRING }
	};
	for (int C1 = 0; C1 < 5; C1++) {
		for (int C2 = 0; C2 < veclen(Parameters[C2]) + 1; C2++) {
			strcpy(Buffers.Parameters[C1][C2], Parameters[C1][C2]);
		}
	}
	int Command_Types[5] = {
		Execute,
		Get_Data,
		Execute,
		Execute,
		LDE_TERMINATOR
	};
	memcpy(Buffers.Commands, Command_Types, sizeof(Command_Types));
	Process_Commands();
	Render_Necessities("submarine_dock", "dock");
}

void Render_H_Exchanger(int X, int Y) {
	Render_Backing();
	Render_Sidebuttons(&Textures.HX_Buttons, &Rects.HX_Buttons);
	Render_Slider(Interface.Slider_Texts[13], 3, LDE_VALVE300LENGTH - 1, 6, &Interface.Slider_Positions[13],
		475, 190, 110, Colors.Cherry_Blossom, Colors.Pure_White, false);
	Render_Slider(Interface.Slider_Texts[7], 2, LDE_VALVE300LENGTH - 1, 7, &Interface.Slider_Positions[7],
		475, 150, 110, Colors.Cherry_Blossom, Colors.Pure_White, false);
	if (Interface.Engagement == 0) {
		strcpy(Buffers.Parameters[0][0], "diagnostics");
		strcpy(Buffers.Parameters[0][1], NULLSTRING);
		Buffers.Commands[0] = Get_Data;
		Buffers.Commands[1] = LDE_TERMINATOR;
		Process_Commands();
	} else if (Interface.Engagement == 2) {
		char Buffer[64];
		snprintf(Buffer, sizeof(Buffer), "%i", (int)Interface.Valve300_Postions[Interface.Slider_Positions[7]]);
		const char* Subparameters[4] = {
			"set_primary_valve",
			Buffer,
			NULLSTRING
		};
		Return_Command(Execute, Subparameters, Interface.Terminal_Entry);
		Tick_Input(2, true);
	} else {
		char Buffer[64];
		snprintf(Buffer, sizeof(Buffer), "%i", (int)Interface.Valve300_Postions[Interface.Slider_Positions[13]]);
		const char* Subparameters[4] = {
			"set_feedwater_valve",
			Buffer,
			NULLSTRING
		};
		Return_Command(Execute, Subparameters, Interface.Terminal_Entry);
		Tick_Input(3, true);
	}
	Render_Necessities("heat_exchanger", "exchanger");
}

void Render_MT_Input(int X, int Y) {
	Render_Backing();
	Render_Sidebuttons(&Textures.MT_Buttons, &Rects.MT_Buttons);
	strcpy(Buffers.Parameters[0][0], "diagnostics");
	strcpy(Buffers.Parameters[0][1], NULLSTRING);
	Buffers.Commands[0] = Get_Data;
	Buffers.Commands[1] = LDE_TERMINATOR;
	Process_Commands();
	Render_Necessities("modular_turbine", "turbine");
}