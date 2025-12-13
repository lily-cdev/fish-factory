#include <Core.h>
#include <Preloader.h>
#include <Items.h>
#include <Connectables.h>
#include <Grid_Handler.h>
#include <Interface_Handler.h>
#include <Render_Handler.h>
#include <Legacy.hpp>
#include <Terminal_Handler.h>
#include <Transition_Handler.h>
#include <Tutorial_Handler.h>
#include <UI_Handler.h>

Core Core_Access;
Metadata Metadata_Access;
Data Data_Access;
Settings Settings_Access;
Textures Textures_Access;
Rectangles Rectangles_Access;
Colors Colors_Access;
Fonts Fonts_Access;
Keybinds Keybinds_Access;
Temporary Temporary_Access;
Cache Cache_Access;
UI UI_Access;
Preconfigurations Preconfigurations_Access;
Preset_Items Preset_Items_Access;
Preset_Categories Preset_Categories_Access;
Transition Transition_Access;
Preset_Fish Preset_Fish_Access;
Preset_IO_Recipes Preset_IO_Recipes_Access;
Preset_I_Recipes Preset_I_Recipes_Access;
Preset_O_Recipes Preset_O_Recipes_Access;

SDL_ScaleMode Scaling_Quality;
Legacy_Item_Stack Legacy_Item_Grid[LDE_GRIDSIZE][LDE_GRIDSIZE];

