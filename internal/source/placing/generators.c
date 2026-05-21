#include <grid.h>

bool Place_Heat_Exchanger(Point Pos) {
	for (int C1 = 0; C1 < 4; C1++) {
		Data.Settings_Grid[pt(Pos)][C1 + 3] = 0;
	}
	for (int C1 = 0; C1 < 2; C1++) {
		Data.Settings_Grid[pt(Pos)][C1 + 7] = ktn_room_temp;
	}
	return true;
}

bool Place_Turbine_Input(Point Pos) {
	Node Nodes = { };
	Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.STI_Inputs);
	Data.Settings_Grid[pt(Interface.Tile)][3] = 0;
	Data.Settings_Grid[pt(Interface.Tile)][4] = 0;
	Data.Data_Grid[pt(Nodes.Data[0])][Fluid_Cap] = ktn_large_cap;
	Data.Settings_Grid[pt(Nodes.Data[0])][0] = F_In;
	Data.Plumbing_Grid[pt(Nodes.Data[0])] = Interface.Rotation + Left;
	ktn_free(Nodes.Data);
	return true;
}

bool Place_Turbine_Impulse(Point Pos) {
	Data.Settings_Grid[pt(Pos)][3] = 0;
	return true;
}

bool Place_Turbine_Output(Point Pos) {
	Node Nodes = { };
	Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.STO_Outputs);
	Data.Data_Grid[pt(Nodes.Data[0])][Fluid_Cap] = ktn_large_cap;
	Data.Settings_Grid[pt(Nodes.Data[0])][0] = F_Out;
	Data.Plumbing_Grid[pt(Nodes.Data[0])] = Interface.Rotation + Left;
	//do outputZ!
	ktn_free(Nodes.Data);
	return true;
}