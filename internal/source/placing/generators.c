#include <grid.h>

bool Place_Bio_Generator(Point Pos) {
	Node Nodes = { };
	Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.BG_Inputs);
	Data.Data_Grid[pt(Nodes.Data[0])][1] = 4;
	Data.Settings_Grid[pt(Nodes.Data[0])][0] = 1;
	int Orientation = Interface.Rotation + Down;
	Orientation = ((Orientation + 3) & 3) + 1;
	Data.Plumbing_Grid[pt(Nodes.Data[0])] = Orientation;
	free_c(Nodes.Data);
	return true;
}

bool Place_Geo_Well(Point Pos) {
	if (evn(Interface.Rotation)) {
		for (int C1 = 0; C1 < 2; C1++) {
			if (Interface.Rotation == C1 * 2) {
				Data.Data_Grid[Pos.X + C1][Pos.Y][Fluid_Cap] = 10;
				Data.Data_Grid[Pos.X + C1][Pos.Y + 2][Fluid_Cap] = 10;
				Data.Settings_Grid[Pos.X + C1][Pos.Y][0] = 2 - C1;
				Data.Settings_Grid[Pos.X + C1][Pos.Y + 2][0] = C1 + 1;
				Data.Plumbing_Grid[Pos.X + C1][Pos.Y] = Up;
				Data.Plumbing_Grid[Pos.X + C1][Pos.Y + 2] = Down;
				Data.Data_Grid[pt(Pos)][5] = fabsf((C1 * 80.0f) - 28.0f);
			}
		}
	} else {
		for (int C1 = 0; C1 < 2; C1++) {
			if (Interface.Rotation == (C1 * 2) + 1) {
				Data.Data_Grid[Pos.X][Pos.Y + C1][Fluid_Cap] = 10;
				Data.Data_Grid[Pos.X + 2][Pos.Y + C1][Fluid_Cap] = 10;
				Data.Settings_Grid[Pos.X][Pos.Y + C1][0] = 2 - C1;
				Data.Settings_Grid[Pos.X + 2][Pos.Y + C1][0] = C1 + 1;
				Data.Plumbing_Grid[Pos.X][Pos.Y + C1] = Left;
				Data.Plumbing_Grid[Pos.X + 2][Pos.Y + C1] = Right;
				Data.Data_Grid[pt(Pos)][6] = fabsf((C1 * 80.0f) - 28.0f);
			}
		}
	}
	return true;
}

bool Place_Heat_Exchanger(Point Pos) {
	if (evn(Interface.Rotation)) {
		for (int C1 = 0; C1 < 2; C1++) {
			for (int C2 = 0; C2 < 2; C2++) {
				Data.Plumbing_Grid[(C2 * 3) + Pos.X][(C1 * 2) + Pos.Y] = (C1 * 2) + Up;
				Data.Data_Grid[(C2 * 3) + Pos.X][(C1 * 2) + Pos.Y][Fluid_Cap] = 300;
				Data.Settings_Grid[(C2 * 3) + Pos.X][Pos.Y][0] = 2 - (Interface.Rotation * 0.5f);
				Data.Settings_Grid[(C2 * 3) + Pos.X][Pos.Y + 2][0] = 1 + (Interface.Rotation * 0.5f);
			}
		}
	} else {
		for (int C1 = 0; C1 < 2; C1++) {
			for (int C2 = 0; C2 < 2; C2++) {
				Data.Plumbing_Grid[(C1 * 2) + Pos.X][Pos.Y + (C2 * 3)] = (C1 * 2) + Left;
				Data.Data_Grid[(C1 * 2) + Pos.X][Pos.Y + (C2 * 3)][Fluid_Cap] = 300;
				Data.Settings_Grid[Pos.X][(C2 * 3) + Pos.Y][0] = (Interface.Rotation * 0.5) + 1;
				Data.Settings_Grid[Pos.X + 2][(C2 * 3) + Pos.Y][0] = 2 - (Interface.Rotation * 0.5);
			}
		}
	}
	for (int C1 = 0; C1 < 4; C1++) {
		Data.Settings_Grid[pt(Pos)][C1 + 3] = 0;
	}
	for (int C1 = 0; C1 < 2; C1++) {
		Data.Settings_Grid[pt(Pos)][C1 + 7] = LDE_ROOMTEMP;
	}
	return true;
}

bool Place_Turbine_Input(Point Pos) {
	Node Nodes = { };
	Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.STI_Inputs);
	Data.Settings_Grid[pt(Interface.Tile)][3] = 0;
	Data.Settings_Grid[pt(Interface.Tile)][4] = 0;
	Data.Data_Grid[pt(Nodes.Data[0])][Fluid_Cap] = LDE_LARGECAP;
	Data.Settings_Grid[pt(Nodes.Data[0])][0] = F_In;
	Data.Plumbing_Grid[pt(Nodes.Data[0])] = Interface.Rotation + Left;
	free_c(Nodes.Data);
	return true;
}

bool Place_Turbine_Impulse(Point Pos) {
	Data.Settings_Grid[pt(Pos)][3] = 0;
	return true;
}

bool Place_Turbine_Output(Point Pos) {
	Node Nodes = { };
	Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.STO_Outputs);
	Data.Data_Grid[pt(Nodes.Data[0])][Fluid_Cap] = LDE_LARGECAP;
	Data.Settings_Grid[pt(Nodes.Data[0])][0] = F_Out;
	Data.Plumbing_Grid[pt(Nodes.Data[0])] = Interface.Rotation + Left;
	//do outputZ!
	free_c(Nodes.Data);
	return true;
}