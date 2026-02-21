#include <rendering.h>

Particle* Particles = { };
int Length = 0;
int Full_Length = 0;
const float Deltas[1] = {
	1.0f
};

void Push_Particle(const int Type, const Point_f Pos) {
	Length++;
	if (Length >= Full_Length) {
		Particle* Buffer = malloc(sizeof(Particle) * Length);
		memcpy_c(Buffer, Particles, sizeof(Particle) * Length);
		free_c(Particles);
		Full_Length += 16;
		Particles = malloc(sizeof(Particle) * Full_Length);
		memcpy_c(Particles, Buffer, sizeof(Particle) * Length);
		free_c(Buffer);
	}
	Particle Candidate = {
		.Type = Type,
		.Max = Deltas[Type],
		.Pos = Pos
	};
	Particles[Length - 1] = Candidate;
}

void Pull_Particle(const int Position) {
	if (Length > 0) {
		for (int C1 = 0; C1 < Length - Position - 1; C1++) {
			Particles[Position + C1] = Particles[Position + C1 + 1];
		}
		Length--;
	}
}

void Tick_Particles() {
	for (int C1 = 0; C1 < Length; C1++) {
		Particles[C1].Delta += 1.0f / Interface.Frame_Rate;
		if (Particles[C1].Delta >= Particles[C1].Max) {
			Pull_Particle(C1);
			C1--;
			continue;
		}
		if (Particles[C1].Type == P_Bubble) {
			float Increment = Particles[C1].Max / 3.0f;
			if (Particles[C1].Delta < Increment) {
				float Size = (Increment / Particles[C1].Delta) * Settings.Screen_Size * 12.0f;
				SDL_FRect Destination = {
					Particles[C1].Pos.X * Settings.Screen_Size,
					Particles[C1].Pos.Y * Settings.Screen_Size,
					Size,
					Size
				};
			} else if (Particles[C1].Delta < Increment * 2.0f) {
				//inner grow
			} else if (Particles[C1].Delta < Increment * 3.0f) {
				//fade
			} else {
				Pull_Particle(C1);
			}
		}
	}
}