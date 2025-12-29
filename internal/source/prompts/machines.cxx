#include <Legacy_UI.hpp>

void Render_MSP_Controller(int X, int Y) {
	Render_Backing();
	if (Data.Settings_Grid[X][Y][3] > 3) {
		Render_Sidebuttons(Textures.MSP_Buttons, Rects.MSP_Buttons);
		Render_Slider(Interface_L.Slider_Texts[1], 1, 2, 9, Interface.Slider_Positions[1], 475, 210, 110,
			Colors.Cherry_Blossom, Colors.Pure_White, false);
		if (Interface.Engagement == 0) {
			std::vector<std::vector<std::string>> Parameters = {
				{ "tank_info" },
				{ "fish_info" },
				{ "fill_pool" },
				{ "drain_pool" }
			};
			std::vector<int> Command_Types = {
				Get_Data,
				Get_Data,
				Execute,
				Execute
			};
			Process_Commands(Command_Types, Parameters);
		} else {
			Interface_L.Terminal_Entry = Return_Command(Execute, { "set_fish", Interface_L
				.Slider_Texts[1][Interface.Slider_Positions[1]] });
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
	Render_Sidebuttons(Textures.TT_Buttons.Data[Temporary.Dialogue_Position],
		Rects.TT_Buttons.Data[Temporary.Dialogue_Position]);
	std::vector<std::vector<std::string>> Parameters;
	Parameters.resize(Metadata.TT_Parameters[Temporary.Dialogue_Position].Length);
	for (int A = 0; A < Metadata.TT_Parameters[Temporary.Dialogue_Position].Length; A++) {
		Parameters[A].resize(Metadata.TT_Parameters[Temporary.Dialogue_Position].Data[A].Length);
		for (int B = 0; B < Metadata.TT_Parameters[Temporary.Dialogue_Position].Data[A].Length; B++) {
			Parameters[A][B] = Metadata.TT_Parameters[Temporary.Dialogue_Position].Data[A].Data[B];
		}
	}
	int Index = 0;
	std::vector<int> Command_Types;
	while (Metadata.TT_Types[Temporary.Dialogue_Position][Index] != LDE_INVALID) {
		Command_Types.push_back(Metadata.TT_Types[Temporary.Dialogue_Position][Index]);
	}
	Process_Commands(Command_Types, Parameters);
	Render_Necessities("transmitter", "tower");
}

void Render_S_Dock(int X, int Y) {
	Render_Backing();
	Render_Sidebuttons(Textures.SD_Buttons, Rects.SD_Buttons);
	std::vector<std::vector<std::string>> Parameters = {
		{ "link" },
		{ "manifest" },
		{ "drain_silo", "1" },
		{ "drain_silo", "2" },
	};
	std::vector<int> Command_Types = {
		Execute,
		Get_Data,
		Execute,
		Execute
	};
	Process_Commands(Command_Types, Parameters);
	Render_Necessities("submarine_dock", "dock");
}

void Render_H_Exchanger(int X, int Y) {
	Render_Backing();
	Render_Sidebuttons(Textures.HX_Buttons, Rects.HX_Buttons);
	Render_Slider(Interface_L.Slider_Texts[13], 3, Interface_L.Valve300_Postions.size() - 1, 6,
		Interface.Slider_Positions[13], 475, 190, 110, Colors.Cherry_Blossom,
		Colors.Pure_White, false);
	Render_Slider(Interface_L.Slider_Texts[7], 2, Interface_L.Valve300_Postions.size() - 1, 7,
		Interface.Slider_Positions[7], 475, 150, 110, Colors.Cherry_Blossom,
		Colors.Pure_White, false);
	if (Interface.Engagement == 0) {
		std::vector<std::vector<std::string>> Parameters = {
			{ "diagnostics" }
		};
		std::vector<int> Command_Types = {
			Get_Data
		};
		Process_Commands(Command_Types, Parameters);
	} else if (Interface.Engagement == 2) {
		Interface_L.Terminal_Entry = Return_Command(Execute, { "set_primary_valve", std::to_string(
			static_cast<int>(Interface_L.Valve300_Postions[Interface.Slider_Positions[7]])) });
		Tick_Input(2, true);
	} else {
		Interface_L.Terminal_Entry = Return_Command(Execute, { "set_feedwater_valve", std::to_string(
			static_cast<int>(Interface_L.Valve300_Postions[Interface.Slider_Positions[13]])) });
		Tick_Input(3, true);
	}
	Render_Necessities("heat_exchanger", "exchanger");
}

void Render_MT_Input(int X, int Y) {
	Render_Backing();
	Render_Sidebuttons(Textures.MT_Buttons, Rects.MT_Buttons);
	std::vector<std::vector<std::string>> Parameters = {
		{ "diagnostics" }
	};
	std::vector<int> Command_Types = {
		Get_Data
	};
	Process_Commands(Command_Types, Parameters);
	Render_Necessities("modular_turbine", "turbine");
}