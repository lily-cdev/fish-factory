#include <prepping.h>

void Free_Preconfig(Node Target[4]) {
	for (int C1 = 0; C1 < 4; C1++) {
		ktn_free(Target[C1].Data);
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
	Point I_Inputs[2] = { { 0, 1 }, { 1, 0 } };
	Setup_Preconfig(Preconfigs.I_Inputs, I_Inputs, (Point){ 3, 3 }, 2);
	Point I_Outputs[2] = { { 2, 1 }, { 1, 2 } };
	Setup_Preconfig(Preconfigs.I_Outputs, I_Outputs, (Point){ 3, 3 }, 2);
	Point GW_Inputs[1] = { { 0, 2 } };
	Setup_Preconfig(Preconfigs.GW_Inputs, GW_Inputs, (Point){ 2, 3 }, 1);
	Point GW_Outputs[1] = { { 0, 0 } };
	Setup_Preconfig(Preconfigs.GW_Outputs, GW_Outputs, (Point){ 2, 3 }, 1);
}

void Free_Preconfigs() {
	Free_Preconfig(Preconfigs.I_Inputs);
	Free_Preconfig(Preconfigs.I_Outputs);
	Free_Preconfig(Preconfigs.GW_Inputs);
	Free_Preconfig(Preconfigs.GW_Outputs);
}

void Return_Nodes(Node* Yield, Point Pos, const int Rotation, Node Preconfig[4]) {
	ktn_free(Yield->Data);
	Yield->Length = Preconfig[Rotation].Length;
	Yield->Data = malloc(sizeof(Point) * Yield->Length);
	for (int C1 = 0; C1 < Yield->Length; C1++) {
		Yield->Data[C1].X = Preconfig[Rotation].Data[C1].X + Pos.X;
		Yield->Data[C1].Y = Preconfig[Rotation].Data[C1].Y + Pos.Y;
	}
}