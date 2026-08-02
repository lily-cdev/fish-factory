#include <tutorials.h>

Tutorial_Step Tutorial_Stack[256] = { };

void Progress_Tutorial() {
	Temporary.Tutorial_Step++;
	int Limiter = 0;
	while (Tutorial_Stack[Limiter].Type != T_Terminator) {
		Limiter++;
	}
	if (Temporary.Tutorial_Step >= Limiter) {
		memset(Tutorial_Stack, 0, sizeof(Tutorial_Stack));
		Temporary.Tutorial_Step = ktn_invalid;
	}
}

void Process_Tutorial(int Input) {
	if (Temporary.Tutorial_Step > ktn_invalid) {
		bool Step_Completed = false;
		if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 0 && Input != ktn_invalid) {
			if ((SDL_Keycode)(Input) == Keybinds.Keybind_List[Tutorial_Stack[Temporary.Tutorial_Step].Hotkey]) {
				Step_Completed = true;
			}
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == T_Button && Input == ktn_invalid) {
			if (ktn_stricmp(Temporary.Tutorial_Selection, Tutorial_Stack[Temporary.Tutorial_Step].Subselection)) {
				Step_Completed = true;
			}
			memset(Temporary.Tutorial_Selection, 0, sizeof(Temporary.Tutorial_Selection));
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 5 && Input == ktn_invalid) {
			if (Tutorial_Stack[Temporary.Tutorial_Step].Hotkey < Tutorial_Stack[Temporary.Tutorial_Step].Selection) {
				Tutorial_Stack[Temporary.Tutorial_Step].Hotkey++;
			} else {
				Step_Completed = true;
			}
		}
		if (Step_Completed) {
			Progress_Tutorial();
		}
	}
	memset(Temporary.Tutorial_Selection, 0, sizeof(Temporary.Tutorial_Selection));
}

