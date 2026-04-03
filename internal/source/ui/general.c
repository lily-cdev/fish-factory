#include <ui.h>

void Render_Toolbar() {
	if (Interface.Tool == T_Building) {
		char Machine_Text[64];
		char Price_Query[64];
		Abbreviate_Number(Interface.Queried_Price, Price_Query, sizeof(Price_Query));
		snprintf(Machine_Text, sizeof(Machine_Text), "%s | %sLA", Metadata.Names[Interface.Item - 1], Price_Query);
		SDL_Texture* Machine_Texture = Render_Text(Fonts.Subtext_Font, Machine_Text, Colors.Abyss_Black);
		float Y = ((Interface.Bar_Up) ? 265.0f : 290.0f) * Settings.Scalar;
		float Height = TTF_GetFontHeight(Fonts.Subtext_Font) + (Settings.Scalar * 18.0f);
		float Padding = Settings.Scalar * 16.0f;
		float Root_X = (Settings.Scalar * 312.0f) - (Machine_Texture->w * 0.5f);
		float Root_Width = Machine_Texture->w + Padding;
		SDL_FRect Machine_Rectangle = { Root_X, Y, Root_Width, Height };
		Set_Renderer_Color(Colors.Dark_Grey);
		SDL_RenderFillRect(Core.Renderer, &Machine_Rectangle);
		Machine_Rectangle = Inline_Rect(Machine_Rectangle, 4);
		Set_Renderer_Color(Colors.Light_Grey);
		SDL_RenderFillRect(Core.Renderer, &Machine_Rectangle);
		Clear_Renderer();
		Machine_Rectangle.x += (Settings.Scalar * 4);
		Machine_Rectangle.y += (Settings.Scalar * 4);
		Machine_Rectangle.w = Machine_Texture->w;
		Machine_Rectangle.h = Machine_Texture->h;
		Render_Texture(Machine_Texture, &Machine_Rectangle);
		free_texture(Machine_Texture);
		if (true) {//tmp
			SDL_Texture* L_Texture = Render_Text(Fonts.Subtext_Font, "<-", Colors.Abyss_Black);
			SDL_Texture* R_Texture = Render_Text(Fonts.Subtext_Font, "->", Colors.Abyss_Black);
			float Width = L_Texture->w + Padding;
			SDL_FRect L_Rect = {
				Root_X - Width,
				Y,
				Width,
				Height
			};
			SDL_FRect R_Rect = {
				Root_X + Root_Width,
				Y,
				Width,
				Height
			};
			Set_Renderer_Color(Colors.Dark_Grey);
			SDL_RenderFillRect(Core.Renderer, &L_Rect);
			SDL_RenderFillRect(Core.Renderer, &R_Rect);
			L_Rect = Inline_Rect(L_Rect, 4);
			R_Rect = Inline_Rect(R_Rect, 4);
			Set_Renderer_Color(Colors.Light_Grey);
			SDL_RenderFillRect(Core.Renderer, &L_Rect);
			SDL_RenderFillRect(Core.Renderer, &R_Rect);
			Clear_Renderer();
			Render_Texture(L_Texture, &L_Rect);
			Render_Texture(R_Texture, &R_Rect);
			free_texture(L_Texture);
			free_texture(R_Texture);
		}
	}
}

void Verify_Settings() {
	bool Keybinds_Altered = false;
	for (int C1 = 0; C1 < LDE_KEYBINDS; C1++) {
		if (Keybinds.Keybind_Settings[C1] != Keybinds.Keybind_List[C1]) {
			Keybinds_Altered = true;
			break;
		}
	}
	if (Settings.Scalar != Interface.Slider_Positions[0] + 1 || Keybinds_Altered || (int)(Settings.AA_Temporary) !=
		Settings.Anti_Aliasing || (int)(Settings.VS_Temporary) != Settings.VSync || Settings.Raw_FPS !=
		Interface.Slider_Positions[4] || Settings.Volume != Interface.Slider_Positions[5] || Interface.Slider_Positions[6] !=
		Settings.Fullscreen) {
		Render_Button(&Textures.Apply, &Rects.Apply, (UI_Link){ Apply_Configs }, Colors.Cherry_Blossom);
		Render_Button(&Textures.Cancel, &Rects.Cancel, (UI_Link){ Clear_Configs }, Colors.Cherry_Blossom);
	}
}

