#include <grid.h>

bool Place_Algae_Bed(Point Pos) {
    bool Placed = false;
	if (evn(Interface.Rotation)) {
		if (Check_Clearance(Pos, 2, 3)) {
			Fill_Clearance(LDE_INVALID, Pos, 2, 3);
			Placed = true;
			Data.Data_Grid[pt(Pos)][5] = 52;
			Data.Data_Grid[pt(Pos)][6] = 32;
			if (Interface.Rotation == 0) {
				Data.Data_Grid[pt(Pos)][5] = 28;
				Data.Data_Grid[pt(Pos)][6] = 88;
			}
		}
	} else {
		if (Check_Clearance(Pos, 3, 2)) {
			Fill_Clearance(LDE_INVALID, Pos, 3, 2);
			Placed = true;
			Data.Data_Grid[pt(Pos)][5] = 88;
			Data.Data_Grid[pt(Pos)][6] = 52;
			if (Interface.Rotation == 1) {
				Data.Data_Grid[pt(Pos)][5] = 32;
				Data.Data_Grid[pt(Pos)][6] = 28;
			}
		}
	}
	if (Placed) {
		Node Nodes = { };
		Return_Nodes(&Nodes, Pos, Interface.Rotation, Preconfigs.GB_Outputs);//+x and +y
		for (int C1 = 0; C1 < Nodes.Length; C1++) {
			Data.Settings_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y][0] = F_Out;
			Data.Data_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y][Fluid_Cap] = 3;
			Data.Plumbing_Grid[Nodes.Data[C1].X][Nodes.Data[C1].Y] = (Interface.Rotation + Down == 4) ? 4 : ((
				Interface.Rotation + Down) & 3);
		}
		Data.Visual_Grid[pt(Pos)] = (Interface.Rotation == 0) ? 42 : Interface.Rotation + 131;
		Data.Wiring_Grid[pt(Pos)] = F_In;
		Data.Animation_Grid[pt(Pos)][0] = 0;
		Data.Animation_Grid[pt(Pos)][1] = 0;
		Data.Data_Grid[pt(Pos)][Power_Cap] = 200;
		free_c(Nodes.Data);
	} else {
		return false;
	}
	return true;
}

bool Place_Spawning_Pool(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 24;
	Data.Behavior_Grid[pt(Pos)] = 0;
	return true;
}

bool Place_Spawning_Controller(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 45;
	Data.Settings_Grid[pt(Pos)][4] = 0;
	Data.Settings_Grid[pt(Pos)][5] = 0;
	Data.Settings_Grid[pt(Pos)][6] = 0;
	Data.Settings_Grid[pt(Pos)][7] = 0;
	Data.Behavior_Grid[pt(Pos)] = 0;
	return true;
}

bool Place_Spawning_Output(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 46;
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = 50;
	Data.Plumbing_Grid[pt(Pos)] = Down;
	Data.Behavior_Grid[pt(Pos)] = 0;
	Data.Settings_Grid[pt(Pos)][0] = F_Out;
	return true;
}

bool Place_Spawning_Input(Point Pos) {
	Data.Visual_Grid[pt(Pos)] = 47;
	Data.Data_Grid[pt(Pos)][Fluid_Cap] = 12;
	Data.Plumbing_Grid[pt(Pos)] = Down;
	Data.Behavior_Grid[pt(Pos)] = 0;
	Data.Settings_Grid[pt(Pos)][0] = F_In;
	return true;
}