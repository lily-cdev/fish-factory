#include <ui.h>

void Render_Toolbar() {
	if (Interface.Tool > LDE_INVALID) {
		Set_Renderer_Color(Colors.Dark_Grey);
		SDL_FRect Backing_Rectangle = Rects.Tool[Interface.Tool];
		Backing_Rectangle.x = Backing_Rectangle.x - (Settings.Screen_Size * 2);
		Backing_Rectangle.w = Backing_Rectangle.w + (Settings.Screen_Size * 4);
		Backing_Rectangle.y = Settings.Screen_Size * 330;
		Backing_Rectangle.h = Settings.Screen_Size * 38;
		SDL_RenderFillRect(Core.Renderer, &Backing_Rectangle);
		Backing_Rectangle.y = Settings.Screen_Size * 334;
		Backing_Rectangle.h = Settings.Screen_Size * 34;
		Set_Renderer_Color(Colors.Light_Grey);
		SDL_RenderFillRect(Core.Renderer, &Backing_Rectangle);
		Clear_Renderer();
		Rects.Cap.x = Backing_Rectangle.x + Backing_Rectangle.w;
		Rects.Cap_Button.x = Rects.Cap.x + Rects.Cap.w + 12;
		Rects.Cap_Hitbox.Data[0] = Rects.Cap_Button;
		Rects.Cap_Hitbox.Data[1] = Rects.Cap_Button;
		Render_Button(&Textures.Cap_Button.Data[0], &Rects.Cap_Hitbox, 4, Colors.Cherry_Blossom);
		Render_Texture(Textures.Cap.Data[0], &Rects.Cap);
		Rects.Cap.x = Backing_Rectangle.x - Rects.Cap.w;
		Rects.Cap_Button.x = Rects.Cap.x - Rects.Cap_Button.w - 12;
		Rects.Cap_Hitbox.Data[0] = Rects.Cap_Button;
		Rects.Cap_Hitbox.Data[1] = Rects.Cap_Button;
		Render_Button(&Textures.Cap_Button.Data[1], &Rects.Cap_Hitbox, 5, Colors.Cherry_Blossom);
		Render_Texture(Textures.Cap.Data[1], &Rects.Cap);
		Render_Texture(Textures.Tool.Data[Interface.Tool], &Rects.Tool[Interface.Tool]);
	}
	if (Interface.Tool == 0) {
		char Machine_Text[64];
		char Price_Query[64];
		Abbreviate_Number(Interface.Queried_Price, Price_Query, sizeof(Price_Query));
		snprintf(Machine_Text, sizeof(Machine_Text), "%s | %sLA", Metadata.Names[Interface.Placing_Item - 1], Price_Query);
		SDL_Surface* Machine_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Machine_Text, 0, Colors.Abyss_Black);
		SDL_FRect Machine_Rectangle = {
			(float)(Settings.Screen_Size * 312) - (Machine_Surface->w * 0.5f),
			Settings.Screen_Size * 290.0f,
			Machine_Surface->w + (float)(Settings.Screen_Size * 16),
			TTF_GetFontHeight(Fonts.Subtext_Font) + (float)(Settings.Screen_Size * 18)
		};
		Set_Renderer_Color(Colors.Dark_Grey);
		SDL_RenderFillRect(Core.Renderer, &Machine_Rectangle);
		Machine_Rectangle.x += (Settings.Screen_Size * 4);
		Machine_Rectangle.y += (Settings.Screen_Size * 4);
		Machine_Rectangle.w -= (Settings.Screen_Size * 8);
		Machine_Rectangle.h -= (Settings.Screen_Size * 8);
		Set_Renderer_Color(Colors.Light_Grey);
		SDL_RenderFillRect(Core.Renderer, &Machine_Rectangle);
		Clear_Renderer();
		Machine_Rectangle.x += (Settings.Screen_Size * 4);
		Machine_Rectangle.y += (Settings.Screen_Size * 4);
		Machine_Rectangle.w = Machine_Surface->w;
		Machine_Rectangle.h = Machine_Surface->h;
		SDL_Texture* Machine_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Machine_Surface);
		Render_Texture(Machine_Texture, &Machine_Rectangle);
		SDL_DestroySurface(Machine_Surface);
		free_texture(Machine_Texture);
	}
}

