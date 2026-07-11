#include <interface.h>

void Close_Prompt() {
	Interface.Prompt_Identifier = P_None;
	Interface.Subprompt_Identifier = ktn_invalid;
	Temporary.Ticker_Frames = 0;
	Temporary.Ticker_Position = 0;
	Temporary.Ticker_Target = 0;
	memset(Interface.Terminal_Logs, 0, ktn_log_max * ktn_param_max);
	Interface.Terminal_Length = 0;
	Temporary.Ticker_Position = 0;
	Temporary.Ticker_Frames = 0;
}

void Update_Cursor() {
	(Interface.Tool == T_None || Interface.Tool == T_Building) ? SDL_ShowCursor() : SDL_HideCursor();
}

void (*Prompt_Functions[13])(Point Pos) = {
    Handle_None,
    Handle_Help,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    Handle_Catalog,
    NULL,
	NULL
};

void Process_Inputs() {
	Point Pos = Interface.Tile;
	SDL_Event Application_Event;
	while (SDL_PollEvent(&Application_Event)) {
		switch (Application_Event.type) {
		case SDL_EVENT_KEY_DOWN:
			if (!Interface.Locked) {
				Process_Tutorial(Application_Event.key.key);
				if (Interface.Prompt_Identifier == P_None) {
					switch (Interface.UI_Tab) {
					case ktn_invalid:
						break;
					case 0:
						for (int C1 = T_Building; C1 <= T_Plumbing; C1++) {
							if (Application_Event.key.key == Keybinds.Keybind_List[C1 + 4]) {
								Interface.Tool = (Interface.Tool == C1) ? T_None : C1;
								Interface.Rotation = 0;
								Update_Cursor();
								Cache_Blueprint();
								Clear_Unconnected_Bridges(&Wires);
								Clear_Unconnected_Bridges(&Pipes);
								Update_Grid();
							}
						}
						if (Application_Event.key.key == Keybinds.Keybind_List[9]) {
							if (Interface.Tool == T_Building) {
								Interface.Prompt_Identifier = P_Shop;
								Interface.Building = false;
							}
						} else if (Application_Event.key.key == Keybinds.Keybind_List[10]) {
							if (Interface.Tool == T_None) {
								Render_Interaction();
							}
						} else if (Application_Event.key.key == Keybinds.Keybind_List[11]) {
							if (Interface.Tool == T_Building) {
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
						if (Interface.Registering_Keybind != ktn_invalid) {
							Keybinds.Keybind_Settings[Interface.Registering_Keybind] = Application_Event.key.key;
							Interface.Registering_Keybind = ktn_invalid;
						}
						break;
					default:
						break;
					}
				} else {
					if (Application_Event.key.key == Keybinds.Keybind_List[13] || Application_Event.key.key ==
						Keybinds.Keybind_List[10]) {
						Close_Prompt();
						Interface.Terminal_Length = 0;
					}
					if (Interface.Prompt_Identifier == P_Shop) {
						if (Application_Event.key.key == Keybinds.Keybind_List[9]) {
							Close_Prompt();
							Interface.Subtab = 0;
						}
					}
				}
			}
			break;
		case SDL_EVENT_KEY_UP:
			if (Interface.UI_Tab == 0 && !Interface.Locked) {
				if (Application_Event.key.key == Keybinds.Keybind_List[0] || Application_Event.key.key ==
					Keybinds.Keybind_List[1]) {
					Interface.UD_Input = ktn_invalid;
				}
				if (Application_Event.key.key == Keybinds.Keybind_List[2] || Application_Event.key.key ==
					Keybinds.Keybind_List[3]) {
					Interface.LR_Input = ktn_invalid;
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
					Log = (Interface.Slider_Positions[2] == 0) ? Credits : Legal;
				}
				if (Application_Event.wheel.y > 0) {
					if (Interface.Log_Offset > 0) {
						Interface.Log_Offset = max(Interface.Log_Offset - (Settings.Scalar * 32), 0.0f);
					}
				} else if (Application_Event.wheel.y < 0) {
					if (Interface.Log_Offset < Interface.Log_Heights[Log]) {
						Interface.Log_Offset = min(Interface.Log_Offset + (Settings.Scalar * 32),
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
						int ID = Data.Settings_Grid[pt(Pos)][5];
						if (Fishlinks[ID].Fish_Ct > 0) {
							Print_Error(Fish_Present);
							Interface.Slider_Positions[1] = Fishlinks[ID].Type->Identifier;
						} else {
							Fishlinks[ID].Type = Get_Fish(Interface.Slider_Positions[1]);
							char Buffer[64];
							snprintf(Buffer, sizeof(Buffer), "set fish type to %s", Interface.Slider_Texts[1][Interface.Slider_Positions[
								1]]);
							Print_Response(Buffer);
						}
						break;
					case P_Exchanger:
						Print_Input();
						if (Interface.Engagement == 2) {
							Data.Settings_Grid[pt(Pos)][3] = Interface.Valve300_Postions[Interface.Slider_Positions[7]];
							char Buffer[64];
							snprintf(Buffer, sizeof(Buffer), "set primary valve to %i%s/s", (int)Data.Settings_Grid[pt(Pos)][3],
								ktn_unit);
							Print_Response(Buffer);
						} else {
							Data.Settings_Grid[pt(Pos)][4] = Interface.Valve300_Postions[Interface.Slider_Positions[13]];
							char Buffer[64];
							snprintf(Buffer, sizeof(Buffer), "set feedwater valve to %i%s/s", (int)Data.Settings_Grid[pt(Pos)][4],
								ktn_unit);
							Print_Response(Buffer);
						}
						break;
					default:
						break;
					}
				}
			}
			if (Interface.Engagement != 0) {
				Interface.Engagement = 0;
			}			
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (!Interface.Locked) {
				if (Application_Event.button.button == SDL_BUTTON_LEFT) {
					//forward essentials
					if (Interface.Engagement == 0) {
						if (Interface.UI_Query.Carrier) {
							Interface.UI_Query.Carrier(Interface.UI_Query.Param, Interface.UI_Query.Param2);
							Play_Sound(Click, false);
						} else {
							if (Interface.Bar_Up) {
								if (Interface.UI_Selection >= T_Building && Interface.UI_Selection <= T_Plumbing) {
									Interface.Tool = Interface.UI_Selection;
									Update_Cursor();//mov
								}
							} else {
								if (Prompt_Functions[Interface.Prompt_Identifier + 1]) {
									Prompt_Functions[Interface.Prompt_Identifier + 1](Pos);//rem
								}
							}
						}
						if (Interface.UI_Tab == 0) {
							Process_Tutorial(ktn_invalid);
						}
					} else {
						Interface.Engagement = 0;
					}		
				} else if (Application_Event.button.button == SDL_BUTTON_RIGHT) {
					if (Interface.Prompt_Identifier == P_None && Interface.Tool == T_Building) {
						Point Coordinates = { ktn_invalid, ktn_invalid };
						for (int Column = 0; Column < ktn_grid_size; Column++) {
							Rects.Tile_1x1.x = ktn_fscale((Column * ktn_tile_size) - Core.Camera.X);
							for (int Row = 0; Row < ktn_grid_size; Row++) {
								Rects.Tile_1x1.y = ktn_fscale((Row * ktn_tile_size) - Core.Camera.Y);
								if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
									if (Data.Visual_Grid[Column][Row] != 0) {
										if (Data.Visual_Grid[Column][Row] == ktn_invalid) {
											Coordinates = (Point){
												(int)(Data.Settings_Grid[Column][Row][S_ParentX]),
												(int)(Data.Settings_Grid[Column][Row][S_ParentY])
											};
										} else {
											Coordinates = (Point){ Column, Row };
										}
									}
								}
							}
						}
						if (Coordinates.X != ktn_invalid) {
							Interface.Item = Visual_To_Machine(Data.Visual_Grid[pt(Coordinates)]);
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