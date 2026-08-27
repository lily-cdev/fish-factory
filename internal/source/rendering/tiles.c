#include <rendering.h>

void Render_Grid() {
	for (int C1 = 0; C1 < 2; C1++) {
		for (int Column = 0; Column < ktn_grid_size; Column++) {
			Update_Tilestack(false, (int)((Column * Core.Tile_Size) - Core.Camera.X), true, ktn_invalid);
			for (int Row = 0; Row < ktn_grid_size; Row++) {
				Update_Tilestack(true, ktn_invalid, false, (int)((Row * Core.Tile_Size) - Core.Camera.Y));
				SDL_FRect Carrier;
				SDL_FPoint Centerpoint;
				Point Offset[4];
				SDL_FRect Source;
				SDL_FRect Destination;
				int Rotation = Visual_To_Rotation(Data.Visual_Grid[Column][Row]);
				switch (C1) {
				case 0:
					if (!ktn_stricmp(Data.Visual_Grid[Column][Row], ktn_strzero)) {
						Render_Texture(Textures.Tile_Texture, &Rects.Tile_1x1);
					}
					break;
				case 1:
					if (ktn_stricmp(Data.Visual_Grid[Column][Row], ktn_strzero)) {
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
							(ktn_evn(Rotation)) ? Machine->Rect.w : Machine->Rect.h,
							(ktn_evn(Rotation)) ? Machine->Rect.h : Machine->Rect.w
						};
						Render_Texture(Machine->Texture2.Data[Rotation], &Carrier);
						break;
					case A_Modular:
						int Max = strlen(Data.Visual_Grid[Column][Row]);
						char Buffer[3] = { 0 };
						Buffer[0] = Data.Visual_Grid[Column][Row][Max - 2];
						Buffer[1] = Data.Visual_Grid[Column][Row][Max - 1];
						if (Data.Visual_Grid[Column][Row][Max - 2] == '_') {
							Buffer[0] = Buffer[1];
							Buffer[1] = '\0';
						}
						Render_Texture(Machine->Texture2.Data[atoi(Buffer)], &Rects.Tile_1x1);
						break;
					case A_Spinner:
						Carrier = (SDL_FRect){
							Rects.Tile_1x1.x,
							Rects.Tile_1x1.y,
							ktn_evn(Rotation) ? Machine->Rect.w : Machine->Rect.h,
							ktn_evn(Rotation) ? Machine->Rect.h : Machine->Rect.w
						};
						Centerpoint = (SDL_FPoint){
							(ktn_evn(Rotation) ? Machine->Rect.w : Machine->Rect.h) * 0.5f,
							(ktn_evn(Rotation) ? Machine->Rect.h : Machine->Rect.w) * 0.5f
						};
						if (Data.Animation_Grid[Column][Row][0] > ktn_epsilon) {
							Data.Animation_Grid[Column][Row][1] += (Interface.Time_Positions[Interface.Slider_Positions[15]] * (float)Machine->Spin_Data.Speed) /
								Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][1] >= 360) {
								Data.Animation_Grid[Column][Row][1] = 0;
							}
						}
						Render_Texture(Machine->Texture3.Data[Rotation].Data[3], &Carrier);
						SDL_RenderTextureRotated(Core.Renderer, Machine->Texture3.Data[Rotation].Data[2], NULL, &Carrier,
							Data.Animation_Grid[Column][Row][1], &Centerpoint, SDL_FLIP_NONE);
						Render_Texture(Machine->Texture3.Data[Rotation].Data[1], &Carrier);
						break;
					case A_Gauged:
						Carrier = (SDL_FRect){
							Rects.Tile_1x1.x,
							Rects.Tile_1x1.y,
							ktn_evn(Rotation) ? Machine->Rect.w : Machine->Rect.h,
							ktn_evn(Rotation) ? Machine->Rect.h : Machine->Rect.w
						};
						Render_Texture(Machine->Texture2.Data[Rotation], &Carrier);
						float Width = (Data.Data_Grid[Column][Row][Stored_Power] / Data.Data_Grid[Column][Row][Power_Cap]) *
							Machine->Gauge_Data.Size.X;
						Point Subsize = { Machine->Size.X * Core.Tile_Size, Machine->Size.Y * Core.Tile_Size };
						Point Origin = Rotate_Px(Machine->Gauge_Data.Pos, Subsize, Rotation);
						Point End = Rotate_Px((Point){ Machine->Gauge_Data.Pos.X + Width, Machine->Gauge_Data.Pos.Y +
							Machine->Gauge_Data.Size.Y }, Subsize, Rotation);
						SDL_FRect Rect = {
							ktn_fscale((Column * Core.Tile_Size) + Origin.X - Core.Camera.X),
							ktn_fscale((Row * Core.Tile_Size) + Origin.Y - Core.Camera.Y),
							ktn_fscale(End.X - Origin.X),
							ktn_fscale(End.Y - Origin.Y)
						};
						Set_Renderer_Color(Colors.Cherry_Blossom);
						SDL_RenderFillRect(Core.Renderer, &Rect);
						Clear_Renderer();
						break;
					case A_Kiln:
						Carrier = (SDL_FRect){
							Rects.Tile_1x1.x,
							Rects.Tile_1x1.y,
							ktn_evn(Rotation) ? Machine->Rect.w : Machine->Rect.h,
							ktn_evn(Rotation) ? Machine->Rect.h : Machine->Rect.w
						};
						Render_Texture(Machine->Texture3.Data[Rotation].Data[2], &Carrier);
						if (Data.Animation_Grid[Column][Row][0] > ktn_epsilon) {
							Data.Animation_Grid[Column][Row][1] += (Interface.Time_Positions[Interface.Slider_Positions[15]] * (float)ktn_static_rate) /
								Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][1] >= 9) {
								Data.Animation_Grid[Column][Row][1] = 0;
							}
							Source = (SDL_FRect){ 0, 0, ktn_fscale(Machine->Kiln_Data.Size.X), ktn_fscale(Machine->Kiln_Data.Size.Y) };
							Point Subsize = { Machine->Size.X * Core.Tile_Size, Machine->Size.Y * Core.Tile_Size };
							Point Origin = Rotate_Px(Machine->Kiln_Data.Pos, Subsize, Rotation);
							Point End = Rotate_Px((Point){ Machine->Kiln_Data.Pos.X + Machine->Kiln_Data.Size.X, Machine->Kiln_Data.Pos.Y + Machine->Kiln_Data.Size.Y },
								Subsize, Rotation);
							Destination = (SDL_FRect){
								ktn_fscale((((Column * 40) + Origin.X) * Core.Ratio) - Core.Camera.X),
								ktn_fscale((((Row * 40) + Origin.Y) * Core.Ratio) - Core.Camera.Y),
								ktn_fscale((End.X - Origin.X) * Core.Ratio),
								ktn_fscale((End.Y - Origin.Y) * Core.Ratio)
							};
							SDL_RenderTexture(Core.Renderer, Textures.Fire.Data[(int)(Data.Animation_Grid[Column][Row][1])], &Source,
								&Destination);
						}
						Render_Texture(Machine->Texture3.Data[Rotation].Data[1], &Carrier);
						break;
					case A_RL_Drag:
						Carrier = (SDL_FRect){
							Rects.Tile_1x1.x,
							Rects.Tile_1x1.y,
							ktn_evn(Rotation) ? Machine->Rect.w : Machine->Rect.h,
							ktn_evn(Rotation) ? Machine->Rect.h : Machine->Rect.w
						};
						float Subcarrier = 0;
						if (Data.Animation_Grid[Column][Row][0] > ktn_epsilon) {
							if (Data.Animation_Grid[Column][Row][1] < Machine->RL_Drag_Data.Start) {
								Subcarrier = 0;
							} else if (Data.Animation_Grid[Column][Row][1] < Machine->RL_Drag_Data.Return) {
								Subcarrier = ktn_fscale(Machine->RL_Drag_Data.Delta) * ((Data.Animation_Grid[Column][Row][1] -
									Machine->RL_Drag_Data.Start) / (Machine->RL_Drag_Data.Return - Machine->RL_Drag_Data.Start));
							} else if (Data.Animation_Grid[Column][Row][1] < Machine->RL_Drag_Data.End) {
								Subcarrier = ktn_fscale(Machine->RL_Drag_Data.Delta);
							} else if (Data.Animation_Grid[Column][Row][1] < 1.0f) {
								Subcarrier = ktn_fscale(Machine->RL_Drag_Data.Delta) * (1.0f - ((Data.Animation_Grid[Column][Row][1] -
									Machine->RL_Drag_Data.End) / (1.0f - Machine->RL_Drag_Data.End)));
							} else {
								Data.Animation_Grid[Column][Row][1] = 0.0f;
							}
							Data.Animation_Grid[Column][Row][1] += Interface.Time_Positions[Interface.Slider_Positions[15]] / Interface.Frame_Rate;
						} else {
							Data.Animation_Grid[Column][Row][1] = 0.0f;
						}
						Subcarrier *= Core.Ratio;
						Render_Texture(Machine->Texture3.Data[Rotation].Data[1], &Carrier);
						switch (Rotation + 1) {
						case Left:
							Carrier.x += Subcarrier;
							break;
						case Up:
							Carrier.y += Subcarrier;
							break;
						case Right:
							Carrier.x -= Subcarrier;
							break;
						case Down:
							Carrier.y -= Subcarrier;
							break;
						default:
							break;
						}
						Render_Texture(Machine->Texture3.Data[Rotation].Data[2], &Carrier);
						break;
					case A_None:
						if (ktn_stricmp(Machine->Index, "ram_pump")) {
							if (Data.Animation_Grid[Column][Row][0] > ktn_epsilon) {
								Data.Animation_Grid[Column][Row][1] += 60.0f / Interface.Frame_Rate;
								if (Data.Animation_Grid[Column][Row][1] >= 360) {
									Data.Animation_Grid[Column][Row][1] = 0;
								}
							}
							Render_Texture(Machine->Texture2.Data[3], &Rects.Tile_1x1);
							SDL_RenderTextureRotated(Core.Renderer, Machine->Texture2.Data[2], NULL,
								&Rects.Tile_1x1, Data.Animation_Grid[Column][Row][1], &Interface.Tile_Centerpoint,
								SDL_FLIP_NONE);
							Render_Texture(Machine->Texture2.Data[1], &Rects.Tile_1x1);
						} else if (ktn_stricmp(Machine->Index, "turbine_impulse")) {
							SDL_Color Lightcolor = { 255, 0, 0 };
							if (Data.Settings_Grid[Column][Row][3] == 1) {
								Lightcolor = (SDL_Color){ 0, 255, 0 };
							}
							SDL_FRect Lightplate = {
								ktn_fscale((Column * Core.Tile_Size) - Core.Camera.X),
								ktn_fscale((Row * Core.Tile_Size) - Core.Camera.Y + 21.0f),
								ktn_fscale(120.0f),
								ktn_fscale(38.0f)
							};
							if (ktn_evn(Rotation)) {
								Lightplate = (SDL_FRect){
									ktn_fscale((Column * Core.Tile_Size)- Core.Camera.X + 21.0f),
									ktn_fscale((Row * Core.Tile_Size) - Core.Camera.Y),
									ktn_fscale(38.0f),
									ktn_fscale(120.0f)
								};
							}
							Set_Renderer_Color(Lightcolor);
							SDL_RenderFillRect(Core.Renderer, &Lightplate);
							Clear_Renderer();
							SDL_FRect Carrier = (ktn_evn(Rotation)) ? Rects.Tile_2x3 : Rects.Tile_3x2;
							Render_Texture(Machine->Texture3.Data[Rotation].Data[1], &Carrier);
						} else if (ktn_stricmp(Machine->Index, "turbine_output")) {
							SDL_Color Lightcolor = { 255, 0, 0 };
							if (Data.Settings_Grid[Column][Row][3] == 1) {
								Lightcolor = (SDL_Color){ 0, 255, 0 };
							}
							SDL_FRect Lightplate;
							#define Set_Lightplate(X, Y, W, H) Lightplate = (SDL_FRect) { \
									Lightplate.x = ktn_fscale((float)(X)), \
									Lightplate.y = ktn_fscale((float)(Y)), \
									Lightplate.w = ktn_fscale((float)(W)), \
									Lightplate.h = ktn_fscale((float)(H)), \
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
							Lightplate.x += ktn_fscale((Column * Core.Tile_Size) - Core.Camera.X);
							Lightplate.y += ktn_fscale((Row * Core.Tile_Size) - Core.Camera.Y);
							Set_Renderer_Color(Lightcolor);
							SDL_RenderFillRect(Core.Renderer, &Lightplate);
							Clear_Renderer();
							Render_Texture(Machine->Texture3.Data[Rotation].Data[1], &Rects.Tile_2x2);
						} else if (ktn_stricmp(Machine->Index, "electro_cell")) {
							Carrier = (ktn_evn(Rotation)) ? Rects.Tile_3x2 : Rects.Tile_2x3;
							Render_Texture(Machine->Texture3.Data[Rotation].Data[0], &Carrier);
						} else if (ktn_stricmp(Machine->Index, "distillery")) {
							Data.Animation_Grid[Column][Row][0] += (Interface.Time_Positions[Interface.Slider_Positions[15]] * ktn_static_rate) / Interface.Frame_Rate;
							if (Data.Animation_Grid[Column][Row][0] >= 9) {
								Data.Animation_Grid[Column][Row][0] = 0;
							}
							Source = (SDL_FRect){ 0.0f, 0.0f, ktn_fscale(20.0f), ktn_fscale(20.0f) };
							Destination = (SDL_FRect){ 12.0f, 12.0f, Source.w, Source.h };
							if (Rotation == 1 || Rotation == 2) {
								Destination.x = 43.0f;
							}
							if (Rotation == 2 || Rotation == 3) {
								Destination.y = 43.0f;
							}
							Destination.x = ktn_fscale((Column * Core.Tile_Size) + Destination.x - Core.Camera.X);
							Destination.y = ktn_fscale((Row * Core.Tile_Size) + Destination.y - Core.Camera.Y);
							SDL_RenderTexture(Core.Renderer, Textures.Fire.Data[(int)(Data.Animation_Grid[Column][Row][0])],
								&Source, &Destination);
							Render_Texture(Machine->Texture3.Data[Rotation].Data[2], &Rects.Tile_2x2);
							if (Data.Settings_Grid[Column][Row][S_Time] > 0) {
								Render_Texture(Machine->Texture3.Data[Rotation].Data[3], &Rects.Tile_2x2);
							}
						} else if (ktn_stricmp(Machine->Index, "algae_bed")) {
							Carrier = ktn_evn(Rotation) ? Rects.Tile_2x3 : Rects.Tile_3x2;
							Render_Texture(Machine->Texture3.Data[Rotation].Data[2], &Carrier);
							if (Data.Animation_Grid[Column][Row][0] > ktn_epsilon) {
								Data.Animation_Grid[Column][Row][1] += Interface.Time_Positions[Interface.Slider_Positions[15]] / Interface.Frame_Rate;
								if (Data.Animation_Grid[Column][Row][1] >= 0.5f) {
									Data.Animation_Grid[Column][Row][1] = 0;
									ktn_tick();
									Point Coordinate = { (Core.State % 52) + 16 };
									ktn_tick();
									Coordinate.Y = (Core.State % 52) + 16;
									Push_Particle(P_Bubble, (Point){ Column, Row }, Rotate_Px(Coordinate, (Point){ Carrier.x, Carrier.y },
										Rotation));
								}
							}
							Render_Particles((Point){ Column, Row });
							Render_Texture(Machine->Texture3.Data[Rotation].Data[1], &Carrier);
						} else if (ktn_stricmp(Machine->Index, "signal_tower")) {
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
								Rects.R_Flash.x = ktn_fscale(X) + Rects.Tile_3x3.x;
								Rects.R_Flash.y = ktn_fscale(Y) + Rects.Tile_3x3.y;
								Render_Texture(Textures.R_Flash, &Rects.R_Flash);
							}
						}
						break;
					default:
						break;
					}
					if (ktn_stricmp(Machine->Index, "sub_dock")) {
						Rects.Tunnel.Data[0].x = ktn_fscale((Column * Core.Tile_Size) - Core.Camera.X);
						Rects.Tunnel.Data[0].y = ktn_fscale(((Row - 2.25f) * Core.Tile_Size) - Core.Camera.Y);
						Render_Texture(Textures.Tunnel.Data[0], &Rects.Tunnel.Data[0]);
					}
					break;
				default:
					break;
				}
			}
		}
	}
}