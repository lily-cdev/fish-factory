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
	for (Pos.X = 0; Pos.X < ktn_tile_size; Pos.X++) {
		for (Pos.Y = 0; Pos.Y < ktn_tile_size; Pos.Y++) {
			Machine_Ptr Chosen = Visual_To_Machine(Data.Visual_Grid[pt(Pos)]);
			if (!Chosen || !Chosen->Has_Audio) {
				continue;
			}
			ma_sound* Carrier = &Visual_To_Machine(Data.Visual_Grid[pt(Pos)])->Run;
			float A = ktn_fscale((Core.Camera.X + 320.0f) - (Pos.X * ktn_tile_size));
			float B = ktn_fscale((Core.Camera.Y + 180.0f) - (Pos.Y * ktn_tile_size));
			float Volume = ktn_sqr(1.0f - fminf((sqrtf(ktn_sqr(A) + ktn_sqr(B)) / ktn_fscale(2000)), 1.0f));
			ma_sound_set_volume(Carrier, Volume);
		}	
	}
}