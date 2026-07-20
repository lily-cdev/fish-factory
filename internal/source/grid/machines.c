#include <grid.h>

bool (*Placing_Functions[])(Point Pos) = {
	Place_Reinforced_Pipe, Place_Submarine_Dock, Place_Spawning_Pool,
	Place_Spawning_Controller, Place_Spawning_Output, Place_Spawning_Input,
	Place_Signal_Tower, Place_Large_Pipe, Place_Heat_Exchanger,
	Place_Money_Generator, Place_Fluid_Generator,
	Place_Turbine_Input, Place_Turbine_Impulse, Place_Power_Generator
};

const char* Placing_Registers[] = {
	"heavy_pipe", "sub_dock", "spawning_pool",
	"spawning_controller", "spawning_output", "spawning_input",
	"signal_tower", "large_pipe", "hx",
	"money_cheat", "fluid_cheat",
	"turbine_input", "turbine_impulse", "power_cheat"
};

Point Find_Linked(const char* Index, Point Parent) {
	Point Pos;
	for (Pos.X = 0; Pos.X < ktn_grid_size; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < ktn_grid_size; Pos.Y++) {
			Machine_Ptr Chosen = Visual_To_Machine(Data.Visual_Grid[pt(Pos)]);
			if (!Chosen) {
				continue;
			}
			if (ktn_stricmp(Chosen->Index, Index) && Data.Settings_Grid[pt(Pos)][3] == Parent.X &&
				Data.Settings_Grid[pt(Pos)][4] == Parent.Y) {
				return Pos;
			}
		}
	}
	return (Point){ ktn_invalid, ktn_invalid };
}

bool Match(Point Pos, Point Og, int Direction, int Target, bool Is_Pipe) {
	bool Yield = (Is_Bound(Pos) && ((Is_Pipe && (Data.Plumbing_Grid[pt(Pos)] == Direction || Data.Plumbing_Grid[pt(Pos)] == Any)) ||
		Data.Behavior_Grid[pt(Pos)] == Target));
	bool Unconnected = true;
	for (int C1 = 0; C1 < Pipes.Length; C1++) {
		if ((Pipes.Data[C1].X1 == Pos.X || Pipes.Data[C1].X2 == Pos.X) && (Pipes.Data[C1].Y1 == Pos.Y || Pipes.Data[C1].Y2 == Pos.Y) &&
			(Pipes.Data[C1].X1 == Og.X || Pipes.Data[C1].X2 == Og.X) && (Pipes.Data[C1].Y1 == Og.Y || Pipes.Data[C1].Y2 == Og.Y)) {
			Unconnected = false;
			break;
		}
	}
	return (Unconnected) ? false : Yield;
}

#define Param(XM, YM, Direction) (Point){ Pos.X + (XM), Pos.Y + (YM) }, Pos, Direction, Target, Is_Pipe
int Modular_Detection(Point Pos, int Target, bool Is_Pipe) {
	if (Target == ktn_invalid) {
		Target = -2;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(1, 0, Left)) && Match(Param(0, 1, Up)) && Match(Param(0, -1, Down))) {
		return C_Omni;
	}
	if (Match(Param(1, 0, Left)) && Match(Param(0, 1, Up)) && Match(Param(0, -1, Down))) {
		return C_LeftT;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(0, -1, Up)) && Match(Param(0, 1, Down))) {
		return C_RightT;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(1, 0, Left)) && Match(Param(0, 1, Up))) {
		return C_UpT;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(1, 0, Left)) && Match(Param(0, -1, Down))) {
		return C_DownT;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(1, 0, Left))) {
		return C_Horizontal;
	}
	if (Match(Param(0, 1, Up)) && Match(Param(0, -1, Down))) {
		return C_Vertical;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(0, -1, Down))) {
		return C_LeftTop;
	}
	if (Match(Param(1, 0, Left)) && Match(Param(0, -1, Down))) {
		return C_TopRight;
	}
	if (Match(Param(1, 0, Left)) && Match(Param(0, 1, Up))) {
		return C_RightBottom;
	}
	if (Match(Param(-1, 0, Right)) && Match(Param(0, 1, Up))) {
		return C_BottomLeft;
	}
	if (Match(Param(-1, 0, Right))) {
		return C_Left;
	}
	if (Match(Param(0, -1, Down))) {
		return C_Top;
	}
	if (Match(Param(1, 0, Left))) {
		return C_Right;
	}
	if (Match(Param(0, 1, Up))) {
		return C_Bottom;
	}
	return C_None;
}
#undef Param

