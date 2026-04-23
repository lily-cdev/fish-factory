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
			Rects.Door[0].x = (int)((Core.Screenhalfsize.X * Percentage) - Core.Screenhalfsize.X);
			Rects.Door[1].x = (int)(Core.Screensize.X - (Core.Screenhalfsize.X * Percentage));
		} else {
			Transition.Phase = 1;
			Interface.UI_Tab = LDE_INVALID;
			Transition.Frames = 0;
			Transition.Max_Frames = (int)(Interface.Frame_Rate / 1.5f);
			Rects.Door[0].x = 0;
			Rects.Door[1].x = Core.Screenhalfsize.X;
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
			Rects.Door[0].x = (int)(-(Core.Screenhalfsize.X * Percentage));
			Rects.Door[1].x = (int)((Core.Screenhalfsize.X * Percentage) + Core.Screenhalfsize.X);
			Render_Texture(Textures.Door.Data[0], &Rects.Door[0]);
			Render_Texture(Textures.Door.Data[1], &Rects.Door[1]);
			SDL_FRect Indicator_Rectangle = {
				scale_f((Percentage * 320.0f) + 342.5f),
				scale_f((1471.0f / 6.0f) - 20.0f),
				scale_f(LDE_TILESIZE),
				scale_f(LDE_TILESIZE)
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
		Rects.Submarine.x = scale_f(Transition.Sub_Offset - Core.Camera.X - 900.0f);
		Rects.Submarine.y = (scale_f(-Transition.Sub_Vertical) - Rects.Submarine.h) - scale_f(Core.Camera.Y);
		for (int C1 = 0; C1 < 2; C1++) {
			SDL_FRect Subrectangle = {
				Rects.Submarine.x + ((Rects.Submarine.w * 0.5f) * C1),
				Rects.Submarine.y,
				Rects.Submarine.w * 0.5f,
				Rects.Submarine.h
			};
			Render_Texture(Textures.Submarine.Data[C1], &Subrectangle);
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
		Transition.Max_Frames = (int)(Interface.Frame_Rate * 0.5f);
	}
	Render_Texture(Textures.Door.Data[0], &Rects.Door[0]);
	Render_Texture(Textures.Door.Data[1], &Rects.Door[1]);
	if (Transition.Frames > (Transition.Max_Frames * 0.5) || Transition.Phase == 2) {
		SDL_FRect Indicator_Rectangle = {
			scale_f(342.5f),
			scale_f((1471.0f / 6.0f) - 20.0f),
			scale_f(LDE_TILESIZE),
			scale_f(LDE_TILESIZE)
		};
		Render_Texture(Textures.R_Flash, &Indicator_Rectangle);
	}
}