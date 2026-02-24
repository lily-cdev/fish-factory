#include <core.h>
#include <prepping.h>
#include <transitions.h>
#include <rendering.h>
#include <data.h>
#include <grid.h>
#include <connectables.h>
#include <tutorials.h>
#include <items.h>
#include <interface.h>
#include <ui.h>

SDL_ScaleMode Scaling_Quality = SDL_SCALEMODE_LINEAR;
jmp_buf Exception = { };
int Exception_Value = 0;
char Exception_Text[128] = { };
const bool Closing_Parameters[5] = { false, false, false, true, true };
void (*Menu_Functions[7])() = {
	Render_Transitions,
	Render_Application,
	Render_Main,
	Render_Loader,
	Render_Settings,
	Render_Changelog,
	Render_Credits
};

int main(int argc, char* args[]) {
	Reseed_State();
	if (setjmp(Exception) != 0) {
		char Carrier[128];
		snprintf(Carrier, sizeof(Carrier), "fatal error %d: %s", Exception_Value, Exception_Text);
		//handle uwu
		puts(Carrier);
		exit(Exception_Value);
	}
	if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
		jump(I_No_SDL3, "could not load SDL3");
	}
	if (!TTF_Init()) {
		jump(I_No_TTF3, "could not load SDL3_ttf");
	}
	Startup_Miniaudio();
	Scaling_Quality = SDL_SCALEMODE_LINEAR;
	SDL_CreateWindowAndRenderer("Fish Factory", 640, 360, SDL_WINDOW_HIGH_PIXEL_DENSITY, &Core.Window, &Core.Renderer);
	if (Core.Window == NULL) {
		jump(I_No_Window, "window creation failed");
	}
	if (Core.Renderer == NULL) {
		jump(I_No_Renderer, "renderer creation failed");
	}
	Temporary.Docks.Length = 0;
	Temporary.Docks.Full_Size = 0;
	Load_Text();
	Generate_Preconfigs();
	Prep_Items();
	Load_Settings();
	Clear_Settings();
	Reload_All();
	Force_Opening();
	while (Core.Is_Running) {
		uint64_t Frame_Beginning = SDL_GetTicks();
		SDL_SetRenderDrawColor(Core.Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(Core.Renderer);
		Clear_Renderer();
		SDL_GetMouseState(&Core.Mouse.X, &Core.Mouse.Y);
		if (Interface.UI_Tab >= LDE_INVALID && Interface.UI_Tab <= 5) {
			Menu_Functions[Interface.UI_Tab + 1]();
		}
		if (Interface.UI_Tab >= 1 && Interface.UI_Tab <= 5) {
			Render_Opening();
			Render_Closing(Closing_Parameters[Interface.UI_Tab - 1]);			
		}
		Process_Inputs();
		switch (Interface.UI_Tab) {
		case 0:
			if (Data.CMD_Placed) {
				if (Data.Time < 1440) {
					if (Interface.Time_Frames < Interface.Max_Time_Frames) {
						Interface.Time_Frames++;
					} else {
						Interface.Time_Frames = 0;
						Data.Time++;
						Update_Machines();
						Update_Power();
						Update_Pipes();
						Purge_Items();
						Process_Tutorial(LDE_INVALID);
					}
				} else if (Interface.Prompt_Identifier != P_Daily_Report) {
					Interface.Prompt_Identifier = P_Daily_Report;
					Interface.Tool = LDE_INVALID;
				}
			} else {
				Render_Texture(Textures.CMD_Warning1, &Rects.CMD_Warning1);
			}
			if (!Interface.Locked && Interface.Prompt_Identifier == P_None && Interface.Tool == LDE_INVALID) {
				Render_Tile_Prompts();
			}
			Process_Movement();
			Drain_Query();
			Render_Hotbar();
			Render_Toolbar();
			{
				char Buffer[256];
				snprintf(Buffer, sizeof(Buffer), "%i/%i FPS", Temporary.Temporary_FPS, Interface.Frame_Rate);
				Process_Supply(&Supplies.FPS, Buffer, Fonts.Halftext_Font, Colors.Abyss_Black, 10, 10);
			}
			Render_Effects();
			Render_Game_UI();
			Render_Prompts();
			Render_Tutorial();
			Render_Opening();
			Render_Closing(false);
			break;
		default:
			break;
		}
		SDL_RenderPresent(Core.Renderer);
		if (Cache.FPS_Tick >= Interface.Frame_Rate - 1) {
			Cache.FPS_Tick = 0;
			float Sum = 0;
			for (int C1 = 0; C1 < Interface.Frame_Rate; C1++) {
				Sum += Cache.FPS_Cache[C1];
			}
			Temporary.Temporary_FPS = (int)(Sum / Interface.Frame_Rate);
		} else {
			Cache.FPS_Tick++;
		}
		uint64_t Total_Time = SDL_GetTicks() - Frame_Beginning;
		float True_Rate = (Total_Time > 0) ? (1000.0f / Total_Time) : 99999;
		Cache.FPS_Cache[Cache.FPS_Tick] = min(True_Rate, Interface.Frame_Rate);
		SDL_Delay((uint32_t)(fmax((1000.0f / Interface.Frame_Rate) - Total_Time, 0.0f)));
	}
	Free_Items();
	Free_Preconfigs();
	free_c(Temporary.Docks.Data);
	Free_Supplies();
	SDL_ShowCursor();
	Cleanup_Assets();
	Free_Sounds();
	Free_Text();
	SDL_DestroyRenderer(Core.Renderer);
	SDL_DestroyWindow(Core.Window);
	Shutdown_Miniaudio();
	SDL_PumpEvents();
	TTF_Quit();
	SDL_Quit();
	return 0;
}