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
		Temporary.Tutorial_Step = LDE_INVALID;
	}
}

void Process_Tutorial(int Input) {
	if (Temporary.Tutorial_Step > LDE_INVALID) {
		bool Step_Completed = false;
		if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 0 && Input != LDE_INVALID) {
			if ((SDL_Keycode)(Input) == Keybinds.Keybind_List[Tutorial_Stack[Temporary.Tutorial_Step].Hotkey]) {
				Step_Completed = true;
			}
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 1 && Input != LDE_INVALID) {
			if (Input == Tutorial_Stack[Temporary.Tutorial_Step].Selection) {
				Step_Completed = true;
			}
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 5 && Input == LDE_INVALID) {
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
}

void Render_Tutorial() {
	if (Temporary.Tutorial_Step > LDE_INVALID) {
		SDL_FRect Bounding_Rectangle = {
			((float)(120 - Core.Camera.X) + Temporary.Tutorial_Offset.X) * Settings.Screen_Size,
			((float)(120 - Core.Camera.Y) + Temporary.Tutorial_Offset.Y) * Settings.Screen_Size,
			(float)(Temporary.Tutorial_Size.X * Settings.Screen_Size),
			(float)(Temporary.Tutorial_Size.Y * Settings.Screen_Size)
		};
		Cache.ID_Query[Cache.Query_Length] = 0;
		Cache.Query[Cache.Query_Length] = Bounding_Rectangle;
		Cache.Color_Query[Cache.Query_Length] = Colors.Pure_White;
		Cache.Query_Length++;
		Render_Box(140, 20, 360, 30, Colors.Light_Grey, Colors.Dark_Grey);
        char Text[128];
		char Carrier[128];
		snprintf(Text, sizeof(Text), "Step %i: ", Temporary.Tutorial_Step + 1);
		if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 0) {
			char Keycore[32];
			strncpy(Keycore, SDL_GetKeyName(Keybinds.Keybind_List[Tutorial_Stack[Temporary.Tutorial_Step].Hotkey]), sizeof(
				Keycore));
			snprintf(Carrier, sizeof(Carrier), "Press \"%s\" (%s).", Keycore, Keybinds.Keybind_Texts[Tutorial_Stack[
				Temporary.Tutorial_Step].Hotkey]);
			strcat_c(Text, Carrier, sizeof(Text));
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 1) {
			snprintf(Carrier, sizeof(Carrier), "Click on the \"%s\" button.", Tutorial_Stack[Temporary.Tutorial_Step].Label);
			strcat_c(Text, Carrier, sizeof(Text));
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 2) {
			int Remaining = 0;
			for (int C1 = 0; C1 < ptlen(Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations); C1++) {
				if ((Data.Visual_Grid[Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[C1].X][
					Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[C1].Y] != Tutorial_Stack[
					Temporary.Tutorial_Step].Item && !Tutorial_Stack[Temporary.Tutorial_Step].ID_Override) ||
					(Visual_To_ID(Data.Visual_Grid[Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[
					C1].X][Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[C1].Y]) != Tutorial_Stack[
					Temporary.Tutorial_Step].Item && Tutorial_Stack[Temporary.Tutorial_Step].ID_Override)) {
					int X;
					int Y;
					ID_To_Size(Visual_To_ID(Tutorial_Stack[Temporary.Tutorial_Step].Item), 0, &X, &Y);
					SDL_FRect Outline_Rectangle = {
						(float)((Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[C1].X * LDE_TILESIZE *
						Settings.Screen_Size) - (Core.Camera.X * Settings.Screen_Size)),
						(float)((Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[C1].Y * LDE_TILESIZE *
							Settings.Screen_Size) - (Core.Camera.Y * Settings.Screen_Size)),
						(float)(X * LDE_TILESIZE * Settings.Screen_Size),
						(float)(Y * LDE_TILESIZE * Settings.Screen_Size)
					};
					Cache.ID_Query[Cache.Query_Length] = 0;
					Cache.Query[Cache.Query_Length] = Outline_Rectangle;
					Cache.Color_Query[Cache.Query_Length] = Colors.Carnage_Pink;
					Cache.Query_Length++;
					Remaining++;
				}
			}
			char Suffix[4] = "s ";
			if (Remaining == 1) {
				strncpy(Suffix, " ", sizeof(Suffix));
			}
			if (Tutorial_Stack[Temporary.Tutorial_Step].Item == 0 && !Tutorial_Stack[Temporary.Tutorial_Step].ID_Override) {
				snprintf(Carrier, sizeof(Carrier), "Remove the %i machine%sshown.", Remaining, Suffix);
				strcat_c(Text, Carrier, sizeof(Text));
			} else {
				char Subcore[64];
				if (Tutorial_Stack[Temporary.Tutorial_Step].ID_Override) {
					strncpy(Subcore, Metadata.Names[Tutorial_Stack[Temporary.Tutorial_Step].Item], sizeof(Subcore));
				} else {
					strncpy(Subcore, Metadata.Names[Visual_To_ID(Tutorial_Stack[Temporary.Tutorial_Step].Item)], sizeof(
						Subcore));
				}
				snprintf(Carrier, sizeof(Carrier), "Place %ix %s in the space%sshown.", Remaining, Subcore, Suffix);
				strcat_c(Text, Carrier, sizeof(Text));
			}
			if (Remaining == 0) {
				Progress_Tutorial();
			}
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 3 || Tutorial_Stack[Temporary.Tutorial_Step].Type == 4) {
			int Remaining = 0;
			for (int C1 = 0; C1 < ptlen(Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations);
				C1 += 2) {
				bool Incomplete = true;
				if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 3) {
					for (int C2 = 0; C2 < Pipes_List.Length; C2++) {
						if (Pipes_List.Data[C2].X1 == Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[
							C1].X && Pipes_List.Data[C2].Y1 == Tutorial_Stack[Temporary.Tutorial_Step]
							.Placement_Locations[C1].Y && Pipes_List.Data[C2].X2 == Tutorial_Stack[
							Temporary.Tutorial_Step].Placement_Locations[C1 + 1].X && Pipes_List.Data[C2].Y2 ==
							Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[C1 + 1].Y) {
							Incomplete = false;
						}
					}
				} else {
					for (int C2 = 0; C2 < Wires_List.Length; C2++) {
						if (Wires_List.Data[C2].X1 == Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[
							C1].X && Wires_List.Data[C2].Y1 == Tutorial_Stack[Temporary.Tutorial_Step]
							.Placement_Locations[C1].Y && Wires_List.Data[C2].X2 == Tutorial_Stack[
							Temporary.Tutorial_Step].Placement_Locations[C1 + 1].X && Wires_List.Data[C2].Y2 ==
							Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[C1 + 1].Y) {
							Incomplete = false;
						}
					}
				}
				if (Incomplete) {
					SDL_FRect Temporary_Rectangle = {
						(float)((Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[C1].X *
						Settings.Screen_Size * LDE_TILESIZE) + ((20 - Core.Camera.X) * Settings.Screen_Size)),
						(float)((Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[C1].Y *
						Settings.Screen_Size * LDE_TILESIZE) + ((20 - Core.Camera.Y) * Settings.Screen_Size)),
						(float)((Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[C1 + 1].X *
						Settings.Screen_Size * LDE_TILESIZE) + ((20 - Core.Camera.X) * Settings.Screen_Size)),
						(float)((Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[C1 + 1].Y *
						Settings.Screen_Size * LDE_TILESIZE) + ((20 - Core.Camera.Y) * Settings.Screen_Size))
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
			if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 4) {
				strncpy(Subcore, "wire", sizeof(Subcore));
			}
			snprintf(Carrier, sizeof(Carrier), "Connect %i %s%sbetween the machine%sshown.", Remaining, Subcore, Suffix,
				Suffix);
			strcat_c(Text, Carrier, sizeof(Text));
			if (Remaining == 0) {
				Progress_Tutorial();
			}
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 5) {
			snprintf(Carrier, sizeof(Carrier), "Wait for %i/%i seconds.", Tutorial_Stack[Temporary.Tutorial_Step].Hotkey,
				Tutorial_Stack[Temporary.Tutorial_Step].Selection);
			strcat_c(Text, Carrier, sizeof(Text));
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 6) {
			int Keybind = 0;
			float Position = 0;
			char Direction[16] = "up";
			Position = Core.Camera.Y;
			switch (Tutorial_Stack[Temporary.Tutorial_Step].Hotkey) {
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
			snprintf(Carrier, sizeof(Carrier), "Hold down \"%c\" to drift the camera %i/%ipx %s.", (char)(tolower(
				SDL_GetKeyName(Keybinds.Keybind_List[Keybind])[0])), (int)Position, (int)Tutorial_Stack[
				Temporary.Tutorial_Step].Selection, Direction);
			strcat_c(Text, Carrier, sizeof(Text));
			if ((Position < Tutorial_Stack[Temporary.Tutorial_Step].Selection && Keybind == 2) ||
				(Position < Tutorial_Stack[Temporary.Tutorial_Step].Selection && Keybind == 0) ||
				(Position > Tutorial_Stack[Temporary.Tutorial_Step].Selection && Keybind == 3) ||
				(Position > Tutorial_Stack[Temporary.Tutorial_Step].Selection && Keybind == 1)) {
				Progress_Tutorial();
			}
		}
		if (Detect_Mouse_Collision((SDL_FRect){ Settings.Screen_Size * 170.0f, Settings.Screen_Size * 20.0f,
			Settings.Screen_Size * 300.0f, Settings.Screen_Size * 30.0f })) {
			char Buffer[128];
			snprintf(Buffer, sizeof(Buffer), "This will %s.", Tutorial_Stack[Temporary.Tutorial_Step].Context);
			Process_Supply(&Supplies.Tutorial, Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, LDE_INVALID, 26);
		} else {
			Process_Supply(&Supplies.Subtutorial, Text, Fonts.Subtext_Font, Colors.Abyss_Black, LDE_INVALID, 26);
		}
	}
}