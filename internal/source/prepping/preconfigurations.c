#include <prepping.h>

void Free_Node(Node Target) {
	free_c(Target.Data);
}

void Free_Preconfiguration(Node Target[4]) {
	for (int Counter = 0; Counter < 4; Counter++) {
		Free_Node(Target[Counter]);
	}
}

void Setup_Preconfiguration(Node Target[4], int Depth) {
	for (int Counter = 0; Counter < 4; Counter++) {
		Target[Counter].Length = Depth;
		Target[Counter].Data = malloc(sizeof(Point) * Depth);
	}
}

void Load_Batch(Node Target[4], Point Batch[4], int Position) {
	for (int Counter = 0; Counter < 4; Counter++) {
		Target[Counter].Data[Position].X = Batch[Counter].X;
		Target[Counter].Data[Position].Y = Batch[Counter].Y;
	}
}

void Generate_Preconfigurations() {
	Setup_Preconfiguration(Preconfigurations.EP_Inputs, 1);
	Point EP_Input_Batch[4] = { { 1, 1 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };
	Load_Batch(Preconfigurations.EP_Inputs, EP_Input_Batch, 0);
	Point EP_Output_Batch1[4] = { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 0, 0 } };
	Point EP_Output_Batch2[4] = { { 1, 0 }, { 1, 1 }, { 1, 1 }, { 0, 1 } };
	Point EP_Output_Batch3[4] = { { 2, 0 }, { 1, 2 }, { 2, 1 }, { 0, 2 } };
	Setup_Preconfiguration(Preconfigurations.EP_Outputs, 3);
	Load_Batch(Preconfigurations.EP_Outputs, EP_Output_Batch1, 0);
	Load_Batch(Preconfigurations.EP_Outputs, EP_Output_Batch2, 1);
	Load_Batch(Preconfigurations.EP_Outputs, EP_Output_Batch3, 2);
	Setup_Preconfiguration(Preconfigurations.FM_Inputs, 6);
	Point FM_Input_Batch1[4] = { { 0, 0 }, { 0, 2 }, { 2, 0 }, { 0, 0 } };
	Point FM_Input_Batch2[4] = { { 0, 1 }, { 1, 2 }, { 2, 1 }, { 1, 0 } };
	Point FM_Input_Batch3[4] = { { 0, 2 }, { 2, 2 }, { 2, 2 }, { 2, 0 } };
	Point FM_Input_Batch4[4] = { { 2, 0 }, { 0, 0 }, { 0, 0 }, { 0, 2 } };
	Point FM_Input_Batch5[4] = { { 2, 1 }, { 1, 0 }, { 0, 1 }, { 1, 2 } };
	Point FM_Input_Batch6[4] = { { 2, 2 }, { 2, 0 }, { 0, 2 }, { 2, 2 } };
	Load_Batch(Preconfigurations.FM_Inputs, FM_Input_Batch1, 0);
	Load_Batch(Preconfigurations.FM_Inputs, FM_Input_Batch2, 1);
	Load_Batch(Preconfigurations.FM_Inputs, FM_Input_Batch3, 2);
	Load_Batch(Preconfigurations.FM_Inputs, FM_Input_Batch4, 3);
	Load_Batch(Preconfigurations.FM_Inputs, FM_Input_Batch5, 4);
	Load_Batch(Preconfigurations.FM_Inputs, FM_Input_Batch6, 5);
	Setup_Preconfiguration(Preconfigurations.FM_Outputs, 2);
	Point FM_Output_Batch1[4] = { { 1, 0 }, { 0, 1 }, { 1, 2 }, { 2, 1 } };
	Point FM_Output_Batch2[4] = { { 1, 2 }, { 2, 1 }, { 1, 0 }, { 0, 1 } };
	Load_Batch(Preconfigurations.FM_Outputs, FM_Output_Batch1, 0);
	Load_Batch(Preconfigurations.FM_Outputs, FM_Output_Batch2, 1);
	Setup_Preconfiguration(Preconfigurations.BG_Inputs, 1);
	Point BG_Input_Batch[4] = { { 0, 2 }, { 0, 0 }, { 2, 0 }, { 2, 2 } };
	Load_Batch(Preconfigurations.BG_Inputs, BG_Input_Batch, 0);
	Setup_Preconfiguration(Preconfigurations.I_Inputs, 2);
	Point I_Input_Batch1[4] = { { 0, 1 }, { 1, 0 }, { 2, 1 }, { 1, 2 } };
	Point I_Input_Batch2[4] = { { 1, 0 }, { 2, 1 }, { 1, 2 }, { 0, 1 } };
	Load_Batch(Preconfigurations.I_Inputs, I_Input_Batch1, 0);
	Load_Batch(Preconfigurations.I_Inputs, I_Input_Batch2, 1);
	Setup_Preconfiguration(Preconfigurations.I_Outputs, 2);
	Point I_Output_Batch1[4] = { { 2, 1 }, { 1, 2 }, { 0, 1 }, { 1, 0 } };
	Point I_Output_Batch2[4] = { { 1, 2 }, { 0, 1 }, { 1, 0 }, { 2, 1 } };
	Load_Batch(Preconfigurations.I_Outputs, I_Output_Batch1, 0);
	Load_Batch(Preconfigurations.I_Outputs, I_Output_Batch2, 1);
	Setup_Preconfiguration(Preconfigurations.D_Inputs, 1);
	Point D_Input_Batch[4] = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } };
	Load_Batch(Preconfigurations.D_Inputs, D_Input_Batch, 0);
	Setup_Preconfiguration(Preconfigurations.D_Outputs, 2);
	Point D_Output_Batch1[4] = { { 1, 0 }, { 1, 1 }, { 0, 1 }, { 0, 0 } };
	Point D_Output_Batch2[4] = { { 1, 1 }, { 0, 1 }, { 0, 0 }, { 1, 0 } };
	Load_Batch(Preconfigurations.D_Outputs, D_Output_Batch1, 0);
	Load_Batch(Preconfigurations.D_Outputs, D_Output_Batch2, 1);
	Setup_Preconfiguration(Preconfigurations.STI_Inputs, 1);
	Point STI_Input_Batch[4] = { { 0, 2 }, { 0, 0 }, { 1, 0 }, { 2, 1 } };
	Load_Batch(Preconfigurations.STI_Inputs, STI_Input_Batch, 0);
	Setup_Preconfiguration(Preconfigurations.GB_Outputs, 2);
	Point GB_Output_Batch1[4] = { { 0, 2 }, { 0, 0 }, { 0, 0 }, { 2, 0 } };
	Point GB_Output_Batch2[4] = { { 1, 2 }, { 0, 1 }, { 1, 0 }, { 2, 1 } };
	Load_Batch(Preconfigurations.GB_Outputs, GB_Output_Batch1, 0);
	Load_Batch(Preconfigurations.GB_Outputs, GB_Output_Batch2, 1);
	Setup_Preconfiguration(Preconfigurations.STO_Outputs, 1);
	Point STO_Output_Batch[4] = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } };
	Load_Batch(Preconfigurations.STO_Outputs, STO_Output_Batch, 0);
	Setup_Preconfiguration(Preconfigurations.GW_Inputs, 1);
	Point GW_Input_Batch[4] = { { 0, 2 }, { 2, 0 }, { 1, 0 }, { 0, 1 } };
	Load_Batch(Preconfigurations.GW_Inputs, GW_Input_Batch, 0);
	Setup_Preconfiguration(Preconfigurations.GW_Outputs, 1);
	Point GW_Output_Batch[4] = { { 0, 0 }, { 0, 0 }, { 1, 2 }, { 2, 1 } };
	Load_Batch(Preconfigurations.GW_Outputs, GW_Output_Batch, 0);
}