int Recursive_Detect(Point Pos, const char* Target, const char* Self, bool Grid[ktn_grid_size][ktn_grid_size], bool Self_Accounted,
	const char* Target1, const char* Target2);

int Recursive_Detect(Point Pos, const char* Target, const char* Self, bool Grid[ktn_grid_size][ktn_grid_size], bool Self_Accounted,
	const char* Target1, const char* Target2) {
	bool Progressing = false;
	if (Pos.X >= 0 && Pos.Y >= 0 && Pos.X < ktn_grid_size && Pos.Y < ktn_grid_size && !Grid[pt(Pos)]) {
		Machine_Ptr Chosen = Visual_To_Machine(Data.Visual_Grid[pt(Pos)]);
		if (Chosen && ktn_stricmp(Chosen->Index, Target)) {
			Progressing = true;
		} else if (Chosen && ktn_stricmp(Visual_To_Machine(Data.Visual_Grid[pt(Pos)])->Index, Self)) {
			if (Self_Accounted) {
				return -9999;
			} else {
				Self_Accounted = true;
				Progressing = true;
			}
		} else if (Chosen && ktn_stricmp(Visual_To_Machine(Data.Visual_Grid[pt(Pos)])->Index, Target1)) {
			Temporary.Modular1_Requirement++;
			Data.Settings_Grid[pt(Pos)][3] = Temporary.First_Coordinate.X;
			Data.Settings_Grid[pt(Pos)][4] = Temporary.First_Coordinate.Y;
			Progressing = true;
		} else if (Chosen && ktn_stricmp(Visual_To_Machine(Data.Visual_Grid[pt(Pos)])->Index, Target2)) {
			Temporary.Modular2_Requirement++;
			Data.Settings_Grid[pt(Pos)][3] = Temporary.First_Coordinate.X;
			Data.Settings_Grid[pt(Pos)][4] = Temporary.First_Coordinate.Y;
			Progressing = true;
		}
	}
	if (Progressing) {
		Grid[pt(Pos)] = true;
		return 1 + Recursive_Detect((Point){ Pos.X + 1, Pos.Y }, Target, Self, Grid, Self_Accounted, Target1, Target2) +
			Recursive_Detect((Point){ Pos.X - 1, Pos.Y }, Target, Self, Grid, Self_Accounted, Target1, Target2) +
			Recursive_Detect((Point){ Pos.X, Pos.Y + 1 }, Target, Self, Grid, Self_Accounted, Target1, Target2) +
			Recursive_Detect((Point){ Pos.X, Pos.Y - 1 }, Target, Self, Grid, Self_Accounted, Target1, Target2);
	}
	return 0;
}

int Find_Modular_Size(Point Pos, const char* Target, const char* Self, const char* Target1, const char* Target2) {
	bool Self_Accounted = false;
	bool Checked_Grid[ktn_grid_size][ktn_grid_size] = { };
	for (int X2 = 0; X2 < ktn_grid_size; X2++) {
		for (int Y2 = 0; Y2 < ktn_grid_size; Y2++) {
			Checked_Grid[X2][Y2] = false;
		}
	}
	return Recursive_Detect(Pos, Target, Self, Checked_Grid, Self_Accounted, Target1, Target2);
}