void Verify_Settings() {
	bool Keybinds_Altered = false;
	for (int Counter = 0; Counter < LDE_KEYBINDS; Counter++) {
		if (Keybinds.Keybind_Settings[Counter] != Keybinds.Keybind_List[Counter]) {
			Keybinds_Altered = true;
			break;
		}
	}
	if (Settings.Screen_Size != Interface.Slider_Positions[0] + 1 || Keybinds_Altered || (int)(Settings.AA_Temporary) !=
		Settings.Anti_Aliasing || (int)(Settings.VS_Temporary) != Settings.VSync || Settings.Raw_FPS !=
		Interface.Slider_Positions[4] || Settings.Volume != Interface.Slider_Positions[5] || Interface.Slider_Positions[6] !=
		Settings.Fullscreen) {
		Render_Button(&Textures.Apply, &Rects.Apply, 2, Colors.Cherry_Blossom);
		Render_Button(&Textures.Cancel, &Rects.Cancel, 3, Colors.Cherry_Blossom);
	}
}

void Render_Tile_Prompts() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				for (int Counter = 0; Counter < intlen(Metadata.Quirk_Positions[Q_Interactable]); Counter++) {
					if (Visual_To_ID(Data.Visual_Grid[Column][Row]) == Metadata.Quirk_Positions[Q_Interactable][Counter]) {
						char Subcore[64];
						char Sub2core[64];
						strcpy(Sub2core, SDL_GetKeyName(Keybinds.Keybind_List[10]));
						for (int Counter = 0; Counter < strlen(Sub2core); Counter++) {
							Sub2core[Counter] = (char)(tolower(Sub2core[Counter]));
						}
						snprintf(Subcore, sizeof(Subcore), "interact - (\"%s\")", Sub2core);
						SDL_Surface* Carrying_Surface = TTF_RenderText_Blended(Fonts.Halftext_Font, Subcore, 0,
							Colors.Cherry_Blossom);
						SDL_FRect Carrying_Rectangle = {
							(float)(Settings.Screen_Size * 320) - (Carrying_Surface->w * 0.5),
							Settings.Screen_Size * 320.0f,
							(float)(Carrying_Surface->w),
							(float)(Carrying_Surface->h)
						};
						SDL_Texture* Carrying_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Carrying_Surface);
						Render_Box((Carrying_Rectangle.x / Settings.Screen_Size) - 4,
							(Carrying_Rectangle.y / Settings.Screen_Size) - 4,
							(Carrying_Rectangle.w / Settings.Screen_Size) + 8,
							(Carrying_Rectangle.h / Settings.Screen_Size) + 8,
							Colors.Light_Grey, Colors.Dark_Grey);
						Render_Texture(Carrying_Texture, &Carrying_Rectangle);
						SDL_DestroySurface(Carrying_Surface);
						free_texture(Carrying_Texture);
					}
				}
			}
		}
	}
}

void Render_Interaction() {
	int Indexes[7] = { 4, 3, 5, 6, 7, 8, 10 };
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Screen_Size);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				for (int Counter = 0; Counter < intlen(Metadata.Quirk_Positions[Q_Interactable]); Counter++) {
					if (Visual_To_ID(Data.Visual_Grid[Column][Row]) == Metadata.Quirk_Positions[Q_Interactable][Counter]) {
						Interface.Prompt_Identifier = Indexes[Counter];
						Interface.Building = false;
						Interface.Target_Tile.X = Column;
						Interface.Target_Tile.Y = Row;
						switch (Visual_To_ID(Data.Visual_Grid[Column][Row])) {
						case Money_Generator:
							Interface.Slider_Positions[8] = Data.Settings_Grid[Interface.Target_Tile.X][
								Interface.Target_Tile.Y][3];
							break;
						case Fluid_Generator:
							Interface.Slider_Positions[9] = Data.Settings_Grid[Interface.Target_Tile.X][
								Interface.Target_Tile.Y][3];
							Interface.Slider_Positions[10] = (int)(Data.Settings_Grid[Interface.Target_Tile.X][
								Interface.Target_Tile.Y][4] * 0.2f);
							for (int Counter = 0; Counter < LDE_VALVE300LENGTH; Counter++) {
								if (Data.Settings_Grid[Interface.Target_Tile.X][Interface.Target_Tile.Y][5] ==
									Interface.Valve300_Postions[Counter]) {
									Interface.Slider_Positions[11] = Counter;
									break;
								}
							}
							break;
						default:
							break;
						}
						break;
					}
				}
				return;
			}
		}
	}
}

