#include <interface.h>

void Close_Prompt() {
	Interface.Prompt_Identifier = P_None;
	Interface.Subprompt_Identifier = LDE_INVALID;
}

void (*Prompt_Functions[12])(int X, int Y) = {
    Handle_None,
    Handle_Help,
    Handle_Shop,
    Handle_Daily_Report,
    Handle_Spawning_Pool,
    Handle_Transmitter,
    Handle_Dock,
    Handle_Exchanger,
    Handle_Money_Generator,
    Handle_Fluid_Generator,
    Handle_Catalog,
    Handle_Turbine
};

void Process_Inputs() {
	int X = Interface.Tile.X, Y = Interface.Tile.Y;
	SDL_Event Application_Event;
	while (SDL_PollEvent(&Application_Event)) {
		switch (Application_Event.type) {
		case SDL_EVENT_KEY_DOWN:
			if (!Interface.Locked) {
				Process_Tutorial(Application_Event.key.key);
				if (Interface.Prompt_Identifier == P_None) {
					switch (Interface.UI_Tab) {
					case LDE_INVALID:
						break;
					case 0:
						if (Application_Event.key.key == Keybinds.Keybind_List[4]) {
							if (Interface.Tool == 0) {
								Interface.Tool = LDE_INVALID;
							} else {
								Interface.Tool = 0;
								SDL_ShowCursor();
							}
							Interface.Rotation = 0;
							Cache_Blueprint();
							Clear_Unconnected_Wires();
							Clear_Unconnected_Pipes();
						} else if (Application_Event.key.key == Keybinds.Keybind_List[5]) {
							if (Interface.Tool == 1) {
								Interface.Tool = LDE_INVALID;
								SDL_ShowCursor();
							} else {
								Interface.Tool = 1;
								SDL_HideCursor();
							}
							Interface.Rotation = 0;
							Cache_Blueprint();
							Clear_Unconnected_Wires();
							Clear_Unconnected_Pipes();
						} else if (Application_Event.key.key == Keybinds.Keybind_List[6]) {
							if (Interface.Tool == 2) {
								Interface.Tool = LDE_INVALID;
								SDL_ShowCursor();
							} else {
								Interface.Tool = 2;
								SDL_HideCursor();
							}
							Interface.Rotation = 0;
							Cache_Blueprint();
							Clear_Unconnected_Wires();
							Clear_Unconnected_Pipes();
						} else if (Application_Event.key.key == Keybinds.Keybind_List[7]) {
							if (Interface.Tool == 3) {
								Interface.Tool = LDE_INVALID;
								SDL_ShowCursor();
							} else {
								Interface.Tool = 3;
								SDL_HideCursor();
							}
							Interface.Rotation = 0;
							Cache_Blueprint();
							Clear_Unconnected_Wires();
							Clear_Unconnected_Pipes();
						} else if (Application_Event.key.key == Keybinds.Keybind_List[8]) {
							if (Interface.Tool == 4) {
								Interface.Tool = LDE_INVALID;
								SDL_ShowCursor();
							} else {
								Interface.Tool = 4;
								SDL_HideCursor();
							}
							Interface.Rotation = 0;
							Cache_Blueprint();
							Clear_Unconnected_Wires();
							Clear_Unconnected_Pipes();
						} else if (Application_Event.key.key == Keybinds.Keybind_List[9]) {
							if (Interface.Tool == Building) {
								Interface.Prompt_Identifier = P_Shop;
								Interface.Building = false;
							}
						} else if (Application_Event.key.key == Keybinds.Keybind_List[10]) {
							if (Interface.Tool == No_Tool) {
								Render_Interaction();
							}
						} else if (Application_Event.key.key == Keybinds.Keybind_List[11]) {
							if (Interface.Tool == Building) {
								Interface.Rotation++;
								if (Interface.Rotation > 3) {
									Interface.Rotation = 0;
								}
								Cache_Blueprint();
							}
						} else if (Application_Event.key.key == Keybinds.Keybind_List[12]) {
							if (!Interface.Sprinting) {
								Interface.Sprinting = true;
							}
						} else if (Application_Event.key.key == Keybinds.Keybind_List[0]) {
							Interface.UD_Input = 0;
						} else if (Application_Event.key.key == Keybinds.Keybind_List[1]) {
							Interface.UD_Input = 1;
						} else if (Application_Event.key.key == Keybinds.Keybind_List[2]) {
							Interface.LR_Input = 0;
						} else if (Application_Event.key.key == Keybinds.Keybind_List[3]) {
							Interface.LR_Input = 1;
						}
						break;
					case 3:
						if (Interface.Registering_Keybind != LDE_INVALID) {
							Keybinds.Keybind_Settings[Interface.Registering_Keybind] = Application_Event.key.key;
							Interface.Registering_Keybind = LDE_INVALID;
						}
						break;
					default:
						break;
					}
				} else if (Interface.Prompt_Identifier == P_Help) {
					if (Application_Event.key.key == Keybinds.Keybind_List[13]) {
						Close_Prompt();
					}
				} else if (Interface.Prompt_Identifier == P_Shop) {
					if (Application_Event.key.key == Keybinds.Keybind_List[9]) {
						Close_Prompt();
						Interface.Subtab = 0;
					}
				} else {
					if (Application_Event.key.key == Keybinds.Keybind_List[10]) {
						Close_Prompt();
						Interface.Terminal_Length = 0;
					}
				}
			}
			break;
		case SDL_EVENT_KEY_UP:
			if (Interface.UI_Tab == 0 && !Interface.Locked) {
				if (Application_Event.key.key == Keybinds.Keybind_List[0] ||
					Application_Event.key.key == Keybinds.Keybind_List[1]) {
					Interface.UD_Input = LDE_INVALID;
				}
				if (Application_Event.key.key == Keybinds.Keybind_List[2] ||
					Application_Event.key.key == Keybinds.Keybind_List[3]) {
					Interface.LR_Input = LDE_INVALID;
				}
				if (Application_Event.key.key == Keybinds.Keybind_List[12] && Interface.Sprinting) {
					Interface.Sprinting = false;
				}
			}
			break;
		case SDL_EVENT_MOUSE_WHEEL:
			if (Interface.UI_Tab == 4 || Interface.UI_Tab == 5) {
				int Log = Changelog;
				if (Interface.UI_Tab == 5) {
					if (Interface.Slider_Positions[2] == 0) {
						Log = Credits;
					} else {
						Log = Legal;
					}
				}
				if (Application_Event.wheel.y > 0) {
					if (Interface.Log_Offset > 0) {
						Interface.Log_Offset = max(Interface.Log_Offset - (Settings.Screen_Size * 32), 0.0f);
					}
				} else if (Application_Event.wheel.y < 0) {
					if (Interface.Log_Offset < Interface.Log_Heights[Log]) {
						Interface.Log_Offset = min(Interface.Log_Offset + (Settings.Screen_Size * 32),
							Interface.Log_Heights[Log]);
					}
				}
				Temporary.Scroll_Percent = (float)((Interface.Log_Offset / Interface.Log_Heights[Log]) * 100);
			}
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (Interface.UI_Tab == 0) {
				if (Interface.Prompt_Identifier == P_None && Interface.Engagement == 0) {
					Interface.Building = false;
				} else if (Interface.Engagement > 0) {
					switch (Interface.Prompt_Identifier) {
					case P_Spawning_Pool:
						Print_Input();
						if (Data.Settings_Grid[X][Y][5] > 0) {
							Print_Error(Fish_Present);
							Interface.Slider_Positions[1] = (int)(Data.Settings_Grid[X][Y][6]);
						} else {
							Data.Settings_Grid[X][Y][6] = Interface.Slider_Positions[1];
							char Buffer[64];
							snprintf(Buffer, sizeof(Buffer), "set fish type to %s", Interface.Slider_Texts[1][
								Interface.Slider_Positions[1]]);
							Print_Response(Buffer);
						}
						break;
					case P_Exchanger:
						Print_Input();
						if (Interface.Engagement == 2) {
							Data.Settings_Grid[X][Y][3] = Interface.Valve300_Postions[Interface.Slider_Positions[7]];
							char Buffer[64];
							snprintf(Buffer, sizeof(Buffer), "set primary valve to %iL/s", (int)Data.Settings_Grid[X][Y][3]);
							Print_Response(Buffer);
						} else {
							Data.Settings_Grid[X][Y][4] = Interface.Valve300_Postions[Interface.Slider_Positions[13]];
							char Buffer[64];
							snprintf(Buffer, sizeof(Buffer), "set feedwater valve to %iL/s", (int)Data.Settings_Grid[X][Y][4]);
							Print_Response(Buffer);
						}
						break;
					default:
						break;
					}
				}
			}
			if (Interface.Engagement > 0) {
				Interface.Engagement = 0;
			}			
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (!Interface.Locked) {
				if (Application_Event.button.button == SDL_BUTTON_LEFT) {
					if (Interface.UI_Tab == 0) {
						Process_Tutorial(Interface.UI_Selection);
					}
					Prompt_Functions[Interface.Prompt_Identifier + 1](X, Y);
					if (Interface.UI_Selection > 0 && Interface.Engagement == 0) {
						Play_Sound(&Audio.Click, false);
					}
				} else if (Application_Event.button.button == SDL_BUTTON_RIGHT) {
					if (Interface.Prompt_Identifier == LDE_INVALID && Interface.Tool == 0) {
						Point Coordinates = { LDE_INVALID, LDE_INVALID };
						for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
							Rects.Tile_1x1.x = (int)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size);
							for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
								Rects.Tile_1x1.y = (int)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size);
								if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
									if (Data.Visual_Grid[Column][Row] != 0) {
										if (Data.Visual_Grid[Column][Row] == LDE_INVALID) {
											Coordinates = (Point){
												(int)(Data.Settings_Grid[Column][Row][1]),
												(int)(Data.Settings_Grid[Column][Row][2])
											};
										} else {
											Coordinates = (Point){ Column, Row };
										}
									}
								}
							}
						}
						if (Coordinates.X != LDE_INVALID) {
							Interface.Item = Visual_To_ID(Data.Visual_Grid[Coordinates.X][Coordinates.Y]) + 1;
							Cache_Price();
							Cache_Blueprint();
							Interface.Building = false;
						}
					}
				}
			}
			break;
		case SDL_EVENT_QUIT:
			Core.Is_Running = false;
			break;
		default:
			break;
		}
	}
	Interface.UI_Selection = 0;
}