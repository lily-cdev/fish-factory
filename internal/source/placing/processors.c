#include <grid.h>

bool Place_Filtration_Plant(Point Pos) {
	Data.Plumbing_Grid[Pos.X][Pos.Y + 1] = Left;
	Data.Plumbing_Grid[Pos.X + 1][Pos.Y] = Right;
	Data.Plumbing_Grid[Pos.X + 1][Pos.Y + 1] = Right;
	Data.Plumbing_Grid[Pos.X + 1][Pos.Y + 2] = Right;
	Data.Data_Grid[pt(Pos)][4] = 5;
	Data.Data_Grid[Pos.X][Pos.Y + 1][Fluid_Cap] = 16;
	Data.Data_Grid[Pos.X + 1][Pos.Y][Fluid_Cap] = 12;
	for (int C1 = 1; C1 < 3; C1++) {
		Data.Data_Grid[Pos.X + 1][Pos.Y + C1][Fluid_Cap] = 4;
		Data.Settings_Grid[Pos.X + 1][Pos.Y + C1][0] = 2;
	}
	Data.Settings_Grid[Pos.X][Pos.Y + 1][0] = 1;
	Data.Settings_Grid[Pos.X + 1][Pos.Y][0] = 2;
	return true;
}

bool Place_Distillery(Point Pos) {
	Node Nodes = { };
	Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.D_Inputs);
	for (int C1 = 0; C1 < Nodes.Length; C1++) {
		Data.Settings_Grid[pt(Nodes.Data[C1])][0] = 1;
		Data.Data_Grid[pt(Nodes.Data[C1])][Fluid_Cap] = 6;
		Data.Plumbing_Grid[pt(Nodes.Data[C1])] = Interface.Rotation + Left;
	}
	Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.D_Outputs);
	for (int C1 = 0; C1 < Nodes.Length; C1++) {
		Data.Settings_Grid[pt(Nodes.Data[C1])][0] = 2;
		Data.Data_Grid[pt(Nodes.Data[C1])][Fluid_Cap] = 4;
		Data.Plumbing_Grid[pt(Nodes.Data[C1])] = (Interface.Rotation + Right == 4) ? 4 : ((Interface.Rotation + Right) & 3);
	}
	free_c(Nodes.Data);
	return true;
}

bool Place_Electrolytic_Cell(Point Pos) {
	if (evn(Interface.Rotation)) {
		for (int C1 = 0; C1 < 3; C1++) {
			Data.Data_Grid[Pos.X + C1][(int)(Interface.Rotation * 0.5f) + Pos.Y][Fluid_Cap] = 20;
			Data.Plumbing_Grid[Pos.X + C1][(int)(Interface.Rotation * 0.5f) + Pos.Y] = Interface.Rotation + Up;
			Data.Settings_Grid[Pos.X + C1][(int)(Interface.Rotation * 0.5f) + Pos.Y][0] = 2;
		}
		Data.Data_Grid[Pos.X + 1][Pos.Y - (int)(Interface.Rotation * 0.5f) + 1][Fluid_Cap] = 16;
		Data.Plumbing_Grid[Pos.X + 1][Pos.Y - (int)(Interface.Rotation * 0.5f) + 1] = Down - Interface.Rotation;
		Data.Settings_Grid[Pos.X + 1][Pos.Y - (int)(Interface.Rotation * 0.5f) + 1][0] = 1;
	} else {
		for (int C1 = 0; C1 < 3; C1++) {
			Data.Data_Grid[Pos.X - (int)((Interface.Rotation - 1) * 0.5f) + 1][Pos.Y + C1][Fluid_Cap] = 20;
			Data.Plumbing_Grid[Pos.X - (int)((Interface.Rotation - 1) * 0.5f) + 1][Pos.Y + C1] = Right - (Interface.Rotation - 1);
			Data.Settings_Grid[Pos.X - (int)((Interface.Rotation - 1) * 0.5f) + 1][Pos.Y + C1][0] = 2;
		}
		Data.Data_Grid[Pos.X + (int)((Interface.Rotation - 1) * 0.5f)][Pos.Y + 1][Fluid_Cap] = 16;
		Data.Plumbing_Grid[Pos.X + (int)((Interface.Rotation - 1) * 0.5f)][Pos.Y + 1] = (Interface.Rotation - 1) + Left;
		Data.Settings_Grid[Pos.X + (int)((Interface.Rotation - 1) * 0.5f)][Pos.Y + 1][0] = 1;
	}
	return true;
}

bool Place_Fluid_Mixer(Point Pos) {
	Node Nodes = { };
	Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.FM_Inputs);
	for (int C1 = 0; C1 < Nodes.Length; C1++) {
		//int Orientation = (int)(floorf(C1 / 3.0f) * 2.0f) + Left;
		//Orientation -= Interface.Rotation;
		//Orientation = ((Orientation + 3) & 3) + 1;
		Data.Data_Grid[pt(Nodes.Data[C1])][Fluid_Cap] = 24;
		Data.Settings_Grid[pt(Nodes.Data[C1])][0] = F_In;
		//Data.Plumbing_Grid[pt(Nodes.Data[C1])] = Orientation;
	}
	Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.FM_Outputs);
	for (int C1 = 0; C1 < Nodes.Length; C1++) {
		int Orientation = (C1 * 2) + Up;
		Orientation -= Interface.Rotation;
		Orientation = ((Orientation + 3) & 3) + 1;
		Data.Data_Grid[pt(Nodes.Data[C1])][Fluid_Cap] = 36;
		Data.Settings_Grid[pt(Nodes.Data[C1])][0] = F_Out;
		Data.Plumbing_Grid[pt(Nodes.Data[C1])] = Orientation;
	}
	free_c(Nodes.Data);
	return true;
}

bool Place_Condenser_Input(Point Pos) {
	return true;
}

bool Place_Condenser_Transferor(Point Pos) {
	return true;
}

bool Place_Condenser_Heatsink(Point Pos) {
	return true;
}

bool Place_Condenser_Output(Point Pos) {
	return true;
}