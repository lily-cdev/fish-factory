#include <grid.h>

void (*Cycle_Functions[LDE_MACHINES])(const int X, const int Y, const int Rotation) = {
	NULL, NULL, Cycle_Incinerator, Cycle_RTG, NULL, NULL, NULL, Cycle_Bio_Gen, NULL, Cycle_Distillery, Cycle_Algae_Bed,
	NULL, NULL, NULL, NULL, NULL, Cycle_Electrolytic_Cell, Cycle_Fluid_Mixer, Cycle_Signal_Tower, NULL, NULL, NULL,
	Cycle_Geo_Well, Cycle_Large_Pipe, Cycle_HX, NULL, NULL, NULL, Cycle_Money_Generator, Cycle_Fluid_Generator,
	Cycle_Intersection, Cycle_Intersection, NULL, NULL, NULL, NULL, NULL, Cycle_Turbine_Input, NULL, NULL,
	Cycle_Power_Generator
};

void Update_Machines() {
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			int Rotation = Visual_To_Rotation(Data.Visual_Grid[X][Y]);
			if (Data.Visual_Grid[X][Y] > 0) {
				if (Data.Settings_Grid[X][Y][S_Time] > 0) {
					Data.Settings_Grid[X][Y][S_Time]--;
					switch (Visual_To_ID(Data.Visual_Grid[X][Y])) {
					case Distillery:
						Extend_Recipe(Preset_IO_Recipes.D_Water, X, Y, Preconfigs.D_Outputs);
						break;
					case Electrolytic_Cell:
						if (Data.Settings_Grid[X][Y][2] == 1) {
							Extend_Recipe(Preset_IO_Recipes.EP_Water, X, Y, Preconfigs.EP_Outputs);
						} else if (Data.Settings_Grid[X][Y][2] == 2) {
							Extend_Recipe(Preset_IO_Recipes.EP_Saltwater, X, Y, Preconfigs.EP_Outputs);
						} else {
							Extend_Recipe(Preset_IO_Recipes.EP_Salt, X, Y, Preconfigs.EP_Outputs);
						}
						break;
					case Algae_Bed:
						if (Extend_Recipe(Preset_O_Recipes.GB_Algae, X, Y, Preconfigs.GB_Outputs)) {
							Data.Animation_Grid[X][Y][1] = 0;
						}
						break;
					default:
						break;
					}
				}
			}
			int Chosen = Visual_To_ID(Data.Visual_Grid[X][Y]);
			if (Chosen >= 0 && Cycle_Functions[Chosen] != NULL) {
				Cycle_Functions[Chosen](X, Y, Rotation);
			}
			if (Data.Visual_Grid[X][Y] == 21) {
				for (int C1 = 0; C1 < 2; C1++) {
					if (Data.Data_Grid[X + C1][Y + 3][Stored_Fluids] > 0) {
						if (Data.Settings_Grid[X][Y][C1 + 5] == Get_Item(X + C1, Y + 3).Identifier || Data.Settings_Grid[X][
							Y][C1 + 5] == LDE_INVALID) {
							Data.Settings_Grid[X][Y][C1 + 3] = min(Data.Settings_Grid[X][Y][C1 + 3] + Data.Data_Grid[X +
								C1][Y + 3][Stored_Fluids], LDE_DOCKCAPACITY);
							Data.Data_Grid[X + C1][Y + 3][Stored_Fluids] = 0;
							Data.Settings_Grid[X][Y][C1 + 5] = Get_Item(X + C1, Y + 3).Identifier;
						}
					}
				}
			} else if (Data.Visual_Grid[X][Y] == 22) {
				Node tmp1 = { };tmp1.Data = (Point*)malloc(sizeof(Point));
				tmp1.Length = 1;tmp1.Data[0].X = X;
				tmp1.Data[0].Y = Y + 1;
				Node tmp2 = { };tmp2.Data = (Point*)malloc(sizeof(Point)*3);
				tmp2.Length = 3;tmp2.Data[0].X = X + 1;
				tmp2.Data[0].Y = Y;tmp2.Data[1].X = X + 1;
				tmp2.Data[1].Y = Y + 1;tmp2.Data[2].X = X + 1;
				tmp2.Data[2].Y = Y + 2;
				bool Running1 = Process_IO_Recipe(Preset_IO_Recipes.FP_Saltwater, X, Y, tmp1, tmp2);
				bool Running2 = Process_IO_Recipe(Preset_IO_Recipes.FP_Biopaste, X, Y, tmp1, tmp2);
				Data.Animation_Grid[X][Y][0] = 0;
				Data.Animation_Grid[X][Y][1] = 0;
				if (Running1 || Running2) {
					Play_Sound(Filtration1, false);
				} else if (Data.Animation_Grid[X][Y][0] == 0) {
					Data.Animation_Grid[X][Y][0] = LDE_INVALID;
					Data.Animation_Grid[X][Y][1] = 0;
				}
				free_c(tmp1.Data);
				free_c(tmp2.Data);
			} else if (Data.Visual_Grid[X][Y] == 45) {
				if (Data.Settings_Grid[X][Y][5] != 0) {
					if (Data.Settings_Grid[X][Y][4] >= Data.Settings_Grid[X][Y][5] * Fish_Catalog[(int)(Data.Settings_Grid[
						X][Y][6])].Food_Consumption) {
						Data.Settings_Grid[X][Y][4] -= Data.Settings_Grid[X][Y][5] * Fish_Catalog[(int)(Data.Settings_Grid[
							X][Y][6])].Food_Consumption;
					} else {
						if (Data.Settings_Grid[X][Y][5] > 1) {
							Data.Settings_Grid[X][Y][5]--;
						} else {
							Data.Settings_Grid[X][Y][5] = 0;
							Data.Settings_Grid[X][Y][7] = 0;
						}
					}
					if (Data.Settings_Grid[X][Y][7] >= Fish_Catalog[(int)(Data.Settings_Grid[X][Y][6])].Max_Growth) {
						Data.Settings_Grid[X][Y][7] = 0;
						Point Coordinate = Find_Linked(14, X, Y);
						Item_Stack Fish = Get_Fish_Item((int)(Data.Settings_Grid[X][Y][6]));
						Update_Item(Coordinate.X, Coordinate.Y, Fish.Identifier, LDE_ROOMTEMP);
						Data.Data_Grid[Coordinate.X][Coordinate.Y][0] = min(Data.Settings_Grid[X][Y][5], Data.Data_Grid[
							Coordinate.X][Coordinate.Y][Fluid_Cap]);
					}
					Data.Settings_Grid[X][Y][7] += 1;
				}
			} else if (Data.Visual_Grid[X][Y] == 47) {
				int Parent_X = (int)(Data.Settings_Grid[X][Y][3]);
				int Parent_Y = (int)(Data.Settings_Grid[X][Y][4]);
				float Food_Multiplier = 0;
				if (Data.Items_Grid[X][Y] == Preset_Items.Marine_Snow.Identifier) {
					Food_Multiplier = 0.35;
				} else if (Data.Items_Grid[X][Y] == Preset_Items.Raw_Algae.Identifier) {
					Food_Multiplier = 0.5;
				} else if (Data.Items_Grid[X][Y] == Preset_Items.Biopaste.Identifier) {
					Food_Multiplier = 0.65;
				}
				if (Data.Data_Grid[X][Y][Stored_Fluids] > 0 && Food_Multiplier > 0) {
					Data.Settings_Grid[Parent_X][Parent_Y][4] += Data.Data_Grid[X][Y][Stored_Fluids] * Food_Multiplier;
					Data.Data_Grid[X][Y][Stored_Fluids] = 0;
				}
			}
		}
	}
}