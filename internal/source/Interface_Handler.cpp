#include <Core.h>
#include <Preloader.h>
#include <Items.h>
#include <Connectables.h>
#include <Interface_Handler.h>
#include <Data_Handler.h>
#include <Transition_Handler.h>
#include <UI_Handler.h>
#include <Tutorial_Handler.h>
#include <Terminal_Handler.h>

void Close_Prompt() {
	UI_Access.Prompt_Identifier = LDE_INVALID;
	UI_Access.Subprompt_Identifier = LDE_INVALID;
}

void Process_Inputs() {
	int X = UI_Access.Target_Tile.X;
	int Y = UI_Access.Target_Tile.Y;
	SDL_Event Application_Event;
	while (SDL_PollEvent(&Application_Event)) {
		switch (Application_Event.type) {
		case SDL_EVENT_KEY_DOWN:
			if (!UI_Access.Animation_Locked) {
				Process_Tutorial(Application_Event.key.key);
				if (UI_Access.Prompt_Identifier == LDE_INVALID) {
					switch (UI_Access.UI_Tab) {
					case LDE_INVALID:
						break;
					case 0:
						if (Application_Event.key.key == Keybinds_Access.Keybind_List[4]) {
							if (UI_Access.Tool == 0) {
								UI_Access.Tool = LDE_INVALID;
							} else {
								UI_Access.Tool = 0;
								SDL_ShowCursor();
							}
							UI_Access.Placing_Rotation = 0;
							Cache_Blueprint();
							Clear_Unconnected_Wires();
							Clear_Unconnected_Pipes();
						} else if (Application_Event.key.key == Keybinds_Access.Keybind_List[5]) {
							if (UI_Access.Tool == 1) {
								UI_Access.Tool = LDE_INVALID;
								SDL_ShowCursor();
							} else {
								UI_Access.Tool = 1;
								SDL_HideCursor();
							}
							UI_Access.Placing_Rotation = 0;
							Cache_Blueprint();
							Clear_Unconnected_Wires();
							Clear_Unconnected_Pipes();
						} else if (Application_Event.key.key == Keybinds_Access.Keybind_List[6]) {
							if (UI_Access.Tool == 2) {
								UI_Access.Tool = LDE_INVALID;
								SDL_ShowCursor();
							} else {
								UI_Access.Tool = 2;
								SDL_HideCursor();
							}
							UI_Access.Placing_Rotation = 0;
							Cache_Blueprint();
							Clear_Unconnected_Wires();
							Clear_Unconnected_Pipes();
						} else if (Application_Event.key.key == Keybinds_Access.Keybind_List[7]) {
							if (UI_Access.Tool == 3) {
								UI_Access.Tool = LDE_INVALID;
								SDL_ShowCursor();
							} else {
								UI_Access.Tool = 3;
								SDL_HideCursor();
							}
							UI_Access.Placing_Rotation = 0;
							Cache_Blueprint();
							Clear_Unconnected_Wires();
							Clear_Unconnected_Pipes();
						} else if (Application_Event.key.key == Keybinds_Access.Keybind_List[8]) {
							if (UI_Access.Tool == 4) {
								UI_Access.Tool = LDE_INVALID;
								SDL_ShowCursor();
							} else {
								UI_Access.Tool = 4;
								SDL_HideCursor();
							}
							UI_Access.Placing_Rotation = 0;
							Cache_Blueprint();
							Clear_Unconnected_Wires();
							Clear_Unconnected_Pipes();
						} else if (Application_Event.key.key == Keybinds_Access.Keybind_List[9]) {
							if (UI_Access.Tool == Building) {
								UI_Access.Prompt_Identifier = 1;
								UI_Access.Building = false;
							}
						} else if (Application_Event.key.key == Keybinds_Access.Keybind_List[10]) {
							if (UI_Access.Tool == No_Tool) {
								Render_Interaction();
							}
						} else if (Application_Event.key.key == Keybinds_Access.Keybind_List[11]) {
							if (UI_Access.Tool == Building) {
								UI_Access.Placing_Rotation++;
								if (UI_Access.Placing_Rotation > 3) {
									UI_Access.Placing_Rotation = 0;
								}
								Cache_Blueprint();
							}
						} else if (Application_Event.key.key == Keybinds_Access.Keybind_List[12]) {
							if (!UI_Access.Sprinting) {
								UI_Access.Sprinting = true;
							}
						} else if (Application_Event.key.key == Keybinds_Access.Keybind_List[0]) {
							UI_Access.UD_Input = 0;
						} else if (Application_Event.key.key == Keybinds_Access.Keybind_List[1]) {
							UI_Access.UD_Input = 1;
						} else if (Application_Event.key.key == Keybinds_Access.Keybind_List[2]) {
							UI_Access.LR_Input = 0;
						} else if (Application_Event.key.key == Keybinds_Access.Keybind_List[3]) {
							UI_Access.LR_Input = 1;
						}
						break;
					case 3:
						if (UI_Access.Registering_Keybind != LDE_INVALID) {
							Keybinds_Access.Keybind_Settings[UI_Access.Registering_Keybind] =
								Application_Event.key.key;
							UI_Access.Registering_Keybind = LDE_INVALID;
						}
						break;
					default:
						break;
					}
				} else if (UI_Access.Prompt_Identifier == 0) {
					if (Application_Event.key.key == Keybinds_Access.Keybind_List[13]) {
						Close_Prompt();
					}
				} else if (UI_Access.Prompt_Identifier == 1) {
					if (Application_Event.key.key == Keybinds_Access.Keybind_List[9]) {
						Close_Prompt();
						UI_Access.Subtab = 0;
					}
				} else if (UI_Access.Prompt_Identifier > 2 || UI_Access.Prompt_Identifier < 6) {
					if (Application_Event.key.key == Keybinds_Access.Keybind_List[10]) {
						Close_Prompt();
						UI_Access.Terminal_Logs.clear();
						Temporary_Access.Dialogue_Position = 0;
					}
				}
			}
			break;
		case SDL_EVENT_KEY_UP:
			if (UI_Access.UI_Tab == 0 && !UI_Access.Animation_Locked) {
				if (Application_Event.key.key == Keybinds_Access.Keybind_List[0] ||
					Application_Event.key.key == Keybinds_Access.Keybind_List[1]) {
					UI_Access.UD_Input = LDE_INVALID;
				}
				if (Application_Event.key.key == Keybinds_Access.Keybind_List[2] ||
					Application_Event.key.key == Keybinds_Access.Keybind_List[3]) {
					UI_Access.LR_Input = LDE_INVALID;
				}
				if (Application_Event.key.key == Keybinds_Access.Keybind_List[12] && UI_Access.Sprinting) {
					UI_Access.Sprinting = false;
				}
			}
			break;
		case SDL_EVENT_MOUSE_WHEEL:
			if (UI_Access.UI_Tab == 4 || UI_Access.UI_Tab == 5) {
				int Log = Changelog;
				if (UI_Access.UI_Tab == 5) {
					if (UI_Access.Slider_Positions[2] == 0) {
						Log = Credits;
					} else {
						Log = Legal;
					}
				}
				if (Application_Event.wheel.y > 0) {
					if (UI_Access.Log_Offset > 0) {
						UI_Access.Log_Offset = std::max(UI_Access.Log_Offset - (32 * Settings_Access.Screen_Size),
							static_cast<long double>(0));
					}
				} else if (Application_Event.wheel.y < 0) {
					if (UI_Access.Log_Offset < UI_Access.Log_Heights[Log]) {
						UI_Access.Log_Offset = std::min(UI_Access.Log_Offset + (32 * Settings_Access.Screen_Size),
							UI_Access.Log_Heights[Log]);
					}
				}
				Temporary_Access.Scroll_Percent = static_cast<double>((
					UI_Access.Log_Offset / UI_Access.Log_Heights[Log]) * 100);
			}
			break;
		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (UI_Access.UI_Tab == 0) {
				if (UI_Access.Prompt_Identifier == LDE_INVALID && UI_Access.Engagement == 0) {
					UI_Access.Building = false;
				} else if (UI_Access.Engagement > 0) {
					switch (UI_Access.Prompt_Identifier) {
					case 3:
						Print_Input();
						if (Data_Access.Settings_Grid[X][Y][5] > 0) {
							Print_Error(Fish_Present);
							UI_Access.Slider_Positions[1] = static_cast<int>(Data_Access.Settings_Grid
								[X][Y][6]);
						} else {
							Data_Access.Settings_Grid[X][Y][6] =
								UI_Access.Slider_Positions[1];
							Print_Response("set fish type to " + UI_Access.Slider_Texts[1][UI_Access.Slider_Positions[1]]);
						}
						break;
					case 6:
						Print_Input();
						if (UI_Access.Engagement == 2) {
							Data_Access.Settings_Grid[X][Y][3] =
								UI_Access.Valve300_Postions[UI_Access.Slider_Positions[7]];
							Print_Response("set primary valve to " + std::to_string(static_cast<int>(
								Data_Access.Settings_Grid[X]
								[Y][3])) + "L/s");
						} else {
							Data_Access.Settings_Grid[X][Y][4] =
								UI_Access.Valve300_Postions[UI_Access.Slider_Positions[13]];
							Print_Response("set feedwater valve to " + std::to_string(static_cast<int>(
								Data_Access.Settings_Grid[X]
								[Y][4])) + "L/s");
						}
						break;
					default:
						break;
					}
				}
			}
			if (UI_Access.Engagement > 0) {
				UI_Access.Engagement = 0;
			}			
			break;
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (!UI_Access.Animation_Locked) {
				if (Application_Event.button.button == SDL_BUTTON_LEFT) {
					if (UI_Access.UI_Tab == 0) {
						Process_Tutorial(UI_Access.UI_Selection);
					}
					if (UI_Access.Prompt_Identifier == LDE_INVALID) {
						switch (UI_Access.UI_Tab) {
						case 0:
							switch (UI_Access.UI_Selection) {
							case 0:
								if (UI_Access.Tool == Building) {
									UI_Access.Building = true;
								} else if (UI_Access.Tool == Deleting) {
									Destroy_Grid();
									Update_Grid();
								} else if (UI_Access.Tool == Wiring) {
									Place_Wire();
								} else if (UI_Access.Tool == Plumbing) {
									Place_Pipe();
								}
								break;
							case 1:
								UI_Access.Prompt_Identifier = 0;
								break;
							case 2:
								if (UI_Access.Save_Frames < 1) {
									UI_Access.Save_Frames = UI_Access.Frame_Rate * 2;
									Save_Data(Core_Access.Selected_Save);
								}
								break;
							case 3:
								UI_Access.Prompt_Identifier = 9;
								break;
							case 4:
								if (UI_Access.Tool == Building) {
									UI_Access.Placing_Rotation = 0;
									Clear_Unconnected_Wires();
									Clear_Unconnected_Pipes();
									Cache_Blueprint();
								}
								if (UI_Access.Tool == LDE_INVALID) {
									Save_Data(Core_Access.Selected_Save);
									Tutorial_Stack.clear();
									Temporary_Access.Tutorial_Step = LDE_INVALID;
									Start_Transition(2);
									Core_Access.Selected_Save = LDE_INVALID;
									Get_Filesizes();
									UI_Access.Placing_Item = 1;
									Cache_Blueprint();
								} else {
									if (UI_Access.Tool < 4) {
										UI_Access.Tool++;
									} else {
										UI_Access.Tool = 0;
									}
								}
								break;
							case 5:
								if (UI_Access.Tool == 0) {
									UI_Access.Placing_Rotation = 0;
									Clear_Unconnected_Wires();
									Clear_Unconnected_Pipes();
									Cache_Blueprint();
								}
								if (UI_Access.Tool > 0) {
									UI_Access.Tool--;
								} else {
									UI_Access.Tool = 4;
								}
								break;
							default:
								break;
							}
							break;
						case 1:
							switch (UI_Access.UI_Selection) {
							case 1:
								Start_Transition(2);
								Core_Access.Selected_Save = LDE_INVALID;
								Get_Filesizes();
								break;
							case 2:
								Start_Transition(3);
								break;
							case 3:
								Start_Transition(4);
								break;
							case 4:
								Start_Transition(5);
								break;
							case 5:
								Core_Access.Is_Running = false;
								break;
							default:
								break;
							}
							break;
						case 2:
							if (UI_Access.UI_Selection == 1) {
								Start_Transition(1);
							} else if (UI_Access.UI_Selection > 1 && UI_Access.UI_Selection < 6) {
								Core_Access.Selected_Save = UI_Access.UI_Selection - 1;
								Reset_Statistics();
								Find_Effect();
								Start_Transition(0);
								Restore_Cache();
								Cache_Price();
								Cache_Blueprint();
								Cache_Access.Wire_State = Deep_Recache;
							} else if (UI_Access.UI_Selection > 5 && UI_Access.UI_Selection < 10) {
								Core_Access.Selected_Save = UI_Access.UI_Selection - 5;
								if (Load_Data(UI_Access.UI_Selection - 5)) {
									Save_Data(UI_Access.UI_Selection - 5);
									Find_Effect();
									Restore_Cache();
									Cache_Access.Wire_State = Deep_Recache;
								}
								Start_Transition(0);
								Cache_Price();
								Cache_Blueprint();
							} else if (UI_Access.UI_Selection > 9 && UI_Access.UI_Selection < 14) {
								Clear_File("Assets/Data/Slot" + std::to_string(UI_Access.UI_Selection - 9));
								Get_Filesizes();
							}
							break;
						case 3:
							if (UI_Access.Engagement == 0 && UI_Access.Registering_Keybind == LDE_INVALID) {
								if (UI_Access.UI_Selection == 1) {
									Start_Transition(1);
								} else if (UI_Access.UI_Selection == 2) {
									Recalibrate_Settings();
									Temporary_Access.Settings_Changed = true;
								} else if (UI_Access.UI_Selection == 3) {
									Clear_Settings();
								} else if (UI_Access.UI_Selection == 4) {
									UI_Access.Engagement = 1;
								} else if (UI_Access.UI_Selection == 5) {
									Settings_Access.AA_Temporary = !Settings_Access.AA_Temporary;
								} else if (UI_Access.UI_Selection > 5 && UI_Access.UI_Selection < 20) {
									UI_Access.Registering_Keybind = UI_Access.UI_Selection - 6;
								} else if (UI_Access.UI_Selection == 20) {
									UI_Access.Engagement = 2;
								} else if (UI_Access.UI_Selection == 21) {
									UI_Access.Engagement = 3;
								} else if (UI_Access.UI_Selection == 22) {
									UI_Access.Engagement = 4;
								} else if (UI_Access.UI_Selection == 23) {
									if (Save_Settings()) {
										Temporary_Access.Settings_Changed = false;
									}
								} else if (UI_Access.UI_Selection == 24) {
									Settings_Access.VS_Temporary = !Settings_Access.VS_Temporary;
								}
							} else {
								UI_Access.Engagement = 0;
							}
							break;
						case 4:
							switch (UI_Access.UI_Selection) {
							case 1:
								Start_Transition(1);
								break;
							case 2:
								Temporary_Access.Log_Inversions[Changelog] = !Temporary_Access.Log_Inversions[Changelog];
								Reload_All();
								break;
							case 3:
								Temporary_Access.Scroll_Percent = 100;
								UI_Access.Log_Offset = UI_Access.Log_Heights[Changelog];
								break;
							case 4:
								Temporary_Access.Scroll_Percent = 0;
								UI_Access.Log_Offset = 0;
								break;
							}
							break;
						case 5:
							if (UI_Access.Engagement == 0) {
								switch (UI_Access.UI_Selection) {
								case 1:
									Start_Transition(1);
									break;
								case 2:
									UI_Access.Engagement = 1;
									break;
								default:
									break;
								}
							} else {
								UI_Access.Engagement = 0;
							}
							break;
						default:
							break;
						}
					} else if (UI_Access.Prompt_Identifier == 0) {
						if (UI_Access.Engagement == 0) {
							if (UI_Access.UI_Selection == 1) {
								UI_Access.Engagement = 1;
							}
							switch (UI_Access.Slider_Positions[3]) {
							case 1:
								if (UI_Access.UI_Selection > 2 && UI_Access.UI_Selection < 5) {
									Temporary_Access.Tutorial_Step = 0;
									Close_Prompt();
								}
								switch (UI_Access.UI_Selection) {
								case 2:
									Tutorial_Stack.clear();
									Temporary_Access.Tutorial_Step = LDE_INVALID;
									break;
								case 3:
									Tutorial_Stack = {
										Tutorial_Step{ 0, 4, 0, "", 0, { }, false, "enable the build tool" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
										Tutorial_Step{ 1, 0, 10, "Special", 0, { }, false, "open the \"Special\" category" },
										Tutorial_Step{ 1, 0, 3, "Command Platform", 0, { }, false,
											"select the \"Command Platform\" item" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
										Tutorial_Step{ 6, 4, 200, "", 0, { }, false, "put the placement site into view" },
										Tutorial_Step{ 2, 0, 0, "", 43, { { 3, 8 } }, false, "allow time to progress" },
										Tutorial_Step{ 0, 4, 0, "", 0, { }, false, "disable the build tool" }
									};
									Temporary_Access.Tutorial_Size = { 320, 240 };
									Temporary_Access.Tutorial_Offset = { 0, 200 };
									break;
								case 4:
									Tutorial_Stack = {
										Tutorial_Step{ 0, 4, 0, "", 0, { }, false, "enable the build tool" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
										Tutorial_Step{ 1, 0, 4, "Extraction", 0, { }, false, "open the \"Extraction\" category" },
										Tutorial_Step{ 1, 0, 3, "Ram Pump", 0, { }, false, "select the \"Ram Pump\" item" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
										Tutorial_Step{ 2, 0, 0, "", 17, { { 4, 5 }, { 3, 6 }, { 4, 7 } }, false,
											"pump in water for the Filtration Plant" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
										Tutorial_Step{ 1, 0, 6, "Processing", 0, { }, false, "open the \"Processing\" category" },
										Tutorial_Step{ 1, 0, 3, "Filtration Plant", 0, { }, false,
											"select the \"Filtration Plant\" item" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
										Tutorial_Step{ 2, 0, 0, "", 22, { { 5, 5 } }, false, "filter water into fuel" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
										Tutorial_Step{ 1, 0, 9, "Other", 0, { }, false, "open the \"Other\" category" },
										Tutorial_Step{ 1, 0, 3, "Incinerator", 0, { }, false, "select the \"Incinerator\" item" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
										Tutorial_Step{ 2, 0, 0, "", 18, { { 7, 5 }, { 7, 7 } }, false,
											"dispose of unwanted byproducts" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
										Tutorial_Step{ 1, 0, 7, "Generation", 0, { }, false, "open the \"Generation\" category" },
										Tutorial_Step{ 1, 0, 4, "Compact Firebox", 0, { }, false,
											"select the \"Compact Firebox\" item" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
										Tutorial_Step{ 2, 0, 0, "", 23, { { 8, 3 } }, false, "burn fuel for electricity" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
										Tutorial_Step{ 1, 0, 3, "Logistics", 0, { }, false, "open the \"Logistics\" category" },
										Tutorial_Step{ 1, 0, 3, "Reinforced Pipe", 0, { }, false,
											"select the \"Reinforced Pipe\" item" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
										Tutorial_Step{ 2, 0, 0, "", 0, { { 4, 6 }, { 7, 6 }, { 8, 6 } }, true,
											"transport fluids between machines" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
										Tutorial_Step{ 1, 0, 3, "Logistics", 0, { }, false, "open the \"Logistics\" category" },
										Tutorial_Step{ 1, 0, 5, "Cable Node", 0, { }, false, "select the \"Cable Node\" item" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
										Tutorial_Step{ 2, 0, 0, "", 63, { { 8, 7 } }, false, "transport power between machines" },
										Tutorial_Step{ 0, 8, 0, "", 0, { }, false, "enable the plumbing tool" },
										Tutorial_Step{ 3, 0, 0, "", 0, { { 4, 7 }, { 4, 6 }, { 4, 5 }, { 4, 6 }, { 3, 6 }, { 4, 6 },
											{ 6, 6 }, { 7, 6 }, { 7, 6 }, { 8, 6 }, { 4, 6 }, { 5, 6 }, { 6, 5 }, { 7, 5 }, { 6, 7 },
											{ 7, 7 }, { 8, 6 }, { 8, 5 } }, false, "allow fluids to flow" },
										Tutorial_Step{ 0, 7, 0, "", 0, { }, false, "enable the wiring tool" },
										Tutorial_Step{ 4, 0, 0, "", 0, { { 8, 7 }, { 3, 6 }, { 8, 7 }, { 4, 5 }, { 8, 7 }, { 4, 7 },
											{ 8, 7 }, { 5, 5 } }, false, "allow power to be distributed" },
										Tutorial_Step{ 0, 4, 0, "", 0, { }, false, "enable the build tool" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "open the catalog" },
										Tutorial_Step{ 1, 0, 7, "Generation", 0, { }, false,
											"open the \"Generation\" category" },
										Tutorial_Step{ 1, 0, 3, "Piezoelectric Generator", 0, { }, false,
											"select the \"Piezoelectric Generator\" item" },
										Tutorial_Step{ 0, 9, 0, "", 0, { }, false, "close the catalog" },
										Tutorial_Step{ 2, 0, 0, "", 19, { { 3, 3 }, { 4, 3 },
											{ 5, 3 }, { 6, 3 }, { 7, 3 }, { 3, 4 },
											{ 4, 4 }, { 5, 4 }, { 6, 4 }, { 7, 4 } }, false,
											"generate a temporary supply of power" },
										Tutorial_Step{ 0, 7, 0, "", 0, { }, false, "enable the wiring tool" },
										Tutorial_Step{ 4, 0, 0, "", 0, { { 3, 3 }, { 8, 7 }, { 4, 3 }, { 8, 7 }, { 5, 3 }, { 8, 7 },
										{ 6, 3 }, { 8, 7 }, { 7, 3 }, { 8, 7 }, { 3, 4 }, { 8, 7 }, { 4, 4 }, { 8, 7 }, { 5, 4 },
										{ 8, 7 }, { 6, 4 }, { 8, 7 }, { 7, 4 }, { 8, 7 } }, false, "jumpstart the setup" },
										Tutorial_Step{ 5, 0, 60, "", 0, { }, false, "allow the first cycle to begin" },
										Tutorial_Step{ 0, 5, 0, "", 0, { }, false, "enable the delete tool" },
										Tutorial_Step{ 2, 0, 0, "", 0, { { 3, 3 }, { 4, 3 }, { 5, 3 }, { 6, 3 }, { 7, 3 }, { 3, 4 },
										{ 4, 4 }, { 5, 4 }, { 6, 4 }, { 7, 4 } }, false, "remove the jumpstarting equipment" },
										Tutorial_Step{ 0, 7, 0, "", 0, { }, false, "enable the wiring tool" },
										Tutorial_Step{ 4, 0, 0, "", 0, { { 8, 3 }, { 8, 7 } }, false,
											"make the setup self-sustaining" },
										Tutorial_Step{ 0, 7, 0, "", 0, { }, false, "disable the wiring tool" }
									};
									Temporary_Access.Tutorial_Size = { 320, 200 };
									Temporary_Access.Tutorial_Offset = { 0, 0 };
									break;
								case 5:
									Temporary_Access.Tutorial_Step = LDE_INVALID;
									//here
									break;
								default:
									break;
								}
								break;
							case 2:
								switch (UI_Access.UI_Selection) {
								case 2:
									UI_Access.Placing_Item = Money_Generator + 1;
									break;
								case 3:
									UI_Access.Placing_Item = Fluid_Generator + 1;
									break;
								default:
									break;
								}
								if (UI_Access.UI_Selection > 1 && UI_Access.UI_Selection < 4) {
									UI_Access.Tool = Building;
									Close_Prompt();
									Cache_Blueprint();
									Cache_Price();
								}
								break;
							default:
								break;
							}
						} else {
							UI_Access.Engagement = 0;
						}
					} else if (UI_Access.Prompt_Identifier == 1) {
						if (UI_Access.Subtab == 0) {
							if (UI_Access.UI_Selection > 2 && UI_Access.UI_Selection < 11) {
								UI_Access.Subtab = UI_Access.UI_Selection - 2;
							}
						} else if (UI_Access.Subtab > 0) {
							if (UI_Access.Subtab < 9) {
								if (UI_Access.UI_Selection > 2) {
									if (UI_Access.UI_Selection > Metadata_Access.Subcategory_Positions
										[UI_Access.Subtab - 1].size() + 2) {
										UI_Access.Placing_Item = Metadata_Access.Item_Labels
											[UI_Access.Subtab - 1][UI_Access.UI_Selection -
											Metadata_Access.Subcategory_Positions
											[UI_Access.Subtab - 1].size() - 3] + 1;
										Cache_Blueprint();
									} else {
										UI_Access.Subtab = Metadata_Access.Subcategory_Positions
											[UI_Access.Subtab - 1][UI_Access.UI_Selection - 3] + 9;
									}
								}
							} else if (UI_Access.UI_Selection > 2) {
								UI_Access.Placing_Item = Metadata_Access.Subcontents
									[UI_Access.Subtab - 9][UI_Access.UI_Selection - 3] + 1;
								Cache_Blueprint();
							}
						}
					} else if (UI_Access.Prompt_Identifier == 2) {
						if (UI_Access.UI_Selection == 1) {
							Close_Prompt();
							Data_Access.Time = 0;
							if (Data_Access.Day < 6) {
								Data_Access.Day++;
							} else {
								Data_Access.Day = 0;
							}
						}
					} else if (UI_Access.Prompt_Identifier == 3) {
						if (Data_Access.Settings_Grid[X][Y][3] > 3) {
							if (UI_Access.Engagement == 0) {
								Forward_Essentials(Rectangles_Access.MSP_Buttons.Length, 1);
								if (UI_Access.UI_Selection == 3) {
									Print_JSON({ "volume\", \"" + Abbreviate_Number(Data_Access.Settings_Grid[X]
										[Y][3] * 90) + "L", "food\", \"" + Abbreviate_Number(
										Data_Access.Settings_Grid[X][Y][4]) + "g" });
								} else if (UI_Access.UI_Selection == 4) {
									if (Data_Access.Settings_Grid[X][Y][5] > 0) {
										Print_JSON({ "type\", \"" + Fish_Catalog[static_cast<int>(Data_Access
											.Settings_Grid[X][Y][6])].Name + " " + Get_Phase_Name(
											static_cast<int>(Data_Access.Settings_Grid[X]
											[Y][6]), static_cast<int>(Data_Access.Settings_Grid
											[X][Y][7]), static_cast<int>(Data_Access.Settings_Grid[X][Y][5])),
											"quantity\", \"" + std::to_string(static_cast<int>(
											Data_Access.Settings_Grid[X][Y][5])) });
									} else {
										Print_Error(No_File);
									}
								} else if (UI_Access.UI_Selection == 5) {
									if (Data_Access.Settings_Grid[X][Y][5] > 0) {
										Print_Error(Fish_Present);
									} else {
										int Added_Fish = static_cast<int>(Data_Access
											.Settings_Grid[X][Y][3] * 1.125);
										Print_Response("added " + std::to_string(Added_Fish) + " fish");
										Data_Access.Settings_Grid[X][Y][5] = Added_Fish;
									}
								} else if (UI_Access.UI_Selection == 6) {
									if (Data_Access.Settings_Grid[X][Y][5] > 0) {
										Print_Response("released " + std::to_string(static_cast<int>(
											Data_Access.Settings_Grid[X][Y][5])) + " fish");
										Data_Access.Settings_Grid[X][Y][5] = 0;
										Data_Access.Settings_Grid[X][Y][7] = 0;
									} else {
										Print_Error(No_Fish);
									}
								} else if (UI_Access.UI_Selection == 9) {
									UI_Access.Engagement = 1;
								}
								Backward_Essentials();
							} else {
								UI_Access.Engagement = 0;
							}
						} else {
							Process_Exit();
						}
						Purge_Excess();
					} else if (UI_Access.Prompt_Identifier == 4) {
						Forward_Essentials(Rectangles_Access.TT_Buttons.Data[
							Temporary_Access.Dialogue_Position].Length, 0);
						switch (Temporary_Access.Dialogue_Position) {
						case 0:
							if (UI_Access.UI_Selection == 3) {
								Print_Response("input docking position");
								Temporary_Access.Dialogue_Position = 1;
							}
							break;
						case 1:
							if (UI_Access.UI_Selection == 3) {
								Print_Response("transmission disconnected");
								Temporary_Access.Dialogue_Position = 0;
							} else if (UI_Access.UI_Selection > 3 && UI_Access.UI_Selection <
								Temporary_Access.Docks.size() + 4) {
								if (Temporary_Access.Submarine_Position[0] == LDE_INVALID &&
									Temporary_Access.Submarine_Position[1] == LDE_INVALID) {
									Print_Response("submarine sent");
									for (int Counter = 0; Counter < 2; Counter++) {
										Temporary_Access.Submarine_Position[Counter] = Temporary_Access.Docks
											[UI_Access.UI_Selection - 4][Counter];
									}
									Temporary_Access.Submarine_Phase = 0;
									Temporary_Access.Submarine_Offset = 3000;
									Temporary_Access.Submarine_Vertical = 105;
								} else {
									Print_Error(Docked_Sub);
								}
							}
							break;
						default:
							break;
						}
						Backward_Essentials();
						Purge_Excess();
					} else if (UI_Access.Prompt_Identifier == 5) {
						Forward_Essentials(Rectangles_Access.SD_Buttons.Length, 0);
						if (UI_Access.UI_Selection == 3) {
							if (Temporary_Access.Submarine_Position[0] == X &&
								Temporary_Access.Submarine_Position[1] == Y &&
								Temporary_Access.Submarine_Phase == 2) {
								int Issues[2] = { 0, 0 };
								for (int Counter1 = 0; Counter1 < 2; Counter1++) {
									if (ID_To_Item(static_cast<int>(Data_Access.Settings_Grid[X]
										[Y][Counter1 + 5])).Value < 1 && Data_Access.Settings_Grid
										[X][Y][Counter1 + 5] != LDE_INVALID) {
										Issues[Counter1] = 1;
									}
									if (Data_Access.Settings_Grid[X][Y][Counter1 + 5] == LDE_INVALID) {
										Issues[Counter1] = 2;
									}
								}
								if (Issues[0] == 0 || Issues[1] == 0) {
									for (int Counter2 = 0; Counter2 < 2; Counter2++) {
										if (Issues[Counter2] == 0) {
											Data_Access.Funds += Data_Access.Settings_Grid[X]
												[Y][Counter2 + 3] * ID_To_Item(static_cast<int>(
												Data_Access.Settings_Grid[X][Y]
												[Counter2 + 5])).Sale_Value;
											Data_Access.Settings_Grid[X][Y][Counter2 + 3] = 0;
											Data_Access.Settings_Grid[X][Y][Counter2 + 5] = LDE_INVALID;
										}
									}
									Print_Response("Items sold");
									Temporary_Access.Submarine_Phase = 3;
								} else {
									int Errors[2] = { Low_Value, Empty_Target };
									for (int Counter2 = 0; Counter2 < 2; Counter2++) {
										Print_Error(Errors[Issues[Counter2] - 1]);
									}
								}
							} else {
								Print_Error(No_Docked_Sub);
							}
						} else if (UI_Access.UI_Selection == 4) {
							std::vector<std::string> JSON = { };
							for (int Counter1 = 0; Counter1 < 2; Counter1++) {
								std::string Carrier1 = "none";
								if (Data_Access.Settings_Grid[X][Y][Counter1 + 5] !=
									LDE_INVALID && ID_To_Item(static_cast<int>(
									Data_Access.Settings_Grid[X][Y][Counter1 + 5])).Value < 1) {
									Carrier1 = "low_value";
								}
								JSON.push_back("capacity_" + std::to_string(Counter1 + 1) + "\", \"" +
									Truncate(std::abs(Data_Access.Settings_Grid[X][Y][Counter1 + 3]),
									Get_Depth(LDE_DOCKCAPACITY)) + "/" + Abbreviate_Number(LDE_DOCKCAPACITY) + "L");
								JSON.push_back("flags_" + std::to_string(Counter1 + 1) + "\", \"" + Carrier1);
								std::string Carrier2 = "none";
								if (Data_Access.Settings_Grid[X][Y][Counter1 + 5] != LDE_INVALID) {
									Carrier2 = ID_To_Item(static_cast<int>(Data_Access.Settings_Grid[
										X][Y][Counter1 + 5])).Display_Name;
									for (int Counter2 = 0; Counter2 < Carrier2.size(); Counter2++) {
										Carrier2[Counter2] = static_cast<char>(std::tolower(Carrier2[Counter2]));
										if (Carrier2[Counter2] == ' ') {
											Carrier2[Counter2] = '_';
										}
									}
								}
								JSON.push_back("item_" + std::to_string(Counter1 + 1) + "\", \"" + Carrier2);
							}
							Print_JSON(JSON);
						} else if (UI_Access.UI_Selection == 5 || UI_Access.UI_Selection == 6) {
							Print_Response(Abbreviate_Number(Data_Access.Settings_Grid[X][
								Y][UI_Access.UI_Selection - 2]) + " liters drained from tank_" +
								std::to_string(UI_Access.UI_Selection - 4));
							Data_Access.Settings_Grid[X][Y][UI_Access.UI_Selection - 2] = 0;
							Data_Access.Settings_Grid[X][Y][UI_Access.UI_Selection] = LDE_INVALID;
						}
						Backward_Essentials();
						Purge_Excess();
					} else if (UI_Access.Prompt_Identifier == 6) {
						if (UI_Access.Engagement == 0) {
							std::string Position;
							Forward_Essentials(Rectangles_Access.HX_Buttons.Length, 2);
							switch (UI_Access.UI_Selection) {
							case 3:
								Print_JSON({
									"primary_valve\", \"" + std::to_string(static_cast<int>(
									Data_Access.Settings_Grid[X][Y][3])) + "L/s",
									"feedwater_valve\", \"" + std::to_string(static_cast<int>(
									Data_Access.Settings_Grid[X][Y][4])) + "L/s",
									"primary_loop\", \"" + Abbreviate_Number(Data_Access.Settings_Grid
										[X][Y][5]) + "/" + Truncate(LDE_HXCAPACITY, 0) + "L",
									"feedwater_loop\", \"" + Abbreviate_Number(Data_Access.Settings_Grid
										[X][Y][6]) + "/" + Truncate(LDE_HXCAPACITY, 0) + "L",
									"primary_temp\", \"" + Abbreviate_Number(Data_Access.Settings_Grid[
										X][Y][7]) + " °F", "feedwater_temp\", \"" + Abbreviate_Number(
										Data_Access.Settings_Grid[X][Y][8]) + " °F"
								});
								break;
							case 6:
								UI_Access.Engagement = 3;
								break;
							case 7:
								UI_Access.Engagement = 2;
								break;
							default:
								break;
							}
							Backward_Essentials();
						} else {
							UI_Access.Engagement = 0;
						}
						Purge_Excess();
					} else if (UI_Access.Prompt_Identifier == 7) {
						if (UI_Access.Engagement == 0) {
							switch (UI_Access.UI_Selection) {
							case 2:
								UI_Access.Engagement = 1;
								break;
							case 3:
								Data_Access.Settings_Grid[X][Y][3] = UI_Access.Slider_Positions[8];
								Data_Access.Settings_Grid[X][Y][4] = sgn(UI_Access.Slider_Positions[8] -
									5) * std::pow(1000, std::abs(UI_Access.Slider_Positions[8] - 5) - 1);
								break;
							case 4:
								UI_Access.Slider_Positions[8] = Data_Access.Settings_Grid[X][Y][3];
								break;
							default:
								break;
							}
						} else {
							UI_Access.Engagement = 0;
						}
					} else if (UI_Access.Prompt_Identifier == 8) {
						if (UI_Access.Engagement == 0) {
							if (UI_Access.UI_Selection > 1 && UI_Access.UI_Selection < 5) {
								UI_Access.Engagement = UI_Access.UI_Selection - 1;
							} else if (UI_Access.UI_Selection == 5) {
								Data_Access.Settings_Grid[X][Y][3] = UI_Access.Slider_Positions[9];
								Data_Access.Settings_Grid[X][Y][4] = UI_Access.Slider_Positions[10] * 5;
								Data_Access.Settings_Grid[X][Y][5] = UI_Access.Valve300_Postions[
									UI_Access.Slider_Positions[11]];
							} else if (UI_Access.UI_Selection == 6) {
								UI_Access.Slider_Positions[9] = Data_Access.Settings_Grid[X][Y][3];
								UI_Access.Slider_Positions[10] = Data_Access.Settings_Grid[X][Y][4] / 5;
								for (int Counter = 0; Counter < UI_Access.Valve300_Postions.size(); Counter++) {
									if (Data_Access.Settings_Grid[X][
										Y][5] == UI_Access.Valve300_Postions[Counter]) {
										UI_Access.Slider_Positions[11] = Counter;
										break;
									}
								}
							}
						} else {
							UI_Access.Engagement = 0;
						}
					} else if (UI_Access.Prompt_Identifier == 9) {
						if (UI_Access.UI_Selection > 3) {
							UI_Access.Subprompt_Identifier = UI_Access.UI_Selection - 3;
						}
					} else if (UI_Access.Prompt_Identifier == 10) {
						Forward_Essentials(Rectangles_Access.MT_Buttons.Length, 0);
						if (UI_Access.UI_Selection == 3) {
							Print_JSON({
								"length\", \"" + Truncate((Data_Access.Settings_Grid[
								X][Y][3] * 1.5) + 0.5 + (static_cast<bool>(Data_Access
								.Settings_Grid[X][Y][4]) ? 0.5 : 0), 0) + "m"
							});
						}
						Backward_Essentials();
					}
					if (UI_Access.UI_Selection > 0 && UI_Access.Engagement == 0) {
						Audio_Access.Play(&Audio_Access.Click, false);
					}
				} else if (Application_Event.button.button == SDL_BUTTON_RIGHT) {
					if (UI_Access.Prompt_Identifier == LDE_INVALID && UI_Access.Tool == 0) {
						std::vector<int> Coordinates = { LDE_INVALID, LDE_INVALID };
						for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
							Rectangles_Access.Tile_1x1.x = static_cast<int>(((Column * 40) - UI_Access.Camera_X) *
								Settings_Access.Screen_Size);
							for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
								Rectangles_Access.Tile_1x1.y = static_cast<int>(((Row * 40) - UI_Access.Camera_Y) *
									Settings_Access.Screen_Size);
								if (Detect_Mouse_Collision(Rectangles_Access.Tile_1x1)) {
									if (Data_Access.Visual_Grid[Column][Row] != 0) {
										if (Data_Access.Visual_Grid[Column][Row] == LDE_INVALID) {
											Coordinates = { static_cast<int>(Data_Access.Settings_Grid[Column][Row][1]),
												static_cast<int>(Data_Access.Settings_Grid[Column][Row][2]) };
										} else {
											Coordinates = { Column, Row };
										}
									}
								}
							}
						}
						if (Coordinates[0] != LDE_INVALID) {
							UI_Access.Placing_Item = Visual_To_ID(Data_Access.Visual_Grid[Coordinates[0]][Coordinates[1]]) + 1;
							Cache_Price();
							Cache_Blueprint();
							UI_Access.Building = false;
						}
					}
				}
			}
			break;
		case SDL_EVENT_QUIT:
			Core_Access.Is_Running = false;
			break;
		default:
			break;
		}
	}
	UI_Access.UI_Selection = 0;
}