void Render_Tile_Prompts() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Scalar);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Scalar);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				for (int C1 = 0; C1 < intlen(Metadata.Quirk_Positions[Q_Interactable]); C1++) {
					if (Visual_To_ID(Data.Visual_Grid[Column][Row]) == Metadata.Quirk_Positions[Q_Interactable][C1]) {
						char Subcore[64];
						char Sub2core[64];
						strncpy(Sub2core, SDL_GetKeyName(Keybinds.Keybind_List[10]), sizeof(Sub2core));
						for (int C1 = 0; C1 < strlen(Sub2core); C1++) {
							Sub2core[C1] = (char)(tolower(Sub2core[C1]));
						}
						snprintf(Subcore, sizeof(Subcore), "interact - (\"%s\")", Sub2core);
						SDL_Texture* Carrier = Render_Text(Fonts.Halftext_Font, Subcore, Colors.Cherry_Blossom);
						SDL_FRect Carrying_Rectangle = {
							Core.Screenhalfsize.X - (Carrier->w * 0.5),
							Core.Screenhalfsize.X,
							(float)Carrier->w,
							(float)Carrier->h
						};
						Render_Box((Point){ (Carrying_Rectangle.x / Settings.Scalar) - 4,
							(Carrying_Rectangle.y / Settings.Scalar) - 4 },
							(Carrying_Rectangle.w / Settings.Scalar) + 8,
							(Carrying_Rectangle.h / Settings.Scalar) + 8,
							Colors.Light_Grey, Colors.Dark_Grey);
						Render_Texture(Carrier, &Carrying_Rectangle);
						free_texture(Carrier);
					}
				}
			}
		}
	}
}

