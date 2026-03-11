#include <transitions.h>

TRANSITION Transition = {
	.Queried_Tab = 0,
	.Frames = 0,
	.Max_Frames = 0,
	.Phase = LDE_INVALID,
	.Sub_Pos = { LDE_INVALID, LDE_INVALID },
	.Sub_Side = 1,
	.Sub_Phase = LDE_INVALID,
	.Sub_Offset = 0,
	.Sub_Vertical = 0
};

float Ease_Sine(float Time) {
	return -(cos(M_PI * Time) - 1.0f) * 0.5f;
}

void Start_Transition(int Tab) {
	Transition.Queried_Tab = Tab;
	Transition.Max_Frames = Interface.Frame_Rate * 0.5f;
	Transition.Frames = 0;
	Transition.Phase = 0;
	Interface.Locked = true;
}

void Force_Opening() {
	Transition.Phase = 2;
	Transition.Frames = 0;
	Transition.Queried_Tab = Interface.UI_Tab;
	Transition.Max_Frames = (int)(Interface.Frame_Rate * 0.5f);
	Trigger_Ambiance();
}

void Render_Closing(bool Clearing) {
	if (Transition.Phase == 0) {
		if (Transition.Frames < Transition.Max_Frames) {
			Transition.Frames++;
			float Percentage = Ease_Sine((float)Transition.Frames / Transition.Max_Frames);
			Rects.Door[0].x = (int)(((Settings.Screen_Size * 320) * Percentage) - (Settings.Screen_Size * 320));
			Rects.Door[1].x = (int)((Settings.Screen_Size * 640) - ((Settings.Screen_Size * 320) * Percentage));
		} else {
			Transition.Phase = 1;
			Interface.UI_Tab = LDE_INVALID;
			Transition.Frames = 0;
			Transition.Max_Frames = (int)(Interface.Frame_Rate / 1.5f);
			Rects.Door[0].x = 0;
			Rects.Door[1].x = Settings.Screen_Size * 320;
			if (Clearing) {	
				Interface.Log_Offset = 0;
				Temporary.Scroll_Percent = 0;
				Interface.Slider_Positions[2] = 0;
			}
		}
		Render_Texture(Textures.Door.Data[0], &Rects.Door[0]);
		Render_Texture(Textures.Door.Data[1], &Rects.Door[1]);
	}
}

void Render_Opening() {
	if (Transition.Phase == 2) {
		if (Transition.Frames < Transition.Max_Frames) {
			Transition.Frames++;
			float Percentage = Ease_Sine((float)Transition.Frames / Transition.Max_Frames);
			Rects.Door[0].x = (int)(-((Settings.Screen_Size * 320) * Percentage));
			Rects.Door[1].x = (int)((Settings.Screen_Size * 320) + ((Settings.Screen_Size * 320) * Percentage));
			Render_Texture(Textures.Door.Data[0], &Rects.Door[0]);
			Render_Texture(Textures.Door.Data[1], &Rects.Door[1]);
			SDL_FRect Indicator_Rectangle = {
				(float)(((Percentage * 320) + 342.5f) * Settings.Screen_Size),
				(float)(((1471 / 6.0f) - 20) * Settings.Screen_Size),
				(float)Settings.Screen_Size * LDE_TILESIZE,
				(float)Settings.Screen_Size * LDE_TILESIZE
			};
			Render_Texture(Textures.R_Flash, &Indicator_Rectangle);
		} else {
			Transition.Phase = LDE_INVALID;
			Interface.Locked = false;
		}
	}
}

void Trigger_Ambiance() {
	Terminate_Sound(Ambience1);
	switch (Transition.Queried_Tab) {
	case 0:
		Play_Sound(Ambience1, true);
		break;
	default:
		break;
	}
}

void Render_Submarine() {
	if (Transition.Sub_Phase != LDE_INVALID) {
		switch (Transition.Sub_Phase) {
		case 0:
			Transition.Sub_Offset -= (float)(LDE_VESSELSPEED * LDE_TILESIZE) / Interface.Frame_Rate;
			if (Transition.Sub_Offset < (Transition.Sub_Pos.X * LDE_TILESIZE) + 120) {
				Transition.Sub_Offset = (Transition.Sub_Pos.X * LDE_TILESIZE) + 120;
				Transition.Sub_Phase = 1;
			}
			break;
		case 1:
			Transition.Sub_Vertical -= 5.0f / Interface.Frame_Rate;
			if (Transition.Sub_Vertical < 85) {
				Transition.Sub_Vertical = 85;
				Transition.Sub_Phase = 2;
			}
			break;
		case 3:
			Transition.Sub_Vertical += 5.0f / Interface.Frame_Rate;
			if (Transition.Sub_Vertical > 105) {
				Transition.Sub_Vertical = 105;
				Transition.Sub_Phase = 4;
			}
			break;
		case 4:
			Transition.Sub_Offset -= (float)(LDE_VESSELSPEED * LDE_TILESIZE) / Interface.Frame_Rate;
			if (Transition.Sub_Offset < -3000) {
				Transition.Sub_Offset = 3000;
				Transition.Sub_Phase = LDE_INVALID;
				Transition.Sub_Pos.X = LDE_INVALID;
				Transition.Sub_Pos.Y = LDE_INVALID;
			}
			break;
		default:
			break;
		}
		Rects.Submarine.x = (int)(((Transition.Sub_Offset) - (Core.Camera.X) - 900) * Settings.Screen_Size);
		Rects.Submarine.y = (int)(((-Transition.Sub_Vertical * Settings.Screen_Size) - Rects.Submarine.h) -
			(Core.Camera.Y * Settings.Screen_Size));
		for (int Counter = 0; Counter < 2; Counter++) {
			SDL_FRect Subrectangle = {
				Rects.Submarine.x + ((Rects.Submarine.w * 0.5f) * Counter),
				Rects.Submarine.y,
				Rects.Submarine.w * 0.5f,
				Rects.Submarine.h
			};
			Render_Texture(Textures.Submarine.Data[Counter], &Subrectangle);
		}
	}
}

void Render_Transitions() {
	if (Transition.Frames < Transition.Max_Frames) {
		Transition.Frames++;
	} else {
		Trigger_Ambiance();
		Transition.Phase = 2;
		Interface.UI_Tab = Transition.Queried_Tab;
		Transition.Frames = 0;
		Transition.Max_Frames = (int)(Interface.Frame_Rate * 0.5);
	}
	Render_Texture(Textures.Door.Data[0], &Rects.Door[0]);
	Render_Texture(Textures.Door.Data[1], &Rects.Door[1]);
	if (Transition.Frames > (Transition.Max_Frames * 0.5) || Transition.Phase == 2) {
		SDL_FRect Indicator_Rectangle = {
			Settings.Screen_Size * 342.5f,
			(float)(((1471 / 6.0f) - 20) * Settings.Screen_Size),
			(float)(LDE_TILESIZE * Settings.Screen_Size),
			(float)(LDE_TILESIZE * Settings.Screen_Size)
		};
		Render_Texture(Textures.R_Flash, &Indicator_Rectangle);
	}
}