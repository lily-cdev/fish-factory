#include <rendering.h>

const float Deltas[1] = {
	5.0f
};

Particle* Particle_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
int Lengths[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };
int Full_Lengths[LDE_GRIDSIZE][LDE_GRIDSIZE] = { };

void Push_Particle(const int Type, const Point Pos, const Point_f Subpos) {
	if (Lengths[pt(Pos)] >= Full_Lengths[pt(Pos)]) {
		Full_Lengths[pt(Pos)] += 32;
		Particle_Grid[pt(Pos)] = realloc(Particle_Grid[pt(Pos)], sizeof(Particle) * Full_Lengths[pt(Pos)]);
	}
	Particle_Grid[pt(Pos)][Lengths[pt(Pos)]] = (Particle){
		.Type = Type,
		.Pos = Subpos,
		.Max = Deltas[Type]
	};
	Lengths[pt(Pos)]++;
}

void Wipe_Grid() {
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			free_c(Particle_Grid[X][Y]);
		}
	}
}

void Init_Grid() {
	Wipe_Grid();
	memset(Lengths, 0, sizeof(Lengths));
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
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
		if (Carrier.Type == P_Bubble) {
			float Increment = Carrier.Max / 3.0f;
			Point_f Rootpos = {
				((float)(Pos.X * LDE_TILESIZE) + Carrier.Pos.X - Core.Camera.X) * Settings.Scalar,
				((float)(Pos.Y * LDE_TILESIZE) + Carrier.Pos.Y - Core.Camera.Y) * Settings.Scalar
			};
			float Rootsize = Settings.Scalar * 12.0f;
			if (Carrier.Delta < (Increment * 2.0f)) {
				float Size = (Carrier.Delta / (Increment * 2.0f)) * Rootsize;
				SDL_FRect Destination = {
					Rootpos.X - (Size * 0.5f),
					Rootpos.Y - (Size * 0.5f),
					Size,
					Size
				};
				Render_Texture(Textures.A_Bubble.Data[0], &Destination);
				if (Carrier.Delta >= Increment) {
					Size = (Increment - ((Carrier.Delta - Increment) / Increment)) * Rootsize;
					Destination = (SDL_FRect){
						Rootpos.X - (Size * 0.5f),
						Rootpos.Y - (Size * 0.5f),
						Size,
						Size
					};
				}
				Render_Texture(Textures.A_Bubble.Data[1], &Destination);
			}
			if (Carrier.Delta >= Increment * 2.0f && Carrier.Delta < Carrier.Max) {
				SDL_FRect Destination = {
					Rootpos.X - (Rootsize * 0.5f),
					Rootpos.Y - (Rootsize * 0.5f),
					Rootsize,
					Rootsize
				};
				float Transparency = 1.0f - ((Carrier.Delta - (Increment * 2.0f)) / Increment);
				SDL_SetTextureAlphaModFloat(Textures.A_Bubble.Data[0], Transparency);
				Render_Texture(Textures.A_Bubble.Data[0], &Destination);
				SDL_SetTextureAlphaMod(Textures.A_Bubble.Data[0], SDL_ALPHA_OPAQUE);
			}
		}
		Particle_Grid[pt(Pos)][C1] = Carrier;
	}
}