void Render_Interaction() {
	int Indexes[8] = { P_Transmitter, P_Spawning_Pool, P_Dock, P_Exchanger, P_Money_Generator, P_Fluid_Generator, P_Turbine,
		P_Power_Generator };
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = (int)(((Column * LDE_TILESIZE) - Core.Camera.X) * Settings.Scalar);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = (int)(((Row * LDE_TILESIZE) - Core.Camera.Y) * Settings.Scalar);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				for (int C1 = 0; C1 < intlen(Metadata.Quirk_Positions[Q_Interactable]); C1++) {
					if (Visual_To_ID(Data.Visual_Grid[Column][Row]) == Metadata.Quirk_Positions[Q_Interactable][C1]) {
						Interface.Prompt_Identifier = Indexes[C1];
						Interface.Building = false;
						Interface.Tile.X = Column;
						Interface.Tile.Y = Row;
						switch (Visual_To_ID(Data.Visual_Grid[Column][Row])) {
						case Money_Generator:
							Interface.Slider_Positions[8] = Data.Settings_Grid[Interface.Tile.X][Interface.Tile.Y][3];
							break;
						case Fluid_Generator:
							Interface.Slider_Positions[9] = Data.Settings_Grid[Interface.Tile.X][Interface.Tile.Y][3];
							Interface.Slider_Positions[10] = (int)(Data.Settings_Grid[Interface.Tile.X][Interface.Tile.Y][
								4] * 0.2f);
							for (int C1 = 0; C1 < LDE_VALVE300LENGTH; C1++) {
								if (Data.Settings_Grid[Interface.Tile.X][Interface.Tile.Y][5] == Interface.Valve300_Postions[
									C1]) {
									Interface.Slider_Positions[11] = C1;
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
		int Width = (int)Core.Screensize.X;
		int Height = (int)Core.Screensize.Y;
		for (int C1 = 0; C1 < floor(Interface.Effects[E_Radiation]); C1++) {
			Tick_State();
			int X = Core.State % Width;
			Tick_State();
			int Y = Core.State % Height;
			for (int Offset_X = -1; Offset_X <= 1; Offset_X++) {
				SDL_RenderPoint(Core.Renderer, (float)(clamp_c(X + Offset_X, 0, Width)), (float)Y);
			}
			for (int Offset_Y = -1; Offset_Y <= 1; Offset_Y++) {
				SDL_RenderPoint(Core.Renderer, (float)X, (float)(clamp_c(Y + Offset_Y, 0, Height)));
			}
		}
		Clear_Renderer();
		//play geiger tick
	}
}

void Cache_Blueprint() {
	int Width, Height;
	ID_To_Size(Interface.Item - 1, Interface.Rotation, &Width, &Height);
	int Max = (Width > Height ? Width : Height) * Settings.Scalar * LDE_TILESIZE;
	free_texture(Cache.Blueprint_Cache);
	Cache.Blueprint_Cache = New_Texture(Core.Renderer, Max, Max);
	SDL_SetTextureBlendMode(Cache.Blueprint_Cache, SDL_BLENDMODE_BLEND);
	SDL_Texture* Backing = New_Texture(Core.Renderer, Width * Settings.Scalar * LDE_TILESIZE, Height *
		Settings.Scalar * LDE_TILESIZE);
	SDL_SetTextureBlendMode(Backing, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Backing);
	for (int X = 0; X < Width; X++) {
		for (int Y = 0; Y < Height; Y++) {
			SDL_FRect Pasting_Rectangle = Rects.Tile_1x1;
			Pasting_Rectangle.x = X * Settings.Scalar * LDE_TILESIZE;
			Pasting_Rectangle.y = Y * Settings.Scalar * LDE_TILESIZE;
			Render_Texture(Textures.Tile_Texture, &Pasting_Rectangle);
		}
	}
	SDL_SetRenderTarget(Core.Renderer, Cache.Blueprint_Cache);
	Render_Texture(Backing, NULL);
	free_texture(Backing);
	int Rotation = Interface.Rotation * 90;
	for (int C1 = 0; C1 < intlen(Metadata.Quirk_Positions[Q_Non_Rotatable]); C1++) {
		if (Metadata.Quirk_Positions[Q_Non_Rotatable][C1] == Interface.Item - 1) {
			Rotation = 0;
		}
	}
	SDL_FPoint Centerpoint = { Max * 0.5f, Max * 0.5f };
	SDL_RenderTextureRotated(Core.Renderer, Metadata.Machines[Interface.Item - 1].Icon, NULL, NULL, Rotation, &Centerpoint,
		SDL_FLIP_NONE);
	SDL_SetRenderTarget(Core.Renderer, NULL);
	SDL_SetTextureAlphaMod(Cache.Blueprint_Cache, 190);
}

void Cache_Price() {
	Interface.Queried_Price = (int)((Metadata.Machines[Interface.Item - 1].Price * 1.1f)) + Metadata.Machines[
		Interface.Item - 1].Tax + 1;
}

void Set_Engagement(Parameter Engagement, Parameter Unused) {
	Interface.Engagement = (Interface.Engagement == 0) ? Engagement.Integer : 0;
}

void Render_Slider(char Labels[256][32], int Engagement, int Nodes, int* Position, Point Pos, int Width, SDL_Color Primary,
	SDL_Color Secondary, bool Text_Visible) {
	bool Active = false;
	SDL_FRect Background_Rectangle = {
		(float)(Pos.X * Settings.Scalar),
		(float)(Pos.Y - 3) * Settings.Scalar,
		(float)(Width * Settings.Scalar),
		Settings.Scalar * 6.0f
	};
	if (Interface.Engagement == Engagement) {
		Active = true;
		int Separators[512];
		for (int C1 = 0; C1 < Nodes; C1++) {
			Separators[C1] = (int)(((((float)C1 / Nodes) * Width) + (Width / (Nodes * 2)) + Pos.X)) * Settings.Scalar;
		}
		Separators[Nodes] = LDE_TERMINATOR;
		for (int C1 = 0; C1 < Nodes; C1++) {
			if (Core.Debug_Mode) {
				SDL_RenderLine(Core.Renderer, (float)(Separators[C1]), 0, (float)(Separators[C1]), Core.Screensize.Y);
			}
			if (Core.Mouse.X < Separators[0]) {
				*Position = 0;
			} else if (Core.Mouse.X >= Separators[Nodes - 1]) {
				*Position = Nodes;
			} else if (Core.Mouse.X >= Separators[C1] && Core.Mouse.X < Separators[C1 + 1]) {
				*Position = C1 + 1;
			}
		}
	}
	Set_Renderer_Color(Primary);
	SDL_RenderFillRect(Core.Renderer, &Background_Rectangle);
	if (Active) {
		Set_Renderer_Color(Secondary);
	}
	SDL_FRect Node_Rectangle = {
		(float)((((float)(*Position) / Nodes) * Width) + Pos.X - 6) * Settings.Scalar,
		(float)(Pos.Y - 6.0f) * Settings.Scalar,
		Settings.Scalar * 12.0f,
		Settings.Scalar * 12.0f
	};
	if (Detect_Mouse_Collision(Node_Rectangle)) {
		UI_Link Link = { Set_Engagement, .Param.Integer = Engagement };
		Interface.UI_Query = Link;
		Set_Renderer_Color(Secondary);
	}
	SDL_RenderFillRect(Core.Renderer, &Node_Rectangle);
	Clear_Renderer();
	if (Text_Visible) {
		SDL_Texture* Caption_Texture = Render_Text(Fonts.Subtext_Font, Labels[*Position], Primary);
		SDL_FRect Caption_Rectangle = {
			(((((float)(*Position) / Nodes) * Width) + Pos.X) * Settings.Scalar) - (float)(Caption_Texture->w * 0.5),
			(float)(Pos.Y + 10.0f) * Settings.Scalar,
			(float)Caption_Texture->w,
			(float)Caption_Texture->h
		};
		Render_Texture(Caption_Texture, &Caption_Rectangle);
		free_texture(Caption_Texture);
	}
}