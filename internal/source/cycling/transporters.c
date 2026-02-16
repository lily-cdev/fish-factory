#include <grid.h>

void Cycle_Large_Pipe(const int X, const int Y, const int Rotation) {
	if (Get_Item(X, Y).Hazard > Harmless) {
		//if hazard then go boom
	}
}

void Cycle_Intersection(const int X, const int Y, const int Rotation) {
	//check4hazard!
	Node Inputs = { };
	Node Outputs = { };
	Return_Nodes(&Inputs, X, Y, Visual_To_Rotation(Data.Visual_Grid[X][Y]), Preconfigs.I_Inputs);
	Return_Nodes(&Outputs, X, Y, Visual_To_Rotation(Data.Visual_Grid[X][Y]), Preconfigs.I_Outputs);
	for (int C1 = 0; C1 < 2; C1++) {
		int OX = Outputs.Data[C1].X;
		int OY = Outputs.Data[C1].Y;
		int IX = Inputs.Data[C1].X;
		int IY = Inputs.Data[C1].Y;
		float Difference = Data.Data_Grid[OX][OY][Fluid_Cap] - Data.Data_Grid[OX][OY][Stored_Fluids];
		Difference = min(Difference, Data.Data_Grid[IX][IY][Stored_Fluids]);
		if (Difference > 0 && (Data.Items_Grid[IX][IY] == Data.Items_Grid[OX][OY] || Data.Items_Grid[OX][OY] ==
			LDE_INVALID)) {
			Data.Data_Grid[OX][OY][Stored_Fluids] += Difference;
			Data.Data_Grid[IX][IY][Stored_Fluids] -= Difference;
			Update_Item(Outputs.Data[C1].X, OY, Data.Items_Grid[IX][IY], Data.Temperature_Grid[IX][IY]);
		}
	}
	free_c(Inputs.Data);
	free_c(Outputs.Data);
}