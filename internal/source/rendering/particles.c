#include <rendering.h>

Particle* Particle_Grid[ktn_grid_size][ktn_grid_size] = { };
int Lengths[ktn_grid_size][ktn_grid_size] = { };
int Full_Lengths[ktn_grid_size][ktn_grid_size] = { };

void Push_Particle(const int Type, const Point Pos, const Point Subpos, const float Lifetime, const float Direction, const float Velocity, SDL_Texture* Icon,
	float Endscale, bool Fading) {
	if (Lengths[pt(Pos)] >= Full_Lengths[pt(Pos)]) {
		Full_Lengths[pt(Pos)] += 32;
		Particle_Grid[pt(Pos)] = realloc(Particle_Grid[pt(Pos)], sizeof(Particle) * Full_Lengths[pt(Pos)]);
	}
	Particle_Grid[pt(Pos)][Lengths[pt(Pos)]] = (Particle){ .Type = Type, .Pos = (Point_f){ Subpos.X, Subpos.Y }, .Max = Lifetime, .Dir = Direction, .Vel = Velocity,
		.Icon = Icon, .Endscale = Endscale, .Fading = Fading };
	Lengths[pt(Pos)]++;
}

void Wipe_Grid() {
	for (int X = 0; X < ktn_grid_size; X++) {
		for (int Y = 0; Y < ktn_grid_size; Y++) {
			ktn_free(Particle_Grid[X][Y]);
		}
	}
}

void Init_Grid() {
	Wipe_Grid();
	memset(Lengths, 0, sizeof(Lengths));
	for (int X = 0; X < ktn_grid_size; X++) {
		for (int Y = 0; Y < ktn_grid_size; Y++) {
			Particle_Grid[X][Y] = calloc(1, sizeof(Particle));
			Full_Lengths[X][Y] = 1;
		}
	}
}

void Pull_Particle(const Point Pos, const int Index) {
	if (Lengths[pt(Pos)] > 0) {
		Particle* Line = Particle_Grid[pt(Pos)];
		for (int C1 = 0; C1 < Lengths[pt(Pos)] - Index - 1; C1++) {
			Line[Index + C1] = Line[Index + C1 + 1];
		}
		Lengths[pt(Pos)]--;
	}
}

void Wipe_Tile(const Point Pos) {
	while (Lengths[pt(Pos)] > 0) {
		Pull_Particle(Pos, 0);
	}
}

void Render_Particles(const Point Pos) {
	for (int C1 = 0; C1 < Lengths[pt(Pos)]; C1++) {
		Particle Carrier = Particle_Grid[pt(Pos)][C1];
		Carrier.Delta += 1.0f / Interface.Frame_Rate;
		if (Carrier.Delta >= Carrier.Max) {
			Pull_Particle(Pos, C1);
			C1--;
			continue;
		}
		if (Carrier.Type == P_Standard) {
			Carrier.Pos.X -= cosf((ktn_pi / 180) * Carrier.Dir) * Carrier.Vel / Interface.Frame_Rate;
			Carrier.Pos.Y += sinf((ktn_pi / 180) * Carrier.Dir) * Carrier.Vel / Interface.Frame_Rate;
			Point_f Rootpos = {
				ktn_fscale((((Pos.X * 40) + Carrier.Pos.X) * Core.Ratio) - Core.Camera.X),
				ktn_fscale((((Pos.Y * 40) + Carrier.Pos.Y) * Core.Ratio) - Core.Camera.Y)
			};
			float Span = Carrier.Delta / Carrier.Max;
			float Size_Mul = ((Carrier.Endscale - 1) * Span) + 1;
			Point_f Size = {
				ktn_fscale(Carrier.Icon->w / 6) * Core.Ratio * Size_Mul,
				ktn_fscale(Carrier.Icon->h / 6) * Core.Ratio * Size_Mul
			};
			SDL_SetTextureAlphaMod(Carrier.Icon, (Carrier.Fading) ? 255 - (Span * 255) : 255);
			Render_Texture(Carrier.Icon, &(SDL_FRect){ Rootpos.X - (Size.X * 0.5f), Rootpos.Y - (Size.Y * 0.5f), Size.X, Size.Y });
		} else if (Carrier.Type == P_Bubble) {
			float Increment = Carrier.Max / 3.0f;
			Point_f Rootpos = {
				ktn_fscale((((Pos.X * 40) + Carrier.Pos.X) * Core.Ratio) - Core.Camera.X),
				ktn_fscale((((Pos.Y * 40) + Carrier.Pos.Y) * Core.Ratio) - Core.Camera.Y)
			};
			float Rootsize = ktn_fscale(Core.Ratio * 12.0f);
			if (Carrier.Delta < (Increment * 2.0f)) {
				float Size = (Carrier.Delta / (Increment * 2.0f)) * Rootsize;
				SDL_FRect Destination = { Rootpos.X - (Size * 0.5f), Rootpos.Y - (Size * 0.5f), Size, Size };
				Render_Texture(Textures.A_Bubble.Data[0], &Destination);
				if (Carrier.Delta >= Increment) {
					Size = (Increment - ((Carrier.Delta - Increment) / Increment)) * Rootsize;
					Destination = (SDL_FRect){ Rootpos.X - (Size * 0.5f), Rootpos.Y - (Size * 0.5f), Size, Size };
				}
				Render_Texture(Textures.A_Bubble.Data[1], &Destination);
			}
			if (Carrier.Delta >= Increment * 2.0f && Carrier.Delta < Carrier.Max) {
				SDL_FRect Destination = { Rootpos.X - (Rootsize * 0.5f), Rootpos.Y - (Rootsize * 0.5f), Rootsize, Rootsize };
				float Transparency = 1.0f - ((Carrier.Delta - (Increment * 2.0f)) / Increment);
				SDL_SetTextureAlphaModFloat(Textures.A_Bubble.Data[0], Transparency);
				Render_Texture(Textures.A_Bubble.Data[0], &Destination);
				SDL_SetTextureAlphaMod(Textures.A_Bubble.Data[0], SDL_ALPHA_OPAQUE);
			}
		}
		Particle_Grid[pt(Pos)][C1] = Carrier;
	}
}