void Restore_Cache() {
	Temporary.Docks.Length = 0;
	Temporary.Docks.Full_Size = 0;
	ktn_free(Temporary.Docks.Data);
	Point Pos;
	for (Pos.X = 0; Pos.X < ktn_grid_size; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < ktn_grid_size; Pos.Y++) {
			Machine_Ptr Machine = Visual_To_Machine(Data.Visual_Grid[pt(Pos)]);
			if (!Machine) {
				continue;
			}
			if (ktn_stricmp(Machine->Index, "sub_dock")) {
				Push_Docks(Pos);
			}
		}
	}
	Recache_TT_Commands();
}

void Destroy_Clearance(Point Pos, int Width, int Height) {
	for (int C1 = 0; C1 < Width; C1++) {
		for (int C2 = 0; C2 < Height; C2++) {
			Reset_Tile((Point){ Pos.X + C1, Pos.Y + C2 });
		}
	}
}

void Update_Grid() {
	int Temporary_Grid[ktn_grid_size][ktn_grid_size];
	Point Pos;
	for (Pos.X = 0; Pos.X < ktn_grid_size; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < ktn_grid_size; Pos.Y++) {
			Temporary_Grid[pt(Pos)] = Data.Visual_Grid[pt(Pos)];
		}
	}
	for (Pos.X = 0; Pos.X < ktn_grid_size; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < ktn_grid_size; Pos.Y++) {
			Machine_Ptr Machine = Visual_To_Machine(Data.Visual_Grid[pt(Pos)]);
			if (!Machine) {
				continue;
			}
			if (ktn_stricmp(Machine->Index, "heavy_pipe")) {
				Temporary_Grid[pt(Pos)] = Modular_Detection(Pos, ktn_invalid, true) + 1;
			} else if (Data.Visual_Grid[pt(Pos)] > 23 && Data.Visual_Grid[pt(Pos)] < 41) {
				Temporary_Grid[pt(Pos)] = Modular_Detection(Pos, 0, false) + 24;
			} else if (Data.Visual_Grid[pt(Pos)] == 45) {
				Temporary.First_Coordinate = Pos;
				int ID = Data.Settings_Grid[pt(Pos)][5];
				Fishlinks[ID].Size = Find_Modular_Size(Pos, "spawning_pool", "spawning_controller", "spawning_output", "spawning_input");
				if (Fishlinks[ID].Size < 0) {
					Fishlinks[ID].Size = -2;
				}
				if (Temporary.Modular1_Requirement != 1) {
					Fishlinks[ID].Size = (Temporary.Modular1_Requirement < 1) ? -3 : -4;
				}
				if (Temporary.Modular2_Requirement != 1) {
					Fishlinks[ID].Size = (Temporary.Modular2_Requirement < 1) ? -5 : -6;
				}
				Temporary.Modular1_Requirement = 0;
				Temporary.Modular2_Requirement = 0;
			} else if (ktn_stricmp(Machine->Index, "large_pipe")) {
				Temporary_Grid[pt(Pos)] = Modular_Detection(Pos, ktn_invalid, true) + 71;
			}
		}
	}
	for (Pos.X = 0; Pos.X < ktn_grid_size; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < ktn_grid_size; Pos.Y++) {
			Data.Visual_Grid[pt(Pos)] = Temporary_Grid[pt(Pos)];
		}
	}
}

