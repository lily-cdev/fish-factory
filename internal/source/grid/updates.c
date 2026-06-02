#include <grid.h>

void (*Cycle_Functions[])(Point Pos, const int Rotation) = {
	Cycle_Incinerator,
	Cycle_RTG,
	Cycle_Furnace,
	Cycle_Signal_Tower,
	Cycle_Geo_Well,
	Cycle_Large_Pipe,
	Cycle_HX,
	Cycle_Money_Generator,
	Cycle_Fluid_Generator,
	Cycle_Intersection,
	Cycle_Intersection,
	Cycle_Turbine_Input,
	Cycle_Power_Generator
};

const char* Cycle_Matches[13] = {
	"incinerator",
	"rtg",
	"furnace",
	"signal_tower",
	"geo_well",
	"large_pipe",
	"hx",
	"money_cheat",
	"fluid_cheat",
	"large_intersection",
	"heavy_intersection",
	"turbine_input",
	"power_cheat"
};

void Update_Machines() {
	Point Pos;
	for (Pos.X = 0; Pos.X < ktn_grid_size; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < ktn_grid_size; Pos.Y++) {
			Machine_Ptr Chosen = Visual_To_Machine(Data.Visual_Grid[pt(Pos)]);
			if (!Chosen) {
				continue;
			}
			for (int C1 = 0; C1 < Core.Recipes; C1++) {
				if (!ktn_stricmp(Chosen->Index, Metadata.Recipes[C1].Machine->Index)) {
					continue;
				}
				Point* Outputs = NULL;
				Point* Inputs = NULL;
				bool Yielded;
				switch (Metadata.Recipes[C1].Type) {
				case 0:
					Yielded = Process_IO_Recipe(Metadata.Recipes[C1], Pos, Inputs, Outputs);
					ktn_free(Outputs);
					ktn_free(Inputs);
					break;
				case 1:
					//Process_I_Recipe
					break;
				case 2:
					Yielded = Process_O_Recipe(Metadata.Recipes[C1], Pos, Outputs);
					ktn_free(Outputs);
					break;
				default:
					break;
				}
				if (Data.Settings_Grid[pt(Pos)][S_Time] > ktn_epsilon) {
					Data.Settings_Grid[pt(Pos)][S_Time]--;
					Extend_Recipe(Metadata.Recipes[C1], Pos, Outputs);
					Yielded = true;
					ktn_free(Outputs);
				}
				if (Yielded) {
					Data.Animation_Grid[pt(Pos)][0] = 1.0f;
					//play sound
				} else {
					Data.Animation_Grid[pt(Pos)][0] = 0.0f;
				}
			}
			int Rotation = Visual_To_Rotation(Data.Visual_Grid[pt(Pos)]);
			for (int C1 = 0; C1 < sizeof(Cycle_Functions) / sizeof(Cycle_Functions[0]); C1++) {
				if (ktn_stricmp(Chosen->Index, Cycle_Matches[C1])) {
					Cycle_Functions[C1](Pos, Rotation);
				}
			}
			if (Data.Visual_Grid[pt(Pos)] == 21) {
				for (int C1 = 0; C1 < 2; C1++) {
					if (Data.Data_Grid[Pos.X + C1][Pos.Y + 3][Stored_Fluids] > 0) {
						if (Data.Settings_Grid[pt(Pos)][C1 + 5] == Data.Items_Grid[Pos.X + C1][Pos.Y] ||
							Data.Settings_Grid[Pos.X][Pos.Y][C1 + 5] == ktn_invalid) {
							Data.Settings_Grid[pt(Pos)][C1 + 3] = min(Data.Settings_Grid[pt(Pos)][C1 + 3] + Data.Data_Grid[
								Pos.X + C1][Pos.Y + 3][Stored_Fluids], ktn_dock_cap);
							Data.Data_Grid[Pos.X + C1][Pos.Y + 3][Stored_Fluids] = 0;
							Data.Settings_Grid[pt(Pos)][C1 + 5] = Data.Items_Grid[Pos.X + C1][Pos.Y + 3];
						}
					}
				}
			} else if (Data.Visual_Grid[pt(Pos)] == 45) {
				if (Data.Settings_Grid[pt(Pos)][5] != 0) {
					if (Data.Settings_Grid[pt(Pos)][4] >= Data.Settings_Grid[pt(Pos)][5] * Fish_Catalog[(int)(
						Data.Settings_Grid[pt(Pos)][6])].Food_Consumption) {
						Data.Settings_Grid[pt(Pos)][4] -= Data.Settings_Grid[pt(Pos)][5] * Fish_Catalog[(int)(
							Data.Settings_Grid[pt(Pos)][6])].Food_Consumption;
					} else {
						if (Data.Settings_Grid[pt(Pos)][5] > 1) {
							Data.Settings_Grid[pt(Pos)][5]--;
						} else {
							Data.Settings_Grid[pt(Pos)][5] = 0;
							Data.Settings_Grid[pt(Pos)][7] = 0;
						}
					}
					if (Data.Settings_Grid[pt(Pos)][7] >= Fish_Catalog[(int)(Data.Settings_Grid[pt(Pos)][6])].Max_Growth) {
						Data.Settings_Grid[pt(Pos)][7] = 0;
						Point Coord = Find_Linked("spawning_output", Pos);
						Item_Ptr Fish = Get_Fish_Item((int)(Data.Settings_Grid[pt(Pos)][6]));
						Update_Item(Coord, Fish->ID, ktn_room_temp);
						Data.Data_Grid[pt(Coord)][0] = min(Data.Settings_Grid[pt(Pos)][5], Data.Data_Grid[pt(Coord)][Fluid_Cap]);
					}
					Data.Settings_Grid[pt(Pos)][7] += 1;
				}
			} else if (Data.Visual_Grid[pt(Pos)] == 47) {
				int Parent_X = (int)(Data.Settings_Grid[pt(Pos)][3]);
				int Parent_Y = (int)(Data.Settings_Grid[pt(Pos)][4]);
				float Food_Multiplier = Get_ID_Item(Data.Items_Grid[pt(Pos)])->Nutrition;
				if (Data.Data_Grid[pt(Pos)][Stored_Fluids] > 0 && Food_Multiplier > 0) {
					Data.Settings_Grid[Parent_X][Parent_Y][4] += Data.Data_Grid[pt(Pos)][Stored_Fluids] * Food_Multiplier;
					Data.Data_Grid[pt(Pos)][Stored_Fluids] = 0;
				}
			}
		}
	}
}