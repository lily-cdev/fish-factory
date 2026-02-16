#include <rendering.h>

void Render_Grid() {
	for (int C1 = 0; C1 < 2; C1++) {
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			Update_Tilestack(false, (int)((Column * LDE_TILESIZE) - Core.Camera.X), true, LDE_INVALID);
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				Update_Tilestack(true, LDE_INVALID, false, (int)((Row * LDE_TILESIZE) - Core.Camera.Y));
				SDL_FRect Selected_Rectangle;
				int Connections[4];
				SDL_FPoint Centerpoint;
				Point Offset[4];
				SDL_FRect Source;
				SDL_FRect Destination;
				const int Valid_Pipes[2] = { Reinforced_Pipe, Large_Pipe };
				int Rotation = Visual_To_Rotation(Data.Visual_Grid[Column][Row]);
				switch (C1) {
				case 0:
					if (Data.Visual_Grid[Column][Row] != 0) {
						Render_Texture(Textures.Tile_Texture, &Rects.Tile_1x1);
					}
					break;
				case 1:
					if (Data.Visual_Grid[Column][Row] == 0) {
						Render_Texture(Textures.Floor_Texture, &Rects.Tile_1x1);
						Render_Texture(Textures.Frame_Texture, &Rects.Tile_1x1);
					}
					switch (Visual_To_ID(Data.Visual_Grid[Column][Row])) {
					case Reinforced_Pipe:
						Render_Texture(Textures.R_Pipe.Data[Data.Visual_Grid[Column][Row] - 1], &Rects.Tile_1x1);
						break;
					case Ram_Pump:
						Render_Texture(Textures.R_Pump.Data[1], &Rects.Tile_1x1);
						if (Data.Animation_Grid[Column][Row][0] == 0) {
							Data.Animation_Grid[Column][Row][1] += 60.0 / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][1] >= 360) {
								Data.Animation_Grid[Column][Row][1] = 0;
							}
						}
						SDL_RenderTextureRotated(Core.Renderer, Textures.R_Pump.Data[2], NULL, &Rects.Tile_1x1,
							Data.Animation_Grid[Column][Row][1], &Interface.Tile_Centerpoint, SDL_FLIP_NONE);
						memset(Connections, LDE_INVALID, sizeof(Connections));
						if ((Data.Plumbing_Grid[Column - 1][Row] == 3 || Data.Plumbing_Grid[Column - 1][Row] == 0) &&
							(Data.Settings_Grid[Column - 1][Row][0] == 1 || Data.Settings_Grid[Column - 1][Row][0] == 0)) {
							Connections[0] = 0;
						}
						if ((Data.Plumbing_Grid[Column][Row - 1] == 4 || Data.Plumbing_Grid[Column][Row - 1] == 0) &&
							(Data.Settings_Grid[Column][Row - 1][0] == 1 || Data.Settings_Grid[Column][Row - 1][0] == 0)) {
							Connections[1] = 0;
						}
						if ((Data.Plumbing_Grid[Column + 1][Row] == 1 || Data.Plumbing_Grid[Column + 1][Row] == 0) &&
							(Data.Settings_Grid[Column + 1][Row][0] == 1 || Data.Settings_Grid[Column + 1][Row][0] == 0)) {
							Connections[2] = 0;
						}
						if ((Data.Plumbing_Grid[Column][Row + 1] == 2 || Data.Plumbing_Grid[Column][Row + 1] == 0) &&
							(Data.Settings_Grid[Column][Row + 1][0] == 1 || Data.Settings_Grid[Column][Row + 1][0] == 0)) {
							Connections[3] = 0;
						}
						Offset[0].X = -1;
						Offset[0].Y = 0;
						Offset[1].X = 0;
						Offset[1].Y = -1;
						Offset[2].X = 1;
						Offset[2].Y = 0;
						Offset[3].X = 0;
						Offset[3].Y = 1;
						for (int C1 = 0; C1 < 2; C1++) {
							for (int C2 = 0; C2 < 4; C2++) {
								if (Visual_To_ID(Data.Visual_Grid[Column + Offset[C2].X][Row + Offset[C2].Y]) ==
									Valid_Pipes[C1]) {
									Connections[C2] = C1 + 1;
								}							
							}
						}
						for (int C1 = 0; C1 < 4; C1++) {
							if (Connections[C1] != LDE_INVALID) {
								Render_Texture(Textures.R_Pump.Data[(Connections[C1] * 4) + C1 + 3],
									&Rects.Tile_1x1);
							}
						}
						break;
					case Incinerator:
						Data.Animation_Grid[Column][Row][0] += LDE_STATICRATE / Interface.Frame_Rate;
						if (Data.Animation_Grid[Column][Row][0] >= 9) {
							Data.Animation_Grid[Column][Row][0] = 0;
						}
						Source.x = 0;
						Source.y = 0;
						Source.w = Settings.Screen_Size * 21.0f;
						Source.h = Settings.Screen_Size * 21.0f;
						Destination.x = (((Settings.Screen_Size * LDE_TILESIZE) - Source.w) * 0.5f) + (Column *
							Settings.Screen_Size * LDE_TILESIZE) - (float)(Core.Camera.X * Settings.Screen_Size);
						Destination.y = (((Settings.Screen_Size * LDE_TILESIZE) - Source.w) * 0.5f) + (Row *
							Settings.Screen_Size * LDE_TILESIZE) - (float)(Core.Camera.Y * Settings.Screen_Size);
						Destination.w = Settings.Screen_Size * 21.0f;
						Destination.h = Settings.Screen_Size * 21.0f;
						SDL_RenderTexture(Core.Renderer, Textures.Fire.Data[(int)(Data.Animation_Grid[Column][Row][0])],
							&Source, &Destination);
						Render_Texture(Textures.Incinerator.Data[Rotation].Data[1], &Rects.Tile_1x1);
						break;
					case RTG:
						Render_Texture(Textures.RTG.Data[Rotation], &Rects.Tile_1x1);
						break;
					case Decoration:
						Render_Texture(Textures.Tile_Texture, &Rects.Tile_1x1);
						break;
					case Bio_Generator:
						Centerpoint.x = 60.0f * Settings.Screen_Size;
						Centerpoint.y = 60.0f * Settings.Screen_Size;
						Render_Texture(Textures.B_Generator.Data[Rotation].Data[3], &Rects.Tile_3x3);
						if (Data.Animation_Grid[Column][Row][0] == 1) {
							Data.Animation_Grid[Column][Row][1] += 20.0 / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][1] >= 360) {
								Data.Animation_Grid[Column][Row][1] = 0;
							}
						}
						SDL_RenderTextureRotated(Core.Renderer, Textures.B_Generator.Data[Rotation].Data[2], NULL,
							&Rects.Tile_3x3, Data.Animation_Grid[Column][Row][1], &Centerpoint, SDL_FLIP_NONE);
						Render_Texture(Textures.B_Generator.Data[Rotation].Data[1], &Rects.Tile_3x3);
						break;
					case Flowerpot:
						Render_Texture(Textures.Flowerpot, &Rects.Tile_1x1);
						break;
					case Ammunition_Shelf:
						Selected_Rectangle = Rects.Tile_1x2;
						if (Data.Visual_Grid[Column][Row] - 52 == 0 || Data.Visual_Grid[Column][Row] - 52 == 2) {
							Selected_Rectangle = Rects.Tile_2x1;
						}
						Render_Texture(Textures.A_Shelf.Data[Data.Visual_Grid[Column][Row] - 52], &Selected_Rectangle);
						break;
					case Large_Pipe:
						Render_Texture(Textures.L_Pipe.Data[Data.Visual_Grid[Column][Row] - 71], &Rects.Tile_1x1);
						break;
					case Heat_Exchanger:
						Selected_Rectangle = Rects.Tile_4x3;
						if (!evn_i(Visual_To_Rotation(Data.Visual_Grid[Column][Row]))) {
							Selected_Rectangle = Rects.Tile_3x4;
						}
						Render_Texture(Textures.H_Exchanger.Data[Data.Visual_Grid[Column][Row] - 87], &Selected_Rectangle);
						break;
					case Petrified_Wood:
						Render_Texture(Textures.P_Wood, &Rects.Tile_1x1);
						break;
					case Basalt_Tile:
						Render_Texture(Textures.B_Tile, &Rects.Tile_1x1);
						break;
					case Silicone_Carpet:
						Render_Texture(Textures.S_Carpet, &Rects.Tile_1x1);
						break;
					case Money_Generator:
						Render_Texture(Textures.M_Generator, &Rects.Tile_1x1);
						break;
					case Fluid_Generator:
						Render_Texture(Textures.F_Generator, &Rects.Tile_1x1);
						break;
					case Electrolytic_Cell:
						if (evn_i(Rotation)) {
							Selected_Rectangle = Rects.Tile_3x2;
						} else {
							Selected_Rectangle = Rects.Tile_2x3;
						}
						if (Data.Visual_Grid[Column][Row] == 48) {
							Render_Texture(Textures.E_Plant.Data[0], &Rects.Tile_3x2);
						} else {
							Render_Texture(Textures.E_Plant.Data[Data.Visual_Grid[Column][Row] - 95], &Selected_Rectangle);
						}
						break;
					case Fluid_Mixer:
						Centerpoint.x = 60.0f * Settings.Screen_Size;
						Centerpoint.y = 60.0f * Settings.Screen_Size;
						if (Data.Animation_Grid[Column][Row][0] == 1) {
							Data.Animation_Grid[Column][Row][1] += 90.0 / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][1] >= 360) {
								Data.Animation_Grid[Column][Row][1] = 0;
							}
						}
						Render_Texture(Textures.F_Mixer.Data[Rotation].Data[3], &Rects.Tile_3x3);
						SDL_RenderTextureRotated(Core.Renderer, Textures.F_Mixer.Data[Rotation].Data[2], NULL, &Rects.Tile_3x3,
							Data.Animation_Grid[Column][Row][1], &Centerpoint, SDL_FLIP_NONE);
						Render_Texture(Textures.F_Mixer.Data[Rotation].Data[1], &Rects.Tile_3x3);
						break;
					case R_Intersection:
						Render_Texture(Textures.R_Intersection.Data[Visual_To_Rotation(Data.Visual_Grid[Column][Row])],
							&Rects.Tile_3x3);
						break;
					case L_Intersection:
						Render_Texture(Textures.L_Intersection.Data[Visual_To_Rotation(Data.Visual_Grid[Column][Row])],
							&Rects.Tile_3x3);
						break;
					case Hazard_Strip:
						Render_Texture(Textures.H_Strip, &Rects.Tile_1x1);
						break;
					case Distillery:
						Data.Animation_Grid[Column][Row][0] += LDE_STATICRATE / Interface.Frame_Rate;
						if (Data.Animation_Grid[Column][Row][0] >= 9) {
							Data.Animation_Grid[Column][Row][0] = 0;
						}
						Source.x = 0;
						Source.y = 0;
						Source.w = Settings.Screen_Size * 20.0f;
						Source.h = Settings.Screen_Size * 20.0f;
						Destination.x = 12.0f;
						Destination.y = 12.0f;
						Destination.w = Source.w;
						Destination.h = Source.h;
						if (Rotation == 1 || Rotation == 2) {
							Destination.x = 43.0f;
						}
						if (Rotation == 2 || Rotation == 3) {
							Destination.y = 43.0f;
						}
						Destination.x = ((Column * LDE_TILESIZE) + Destination.x - Core.Camera.X) * Settings.Screen_Size;
						Destination.y = ((Row * LDE_TILESIZE) + Destination.y - Core.Camera.Y) * Settings.Screen_Size;
						SDL_RenderTexture(Core.Renderer, Textures.Fire.Data[(int)(Data.Animation_Grid[Column][Row][0])],
							&Source, &Destination);
						Render_Texture(Textures.Distillery.Data[Rotation].Data[2], &Rects.Tile_2x2);
						if (Data.Settings_Grid[Column][Row][1] > 0) {
							Render_Texture(Textures.Distillery.Data[Rotation].Data[3], &Rects.Tile_2x2);
						}
						break;
					case Turbine_Input:
						if (evn_i(Rotation)) {
							Render_Texture(Textures.ST_Input.Data[Rotation], &Rects.Tile_2x3);
						} else {
							Render_Texture(Textures.ST_Input.Data[Rotation], &Rects.Tile_3x2);
						}
						break;
					case Turbine_Impulse: {
							SDL_Color Lightcolor = { 255, 0, 0 };
							if (Data.Settings_Grid[Column][Row][3] == 1) {
								Lightcolor.r = 255;
								Lightcolor.g = 255;
								Lightcolor.b = 0;
							}
							//if active, set lights green
							SDL_FRect Lightplate = {
								(float)((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size,
								(float)((Row * LDE_TILESIZE) + 21.0 - Core.Camera.Y) * Settings.Screen_Size,
								Settings.Screen_Size * 120.0f,
								Settings.Screen_Size * 38.0f
							};
							if (evn_i(Rotation)) {
								Lightplate.x = (float)((Column * LDE_TILESIZE) + 21.0 - Core.Camera.X) *
									Settings.Screen_Size;
								Lightplate.y = (float)((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
								Lightplate.w = Settings.Screen_Size * 38.0f;
								Lightplate.h = Settings.Screen_Size * 120.0f;
							}
							Set_Renderer_Color(Lightcolor);
							SDL_RenderFillRect(Core.Renderer, &Lightplate);
							Clear_Renderer();
							if (evn_i(Rotation)) {
								Render_Texture(Textures.STIT_Block.Data[Rotation].Data[1], &Rects.Tile_2x3);
							} else {
								Render_Texture(Textures.STIT_Block.Data[Rotation].Data[1], &Rects.Tile_3x2);
							}
						}
						break;
					case Turbine_Output: {
							SDL_Color Lightcolor = { 255, 0, 0 };
							if (Data.Settings_Grid[Column][Row][3] == 1) {
								Lightcolor.r = 255;
								Lightcolor.g = 255;
								Lightcolor.b = 0;
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
								Lightplate.x = 0;
								Lightplate.y = Settings.Screen_Size * 21.0f;
								Lightplate.w = Settings.Screen_Size * 40.0f;
								Lightplate.h = Settings.Screen_Size * 38.0f;
								break;
							case 2:
								Lightplate.x = Settings.Screen_Size * 21.0f;
								Lightplate.y = 0;
								Lightplate.w = Settings.Screen_Size * 38.0f;
								Lightplate.h = Settings.Screen_Size * 40.0f;
								break;
							case 3:
								Lightplate.x = Settings.Screen_Size * 40.0f;
								Lightplate.y = Settings.Screen_Size * 21.0f;
								Lightplate.w = Settings.Screen_Size * 40.0f;
								Lightplate.h = Settings.Screen_Size * 38.0f;
								break;
							default:
								break;
							}
							Lightplate.x += ((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
							Lightplate.y += ((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
							Set_Renderer_Color(Lightcolor);
							SDL_RenderFillRect(Core.Renderer, &Lightplate);
							Clear_Renderer();
							Render_Texture(Textures.ST_Output.Data[Rotation].Data[1], &Rects.Tile_2x2);
							break;
						}
					case Algae_Bed:
						Selected_Rectangle = evn_i(Rotation) ? Rects.Tile_2x3 : Rects.Tile_3x2;
						Render_Texture(Textures.G_Bed.Data[Rotation].Data[2], &Selected_Rectangle);
						//bubbles
						Render_Texture(Textures.G_Bed.Data[Rotation].Data[1], &Selected_Rectangle);
						break;
					default:
						break;
					}
					if (Data.Visual_Grid[Column][Row] == 21) {
						Rects.Tunnel.Data[0].x = ((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
						Rects.Tunnel.Data[0].y = (((Row - 2.25f) * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
						Render_Texture(Textures.S_Dock.Data[0], &Rects.Tile_6x4);
						Render_Texture(Textures.Tunnel.Data[0], &Rects.Tunnel.Data[0]);
					} else if (Data.Visual_Grid[Column][Row] == 22) {
						Render_Texture(Textures.F_Plant.Data[2], &Rects.Tile_2x3);
						SDL_FRect Offset_Rectangle = Rects.Tile_2x3;
						if (Data.Animation_Grid[Column][Row][0] == 0) {
							Data.Animation_Grid[Column][Row][1] += 1.0f / Interface.Frame_Rate;
							SDL_FRect Progress_Rectangle = {
								Rects.Tile_2x3.x + (Settings.Screen_Size * 19),
								Rects.Tile_2x3.y + (Settings.Screen_Size * 57),
								(float)((Data.Animation_Grid[Column][Row][1] * 50) * Settings.Screen_Size),
								Settings.Screen_Size * 7.0f
							};
							Set_Renderer_Color(Colors.Cherry_Blossom);
							SDL_RenderFillRect(Core.Renderer, &Progress_Rectangle);
							Clear_Renderer();
							Data.Animation_Grid[Column][Row][2] += 64.0f / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][2] > ((float)32 / 6)) {
								Data.Animation_Grid[Column][Row][2] = 0;
							}
							Offset_Rectangle.y += Data.Animation_Grid[Column][Row][2] * Settings.Screen_Size;
						}
						Render_Texture(Textures.F_Plant.Data[3], &Offset_Rectangle);
						Render_Texture(Textures.F_Plant.Data[1], &Rects.Tile_2x3);
					} else if (Data.Visual_Grid[Column][Row] > 23 && Data.Visual_Grid[Column][Row] < 41) {
						Render_Texture(Textures.MS_Pool.Data[Data.Visual_Grid[Column][Row] - 24], &Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] == 43) {
						Render_Texture(Textures.C_Platform.Data[0], &Rects.Tile_8x6);
					} else if (Data.Visual_Grid[Column][Row] == 44) {
						Render_Texture(Textures.B_Scrubber.Data[0], &Rects.Tile_2x2);
					} else if (Data.Visual_Grid[Column][Row] == 45) {
						Render_Texture(Textures.MS_Controller, &Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] == 46) {
						Render_Texture(Textures.MS_Output, &Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] == 47) {
						Render_Texture(Textures.MS_Input, &Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] == 50) {
						Render_Texture(Textures.T_Tower.Data[0], &Rects.Tile_3x3);
						if (Data.Settings_Grid[Column][Row][3] == 0) {
							Rects.R_Flash.x = Rects.Tile_3x3.x + (Settings.Screen_Size * 57);
							Rects.R_Flash.y = Rects.Tile_3x3.y + (Settings.Screen_Size * 57);
							Render_Texture(Textures.R_Flash, &Rects.R_Flash);
						}
					} else if (Data.Visual_Grid[Column][Row] == 56) {
						Render_Texture(Textures.C_Platform.Data[1], &Rects.Tile_6x8);
					} else if (Data.Visual_Grid[Column][Row] == 57) {
						Render_Texture(Textures.C_Platform.Data[2], &Rects.Tile_8x6);
					} else if (Data.Visual_Grid[Column][Row] == 58) {
						Render_Texture(Textures.C_Platform.Data[3], &Rects.Tile_6x8);
					} else if (Data.Visual_Grid[Column][Row] > 59 && Data.Visual_Grid[Column][Row] < 63) {
						Render_Texture(Textures.T_Tower.Data[Data.Visual_Grid[Column][Row] - 59], &Rects.Tile_3x3);
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
							Rects.R_Flash.x = Rects.Tile_3x3.x + (X * Settings.Screen_Size);
							Rects.R_Flash.y = Rects.Tile_3x3.y + (Y * Settings.Screen_Size);
							Render_Texture(Textures.R_Flash, &Rects.R_Flash);
						}
					} else if (Data.Visual_Grid[Column][Row] == 63) {
						Render_Texture(Textures.C_Node, &Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] > 63 && Data.Visual_Grid[Column][Row] < 67) {
						Render_Texture(Textures.B_Scrubber.Data[Data.Visual_Grid[Column][Row] - 63], &Rects.Tile_2x2);
					} else if (Data.Visual_Grid[Column][Row] == 67 || Data.Visual_Grid[Column][Row] == 69) {
						Render_Texture(Textures.G_Well.Data[Data.Visual_Grid[Column][Row] - 67], &Rects.Tile_2x3);
					} else if (Data.Visual_Grid[Column][Row] == 68 || Data.Visual_Grid[Column][Row] == 70) {
						Render_Texture(Textures.G_Well.Data[Data.Visual_Grid[Column][Row] - 67], &Rects.Tile_3x2);
					}
					break;
				default:
					break;
				}
			}
		}
	}
}