void Build_Grid() {
	for (int Column = 0; Column < ktn_grid_size; Column++) {
		Rects.Tile_1x1.x = ktn_fscale((Column * ktn_tile_size) - Core.Camera.X);
		for (int Row = 0; Row < ktn_grid_size; Row++) {
			Rects.Tile_1x1.y = ktn_fscale((Row * ktn_tile_size) - Core.Camera.Y);
			if (!Detect_Mouse_Collision(Rects.Tile_1x1)) {
				continue;
			}
			if (Data.Visual_Grid[Column][Row] != 0) {
				return;
			}
			int Rotation = (Interface.Item->Quirks[Q_Non_Rotatable]) ? 0 : Interface.Rotation;
			Point Pos = { Column, Row };
			Point Size = Interface.Item->Size;
			if ((Data.CMD_Placed && Interface.Item->Command) || (Pool_Ct >= 16 && ktn_stricmp(Interface.Item->Index,
				"spawning_controller"))) {
				return;
			}
			if (ktn_evn(Rotation)) {
				if (!Check_Clearance(Pos, Size.X, Size.Y)) {
					return;
				}
				Destroy_Clearance(Pos, Size.X, Size.Y);
				Fill_Clearance(ktn_invalid, Pos, Size.X, Size.Y);
			} else {
				if (!Check_Clearance(Pos, Size.Y, Size.X)) {
					return;
				}
				Destroy_Clearance(Pos, Size.Y, Size.X);
				Fill_Clearance(ktn_invalid, Pos, Size.Y, Size.X);
			}
			for (int C1 = 0; C1 < sizeof(Placing_Functions) / sizeof(Placing_Functions[0]); C1++) {
				if (ktn_stricmp(Interface.Item->Index, Placing_Registers[C1])) {
					if (!Placing_Functions[C1](Pos)) {
						return;
					}
				}
			}
			Data.Wiring_Grid[Column][Row] = Interface.Item->Power_Type;
			if (Interface.Item->Power_Type != F_None) {
				Data.Data_Grid[Column][Row][Power_Cap] = Interface.Item->Power_Capacity;
				Point_f Anchor = (Point_f){
					(float)Interface.Item->Anchor.X,
					(float)Interface.Item->Anchor.Y
				};
				if (ktn_evn(Rotation)) {
					Data.Data_Grid[Column][Row][5] = (Rotation == 0) ? Anchor.X : (Size.X * 40.0f) - Anchor.X;
					Data.Data_Grid[Column][Row][6] = (Rotation == 0) ? Anchor.Y : (Size.Y * 40.0f) - Anchor.Y;
				} else {
					Data.Data_Grid[Column][Row][5] = (Rotation == 1) ? (Size.Y * 40.0f) - Anchor.Y : Anchor.Y;
					Data.Data_Grid[Column][Row][6] = (Rotation == 1) ? Anchor.X : (Size.X * 40.0f) - Anchor.X;
				}
			}
			Data.Funds -= Interface.Queried_Price;
			if (Interface.Item->Visual_Type == I_Single) {
				Data.Visual_Grid[Column][Row] = Interface.Item->Visual_ID1;
			} else if (Interface.Item->Visual_Type == I_Rot) {
				Data.Visual_Grid[Column][Row] = Interface.Item->Visual_ID4[Rotation];
			}
			if (Interface.Item->Command) {
				Data.CMD_Placed = true;
			}
			int Node_Cts[3] = { Interface.Item->Input_Ct, Interface.Item->Output_Ct, Interface.Item->Neutral_Ct };
			Node_Data* Node_Ptrs[3] = { Interface.Item->Inputs, Interface.Item->Outputs, Interface.Item->Neutrals };
			for (int C1 = 0; C1 < 3; C1++) {
				for (int C2 = 0; C2 < Node_Cts[C1]; C2++) {
					Point Tile = Rotate_Pt(Node_Ptrs[C1][C2].Pos, Interface.Item->Size, Interface.Rotation);
					Tile.X += Column;
					Tile.Y += Row;
					if (Node_Ptrs[C1][C2].Connection == Any) {
						Data.Plumbing_Grid[pt(Tile)] = Any;
					} else {
						Data.Plumbing_Grid[pt(Tile)] = Node_Ptrs[C1][C2].Connection + Interface.Rotation;
						if (Data.Plumbing_Grid[pt(Tile)] > Down) {
							Data.Plumbing_Grid[pt(Tile)] -= 4;
						}
					}
					Data.Settings_Grid[pt(Tile)][0] = Node_Ptrs[C1][C2].Flow;
					Data.Data_Grid[pt(Tile)][Fluid_Cap] = Node_Ptrs[C1][C2].Cap;
				}
			}
			Update_Grid();
			Recast_Machines();
			Bake_Light((Point){ Column, Row });
			Find_Effect();
			return;
		}
	}
}