void Render_Effects() {
	if (Interface.Effects[E_Heat] > 0) {
		//std::cout << "boilin'" << " ";
	}
	if (Interface.Effects[E_Radiation] > 0) {
		Set_Renderer_Color(Colors.Pure_White);
		uint32_t State = (uint32_t)(SDL_GetTicks() & UINT8_MAX);
		for (int Counter = 0; Counter < floor(Interface.Effects[E_Radiation]); Counter++) {
			step_c(State);
			int X = State % (Settings.Screen_Size * 640);
			step_c(State);
			int Y = State % (Settings.Screen_Size * 320);
			SDL_RenderPoint(Core.Renderer, (float)X, (float)Y);
		}
		Clear_Renderer();
		//play geiger tick
	}
}

void Find_Effect() {
	Interface.Effects[E_Heat] = 0;
	Interface.Effects[E_Radiation] = 0;
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			for (int Counter = 0; Counter < intlen(Metadata.Heating_Machines); Counter++) {
				if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Metadata.Heating_Machines[Counter] &&
					X * LDE_TILESIZE > Core.Camera.X && Y * LDE_TILESIZE > Core.Camera.Y && X * LDE_TILESIZE <
					Core.Camera.X + 640 && Y * LDE_TILESIZE < Core.Camera.Y + 360) {
					Interface.Effects[E_Heat] += 0.1;
					return;
				}
			}
			for (int Counter = 0; Counter < intlen(Metadata.Irradiating_Machines); Counter++) {
				if (Visual_To_ID(Data.Visual_Grid[X][Y]) == Metadata.Irradiating_Machines[Counter]) {
					float A = ((Core.Camera.X + 320) - (X * LDE_TILESIZE)) * Settings.Screen_Size;
					float B = ((Core.Camera.Y + 180) - (Y * LDE_TILESIZE)) * Settings.Screen_Size;
					float Distance = sqrtf(sqr_f(A) + sqr_f(B)) / (float)LDE_TILESIZE;
					Interface.Effects[E_Radiation] += fmax(((int)(-0.2625 * sqr_f(Distance)) + 105) * Settings.Screen_Size,
						0.0f);
					return;
				}
			}
		}
	}
}

void Cache_Blueprint() {
	int Width;
	int Height;
	ID_To_Size(Interface.Placing_Item - 1, Interface.Placing_Rotation, &Width, &Height);
	int Maximum = (Width > Height ? Width : Height) * Settings.Screen_Size * LDE_TILESIZE;
	free_texture(Cache.Blueprint_Cache);
	Cache.Blueprint_Cache = SDL_GenerateTexture(Core.Renderer, Maximum, Maximum);
	SDL_SetTextureBlendMode(Cache.Blueprint_Cache, SDL_BLENDMODE_BLEND);
	SDL_Texture* Backing = SDL_GenerateTexture(Core.Renderer, Width * Settings.Screen_Size * LDE_TILESIZE, Height *
		Settings.Screen_Size * LDE_TILESIZE);
	SDL_SetTextureBlendMode(Backing, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Backing);
	for (int X = 0; X < Width; X++) {
		for (int Y = 0; Y < Height; Y++) {
			SDL_FRect Pasting_Rectangle = Rects.Tile_1x1;
			Pasting_Rectangle.x = X * Settings.Screen_Size * LDE_TILESIZE;
			Pasting_Rectangle.y = Y * Settings.Screen_Size * LDE_TILESIZE;
			Render_Texture(Textures.Tile_Texture, &Pasting_Rectangle);
		}
	}
	SDL_SetRenderTarget(Core.Renderer, Cache.Blueprint_Cache);
	Render_Texture(Backing, NULL);
	free_texture(Backing);
	int Rotation = Interface.Placing_Rotation * 90;
	for (int Counter = 0; Counter < intlen(Metadata.Quirk_Positions[Q_Non_Rotatable]); Counter++) {
		if (Metadata.Quirk_Positions[Q_Non_Rotatable][Counter] == Interface.Placing_Item - 1) {
			Rotation = 0;
		}
	}
	SDL_FPoint Centerpoint = { Maximum * 0.5f, Maximum * 0.5f };
	SDL_RenderTextureRotated(Core.Renderer, Metadata.Machine_Sprites[Interface.Placing_Item - 1], NULL, NULL, Rotation,
		&Centerpoint, SDL_FLIP_NONE);
	SDL_SetRenderTarget(Core.Renderer, NULL);
	SDL_SetTextureAlphaMod(Cache.Blueprint_Cache, 190);
}