int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	Audio_Access.Startup();
	Scaling_Quality = SDL_SCALEMODE_LINEAR;
	SDL_CreateWindowAndRenderer("Fish Factory", 640, 360, SDL_WINDOW_HIGH_PIXEL_DENSITY,
		&Core_Access.Application_Window, &Core_Access.Application_Renderer);
	Update_Metadata();
	Load_Settings();
	Clear_Settings();
	Reload_All();
	Force_Opening();
	while (Core_Access.Is_Running) {
		std::chrono::steady_clock::time_point Frame_Beginning = std::chrono::steady_clock::now();
		SDL_SetRenderDrawColor(Core_Access.Application_Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(Core_Access.Application_Renderer);
		Clear_Renderer();
		SDL_GetMouseState(&UI_Access.X_Mouse_Position, &UI_Access.Y_Mouse_Position);
		if (UI_Access.UI_Tab == LDE_INVALID) {
			if (Transition_Access.Transition_Frames < Transition_Access.Maximum_Transition_Frames) {
				Transition_Access.Transition_Frames++;
			} else {
				Trigger_Ambiance();
				Transition_Access.Transition_Phase = 2;
				UI_Access.UI_Tab = Transition_Access.Queried_Tab;
				Transition_Access.Transition_Frames = 0;
				Transition_Access.Maximum_Transition_Frames = static_cast<int>(UI_Access.Frame_Rate / 2);
			}
			SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
				.Door.Data[0], NULL, &Rectangles_Access.Door[0]);
			SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
				.Door.Data[1], NULL, &Rectangles_Access.Door[1]);
			if (Transition_Access.Transition_Frames > (Transition_Access.Maximum_Transition_Frames / 2) ||
				Transition_Access.Transition_Phase == 2) {
				SDL_FRect Indicator_Rectangle = { static_cast<float>(((2175 / 6.0f) - 20) * Settings_Access.Screen_Size),
					static_cast<float>(((1471 / 6.0f) - 20) *	Settings_Access.Screen_Size), 40.0f *
					Settings_Access.Screen_Size, 40.0f * Settings_Access.Screen_Size };
				SDL_RenderTexture(Core_Access.Application_Renderer,
					Textures_Access.RFlash, NULL, &Indicator_Rectangle);
			}
		} else if (UI_Access.UI_Tab == 0) {
			SDL_SetRenderTarget(Core_Access.Application_Renderer, Core_Access.Game_Texture);
			UI_Access.Ocean_Cycle += LDE_STATICRATE / UI_Access.Frame_Rate;
			if (UI_Access.Ocean_Cycle > 9) {
				UI_Access.Ocean_Cycle = 0;
			}
			SDL_FRect Ocean_Rectangle = {
				0,
				0,
				1200.0f * Settings_Access.Screen_Size,
				1200.0f * Settings_Access.Screen_Size
			};
			for (int Counter1 = 0; Counter1 < 3; Counter1++) {
				for (int Counter2 = 0; Counter2 < 3; Counter2++) {
					Ocean_Rectangle.x = (Counter1 * Ocean_Rectangle.w) -
						((UI_Access.Camera_X + LDE_BUFFERSIZE) * Settings_Access.Screen_Size);
					Ocean_Rectangle.y = (Counter2 * Ocean_Rectangle.h) -
						((UI_Access.Camera_Y + LDE_BUFFERSIZE) * Settings_Access.Screen_Size);
					SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.None
						.Data[static_cast<int>(UI_Access.Ocean_Cycle)], NULL, &Ocean_Rectangle);
				}
			}
			float Width = ((LDE_GRIDSIZE * 40) + (LDE_BUFFERSIZE * 2)) * Settings_Access.Screen_Size;
			SDL_FRect Mesh_Rectangle = {
				static_cast<float>(-(UI_Access.Camera_X + 70)) * Settings_Access.Screen_Size,
				static_cast<float>(-(UI_Access.Camera_Y + 70)) * Settings_Access.Screen_Size,
				static_cast<float>((LDE_GRIDSIZE * 40) + 140) * Settings_Access.Screen_Size,
				static_cast<float>((LDE_GRIDSIZE * 40) + 140) * Settings_Access.Screen_Size
			};
			SDL_RenderTexture(Core_Access.Application_Renderer,
				Textures_Access.Mesh, NULL,	&Mesh_Rectangle);
			for (int X = 0; X < 2; X++) {
				for (int Y = 0; Y < 2; Y++) {
					SDL_FRect Pyramid_Rectangle = {
						static_cast<float>(Width * X) - static_cast<float>(
							UI_Access.Camera_X * Settings_Access.Screen_Size) -
							(LDE_BUFFERSIZE * Settings_Access.Screen_Size),
						static_cast<float>(Width * Y) - static_cast<float>(
							UI_Access.Camera_Y * Settings_Access.Screen_Size) -
							(LDE_BUFFERSIZE * Settings_Access.Screen_Size),
						Width,
						Width
					};
					SDL_RenderTexture(Core_Access.Application_Renderer,
						Textures_Access.Pyramid.Data[(X * 2) + Y], NULL,
						&Pyramid_Rectangle);
				}
			}
			if (UI_Access.Building && Data_Access.Funds - Metadata_Access.Machine_Prices
				[UI_Access.Placing_Item - 1] > 0) {
				Build_Grid(UI_Access.Placing_Item);
				Update_Grid();
			}
			Render_Grid();
			if (Cache_Access.Wire_State != LDE_INVALID) {
				Render_Wires();
				if (Cache_Access.Wire_State == Deep_Recache) {
					Clear_Unconnected_Wires();
				}
				Cache_Access.Wire_State = LDE_INVALID;
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
				Cache_Access.Wire_Box.x = static_cast<int>(Offset_X -
					UI_Access.Camera_X) * Settings_Access.Screen_Size;
				Cache_Access.Wire_Box.y = static_cast<int>(Offset_Y -
					UI_Access.Camera_Y) * Settings_Access.Screen_Size;
				SDL_RenderTexture(Core_Access.Application_Renderer, Cache_Access
					.Wire_Cache.Data[Counter], NULL, &Cache_Access.Wire_Box);
			}
			if (UI_Access.Tool == 4) {
				Render_Pipes();
			}
			if (UI_Access.Tool == 0 && UI_Access.UI_Selection == 0) {
				int X;
				int Y;
				ID_To_Size(UI_Access.Placing_Item - 1, UI_Access.Placing_Rotation, X, Y);
				Render_Blueprint(X, Y);
			}
			Render_Submarine();
			SDL_SetRenderTarget(Core_Access.Application_Renderer, NULL);
			SDL_FRect Temporary_Rectangle = { 0, 0, 640.0f * Settings_Access.Screen_Size, 360.0f * Settings_Access.Screen_Size };
			SDL_RenderTexture(Core_Access.Application_Renderer, Core_Access.Game_Texture, NULL, &Temporary_Rectangle);
			if (UI_Access.Tool > 0) {
				SDL_FRect Hitbox = { 0, 0, 40.0f * Settings_Access.Screen_Size, 40.0f * Settings_Access.Screen_Size };
				Hitbox.x = static_cast<int>((static_cast<int>((UI_Access.X_Mouse_Position + (UI_Access.Camera_X *
					Settings_Access.Screen_Size)) /	(40 * Settings_Access.Screen_Size)) * (40 * Settings_Access.Screen_Size)) -
					(UI_Access.Camera_X * Settings_Access.Screen_Size));
				Hitbox.y = static_cast<int>((static_cast<int>((UI_Access.Y_Mouse_Position + (UI_Access.Camera_Y *
					Settings_Access.Screen_Size)) /	(40 * Settings_Access.Screen_Size)) * (40 * Settings_Access.Screen_Size)) -
					(UI_Access.Camera_Y * Settings_Access.Screen_Size));
				SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Crosshair, NULL, &Hitbox);
				Hitbox.x = UI_Access.X_Mouse_Position - (20 * Settings_Access.Screen_Size);
				Hitbox.y = UI_Access.Y_Mouse_Position - (20 * Settings_Access.Screen_Size);
				SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Cursor, NULL, &Hitbox);
				bool Targeting = false;
				switch (UI_Access.Tool) {
				case 1:
					if (Get_Simple_Grid_Tile(Data_Access.Visual_Grid, 0) != 0) {
						Targeting = true;
					}
					break;
				default:
					break;
				}
				if (Targeting) {
					SDL_RenderTexture(Core_Access.Application_Renderer,
						Textures_Access.Cursor_Core, NULL, &Hitbox);
				}
			}
		} else if (UI_Access.UI_Tab == 1) {
			SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Logo,
				NULL, &Rectangles_Access.Logo);
			Render_Dynamic_Text(Fonts_Access.Logo_Font, "fish", Colors_Access.Abyss_Black, 325, 44);
			Render_Dynamic_Text(Fonts_Access.Logo_Font, "factory", Colors_Access.Abyss_Black, 325, 78);
			Render_Button(Textures_Access.New_Game, Rectangles_Access.New_Game, 1);
			Render_Button(Textures_Access.Settings, Rectangles_Access.Settings, 2);
			Render_Button(Textures_Access.Update_Logs, Rectangles_Access.Update_Logs, 3);
			Render_Button(Textures_Access.Credits, Rectangles_Access.Credits, 4);
			Render_Button(Textures_Access.Quit_Game, Rectangles_Access.Quit_Game, 5);
			Render_Opening();
			Render_Closing();
		} else if (UI_Access.UI_Tab == 2) {
			Render_Saveloader();
			Render_Button(Textures_Access.Return, Rectangles_Access.Return, 1);
			Render_Opening();
			Render_Closing();
		} else if (UI_Access.UI_Tab == 3) {
			for (int Counter = 0; Counter < Textures_Access.Settings_Label.Length; Counter++) {
				SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Settings_Label
					.Data[Counter], NULL, &Rectangles_Access.Settings_Label.Data[Counter]);
			}
			Render_Button(Textures_Access.Return, Rectangles_Access.Return, 1);
			Render_Slider(UI_Access.Slider_Texts[0], 1, 5, 4, UI_Access.Slider_Positions[0], 50, 70, 220,
				Colors_Access.Abyss_Black, Colors_Access.Cherry_Blossom, true);
			Render_Slider(UI_Access.Slider_Texts[4], 2, 4, 20, UI_Access.Slider_Positions[4], 50, 140, 220,
				Colors_Access.Abyss_Black, Colors_Access.Cherry_Blossom, true);
			Render_Slider(UI_Access.Slider_Texts[5], 3, 100, 21, UI_Access.Slider_Positions[5], 50, 210, 220,
				Colors_Access.Abyss_Black, Colors_Access.Cherry_Blossom, true);
			Render_Slider(UI_Access.Slider_Texts[6], 4, 2, 22, UI_Access.Slider_Positions[6], 50, 280, 220,
				Colors_Access.Abyss_Black, Colors_Access.Cherry_Blossom, true);
			if (Settings_Access.AA_Temporary) {
				Render_Button(Textures_Access.Anti_Aliasing.Data[0],
					Rectangles_Access.Anti_Aliasing.Data[0], 5);
			} else {
				Render_Button(Textures_Access.Anti_Aliasing.Data[1],
					Rectangles_Access.Anti_Aliasing.Data[1], 5);
			}
			if (Settings_Access.VS_Temporary) {
				Render_Button(Textures_Access.V_Sync.Data[1], Rectangles_Access.V_Sync.Data[1], 24);
			} else {
				Render_Button(Textures_Access.V_Sync.Data[0], Rectangles_Access.V_Sync.Data[0], 24);
			}
			if (Temporary_Access.Settings_Changed) {
				Render_Button(Textures_Access.Save_Settings, Rectangles_Access.Save_Settings, 23);
			}
			Render_Dynamic_Text(Fonts_Access.Subtext_Font, Metadata_Access.Monitor_Size, Colors_Access.Abyss_Black, 50, 40);
			for (int First_Counter = 0; First_Counter < Keybinds_Access.Keybind_Texts.size(); First_Counter++) {
				std::string Text = Keybinds_Access.Keybind_Texts[First_Counter] + "...";
				SDL_Surface* Prefix_Surface = TTF_RenderText_Blended(Fonts_Access.Subtext_Font, Text.c_str(),
					Text.size(), Colors_Access.Abyss_Black);
				SDL_Texture* Prefix_Texture = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Prefix_Surface);
				SDL_FRect Prefix_Rectangle = { 370.0f * Settings_Access.Screen_Size, static_cast<float>(
					40 + (16 * First_Counter)) * Settings_Access.Screen_Size, static_cast<float>(
						Prefix_Surface->w), static_cast<float>(Prefix_Surface->h) };
				SDL_RenderTexture(Core_Access.Application_Renderer, Prefix_Texture, NULL, &Prefix_Rectangle);
				if (UI_Access.Registering_Keybind == First_Counter) {
					SDL_Surface* Registering_Surface = TTF_RenderText_Blended(Fonts_Access.Subtext_Font,
						"...", 3, Colors_Access.Abyss_Black);
					SDL_Texture* Registering_Texture = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer,
						Registering_Surface);
					SDL_FRect Registering_Rectangle = { Prefix_Rectangle.x + Prefix_Rectangle.w + 20, Prefix_Rectangle.y,
						static_cast<float>(Registering_Surface->w), static_cast<float>(Registering_Surface->h) };
					SDL_RenderTexture(Core_Access.Application_Renderer, Registering_Texture, NULL, &Registering_Rectangle);
					SDL_DestroySurface(Registering_Surface);
					SDL_DestroyTexture(Registering_Texture);
				} else {
					std::string Core = SDL_GetKeyName(Keybinds_Access.Keybind_Settings[First_Counter]);
					for (int Second_Counter = 0; Second_Counter < Core.length(); Second_Counter++) {
						Core[Second_Counter] = static_cast<char>(std::tolower(Core[Second_Counter]));
					}
					SDL_Surface* Deadbutton_Surface = TTF_RenderText_Blended(Fonts_Access.Subtext_Font,
						Core.c_str(), Core.size(), Colors_Access.Abyss_Black);
					SDL_Texture* Deadbutton_Texture = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer,
						Deadbutton_Surface);
					SDL_FRect Deadbutton_Rectangle = { Prefix_Rectangle.x + Prefix_Rectangle.w + 20, Prefix_Rectangle.y,
						static_cast<float>(Deadbutton_Surface->w), static_cast<float>(Deadbutton_Surface->h) };
					if (Detect_Mouse_Collision(Deadbutton_Rectangle)) {
						UI_Access.UI_Selection = First_Counter + 6;
						std::string Alivebutton_Text = "> " + Core + " <";
						SDL_Surface* Alivebutton_Surface = TTF_RenderText_Blended(Fonts_Access.Subtext_Font,
							Alivebutton_Text.c_str(), Alivebutton_Text.size(), Colors_Access.Cherry_Blossom);
						SDL_Texture* Alivebutton_Texture = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer,
							Alivebutton_Surface);
						SDL_Surface* Temporary_Surface = TTF_RenderText_Blended(Fonts_Access.Subtext_Font, "> ", 2,
							Colors_Access.Cherry_Blossom);
						int Offset = Temporary_Surface->w;
						SDL_DestroySurface(Temporary_Surface);
						SDL_FRect Alivebutton_Rectangle = { Deadbutton_Rectangle.x - Offset, Deadbutton_Rectangle.y,
							static_cast<float>(Alivebutton_Surface->w), static_cast<float>(Alivebutton_Surface->h) };
						SDL_RenderTexture(Core_Access.Application_Renderer, Alivebutton_Texture, NULL, &Alivebutton_Rectangle);
						SDL_FRect Underline_Rectangle = { Deadbutton_Rectangle.x, Deadbutton_Rectangle.y + Deadbutton_Rectangle.h + 2,
							Deadbutton_Rectangle.w, Deadbutton_Rectangle.h / 10 };
						SDL_SetRenderDrawColor(Core_Access.Application_Renderer, Colors_Access.Cherry_Blossom.r,
							Colors_Access.Cherry_Blossom.g, Colors_Access.Cherry_Blossom.b, SDL_ALPHA_OPAQUE);
						SDL_RenderFillRect(Core_Access.Application_Renderer, &Underline_Rectangle);
						Clear_Renderer();
						SDL_DestroySurface(Alivebutton_Surface);
						SDL_DestroyTexture(Alivebutton_Texture);
					} else {
						SDL_RenderTexture(Core_Access.Application_Renderer, Deadbutton_Texture, NULL, &Deadbutton_Rectangle);
					}
					SDL_DestroySurface(Deadbutton_Surface);
					SDL_DestroyTexture(Deadbutton_Texture);
				}
				SDL_DestroySurface(Prefix_Surface);
				SDL_DestroyTexture(Prefix_Texture);
			}
			Verify_Settings();
			Render_Opening();
			Render_Closing();
		} else if (UI_Access.UI_Tab == 4) {
			for (int Counter = 0; Counter < Cache_Access.Log_Cache.Data[Changelog].Length; Counter++) {
				SDL_FRect Log_Rectangle = Cache_Access.Log_Rectangles[Changelog][Counter];
				Log_Rectangle.y -= UI_Access.Log_Offset;
				SDL_RenderTexture(Core_Access.Application_Renderer, Cache_Access.Log_Cache
					.Data[Changelog].Data[Counter], NULL, &Log_Rectangle);
			}
			SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Log_Background, NULL,
				&Rectangles_Access.Log_Background);
			Render_Dynamic_Text(Fonts_Access.Subtext_Font, "Changelog - " +
				Truncate(Temporary_Access.Scroll_Percent, 0) +
				"%", Colors_Access.Abyss_Black, LDE_INVALID, 10);
			Render_Button(Textures_Access.Return, Rectangles_Access.Return, 1);
			if (Temporary_Access.Log_Inversions[Changelog]) {
				Render_Button(Textures_Access.Sort.Data[0], Rectangles_Access.Sort.Data[0], 2);
			} else {
				Render_Button(Textures_Access.Sort.Data[1], Rectangles_Access.Sort.Data[1], 2);
			}
			if (Temporary_Access.Scroll_Percent < 50) {
				Render_Button(Textures_Access.TBW_Texture.Data[0], Rectangles_Access.TBW_Rectangle.Data[0], 3);
			} else {
				Render_Button(Textures_Access.TBW_Texture.Data[1], Rectangles_Access.TBW_Rectangle.Data[1], 4);
			}
			Render_Opening();
			Render_Closing(true);
		} else if (UI_Access.UI_Tab == 5) {
			std::string Prefix = "Credits";
			switch (UI_Access.Slider_Positions[2]) {
			case 0:
				for (int Counter = 0; Counter < Cache_Access.Log_Cache.Data[Credits].Length; Counter++) {
					SDL_FRect Log_Rectangle = Cache_Access.Log_Rectangles[Credits][Counter];
					Log_Rectangle.y -= UI_Access.Log_Offset;
					SDL_RenderTexture(Core_Access.Application_Renderer, Cache_Access
						.Log_Cache.Data[Credits].Data[Counter], NULL, &Log_Rectangle);
				}
				break;
			case 1:
				for (int Counter = 0; Counter < Cache_Access.Log_Cache.Data[Legal].Length; Counter++) {
					SDL_FRect Log_Rectangle = Cache_Access.Log_Rectangles[Legal][Counter];
					Log_Rectangle.y -= UI_Access.Log_Offset;
					SDL_RenderTexture(Core_Access.Application_Renderer, Cache_Access
						.Log_Cache.Data[Legal].Data[Counter], NULL, &Log_Rectangle);
				}
				Prefix = "Legal";
				break;
			default:
				break;
			}
			SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Log_Background, NULL,
				&Rectangles_Access.Log_Background);
			Render_Dynamic_Text(Fonts_Access.Subtext_Font, Prefix + " - " +
				Truncate(Temporary_Access.Scroll_Percent, 0) +
				"%", Colors_Access.Abyss_Black, LDE_INVALID, 10);
			Render_Button(Textures_Access.Return, Rectangles_Access.Return, 1);
			Render_Slider(UI_Access.Slider_Texts[2], 1, 1, 2, UI_Access.Slider_Positions[2], 200, 340, 240,
				Colors_Access.Abyss_Black, Colors_Access.Cherry_Blossom, false);
			Render_Opening();
			Render_Closing(true);
		}
		Process_Inputs();
		switch (UI_Access.UI_Tab) {
		case 0:
			if (UI_Access.Subtime_Frames < UI_Access.Maximum_Subtime_Frames) {
				UI_Access.Subtime_Frames++;
			} else {
				UI_Access.Subtime_Frames = 0;
				double Sum = 0;
				for (int Counter = 0; Counter < Temporary_Access.FPS_Query.size(); Counter++) {
					Sum += Temporary_Access.FPS_Query[Counter];
				}
				Temporary_Access.Temporary_FPS = static_cast<int>(Sum / Temporary_Access.FPS_Query.size());
				Temporary_Access.FPS_Query.clear();
			}
			if (Data_Access.CMD_Placed) {
				if (Data_Access.Time < 1440) {
					if (UI_Access.Time_Frames < UI_Access.Maximum_Time_Frames) {
						UI_Access.Time_Frames++;
					} else {
						UI_Access.Time_Frames = 0;
						Data_Access.Time = Data_Access.Time + 1;
						Update_Machines();
						Update_Power();
						Update_Pipes();
						Purge_Items();
						Process_Tutorial(LDE_INVALID);
					}
				} else if (UI_Access.Prompt_Identifier != 2) {
					UI_Access.Prompt_Identifier = 2;
					UI_Access.Tool = LDE_INVALID;
				}
			} else {
				Render_Dynamic_Text(Fonts_Access.Text_Font, "Time will not progress until a command platform is placed!",
					Colors_Access.Cherry_Blossom, LDE_INVALID, 120);
			}
			if (!UI_Access.Animation_Locked && UI_Access.Prompt_Identifier == LDE_INVALID && UI_Access.Tool == LDE_INVALID) {
				Render_Tile_Prompts();
			}
			if (UI_Access.UD_Input != LDE_INVALID || UI_Access.LR_Input != LDE_INVALID) {
				int Increment = (UI_Access.Movespeed / UI_Access.Frame_Rate) *
					(1 + (static_cast<int>(UI_Access.Sprinting) * 4));
				if (UI_Access.UD_Input == 0) {
					UI_Access.Camera_Y = UI_Access.Camera_Y - Increment;
					Find_Effect();
					if (UI_Access.Camera_Y < -LDE_BUFFERSIZE) {
						UI_Access.Camera_Y = -LDE_BUFFERSIZE;
						UI_Access.UD_Input = LDE_INVALID;
					}
				} else if (UI_Access.UD_Input == 1) {
					UI_Access.Camera_Y = UI_Access.Camera_Y + Increment;
					Find_Effect();
					if (UI_Access.Camera_Y > UI_Access.Map_Y) {
						UI_Access.Camera_Y = UI_Access.Map_Y;
						UI_Access.UD_Input = LDE_INVALID;
					}
				}
				if (UI_Access.LR_Input == 0) {
					UI_Access.Camera_X = UI_Access.Camera_X - Increment;
					Find_Effect();
					if (UI_Access.Camera_X < -LDE_BUFFERSIZE) {
						UI_Access.Camera_X = -LDE_BUFFERSIZE;
						UI_Access.LR_Input = LDE_INVALID;
					}
				} else if (UI_Access.LR_Input == 1) {
					UI_Access.Camera_X = UI_Access.Camera_X + Increment;
					Find_Effect();
					if (UI_Access.Camera_X > UI_Access.Map_X) {
						UI_Access.Camera_X = UI_Access.Map_X;
						UI_Access.LR_Input = LDE_INVALID;
					}
				}
			}
			Drain_Query();
			Render_Toolbar();
			Render_Dynamic_Text(Fonts_Access.Halftext_Font, std::to_string(static_cast<int>(Temporary_Access.Temporary_FPS)) +
				"/" + std::to_string(UI_Access.Frame_Rate) + " FPS", Colors_Access.Abyss_Black, 10, 10);
			Render_Effects();
			Render_Game_UI();
			Render_Prompts();
			Render_Tutorial();
			Render_Opening();
			Render_Closing();
			break;
		default:
			break;
		}
		SDL_RenderPresent(Core_Access.Application_Renderer);
		std::chrono::steady_clock::time_point Frame_End = std::chrono::steady_clock::now();
		double Total_Time = std::chrono::duration_cast<std::chrono::milliseconds>(
			Frame_End - Frame_Beginning).count();
		double Remaining_Delay = (1000 / UI_Access.Frame_Rate) - Total_Time;
		double True_Rate = 1 / (Total_Time / 1000);
		if (True_Rate > UI_Access.Frame_Rate) {
			True_Rate = UI_Access.Frame_Rate;
		}
		Temporary_Access.FPS_Query.push_back(True_Rate);
		SDL_Delay(static_cast<Uint32>(std::max(Remaining_Delay, 0.0)));
	}
	Audio_Access.Shutdown();
	SDL_ShowCursor();
	Cleanup_Assets();
	SDL_DestroyRenderer(Core_Access.Application_Renderer);
	SDL_DestroyWindow(Core_Access.Application_Window);
	SDL_PumpEvents();
	TTF_Quit();
	SDL_Quit();
	return 0;
}