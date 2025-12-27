#include <Tutorial_Handler.h>

void Progress_Tutorial() {
	Temporary.Tutorial_Step++;
	if (Temporary.Tutorial_Step >= Tutorial_Stack.size()) {
		Tutorial_Stack.clear();
		Temporary.Tutorial_Step = LDE_INVALID;
	}
}

void Process_Tutorial(int Input) {
	if (Temporary.Tutorial_Step > LDE_INVALID) {
		bool Step_Completed = false;
		if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 0 && Input != LDE_INVALID) {
			if (static_cast<SDL_Keycode>(Input) == Keybinds_L.Keybind_List[
				 Tutorial_Stack[Temporary.Tutorial_Step].Hotkey]) {
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
		SDL_FRect Bounding_Rectangle = { (static_cast<float>(120 - Core.Camera.X) + Temporary.Tutorial_Offset.X) *
			Settings.Screen_Size, (static_cast<float>(120 - Core.Camera.Y) + Temporary.Tutorial_Offset.Y) *
			Settings.Screen_Size, static_cast<float>(Temporary.Tutorial_Size.X * Settings.Screen_Size),
			static_cast<float>(Temporary.Tutorial_Size.Y * Settings.Screen_Size) };
		Temporary_L.ID_Query.push_back(0);
		Temporary_L.Query.push_back(Bounding_Rectangle);
		Temporary_L.Color_Query.push_back(Colors.Pure_White);
		Render_Box(140, 20, 360, 30, Colors.Light_Grey, Colors.Dark_Grey);
		std::string Text = "Step " + std::to_string(Temporary.Tutorial_Step + 1) + ": ";
		if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 0) {
			std::string Keycore = SDL_GetKeyName(Keybinds_L.Keybind_List[Tutorial_Stack[
				Temporary.Tutorial_Step].Hotkey]);
			Text = Text + "Press \"" + Keycore + "\" (" + Keybinds_L.Keybind_Texts[
				Tutorial_Stack[Temporary.Tutorial_Step].Hotkey] + ").";
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 1) {
			Text = Text + "Click on the \"" + Tutorial_Stack[Temporary.Tutorial_Step].Label + "\" button.";
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 2) {
			int Remaining = 0;
			for (int Counter = 0; Counter < Tutorial_Stack[Temporary.Tutorial_Step]
				.Placement_Locations.size(); Counter++) {
				if ((Data.Visual_Grid[Tutorial_Stack[Temporary.Tutorial_Step]
					.Placement_Locations[Counter][0]][Tutorial_Stack[Temporary.Tutorial_Step]
					.Placement_Locations[Counter][1]] != Tutorial_Stack[Temporary.Tutorial_Step]
					.Item && !Tutorial_Stack[Temporary.Tutorial_Step].ID_Override) || (Visual_To_ID(
					Data.Visual_Grid[Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations
					[Counter][0]][Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations[
					Counter][1]]) != Tutorial_Stack[Temporary.Tutorial_Step].Item && Tutorial_Stack[
					Temporary.Tutorial_Step].ID_Override)) {
					int X;
					int Y;
					ID_To_Size(Visual_To_ID(Tutorial_Stack[Temporary.Tutorial_Step].Item), 0, &X, &Y);
					SDL_FRect Outline_Rectangle = { static_cast<float>((Tutorial_Stack
						[Temporary.Tutorial_Step].Placement_Locations[Counter][0] * LDE_TILESIZE * Settings.Screen_Size) -
						(Core.Camera.X * Settings.Screen_Size)), static_cast<float>((Tutorial_Stack
						[Temporary.Tutorial_Step].Placement_Locations[Counter][1] * LDE_TILESIZE * Settings.Screen_Size) -
						(Core.Camera.Y * Settings.Screen_Size)), static_cast<float>(X * LDE_TILESIZE *
						Settings.Screen_Size), static_cast<float>(Y * LDE_TILESIZE * Settings.Screen_Size) };
					Temporary_L.ID_Query.push_back(0);
					Temporary_L.Query.push_back(Outline_Rectangle);
					Temporary_L.Color_Query.push_back(Colors.Carnage_Pink);
					Remaining++;
				}
			}
			std::string Suffix = "s";
			if (Remaining == 1) {
				Suffix = "";
			}
			if (Tutorial_Stack[Temporary.Tutorial_Step].Item == 0 &&
				!Tutorial_Stack[Temporary.Tutorial_Step].ID_Override) {
				Text = Text + "Remove the " + std::to_string(Remaining) + " machines shown.";
			} else {
				std::string Subcore = "";
				if (Tutorial_Stack[Temporary.Tutorial_Step].ID_Override) {
					Subcore = Metadata_L.Machine_Names[Tutorial_Stack[Temporary.Tutorial_Step].Item];
				} else {
					Subcore = Metadata_L.Machine_Names[Visual_To_ID(
						Tutorial_Stack[Temporary.Tutorial_Step].Item)];
				}
				Text = Text + "Place " + std::to_string(Remaining) + "x " +
					Subcore + " in the space" + Suffix + " shown.";
			}
			if (Remaining == 0) {
				Progress_Tutorial();
			}
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 3 ||
			Tutorial_Stack[Temporary.Tutorial_Step].Type == 4) {
			int Remaining = 0;
			for (int Counter1 = 0; Counter1 < Tutorial_Stack
				[Temporary.Tutorial_Step].Placement_Locations.size(); Counter1 += 2) {
				bool Incomplete = true;
				if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 3) {
					for (int Counter2 = 0; Counter2 < Pipes_List.size(); Counter2++) {
						if (Pipes_List[Counter2].X1 == Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations
							[Counter1][0] && Pipes_List[Counter2].Y1 == Tutorial_Stack
							[Temporary.Tutorial_Step].Placement_Locations[Counter1][1] &&
							Pipes_List[Counter2].X2 == Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations
							[Counter1 + 1][0] && Pipes_List[Counter2].Y2 == Tutorial_Stack
							[Temporary.Tutorial_Step].Placement_Locations[Counter1 + 1][1]) {
							Incomplete = false;
						}
					}
				} else {
					for (int Counter2 = 0; Counter2 < Wires_List.size(); Counter2++) {
						if (Wires_List[Counter2].X1 == Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations
							[Counter1][0] && Wires_List[Counter2].Y1 == Tutorial_Stack
							[Temporary.Tutorial_Step].Placement_Locations[Counter1][1] &&
							Wires_List[Counter2].X2 == Tutorial_Stack[Temporary.Tutorial_Step].Placement_Locations
							[Counter1 + 1][0] && Wires_List[Counter2].Y2 == Tutorial_Stack
							[Temporary.Tutorial_Step].Placement_Locations[Counter1 + 1][1]) {
							Incomplete = false;
						}
					}
				}
				if (Incomplete) {
					SDL_FRect Temporary_Rectangle = { static_cast<float>((Tutorial_Stack
						[Temporary.Tutorial_Step].Placement_Locations[Counter1][0] * Settings.Screen_Size *
						40) + ((20 - Core.Camera.X) * Settings.Screen_Size)), static_cast<float>((Tutorial_Stack
						[Temporary.Tutorial_Step].Placement_Locations[Counter1][1] * Settings.Screen_Size * 40) +
						((20 - Core.Camera.Y) * Settings.Screen_Size)), static_cast<float>((Tutorial_Stack
						[Temporary.Tutorial_Step].Placement_Locations[Counter1 + 1][0] * Settings.Screen_Size *
						40) + ((20 - Core.Camera.X) * Settings.Screen_Size)), static_cast<float>((Tutorial_Stack
						[Temporary.Tutorial_Step].Placement_Locations[Counter1 + 1][1] * Settings.Screen_Size *
						40) + ((20 - Core.Camera.Y) * Settings.Screen_Size)) };
					Temporary_L.Query.push_back(Temporary_Rectangle);
					Temporary_L.ID_Query.push_back(1);
					Temporary_L.Color_Query.push_back(Colors.Carnage_Pink);
					Remaining++;
				}
			}
			std::string Suffix = "s";
			if (Remaining == 1) {
				Suffix = "";
			}
			std::string Core = "pipe";
			if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 4) {
				Core = "wire";
			}
			Text = Text + "Connect " + std::to_string(Remaining) + " " + Core +
				Suffix + " between the machine" + Suffix + " shown.";
			if (Remaining == 0) {
				Progress_Tutorial();
			}
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 5) {
			Text = Text + "Wait for " + std::to_string(Tutorial_Stack[Temporary.Tutorial_Step].Hotkey) + "/" +
				std::to_string(Tutorial_Stack[Temporary.Tutorial_Step].Selection) + " seconds.";
		} else if (Tutorial_Stack[Temporary.Tutorial_Step].Type == 6) {
			int Keybind = 0;
			double Position = 0;
			std::string Direction = "up";
			Position = Core.Camera.Y;
			switch (Tutorial_Stack[Temporary.Tutorial_Step].Hotkey) {
			case 1:
				Keybind = 2;
				Direction = "left";
				Position = Core.Camera.X;
				break;
			case 3:
				Keybind = 3;
				Direction = "right";
				Position = Core.Camera.X;
				break;
			case 4:
				Keybind = 1;
				Direction = "down";
				Position = Core.Camera.Y;
				break;
			default:
				break;
			}
			Text = Text + "Hold down \"" + static_cast<char>(std::tolower(
				SDL_GetKeyName(Keybinds_L.Keybind_List[Keybind])[
				0])) + "\" to drift the camera " + std::to_string(
				static_cast<int>(Position)) + "/" + std::to_string(
				static_cast<int>(Tutorial_Stack[Temporary.Tutorial_Step]
				.Selection)) + "px " + Direction + ".";
			if ((Position < Tutorial_Stack[Temporary.Tutorial_Step].Selection && Keybind == 2) ||
				(Position < Tutorial_Stack[Temporary.Tutorial_Step].Selection && Keybind == 0) ||
				(Position > Tutorial_Stack[Temporary.Tutorial_Step].Selection && Keybind == 3) ||
				(Position > Tutorial_Stack[Temporary.Tutorial_Step].Selection && Keybind == 1)) {
				Progress_Tutorial();
			}
		}
		if (Detect_Mouse_Collision({ 170.0f * Settings.Screen_Size, 20.0f * Settings.Screen_Size,
			300.0f * Settings.Screen_Size, 30.0f * Settings.Screen_Size })) {
			Render_Dynamic_Text(Fonts.Subtext_Font, "This will " + Tutorial_Stack[
				Temporary.Tutorial_Step].Context + ".", Colors.Abyss_Black, LDE_INVALID, 26);
		} else {
			Render_Dynamic_Text(Fonts.Subtext_Font, Text, Colors.Abyss_Black, LDE_INVALID, 26);
		}
	}
}

std::vector<Tutorial_Step> Tutorial_Stack = { };