void Remove_Machine(Point Pos) {
	Data.Funds += (int)(floorf(Visual_To_Machine(Data.Visual_Grid[pt(Pos)])->Price * 0.75f));
	int Width;
	int Height;
	Machine_Ptr Target = Visual_To_Machine(Data.Visual_Grid[pt(Pos)]);
	if (!Target) {
		return;
	}
	ID_To_Size(Target, Visual_To_Rotation(Data.Visual_Grid[pt(Pos)]), &Width, &Height);
	if (Width == 1 && Height == 1) {
		Wipe_Tile(Pos);
		Data.Visual_Grid[pt(Pos)] = 0;
		Data.Wiring_Grid[pt(Pos)] = ktn_invalid;
		Data.Plumbing_Grid[pt(Pos)] = ktn_invalid;
		Data.Behavior_Grid[pt(Pos)] = ktn_invalid;
		memset(Data.Data_Grid[pt(Pos)], 0, sizeof(Data.Data_Grid[pt(Pos)]));
		Data.Data_Grid[pt(Pos)][4] = ktn_invalid;
		for (int C1 = 0; C1 < sizeof(Data.Settings_Grid[pt(Pos)]) / sizeof(Data.Settings_Grid[pt(Pos)][0]); C1++) {
			Data.Settings_Grid[pt(Pos)][C1] = ktn_invalid;
		}
		for (int C1 = 0; C1 < sizeof(Data.Animation_Grid[pt(Pos)]) / sizeof(Data.Animation_Grid[pt(Pos)][0]); C1++) {
			Data.Animation_Grid[pt(Pos)][C1] = ktn_invalid;
		}
		Update_Item(Pos, ktn_invalid, ktn_room_temp);
		if (ktn_stricmp(Target->Index, "spawning_controller")) {
			Fishlinks[(int)Data.Settings_Grid[pt(Pos)][5]].Allocated = false;
			ktn_free(Fishlinks[(int)Data.Settings_Grid[pt(Pos)][5]].Fish);
			//rem fishlink
			Pool_Ct--;
		}
	} else {
		if (ktn_stricmp(Target->Index, "sub_dock")) {
			for (int C1 = 0; C1 < Temporary.Docks.Length; C1++) {
				if (Temporary.Docks.Data[C1].X == Pos.X && Temporary.Docks.Data[C1].Y == Pos.Y) {
					Pull_Docks(C1);
				}
			}
			if (Transition.Sub_Pos.X == Pos.X && Transition.Sub_Pos.X == Pos.Y) {
				Transition.Sub_Phase = 3;
			}
			Recache_TT_Commands();
		}
		if (Interface.Item->Command) {
			Data.CMD_Placed = false;
		}
		Destroy_Clearance(Pos, Width, Height);
	}
	for (int C1 = 0; C1 < Wires.Length; C1++) {
		if ((Wires.Data[C1].X1 == Pos.X && Wires.Data[C1].Y1 == Pos.Y) || (Wires.Data[C1].X2 == Pos.X &&
			Wires.Data[C1].Y2 == Pos.Y)) {
			Wires.Data[C1].Filled = false;
		}
	}
	for (int C1 = 0; C1 < Pipes.Length; C1++) {
		if ((Pipes.Data[C1].X1 == Pos.X && Pipes.Data[C1].Y1 == Pos.Y) || (Pipes.Data[C1].X2 == Pos.X &&
			Pipes.Data[C1].Y2 == Pos.Y)) {
			Pipes.Data[C1].Filled = false;
		}
	}
}

