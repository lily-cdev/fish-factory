#include <grid.h>

bool Place_Reinforced_Pipe(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 1;
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = LDE_REINFORCEDCAP;
	Data.Settings_Grid[pt(Pos)][0] = F_Either;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	return true;
}

bool Place_Submarine_Dock(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 21;
	Data.Plumbing_Grid[Pos.X][Pos.Y + 3] = Down;
	Data.Plumbing_Grid[Pos.X + 1][Pos.Y + 3] = Down;
	Data.Settings_Grid[Pos.X][Pos.Y + 3][0] = F_In;
	Data.Settings_Grid[Pos.X + 1][Pos.Y + 3][0] = F_In;
	Data.Data_Grid[Pos.X][Pos.Y + 3][Fluid_Cap] = 200;
	Data.Data_Grid[Pos.X + 1][Pos.Y + 3][Fluid_Cap] = 200;
	Data.Settings_Grid[pt(Pos)][3] = 0;
	Data.Settings_Grid[pt(Pos)][4] = 0;
	Data.Settings_Grid[pt(Pos)][5] = LDE_INVALID;
	Data.Settings_Grid[pt(Pos)][6] = LDE_INVALID;
	Push_Docks(Pos);
	Recache_TT_Commands();
	return true;
}

bool Place_Large_Pipe(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 71;
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = LDE_LARGECAP;
	Data.Settings_Grid[pt(Pos)][0] = F_Either;
	Data.Plumbing_Grid[pt(Pos)] = Any;
	return true;
}

bool Place_RL_Intersection(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = Interface.Rotation + ((stricmp(Interface.Item->Index, "heavy_intersection")) ? 105 : 109);
	Node Nodes = { };
	Return_Nodes(&Nodes, Pos, 0, Preconfigs.I_Inputs);
	for (int C1 = 0; C1 < 2; C1++) {
		Data.Plumbing_Grid[pt(Nodes.Data[C1])] = C1 + 1;
	}
	Return_Nodes(&Nodes, Pos, 0, Preconfigs.I_Outputs);
	for (int C1 = 0; C1 < 2; C1++) {
		Data.Plumbing_Grid[pt(Nodes.Data[C1])] = C1 + 3;
	}
	for (int C1 = 0; C1 < 2; C1++) {
		if (C1 == 1) {
			Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.I_Outputs);
		} else {
			Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.I_Inputs);
		}
		for (int C2 = 0; C2 < 2; C2++) {
			Data.Data_Grid[pt(Nodes.Data[C2])][Fluid_Cap] = (stricmp(Interface.Item->Index, "heavy_intersection")) ?
				LDE_REINFORCEDCAP : LDE_LARGECAP;
			Data.Settings_Grid[pt(Nodes.Data[C2])][0] = C1 + 1;
		}
	}
	free_c(Nodes.Data);
	return true;
}