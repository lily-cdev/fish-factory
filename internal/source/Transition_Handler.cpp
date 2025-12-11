#include <Core.h>

#include <Preloader.h>
#include <Transition_Handler.h>

double Ease_Sine(double Time) {
	return -(cos(M_PI * Time) - 1.0f) / 2.0f;
}

void Start_Transition(int Tab) {
	Transition_Access.Queried_Tab = Tab;
	Transition_Access.Maximum_Transition_Frames = UI_Access.Frame_Rate / 2;
	Transition_Access.Transition_Frames = 0;
	Transition_Access.Transition_Phase = 0;
	UI_Access.Animation_Locked = true;
}

void Force_Opening() {
	Transition_Access.Transition_Phase = 2;
	Transition_Access.Transition_Frames = 0;
	Transition_Access.Queried_Tab = UI_Access.UI_Tab;
	Transition_Access.Maximum_Transition_Frames = static_cast<int>(UI_Access.Frame_Rate / 2);
	Trigger_Ambiance();
}

void Render_Closing(bool Clearing) {
	if (Transition_Access.Transition_Phase == 0) {
		if (Transition_Access.Transition_Frames < Transition_Access.Maximum_Transition_Frames) {
			Transition_Access.Transition_Frames++;
			double Percentage = Ease_Sine((double)Transition_Access.Transition_Frames /
				Transition_Access.Maximum_Transition_Frames);
			Rectangles_Access.Door[0].x = static_cast<int>(((320 * Settings_Access.Screen_Size) * Percentage) -
				(320 * Settings_Access.Screen_Size));
			Rectangles_Access.Door[1].x = static_cast<int>((640 * Settings_Access.Screen_Size) -
				((320 * Settings_Access.Screen_Size) * Percentage));
		} else {
			Transition_Access.Transition_Phase = 1;
			UI_Access.UI_Tab = LDE_INVALID;
			Transition_Access.Transition_Frames = 0;
			Transition_Access.Maximum_Transition_Frames = static_cast<int>(UI_Access.Frame_Rate / 1.5);
			Rectangles_Access.Door[0].x = 0;
			Rectangles_Access.Door[1].x = 320 * Settings_Access.Screen_Size;
			if (Clearing) {	
				UI_Access.Log_Offset = 0;
				Temporary_Access.Scroll_Percent = 0;
				UI_Access.Slider_Positions[2] = 0;
			}
		}
		SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
			.Door.Data[0], NULL, &Rectangles_Access.Door[0]);
		SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
			.Door.Data[1], NULL, &Rectangles_Access.Door[1]);
	}
}

void Render_Opening() {
	if (Transition_Access.Transition_Phase == 2) {
		if (Transition_Access.Transition_Frames < Transition_Access.Maximum_Transition_Frames) {
			Transition_Access.Transition_Frames++;
			double Percentage = Ease_Sine((double)Transition_Access.Transition_Frames /
				Transition_Access.Maximum_Transition_Frames);
			Rectangles_Access.Door[0].x = static_cast<int>(-((320 * Settings_Access.Screen_Size) * Percentage));
			Rectangles_Access.Door[1].x = static_cast<int>((320 * Settings_Access.Screen_Size) +
				((320 * Settings_Access.Screen_Size) * Percentage));
			SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
				.Door.Data[0], NULL, &Rectangles_Access.Door[0]);
			SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
				.Door.Data[1], NULL, &Rectangles_Access.Door[1]);
			SDL_FRect Indicator_Rectangle = { static_cast<float>(((2175 / 6.0f) + (320 * Percentage) - 20) *
				Settings_Access.Screen_Size), static_cast<float>(((1471 / 6.0f) - 20) *	Settings_Access.Screen_Size),
				40.0f * Settings_Access.Screen_Size, 40.0f * Settings_Access.Screen_Size };
			SDL_RenderTexture(Core_Access.Application_Renderer,
				Textures_Access.RFlash, NULL, &Indicator_Rectangle);
		} else {
			Transition_Access.Transition_Phase = LDE_INVALID;
			UI_Access.Animation_Locked = false;
		}
	}
}

void Trigger_Ambiance() {
	Audio_Access.Terminate(&Audio_Access.Primary_Ambience);
	switch (Transition_Access.Queried_Tab) {
	case 0:
		Audio_Access.Play(&Audio_Access.Primary_Ambience, true);
		break;
	default:
		break;
	}
}

void Render_Submarine() {
	if (Temporary_Access.Submarine_Phase != LDE_INVALID) {
		switch (Temporary_Access.Submarine_Phase) {
		case 0:
			Temporary_Access.Submarine_Offset -= (double)(LDE_VESSELSPEED * 40) / UI_Access.Frame_Rate;
			if (Temporary_Access.Submarine_Offset < (Temporary_Access.Submarine_Position[0] * 40) + 120) {
				Temporary_Access.Submarine_Offset = (Temporary_Access.Submarine_Position[0] * 40) + 120;
				Temporary_Access.Submarine_Phase = 1;
			}
			break;
		case 1:
			Temporary_Access.Submarine_Vertical -= 5.0f / UI_Access.Frame_Rate;
			if (Temporary_Access.Submarine_Vertical < 85) {
				Temporary_Access.Submarine_Vertical = 85;
				Temporary_Access.Submarine_Phase = 2;
			}
			break;
		case 3:
			Temporary_Access.Submarine_Vertical += 5.0f / UI_Access.Frame_Rate;
			if (Temporary_Access.Submarine_Vertical > 105) {
				Temporary_Access.Submarine_Vertical = 105;
				Temporary_Access.Submarine_Phase = 4;
			}
			break;
		case 4:
			Temporary_Access.Submarine_Offset -= (double)(LDE_VESSELSPEED * 40) / UI_Access.Frame_Rate;
			if (Temporary_Access.Submarine_Offset < -3000) {
				Temporary_Access.Submarine_Offset = 3000;
				Temporary_Access.Submarine_Phase = LDE_INVALID;
				Temporary_Access.Submarine_Position = { LDE_INVALID, LDE_INVALID };
			}
			break;
		default:
			break;
		}
		Rectangles_Access.Submarine.x = static_cast<int>(((Temporary_Access
			.Submarine_Offset) - (UI_Access.Camera_X) - 900) * Settings_Access.Screen_Size);
		Rectangles_Access.Submarine.y = static_cast<int>(((-Temporary_Access
			.Submarine_Vertical * Settings_Access.Screen_Size) -
			Rectangles_Access.Submarine.h) - (UI_Access.Camera_Y * Settings_Access.Screen_Size));
		for (int Counter = 0; Counter < 2; Counter++) {
			SDL_FRect Subrectangle = { Rectangles_Access.Submarine.x +
				((Rectangles_Access.Submarine.w / 2) * Counter),
				Rectangles_Access.Submarine.y, Rectangles_Access
				.Submarine.w / 2, Rectangles_Access.Submarine.h };
			SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
				.Submarine.Data[Counter], NULL, &Subrectangle);
		}
	}
}