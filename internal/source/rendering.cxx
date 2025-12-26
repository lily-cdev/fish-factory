#include <ui.h>

void Render_Grid() {
	for (int Counter = 0; Counter < 2; Counter++) {
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			Update_Tilestack(false, static_cast<int>((Column * LDE_TILESIZE) -
				Interface.Camera_X), true, LDE_INVALID);
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				Update_Tilestack(true, LDE_INVALID, false, static_cast<int>((Row *
					LDE_TILESIZE) - Interface.Camera_Y));
				SDL_FRect Selected_Rectangle;
				std::vector<int> Connections;
				SDL_FPoint Centerpoint;
				std::vector<std::vector<int>> Offset;
				SDL_FRect Source;
				SDL_FRect Destination;
				const int Valid_Pipes[2] = { Reinforced_Pipe, Large_Pipe };
				int Rotation = Visual_To_Rotation(Data.Visual_Grid[Column][Row]);
				switch (Counter) {
				case 0:
					if (Data.Visual_Grid[Column][Row] != 0) {
						SDL_RenderTexture(Core.Renderer, Textures.Tile_Texture, NULL,
							&Rects.Tile_1x1);
					}
					break;
				case 1:
					if (Data.Visual_Grid[Column][Row] == 0) {
						SDL_RenderTexture(Core.Renderer, Textures.Floor_Texture, NULL,
							&Rects.Tile_1x1);
						SDL_RenderTexture(Core.Renderer, Textures.Frame_Texture, NULL,
							&Rects.Tile_1x1);
					}
					switch (Visual_To_ID(Data.Visual_Grid[Column][Row])) {
					case Reinforced_Pipe:
						SDL_RenderTexture(Core.Renderer, Textures.R_Pipe
							.Data[Data.Visual_Grid[Column][Row] - 1], NULL,
							&Rects.Tile_1x1);
						break;
					case Ram_Pump:
						SDL_RenderTexture(Core.Renderer, Textures
							.R_Pump.Data[1], NULL, &Rects.Tile_1x1);
						if (Data.Animation_Grid[Column][Row][0] == 0) {
							Data.Animation_Grid[Column][Row][1] += 60.0 / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][1] >= 360) {
								Data.Animation_Grid[Column][Row][1] = 0;
							}
						}
						SDL_RenderTextureRotated(Core.Renderer, Textures
							.R_Pump.Data[2], NULL, &Rects.Tile_1x1, Data
							.Animation_Grid[Column][Row][1], &Interface.Tile_Centrepoint, SDL_FLIP_NONE);
						Connections.resize(4, LDE_INVALID);
						if ((Data.Plumbing_Grid[Column - 1][Row] == 3 || Data.Plumbing_Grid
							[Column - 1][Row] == 0) && (Data.Settings_Grid[Column - 1][Row][0] == 1 ||
							Data.Settings_Grid[Column - 1][Row][0] == 0)) {
							Connections[0] = 0;
						}
						if ((Data.Plumbing_Grid[Column][Row - 1] == 4 || Data.Plumbing_Grid
							[Column][Row - 1] == 0) && (Data.Settings_Grid[Column][Row - 1][0] == 1 ||
							Data.Settings_Grid[Column][Row - 1][0] == 0)) {
							Connections[1] = 0;
						}
						if ((Data.Plumbing_Grid[Column + 1][Row] == 1 || Data.Plumbing_Grid
							[Column + 1][Row] == 0) && (Data.Settings_Grid[Column + 1][Row][0] == 1 ||
							Data.Settings_Grid[Column + 1][Row][0] == 0)) {
							Connections[2] = 0;
						}
						if ((Data.Plumbing_Grid[Column][Row + 1] == 2 || Data.Plumbing_Grid
							[Column][Row + 1] == 0) && (Data.Settings_Grid[Column][Row + 1][0] == 1 ||
							Data.Settings_Grid[Column][Row + 1][0] == 0)) {
							Connections[3] = 0;
						}
						Offset = {
							{ -1, 0 },
							{ 0, -1 },
							{ 1, 0 },
							{ 0, 1 }
						};
						for (int Counter1 = 0; Counter1 < 2; Counter1++) {
							for (int Counter2 = 0; Counter2 < 4; Counter2++) {
								if (Visual_To_ID(Data.Visual_Grid[Column + Offset[Counter2][0]]
									[Row + Offset[Counter2][1]]) == Valid_Pipes[Counter1]) {
									Connections[Counter2] = Counter1 + 1;
								}							
							}
						}
						for (int Counter1 = 0; Counter1 < 4; Counter1++) {
							if (Connections[Counter1] != LDE_INVALID) {
								SDL_RenderTexture(Core.Renderer,
									Textures.R_Pump.Data[(Connections[Counter1] * 4) +
									Counter1 + 3], NULL, &Rects.Tile_1x1);
							}
						}
						break;
					case Incinerator:
						Data.Animation_Grid[Column][Row][0] += LDE_STATICRATE / Interface.Frame_Rate;
						if (Data.Animation_Grid[Column][Row][0] >= 9) {
							Data.Animation_Grid[Column][Row][0] = 0;
						}
						Source = {
							0,
							0,
							Settings.Screen_Size * 21.0f,
							Settings.Screen_Size * 21.0f
						};
						Destination = {
							(((Settings.Screen_Size * LDE_TILESIZE) - Source.w) * 0.5f) +
								(Column * Settings.Screen_Size * LDE_TILESIZE) -
								static_cast<float>(Interface.Camera_X * Settings.Screen_Size),
							(((Settings.Screen_Size * LDE_TILESIZE) - Source.w) * 0.5f) +
								(Row * Settings.Screen_Size * LDE_TILESIZE) -
								static_cast<float>(Interface.Camera_Y * Settings.Screen_Size),
							Settings.Screen_Size * 21.0f,
							Settings.Screen_Size * 21.0f
						};
						SDL_RenderTexture(Core.Renderer, Textures
							.Fire.Data[static_cast<int>(Data.Animation_Grid[
							Column][Row][0])], &Source, &Destination);
						SDL_RenderTexture(Core.Renderer, Textures.Incinerator
							.Data[Rotation].Data[1], NULL, &Rects.Tile_1x1);
						break;
					case Piezo_Generator:
						SDL_RenderTexture(Core.Renderer, Textures.P_Generator, NULL,
							&Rects.Tile_1x1);
						break;
					case Decoration:
						SDL_RenderTexture(Core.Renderer, Textures.Tile_Texture, NULL,
							&Rects.Tile_1x1);
						break;
					case Bio_Generator:
						Centerpoint = { 60.0f * Settings.Screen_Size,
							60.0f * Settings.Screen_Size };
						SDL_RenderTexture(Core.Renderer, Textures.B_Generator
							.Data[Rotation].Data[3], NULL, &Rects.Tile_3x3);
						if (Data.Animation_Grid[Column][Row][0] == 1) {
							Data.Animation_Grid[Column][Row][1] += 20.0 / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][1] >= 360) {
								Data.Animation_Grid[Column][Row][1] = 0;
							}
						}
						SDL_RenderTextureRotated(Core.Renderer, Textures.B_Generator
							.Data[Rotation].Data[2], NULL, &Rects.Tile_3x3, Data.Animation_Grid
							[Column][Row][1], &Centerpoint, SDL_FLIP_NONE);
						SDL_RenderTexture(Core.Renderer, Textures.B_Generator
							.Data[Rotation].Data[1], NULL, &Rects.Tile_3x3);
						break;
					case Flowerpot:
						SDL_RenderTexture(Core.Renderer, Textures.Flowerpot, NULL,
							&Rects.Tile_1x1);
						break;
					case Ammunition_Shelf:
						Selected_Rectangle = Rects.Tile_1x2;
						if (Data.Visual_Grid[Column][Row] - 52 == 0 ||
							Data.Visual_Grid[Column][Row] - 52 == 2) {
							Selected_Rectangle = Rects.Tile_2x1;
						}
						SDL_RenderTexture(Core.Renderer, Textures.A_Shelf
							.Data[Data.Visual_Grid[Column][Row] - 52], NULL, &Selected_Rectangle);
						break;
					case Large_Pipe:
						SDL_RenderTexture(Core.Renderer, Textures.L_Pipe
							.Data[Data.Visual_Grid[Column][Row] - 71], NULL, &Rects.Tile_1x1);
						break;
					case Heat_Exchanger:
						Selected_Rectangle = Rects.Tile_4x3;
						if (!evn_i(Visual_To_Rotation(Data.Visual_Grid[Column][Row]))) {
							Selected_Rectangle = Rects.Tile_3x4;
						}
						SDL_RenderTexture(Core.Renderer, Textures.H_Exchanger
							.Data[Data.Visual_Grid[Column][Row] - 87], NULL, &Selected_Rectangle);
						break;
					case Petrified_Wood:
						SDL_RenderTexture(Core.Renderer, Textures.P_Wood,
							NULL, &Rects.Tile_1x1);
						break;
					case Basalt_Tile:
						SDL_RenderTexture(Core.Renderer, Textures.B_Tile,
							NULL, &Rects.Tile_1x1);
						break;
					case Silicone_Carpet:
						SDL_RenderTexture(Core.Renderer, Textures.S_Carpet,
							NULL, &Rects.Tile_1x1);
						break;
					case Money_Generator:
						SDL_RenderTexture(Core.Renderer, Textures.M_Generator,
							NULL, &Rects.Tile_1x1);
						break;
					case Fluid_Generator:
						SDL_RenderTexture(Core.Renderer, Textures.F_Generator,
							NULL, &Rects.Tile_1x1);
						break;
					case Electrolytic_Cell:
						if (evn_i(Rotation)) {
							Selected_Rectangle = Rects.Tile_3x2;
						} else {
							Selected_Rectangle = Rects.Tile_2x3;
						}
						if (Data.Visual_Grid[Column][Row] == 48) {
							SDL_RenderTexture(Core.Renderer, Textures
								.E_Plant.Data[0], NULL, &Rects.Tile_3x2);
						} else {
							SDL_RenderTexture(Core.Renderer, Textures.E_Plant.Data
								[Data.Visual_Grid[Column][Row] - 95], NULL, &Selected_Rectangle);
						}
						break;
					case Fluid_Mixer:
						Centerpoint = { 60.0f * Settings.Screen_Size,
							60.0f * Settings.Screen_Size };
						if (Data.Animation_Grid[Column][Row][0] == 1) {
							Data.Animation_Grid[Column][Row][1] += 90.0 / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][1] >= 360) {
								Data.Animation_Grid[Column][Row][1] = 0;
							}
						}
						SDL_RenderTexture(Core.Renderer, Textures.F_Mixer
							.Data[Rotation].Data[3], NULL, &Rects.Tile_3x3);
						SDL_RenderTextureRotated(Core.Renderer, Textures.F_Mixer
							.Data[Rotation].Data[2], NULL, &Rects.Tile_3x3, Data.Animation_Grid
							[Column][Row][1], &Centerpoint, SDL_FLIP_NONE);
						SDL_RenderTexture(Core.Renderer, Textures.F_Mixer
							.Data[Rotation].Data[1], NULL, &Rects.Tile_3x3);
						break;
					case R_Intersection:
						SDL_RenderTexture(Core.Renderer, Textures
							.R_Intersection.Data[Visual_To_Rotation(Data.Visual_Grid[
							Column][Row])], NULL, &Rects.Tile_3x3);
						break;
					case L_Intersection:
						SDL_RenderTexture(Core.Renderer, Textures
							.L_Intersection.Data[Visual_To_Rotation(Data.Visual_Grid[
							Column][Row])], NULL, &Rects.Tile_3x3);
						break;
					case Hazard_Strip:
						SDL_RenderTexture(Core.Renderer, Textures.H_Strip,
							NULL, &Rects.Tile_1x1);
						break;
					case Distillery:
						Data.Animation_Grid[Column][Row][0] += LDE_STATICRATE / Interface.Frame_Rate;
						if (Data.Animation_Grid[Column][Row][0] >= 9) {
							Data.Animation_Grid[Column][Row][0] = 0;
						}
						Source = {
							0,
							0,
							Settings.Screen_Size * 20.0f,
							Settings.Screen_Size * 20.0f
						};
						Destination = {
							12.0f,
							12.0f,
							Source.w,
							Source.h
						};
						if (Rotation == 1 || Rotation == 2) {
							Destination.x = 43.0f;
						}
						if (Rotation == 2 || Rotation == 3) {
							Destination.y = 43.0f;
						}
						Destination.x = ((Column * LDE_TILESIZE) + Destination.x -
							Interface.Camera_X) * Settings.Screen_Size;
						Destination.y = ((Row * LDE_TILESIZE) + Destination.y -
							Interface.Camera_Y) * Settings.Screen_Size;
						SDL_RenderTexture(Core.Renderer, Textures
							.Fire.Data[static_cast<int>(Data.Animation_Grid[
							Column][Row][0])], &Source, &Destination);
						SDL_RenderTexture(Core.Renderer,
							Textures.Distillery.Data[Rotation].Data[2], NULL,
							&Rects.Tile_2x2);
						if (Data.Settings_Grid[Column][Row][1] > 0) {
							SDL_RenderTexture(Core.Renderer,
								Textures.Distillery.Data[Rotation].Data[3],
								NULL, &Rects.Tile_2x2);
						}
						break;
					case Turbine_Input:
						if (evn_i(Rotation)) {
							SDL_RenderTexture(Core.Renderer, Textures
								.ST_Input.Data[Rotation], NULL, &Rects.Tile_2x3);
						} else {
							SDL_RenderTexture(Core.Renderer, Textures
								.ST_Input.Data[Rotation], NULL, &Rects.Tile_3x2);
						}
						break;
					case Turbine_Impulse: {
							SDL_Color Lightcolor = { 255, 0, 0 };
							if (Data.Settings_Grid[Column][Row][3] == 1) {
								Lightcolor = { 255, 255, 0 };
							}
							//if active, set lights green
							SDL_FRect Lightplate = {
								static_cast<float>((Column * LDE_TILESIZE) - Interface
									.Camera_X) * Settings.Screen_Size,
								static_cast<float>((Row * LDE_TILESIZE) + 21.0 - Interface
									.Camera_Y) * Settings.Screen_Size,
								Settings.Screen_Size * 120.0f,
								Settings.Screen_Size * 38.0f
							};
							if (evn_i(Rotation)) {
								Lightplate = {
									static_cast<float>((Column * LDE_TILESIZE) + 21.0 - Interface
										.Camera_X) * Settings.Screen_Size,
									static_cast<float>((Row * LDE_TILESIZE) - Interface.Camera_Y) *
										Settings.Screen_Size,
									Settings.Screen_Size * 38.0f,
									Settings.Screen_Size * 120.0f
								};
							}
							Set_Renderer_Color(Lightcolor);
							SDL_RenderFillRect(Core.Renderer, &Lightplate);
							Clear_Renderer();
							if (evn_i(Rotation)) {
								SDL_RenderTexture(Core.Renderer, Textures
									.STIT_Block.Data[Rotation].Data[1], NULL, &Rects.Tile_2x3);
							} else {
								SDL_RenderTexture(Core.Renderer, Textures
									.STIT_Block.Data[Rotation].Data[1], NULL, &Rects.Tile_3x2);
							}
						}
						break;
					case Turbine_Output: {
							SDL_Color Lightcolor = { 255, 0, 0 };
							if (Data.Settings_Grid[Column][Row][3] == 1) {
								Lightcolor = { 255, 255, 0 };
							}
							//if active, set lights green
							SDL_FRect Lightplate = {
								Settings.Screen_Size * 21.0f,
								Settings.Screen_Size * 40.0f,
								Settings.Screen_Size * 38.0f,
								Settings.Screen_Size * 40.0f
							};
							switch (Rotation) {
							case 1:
								Lightplate = {
									0,
									Settings.Screen_Size * 21.0f,
									Settings.Screen_Size * 40.0f,
									Settings.Screen_Size * 38.0f
								};
								break;
							case 2:
								Lightplate = {
									Settings.Screen_Size * 21.0f,
									0,
									Settings.Screen_Size * 38.0f,
									Settings.Screen_Size * 40.0f
								};
								break;
							case 3:
								Lightplate = {
									Settings.Screen_Size * 40.0f,
									Settings.Screen_Size * 21.0f,
									Settings.Screen_Size * 40.0f,
									Settings.Screen_Size * 38.0f
								};
								break;
							default:
								break;
							}
							Lightplate.x += ((Column * LDE_TILESIZE) - Interface.Camera_X) * Settings.Screen_Size;
							Lightplate.y += ((Row * LDE_TILESIZE) - Interface.Camera_Y) * Settings.Screen_Size;
							Set_Renderer_Color(Lightcolor);
							SDL_RenderFillRect(Core.Renderer, &Lightplate);
							Clear_Renderer();
							SDL_RenderTexture(Core.Renderer, Textures
								.ST_Output.Data[Rotation].Data[1], NULL, &Rects.Tile_2x2);
							break;
						}
					case Algae_Bed:
						Selected_Rectangle = evn_i(Rotation) ? Rects.Tile_2x3 :
							Rects.Tile_3x2;
						SDL_RenderTexture(Core.Renderer, Textures
							.G_Bed.Data[Rotation].Data[2], NULL, &Selected_Rectangle);
						//bubbles
						SDL_RenderTexture(Core.Renderer, Textures
							.G_Bed.Data[Rotation].Data[1], NULL, &Selected_Rectangle);
						break;
					default:
						break;
					}
					if (Data.Visual_Grid[Column][Row] == 21) {
						Rects.Tunnel.Data[0].x = ((Column * LDE_TILESIZE) -
							Interface.Camera_X) * Settings.Screen_Size;
						Rects.Tunnel.Data[0].y = (((Row - 2.25f) * LDE_TILESIZE) -
							Interface.Camera_Y) * Settings.Screen_Size;
						SDL_RenderTexture(Core.Renderer, Textures
							.S_Dock.Data[0], NULL, &Rects.Tile_6x4);
						SDL_RenderTexture(Core.Renderer, Textures
							.Tunnel.Data[0], NULL, &Rects.Tunnel.Data[0]);
					} else if (Data.Visual_Grid[Column][Row] == 22) {
						SDL_RenderTexture(Core.Renderer, Textures
							.F_Plant.Data[2], NULL, &Rects.Tile_2x3);
						SDL_FRect Offset_Rectangle = Rects.Tile_2x3;
						if (Data.Animation_Grid[Column][Row][0] == 0) {
							Data.Animation_Grid[Column][Row][1] += 1.0f / Interface.Frame_Rate;
							SDL_FRect Progress_Rectangle = { Rects.Tile_2x3.x + (19 *
								Settings.Screen_Size), Rects.Tile_2x3.y + (57 *
								Settings.Screen_Size), static_cast<float>((50 * Data.Animation_Grid
								[Column][Row][1]) *	Settings.Screen_Size), 7.0f * Settings.Screen_Size };
							Set_Renderer_Color(Colors.Cherry_Blossom);
							SDL_RenderFillRect(Core.Renderer, &Progress_Rectangle);
							Clear_Renderer();
							Data.Animation_Grid[Column][Row][2] += 64.0f / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][2] > ((double)32 / 6)) {
								Data.Animation_Grid[Column][Row][2] = 0;
							}
							Offset_Rectangle.y += Data.Animation_Grid[Column][Row][2] * Settings.Screen_Size;
						}
						SDL_RenderTexture(Core.Renderer, Textures
							.F_Plant.Data[3], NULL, &Offset_Rectangle);
						SDL_RenderTexture(Core.Renderer, Textures
							.F_Plant.Data[1], NULL, &Rects.Tile_2x3);
					} else if (Data.Visual_Grid[Column][Row] > 23 && Data.Visual_Grid[Column][Row] < 41) {
						SDL_RenderTexture(Core.Renderer, Textures.MS_Pool.Data[
							Data.Visual_Grid[Column][Row] - 24], NULL, &Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] == 43) {
						SDL_RenderTexture(Core.Renderer, Textures
							.C_Platform.Data[0], NULL, &Rects.Tile_8x6);
					} else if (Data.Visual_Grid[Column][Row] == 44) {
						SDL_RenderTexture(Core.Renderer, Textures
							.B_Scrubber.Data[0], NULL, &Rects.Tile_2x2);
					} else if (Data.Visual_Grid[Column][Row] == 45) {
						SDL_RenderTexture(Core.Renderer, Textures.MS_Controller, NULL,
							&Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] == 46) {
						SDL_RenderTexture(Core.Renderer, Textures.MS_Output, NULL,
							&Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] == 47) {
						SDL_RenderTexture(Core.Renderer, Textures.MS_Input, NULL,
							&Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] == 50) {
						SDL_RenderTexture(Core.Renderer, Textures
							.T_Tower.Data[0], NULL,	&Rects.Tile_3x3);
						if (Data.Settings_Grid[Column][Row][3] == 0) {
							Rects.R_Flash.x = Rects.Tile_3x3.x +
								(57 * Settings.Screen_Size);
							Rects.R_Flash.y = Rects.Tile_3x3.y +
								(57 * Settings.Screen_Size);
							SDL_RenderTexture(Core.Renderer, Textures.R_Flash,
								NULL, &Rects.R_Flash);
						}
					} else if (Data.Visual_Grid[Column][Row] == 56) {
						SDL_RenderTexture(Core.Renderer, Textures
							.C_Platform.Data[1], NULL, &Rects.Tile_6x8);
					} else if (Data.Visual_Grid[Column][Row] == 57) {
						SDL_RenderTexture(Core.Renderer, Textures
							.C_Platform.Data[2], NULL, &Rects.Tile_8x6);
					} else if (Data.Visual_Grid[Column][Row] == 58) {
						SDL_RenderTexture(Core.Renderer, Textures
							.C_Platform.Data[3], NULL, &Rects.Tile_6x8);
					} else if (Data.Visual_Grid[Column][Row] > 59 && Data.Visual_Grid[Column][Row] < 63) {
						SDL_RenderTexture(Core.Renderer, Textures.T_Tower.Data[
							Data.Visual_Grid[Column][Row] - 59], NULL, &Rects.Tile_3x3);
						if (Data.Settings_Grid[Column][Row][3] == 0) {
							int X = 57;
							int Y = 57;
							switch (Data.Visual_Grid[Column][Row] - 60) {
							case 0:
								X = 23;
								break;
							case 1:
								X = 23;
								Y = 23;
								break;
							case 2:
								Y = 23;
								break;
							default:
								break;
							}
							Rects.R_Flash.x = Rects.Tile_3x3.x +
								(X * Settings.Screen_Size);
							Rects.R_Flash.y = Rects.Tile_3x3.y +
								(Y * Settings.Screen_Size);
							SDL_RenderTexture(Core.Renderer, Textures.R_Flash,
								NULL, &Rects.R_Flash);
						}
					} else if (Data.Visual_Grid[Column][Row] == 63) {
						SDL_RenderTexture(Core.Renderer, Textures.C_Node, NULL,
							&Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] > 63 && Data.Visual_Grid[Column][Row] < 67) {
						SDL_RenderTexture(Core.Renderer, Textures.B_Scrubber.Data
							[Data.Visual_Grid[Column][Row] - 63], NULL, &Rects.Tile_2x2);
					} else if (Data.Visual_Grid[Column][Row] == 67 || Data.Visual_Grid[Column][Row] == 69) {
						SDL_RenderTexture(Core.Renderer, Textures.G_Well.Data
							[Data.Visual_Grid[Column][Row] - 67], NULL, &Rects.Tile_2x3);
					} else if (Data.Visual_Grid[Column][Row] == 68 || Data.Visual_Grid[Column][Row] == 70) {
						SDL_RenderTexture(Core.Renderer, Textures.G_Well.Data
							[Data.Visual_Grid[Column][Row] - 67], NULL, &Rects.Tile_3x2);
					}
					break;
				default:
					break;
				}
			}
		}
	}
}