void Cache_Price() {
	Interface.Queried_Price = (int)((Metadata.Machine_Prices[Interface.Placing_Item - 1] * 1.1)) + Metadata.Machine_Taxes[
		Interface.Placing_Item - 1] + 1;
}

void Render_Slider(char Labels[256][32], int Engagement, int Nodes, int Selection, int* Position, int X, int Y, int Width,
	SDL_Color Primary, SDL_Color Secondary, bool Text_Visible) {
	bool Active = false;
	SDL_FRect Background_Rectangle = {
		(float)(X * Settings.Screen_Size),
		(float)(Y - 3) * Settings.Screen_Size,
		(float)(Width * Settings.Screen_Size),
		Settings.Screen_Size * 6.0f
	};
	if (Interface.Engagement == Engagement) {
		Active = true;
		int Separators[512];
		for (int Counter = 0; Counter < Nodes; Counter++) {
			Separators[Counter] = (int)(((((float)Counter / Nodes) * Width) + (Width / (Nodes * 2)) + X)) *
				Settings.Screen_Size;
		}
		Separators[Nodes] = LDE_TERMINATOR;
		for (int Counter = 0; Counter < Nodes; Counter++) {
			if (Core.Debug_Mode) {
				SDL_RenderLine(Core.Renderer, (float)(Separators[Counter]), 0, (float)(Separators[Counter]),
					Settings.Screen_Size * 360.0f);
			}
			if (Core.Mouse.X < Separators[0]) {
				*Position = 0;
			} else if (Core.Mouse.X >= Separators[Nodes - 1]) {
				*Position = Nodes;
			} else if (Core.Mouse.X >= Separators[Counter] && Core.Mouse.X < Separators[Counter + 1]) {
				*Position = Counter + 1;
			}
		}
	}
	Set_Renderer_Color(Primary);
	SDL_RenderFillRect(Core.Renderer, &Background_Rectangle);
	if (Active) {
		Set_Renderer_Color(Secondary);
	}
	SDL_FRect Node_Rectangle = {
		(float)((((float)(*Position) / Nodes) * Width) + X - 6) * Settings.Screen_Size,
		(float)(Y - 6) * Settings.Screen_Size,
		Settings.Screen_Size * 12.0f,
		Settings.Screen_Size * 12.0f
	};
	if (Detect_Mouse_Collision(Node_Rectangle)) {
		Interface.UI_Selection = Selection;
		Set_Renderer_Color(Secondary);
	}
	SDL_RenderFillRect(Core.Renderer, &Node_Rectangle);
	Clear_Renderer();
	if (Text_Visible) {
		SDL_Surface* Caption_Surface = TTF_RenderText_Blended(Fonts.Subtext_Font, Labels[*Position], 0, Primary);
		SDL_FRect Caption_Rectangle = {
			(((((float)(*Position) / Nodes) * Width) + X) * Settings.Screen_Size) - (float)(Caption_Surface->w * 0.5),
			(float)(Y + 10) * Settings.Screen_Size,
			(float)(Caption_Surface->w),
			(float)(Caption_Surface->h)
		};
		SDL_Texture* Caption_Texture = SDL_GenerateTextureFromSurface(Core.Renderer, Caption_Surface);
		Render_Texture(Caption_Texture, &Caption_Rectangle);
		SDL_DestroySurface(Caption_Surface);
		free_texture(Caption_Texture);
	}
}