void Render_Emitters() {
	for (int Column = 0; Column < ktn_grid_size; Column++) {
		Update_Tilestack(false, (int)((Column * Core.Tile_Size) - Core.Camera.X), true, ktn_invalid);
		for (int Row = 0; Row < ktn_grid_size; Row++) {
			Update_Tilestack(true, ktn_invalid, false, (int)((Row * Core.Tile_Size) - Core.Camera.Y));
			int Rotation = Visual_To_Rotation(Data.Visual_Grid[Column][Row]);
			Machine_Ptr Machine = Visual_To_Machine(Data.Visual_Grid[Column][Row]);
			if (!Machine) {
				continue;
			}
			if (Machine->Has_Emitter) {
				for (int C2 = 0; C2 < Machine->Emitter_Ct; C2++) {
					if (Data.Animation_Grid[Column][Row][0] > ktn_epsilon) {
						Data.Animation_Grid[Column][Row][C2 + 2] += Interface.Time_Positions[Interface.Slider_Positions[15]] / Interface.Frame_Rate;
						if (Data.Animation_Grid[Column][Row][C2 + 2] >= 1.0f / Machine->Emitter_Rate[C2]) {
							Data.Animation_Grid[Column][Row][C2 + 2] = 0;
							SDL_FRect Carrier = {
								Rects.Tile_1x1.x,
								Rects.Tile_1x1.y,
								ktn_evn(Rotation) ? Machine->Rect.w : Machine->Rect.h,
								ktn_evn(Rotation) ? Machine->Rect.h : Machine->Rect.w
							};
							ktn_tick();
							Point Subsize = { Machine->Size.X * 40, Machine->Size.Y * 40 };
							Point Subcarrier = Rotate_Px((Point){ Machine->Emitter_Pos[C2].X, Machine->Emitter_Pos[C2].Y }, Subsize, Rotation);
							float Direction = fmodf(Core.State, Machine->Emitter_Spread[C2] * 2) - (Machine->Emitter_Spread[C2]) + Machine->Emitter_Dir[C2];
							Push_Particle(P_Standard, (Point){ Column, Row }, Subcarrier, Machine->Emitter_Lifetime[C2], Direction, Machine->Emitter_Speed[C2],
								Machine->Emitter_Texture[C2], Machine->Emitter_Endscale[C2], Machine->Emitter_Fading[C2]);
						}
					}
				}
			}
			Render_Particles((Point){ Column, Row });
		}
	}
}