bool Destroy_Grid() {
	Point Pos;
	for (Pos.X = 0; Pos.X < ktn_grid_size; Pos.X++) {
		Rects.Tile_1x1.x = ktn_fscale((Pos.X * ktn_tile_size) - Core.Camera.X);
		for (Pos.Y = 0; Pos.Y < ktn_grid_size; Pos.Y++) {
			Rects.Tile_1x1.y = ktn_fscale((Pos.Y * ktn_tile_size) - Core.Camera.Y);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				if (Data.Visual_Grid[pt(Pos)] != 0) {
					Cache.Wire_State = Deep_Recache;
					if (Data.Visual_Grid[pt(Pos)] == ktn_invalid) {
						Remove_Machine((Point){
							(int)(Data.Settings_Grid[pt(Pos)][S_ParentX]),
							(int)(Data.Settings_Grid[pt(Pos)][S_ParentY])
						});
					} else {
						Remove_Machine(Pos);
					}
					Clear_Unconnected_Bridges(&Wires);
					Clear_Unconnected_Bridges(&Pipes);
					Update_Grid();
					Recast_Machines();
					Bake_Lights();
					Find_Effect();
					return true;
				}
			}
		}
	}
	return false;
}

void Recast_Machines() {
	Point Pos;
	for (Pos.X = 0; Pos.X < ktn_grid_size; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < ktn_grid_size; Pos.Y++) {
			Machine_Ptr Machine = Visual_To_Machine(Data.Visual_Grid[pt(Pos)]);
			if (!Machine) {
				continue;
			}
			if (ktn_stricmp(Machine->Index, "turbine_input")) {
				Data.Settings_Grid[pt(Pos)][3] = 0;
				Data.Settings_Grid[pt(Pos)][4] = 0;
				bool Chaining = true;
				Point Chain = Pos;
				int Rotation = Visual_To_Rotation(Data.Visual_Grid[pt(Pos)]);
				while (Chaining) {
					switch (Rotation) {
					case 0:
						(Chain.Y - 3 >= 0) ? (Chain.Y -= 3) : (Chaining = false);
						break;
					case 1:
						(Chain.X + 3 < ktn_grid_size) ? (Chain.X += 3) : (Chaining = false);
						break;
					case 2:
						(Chain.Y + 3 < ktn_grid_size) ? (Chain.Y += 3) : (Chaining = false);
						break;
					case 3:
						(Chain.X - 3 >= 0) ? (Chain.X -= 3) : (Chaining = false);
						break;
					default:
						break;
					}
					Machine_Ptr Machine2 = Visual_To_Machine(Data.Visual_Grid[pt(Chain)]);
					if (!Chaining || !Machine2) {
						break;
					}
					if (ktn_stricmp(Machine2->Index, "turbine_impulse")) {
						if (Rotation == Visual_To_Rotation(Data.Visual_Grid[pt(Chain)])) {
							Data.Settings_Grid[pt(Pos)][3]++;
							Data.Settings_Grid[pt(Chain)][3] = 1;
						} else {
							Chaining = false;
						}
					}
					Point End_Pos = Chain;
					switch (Rotation) {
					case 0:
						End_Pos.Y -= 2;
						break;
					case 1:
						End_Pos.X += 3;
						break;
					case 2:
						End_Pos.Y += 3;
						break;
					case 3:
						End_Pos.X -= 2;
						break;
					default:
						break;
					}
					if (End_Pos.X < 0 || End_Pos.Y < 0 || End_Pos.X >= ktn_grid_size || End_Pos.Y >= ktn_grid_size) {
						Chaining = false;
					}
					Machine2 = Visual_To_Machine(Data.Visual_Grid[pt(End_Pos)]);
					if (Machine2 && ktn_stricmp(Machine2->Index, "turbine_output") &&
						Rotation == Visual_To_Rotation(Data.Visual_Grid[pt(End_Pos)])) {
						Data.Settings_Grid[pt(Pos)][4] = 1;
						Data.Settings_Grid[pt(End_Pos)][3] = 1;
						Data.Settings_Grid[pt(Pos)][5] = End_Pos.X;
						Data.Settings_Grid[pt(Pos)][6] = End_Pos.Y;
						Chaining = false;
					}
				}
			}
		}
	}
}