void Free_Preconfigurations() {
	Free_Preconfiguration(Preconfigurations.EP_Inputs);
	Free_Preconfiguration(Preconfigurations.EP_Outputs);
	Free_Preconfiguration(Preconfigurations.FM_Inputs);
	Free_Preconfiguration(Preconfigurations.FM_Outputs);
	Free_Preconfiguration(Preconfigurations.BG_Inputs);
	Free_Preconfiguration(Preconfigurations.I_Inputs);
	Free_Preconfiguration(Preconfigurations.I_Outputs);
	Free_Preconfiguration(Preconfigurations.D_Inputs);
	Free_Preconfiguration(Preconfigurations.D_Outputs);
	Free_Preconfiguration(Preconfigurations.STI_Inputs);
	Free_Preconfiguration(Preconfigurations.GB_Outputs);
	Free_Preconfiguration(Preconfigurations.STO_Outputs);
	Free_Preconfiguration(Preconfigurations.GW_Inputs);
	Free_Preconfiguration(Preconfigurations.GW_Outputs);
}

void Return_Nodes(Node Yield, const int Column, const int Row, const int Rotation, Node Preconfiguration[4]) {
	Free_Node(Yield);
	Yield.Length = Preconfiguration[Rotation].Length;
	Yield.Data = malloc(sizeof(Point) * Yield.Length);
	for (int Counter = 0; Counter < Yield.Length; Counter++) {
		Yield.Data[Counter].X = Preconfiguration[Rotation].Data[Counter].X;
		Yield.Data[Counter].Y = Preconfiguration[Rotation].Data[Counter].Y;
	}
}