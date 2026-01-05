#include <ui.h>

void Render_MSP_Controller(int X, int Y) {
	Render_Backing();
	if (Data.Settings_Grid[X][Y][3] > 3) {
		Render_Sidebuttons(Textures.MSP_Buttons, Rects.MSP_Buttons);
		Render_Slider(Interface.Slider_Texts[1], 1, 2, 9, &Interface.Slider_Positions[1], 475, 210, 110,
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
			Interface_L.Terminal_Entry = Return_Command(Execute, { "set_fish", Interface
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
	Render_Sidebuttons(Textures.TT_Buttons, Rects.TT_Buttons);
	std::vector<int> Command_Types = { };
	std::vector<std::vector<std::string>> Parameters = { };
	for (int Counter = 0; Counter < Temporary.Docks.Length; Counter++) {
		Command_Types.push_back(Execute);
		Parameters.push_back({ "SEND_DOCK_" + std::to_string(Counter + 1) });
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
	Render_Slider(Interface.Slider_Texts[13], 3, LDE_VALVE300LENGTH - 1, 6, &Interface.Slider_Positions[13],
		475, 190, 110, Colors.Cherry_Blossom, Colors.Pure_White, false);
	Render_Slider(Interface.Slider_Texts[7], 2, LDE_VALVE300LENGTH - 1, 7, &Interface.Slider_Positions[7],
		475, 150, 110, Colors.Cherry_Blossom, Colors.Pure_White, false);
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
			static_cast<int>(Interface.Valve300_Postions[Interface.Slider_Positions[7]])) });
		Tick_Input(2, true);
	} else {
		Interface_L.Terminal_Entry = Return_Command(Execute, { "set_feedwater_valve", std::to_string(
			static_cast<int>(Interface.Valve300_Postions[Interface.Slider_Positions[13]])) });
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