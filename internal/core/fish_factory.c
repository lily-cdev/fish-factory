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

SDL_ScaleMode Scaling_Quality;

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	Startup_Miniaudio();
	Scaling_Quality = SDL_SCALEMODE_LINEAR;
	SDL_CreateWindowAndRenderer("Fish Factory", 640, 360, SDL_WINDOW_HIGH_PIXEL_DENSITY, &Core.Window, &Core.Renderer);
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
		if (Interface.UI_Tab == LDE_INVALID) {
			if (Transition.Transition_Frames < Transition.Maximum_Transition_Frames) {
				Transition.Transition_Frames++;
			} else {
				Trigger_Ambiance();
				Transition.Transition_Phase = 2;
				Interface.UI_Tab = Transition.Queried_Tab;
				Transition.Transition_Frames = 0;
				Transition.Maximum_Transition_Frames = (int)(Interface.Frame_Rate * 0.5);
			}
			Render_Texture(Textures.Door.Data[0], &Rects.Door[0]);
			Render_Texture(Textures.Door.Data[1], &Rects.Door[1]);
			if (Transition.Transition_Frames > (Transition.Maximum_Transition_Frames * 0.5) || Transition.Transition_Phase ==
				2) {
				SDL_FRect Indicator_Rectangle = {
					(float)(((2175 / 6.0f) - 20) * Settings.Screen_Size),
					(float)(((1471 / 6.0f) - 20) * Settings.Screen_Size),
					(float)(LDE_TILESIZE * Settings.Screen_Size),
					(float)(LDE_TILESIZE * Settings.Screen_Size)
				};
				Render_Texture(Textures.R_Flash, &Indicator_Rectangle);
			}
		} else if (Interface.UI_Tab == 0) {
			SDL_SetRenderTarget(Core.Renderer, Core.Game_Texture);
			Render_Ocean();
			Render_Pyramid();
			if (Interface.Building && Data.Funds - Metadata.Machine_Prices[Interface.Placing_Item - 1] > 0) {
				Build_Grid();
				Update_Grid();
			}
			Render_Grid();
			if (Cache.Wire_State != LDE_INVALID) {
				Render_Wires();
				if (Cache.Wire_State == Deep_Recache) {
					Clear_Unconnected_Wires();
				}
				Cache.Wire_State = LDE_INVALID;
			}
			Render_Wire_Nodes();
			for (int Counter = 0; Counter < 4; Counter++) {
				int Offset_X = 0;
				int Offset_Y = 0;
				switch (Counter) {
				case 1:
					Offset_X = 1;
					break;
				case 2:
					Offset_X = 1;
					Offset_Y = 1;
					break;
				case 3:
					Offset_Y = 1;
					break;
				default:
					break;
				}
				Offset_X *= LDE_GRIDSIZE * 20;
				Offset_Y *= LDE_GRIDSIZE * 20;
				Cache.Wire_Box.x = (int)(Offset_X - Core.Camera.X) * Settings.Screen_Size;
				Cache.Wire_Box.y = (int)(Offset_Y - Core.Camera.Y) * Settings.Screen_Size;
				Render_Texture(Cache.Wire_Cache.Data[Counter], &Cache.Wire_Box);
			}
			if (Interface.Tool == 4) {
				Render_Pipes();
			}
			if (Interface.Tool == 0 && Interface.UI_Selection == 0) {
				int X;
				int Y;
				ID_To_Size(Interface.Placing_Item - 1, Interface.Placing_Rotation, &X, &Y);
				Render_Blueprint(X, Y);
			}
			Render_Submarine();
			SDL_SetRenderTarget(Core.Renderer, NULL);
			SDL_FRect Temporary_Rectangle = { 0, 0, Settings.Screen_Size * 640.0f, Settings.Screen_Size * 360.0f };
			Render_Texture(Core.Game_Texture, &Temporary_Rectangle);
			if (Interface.Tool > 0) {
				SDL_FRect Hitbox = {
					0.0f,
					0.0f,
					(float)(LDE_TILESIZE * Settings.Screen_Size),
					(float)(LDE_TILESIZE * Settings.Screen_Size)
				};
				Hitbox.x = (int)(((int)((Core.Mouse.X + (Core.Camera.X * Settings.Screen_Size)) / (LDE_TILESIZE * Settings
					.Screen_Size)) * (LDE_TILESIZE * Settings.Screen_Size)) - (Core.Camera.X * Settings.Screen_Size));
				Hitbox.y = (int)(((int)((Core.Mouse.Y + (Core.Camera.Y * Settings.Screen_Size)) / (LDE_TILESIZE * Settings
					.Screen_Size)) * (LDE_TILESIZE * Settings.Screen_Size)) - (Core.Camera.Y * Settings.Screen_Size));
				Render_Texture(Textures.Crosshair, &Hitbox);
				Hitbox.x = Core.Mouse.X - (LDE_TILESIZE * Settings.Screen_Size * 0.5f);
				Hitbox.y = Core.Mouse.Y - (LDE_TILESIZE * Settings.Screen_Size * 0.5f);
				Render_Texture(Textures.Cursor, &Hitbox);
				bool Targeting = false;
				switch (Interface.Tool) {
				case 1:
					if (Get_Simple_Grid_Tile(Data.Visual_Grid, 0) != 0) {
						Targeting = true;
					}
					break;
				default:
					break;
				}
				if (Targeting) {
					Render_Texture(Textures.Cursor_Core, &Hitbox);
				}
			}
		} else if (Interface.UI_Tab == 1) {
			Render_Texture(Textures.Emblem, &Rects.Emblem);
			Render_Texture(Textures.Logo1, &Rects.Logo1);
			Render_Texture(Textures.Logo2, &Rects.Logo2);
			Render_Button(&Textures.New_Game, &Rects.New_Game, 1, Colors.Cherry_Blossom);
			Render_Button(&Textures.Settings, &Rects.Settings, 2, Colors.Cherry_Blossom);
			Render_Button(&Textures.Update_Logs, &Rects.Update_Logs, 3, Colors.Cherry_Blossom);
			Render_Button(&Textures.Credits, &Rects.Credits, 4, Colors.Cherry_Blossom);
			Render_Button(&Textures.Quit_Game, &Rects.Quit_Game, 5, Colors.Cherry_Blossom);
			Render_Opening();
			Render_Closing(false);
		} else if (Interface.UI_Tab == 2) {
			Render_Saveloader();
			Render_Button(&Textures.Return, &Rects.Return, 1, Colors.Cherry_Blossom);
			Render_Opening();
			Render_Closing(false);
		} else if (Interface.UI_Tab == 3) {
			for (int Counter = 0; Counter < Textures.Settings_Label.Length; Counter++) {
				Render_Texture(Textures.Settings_Label.Data[Counter], &Rects.Settings_Label.Data[Counter]);
			}
			Render_Button(&Textures.Return, &Rects.Return, 1, Colors.Cherry_Blossom);
			Render_Slider(Interface.Slider_Texts[0], 1, 5, 4, &Interface.Slider_Positions[0], 50, 70, 220,
				Colors.Abyss_Black, Colors.Cherry_Blossom, true);
			Render_Slider(Interface.Slider_Texts[4], 2, 4, 20, &Interface.Slider_Positions[4], 50, 140, 220,
				Colors.Abyss_Black, Colors.Cherry_Blossom, true);
			Render_Slider(Interface.Slider_Texts[5], 3, 100, 21, &Interface.Slider_Positions[5], 50, 210, 220,
				Colors.Abyss_Black, Colors.Cherry_Blossom, true);
			Render_Slider(Interface.Slider_Texts[6], 4, 2, 22, &Interface.Slider_Positions[6], 50, 280, 220,
				Colors.Abyss_Black, Colors.Cherry_Blossom, true);
			if (Settings.AA_Temporary) {
				Render_Button(&Textures.Anti_Aliasing.Data[0], &Rects.Anti_Aliasing.Data[0], 5, Colors.Cherry_Blossom);
			} else {
				Render_Button(&Textures.Anti_Aliasing.Data[1], &Rects.Anti_Aliasing.Data[1], 5, Colors.Cherry_Blossom);
			}
			if (Settings.VS_Temporary) {
				Render_Button(&Textures.V_Sync.Data[1], &Rects.V_Sync.Data[1], 24, Colors.Cherry_Blossom);
			} else {
				Render_Button(&Textures.V_Sync.Data[0], &Rects.V_Sync.Data[0], 24, Colors.Cherry_Blossom);
			}
			if (Temporary.Settings_Changed) {
				Render_Button(&Textures.Save_Settings, &Rects.Save_Settings, 23, Colors.Cherry_Blossom);
			}
			Process_Supply(&Supplies.Monitor_Size, Metadata.Monitor_Size, Fonts.Subtext_Font, Colors.Abyss_Black, 50, 40);
			for (int Counter1 = 0; Counter1 < LDE_KEYBINDS; Counter1++) {
				char Text[64];
				snprintf(Text, sizeof(Text), "%s...", Keybinds.Keybind_Texts[Counter1]);
				SDL_Surface* Prefix_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Text, 0, Colors.Abyss_Black);
				SDL_Texture* Prefix_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Prefix_Surface);
				SDL_FRect Prefix_Rectangle = {
					Settings.Screen_Size * 370.0f,
					(float)((Counter1 * 16) + 40) * Settings.Screen_Size,
					(float)(Prefix_Surface->w),
					(float)(Prefix_Surface->h)
				};
				Render_Texture(Prefix_Texture, &Prefix_Rectangle);
				if (Interface.Registering_Keybind == Counter1) {
					SDL_Surface* Registering_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, "...", 0,
						Colors.Abyss_Black);
					SDL_Texture* Registering_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Registering_Surface);
					SDL_FRect Registering_Rectangle = {
						Prefix_Rectangle.x + Prefix_Rectangle.w + 20,
						Prefix_Rectangle.y,
						(float)(Registering_Surface->w),
						(float)(Registering_Surface->h)
					};
					Render_Texture(Registering_Texture, &Registering_Rectangle);
					SDL_DestroySurface(Registering_Surface);
					free_texture(Registering_Texture);
				} else {
					char Subcore[32];
					strcpy(Subcore, SDL_GetKeyName(Keybinds.Keybind_Settings[Counter1]));
					for (int Counter2 = 0; Counter2 < strlen(Subcore); Counter2++) {
						Subcore[Counter2] = (char)(tolower(Subcore[Counter2]));
					}
					SDL_Surface* Deadbutton_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Subcore, 0,
						Colors.Abyss_Black);
					SDL_Texture* Deadbutton_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Deadbutton_Surface);
					SDL_FRect Deadbutton_Rectangle = {
						Prefix_Rectangle.x + Prefix_Rectangle.w + 20,
						Prefix_Rectangle.y,
						(float)(Deadbutton_Surface->w),
						(float)(Deadbutton_Surface->h)
					};
					if (Detect_Mouse_Collision(Deadbutton_Rectangle)) {
						Interface.UI_Selection = Counter1 + 6;
						char Alivebutton_Text[64];
						snprintf(Alivebutton_Text, sizeof(Alivebutton_Text), "> %s <", Subcore);
						SDL_Surface* Alivebutton_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Alivebutton_Text, 0,
							Colors.Cherry_Blossom);
						SDL_Texture* Alivebutton_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Alivebutton_Surface);
						SDL_Surface* Temporary_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, "> ", 0,
							Colors.Cherry_Blossom);
						int Offset = Temporary_Surface->w;
						SDL_DestroySurface(Temporary_Surface);
						SDL_FRect Alivebutton_Rectangle = {
							Deadbutton_Rectangle.x - Offset,
							Deadbutton_Rectangle.y,
							(float)(Alivebutton_Surface->w),
							(float)(Alivebutton_Surface->h)
						};
						Render_Texture(Alivebutton_Texture, &Alivebutton_Rectangle);
						SDL_FRect Underline_Rectangle = {
							Deadbutton_Rectangle.x,
							Deadbutton_Rectangle.y +
							Deadbutton_Rectangle.h + 2,
							Deadbutton_Rectangle.w,
							Deadbutton_Rectangle.h * 0.1f
						};
						SDL_SetRenderDrawColor(Core.Renderer, Colors.Cherry_Blossom.r, Colors.Cherry_Blossom.g,
							Colors.Cherry_Blossom.b, SDL_ALPHA_OPAQUE);
						SDL_RenderFillRect(Core.Renderer, &Underline_Rectangle);
						Clear_Renderer();
						SDL_DestroySurface(Alivebutton_Surface);
						free_texture(Alivebutton_Texture);
					} else {
						Render_Texture(Deadbutton_Texture, &Deadbutton_Rectangle);
					}
					SDL_DestroySurface(Deadbutton_Surface);
					free_texture(Deadbutton_Texture);
				}
				SDL_DestroySurface(Prefix_Surface);
				free_texture(Prefix_Texture);
			}
			Verify_Settings();
			Render_Opening();
			Render_Closing(false);
		} else if (Interface.UI_Tab == 4) {
			for (int Counter = 0; Counter < Cache.Log_Cache.Data[Changelog].Length; Counter++) {
				SDL_FRect Log_Rectangle = Cache.Log_Rectangles.Data[Changelog].Data[Counter];
				Log_Rectangle.y -= Interface.Log_Offset;
				Render_Texture(Cache.Log_Cache.Data[Changelog].Data[Counter], &Log_Rectangle);
			}
			Render_Texture(Textures.Log_Background, &Rects.Log_Background);
			char Buffer[64];
			char Subbuffer[64];
			Truncate(Temporary.Scroll_Percent, 0, Subbuffer, sizeof(Subbuffer));
			snprintf(Buffer, sizeof(Buffer), "Changelog - %s%%", Subbuffer);
			Process_Supply(&Supplies.Changelog_Scroll, Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, LDE_INVALID, 10);
			Render_Button(&Textures.Return, &Rects.Return, 1, Colors.Cherry_Blossom);
			if (Temporary.Log_Inversions[Changelog]) {
				Render_Button(&Textures.Sort.Data[0], &Rects.Sort.Data[0], 2, Colors.Cherry_Blossom);
			} else {
				Render_Button(&Textures.Sort.Data[1], &Rects.Sort.Data[1], 2, Colors.Cherry_Blossom);
			}
			if (Temporary.Scroll_Percent < 50) {
				Render_Button(&Textures.TBW_Texture.Data[0], &Rects.TBW_Rectangle.Data[0], 3, Colors.Cherry_Blossom);
			} else {
				Render_Button(&Textures.TBW_Texture.Data[1], &Rects.TBW_Rectangle.Data[1], 4, Colors.Cherry_Blossom);
			}
			Render_Opening();
			Render_Closing(true);
		} else if (Interface.UI_Tab == 5) {
			char Prefix[16] = "Credits";
			switch (Interface.Slider_Positions[2]) {
			case 0:
				for (int Counter = 0; Counter < Cache.Log_Cache.Data[Credits].Length; Counter++) {
					SDL_FRect Log_Rectangle = Cache.Log_Rectangles.Data[Credits].Data[Counter];
					Log_Rectangle.y -= Interface.Log_Offset;
					Render_Texture(Cache.Log_Cache.Data[Credits].Data[Counter], &Log_Rectangle);
				}
				break;
			case 1:
				for (int Counter = 0; Counter < Cache.Log_Cache.Data[Legal].Length; Counter++) {
					SDL_FRect Log_Rectangle = Cache.Log_Rectangles.Data[Legal].Data[Counter];
					Log_Rectangle.y -= Interface.Log_Offset;
					Render_Texture(Cache.Log_Cache.Data[Legal].Data[Counter], &Log_Rectangle);
				}
				strcpy(Prefix, "Legal");
				break;
			default:
				break;
			}
			Render_Texture(Textures.Log_Background, &Rects.Log_Background);
			char Buffer[64];
			char Subbuffer[64];
			Truncate(Temporary.Scroll_Percent, 0, Subbuffer, sizeof(Subbuffer));
			snprintf(Buffer, sizeof(Buffer), "%s - %s%%", Prefix, Subbuffer);
			Process_Supply(&Supplies.Scroll_Percent, Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, LDE_INVALID, 10);
			Render_Button(&Textures.Return, &Rects.Return, 1, Colors.Cherry_Blossom);
			Render_Slider(Interface.Slider_Texts[2], 1, 1, 2, &Interface.Slider_Positions[2], 200, 340, 240,
				Colors.Abyss_Black, Colors.Cherry_Blossom, false);
			Render_Opening();
			Render_Closing(true);
		}
		Process_Inputs();
		switch (Interface.UI_Tab) {
		case 0:
			if (Interface.Subtime_Frames < Interface.Maximum_Subtime_Frames) {
				Interface.Subtime_Frames++;
			} else {
				Interface.Subtime_Frames = 0;
				float Sum = 0;
				for (int Counter = 0; Counter < Cache.FPS_Length; Counter++) {
					Sum += Cache.FPS_Cache[Counter];
				}
				Temporary.Temporary_FPS = (int)(Sum / Cache.FPS_Length);
				Cache.FPS_Length = 0;
			}
			if (Data.CMD_Placed) {
				if (Data.Time < 1440) {
					if (Interface.Time_Frames < Interface.Maximum_Time_Frames) {
						Interface.Time_Frames++;
					} else {
						Interface.Time_Frames = 0;
						Data.Time = Data.Time + 1;
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
			if (!Interface.Animation_Locked && Interface.Prompt_Identifier == P_None && Interface.Tool == LDE_INVALID) {
				Render_Tile_Prompts();
			}
			if (Interface.UD_Input != LDE_INVALID || Interface.LR_Input != LDE_INVALID) {
				int Increment = (Interface.Movespeed / Interface.Frame_Rate) * (((int)(Interface.Sprinting) * 4) + 1);
				if (Interface.UD_Input == 0) {
					Core.Camera.Y = Core.Camera.Y - Increment;
					Find_Effect();
					if (Core.Camera.Y < -LDE_BUFFERSIZE) {
						Core.Camera.Y = -LDE_BUFFERSIZE;
						Interface.UD_Input = LDE_INVALID;
					}
				} else if (Interface.UD_Input == 1) {
					Core.Camera.Y = Core.Camera.Y + Increment;
					Find_Effect();
					if (Core.Camera.Y > Interface.Map_Y) {
						Core.Camera.Y = Interface.Map_Y;
						Interface.UD_Input = LDE_INVALID;
					}
				}
				if (Interface.LR_Input == 0) {
					Core.Camera.X = Core.Camera.X - Increment;
					Find_Effect();
					if (Core.Camera.X < -LDE_BUFFERSIZE) {
						Core.Camera.X = -LDE_BUFFERSIZE;
						Interface.LR_Input = LDE_INVALID;
					}
				} else if (Interface.LR_Input == 1) {
					Core.Camera.X = Core.Camera.X + Increment;
					Find_Effect();
					if (Core.Camera.X > Interface.Map_X) {
						Core.Camera.X = Interface.Map_X;
						Interface.LR_Input = LDE_INVALID;
					}
				}
			}
			Drain_Query();
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
		uint64_t Total_Time = SDL_GetTicks() - Frame_Beginning;
		float Remaining_Delay = (1000 / Interface.Frame_Rate) - Total_Time;
		float True_Rate = 99999;
		if (Total_Time > 0) {
			True_Rate = 1000.0 / Total_Time;
		}
		if (True_Rate > Interface.Frame_Rate) {
			True_Rate = Interface.Frame_Rate;
		}
		Cache.FPS_Cache[Cache.FPS_Length] = True_Rate;
		Cache.FPS_Length++;
		SDL_Delay((uint32_t)(fmax(Remaining_Delay, 0.0f)));
	}
	Free_Text();
	Free_Preconfigs();
	free_c(Temporary.Docks.Data);
	Free_Supplies();
	Shutdown_Miniaudio();
	SDL_ShowCursor();
	Cleanup_Assets();
	SDL_DestroyRenderer(Core.Renderer);
	SDL_DestroyWindow(Core.Window);
	SDL_PumpEvents();
	TTF_Quit();
	SDL_Quit();
	return 0;
}