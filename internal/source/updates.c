#include <grid.h>

void Update_Machines() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			int Rotation = Visual_To_Rotation(Data.Visual_Grid[Column][Row]);
			if (Data.Visual_Grid[Column][Row] > 0) {
				if (Data.Settings_Grid[Column][Row][1] > 0) {
					Data.Settings_Grid[Column][Row][1]--;
					switch (Visual_To_ID(Data.Visual_Grid[Column][Row])) {
					case Distillery:
						Extend_Recipe(Preset_IO_Recipes.D_Water, Column, Row, Preconfigs.D_Outputs);
						break;
					case Electrolytic_Cell:
						if (Data.Settings_Grid[Column][Row][2] == 1) {
							Extend_Recipe(Preset_IO_Recipes.EP_Water, Column, Row, Preconfigs.EP_Outputs);
						} else if (Data.Settings_Grid[Column][Row][2] == 2) {
							Extend_Recipe(Preset_IO_Recipes.EP_Saltwater, Column, Row, Preconfigs.EP_Outputs);
						} else {
							Extend_Recipe(Preset_IO_Recipes.EP_Salt, Column, Row, Preconfigs.EP_Outputs);
						}
						break;
					case Algae_Bed:
						Extend_Recipe(Preset_O_Recipes.GB_Algae, Column, Row, Preconfigs.GB_Outputs);
						break;
					default:
						break;
					}
				}
			}
			Node Inputs;
			Node Outputs;
			bool Conditional;
			switch (Visual_To_ID(Data.Visual_Grid[Column][Row])) {
			case Incinerator:
				{
					float Resulting_Fluid = max(Data.Data_Grid[Column][Row][Stored_Fluids] - 8.0, 0.0);
					Data.Data_Grid[Column][Row][Stored_Fluids] = Resulting_Fluid;
				}
				break;
			case Bio_Generator:
				{
					Point Offset = { 0, 2 };
					switch (Visual_To_Rotation(Data.Visual_Grid[Column][Row])) {
					case 1:
						Offset.Y = 0;
						break;
					case 2:
						Offset.X = 2;
						Offset.Y = 0;
						break;
					case 3:
						Offset.X = 2;
						break;
					}
					Item_Stack Target_Item = Get_Item(Column + Offset.X, Row + Offset.Y);
					Data.Animation_Grid[Column][Row][0] = 0;
					if (Check_Category(Target_Item.Identifier, Preset_Categories.Biomass) > 0 && Data.Data_Grid[Column +
						Offset.X][Row + Offset.Y][Stored_Fluids] >= 2) {
						Data.Data_Grid[Column + Offset.X][Row + Offset.Y][Stored_Fluids] -= 2;
						Data.Data_Grid[Column][Row][Stored_Power] = min(Data.Data_Grid[Column][Row][Stored_Power] +
							(Target_Item.Chemical_Energy / 100), Data.Data_Grid[Column][Row][Power_Cap]);
						Data.Animation_Grid[Column][Row][0] = 1;
					}
				}
				break;
			case Distillery:
				Return_Nodes(&Inputs, Column, Row, Visual_To_Rotation(Data.Visual_Grid[Column][Row]), Preconfigs.D_Inputs);
				Return_Nodes(&Outputs, Column, Row, Visual_To_Rotation(Data.Visual_Grid[Column][Row]), Preconfigs.D_Outputs);
				Process_Recipe(Preset_IO_Recipes.D_Water, Column, Row, Inputs, Outputs);
				break;
			case Algae_Bed:
				if (Data.Data_Grid[Column][Row][Stored_Power] > 120 && Data.Data_Grid[Column][Row + 2][Stored_Fluids] <= 2 &&
					Data.Data_Grid[Column + 1][Row + 2][Stored_Fluids] <= 2 && Data.Settings_Grid[Column][Row][1] <= 0) {
					Data.Settings_Grid[Column][Row][1] = 2;
				}
				Return_Nodes(&Outputs, Column, Row, Visual_To_Rotation(Data.Visual_Grid[Column][Row]), Preconfigs.GB_Outputs);
				Process_O_Recipe(Preset_O_Recipes.GB_Algae, Column, Row, Outputs);
				break;
			case Electrolytic_Cell:
				{
					Recipe Selected_Recipes[3] = {
						Preset_IO_Recipes.EP_Saltwater,
						Preset_IO_Recipes.EP_Water,
						Preset_IO_Recipes.EP_Salt
					};
					Return_Nodes(&Inputs, Column, Row, Visual_To_Rotation(Data.Visual_Grid[Column][Row]),
						Preconfigs.EP_Inputs);
					Return_Nodes(&Outputs, Column, Row, Visual_To_Rotation(Data.Visual_Grid[Column][Row]),
						Preconfigs.EP_Outputs);
					for (int Counter = 0; Counter < 3; Counter++) {
						Process_Recipe(Selected_Recipes[Counter], Column, Row, Inputs, Outputs);
					}
				}
				break;
			case Fluid_Mixer:
				{
					Recipe Selected_Recipes[4] = {
						Preset_IO_Recipes.FM_Drillmud_1,
						Preset_IO_Recipes.FM_Drillmud_2,
						Preset_IO_Recipes.FM_Hydrogen_Chloride,
						Preset_IO_Recipes.FM_Hydrochloric_Acid
					};
					for (int Counter = 0; Counter < 4; Counter++) {
						Data.Animation_Grid[Column][Row][0] = 0;
						Node Subinputs;
						Node Suboutputs;
						Return_Nodes(&Subinputs, Column, Row, Visual_To_Rotation(Data.Visual_Grid[Column][Row]),
							Preconfigs.FM_Inputs);
						Return_Nodes(&Suboutputs, Column, Row, Visual_To_Rotation(Data.Visual_Grid[Column][Row]),
							Preconfigs.FM_Outputs);
						if (Process_Recipe(Selected_Recipes[Counter], Column, Row, Subinputs, Suboutputs)) {
							Data.Animation_Grid[Column][Row][0] = 1;
							break;
						}
						free_c(Subinputs.Data);
						free_c(Suboutputs.Data);
					}
				}
				break;
			case Signal_Tower:
				if (Data.Settings_Grid[Column][Row][3] == 0) {
					Data.Settings_Grid[Column][Row][3] = 1;
				} else {
					Data.Settings_Grid[Column][Row][3] = 0;
				}
				break;
			case Geo_Well:
				Conditional = true;
				if (Data.Data_Grid[Column][Row][Stored_Power] < 2500) {
					Conditional = false;
				}
				Return_Nodes(&Inputs, Column, Row, Rotation, Preconfigs.GW_Inputs);
				Return_Nodes(&Outputs, Column, Row, Rotation, Preconfigs.GW_Outputs);
				if (Data.Data_Grid[Inputs.Data[Rotation].X][Inputs.Data[Rotation].Y][Stored_Fluids] < 8 || Data.Data_Grid[
					Outputs.Data[Rotation].X][Outputs.Data[Rotation].Y][Stored_Fluids] > 0) {
					Conditional = false;
				}
				if (Check_Category(Data.Items_Grid[Outputs.Data[Rotation].X][Outputs.Data[Rotation].Y],
					Preset_Categories.Coolant)) {
					Conditional = false;
				}
				if (Conditional) {
					Data.Data_Grid[Column][Row][Stored_Power] -= 2500;
					Data.Data_Grid[Inputs.Data[Rotation].X][Inputs.Data[Rotation].Y][Stored_Fluids] -= 8;
					Data.Data_Grid[Outputs.Data[Rotation].X][Outputs.Data[Rotation].Y][Stored_Fluids] += 8;
					int Temperature = Data.Temperature_Grid[Inputs.Data[Rotation].X][Inputs.Data[Rotation].Y];
					if (Temperature == 328) {
						Temperature = 327;
					}
					float Benchmark = log10((float)(328 - Temperature) / 263) / log10(0.64);
					Update_Item(Outputs.Data[Rotation].X, Outputs.Data[Rotation].Y, Data.Items_Grid[Inputs.Data[Rotation].X][
						Inputs.Data[Rotation].Y], (-263 * pow(0.64, Benchmark + 1)) + 328);
				}
				break;
			case Large_Pipe:
				if (Get_Item(Column, Row).Hazard > Harmless) {
					//if hazard then go boom
				}
				break;
			case Money_Generator:
				Data.Funds = max(Data.Funds + (float)(Data.Settings_Grid[Column][Row][4]), 0.0f);
				break;
			case Fluid_Generator:
				if (Data.Items_Grid[Column][Row] != Data.Settings_Grid[Column][Row][3] || Data.Temperature_Grid[Column][
					Row] != Data.Settings_Grid[Column][Row][4]) {
					Data.Data_Grid[Column][Row][Stored_Fluids] = 0;
					Data.Items_Grid[Column][Row] = Data.Settings_Grid[Column][Row][3];
					Data.Temperature_Grid[Column][Row] = Data.Settings_Grid[Column][Row][4];
				}
				Data.Data_Grid[Column][Row][Stored_Fluids] = min(Data.Settings_Grid[Column][Row][5] + Data.Data_Grid[Column][
					Row][Stored_Fluids], Data.Data_Grid[Column][Row][Fluid_Cap]);
				break;
			case R_Intersection:
			case L_Intersection:
				//check4hazard!
				Return_Nodes(&Inputs, Column, Row, Visual_To_Rotation(Data.Visual_Grid[Column][Row]), Preconfigs.I_Inputs);
				Return_Nodes(&Outputs, Column, Row, Visual_To_Rotation(Data.Visual_Grid[Column][Row]), Preconfigs.I_Outputs);
				for (int Counter = 0; Counter < 2; Counter++) {
					int OX = Outputs.Data[Counter].X;
					int OY = Outputs.Data[Counter].Y;
					int IX = Inputs.Data[Counter].X;
					int IY = Inputs.Data[Counter].Y;
					float Difference = Data.Data_Grid[OX][OY][Fluid_Cap] - Data.Data_Grid[OX][OY][Stored_Fluids];
					Difference = min(Difference, Data.Data_Grid[IX][IY][Stored_Fluids]);
					if (Difference > 0 && (Data.Items_Grid[IX][IY] == Data.Items_Grid[OX][OY] || Data.Items_Grid[OX][OY] ==
						LDE_INVALID)) {
						Data.Data_Grid[OX][OY][Stored_Fluids] += Difference;
						Data.Data_Grid[IX][IY][Stored_Fluids] -= Difference;
						Update_Item(Outputs.Data[Counter].X, OY, Data.Items_Grid[IX][IY], Data.Temperature_Grid[IX][IY]);
					}
				}
				break;
			case Turbine_Input:
				Data.Settings_Grid[Column][Row][7] = 0;
				Return_Nodes(&Inputs, Column, Row, Visual_To_Rotation(Data.Visual_Grid[Column][Row]), Preconfigs.STI_Inputs);
				Return_Nodes(&Outputs, Data.Settings_Grid[Column][Row][5], Data.Settings_Grid[Column][Row][6],
					Visual_To_Rotation(Data.Visual_Grid[(int)(Data.Settings_Grid[Column][Row][5])][(int)(Data.Settings_Grid[
					Column][Row][6])]), Preconfigs.STO_Outputs);
				if (Data.Settings_Grid[Column][Row][3] > 0 && Data.Settings_Grid[Column][Row][4] == 1 && Data.Items_Grid[
					Inputs.Data[0].X][Inputs.Data[0].Y] == Preset_Items.Steam.Identifier && Data.Items_Grid[Outputs.Data[0].X][
					Outputs.Data[0].Y] ==Preset_Items.Steam.Identifier) {
					float Transferred = Data.Data_Grid[Outputs.Data[0].X][Outputs.Data[0].Y][Fluid_Cap] - Data.Data_Grid[
						Outputs.Data[0].X][Outputs.Data[0].Y][Stored_Fluids];
					Transferred = min(Transferred, Data.Data_Grid[Inputs.Data[0].X][Inputs.Data[0].Y][Stored_Fluids]);
					if (Transferred > 0) {
						Data.Data_Grid[Inputs.Data[0].X][Inputs.Data[0].Y][Stored_Fluids] -= Transferred;
						Data.Data_Grid[Outputs.Data[0].X][Outputs.Data[0].Y][Stored_Fluids] += Transferred;
						float Generated = Transferred * LDE_TURBINECOEFFICIENT * log(sqr_f(Data.Temperature_Grid[Inputs.Data[
							0].X][Inputs.Data[0].Y])) * log(Data.Settings_Grid[Column][Row][3] * 1.5);
						Update_Item(Outputs.Data[0].X, Outputs.Data[0].Y, Preset_Items.Steam.Identifier,
							(Data.Temperature_Grid[Inputs.Data[0].X][Inputs.Data[0].Y] * 0.1) + 32);
						if (Data.Temperature_Grid[Inputs.Data[0].X][Inputs.Data[0].Y] < 200) {
							Generated = 0;
						}
						Data.Settings_Grid[Column][Row][7] = Generated;
						Data.Data_Grid[Column][Row][Stored_Power] = min(Data.Data_Grid[Column][Row][Power_Cap], Data.Data_Grid[
							Column][Row][Stored_Power] + Generated);
					}
				}
				break;
			default:
				break;
			}
			if (Data.Visual_Grid[Column][Row] == 17) {
				Node tmp3;tmp3.Data=(Point*)malloc(sizeof(Point));tmp3.Length=1;
				tmp3.Data[0].X = Column;tmp3.Data[0].Y=Row;
				if (Process_O_Recipe(Preset_O_Recipes.RP_Saltwater, Column, Row, tmp3)) {
					Data.Animation_Grid[Column][Row][0] = 0;
					Play_Sound(&Audio.Ram_Loop, false);
				} else if (Data.Animation_Grid[Column][Row][0] == 0) {
					Data.Animation_Grid[Column][Row][0] = LDE_INVALID;
				}
				free_c(tmp3.Data);
			} else if (Data.Visual_Grid[Column][Row] == 19) {
				Data.Data_Grid[Column][Row][Stored_Power] = min(Data.Data_Grid[Column][Row][Stored_Power] + 0.5,
					Data.Data_Grid[Column][Row][Power_Cap]);
			} else if (Data.Visual_Grid[Column][Row] == 21) {
				for (int Counter = 0; Counter < 2; Counter++) {
					if (Data.Data_Grid[Column + Counter][Row + 3][Stored_Fluids] > 0) {
						if (Data.Settings_Grid[Column][Row][Counter + 5] == Get_Item(Column + Counter, Row + 3).Identifier ||
							Data.Settings_Grid[Column][Row][Counter + 5] == LDE_INVALID) {
							Data.Settings_Grid[Column][Row][Counter + 3] = min(Data.Settings_Grid[Column][Row][Counter + 3] +
								Data.Data_Grid[Column + Counter][Row + 3][Stored_Fluids], LDE_DOCKCAPACITY);
							Data.Data_Grid[Column + Counter][Row + 3][Stored_Fluids] = 0;
							Data.Settings_Grid[Column][Row][Counter + 5] = Get_Item(Column + Counter, Row + 3).Identifier;
						}
					}
				}
			} else if (Data.Visual_Grid[Column][Row] == 22) {
				Node tmp1;tmp1.Data = (Point*)malloc(sizeof(Point));
				tmp1.Length = 1;tmp1.Data[0].X = Column;
				tmp1.Data[0].Y = Row + 1;
				Node tmp2;tmp2.Data = (Point*)malloc(sizeof(Point)*3);
				tmp2.Length = 3;tmp2.Data[0].X = Column + 1;
				tmp2.Data[0].Y = Row;tmp2.Data[1].X = Column + 1;
				tmp2.Data[1].Y = Row + 1;tmp2.Data[2].X = Column + 1;
				tmp2.Data[2].Y = Row + 2;
				bool Running1 = Process_Recipe(Preset_IO_Recipes.FP_Saltwater,
					Column, Row, tmp1, tmp2);
				bool Running2 = Process_Recipe(Preset_IO_Recipes.FP_Biopaste,
					Column, Row, tmp1, tmp2);
				Data.Animation_Grid[Column][Row][0] = 0;
				Data.Animation_Grid[Column][Row][1] = 0;
				if (Running1 || Running2) {
					Play_Sound(&Audio.Filtration_Loop, false);
				} else if (Data.Animation_Grid[Column][Row][0] == 0) {
					Data.Animation_Grid[Column][Row][0] = LDE_INVALID;
					Data.Animation_Grid[Column][Row][1] = 0;
				}
				free_c(tmp1.Data);
				free_c(tmp2.Data);
			} else if (Data.Visual_Grid[Column][Row] == 45) {
				if (Data.Settings_Grid[Column][Row][5] != 0) {
					if (Data.Settings_Grid[Column][Row][4] >= Data.Settings_Grid[Column][Row][5] *
						Fish_Catalog[(int)(Data.Settings_Grid[Column][Row][6])].Food_Consumption) {
						Data.Settings_Grid[Column][Row][4] -= Data.Settings_Grid[Column][Row][5] *
							Fish_Catalog[(int)(Data.Settings_Grid[Column][Row][6])].Food_Consumption;
					} else {
						if (Data.Settings_Grid[Column][Row][5] > 1) {
							Data.Settings_Grid[Column][Row][5]--;
						} else {
							Data.Settings_Grid[Column][Row][5] = 0;
							Data.Settings_Grid[Column][Row][7] = 0;
						}
					}
					if (Data.Settings_Grid[Column][Row][7] >= Fish_Catalog[(int)(Data.Settings_Grid[Column][Row][6])]
						.Maximum_Growth) {
						Data.Settings_Grid[Column][Row][7] = 0;
						Point Coordinate = Find_Linked(14, Column, Row);
						Item_Stack Fish = Get_Fish_Item((int)(Data.Settings_Grid[Column][Row][6]));
						Update_Item(Coordinate.X, Coordinate.Y, Fish.Identifier, LDE_ROOMTEMP);
						Data.Data_Grid[Coordinate.X][Coordinate.Y][0] = min(Data.Settings_Grid[Column][Row][5], Data.Data_Grid[
							Coordinate.X][Coordinate.Y][Fluid_Cap]);
					}
					Data.Settings_Grid[Column][Row][7] += 1;
				}
			} else if (Data.Visual_Grid[Column][Row] == 47) {
				int Parent_X = (int)(Data.Settings_Grid[Column][Row][3]);
				int Parent_Y = (int)(Data.Settings_Grid[Column][Row][4]);
				double Food_Multiplier = 0;
				if (Data.Items_Grid[Column][Row] == Preset_Items.Marine_Snow.Identifier) {
					Food_Multiplier = 0.35;
				} else if (Data.Items_Grid[Column][Row] == Preset_Items.Raw_Algae.Identifier) {
					Food_Multiplier = 0.5;
				} else if (Data.Items_Grid[Column][Row] == Preset_Items.Biopaste.Identifier) {
					Food_Multiplier = 0.65;
				}
				if (Data.Data_Grid[Column][Row][Stored_Fluids] > 0 && Food_Multiplier > 0) {
					Data.Settings_Grid[Parent_X][Parent_Y][4] += Data.Data_Grid[
						Column][Row][Stored_Fluids] * Food_Multiplier;
					Data.Data_Grid[Column][Row][Stored_Fluids] = 0;
				}
			} else if (Visual_To_ID(Data.Visual_Grid[Column][Row]) == Heat_Exchanger) {
				bool Boiling = false;
				if (Data.Settings_Grid[Interface.Target_Tile.X][Interface.Target_Tile.Y][8] >= LDE_WATERBOILPOINT) {
					Boiling = true;
				}
				Point Outputs[2][4] = {
					{
						{ Column + 3, Row },
						{ Column + 2, Row + 3 },
						{ Column, Row + 2 },
						{ Column, Row }
					},
					{
						{ Column, Row },
						{ Column + 2, Row },
						{ Column + 3, Row + 2 },
						{ Column, Row + 3 }
					}
				};
				for (int Counter = 0; Counter < 2; Counter++) {
					Point Output_Pos = Outputs[Counter][Visual_To_Rotation(Data.Visual_Grid[Column][Row])];
					if ((Data.Items_Grid[Output_Pos.X][Output_Pos.Y] == LDE_INVALID || (Data.Settings_Grid[Column][Row][
						Counter + 9] == Data.Items_Grid[Output_Pos.X][Output_Pos.Y] && !Boiling) || (Data.Items_Grid[
						Output_Pos.X][Output_Pos.Y] == Preset_Items.Steam.Identifier && Boiling && Counter == 1)) &&
						Data.Settings_Grid[Column][Row][Counter + 5] > 0) {
						if (Boiling && Counter == 1) {
							Data.Items_Grid[Output_Pos.X][Output_Pos.Y] = Preset_Items.Steam.Identifier;
						} else {
							Data.Items_Grid[Output_Pos.X][Output_Pos.Y] = Data.Settings_Grid[Column][Row][Counter + 9];
						}
						float Draining_Amount = min(Data.Settings_Grid[Column][Row][Counter + 3], Data.Settings_Grid[Column][
							Row][Counter + 5]);
						Draining_Amount = min(Draining_Amount, Data.Data_Grid[Output_Pos.X][Output_Pos.Y][Fluid_Cap] -
							Data.Data_Grid[Output_Pos.X][Output_Pos.Y][Stored_Fluids]);
						Data.Data_Grid[Output_Pos.X][Output_Pos.Y][Stored_Fluids] += Draining_Amount;
						Data.Settings_Grid[Column][Row][Counter + 5] -= Draining_Amount;
					}
				}
				Point Inputs[2][4] = {
					{
						{ Column + 3, Row + 2 },
						{ Column, Row + 3 },
						{ Column, Row },
						{ Column + 2, Row }
					},
					{
						{ Column, Row + 2 },
						{ Column, Row },
						{ Column + 3, Row },
						{ Column + 2, Row + 3 }
					}
				};
				Item_Category Categories[2] = {
					Preset_Categories.Coolant,
					Preset_Categories.Feedwater
				};
				for (int Counter = 0; Counter < 2; Counter++) {
					Point Input_Pos = Inputs[Counter][Visual_To_Rotation(Data.Visual_Grid[Column][Row])];
					if (Check_Category(ID_To_Item(Data.Items_Grid[Input_Pos.X][Input_Pos.Y]).Identifier, Categories[
						Counter]) && (Data.Settings_Grid[Column][Row][Counter + 9] == LDE_INVALID || Data.Settings_Grid[
						Column][Row][Counter + 9] == Data.Items_Grid[Input_Pos.X][Input_Pos.Y])) {
						Data.Settings_Grid[Column][Row][Counter + 9] = Data.Items_Grid[Input_Pos.X][Input_Pos.Y];
						int Volume = Data.Settings_Grid[Column][Row][Counter + 5];
						int Intake = 0;
						if (Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids] > 0 && Volume < LDE_HXCAPACITY) {
							if (Volume + Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids] > LDE_HXCAPACITY) {
								Intake = LDE_HXCAPACITY - Volume;
								Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids] -= Intake;
								Data.Settings_Grid[Column][Row][Counter + 5] = LDE_HXCAPACITY;
							} else {
								Intake = Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids];
								Data.Settings_Grid[Column][Row][Counter + 5] += Intake;
								Data.Data_Grid[Input_Pos.X][Input_Pos.Y][Stored_Fluids] = 0;
							}
						}
						if (Volume + Intake != 0) {
							Data.Settings_Grid[Column][Row][Counter + 7] = ((Data.Settings_Grid[Column][Row][Counter + 7] *
								Volume) + (Data.Temperature_Grid[Input_Pos.X][Input_Pos.Y] * Intake)) / (Volume + Intake);
						}
					}
				}
				float Temp_Equil = ((Data.Settings_Grid[Column][Row][6] * Data.Settings_Grid[Column][Row][8]) +
					(Data.Settings_Grid[Column][Row][5] * Data.Settings_Grid[Column][Row][7])) / (Data.Settings_Grid[Column][
					Row][6] + Data.Settings_Grid[Column][Row][5]);
				float Difference = Data.Settings_Grid[Column][Row][7] - Data.Settings_Grid[Column][Row][8];
				float Remaining = pow(M_E, (-1 * ((LDE_HXEFFICIENCY * (Data.Settings_Grid[Column][Row][6] + Data.Settings_Grid[
					Column][Row][5])) / (4.186 * Data.Settings_Grid[Column][Row][6] * Data.Settings_Grid[Column][Row][5]))));
				float FW_Yield = Temp_Equil - (((Data.Settings_Grid[Column][Row][5] / (Data.Settings_Grid[Column][Row][6] +
					Data.Settings_Grid[Column][Row][5])) * Difference) * Remaining);
				float HM_Yield = Temp_Equil + (((Data.Settings_Grid[Column][Row][6] / (Data.Settings_Grid[Column][Row][6] +
					Data.Settings_Grid[Column][Row][5])) * Difference) * Remaining);
				if (HM_Yield > 0 && FW_Yield > 0) {
					Data.Settings_Grid[Column][Row][7] = HM_Yield;
					Data.Settings_Grid[Column][Row][8] = FW_Yield;
				}
			}
			free_c(Inputs.Data);
			free_c(Outputs.Data);
		}
	}
}