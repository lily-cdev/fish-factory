#include <Core.h>

#include <Preloader.h>
#include <UI_Handler.h>
#include <Tutorial_Handler.h>


void Progress_Tutorial() {
	Temporary_Access.Tutorial_Step++;
	if (Temporary_Access.Tutorial_Step >= Tutorial_Stack.size()) {
		Tutorial_Stack.clear();
		Temporary_Access.Tutorial_Step = LDE_INVALID;
	}
}

void Process_Tutorial(int Input) {
	if (Temporary_Access.Tutorial_Step > LDE_INVALID) {
		bool Step_Completed = false;
		if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Type == 0 && Input != LDE_INVALID) {
			if (static_cast<SDL_Keycode>(Input) == Keybinds_Access.Keybind_List
				[Tutorial_Stack[Temporary_Access.Tutorial_Step].Hotkey]) {
				Step_Completed = true;
			}
		} else if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Type == 1 && Input != LDE_INVALID) {
			if (Input == Tutorial_Stack[Temporary_Access.Tutorial_Step].Selection) {
				Step_Completed = true;
			}
		} else if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Type == 5 && Input == LDE_INVALID) {
			if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Hotkey < Tutorial_Stack[Temporary_Access.Tutorial_Step].Selection) {
				Tutorial_Stack[Temporary_Access.Tutorial_Step].Hotkey++;
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
	if (Temporary_Access.Tutorial_Step > LDE_INVALID) {
		SDL_FRect Bounding_Rectangle = { (static_cast<float>(120 - UI_Access.Camera_X) + Temporary_Access.Tutorial_Offset[0]) *
			Settings_Access.Screen_Size, (static_cast<float>(120 - UI_Access.Camera_Y) + Temporary_Access.Tutorial_Offset[1]) *
			Settings_Access.Screen_Size, static_cast<float>(Temporary_Access.Tutorial_Size[0] * Settings_Access.Screen_Size),
			static_cast<float>(Temporary_Access.Tutorial_Size[1] * Settings_Access.Screen_Size) };
		Temporary_Access.ID_Query.push_back(0);
		Temporary_Access.Query.push_back(Bounding_Rectangle);
		Temporary_Access.Color_Query.push_back(Colors_Access.Pure_White);
		Render_Box(140, 20, 360, 30, Colors_Access.Light_Grey, Colors_Access.Dark_Grey);
		std::string Text = "Step " + std::to_string(Temporary_Access.Tutorial_Step + 1) + ": ";
		if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Type == 0) {
			std::string Keycore = SDL_GetKeyName(Keybinds_Access.Keybind_List[Tutorial_Stack[Temporary_Access.Tutorial_Step].Hotkey]);
			Text = Text + "Press \"" + Keycore + "\" (" + Keybinds_Access.Keybind_Texts
				[Tutorial_Stack[Temporary_Access.Tutorial_Step].Hotkey] + ").";
		} else if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Type == 1) {
			Text = Text + "Click on the \"" + Tutorial_Stack[Temporary_Access.Tutorial_Step].Label + "\" button.";
		} else if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Type == 2) {
			int Remaining = 0;
			for (int Counter = 0; Counter < Tutorial_Stack[Temporary_Access.Tutorial_Step]
				.Placement_Locations.size(); Counter++) {
				if ((Data_Access.Visual_Grid[Tutorial_Stack[Temporary_Access.Tutorial_Step]
					.Placement_Locations[Counter][0]][Tutorial_Stack[Temporary_Access.Tutorial_Step]
					.Placement_Locations[Counter][1]] != Tutorial_Stack[Temporary_Access.Tutorial_Step]
					.Item && !Tutorial_Stack[Temporary_Access.Tutorial_Step].ID_Override) || (Visual_To_ID(
					Data_Access.Visual_Grid[Tutorial_Stack[Temporary_Access.Tutorial_Step].Placement_Locations
					[Counter][0]][Tutorial_Stack[Temporary_Access.Tutorial_Step].Placement_Locations[
					Counter][1]]) != Tutorial_Stack[Temporary_Access.Tutorial_Step].Item && Tutorial_Stack[
					Temporary_Access.Tutorial_Step].ID_Override)) {
					int X;
					int Y;
					ID_To_Size(Visual_To_ID(Tutorial_Stack[Temporary_Access.Tutorial_Step].Item), 0, X, Y);
					SDL_FRect Outline_Rectangle = { static_cast<float>((Tutorial_Stack
						[Temporary_Access.Tutorial_Step].Placement_Locations[Counter][0] * 40 * Settings_Access.Screen_Size) -
						(UI_Access.Camera_X * Settings_Access.Screen_Size)), static_cast<float>((Tutorial_Stack
						[Temporary_Access.Tutorial_Step].Placement_Locations[Counter][1] * 40 *	Settings_Access.Screen_Size) -
						(UI_Access.Camera_Y * Settings_Access.Screen_Size)), static_cast<float>(X * 40 *
						Settings_Access.Screen_Size), static_cast<float>(Y * 40 * Settings_Access.Screen_Size) };
					Temporary_Access.ID_Query.push_back(0);
					Temporary_Access.Query.push_back(Outline_Rectangle);
					Temporary_Access.Color_Query.push_back(Colors_Access.Carnage_Pink);
					Remaining++;
				}
			}
			std::string Suffix = "s";
			if (Remaining == 1) {
				Suffix = "";
			}
			if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Item == 0 &&
				!Tutorial_Stack[Temporary_Access.Tutorial_Step].ID_Override) {
				Text = Text + "Remove the " + std::to_string(Remaining) + " machines shown.";
			} else {
				std::string Core = "";
				if (Tutorial_Stack[Temporary_Access.Tutorial_Step].ID_Override) {
					Core = Metadata_Access.Machine_Names[Tutorial_Stack[Temporary_Access.Tutorial_Step].Item];
				} else {
					Core = Metadata_Access.Machine_Names[Visual_To_ID(Tutorial_Stack[Temporary_Access.Tutorial_Step].Item)];
				}
				Text = Text + "Place " + std::to_string(Remaining) + "x " + Core + " in the space" + Suffix + " shown.";
			}
			if (Remaining == 0) {
				Progress_Tutorial();
			}
		} else if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Type == 3 ||
			Tutorial_Stack[Temporary_Access.Tutorial_Step].Type == 4) {
			int Remaining = 0;
			for (int First_Counter = 0; First_Counter < Tutorial_Stack
				[Temporary_Access.Tutorial_Step].Placement_Locations.size(); First_Counter += 2) {
				bool Incomplete = true;
				if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Type == 3) {
					for (int Second_Counter = 0; Second_Counter < Pipes_List.size(); Second_Counter++) {
						if (Pipes_List[Second_Counter].First_X == Tutorial_Stack[Temporary_Access.Tutorial_Step].Placement_Locations
							[First_Counter][0] && Pipes_List[Second_Counter].First_Y == Tutorial_Stack
							[Temporary_Access.Tutorial_Step].Placement_Locations[First_Counter][1] &&
							Pipes_List[Second_Counter].Second_X == Tutorial_Stack[Temporary_Access.Tutorial_Step].Placement_Locations
							[First_Counter + 1][0] && Pipes_List[Second_Counter].Second_Y == Tutorial_Stack
							[Temporary_Access.Tutorial_Step].Placement_Locations[First_Counter + 1][1]) {
							Incomplete = false;
						}
					}
				} else {
					for (int Second_Counter = 0; Second_Counter < Wires_List.size(); Second_Counter++) {
						if (Wires_List[Second_Counter].First_X == Tutorial_Stack[Temporary_Access.Tutorial_Step].Placement_Locations
							[First_Counter][0] && Wires_List[Second_Counter].First_Y == Tutorial_Stack
							[Temporary_Access.Tutorial_Step].Placement_Locations[First_Counter][1] &&
							Wires_List[Second_Counter].Second_X == Tutorial_Stack[Temporary_Access.Tutorial_Step].Placement_Locations
							[First_Counter + 1][0] && Wires_List[Second_Counter].Second_Y == Tutorial_Stack
							[Temporary_Access.Tutorial_Step].Placement_Locations[First_Counter + 1][1]) {
							Incomplete = false;
						}
					}
				}
				if (Incomplete) {
					SDL_FRect Temporary_Rectangle = { static_cast<float>((Tutorial_Stack
						[Temporary_Access.Tutorial_Step].Placement_Locations[First_Counter][0] * Settings_Access.Screen_Size *
						40) + ((20 - UI_Access.Camera_X) * Settings_Access.Screen_Size)), static_cast<float>((Tutorial_Stack
						[Temporary_Access.Tutorial_Step].Placement_Locations[First_Counter][1] * Settings_Access.Screen_Size * 40) +
						((20 - UI_Access.Camera_Y) * Settings_Access.Screen_Size)), static_cast<float>((Tutorial_Stack
						[Temporary_Access.Tutorial_Step].Placement_Locations[First_Counter + 1][0] * Settings_Access.Screen_Size *
						40) + ((20 - UI_Access.Camera_X) * Settings_Access.Screen_Size)), static_cast<float>((Tutorial_Stack
						[Temporary_Access.Tutorial_Step].Placement_Locations[First_Counter + 1][1] * Settings_Access.Screen_Size *
						40) + ((20 - UI_Access.Camera_Y) * Settings_Access.Screen_Size)) };
					Temporary_Access.Query.push_back(Temporary_Rectangle);
					Temporary_Access.ID_Query.push_back(1);
					Temporary_Access.Color_Query.push_back(Colors_Access.Carnage_Pink);
					Remaining++;
				}
			}
			std::string Suffix = "s";
			if (Remaining == 1) {
				Suffix = "";
			}
			std::string Core = "pipe";
			if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Type == 4) {
				Core = "wire";
			}
			Text = Text + "Connect " + std::to_string(Remaining) + " " + Core + Suffix + " between the machine" + Suffix + " shown.";
			if (Remaining == 0) {
				Progress_Tutorial();
			}
		} else if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Type == 5) {
			Text = Text + "Wait for " + std::to_string(Tutorial_Stack[Temporary_Access.Tutorial_Step].Hotkey) + "/" +
				std::to_string(Tutorial_Stack[Temporary_Access.Tutorial_Step].Selection) + " seconds.";
		} else if (Tutorial_Stack[Temporary_Access.Tutorial_Step].Type == 6) {
			int Keybind = 0;
			double Position = 0;
			std::string Direction = "up";
			Position = UI_Access.Camera_Y;
			switch (Tutorial_Stack[Temporary_Access.Tutorial_Step].Hotkey) {
			case 1:
				Keybind = 2;
				Direction = "left";
				Position = UI_Access.Camera_X;
				break;
			case 3:
				Keybind = 3;
				Direction = "right";
				Position = UI_Access.Camera_X;
				break;
			case 4:
				Keybind = 1;
				Direction = "down";
				Position = UI_Access.Camera_Y;
				break;
			default:
				break;
			}
			Text = Text + "Hold down \"" + static_cast<char>(std::tolower(SDL_GetKeyName(Keybinds_Access.Keybind_List[Keybind])
				[0])) + "\" to drift the camera " + std::to_string(static_cast<int>(Position)) + "/" + std::to_string(
				static_cast<int>(Tutorial_Stack[Temporary_Access.Tutorial_Step].Selection)) + "px " + Direction + ".";
			if ((Position < Tutorial_Stack[Temporary_Access.Tutorial_Step].Selection && Keybind == 2) ||
				(Position < Tutorial_Stack[Temporary_Access.Tutorial_Step].Selection && Keybind == 0) ||
				(Position > Tutorial_Stack[Temporary_Access.Tutorial_Step].Selection && Keybind == 3) ||
				(Position > Tutorial_Stack[Temporary_Access.Tutorial_Step].Selection && Keybind == 1)) {
				Progress_Tutorial();
			}
		}
		if (Detect_Mouse_Collision({ 170.0f * Settings_Access.Screen_Size, 20.0f * Settings_Access.Screen_Size,
			300.0f * Settings_Access.Screen_Size, 30.0f * Settings_Access.Screen_Size })) {
			Render_Dynamic_Text(Fonts_Access.Subtext_Font, "This will " + Tutorial_Stack[Temporary_Access.Tutorial_Step].Context +
				".", Colors_Access.Abyss_Black, LDE_INVALID, 26);
		} else {
			Render_Dynamic_Text(Fonts_Access.Subtext_Font, Text, Colors_Access.Abyss_Black, LDE_INVALID, 26);
		}
	}
}

std::vector<Tutorial_Step> Tutorial_Stack = { };