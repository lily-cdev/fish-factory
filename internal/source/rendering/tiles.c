#include <rendering.h>

void Render_Grid() {
	for (int C1 = 0; C1 < 2; C1++) {
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			Update_Tilestack(false, (int)((Column * LDE_TILESIZE) - Core.Camera.X), true, LDE_INVALID);
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				Update_Tilestack(true, LDE_INVALID, false, (int)((Row * LDE_TILESIZE) - Core.Camera.Y));
				SDL_FRect Carrier;
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
						Render_Texture(Metadata.Machines[Reinforced_Pipe].Texture2.Data[Data.Visual_Grid[Column][Row] - 1],
							&Rects.Tile_1x1);
						break;
					case Ram_Pump:
						Render_Texture(Metadata.Machines[Ram_Pump].Texture2.Data[1], &Rects.Tile_1x1);
						if (Data.Animation_Grid[Column][Row][0] == 0) {
							Data.Animation_Grid[Column][Row][1] += 60.0f / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][1] >= 360) {
								Data.Animation_Grid[Column][Row][1] = 0;
							}
						}
						SDL_RenderTextureRotated(Core.Renderer, Metadata.Machines[Ram_Pump].Texture2.Data[2], NULL,
							&Rects.Tile_1x1, Data.Animation_Grid[Column][Row][1], &Interface.Tile_Centerpoint,
							SDL_FLIP_NONE);
						{
							const Point Offsets[4] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
							for (int C1 = 0; C1 < 4; C1++) {
								Point Pos = { Column + Offsets[C1].X, Row + Offsets[C1].Y };
								if ((Data.Plumbing_Grid[Pos.X][Pos.Y] == C1 + 1 || Data.Plumbing_Grid[Pos.X][Pos.Y] ==
									Any) && (Data.Settings_Grid[Pos.X][Pos.Y][0] == F_In || Data.Settings_Grid[Pos.X][
									Pos.Y][0] == F_Either)) {
									Render_Texture(Metadata.Machines[Ram_Pump].Texture2.Data[((C1 + 2) & 3) + 3],
										&Rects.Tile_1x1);
								}
							}
						}
						break;
					case Incinerator:
						Data.Animation_Grid[Column][Row][0] += LDE_STATICRATE / Interface.Frame_Rate;
						if (Data.Animation_Grid[Column][Row][0] >= 9) {
							Data.Animation_Grid[Column][Row][0] = 0;
						}
						Source = (SDL_FRect){ 0.0f, 0.0f, Settings.Screen_Size * 21.0f, Settings.Screen_Size * 21.0f };
						Destination = (SDL_FRect){
							(((Settings.Screen_Size * LDE_TILESIZE) - Source.w) * 0.5f) + (Column * Settings.Screen_Size *
								LDE_TILESIZE) - (float)(Core.Camera.X * Settings.Screen_Size),
							(((Settings.Screen_Size * LDE_TILESIZE) - Source.w) * 0.5f) + (Row * Settings.Screen_Size *
								LDE_TILESIZE) - (float)(Core.Camera.Y * Settings.Screen_Size),
							Settings.Screen_Size * 21.0f,
							Settings.Screen_Size * 21.0f
						};
						SDL_RenderTexture(Core.Renderer, Textures.Fire.Data[(int)(Data.Animation_Grid[Column][Row][0])],
							&Source, &Destination);
						Render_Texture(Metadata.Machines[Incinerator].Texture3.Data[Rotation].Data[1], &Rects.Tile_1x1);
						break;
					case RTG:
						Render_Texture(Metadata.Machines[RTG].Texture2.Data[Rotation], &Rects.Tile_1x1);
						break;
					case Decoration:
						Render_Texture(Textures.Tile_Texture, &Rects.Tile_1x1);
						break;
					case Bio_Generator:
						Centerpoint.x = 60.0f * Settings.Screen_Size;
						Centerpoint.y = 60.0f * Settings.Screen_Size;
						Render_Texture(Metadata.Machines[Bio_Generator].Texture3.Data[Rotation].Data[3], &Rects.Tile_3x3);
						if (Data.Animation_Grid[Column][Row][0] == 1) {
							Data.Animation_Grid[Column][Row][1] += 20.0 / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][1] >= 360) {
								Data.Animation_Grid[Column][Row][1] = 0;
							}
						}
						SDL_RenderTextureRotated(Core.Renderer, Metadata.Machines[Bio_Generator].Texture3.Data[
							Rotation].Data[2], NULL, &Rects.Tile_3x3, Data.Animation_Grid[Column][Row][1], &Centerpoint,
							SDL_FLIP_NONE);
						Render_Texture(Metadata.Machines[Bio_Generator].Texture3.Data[Rotation].Data[1], &Rects.Tile_3x3);
						break;
					case Flowerpot:
						Render_Texture(Metadata.Machines[Flowerpot].Texture1, &Rects.Tile_1x1);
						break;
					case Ammunition_Shelf:
						Carrier = (evn(Rotation)) ? Rects.Tile_2x1 : Rects.Tile_1x2;
						Render_Texture(Metadata.Machines[Ammunition_Shelf].Texture2.Data[Rotation], &Carrier);
						break;
					case Large_Pipe:
						Render_Texture(Metadata.Machines[Large_Pipe].Texture2.Data[Data.Visual_Grid[Column][Row] - 71],
							&Rects.Tile_1x1);
						break;
					case Heat_Exchanger:
						Carrier = (evn(Rotation)) ? Rects.Tile_3x4 : Rects.Tile_4x3;
						Render_Texture(Metadata.Machines[Heat_Exchanger].Texture2.Data[Rotation], &Carrier);
						break;
					case Petrified_Wood:
						Render_Texture(Metadata.Machines[Petrified_Wood].Texture1, &Rects.Tile_1x1);
						break;
					case Basalt_Tile:
						Render_Texture(Metadata.Machines[Basalt_Tile].Texture1, &Rects.Tile_1x1);
						break;
					case Silicone_Carpet:
						Render_Texture(Metadata.Machines[Silicone_Carpet].Texture1, &Rects.Tile_1x1);
						break;
					case Money_Generator:
						Render_Texture(Metadata.Machines[Money_Generator].Texture1, &Rects.Tile_1x1);
						break;
					case Fluid_Generator:
						Render_Texture(Metadata.Machines[Fluid_Generator].Texture1, &Rects.Tile_1x1);
						break;
					case Power_Generator:
						Render_Texture(Metadata.Machines[Power_Generator].Texture1, &Rects.Tile_1x1);
						break;
					case Electrolytic_Cell:
						Carrier = (evn(Rotation)) ? Rects.Tile_3x2 : Rects.Tile_2x3;
						if (Data.Visual_Grid[Column][Row] == 48) {
							Render_Texture(Metadata.Machines[Electrolytic_Cell].Texture2.Data[0], &Rects.Tile_3x2);
						} else {
							Render_Texture(Metadata.Machines[Electrolytic_Cell].Texture2.Data[Rotation], &Carrier);
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
						Render_Texture(Metadata.Machines[Fluid_Mixer].Texture3.Data[Rotation].Data[3], &Rects.Tile_3x3);
						SDL_RenderTextureRotated(Core.Renderer, Metadata.Machines[Fluid_Mixer].Texture3.Data[
							Rotation].Data[2], NULL, &Rects.Tile_3x3, Data.Animation_Grid[Column][Row][1], &Centerpoint,
							SDL_FLIP_NONE);
						Render_Texture(Metadata.Machines[Fluid_Mixer].Texture3.Data[Rotation].Data[1], &Rects.Tile_3x3);
						break;
					case R_Intersection:
						Render_Texture(Metadata.Machines[R_Intersection].Texture2.Data[Rotation], &Rects.Tile_3x3);
						break;
					case L_Intersection:
						Render_Texture(Metadata.Machines[L_Intersection].Texture2.Data[Rotation], &Rects.Tile_3x3);
						break;
					case Hazard_Strip:
						Render_Texture(Metadata.Machines[Hazard_Strip].Texture1, &Rects.Tile_1x1);
						break;
					case Distillery:
						Data.Animation_Grid[Column][Row][0] += LDE_STATICRATE / Interface.Frame_Rate;
						if (Data.Animation_Grid[Column][Row][0] >= 9) {
							Data.Animation_Grid[Column][Row][0] = 0;
						}
						Source = (SDL_FRect){ 0.0f, 0.0f, Settings.Screen_Size * 20.0f, Settings.Screen_Size * 20.0f };
						Destination = (SDL_FRect){ 12.0f, 12.0f, Source.w, Source.h };
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
						Render_Texture(Metadata.Machines[Distillery].Texture3.Data[Rotation].Data[2], &Rects.Tile_2x2);
						if (Data.Settings_Grid[Column][Row][S_Time] > 0) {
							Render_Texture(Metadata.Machines[Distillery].Texture3.Data[Rotation].Data[3], &Rects.Tile_2x2);
						}
						break;
					case Turbine_Input:
						Carrier = (evn(Rotation)) ? Rects.Tile_2x3 : Rects.Tile_3x2;
						Render_Texture(Metadata.Machines[Turbine_Input].Texture2.Data[Rotation], &Carrier);
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
							if (evn(Rotation)) {
								Lightplate.x = (float)((Column * LDE_TILESIZE) + 21.0 - Core.Camera.X) *
									Settings.Screen_Size;
								Lightplate.y = (float)((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
								Lightplate.w = Settings.Screen_Size * 38.0f;
								Lightplate.h = Settings.Screen_Size * 120.0f;
							}
							Set_Renderer_Color(Lightcolor);
							SDL_RenderFillRect(Core.Renderer, &Lightplate);
							Clear_Renderer();
							SDL_FRect Carrier = (evn(Rotation)) ? Rects.Tile_2x3 : Rects.Tile_3x2;
							Render_Texture(Metadata.Machines[Turbine_Impulse].Texture3.Data[Rotation].Data[1], &Carrier);
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
							SDL_FRect Lightplate;
							#define Set_Lightplate(X, Y, W, H) Lightplate = (SDL_FRect) { \
									Lightplate.x = Settings.Screen_Size * ((float)(X)), \
									Lightplate.y = Settings.Screen_Size * ((float)(Y)), \
									Lightplate.w = Settings.Screen_Size * ((float)(W)), \
									Lightplate.h = Settings.Screen_Size * ((float)(H)), \
								}
							switch (Rotation) {
							case 1:
								Set_Lightplate(0, 21, 40, 38);
								break;
							case 2:
								Set_Lightplate(21, 0, 38, 40);
								break;
							case 3:
								Set_Lightplate(40, 21, 40, 38);
								break;
							default:
								Set_Lightplate(21, 40, 38, 40);
								break;
							}
							#undef Set_Lightplate
							Lightplate.x += ((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size;
							Lightplate.y += ((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size;
							Set_Renderer_Color(Lightcolor);
							SDL_RenderFillRect(Core.Renderer, &Lightplate);
							Clear_Renderer();
							Render_Texture(Metadata.Machines[Turbine_Output].Texture3.Data[Rotation].Data[1],
								&Rects.Tile_2x2);
							break;
						}
					case Algae_Bed:
						Carrier = evn(Rotation) ? Rects.Tile_2x3 : Rects.Tile_3x2;
						Render_Texture(Metadata.Machines[Algae_Bed].Texture3.Data[Rotation].Data[2], &Carrier);
						if (Data.Animation_Grid[Column][Row][1] > 0) {
							Data.Animation_Grid[Column][Row][0] += 1.0f / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][0] >= 0.5f) {
								Data.Animation_Grid[Column][Row][0] = 0;
								Tick_State();
								Point_f Coordinate = { (float)(Core.State % 52) + 16.0f };
								Tick_State();
								Coordinate.Y = (float)(Core.State % 52) + 16.0f;
								Push_Particle(P_Bubble, (Point){ Column, Row }, Coordinate);
							}
						}
						Render_Particles((Point){ Column, Row });
						Render_Texture(Metadata.Machines[Algae_Bed].Texture3.Data[Rotation].Data[1], &Carrier);
						break;
					case Cable_Node:
						Render_Texture(Metadata.Machines[Cable_Node].Texture1, &Rects.Tile_1x1);
						break;
					case Geo_Well:
						Carrier = (evn(Rotation)) ? Rects.Tile_3x2 : Rects.Tile_2x3;
						Render_Texture(Metadata.Machines[Geo_Well].Texture2.Data[Rotation], &Carrier);
						break;
					case Signal_Tower:
						Render_Texture(Metadata.Machines[Signal_Tower].Texture2.Data[Rotation], &Rects.Tile_3x3);
						if (Data.Settings_Grid[Column][Row][3] == 0) {
							int X = 57;
							int Y = 57;
							switch (Rotation) {
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
						break;
					case Battery:
						Render_Texture(Metadata.Machines[Battery].Texture2.Data[Rotation], &Rects.Tile_2x2);
						break;
					case Command_Platform:
						Render_Texture(Metadata.Machines[Command_Platform].Texture2.Data[Rotation], &Rects.Tile_8x6);
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
						Render_Texture(Metadata.Machines[Filtration_Plant].Texture2.Data[2], &Rects.Tile_2x3);
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
							if (Data.Animation_Grid[Column][Row][2] > 16.0f / 3.0f) {
								Data.Animation_Grid[Column][Row][2] = 0;
							}
							Offset_Rectangle.y += Data.Animation_Grid[Column][Row][2] * Settings.Screen_Size;
						}
						Render_Texture(Metadata.Machines[Filtration_Plant].Texture2.Data[3], &Offset_Rectangle);
						Render_Texture(Metadata.Machines[Filtration_Plant].Texture2.Data[1], &Rects.Tile_2x3);
					} else if (Data.Visual_Grid[Column][Row] > 23 && Data.Visual_Grid[Column][Row] < 41) {
						Render_Texture(Metadata.Machines[Spawning_Pool].Texture2.Data[Data.Visual_Grid[Column][Row] - 24],
							&Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] == 45) {
						Render_Texture(Metadata.Machines[Spawning_Controller].Texture1, &Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] == 46) {
						Render_Texture(Metadata.Machines[Spawning_Output].Texture1, &Rects.Tile_1x1);
					} else if (Data.Visual_Grid[Column][Row] == 47) {
						Render_Texture(Metadata.Machines[Spawning_Input].Texture1, &Rects.Tile_1x1);
					}
					break;
				default:
					break;
				}
			}
		}
	}
}