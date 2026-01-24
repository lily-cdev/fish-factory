#include <transitions.h>

TRANSITION Transition = {
	.Queried_Tab = 0,
	.Transition_Frames = 0,
	.Maximum_Transition_Frames = 0,
	.Transition_Phase = LDE_INVALID,
	.Submarine_Position = { LDE_INVALID, LDE_INVALID },
	.Submarine_Side = 1,
	.Submarine_Phase = LDE_INVALID,
	.Submarine_Offset = 0,
	.Submarine_Vertical = 0
};

float Ease_Sine(float Time) {
	return -(cos(M_PI * Time) - 1.0f) * 0.5f;
}

void Start_Transition(int Tab) {
	Transition.Queried_Tab = Tab;
	Transition.Maximum_Transition_Frames = Interface.Frame_Rate * 0.5f;
	Transition.Transition_Frames = 0;
	Transition.Transition_Phase = 0;
	Interface.Animation_Locked = true;
}

void Force_Opening() {
	Transition.Transition_Phase = 2;
	Transition.Transition_Frames = 0;
	Transition.Queried_Tab = Interface.UI_Tab;
	Transition.Maximum_Transition_Frames = (int)(Interface.Frame_Rate * 0.5f);
	Trigger_Ambiance();
}

void Render_Closing(bool Clearing) {
	if (Transition.Transition_Phase == 0) {
		if (Transition.Transition_Frames < Transition.Maximum_Transition_Frames) {
			Transition.Transition_Frames++;
			float Percentage = Ease_Sine((float)Transition.Transition_Frames / Transition.Maximum_Transition_Frames);
			Rects.Door[0].x = (int)(((Settings.Screen_Size * 320) * Percentage) - (Settings.Screen_Size * 320));
			Rects.Door[1].x = (int)((Settings.Screen_Size * 640) - ((Settings.Screen_Size * 320) * Percentage));
		} else {
			Transition.Transition_Phase = 1;
			Interface.UI_Tab = LDE_INVALID;
			Transition.Transition_Frames = 0;
			Transition.Maximum_Transition_Frames = (int)(Interface.Frame_Rate / 1.5);
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
	if (Transition.Transition_Phase == 2) {
		if (Transition.Transition_Frames < Transition.Maximum_Transition_Frames) {
			Transition.Transition_Frames++;
			float Percentage = Ease_Sine((float)Transition.Transition_Frames / Transition.Maximum_Transition_Frames);
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
			Transition.Transition_Phase = LDE_INVALID;
			Interface.Animation_Locked = false;
		}
	}
}

void Trigger_Ambiance() {
	Terminate_Sound(&Audio.Primary_Ambience);
	switch (Transition.Queried_Tab) {
	case 0:
		Play_Sound(&Audio.Primary_Ambience, true);
		break;
	default:
		break;
	}
}

void Render_Submarine() {
	if (Transition.Submarine_Phase != LDE_INVALID) {
		switch (Transition.Submarine_Phase) {
		case 0:
			Transition.Submarine_Offset -= (float)(LDE_VESSELSPEED * LDE_TILESIZE) / Interface.Frame_Rate;
			if (Transition.Submarine_Offset < (Transition.Submarine_Position.X * LDE_TILESIZE) + 120) {
				Transition.Submarine_Offset = (Transition.Submarine_Position.X * LDE_TILESIZE) + 120;
				Transition.Submarine_Phase = 1;
			}
			break;
		case 1:
			Transition.Submarine_Vertical -= 5.0f / Interface.Frame_Rate;
			if (Transition.Submarine_Vertical < 85) {
				Transition.Submarine_Vertical = 85;
				Transition.Submarine_Phase = 2;
			}
			break;
		case 3:
			Transition.Submarine_Vertical += 5.0f / Interface.Frame_Rate;
			if (Transition.Submarine_Vertical > 105) {
				Transition.Submarine_Vertical = 105;
				Transition.Submarine_Phase = 4;
			}
			break;
		case 4:
			Transition.Submarine_Offset -= (float)(LDE_VESSELSPEED * LDE_TILESIZE) / Interface.Frame_Rate;
			if (Transition.Submarine_Offset < -3000) {
				Transition.Submarine_Offset = 3000;
				Transition.Submarine_Phase = LDE_INVALID;
				Transition.Submarine_Position.X = LDE_INVALID;
				Transition.Submarine_Position.Y = LDE_INVALID;
			}
			break;
		default:
			break;
		}
		Rects.Submarine.x = (int)(((Transition.Submarine_Offset) - (Core.Camera.X) - 900) * Settings.Screen_Size);
		Rects.Submarine.y = (int)(((-Transition.Submarine_Vertical * Settings.Screen_Size) - Rects.Submarine.h) -
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