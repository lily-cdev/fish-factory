#include <clib.hpp>
extern "C" {
	#include <core.h>
	#include <prepping.h>
	#include <transitions.h>
	#include <rendering.h>
	#include <data.h>
	#include <grid.h>
}
#include <Legacy_Preloader.hpp>
#include <Legacy_Items.hpp>
#include <Legacy_Connectables.hpp>
#include <Legacy_Grid.hpp>
#include <Legacy_Interface.hpp>
#include <Legacy_Tutorials.hpp>
#include <Legacy_UI.hpp>

OLD_METADATA Metadata_L;
OLD_KEYBINDS Keybinds_L;
OLD_TEMPORARY Temporary_L;
OLD_CACHE Cache_L;
OLD_INTERFACE Interface_L;
PRESET_ITEMS Preset_Items;
PRESET_CATEGORIES Preset_Categories;
PRESET_FISH Preset_Fish;
PRESET_IO_RECIPES Preset_IO_Recipes;
PRESET_I_RECIPES Preset_I_Recipes;
PRESET_O_RECIPES Preset_O_Recipes;

SDL_ScaleMode Scaling_Quality;

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	Startup_Miniaudio();
	Scaling_Quality = SDL_SCALEMODE_LINEAR;
	SDL_CreateWindowAndRenderer("Fish Factory", 640, 360, SDL_WINDOW_HIGH_PIXEL_DENSITY,
		&Core.Window, &Core.Renderer);
	Temporary.Docks.Length = 0;
	Temporary.Docks.Full_Size = 0;
	Load_Text();
	Generate_Preconfigurations();
	Update_Metadata();
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
				Transition.Maximum_Transition_Frames = static_cast<int>(Interface.Frame_Rate * 0.5);
			}
			SDL_RenderTexture(Core.Renderer, Textures
				.Door.Data[0], NULL, &Rects.Door[0]);
			SDL_RenderTexture(Core.Renderer, Textures
				.Door.Data[1], NULL, &Rects.Door[1]);
			if (Transition.Transition_Frames > (Transition.Maximum_Transition_Frames / 2) ||
				Transition.Transition_Phase == 2) {
				SDL_FRect Indicator_Rectangle = {
					static_cast<float>(((2175 / 6.0f) - 20) * Settings.Screen_Size),
					static_cast<float>(((1471 / 6.0f) - 20) * Settings.Screen_Size),
					static_cast<float>(LDE_TILESIZE * Settings.Screen_Size),
					static_cast<float>(LDE_TILESIZE * Settings.Screen_Size)
				};
				SDL_RenderTexture(Core.Renderer,
					Textures.R_Flash, NULL, &Indicator_Rectangle);
			}
		} else if (Interface.UI_Tab == 0) {
			SDL_SetRenderTarget(Core.Renderer, Core.Game_Texture);
			Render_Ocean();
			Render_Pyramid();
			if (Interface.Building && Data.Funds - Metadata.Machine_Prices[
				Interface.Placing_Item - 1] > 0) {
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
				Offset_X *= 20 * LDE_GRIDSIZE;
				Offset_Y *= 20 * LDE_GRIDSIZE;
				Cache.Wire_Box.x = static_cast<int>(Offset_X -
					Core.Camera.X) * Settings.Screen_Size;
				Cache.Wire_Box.y = static_cast<int>(Offset_Y -
					Core.Camera.Y) * Settings.Screen_Size;
				SDL_RenderTexture(Core.Renderer, Cache.Wire_Cache.Data[
					Counter], NULL, &Cache.Wire_Box);
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
			SDL_FRect Temporary_Rectangle = { 0, 0, 640.0f * Settings.Screen_Size, 360.0f * Settings.Screen_Size };
			SDL_RenderTexture(Core.Renderer, Core.Game_Texture, NULL, &Temporary_Rectangle);
			if (Interface.Tool > 0) {
				SDL_FRect Hitbox = {
					0.0f, 0.0f,
					static_cast<float>(LDE_TILESIZE * Settings.Screen_Size),
					static_cast<float>(LDE_TILESIZE * Settings.Screen_Size)
				};
				Hitbox.x = static_cast<int>((static_cast<int>((Core.Mouse.X +
					(Core.Camera.X * Settings.Screen_Size)) / (LDE_TILESIZE * Settings
					.Screen_Size)) * (LDE_TILESIZE * Settings.Screen_Size)) - (Core
					.Camera.X * Settings.Screen_Size));
				Hitbox.y = static_cast<int>((static_cast<int>((Core.Mouse.Y +
					(Core.Camera.Y * Settings.Screen_Size)) / (LDE_TILESIZE * Settings
					.Screen_Size)) * (LDE_TILESIZE * Settings.Screen_Size)) - (Core
					.Camera.Y * Settings.Screen_Size));
				SDL_RenderTexture(Core.Renderer, Textures.Crosshair, NULL, &Hitbox);
				Hitbox.x = Core.Mouse.X - (LDE_TILESIZE * Settings.Screen_Size * 0.5f);
				Hitbox.y = Core.Mouse.Y - (LDE_TILESIZE * Settings.Screen_Size * 0.5f);
				SDL_RenderTexture(Core.Renderer, Textures.Cursor, NULL, &Hitbox);
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
					SDL_RenderTexture(Core.Renderer,
						Textures.Cursor_Core, NULL, &Hitbox);
				}
			}
		} else if (Interface.UI_Tab == 1) {
			SDL_RenderTexture(Core.Renderer, Textures.Logo,
				NULL, &Rects.Logo);
			Render_Dynamic_Text(Fonts.Logo_Font, "fish", Colors.Abyss_Black, 325, 44);
			Render_Dynamic_Text(Fonts.Logo_Font, "factory", Colors.Abyss_Black, 325, 78);
			Render_Button(Textures.New_Game, Rects.New_Game, 1, Colors.Cherry_Blossom);
			Render_Button(Textures.Settings, Rects.Settings, 2, Colors.Cherry_Blossom);
			Render_Button(Textures.Update_Logs, Rects.Update_Logs, 3, Colors.Cherry_Blossom);
			Render_Button(Textures.Credits, Rects.Credits, 4, Colors.Cherry_Blossom);
			Render_Button(Textures.Quit_Game, Rects.Quit_Game, 5, Colors.Cherry_Blossom);
			Render_Opening();
			Render_Closing(false);
		} else if (Interface.UI_Tab == 2) {
			Render_Saveloader();
			Render_Button(Textures.Return, Rects.Return, 1, Colors.Cherry_Blossom);
			Render_Opening();
			Render_Closing(false);
		} else if (Interface.UI_Tab == 3) {
			for (int Counter = 0; Counter < Textures.Settings_Label.Length; Counter++) {
				SDL_RenderTexture(Core.Renderer, Textures.Settings_Label
					.Data[Counter], NULL, &Rects.Settings_Label.Data[Counter]);
			}
			Render_Button(Textures.Return, Rects.Return, 1, Colors.Cherry_Blossom);
			Render_Slider(Interface_L.Slider_Texts[0], 1, 5, 4, Interface.Slider_Positions[0], 50, 70, 220,
				Colors.Abyss_Black, Colors.Cherry_Blossom, true);
			Render_Slider(Interface_L.Slider_Texts[4], 2, 4, 20, Interface.Slider_Positions[4], 50, 140, 220,
				Colors.Abyss_Black, Colors.Cherry_Blossom, true);
			Render_Slider(Interface_L.Slider_Texts[5], 3, 100, 21, Interface.Slider_Positions[5], 50, 210, 220,
				Colors.Abyss_Black, Colors.Cherry_Blossom, true);
			Render_Slider(Interface_L.Slider_Texts[6], 4, 2, 22, Interface.Slider_Positions[6], 50, 280, 220,
				Colors.Abyss_Black, Colors.Cherry_Blossom, true);
			if (Settings.AA_Temporary) {
				Render_Button(Textures.Anti_Aliasing.Data[0],
					Rects.Anti_Aliasing.Data[0], 5, Colors.Cherry_Blossom);
			} else {
				Render_Button(Textures.Anti_Aliasing.Data[1],
					Rects.Anti_Aliasing.Data[1], 5, Colors.Cherry_Blossom);
			}
			if (Settings.VS_Temporary) {
				Render_Button(Textures.V_Sync.Data[1], Rects.V_Sync.Data[1], 24, Colors.Cherry_Blossom);
			} else {
				Render_Button(Textures.V_Sync.Data[0], Rects.V_Sync.Data[0], 24, Colors.Cherry_Blossom);
			}
			if (Temporary.Settings_Changed) {
				Render_Button(Textures.Save_Settings, Rects.Save_Settings, 23, Colors.Cherry_Blossom);
			}
			Render_Dynamic_Text(Fonts.Subtext_Font, Metadata_L.Monitor_Size, Colors.Abyss_Black, 50, 40);
			for (int Counter1 = 0; Counter1 < Keybinds_L.Keybind_Texts.size(); Counter1++) {
				std::string Text = Keybinds_L.Keybind_Texts[Counter1] + "...";
				SDL_Surface* Prefix_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Text.c_str(),
					Text.size(), Colors.Abyss_Black);
				SDL_Texture* Prefix_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Prefix_Surface);
				SDL_FRect Prefix_Rectangle = { 370.0f * Settings.Screen_Size, static_cast<float>(
					40 + (16 * Counter1)) * Settings.Screen_Size, static_cast<float>(
						Prefix_Surface->w), static_cast<float>(Prefix_Surface->h) };
				SDL_RenderTexture(Core.Renderer, Prefix_Texture, NULL, &Prefix_Rectangle);
				if (Interface.Registering_Keybind == Counter1) {
					SDL_Surface* Registering_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font,
						"...", 3, Colors.Abyss_Black);
					SDL_Texture* Registering_Texture = SDL_GenerateTextureFromSurface(Core.Renderer,
						Registering_Surface);
					SDL_FRect Registering_Rectangle = { Prefix_Rectangle.x + Prefix_Rectangle.w + 20, Prefix_Rectangle.y,
						static_cast<float>(Registering_Surface->w), static_cast<float>(Registering_Surface->h) };
					SDL_RenderTexture(Core.Renderer, Registering_Texture, NULL, &Registering_Rectangle);
					SDL_DestroySurface(Registering_Surface);
					SDL_DestroyTexture(Registering_Texture);
				} else {
					std::string Subcore = SDL_GetKeyName(Keybinds_L.Keybind_Settings[Counter1]);
					for (int Counter2 = 0; Counter2 < Subcore.length(); Counter2++) {
						Subcore[Counter2] = static_cast<char>(std::tolower(Subcore[Counter2]));
					}
					SDL_Surface* Deadbutton_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font,
						Subcore.c_str(), Subcore.size(), Colors.Abyss_Black);
					SDL_Texture* Deadbutton_Texture = SDL_GenerateTextureFromSurface(Core.Renderer,
						Deadbutton_Surface);
					SDL_FRect Deadbutton_Rectangle = { Prefix_Rectangle.x + Prefix_Rectangle.w + 20, Prefix_Rectangle.y,
						static_cast<float>(Deadbutton_Surface->w), static_cast<float>(Deadbutton_Surface->h) };
					if (Detect_Mouse_Collision(Deadbutton_Rectangle)) {
						Interface.UI_Selection = Counter1 + 6;
						std::string Alivebutton_Text = "> " + Subcore + " <";
						SDL_Surface* Alivebutton_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font,
							Alivebutton_Text.c_str(), Alivebutton_Text.size(), Colors.Cherry_Blossom);
						SDL_Texture* Alivebutton_Texture = SDL_GenerateTextureFromSurface(Core.Renderer,
							Alivebutton_Surface);
						SDL_Surface* Temporary_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, "> ", 2,
							Colors.Cherry_Blossom);
						int Offset = Temporary_Surface->w;
						SDL_DestroySurface(Temporary_Surface);
						SDL_FRect Alivebutton_Rectangle = { Deadbutton_Rectangle.x - Offset, Deadbutton_Rectangle.y,
							static_cast<float>(Alivebutton_Surface->w), static_cast<float>(Alivebutton_Surface->h) };
						SDL_RenderTexture(Core.Renderer, Alivebutton_Texture, NULL, &Alivebutton_Rectangle);
						SDL_FRect Underline_Rectangle = { Deadbutton_Rectangle.x, Deadbutton_Rectangle.y + Deadbutton_Rectangle.h + 2,
							Deadbutton_Rectangle.w, Deadbutton_Rectangle.h / 10 };
						SDL_SetRenderDrawColor(Core.Renderer, Colors.Cherry_Blossom.r,
							Colors.Cherry_Blossom.g, Colors.Cherry_Blossom.b, SDL_ALPHA_OPAQUE);
						SDL_RenderFillRect(Core.Renderer, &Underline_Rectangle);
						Clear_Renderer();
						SDL_DestroySurface(Alivebutton_Surface);
						SDL_DestroyTexture(Alivebutton_Texture);
					} else {
						SDL_RenderTexture(Core.Renderer, Deadbutton_Texture, NULL, &Deadbutton_Rectangle);
					}
					SDL_DestroySurface(Deadbutton_Surface);
					SDL_DestroyTexture(Deadbutton_Texture);
				}
				SDL_DestroySurface(Prefix_Surface);
				SDL_DestroyTexture(Prefix_Texture);
			}
			Verify_Settings();
			Render_Opening();
			Render_Closing(false);
		} else if (Interface.UI_Tab == 4) {
			for (int Counter = 0; Counter < Cache.Log_Cache.Data[Changelog].Length; Counter++) {
				SDL_FRect Log_Rectangle = Cache_L.Log_Rectangles[Changelog][Counter];
				Log_Rectangle.y -= Interface.Log_Offset;
				SDL_RenderTexture(Core.Renderer, Cache.Log_Cache
					.Data[Changelog].Data[Counter], NULL, &Log_Rectangle);
			}
			SDL_RenderTexture(Core.Renderer, Textures.Log_Background, NULL,
				&Rects.Log_Background);
			Render_Dynamic_Text(Fonts.Subtext_Font, "Changelog - " +
				Truncate(Temporary.Scroll_Percent, 0) +
				"%", Colors.Abyss_Black, LDE_INVALID, 10);
			Render_Button(Textures.Return, Rects.Return, 1, Colors.Cherry_Blossom);
			if (Temporary.Log_Inversions[Changelog]) {
				Render_Button(Textures.Sort.Data[0], Rects.Sort.Data[0], 2, Colors.Cherry_Blossom);
			} else {
				Render_Button(Textures.Sort.Data[1], Rects.Sort.Data[1], 2, Colors.Cherry_Blossom);
			}
			if (Temporary.Scroll_Percent < 50) {
				Render_Button(Textures.TBW_Texture.Data[0], Rects.TBW_Rectangle.Data[0], 3, Colors.Cherry_Blossom);
			} else {
				Render_Button(Textures.TBW_Texture.Data[1], Rects.TBW_Rectangle.Data[1], 4, Colors.Cherry_Blossom);
			}
			Render_Opening();
			Render_Closing(true);
		} else if (Interface.UI_Tab == 5) {
			std::string Prefix = "Credits";
			switch (Interface.Slider_Positions[2]) {
			case 0:
				for (int Counter = 0; Counter < Cache.Log_Cache.Data[Credits].Length; Counter++) {
					SDL_FRect Log_Rectangle = Cache_L.Log_Rectangles[Credits][Counter];
					Log_Rectangle.y -= Interface.Log_Offset;
					SDL_RenderTexture(Core.Renderer, Cache.Log_Cache.Data[
						Credits].Data[Counter], NULL, &Log_Rectangle);
				}
				break;
			case 1:
				for (int Counter = 0; Counter < Cache.Log_Cache.Data[Legal].Length; Counter++) {
					SDL_FRect Log_Rectangle = Cache_L.Log_Rectangles[Legal][Counter];
					Log_Rectangle.y -= Interface.Log_Offset;
					SDL_RenderTexture(Core.Renderer, Cache.Log_Cache.Data[
						Legal].Data[Counter], NULL, &Log_Rectangle);
				}
				Prefix = "Legal";
				break;
			default:
				break;
			}
			SDL_RenderTexture(Core.Renderer, Textures.Log_Background, NULL,
				&Rects.Log_Background);
			Render_Dynamic_Text(Fonts.Subtext_Font, Prefix + " - " +
				Truncate(Temporary.Scroll_Percent, 0) +
				"%", Colors.Abyss_Black, LDE_INVALID, 10);
			Render_Button(Textures.Return, Rects.Return, 1, Colors.Cherry_Blossom);
			Render_Slider(Interface_L.Slider_Texts[2], 1, 1, 2, Interface.Slider_Positions[2], 200, 340, 240,
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
				double Sum = 0;
				for (int Counter = 0; Counter < Temporary_L.FPS_Query.size(); Counter++) {
					Sum += Temporary_L.FPS_Query[Counter];
				}
				Temporary.Temporary_FPS = static_cast<int>(Sum / Temporary_L.FPS_Query.size());
				Temporary_L.FPS_Query.clear();
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
				Render_Dynamic_Text(Fonts.Text_Font, "Time will not progress until a command platform is placed!",
					Colors.Cherry_Blossom, LDE_INVALID, 120);
			}
			if (!Interface.Animation_Locked && Interface.Prompt_Identifier ==
				P_None && Interface.Tool == LDE_INVALID) {
				Render_Tile_Prompts();
			}
			if (Interface.UD_Input != LDE_INVALID || Interface.LR_Input != LDE_INVALID) {
				int Increment = (Interface.Movespeed / Interface.Frame_Rate) *
					(1 + (static_cast<int>(Interface.Sprinting) * 4));
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
			Render_Dynamic_Text(Fonts.Halftext_Font, std::to_string(static_cast<int>(Temporary.Temporary_FPS)) +
				"/" + std::to_string(Interface.Frame_Rate) + " FPS", Colors.Abyss_Black, 10, 10);
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
		double Remaining_Delay = (1000 / Interface.Frame_Rate) - Total_Time;
		double True_Rate = 99999;
		if (Total_Time > 0) {
			True_Rate = 1000.0 / Total_Time;
		}
		if (True_Rate > Interface.Frame_Rate) {
			True_Rate = Interface.Frame_Rate;
		}
		Temporary_L.FPS_Query.push_back(True_Rate);
		SDL_Delay(static_cast<uint32_t>(std::max(Remaining_Delay, 0.0)));
	}
	Free_Text();
	Free_Preconfigurations();
	free(Temporary.Docks.Data);
	Temporary.Docks.Data = nullptr;
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