void Bake_Light(Point Pos) {
	Machine_Ptr Chosen = Visual_To_Machine(Data.Visual_Grid[pt(Pos)]);
	if (!Chosen) {
		return;
	}
	for (int C1 = 0; C1 < Chosen->Light_Ct; C1++) {
		Point Subpx = Rotate_Px(Chosen->Light_Pos[C1], (Point){ Chosen->Size.X * ktn_tile_size, Chosen->Size.Y * ktn_tile_size },
		Visual_To_Rotation(Data.Visual_Grid[pt(Pos)]));
		Point Subpos = { ktn_fscale((Pos.X * ktn_tile_size) + Subpx.X), ktn_fscale((Pos.Y * ktn_tile_size) + Subpx.Y) };
		int Rad = ktn_fscale(Chosen->Light_Range[C1]);
		for (int X = 0; X < 2; X++) {
			for (int Y = 0; Y < 2; Y++) {
				SDL_SetRenderTarget(Core.Renderer, Temporary.Lighting[(X * 2) + Y]);
				SDL_FRect Rect = { Subpos.X - Rad - (X * Temporary.Pixels), Subpos.Y - Rad - (Y * Temporary.Pixels), Rad * 2, Rad * 2 };
				Render_Texture(Cache.Light_Grad, &Rect);
			}
		}
	}
	ktn_reset_target();
	Clear_Renderer();
}

void Bake_Lights() {
	for (int C1 = 0; C1 < 4; C1++) {
		SDL_SetRenderTarget(Core.Renderer, Temporary.Lighting[C1]);
		SDL_SetTextureBlendMode(Temporary.Lighting[C1], SDL_BLENDMODE_NONE);
		SDL_SetRenderDrawColor(Core.Renderer, 0, 0, 0, 127);
		SDL_RenderClear(Core.Renderer);
	}
	Clear_Renderer();
	ktn_reset_target();
	for (int X = 0; X < ktn_grid_size; X++) {
		for (int Y = 0; Y < ktn_grid_size; Y++) {
			Bake_Light((Point){ X, Y });
		}
	}
	for (int C1 = 0; C1 < 4; C1++) {
		SDL_SetTextureBlendMode(Temporary.Lighting[C1], SDL_BLENDMODE_BLEND);
	}
}

int Get_Simple_Grid_Tile(int Grid[ktn_grid_size][ktn_grid_size], int Neutral) {
	for (int Column = 0; Column < ktn_grid_size; Column++) {
		Rects.Tile_1x1.x = ktn_fscale((Column * ktn_tile_size) - Core.Camera.X);
		for (int Row = 0; Row < ktn_grid_size; Row++) {
			Rects.Tile_1x1.y = ktn_fscale((Row * ktn_tile_size) - Core.Camera.Y);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				return Grid[Column][Row];
			}
		}
	}
	return Neutral;
}

void Find_Effect() {
	Interface.Effects[E_Heat] = 0;
	Interface.Effects[E_Radiation] = 0;
	Point Pos;
	for (Pos.X = 0; Pos.X < ktn_grid_size; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < ktn_grid_size; Pos.Y++) {
			Machine_Ptr Machine = Visual_To_Machine(Data.Visual_Grid[pt(Pos)]);
			if (!Machine) {
				continue;
			}
			if (Machine->Heating && Pos.X * ktn_tile_size > Core.Camera.X && Pos.Y * ktn_tile_size > Core.Camera.Y && Pos.X *
				ktn_tile_size < Core.Camera.X + 640.0f && Pos.Y * ktn_tile_size < Core.Camera.Y + 360.0f) {
				Interface.Effects[E_Heat] += 0.1f;
				return;
			}
			if (Machine->Irradiating) {
				float A = ktn_fscale((Core.Camera.X + 320.0f) - (Pos.X * ktn_tile_size));
				float B = ktn_fscale((Core.Camera.Y + 180.0f) - (Pos.Y * ktn_tile_size));
				float Distance = sqrtf(ktn_sqr(A) + ktn_sqr(B));
				Interface.Effects[E_Radiation] += fmaxf(35.0f - (Distance * 0.05f), 0.0f);
			}
		}
	}
}