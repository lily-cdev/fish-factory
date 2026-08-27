#include <grid.h>

void Cycle_Large_Pipe(Point Pos, const int Rotation) {
	if (Get_Item(Data.Items_Grid[pt(Pos)])->Danger > Harmless) {
		//if hazard then go boom
	}
}

void Cycle_Intersection(Point Pos, const int Rotation) {
	//check4hazard!
	for (int C1 = 0; C1 < 2; C1++) {
		Point Input = Get_Transformed(Get_Machine("heavy_intersection")->Inputs[C1], Pos);
		Point Output = Get_Transformed(Get_Machine("heavy_intersection")->Outputs[C1], Pos);
		int OX = Output.X;
		int OY = Output.Y;
		int IX = Input.X;
		int IY = Input.Y;
		float Difference = Data.Data_Grid[OX][OY][Fluid_Cap] - Data.Data_Grid[OX][OY][Stored_Fluids];
		Difference = fminf(Difference, Data.Data_Grid[IX][IY][Stored_Fluids]);
		if (Difference > 0 && (Data.Items_Grid[IX][IY] == Data.Items_Grid[OX][OY] || ktn_stricmp(Data.Items_Grid[OX][OY], Metadata.Null_Item.Index))) {
			Data.Data_Grid[OX][OY][Stored_Fluids] += Difference;
			Data.Data_Grid[IX][IY][Stored_Fluids] -= Difference;
			Update_Item(Output, Data.Items_Grid[IX][IY], Data.Temperature_Grid[IX][IY]);
		}
	}
}