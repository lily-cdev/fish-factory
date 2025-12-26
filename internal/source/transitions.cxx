#include <Transition_Handler.h>

double Ease_Sine(double Time) {
	return -(cos(M_PI * Time) - 1.0f) / 2.0f;
}

void Start_Transition(int Tab) {
	Transition.Queried_Tab = Tab;
	Transition.Maximum_Transition_Frames = Interface.Frame_Rate / 2;
	Transition.Transition_Frames = 0;
	Transition.Transition_Phase = 0;
	Interface.Animation_Locked = true;
}

void Force_Opening() {
	Transition.Transition_Phase = 2;
	Transition.Transition_Frames = 0;
	Transition.Queried_Tab = Interface.UI_Tab;
	Transition.Maximum_Transition_Frames = static_cast<int>(Interface.Frame_Rate / 2);
	Trigger_Ambiance();
}

void Render_Closing(bool Clearing) {
	if (Transition.Transition_Phase == 0) {
		if (Transition.Transition_Frames < Transition.Maximum_Transition_Frames) {
			Transition.Transition_Frames++;
			double Percentage = Ease_Sine((double)Transition.Transition_Frames /
				Transition.Maximum_Transition_Frames);
			Rects.Door[0].x = static_cast<int>(((320 * Settings.Screen_Size) * Percentage) -
				(320 * Settings.Screen_Size));
			Rects.Door[1].x = static_cast<int>((640 * Settings.Screen_Size) -
				((320 * Settings.Screen_Size) * Percentage));
		} else {
			Transition.Transition_Phase = 1;
			Interface.UI_Tab = LDE_INVALID;
			Transition.Transition_Frames = 0;
			Transition.Maximum_Transition_Frames = static_cast<int>(Interface.Frame_Rate / 1.5);
			Rects.Door[0].x = 0;
			Rects.Door[1].x = 320 * Settings.Screen_Size;
			if (Clearing) {	
				Interface.Log_Offset = 0;
				Temporary.Scroll_Percent = 0;
				Interface.Slider_Positions[2] = 0;
			}
		}
		SDL_RenderTexture(Core.Renderer, Textures
			.Door.Data[0], NULL, &Rects.Door[0]);
		SDL_RenderTexture(Core.Renderer, Textures
			.Door.Data[1], NULL, &Rects.Door[1]);
	}
}

void Render_Opening() {
	if (Transition.Transition_Phase == 2) {
		if (Transition.Transition_Frames < Transition.Maximum_Transition_Frames) {
			Transition.Transition_Frames++;
			double Percentage = Ease_Sine((double)Transition.Transition_Frames /
				Transition.Maximum_Transition_Frames);
			Rects.Door[0].x = static_cast<int>(-((320 * Settings.Screen_Size) * Percentage));
			Rects.Door[1].x = static_cast<int>((320 * Settings.Screen_Size) +
				((320 * Settings.Screen_Size) * Percentage));
			SDL_RenderTexture(Core.Renderer, Textures
				.Door.Data[0], NULL, &Rects.Door[0]);
			SDL_RenderTexture(Core.Renderer, Textures
				.Door.Data[1], NULL, &Rects.Door[1]);
			SDL_FRect Indicator_Rectangle = { static_cast<float>(((2175 / 6.0f) + (320 * Percentage) - 20) *
				Settings.Screen_Size), static_cast<float>(((1471 / 6.0f) - 20) *	Settings.Screen_Size),
				40.0f * Settings.Screen_Size, 40.0f * Settings.Screen_Size };
			SDL_RenderTexture(Core.Renderer, Textures.R_Flash, NULL, &Indicator_Rectangle);
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
	if (Temporary.Submarine_Phase != LDE_INVALID) {
		switch (Temporary.Submarine_Phase) {
		case 0:
			Temporary.Submarine_Offset -= (double)(LDE_VESSELSPEED * 40) / Interface.Frame_Rate;
			if (Temporary.Submarine_Offset < (Temporary.Submarine_Position.X * 40) + 120) {
				Temporary.Submarine_Offset = (Temporary.Submarine_Position.X * 40) + 120;
				Temporary.Submarine_Phase = 1;
			}
			break;
		case 1:
			Temporary.Submarine_Vertical -= 5.0f / Interface.Frame_Rate;
			if (Temporary.Submarine_Vertical < 85) {
				Temporary.Submarine_Vertical = 85;
				Temporary.Submarine_Phase = 2;
			}
			break;
		case 3:
			Temporary.Submarine_Vertical += 5.0f / Interface.Frame_Rate;
			if (Temporary.Submarine_Vertical > 105) {
				Temporary.Submarine_Vertical = 105;
				Temporary.Submarine_Phase = 4;
			}
			break;
		case 4:
			Temporary.Submarine_Offset -= (double)(LDE_VESSELSPEED * 40) / Interface.Frame_Rate;
			if (Temporary.Submarine_Offset < -3000) {
				Temporary.Submarine_Offset = 3000;
				Temporary.Submarine_Phase = LDE_INVALID;
				Temporary.Submarine_Position = { LDE_INVALID, LDE_INVALID };
			}
			break;
		default:
			break;
		}
		Rects.Submarine.x = static_cast<int>(((Temporary
			.Submarine_Offset) - (Interface.Camera_X) - 900) * Settings.Screen_Size);
		Rects.Submarine.y = static_cast<int>(((-Temporary
			.Submarine_Vertical * Settings.Screen_Size) -
			Rects.Submarine.h) - (Interface.Camera_Y * Settings.Screen_Size));
		for (int Counter = 0; Counter < 2; Counter++) {
			SDL_FRect Subrectangle = { Rects.Submarine.x +
				((Rects.Submarine.w / 2) * Counter),
				Rects.Submarine.y, Rects
				.Submarine.w / 2, Rects.Submarine.h };
			SDL_RenderTexture(Core.Renderer, Textures
				.Submarine.Data[Counter], NULL, &Subrectangle);
		}
	}
}