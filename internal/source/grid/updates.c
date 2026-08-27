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
			bool Yield = false;
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
				if (Data.Settings_Grid[pt(Pos)][S_Time] > ktn_epsilon && ktn_stricmp(Data.Processing_Grid[pt(Pos)], Metadata.Recipes[C1].Index)) {
					Data.Settings_Grid[pt(Pos)][S_Time]--;
					Extend_Recipe(Metadata.Recipes[C1], Pos, Outputs);
					Yielded = true;
					ktn_free(Outputs);
				}
				if (Yielded) {
					Yield = true;
				}
			}
			if (Yield) {
				Data.Animation_Grid[pt(Pos)][0] = 1.0f;
				if (Visual_To_Machine(Data.Visual_Grid[pt(Pos)])->Has_Audio) {
					ma_sound* Carrier = &Visual_To_Machine(Data.Visual_Grid[pt(Pos)])->Run;
					ma_result Result = ma_sound_start(Carrier);
					if (Result != MA_SUCCESS) {
						printf("%d\n", Result);//TMP
					}
				}
				//play sound
			} else {
				Data.Animation_Grid[pt(Pos)][0] = 0.0f;
				//stopsound
			}
			int Rotation = Visual_To_Rotation(Data.Visual_Grid[pt(Pos)]);
			for (int C1 = 0; C1 < sizeof(Cycle_Functions) / sizeof(Cycle_Functions[0]); C1++) {
				if (ktn_stricmp(Chosen->Index, Cycle_Matches[C1])) {
					Cycle_Functions[C1](Pos, Rotation);
				}
			}
			if (ktn_stricmp(Visual_To_Machine(Data.Visual_Grid[pt(Pos)])->Index, "sub_dock")) {
				for (int C1 = 0; C1 < 2; C1++) {
					if (Data.Settings_Grid[pt(Pos)][C1 + 3] > ktn_dock_cap - ktn_epsilon && Get_Perk("adv_automation")->Owned) {
						if (Transition.Sub_Pos.X == ktn_invalid && Transition.Sub_Pos.Y == ktn_invalid) {
							Transition.Sub_Pos = Pos;
							Transition.Sub_Phase = 0;
							Transition.Sub_Frames = 0;
							Transition.Sub_Offset = 3000;
							Transition.Sub_Vertical = 105;
						}
						if (Transition.Sub_Pos.X == Pos.X && Transition.Sub_Pos.Y == Pos.Y && Transition.Sub_Phase == 2) {
							Sell(Pos, false);
						}
					}
					if (Data.Data_Grid[Pos.X + C1][Pos.Y + 3][Stored_Fluids] > 0) {
						if ((int)(Data.Settings_Grid[pt(Pos)][C1 + 5]) == Get_Item(Data.Items_Grid[Pos.X + C1][Pos.Y + 3])->ID || Data.Settings_Grid[pt(Pos)][
							C1 + 5] == ktn_invalid) {
							Data.Settings_Grid[pt(Pos)][C1 + 3] = fminf(Data.Settings_Grid[pt(Pos)][C1 + 3] + Data.Data_Grid[Pos.X + C1][Pos.Y + 3][Stored_Fluids],
								ktn_dock_cap);
							Data.Data_Grid[Pos.X + C1][Pos.Y + 3][Stored_Fluids] = 0;
							Data.Settings_Grid[pt(Pos)][C1 + 5] = Get_Item(Data.Items_Grid[Pos.X + C1][Pos.Y + 3])->ID;
						}
					}
				}
			} else if (ktn_stricmp(Visual_To_Machine(Data.Visual_Grid[pt(Pos)])->Index, "spawning_controller")) {
				int ID = Data.Settings_Grid[pt(Pos)][5];
				if (Fishlinks[ID].Autofill) {
					int Max = (int)floorf(Fishlinks[ID].Size / Fishlinks[ID].Type->Size);
					Fishlinks[ID].Fish = realloc(Fishlinks[ID].Fish, sizeof(struct Subfish) * Max);
					memset(Fishlinks[ID].Fish + Fishlinks[ID].Fish_Ct, 0, (Max - Fishlinks[ID].Fish_Ct) * sizeof(struct Subfish));
					Fishlinks[ID].Fish_Ct = Max;
				}
				for (int C1 = Fishlinks[ID].Fish_Ct - 1; C1 >= 0; C1--) {
					if (Fishlinks[ID].Fish[C1].Damage > ktn_health) {
						continue;
					}
					Fishlinks[ID].Nutrition = ktn_max(Fishlinks[ID].Nutrition - Fishlinks[ID].Type->Food_Consumption, 0);
					if (Fishlinks[ID].Nutrition < ktn_epsilon) {
						Fishlinks[ID].Fish[C1].Damage += Fishlinks[ID].Type->Fragility;
						continue;
					}
					Fishlinks[ID].Fish[C1].Growth++;
					if (Fishlinks[ID].Fish[C1].Growth >= Fishlinks[ID].Type->Max_Growth && Fishlinks[ID].Fish[C1].Damage <= ktn_health * 0.5f) {
						Fishlinks[ID].Fish_Ct--;
						memcpy(Fishlinks[ID].Fish + C1, Fishlinks[ID].Fish + C1 + 1, (Fishlinks[ID].Fish_Ct - C1) *
							sizeof(struct Subfish));
						Point Output = Find_Linked("spawning_output", Pos);
						Data.Data_Grid[pt(Output)][Stored_Fluids] = ktn_min(Data.Data_Grid[pt(Output)][Stored_Fluids] + 1, Data.Data_Grid[pt(Output)][Fluid_Cap]);
						Update_Item(Output, Fishlinks[ID].Type->Item->Index, 50);
					}
				}
			} else if (ktn_stricmp(Visual_To_Machine(Data.Visual_Grid[pt(Pos)])->Index, "spawning_input")) {
				Point Parent = { (int)(Data.Settings_Grid[pt(Pos)][3]), (int)(Data.Settings_Grid[pt(Pos)][4]) };
				float Food_Multiplier = Get_Item(Data.Items_Grid[pt(Pos)])->Nutrition;
				if (Data.Data_Grid[pt(Pos)][Stored_Fluids] > 0 && Food_Multiplier > 0) {
					Fishlinks[(int)(Data.Settings_Grid[pt(Parent)][5])].Nutrition += Data.Data_Grid[pt(Pos)][Stored_Fluids] * Food_Multiplier * 120.0f;
					Data.Data_Grid[pt(Pos)][Stored_Fluids] = 0;
				}
			}
		}
	}
}