#include <rendering.h>

void Render_Lighting() {
	for (int X = 0; X < 2; X++) {
		for (int Y = 0; Y < 2; Y++) {
			SDL_FRect Rect = {
				(Temporary.Pixels * X) - ktn_fscale(Core.Camera.X),
				(Temporary.Pixels * Y) - ktn_fscale(Core.Camera.Y),
				Temporary.Pixels,
				Temporary.Pixels
			};
			Render_Texture(Temporary.Lighting[(X * 2) + Y], &Rect);
		}
	}
}

void Adjust_Audio() {
	Point Pos;
	for (Pos.X = 0; Pos.X < Core.Tile_Size; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < Core.Tile_Size; Pos.Y++) {
			float A = ktn_fscale((Core.Camera.X + 320.0f) - (Pos.X * Core.Tile_Size));
			float B = ktn_fscale((Core.Camera.Y + 180.0f) - (Pos.Y * Core.Tile_Size));
			float Volume = ktn_sqr(1.0f - fminf((sqrtf(ktn_sqr(A) + ktn_sqr(B)) / ktn_fscale(2000)), 1.0f));
			for (int C1 = 0; C1 < Core.Machines; C1++) {
				if (Metadata.Machines[C1].Has_Audio) {
					ma_sound_set_volume(&Data.Audio_Grid[pt(Pos)][C1], Settings.Volume * Volume * 0.01f);
				}
			}
		}	
	}
}