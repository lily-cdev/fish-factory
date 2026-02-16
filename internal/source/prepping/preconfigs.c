#include <prepping.h>

void Free_Preconfig(Node Target[4]) {
	for (int C1 = 0; C1 < 4; C1++) {
		free_c(Target[C1].Data);
	}
}

void Setup_Preconfig(Node Target[4], int Depth) {
	for (int C1 = 0; C1 < 4; C1++) {
		Target[C1].Length = Depth;
		Target[C1].Data = malloc(sizeof(Point) * Depth);
	}
}

void Load_Batch(Node Target[4], Point Batch[4], int Position) {
	for (int C1 = 0; C1 < 4; C1++) {
		Target[C1].Data[Position].X = Batch[C1].X;
		Target[C1].Data[Position].Y = Batch[C1].Y;
	}
}

void Generate_Preconfigs() {
	Setup_Preconfig(Preconfigs.EP_Inputs, 1);
	Point EP_Input_Batch[4] = { { 1, 1 }, { 0, 1 }, { 1, 0 }, { 1, 1 } };
	Load_Batch(Preconfigs.EP_Inputs, EP_Input_Batch, 0);
	Point EP_Output_Batch1[4] = { { 0, 0 }, { 1, 0 }, { 0, 1 }, { 0, 0 } };
	Point EP_Output_Batch2[4] = { { 1, 0 }, { 1, 1 }, { 1, 1 }, { 0, 1 } };
	Point EP_Output_Batch3[4] = { { 2, 0 }, { 1, 2 }, { 2, 1 }, { 0, 2 } };
	Setup_Preconfig(Preconfigs.EP_Outputs, 3);
	Load_Batch(Preconfigs.EP_Outputs, EP_Output_Batch1, 0);
	Load_Batch(Preconfigs.EP_Outputs, EP_Output_Batch2, 1);
	Load_Batch(Preconfigs.EP_Outputs, EP_Output_Batch3, 2);
	Setup_Preconfig(Preconfigs.FM_Inputs, 6);
	Point FM_Input_Batch1[4] = { { 0, 0 }, { 0, 2 }, { 2, 0 }, { 0, 0 } };
	Point FM_Input_Batch2[4] = { { 0, 1 }, { 1, 2 }, { 2, 1 }, { 1, 0 } };
	Point FM_Input_Batch3[4] = { { 0, 2 }, { 2, 2 }, { 2, 2 }, { 2, 0 } };
	Point FM_Input_Batch4[4] = { { 2, 0 }, { 0, 0 }, { 0, 0 }, { 0, 2 } };
	Point FM_Input_Batch5[4] = { { 2, 1 }, { 1, 0 }, { 0, 1 }, { 1, 2 } };
	Point FM_Input_Batch6[4] = { { 2, 2 }, { 2, 0 }, { 0, 2 }, { 2, 2 } };
	Load_Batch(Preconfigs.FM_Inputs, FM_Input_Batch1, 0);
	Load_Batch(Preconfigs.FM_Inputs, FM_Input_Batch2, 1);
	Load_Batch(Preconfigs.FM_Inputs, FM_Input_Batch3, 2);
	Load_Batch(Preconfigs.FM_Inputs, FM_Input_Batch4, 3);
	Load_Batch(Preconfigs.FM_Inputs, FM_Input_Batch5, 4);
	Load_Batch(Preconfigs.FM_Inputs, FM_Input_Batch6, 5);
	Setup_Preconfig(Preconfigs.FM_Outputs, 2);
	Point FM_Output_Batch1[4] = { { 1, 0 }, { 0, 1 }, { 1, 2 }, { 2, 1 } };
	Point FM_Output_Batch2[4] = { { 1, 2 }, { 2, 1 }, { 1, 0 }, { 0, 1 } };
	Load_Batch(Preconfigs.FM_Outputs, FM_Output_Batch1, 0);
	Load_Batch(Preconfigs.FM_Outputs, FM_Output_Batch2, 1);
	Setup_Preconfig(Preconfigs.BG_Inputs, 1);
	Point BG_Input_Batch[4] = { { 0, 2 }, { 0, 0 }, { 2, 0 }, { 2, 2 } };
	Load_Batch(Preconfigs.BG_Inputs, BG_Input_Batch, 0);
	Setup_Preconfig(Preconfigs.I_Inputs, 2);
	Point I_Input_Batch1[4] = { { 0, 1 }, { 1, 0 }, { 2, 1 }, { 1, 2 } };
	Point I_Input_Batch2[4] = { { 1, 0 }, { 2, 1 }, { 1, 2 }, { 0, 1 } };
	Load_Batch(Preconfigs.I_Inputs, I_Input_Batch1, 0);
	Load_Batch(Preconfigs.I_Inputs, I_Input_Batch2, 1);
	Setup_Preconfig(Preconfigs.I_Outputs, 2);
	Point I_Output_Batch1[4] = { { 2, 1 }, { 1, 2 }, { 0, 1 }, { 1, 0 } };
	Point I_Output_Batch2[4] = { { 1, 2 }, { 0, 1 }, { 1, 0 }, { 2, 1 } };
	Load_Batch(Preconfigs.I_Outputs, I_Output_Batch1, 0);
	Load_Batch(Preconfigs.I_Outputs, I_Output_Batch2, 1);
	Setup_Preconfig(Preconfigs.D_Inputs, 1);
	Point D_Input_Batch[4] = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } };
	Load_Batch(Preconfigs.D_Inputs, D_Input_Batch, 0);
	Setup_Preconfig(Preconfigs.D_Outputs, 2);
	Point D_Output_Batch1[4] = { { 1, 0 }, { 1, 1 }, { 0, 1 }, { 0, 0 } };
	Point D_Output_Batch2[4] = { { 1, 1 }, { 0, 1 }, { 0, 0 }, { 1, 0 } };
	Load_Batch(Preconfigs.D_Outputs, D_Output_Batch1, 0);
	Load_Batch(Preconfigs.D_Outputs, D_Output_Batch2, 1);
	Setup_Preconfig(Preconfigs.STI_Inputs, 1);
	Point STI_Input_Batch[4] = { { 0, 2 }, { 0, 0 }, { 1, 0 }, { 2, 1 } };
	Load_Batch(Preconfigs.STI_Inputs, STI_Input_Batch, 0);
	Setup_Preconfig(Preconfigs.GB_Outputs, 2);
	Point GB_Output_Batch1[4] = { { 0, 2 }, { 0, 0 }, { 0, 0 }, { 2, 0 } };
	Point GB_Output_Batch2[4] = { { 1, 2 }, { 0, 1 }, { 1, 0 }, { 2, 1 } };
	Load_Batch(Preconfigs.GB_Outputs, GB_Output_Batch1, 0);
	Load_Batch(Preconfigs.GB_Outputs, GB_Output_Batch2, 1);
	Setup_Preconfig(Preconfigs.STO_Outputs, 1);
	Point STO_Output_Batch[4] = { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } };
	Load_Batch(Preconfigs.STO_Outputs, STO_Output_Batch, 0);
	Setup_Preconfig(Preconfigs.GW_Inputs, 1);
	Point GW_Input_Batch[4] = { { 0, 2 }, { 2, 0 }, { 1, 0 }, { 0, 1 } };
	Load_Batch(Preconfigs.GW_Inputs, GW_Input_Batch, 0);
	Setup_Preconfig(Preconfigs.GW_Outputs, 1);
	Point GW_Output_Batch[4] = { { 0, 0 }, { 0, 0 }, { 1, 2 }, { 2, 1 } };
	Load_Batch(Preconfigs.GW_Outputs, GW_Output_Batch, 0);
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