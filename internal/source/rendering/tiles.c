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
					Machine_Ptr Machine = Visual_To_Machine(Data.Visual_Grid[Column][Row]);
					if (!Machine) {
						break;
					}
					switch (Machine->Animation_Type) {
					case A_Static:
						Carrier = (SDL_FRect){
							Rects.Tile_1x1.x,
							Rects.Tile_1x1.y,
							Machine->Rect.w,
							Machine->Rect.h
						};
						Render_Texture(Machine->Texture1, &Carrier);
						break;
					case A_Rot:
						Carrier = (SDL_FRect){
							Rects.Tile_1x1.x,
							Rects.Tile_1x1.y,
							(evn(Rotation)) ? Machine->Rect.w : Machine->Rect.h,
							(evn(Rotation)) ? Machine->Rect.h : Machine->Rect.w
						};
						Render_Texture(Machine->Texture2.Data[Rotation], &Carrier);
						break;
					case A_Modular:
						if (stricmp(Machine->Index, "heavy_pipe")) {
							Render_Texture(Machine->Texture2.Data[Data.Visual_Grid[Column][Row] - 1], &Rects.Tile_1x1);
						} else if (stricmp(Machine->Index, "large_pipe")) {	
							Render_Texture(Machine->Texture2.Data[Data.Visual_Grid[Column][Row] - 71], &Rects.Tile_1x1);
						} else if (stricmp(Machine->Index, "spawning_pool")) {
							Render_Texture(Machine->Texture2.Data[Data.Visual_Grid[Column][Row] - 24], &Rects.Tile_1x1);
						}
						break;
					case A_Spinner:
						Carrier = (SDL_FRect){
							Rects.Tile_1x1.x,
							Rects.Tile_1x1.y,
							(evn(Rotation)) ? Machine->Rect.w : Machine->Rect.h,
							(evn(Rotation)) ? Machine->Rect.h : Machine->Rect.w
						};
						Centerpoint = (SDL_FPoint){ Machine->Rect.w * 0.5f, Machine->Rect.h * 0.5f };
						if (Data.Animation_Grid[Column][Row][0] == 1) {
							Data.Animation_Grid[Column][Row][1] += ((float)Machine->Spin_Data.Speed) / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][1] >= 360) {
								Data.Animation_Grid[Column][Row][1] = 0;
							}
						}
						Render_Texture(Machine->Texture3.Data[Rotation].Data[3], &Carrier);
						SDL_RenderTextureRotated(Core.Renderer, Machine->Texture3.Data[Rotation].Data[2], NULL, &Carrier,
							Data.Animation_Grid[Column][Row][1], &Centerpoint, SDL_FLIP_NONE);
						Render_Texture(Machine->Texture3.Data[Rotation].Data[1], &Carrier);
					case A_None:
						if (stricmp(Machine->Index, "ram_pump")) {
							Render_Texture(Machine->Texture2.Data[1], &Rects.Tile_1x1);
							if (Data.Animation_Grid[Column][Row][0] == 0) {
								Data.Animation_Grid[Column][Row][1] += 60.0f / Interface.Frame_Rate;
								if (Data.Animation_Grid[Column][Row][1] >= 360) {
									Data.Animation_Grid[Column][Row][1] = 0;
								}
							}
							SDL_RenderTextureRotated(Core.Renderer, Machine->Texture2.Data[2], NULL,
								&Rects.Tile_1x1, Data.Animation_Grid[Column][Row][1], &Interface.Tile_Centerpoint,
								SDL_FLIP_NONE);
							{
								const Point Offsets[4] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };
								for (int C1 = 0; C1 < 4; C1++) {
									Point Pos = { Column + Offsets[C1].X, Row + Offsets[C1].Y };
									if ((Data.Plumbing_Grid[pt(Pos)] == C1 + 1 || Data.Plumbing_Grid[pt(Pos)] == Any) && (
										Data.Settings_Grid[pt(Pos)][0] == F_In || Data.Settings_Grid[pt(Pos)][0] == F_Either)) {
										Render_Texture(Machine->Texture2.Data[((C1 + 2) & 3) + 3],
											&Rects.Tile_1x1);
									}
								}
							}
						} else if (stricmp(Machine->Index, "incinerator")) {
							Data.Animation_Grid[Column][Row][0] += LDE_STATICRATE / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][0] >= 9) {
								Data.Animation_Grid[Column][Row][0] = 0;
							}
							Source = (SDL_FRect){ 0.0f, 0.0f, scale_f(21.0f), scale_f(21.0f) };
							Destination = (SDL_FRect){
								((scale_f(LDE_TILESIZE) - Source.w) * 0.5f) + scale_f(Column * LDE_TILESIZE) - scale_f(
									Core.Camera.X),
								((scale_f(LDE_TILESIZE) - Source.w) * 0.5f) + scale_f(Row * LDE_TILESIZE) - scale_f(Core.Camera.Y),
								scale_f(21.0f),
								scale_f(21.0f)
							};
							SDL_RenderTexture(Core.Renderer, Textures.Fire.Data[(int)(Data.Animation_Grid[Column][Row][0])],
								&Source, &Destination);
							Render_Texture(Machine->Texture3.Data[Rotation].Data[1], &Rects.Tile_1x1);
						} else if (stricmp(Machine->Index, "turbine_impulse")) {
							SDL_Color Lightcolor = { 255, 0, 0 };
							if (Data.Settings_Grid[Column][Row][3] == 1) {
								Lightcolor = (SDL_Color){ 255, 255, 0 };
							}
							//if active, set lights green
							SDL_FRect Lightplate = {
								scale_f((Column * LDE_TILESIZE) - Core.Camera.X),
								scale_f((Row * LDE_TILESIZE) - Core.Camera.Y + 21.0f),
								scale_f(120.0f),
								scale_f(38.0f)
							};
							if (evn(Rotation)) {
								Lightplate = (SDL_FRect){
									scale_f((Column * LDE_TILESIZE)- Core.Camera.X + 21.0f),
									scale_f((Row * LDE_TILESIZE) - Core.Camera.Y),
									scale_f(38.0f),
									scale_f(120.0f)
								};
							}
							Set_Renderer_Color(Lightcolor);
							SDL_RenderFillRect(Core.Renderer, &Lightplate);
							Clear_Renderer();
							SDL_FRect Carrier = (evn(Rotation)) ? Rects.Tile_2x3 : Rects.Tile_3x2;
							Render_Texture(Machine->Texture3.Data[Rotation].Data[1], &Carrier);
						} else if (stricmp(Machine->Index, "turbine_output")) {
							SDL_Color Lightcolor = { 255, 0, 0 };
							if (Data.Settings_Grid[Column][Row][3] == 1) {
								Lightcolor.r = 255;
								Lightcolor.g = 255;
								Lightcolor.b = 0;
							}
							//if active, set lights green
							SDL_FRect Lightplate;
							#define Set_Lightplate(X, Y, W, H) Lightplate = (SDL_FRect) { \
									Lightplate.x = Settings.Scalar * ((float)(X)), \
									Lightplate.y = Settings.Scalar * ((float)(Y)), \
									Lightplate.w = Settings.Scalar * ((float)(W)), \
									Lightplate.h = Settings.Scalar * ((float)(H)), \
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
							Lightplate.x += scale_f((Column * LDE_TILESIZE) - Core.Camera.X);
							Lightplate.y += scale_f((Row * LDE_TILESIZE) - Core.Camera.Y);
							Set_Renderer_Color(Lightcolor);
							SDL_RenderFillRect(Core.Renderer, &Lightplate);
							Clear_Renderer();
							Render_Texture(Machine->Texture3.Data[Rotation].Data[1],
								&Rects.Tile_2x2);
						} else if (stricmp(Machine->Index, "electro_cell")) {
							Carrier = (evn(Rotation)) ? Rects.Tile_3x2 : Rects.Tile_2x3;
							Render_Texture(Machine->Texture3.Data[Rotation].Data[0], &Carrier);
						} else if (stricmp(Machine->Index, "distillery")) {
							Data.Animation_Grid[Column][Row][0] += LDE_STATICRATE / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][0] >= 9) {
								Data.Animation_Grid[Column][Row][0] = 0;
							}
							Source = (SDL_FRect){ 0.0f, 0.0f, scale_f(20.0f), scale_f(20.0f) };
							Destination = (SDL_FRect){ 12.0f, 12.0f, Source.w, Source.h };
							if (Rotation == 1 || Rotation == 2) {
								Destination.x = 43.0f;
							}
							if (Rotation == 2 || Rotation == 3) {
								Destination.y = 43.0f;
							}
							Destination.x = scale_f((Column * LDE_TILESIZE) + Destination.x - Core.Camera.X);
							Destination.y = scale_f((Row * LDE_TILESIZE) + Destination.y - Core.Camera.Y);
							SDL_RenderTexture(Core.Renderer, Textures.Fire.Data[(int)(Data.Animation_Grid[Column][Row][0])],
								&Source, &Destination);
							Render_Texture(Machine->Texture3.Data[Rotation].Data[2], &Rects.Tile_2x2);
							if (Data.Settings_Grid[Column][Row][S_Time] > 0) {
								Render_Texture(Machine->Texture3.Data[Rotation].Data[3], &Rects.Tile_2x2);
							}
						} else if (stricmp(Machine->Index, "algae_bed")) {
							Carrier = evn(Rotation) ? Rects.Tile_2x3 : Rects.Tile_3x2;
							Render_Texture(Machine->Texture3.Data[Rotation].Data[2], &Carrier);
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
							Render_Texture(Machine->Texture3.Data[Rotation].Data[1], &Carrier);
						} else if (stricmp(Machine->Index, "battery")) {	
							Render_Texture(Machine->Texture2.Data[Rotation], &Rects.Tile_2x2);
						} else if (stricmp(Machine->Index, "signal_tower")) {
							Render_Texture(Machine->Texture2.Data[Rotation], &Rects.Tile_3x3);
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
								Rects.R_Flash.x = scale_f(X) + Rects.Tile_3x3.x;
								Rects.R_Flash.y = scale_f(Y) + Rects.Tile_3x3.y;
								Render_Texture(Textures.R_Flash, &Rects.R_Flash);
							}
						} else if (stricmp(Machine->Index, "sub_dock")) {
							Rects.Tunnel.Data[0].x = scale_f((Column * LDE_TILESIZE) - Core.Camera.X);
							Rects.Tunnel.Data[0].y = scale_f(((Row - 2.25f) * LDE_TILESIZE) - Core.Camera.Y);
							Render_Texture(Machine->Texture2.Data[0], &Rects.Tile_6x4);
							Render_Texture(Textures.Tunnel.Data[0], &Rects.Tunnel.Data[0]);
						} else if (stricmp(Machine->Index, "filtration_plant")) {
							Render_Texture(Machine->Texture2.Data[2], &Rects.Tile_2x3);
							SDL_FRect Offset_Rectangle = Rects.Tile_2x3;
							if (Data.Animation_Grid[Column][Row][0] == 0) {
								Data.Animation_Grid[Column][Row][1] += 1.0f / Interface.Frame_Rate;
								SDL_FRect Progress_Rectangle = {
									scale_f(19.0f) + Rects.Tile_2x3.x,
									scale_f(57.0f) + Rects.Tile_2x3.y,
									scale_f(Data.Animation_Grid[Column][Row][1] * 50.0f),
									Settings.Scalar * 7.0f
								};
								Set_Renderer_Color(Colors.Cherry_Blossom);
								SDL_RenderFillRect(Core.Renderer, &Progress_Rectangle);
								Clear_Renderer();
								Data.Animation_Grid[Column][Row][2] += 64.0f / Interface.Frame_Rate;
								if (Data.Animation_Grid[Column][Row][2] > 16.0f / 3.0f) {
									Data.Animation_Grid[Column][Row][2] = 0;
								}
								Offset_Rectangle.y += scale_f(Data.Animation_Grid[Column][Row][2]);
							}
							Render_Texture(Machine->Texture2.Data[3], &Offset_Rectangle);
							Render_Texture(Machine->Texture2.Data[1], &Rects.Tile_2x3);
						}
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
			}
		}
	}
}