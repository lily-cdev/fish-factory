#include <prepping.h>

void Free_Preconfig(Node Target[4]) {
	for (int C1 = 0; C1 < 4; C1++) {
		free_c(Target[C1].Data);
	}
}

void Setup_Preconfig(Node Target[4], Point Data[], Point Bounds, int Depth) {
	for (int C1 = 0; C1 < 4; C1++) {
		Target[C1].Length = Depth;
		Target[C1].Data = malloc(sizeof(Point) * Depth);
	}
	for (int C1 = 0; C1 < Depth; C1++) {
		Point Input = Data[C1];
		Point Size = Bounds;
		for (int C2 = 0; C2 < 4; C2++) {
			Target[C2].Data[C1] = Input;
			Point Carrier = Input;
			Input.X = (Size.Y - 1) - Carrier.Y;
			Input.Y = Carrier.X;
			int Subcarrier = Size.X;
			Size.X = Size.Y;
			Size.Y = Subcarrier;
		}
	}
}

void Generate_Preconfigs() {
	Point EP_Inputs[1] = { { 1, 1 } };
	Setup_Preconfig(Preconfigs.EP_Inputs, EP_Inputs, (Point){ 3, 2 }, 1);
	Point EP_Outputs[3] = { { 0, 0 }, { 1, 0 }, { 2, 0 } };
	Setup_Preconfig(Preconfigs.EP_Outputs, EP_Outputs, (Point){ 3, 2 }, 3);
	Point FM_Inputs[6] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 2, 0 }, { 2, 1 }, { 2, 2 } };
	Setup_Preconfig(Preconfigs.FM_Inputs, FM_Inputs, (Point){ 3, 3 }, 6);
	Point FM_Outputs[2] = { { 1, 0 }, { 1, 2 } };
	Setup_Preconfig(Preconfigs.FM_Outputs, FM_Outputs, (Point){ 3, 3 }, 2);
	Point BG_Inputs[1] = { { 0, 2 } };
	Setup_Preconfig(Preconfigs.BG_Inputs, BG_Inputs, (Point){ 3, 3 }, 1);
	Point I_Inputs[2] = { { 0, 1 }, { 1, 0 } };
	Setup_Preconfig(Preconfigs.I_Inputs, I_Inputs, (Point){ 3, 3 }, 2);
	Point I_Outputs[2] = { { 2, 1 }, { 1, 2 } };
	Setup_Preconfig(Preconfigs.I_Outputs, I_Outputs, (Point){ 3, 3 }, 2);
	Point D_Inputs[1] = { { 0, 0 } };
	Setup_Preconfig(Preconfigs.D_Inputs, D_Inputs, (Point){ 2, 2 }, 1);
	Point D_Outputs[2] = { { 1, 0 }, { 1, 1 } };
	Setup_Preconfig(Preconfigs.D_Outputs, D_Outputs, (Point){ 2, 2 }, 2);
	Point STI_Inputs[1] = { { 0, 2 } };
	Setup_Preconfig(Preconfigs.STI_Inputs, STI_Inputs, (Point){ 2, 3 }, 1);
	Point GB_Outputs[2] = { { 0, 2 }, { 1, 2 } };
	Setup_Preconfig(Preconfigs.GB_Outputs, GB_Outputs, (Point){ 2, 3 }, 2);
	Point STO_Outputs[1] = { { 0, 0 } };
	Setup_Preconfig(Preconfigs.STO_Outputs, STO_Outputs, (Point){ 2, 2 }, 1);
	Point GW_Inputs[1] = { { 0, 2 } };
	Setup_Preconfig(Preconfigs.GW_Inputs, GW_Inputs, (Point){ 2, 3 }, 1);
	Point GW_Outputs[1] = { { 0, 0 } };
	Setup_Preconfig(Preconfigs.GW_Outputs, GW_Outputs, (Point){ 2, 3 }, 1);
	Point RP_Outputs[1] = { 0, 0 };
	Setup_Preconfig(Preconfigs.RP_Outputs, RP_Outputs, (Point){ 1, 1 }, 1);
}

void Free_Preconfigs() {
	Free_Preconfig(Preconfigs.EP_Inputs);
	Free_Preconfig(Preconfigs.EP_Outputs);
	Free_Preconfig(Preconfigs.FM_Inputs);
	Free_Preconfig(Preconfigs.FM_Outputs);
	Free_Preconfig(Preconfigs.BG_Inputs);
	Free_Preconfig(Preconfigs.I_Inputs);
	Free_Preconfig(Preconfigs.I_Outputs);
	Free_Preconfig(Preconfigs.D_Inputs);
	Free_Preconfig(Preconfigs.D_Outputs);
	Free_Preconfig(Preconfigs.STI_Inputs);
	Free_Preconfig(Preconfigs.GB_Outputs);
	Free_Preconfig(Preconfigs.STO_Outputs);
	Free_Preconfig(Preconfigs.GW_Inputs);
	Free_Preconfig(Preconfigs.GW_Outputs);
	Free_Preconfig(Preconfigs.RP_Outputs);
}

void Return_Nodes(Node* Yield, const int Column, const int Row, const int Rotation, Node Preconfig[4]) {
	free_c(Yield->Data);
	Yield->Length = Preconfig[Rotation].Length;
	Yield->Data = malloc(sizeof(Point) * Yield->Length);
	for (int C1 = 0; C1 < Yield->Length; C1++) {
		Yield->Data[C1].X = Preconfig[Rotation].Data[C1].X + Column;
		Yield->Data[C1].Y = Preconfig[Rotation].Data[C1].Y + Row;
	}
}