void Render_Tutorial() {
	if (Temporary.Tutorial_Step == ktn_invalid) {
		return;
	}
	SDL_FRect Bounding_Rectangle = {
		ktn_fscale((120.0f - Core.Camera.X) + Temporary.Tutorial_Offset.X),
		ktn_fscale((120.0f - Core.Camera.Y) + Temporary.Tutorial_Offset.Y),
		ktn_fscale(Temporary.Tutorial_Size.X),
		ktn_fscale(Temporary.Tutorial_Size.Y)
	};
	Cache.ID_Query[Cache.Query_Length] = 0;
	Cache.Query[Cache.Query_Length] = Bounding_Rectangle;
	Cache.Color_Query[Cache.Query_Length] = Colors.Pure_White;
	Cache.Query_Length++;
	Render_Box((Point){ 140, 20 }, 360, 30, Colors.Light_Grey, Colors.Dark_Grey);
	char Text[128];
	char Carrier[128];
	snprintf(Text, sizeof(Text), "step %i: ", Temporary.Tutorial_Step + 1);
	Tutorial_Step Step = Tutorial_Stack[Temporary.Tutorial_Step];
	if (Step.Type == 0) {
		char Keycore[32];
		strncpy(Keycore, SDL_GetKeyName(Keybinds.Keybind_List[Step.Hotkey]), sizeof(
			Keycore));
		snprintf(Carrier, sizeof(Carrier), "press \"%s\" (%s).", Keycore, Keybinds.Keybind_Texts[Step.Hotkey]);
		strcat(Text, Carrier);
	} else if (Step.Type == 1) {
		snprintf(Carrier, sizeof(Carrier), "click on the \"%s\" button.", Step.Label);
		strcat(Text, Carrier);
	} else if (Step.Type == 2) {
		int Remaining = 0;
		for (int C1 = 0; C1 < ktn_ptlen(Step.Placement_Locations); C1++) {
			if (Step.ID_Override) {
				Machine_Ptr Highlighted = Visual_To_Machine(Data.Visual_Grid[pt(Step.Placement_Locations[C1])]);
				if (Highlighted && ktn_stricmp(Highlighted->Index, Step.ID_Override->Index)) {
					continue;
				}
			} else {
				if (Data.Visual_Grid[pt(Step.Placement_Locations[C1])] == Step.Item) {
					continue;
				}
			}
			int X;
			int Y;
			ID_To_Size((Step.ID_Override) ? Get_Machine(Step.ID_Override->Index) : Visual_To_Machine(Step.Item), 0, &X, &Y);
			SDL_FRect Outline_Rectangle = {
				ktn_fscale((Step.Placement_Locations[C1].X * ktn_tile_size) - Core.Camera.X),
				ktn_fscale((Step.Placement_Locations[C1].Y * ktn_tile_size) - Core.Camera.Y),
				ktn_fscale(X * ktn_tile_size),
				ktn_fscale(Y * ktn_tile_size)
			};
			Cache.ID_Query[Cache.Query_Length] = 0;
			Cache.Query[Cache.Query_Length] = Outline_Rectangle;
			Cache.Color_Query[Cache.Query_Length] = Colors.Carnage_Pink;
			Cache.Query_Length++;
			Remaining++;
		}
		char Suffix[4] = "s ";
		if (Remaining == 1) {
			strncpy(Suffix, " ", sizeof(Suffix));
		}
		if (Step.Item == 0 && !Step.ID_Override) {
			snprintf(Carrier, sizeof(Carrier), "remove the %i machine%sshown.", Remaining, Suffix);
			strcat(Text, Carrier);
		} else {
			char Subcore[64];
			if (Step.ID_Override) {
				strncpy(Subcore, Step.ID_Override->Name, sizeof(Subcore));
			} else {
				strncpy(Subcore, Visual_To_Machine(Step.Item)->Name, sizeof(Subcore));
			}
			snprintf(Carrier, sizeof(Carrier), "place %ix %s in the space%sshown.", Remaining, Subcore, Suffix);
			strcat(Text, Carrier);
		}
		if (Remaining == 0) {
			Progress_Tutorial();
		}
	} else if (Step.Type == 3 || Step.Type == 4) {
		int Remaining = 0;
		for (int C1 = 0; C1 < ktn_ptlen(Step.Placement_Locations);
			C1 += 2) {
			bool Incomplete = true;
			if (Step.Type == 3) {
				for (int C2 = 0; C2 < Pipes.Length; C2++) {
					if (Pipes.Data[C2].X1 == Step.Placement_Locations[C1].X && Pipes.Data[C2].Y1 == Step.Placement_Locations[
						C1].Y && Pipes.Data[C2].X2 == Step.Placement_Locations[C1 + 1].X && Pipes.Data[C2].Y2 ==
						Step.Placement_Locations[C1 + 1].Y) {
						Incomplete = false;
					}
				}
			} else {
				for (int C2 = 0; C2 < Wires.Length; C2++) {
					if (Wires.Data[C2].X1 == Step.Placement_Locations[C1].X && Wires.Data[C2].Y1 == Step.Placement_Locations[
						C1].Y && Wires.Data[C2].X2 == Step.Placement_Locations[C1 + 1].X && Wires.Data[C2].Y2 ==
						Step.Placement_Locations[C1 + 1].Y) {
						Incomplete = false;
					}
				}
			}
			if (Incomplete) {
				SDL_FRect Temporary_Rectangle = {
					ktn_fscale(Step.Placement_Locations[C1].X * ktn_tile_size) + ktn_fscale(20.0f - Core.Camera.X),
					ktn_fscale(Step.Placement_Locations[C1].Y * ktn_tile_size) + ktn_fscale(20.0f - Core.Camera.Y),
					ktn_fscale(Step.Placement_Locations[C1 + 1].X * ktn_tile_size) + ktn_fscale(20.0f - Core.Camera.X),
					ktn_fscale(Step.Placement_Locations[C1 + 1].Y * ktn_tile_size) + ktn_fscale(20.0f - Core.Camera.Y)
				};
				Cache.Query[Cache.Query_Length] = Temporary_Rectangle;
				Cache.ID_Query[Cache.Query_Length] = 1;
				Cache.Color_Query[Cache.Query_Length] = Colors.Carnage_Pink;
				Cache.Query_Length++;
				Remaining++;
			}
		}
		char Suffix[4] = "s ";
		if (Remaining == 1) {
			strncpy(Suffix, " ", sizeof(Suffix));
		}
		char Subcore[16] = "pipe";
		if (Step.Type == 4) {
			strncpy(Subcore, "wire", sizeof(Subcore));
		}
		snprintf(Carrier, sizeof(Carrier), "connect %i %s%sbetween the machine%sshown.", Remaining, Subcore, Suffix, Suffix);
		strcat(Text, Carrier);
		if (Remaining == 0) {
			Progress_Tutorial();
		}
	} else if (Step.Type == 5) {
		snprintf(Carrier, sizeof(Carrier), "wait for %i/%i seconds.", Step.Hotkey, Step.Selection);
		strcat(Text, Carrier);
	} else if (Step.Type == 6) {
		int Keybind = 0;
		float Position = 0;
		char Direction[16] = "up";
		Position = Core.Camera.Y;
		switch (Step.Hotkey) {
		case 1:
			Keybind = 2;
			strncpy(Direction, "left", sizeof(Direction));
			Position = Core.Camera.X;
			break;
		case 3:
			Keybind = 3;
			strncpy(Direction, "right", sizeof(Direction));
			Position = Core.Camera.X;
			break;
		case 4:
			Keybind = 1;
			strncpy(Direction, "down", sizeof(Direction));
			Position = Core.Camera.Y;
			break;
		default:
			break;
		}
		snprintf(Carrier, sizeof(Carrier), "hold down \"%c\" to drift the camera %i/%ipx %s.", (char)(tolower(
			SDL_GetKeyName(Keybinds.Keybind_List[Keybind])[0])), (int)Position, (int)Tutorial_Stack[
			Temporary.Tutorial_Step].Selection, Direction);
		strcat(Text, Carrier);
		if ((Position < Step.Selection && Keybind == 2) ||
			(Position < Step.Selection && Keybind == 0) ||
			(Position > Step.Selection && Keybind == 3) ||
			(Position > Step.Selection && Keybind == 1)) {
			Progress_Tutorial();
		}
	}
	if (Detect_Mouse_Collision((SDL_FRect){ Settings.Scalar * 170.0f, Settings.Scalar * 20.0f,
		Settings.Scalar * 300.0f, Settings.Scalar * 30.0f })) {
		char Buffer[128];
		snprintf(Buffer, sizeof(Buffer), "this will %s.", Step.Context);
		Process_Supply(&Supplies.Tutorial, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ ktn_invalid, 26 });
	} else {
		Process_Supply(&Supplies.Subtutorial, Text, F_Subtext, Colors.Abyss_Black, (Point){ ktn_invalid, 26 });
	}
}