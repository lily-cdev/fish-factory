#include <Core.h>
#include <Preloader.h>
#include <Grid_Handler.h>
#include <Render_Handler.h>

void Render_Grid() {
	for (int Counter = 0; Counter < 2; Counter++) {
		for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
			Update_Tilestack(false, static_cast<int>((Column * 40) - UI_Access.Camera_X), true, LDE_INVALID);
			for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
				Update_Tilestack(true, LDE_INVALID, false, static_cast<int>((Row * 40) - UI_Access.Camera_Y));
				SDL_FRect Selected_Rectangle;
				std::vector<int> Connections;
				SDL_FPoint Centerpoint;
				std::vector<std::vector<int>> Offset;
				SDL_FRect Source;
				SDL_FRect Destination;
				const int Valid_Pipes[2] = { Reinforced_Pipe, Large_Pipe };
				int Rotation = Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row]);
				switch (Counter) {
				case 0:
					if (Data_Access.Visual_Grid[Column][Row] != 0) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Tile_Texture, NULL,
							&Rectangles_Access.Tile_1x1);
					}
					break;
				case 1:
					if (Data_Access.Visual_Grid[Column][Row] == 0) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Floor_Texture, NULL,
							&Rectangles_Access.Tile_1x1);
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Frame_Texture, NULL,
							&Rectangles_Access.Tile_1x1);
					}
					switch (Visual_To_ID(Data_Access.Visual_Grid[Column][Row])) {
					case Reinforced_Pipe:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.R_Pipe
							.Data[Data_Access.Visual_Grid[Column][Row] - 1], NULL,
							&Rectangles_Access.Tile_1x1);
						break;
					case Ram_Pump:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.R_Pump.Data[1], NULL, &Rectangles_Access.Tile_1x1);
						if (Data_Access.Animation_Grid[Column][Row][0] == 0) {
							Data_Access.Animation_Grid[Column][Row][1] += 60.0 / UI_Access.Frame_Rate;
							if (Data_Access.Animation_Grid[Column][Row][1] >= 360) {
								Data_Access.Animation_Grid[Column][Row][1] = 0;
							}
						}
						SDL_RenderTextureRotated(Core_Access.Application_Renderer, Textures_Access
							.R_Pump.Data[2], NULL, &Rectangles_Access.Tile_1x1, Data_Access
							.Animation_Grid[Column][Row][1], &UI_Access.Tile_Centrepoint, SDL_FLIP_NONE);
						Connections.resize(4, LDE_INVALID);
						if ((Data_Access.Plumbing_Grid[Column - 1][Row] == 3 || Data_Access.Plumbing_Grid
							[Column - 1][Row] == 0) && (Data_Access.Settings_Grid[Column - 1][Row][0] == 1 ||
							Data_Access.Settings_Grid[Column - 1][Row][0] == 0)) {
							Connections[0] = 0;
						}
						if ((Data_Access.Plumbing_Grid[Column][Row - 1] == 4 || Data_Access.Plumbing_Grid
							[Column][Row - 1] == 0) && (Data_Access.Settings_Grid[Column][Row - 1][0] == 1 ||
							Data_Access.Settings_Grid[Column][Row - 1][0] == 0)) {
							Connections[1] = 0;
						}
						if ((Data_Access.Plumbing_Grid[Column + 1][Row] == 1 || Data_Access.Plumbing_Grid
							[Column + 1][Row] == 0) && (Data_Access.Settings_Grid[Column + 1][Row][0] == 1 ||
							Data_Access.Settings_Grid[Column + 1][Row][0] == 0)) {
							Connections[2] = 0;
						}
						if ((Data_Access.Plumbing_Grid[Column][Row + 1] == 2 || Data_Access.Plumbing_Grid
							[Column][Row + 1] == 0) && (Data_Access.Settings_Grid[Column][Row + 1][0] == 1 ||
							Data_Access.Settings_Grid[Column][Row + 1][0] == 0)) {
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
								if (Visual_To_ID(Data_Access.Visual_Grid[Column + Offset[Counter2][0]]
									[Row + Offset[Counter2][1]]) == Valid_Pipes[Counter1]) {
									Connections[Counter2] = Counter1 + 1;
								}							
							}
						}
						for (int Counter1 = 0; Counter1 < 4; Counter1++) {
							if (Connections[Counter1] != LDE_INVALID) {
								SDL_RenderTexture(Core_Access.Application_Renderer,
									Textures_Access.R_Pump.Data[(Connections[Counter1] * 4) +
									Counter1 + 3], NULL, &Rectangles_Access.Tile_1x1);
							}
						}
						break;
					case Incinerator:
						Data_Access.Animation_Grid[Column][Row][0] += LDE_STATICRATE / UI_Access.Frame_Rate;
						if (Data_Access.Animation_Grid[Column][Row][0] >= 9) {
							Data_Access.Animation_Grid[Column][Row][0] = 0;
						}
						Source = {
							0,
							0,
							Settings_Access.Screen_Size * 21.0f,
							Settings_Access.Screen_Size * 21.0f
						};
						Destination = {
							(((Settings_Access.Screen_Size * 40.0f) - Source.w) * 0.5f) +
								(Column * Settings_Access.Screen_Size * 40.0f) -
								static_cast<float>(UI_Access.Camera_X * Settings_Access.Screen_Size),
							(((Settings_Access.Screen_Size * 40.0f) - Source.w) * 0.5f) +
								(Row * Settings_Access.Screen_Size * 40.0f) -
								static_cast<float>(UI_Access.Camera_Y * Settings_Access.Screen_Size),
							Settings_Access.Screen_Size * 21.0f,
							Settings_Access.Screen_Size * 21.0f
						};
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.Fire.Data[static_cast<int>(Data_Access.Animation_Grid[
							Column][Row][0])], &Source, &Destination);
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Incinerator
							.Data[Rotation].Data[1], NULL, &Rectangles_Access.Tile_1x1);
						break;
					case Piezo_Generator:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.P_Generator, NULL,
							&Rectangles_Access.Tile_1x1);
						break;
					case Decoration:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Tile_Texture, NULL,
							&Rectangles_Access.Tile_1x1);
						break;
					case Bio_Generator:
						Centerpoint = { 60.0f * Settings_Access.Screen_Size,
							60.0f * Settings_Access.Screen_Size };
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.B_Generator
							.Data[Rotation].Data[3], NULL, &Rectangles_Access.Tile_3x3);
						if (Data_Access.Animation_Grid[Column][Row][0] == 1) {
							Data_Access.Animation_Grid[Column][Row][1] += 20.0 / UI_Access.Frame_Rate;
							if (Data_Access.Animation_Grid[Column][Row][1] >= 360) {
								Data_Access.Animation_Grid[Column][Row][1] = 0;
							}
						}
						SDL_RenderTextureRotated(Core_Access.Application_Renderer, Textures_Access.B_Generator
							.Data[Rotation].Data[2], NULL, &Rectangles_Access.Tile_3x3, Data_Access.Animation_Grid
							[Column][Row][1], &Centerpoint, SDL_FLIP_NONE);
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.B_Generator
							.Data[Rotation].Data[1], NULL, &Rectangles_Access.Tile_3x3);
						break;
					case Flowerpot:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Flowerpot, NULL,
							&Rectangles_Access.Tile_1x1);
						break;
					case Ammunition_Shelf:
						Selected_Rectangle = Rectangles_Access.Tile_1x2;
						if (Data_Access.Visual_Grid[Column][Row] - 52 == 0 ||
							Data_Access.Visual_Grid[Column][Row] - 52 == 2) {
							Selected_Rectangle = Rectangles_Access.Tile_2x1;
						}
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.A_Shelf
							.Data[Data_Access.Visual_Grid[Column][Row] - 52], NULL, &Selected_Rectangle);
						break;
					case Large_Pipe:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.L_Pipe
							.Data[Data_Access.Visual_Grid[Column][Row] - 71], NULL, &Rectangles_Access.Tile_1x1);
						break;
					case Heat_Exchanger:
						Selected_Rectangle = Rectangles_Access.Tile_4x3;
						if (!evn_i(Visual_To_Rotation(Data_Access.Visual_Grid[Column][Row]))) {
							Selected_Rectangle = Rectangles_Access.Tile_3x4;
						}
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.H_Exchanger
							.Data[Data_Access.Visual_Grid[Column][Row] - 87], NULL, &Selected_Rectangle);
						break;
					case Petrified_Wood:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.P_Wood,
							NULL, &Rectangles_Access.Tile_1x1);
						break;
					case Basalt_Tile:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.B_Tile,
							NULL, &Rectangles_Access.Tile_1x1);
						break;
					case Silicone_Carpet:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.S_Carpet,
							NULL, &Rectangles_Access.Tile_1x1);
						break;
					case Money_Generator:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.M_Generator,
							NULL, &Rectangles_Access.Tile_1x1);
						break;
					case Fluid_Generator:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.F_Generator,
							NULL, &Rectangles_Access.Tile_1x1);
						break;
					case Electrolytic_Cell:
						if (evn_i(Rotation)) {
							Selected_Rectangle = Rectangles_Access.Tile_3x2;
						} else {
							Selected_Rectangle = Rectangles_Access.Tile_2x3;
						}
						if (Data_Access.Visual_Grid[Column][Row] == 48) {
							SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
								.E_Plant.Data[0], NULL, &Rectangles_Access.Tile_3x2);
						} else {
							SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.E_Plant.Data
								[Data_Access.Visual_Grid[Column][Row] - 95], NULL, &Selected_Rectangle);
						}
						break;
					case Fluid_Mixer:
						Centerpoint = { 60.0f * Settings_Access.Screen_Size,
							60.0f * Settings_Access.Screen_Size };
						if (Data_Access.Animation_Grid[Column][Row][0] == 1) {
							Data_Access.Animation_Grid[Column][Row][1] += 90.0 / UI_Access.Frame_Rate;
							if (Data_Access.Animation_Grid[Column][Row][1] >= 360) {
								Data_Access.Animation_Grid[Column][Row][1] = 0;
							}
						}
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.F_Mixer
							.Data[Rotation].Data[3], NULL, &Rectangles_Access.Tile_3x3);
						SDL_RenderTextureRotated(Core_Access.Application_Renderer, Textures_Access.F_Mixer
							.Data[Rotation].Data[2], NULL, &Rectangles_Access.Tile_3x3, Data_Access.Animation_Grid
							[Column][Row][1], &Centerpoint, SDL_FLIP_NONE);
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.F_Mixer
							.Data[Rotation].Data[1], NULL, &Rectangles_Access.Tile_3x3);
						break;
					case R_Intersection:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.R_Intersection.Data[Visual_To_Rotation(Data_Access.Visual_Grid[
							Column][Row])], NULL, &Rectangles_Access.Tile_3x3);
						break;
					case L_Intersection:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.L_Intersection.Data[Visual_To_Rotation(Data_Access.Visual_Grid[
							Column][Row])], NULL, &Rectangles_Access.Tile_3x3);
						break;
					case Hazard_Strip:
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.H_Strip,
							NULL, &Rectangles_Access.Tile_1x1);
						break;
					case Distillery:
						Data_Access.Animation_Grid[Column][Row][0] += LDE_STATICRATE / UI_Access.Frame_Rate;
						if (Data_Access.Animation_Grid[Column][Row][0] >= 9) {
							Data_Access.Animation_Grid[Column][Row][0] = 0;
						}
						Source = {
							0,
							0,
							Settings_Access.Screen_Size * 20.0f,
							Settings_Access.Screen_Size * 20.0f
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
						Destination.x = ((Column * 40.0f) + Destination.x -
							UI_Access.Camera_X) * Settings_Access.Screen_Size;
						Destination.y = ((Row * 40.0f) + Destination.y -
							UI_Access.Camera_Y) * Settings_Access.Screen_Size;
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.Fire.Data[static_cast<int>(Data_Access.Animation_Grid[
							Column][Row][0])], &Source, &Destination);
						SDL_RenderTexture(Core_Access.Application_Renderer,
							Textures_Access.Distillery.Data[Rotation].Data[2], NULL,
							&Rectangles_Access.Tile_2x2);
						if (Data_Access.Settings_Grid[Column][Row][1] > 0) {
							SDL_RenderTexture(Core_Access.Application_Renderer,
								Textures_Access.Distillery.Data[Rotation].Data[3],
								NULL, &Rectangles_Access.Tile_2x2);
						}
						break;
					case Turbine_Input:
						if (evn_i(Rotation)) {
							SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
								.ST_Input.Data[Rotation], NULL, &Rectangles_Access.Tile_2x3);
						} else {
							SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
								.ST_Input.Data[Rotation], NULL, &Rectangles_Access.Tile_3x2);
						}
						break;
					case Turbine_Impulse: {
							SDL_Color Lightcolor = { 255, 0, 0 };
							if (Data_Access.Settings_Grid[Column][Row][3] == 1) {
								Lightcolor = { 255, 255, 0 };
							}
							//if active, set lights green
							SDL_FRect Lightplate = {
								static_cast<float>((40.0 * Column) - UI_Access
									.Camera_X) * Settings_Access.Screen_Size,
								static_cast<float>((40.0 * Row) + 21.0 - UI_Access
									.Camera_Y) * Settings_Access.Screen_Size,
								Settings_Access.Screen_Size * 120.0f,
								Settings_Access.Screen_Size * 38.0f
							};
							if (evn_i(Rotation)) {
								Lightplate = {
									static_cast<float>((40.0 * Column) + 21.0 - UI_Access
										.Camera_X) * Settings_Access.Screen_Size,
									static_cast<float>((40.0 * Row) - UI_Access.Camera_Y) *
										Settings_Access.Screen_Size,
									Settings_Access.Screen_Size * 38.0f,
									Settings_Access.Screen_Size * 120.0f
								};
							}
							Set_Renderer_Color(Lightcolor);
							SDL_RenderFillRect(Core_Access.Application_Renderer, &Lightplate);
							Clear_Renderer();
							if (evn_i(Rotation)) {
								SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
									.STIT_Block.Data[Rotation].Data[1], NULL, &Rectangles_Access.Tile_2x3);
							} else {
								SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
									.STIT_Block.Data[Rotation].Data[1], NULL, &Rectangles_Access.Tile_3x2);
							}
						}
						break;
					case Turbine_Output: {
							SDL_Color Lightcolor = { 255, 0, 0 };
							if (Data_Access.Settings_Grid[Column][Row][3] == 1) {
								Lightcolor = { 255, 255, 0 };
							}
							//if active, set lights green
							SDL_FRect Lightplate = {
								Settings_Access.Screen_Size * 21.0f,
								Settings_Access.Screen_Size * 40.0f,
								Settings_Access.Screen_Size * 38.0f,
								Settings_Access.Screen_Size * 40.0f
							};
							switch (Rotation) {
							case 1:
								Lightplate = {
									0,
									Settings_Access.Screen_Size * 21.0f,
									Settings_Access.Screen_Size * 40.0f,
									Settings_Access.Screen_Size * 38.0f
								};
								break;
							case 2:
								Lightplate = {
									Settings_Access.Screen_Size * 21.0f,
									0,
									Settings_Access.Screen_Size * 38.0f,
									Settings_Access.Screen_Size * 40.0f
								};
								break;
							case 3:
								Lightplate = {
									Settings_Access.Screen_Size * 40.0f,
									Settings_Access.Screen_Size * 21.0f,
									Settings_Access.Screen_Size * 40.0f,
									Settings_Access.Screen_Size * 38.0f
								};
								break;
							default:
								break;
							}
							Lightplate.x += ((Column * 40.0f) - UI_Access.Camera_X) * Settings_Access.Screen_Size;
							Lightplate.y += ((Row * 40.0f) - UI_Access.Camera_Y) * Settings_Access.Screen_Size;
							Set_Renderer_Color(Lightcolor);
							SDL_RenderFillRect(Core_Access.Application_Renderer, &Lightplate);
							Clear_Renderer();
							SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
								.ST_Output.Data[Rotation].Data[1], NULL, &Rectangles_Access.Tile_2x2);
							break;
						}
					case Algae_Bed:
						Selected_Rectangle = evn_i(Rotation) ? Rectangles_Access.Tile_2x3 :
							Rectangles_Access.Tile_3x2;
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.G_Bed.Data[Rotation].Data[2], NULL, &Selected_Rectangle);
						//bubbles
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.G_Bed.Data[Rotation].Data[1], NULL, &Selected_Rectangle);
						break;
					default:
						break;
					}
					if (Data_Access.Visual_Grid[Column][Row] == 21) {
						Rectangles_Access.Tunnel.Data[0].x = ((Column * 40.0f) -
							UI_Access.Camera_X) * Settings_Access.Screen_Size;
						Rectangles_Access.Tunnel.Data[0].y = (((Row - 2.25f) * 40.0f) -
							UI_Access.Camera_Y) * Settings_Access.Screen_Size;
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.S_Dock.Data[0], NULL, &Rectangles_Access.Tile_6x4);
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.Tunnel.Data[0], NULL, &Rectangles_Access.Tunnel.Data[0]);
					} else if (Data_Access.Visual_Grid[Column][Row] == 22) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.F_Plant.Data[2], NULL, &Rectangles_Access.Tile_2x3);
						SDL_FRect Offset_Rectangle = Rectangles_Access.Tile_2x3;
						if (Data_Access.Animation_Grid[Column][Row][0] == 0) {
							Data_Access.Animation_Grid[Column][Row][1] += 1.0f / UI_Access.Frame_Rate;
							SDL_FRect Progress_Rectangle = { Rectangles_Access.Tile_2x3.x + (19 *
								Settings_Access.Screen_Size), Rectangles_Access.Tile_2x3.y + (57 *
								Settings_Access.Screen_Size), static_cast<float>((50 * Data_Access.Animation_Grid
								[Column][Row][1]) *	Settings_Access.Screen_Size), 7.0f * Settings_Access.Screen_Size };
							Set_Renderer_Color(Colors_Access.Cherry_Blossom);
							SDL_RenderFillRect(Core_Access.Application_Renderer, &Progress_Rectangle);
							Clear_Renderer();
							Data_Access.Animation_Grid[Column][Row][2] += 64.0f / UI_Access.Frame_Rate;
							if (Data_Access.Animation_Grid[Column][Row][2] > ((double)32 / 6)) {
								Data_Access.Animation_Grid[Column][Row][2] = 0;
							}
							Offset_Rectangle.y += Data_Access.Animation_Grid[Column][Row][2] * Settings_Access.Screen_Size;
						}
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.F_Plant.Data[3], NULL, &Offset_Rectangle);
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.F_Plant.Data[1], NULL, &Rectangles_Access.Tile_2x3);
					} else if (Data_Access.Visual_Grid[Column][Row] > 23 && Data_Access.Visual_Grid[Column][Row] < 41) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.MS_Pool.Data[
							Data_Access.Visual_Grid[Column][Row] - 24], NULL, &Rectangles_Access.Tile_1x1);
					} else if (Data_Access.Visual_Grid[Column][Row] == 43) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.C_Platform.Data[0], NULL, &Rectangles_Access.Tile_8x6);
					} else if (Data_Access.Visual_Grid[Column][Row] == 44) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.B_Scrubber.Data[0], NULL, &Rectangles_Access.Tile_2x2);
					} else if (Data_Access.Visual_Grid[Column][Row] == 45) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.MS_Controller, NULL,
							&Rectangles_Access.Tile_1x1);
					} else if (Data_Access.Visual_Grid[Column][Row] == 46) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.MS_Output, NULL,
							&Rectangles_Access.Tile_1x1);
					} else if (Data_Access.Visual_Grid[Column][Row] == 47) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.MS_Input, NULL,
							&Rectangles_Access.Tile_1x1);
					} else if (Data_Access.Visual_Grid[Column][Row] == 50) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.T_Tower.Data[0], NULL,	&Rectangles_Access.Tile_3x3);
						if (Data_Access.Settings_Grid[Column][Row][3] == 0) {
							Rectangles_Access.RFlash.x = Rectangles_Access.Tile_3x3.x +
								(57 * Settings_Access.Screen_Size);
							Rectangles_Access.RFlash.y = Rectangles_Access.Tile_3x3.y +
								(57 * Settings_Access.Screen_Size);
							SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.RFlash,
								NULL, &Rectangles_Access.RFlash);
						}
					} else if (Data_Access.Visual_Grid[Column][Row] == 56) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.C_Platform.Data[1], NULL, &Rectangles_Access.Tile_6x8);
					} else if (Data_Access.Visual_Grid[Column][Row] == 57) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.C_Platform.Data[2], NULL, &Rectangles_Access.Tile_8x6);
					} else if (Data_Access.Visual_Grid[Column][Row] == 58) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
							.C_Platform.Data[3], NULL, &Rectangles_Access.Tile_6x8);
					} else if (Data_Access.Visual_Grid[Column][Row] > 59 && Data_Access.Visual_Grid[Column][Row] < 63) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.T_Tower.Data[
							Data_Access.Visual_Grid[Column][Row] - 59], NULL, &Rectangles_Access.Tile_3x3);
						if (Data_Access.Settings_Grid[Column][Row][3] == 0) {
							int X = 57;
							int Y = 57;
							switch (Data_Access.Visual_Grid[Column][Row] - 60) {
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
							Rectangles_Access.RFlash.x = Rectangles_Access.Tile_3x3.x +
								(X * Settings_Access.Screen_Size);
							Rectangles_Access.RFlash.y = Rectangles_Access.Tile_3x3.y +
								(Y * Settings_Access.Screen_Size);
							SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.RFlash,
								NULL, &Rectangles_Access.RFlash);
						}
					} else if (Data_Access.Visual_Grid[Column][Row] == 63) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.C_Node, NULL,
							&Rectangles_Access.Tile_1x1);
					} else if (Data_Access.Visual_Grid[Column][Row] > 63 && Data_Access.Visual_Grid[Column][Row] < 67) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.B_Scrubber.Data
							[Data_Access.Visual_Grid[Column][Row] - 63], NULL, &Rectangles_Access.Tile_2x2);
					} else if (Data_Access.Visual_Grid[Column][Row] == 67 || Data_Access.Visual_Grid[Column][Row] == 69) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.G_Well.Data
							[Data_Access.Visual_Grid[Column][Row] - 67], NULL, &Rectangles_Access.Tile_2x3);
					} else if (Data_Access.Visual_Grid[Column][Row] == 68 || Data_Access.Visual_Grid[Column][Row] == 70) {
						SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.G_Well.Data
							[Data_Access.Visual_Grid[Column][Row] - 67], NULL, &Rectangles_Access.Tile_3x2);
					}
					break;
				default:
					break;
				}
			}
		}
	}
}