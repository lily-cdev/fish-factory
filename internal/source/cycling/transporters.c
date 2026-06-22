#include <grid.h>

void Cycle_Large_Pipe(Point Pos, const int Rotation) {
	if (Get_ID_Item(Data.Items_Grid[pt(Pos)])->Danger > Harmless) {
		//if hazard then go boom
	}
}

void Cycle_Intersection(Point Pos, const int Rotation) {
	//check4hazard!
	Machine_Ptr Machine = Get_Machine("heavy_intersection");
	for (int C1 = 0; C1 < 2; C1++) {
		Point Input = Get_Transformed(Machine, Machine->Inputs[C1], Pos);
		Point Output = Get_Transformed(Machine, Machine->Outputs[C1], Pos);
		int OX = Output.X;
		int OY = Output.Y;
		int IX = Input.X;
		int IY = Input.Y;
		float Difference = Data.Data_Grid[OX][OY][Fluid_Cap] - Data.Data_Grid[OX][OY][Stored_Fluids];
		Difference = min(Difference, Data.Data_Grid[IX][IY][Stored_Fluids]);
		if (Difference > 0 && (Data.Items_Grid[IX][IY] == Data.Items_Grid[OX][OY] || Data.Items_Grid[OX][OY] == ktn_invalid)) {
			Data.Data_Grid[OX][OY][Stored_Fluids] += Difference;
			Data.Data_Grid[IX][IY][Stored_Fluids] -= Difference;
			Update_Item(Output, Data.Items_Grid[IX][IY], Data.Temperature_Grid[IX][IY]);
		}
	}
}