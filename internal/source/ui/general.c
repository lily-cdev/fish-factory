#include <ui.h>

void Render_Toolbar() {
	if (Interface.Tool != T_Building) {
		return;
	}
	if (!Interface.Item) {
		Interface.Item = Get_Machine("heavy_pipe");
	}
	char Machine_Text[64];
	char Price_Query[64];
	Abbreviate_Number(Interface.Queried_Price, Price_Query, sizeof(Price_Query));
	snprintf(Machine_Text, sizeof(Machine_Text), "%s | %sLA", Interface.Item->Name, Price_Query);
	SDL_Texture* Machine_Texture = Render_Text(F_Subtext, Machine_Text, Colors.Abyss_Black);
	float Y = scale_f((Interface.Bar_Up) ? 265.0f : 290.0f);
	float Height = TTF_GetFontHeight(Fonts.Faces[F_Subtext]) + scale_f(18.0f);
	float Padding = scale_f(16.0f);
	float Root_X = scale_f(312.0f) - (Machine_Texture->w * 0.5f);
	float Root_Width = Machine_Texture->w + Padding;
	SDL_FRect Machine_Rectangle = { Root_X, Y, Root_Width, Height };
	Set_Renderer_Color(Colors.Dark_Grey);
	SDL_RenderFillRect(Core.Renderer, &Machine_Rectangle);
	Machine_Rectangle = Inline_Rect(Machine_Rectangle, 4);
	Set_Renderer_Color(Colors.Light_Grey);
	SDL_RenderFillRect(Core.Renderer, &Machine_Rectangle);
	Clear_Renderer();
	Machine_Rectangle.x += scale_f(4.0f);
	Machine_Rectangle.y += scale_f(4.0f);
	Machine_Rectangle.w = Machine_Texture->w;
	Machine_Rectangle.h = Machine_Texture->h;
	Render_Texture(Machine_Texture, &Machine_Rectangle);
	free_texture(Machine_Texture);
	if (true) {//tmp
		SDL_Texture* L_Texture = Render_Text(F_Subtext, "<-", Colors.Abyss_Black);
		SDL_Texture* R_Texture = Render_Text(F_Subtext, "->", Colors.Abyss_Black);
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
		Rects.Tile_1x1.x = scale_f((Column * LDE_TILESIZE) - Core.Camera.X);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = scale_f((Row * LDE_TILESIZE) - Core.Camera.Y);
			Machine_Ptr Machine = Visual_To_Machine(Data.Visual_Grid[Column][Row]);
			if (!Machine) {
				return;
			}
			if (!Detect_Mouse_Collision(Rects.Tile_1x1)) {
				continue;
			}
			if (Data.Visual_Grid[Column][Row] == 0 || !Machine->Quirks[Q_Interactable]) {
				return;
			}
			char Subcore[64];
			char Sub2core[64];
			strncpy(Sub2core, SDL_GetKeyName(Keybinds.Keybind_List[10]), sizeof(Sub2core));
			for (int C1 = 0; C1 < strlen(Sub2core); C1++) {
				Sub2core[C1] = (char)(tolower(Sub2core[C1]));
			}
			snprintf(Subcore, sizeof(Subcore), "interact - (\"%s\")", Sub2core);
			SDL_Texture* Carrier = Render_Text(F_Halftext, Subcore, Colors.Cherry_Blossom);
			SDL_FRect Carrying_Rectangle = {
				Core.Screenhalfsize.X - (Carrier->w * 0.5), Core.Screenhalfsize.X, (float)Carrier->w, (float)Carrier->h
			};
			Render_Box((Point){ (Carrying_Rectangle.x / Settings.Scalar) - 4, (Carrying_Rectangle.y / Settings.Scalar) - 4 },
				(Carrying_Rectangle.w / Settings.Scalar) + 8, (Carrying_Rectangle.h / Settings.Scalar) + 8, Colors.Light_Grey,
				Colors.Dark_Grey);
			Render_Texture(Carrier, &Carrying_Rectangle);
			free_texture(Carrier);
			return;
		}
	}
}

void Render_Interaction() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rects.Tile_1x1.x = scale_f((Column * LDE_TILESIZE) - Core.Camera.X);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rects.Tile_1x1.y = scale_f((Row * LDE_TILESIZE) - Core.Camera.Y);
			if (Detect_Mouse_Collision(Rects.Tile_1x1)) {
				Machine_Ptr Machine = Visual_To_Machine(Data.Visual_Grid[Column][Row]);
				if (!(*Machine).Quirks[Q_Interactable]) {
					return;
				}
				if (stricmp((*Machine).Index, "signal_tower")) {
					Interface.Prompt_Identifier = P_Transmitter;
				} else if (stricmp((*Machine).Index, "spawning_controller")) {
					Interface.Prompt_Identifier = P_Spawning_Pool;
				} else if (stricmp((*Machine).Index, "sub_dock")) {
					Interface.Prompt_Identifier = P_Dock;
				} else if (stricmp((*Machine).Index, "hx")) {
					Interface.Prompt_Identifier = P_Exchanger;
				} else if (stricmp((*Machine).Index, "money_cheat")) {
					Interface.Prompt_Identifier = P_Money_Generator;
					Interface.Slider_Positions[8] = Data.Settings_Grid[pt(Interface.Tile)][3];
				} else if (stricmp((*Machine).Index, "fluid_cheat")) {
					Interface.Prompt_Identifier = P_Fluid_Generator;
					Interface.Slider_Positions[9] = Data.Settings_Grid[pt(Interface.Tile)][3];
					Interface.Slider_Positions[10] = (int)(Data.Settings_Grid[pt(Interface.Tile)][4] * 0.2f);
					for (int C1 = 0; C1 < LDE_VALVE300LENGTH; C1++) {
						if (Data.Settings_Grid[pt(Interface.Tile)][5] == Interface.Valve300_Postions[C1]) {
							Interface.Slider_Positions[11] = C1;
							break;
						}
					}
				} else if (stricmp((*Machine).Index, "turbine_input")) {
					Interface.Prompt_Identifier = P_Turbine;
				} else if (stricmp((*Machine).Index, "power_cheat")) {
					Interface.Prompt_Identifier = P_Power_Generator;
				}
				Interface.Building = false;
				Interface.Tile = (Point){ Column, Row };
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
		for (int C1 = 0; C1 < (int)floorf(Interface.Effects[E_Radiation]); C1++) {
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
	if (!Interface.Item) {
		Interface.Item = Get_Machine("heavy_pipe");
	}
	Point Size;
	ID_To_Size(Interface.Item, Interface.Rotation, &Size.X, &Size.Y);
	int Max = scale(max(Size.X, Size.Y) * LDE_TILESIZE);
	free_texture(Cache.Blueprint_Cache);
	Cache.Blueprint_Cache = New_Texture(Max, Max);
	SDL_SetTextureBlendMode(Cache.Blueprint_Cache, SDL_BLENDMODE_BLEND);
	SDL_Texture* Backing = New_Texture(scale(Size.X * LDE_TILESIZE), scale(Size.Y * LDE_TILESIZE));
	SDL_SetTextureBlendMode(Backing, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core.Renderer, Backing);
	for (int X = 0; X < Size.X; X++) {
		for (int Y = 0; Y < Size.Y; Y++) {
			SDL_FRect Pasting_Rectangle = Rects.Tile_1x1;
			Pasting_Rectangle.x = scale_f(X * LDE_TILESIZE);
			Pasting_Rectangle.y = scale_f(Y * LDE_TILESIZE);
			Render_Texture(Textures.Tile_Texture, &Pasting_Rectangle);
		}
	}
	SDL_SetRenderTarget(Core.Renderer, Cache.Blueprint_Cache);
	Render_Texture(Backing, NULL);
	free_texture(Backing);
	int Rotation = Interface.Rotation * 90;
	if (Interface.Item->Quirks[Q_Non_Rotatable]) {
		Rotation = 0;
	}
	SDL_FPoint Centerpoint = { Max * 0.5f, Max * 0.5f };
	SDL_RenderTextureRotated(Core.Renderer, Interface.Item->Icon, NULL, NULL, Rotation, &Centerpoint, SDL_FLIP_NONE);
	SDL_SetRenderTarget(Core.Renderer, NULL);
	SDL_SetTextureAlphaMod(Cache.Blueprint_Cache, 190);
}

void Cache_Price() {
	Interface.Queried_Price = (Interface.Item) ? (int)(Interface.Item->Price * 1.1f) + Interface.Item->Fee + 1 : 0;
}

void Set_Engagement(Parameter Engagement, Parameter Unused) {
	Interface.Engagement = (Interface.Engagement == 0) ? Engagement.Integer : 0;
}

void Render_Slider(char Labels[256][32], int Engagement, int Nodes, int* Position, Point Pos, int Width, SDL_Color Primary,
	SDL_Color Secondary, bool Text_Visible) {
	bool Active = false;
	SDL_FRect Background_Rectangle = {
		scale_f(Pos.X),
		scale_f(Pos.Y - 3.0f),
		scale_f(Width),
		scale_f(6.0f)
	};
	if (Interface.Engagement == Engagement) {
		Active = true;
		int Separators[512];
		for (int C1 = 0; C1 < Nodes; C1++) {
			Separators[C1] = scale((((float)C1 / Nodes) * Width) + (Width / (Nodes * 2.0f)) + Pos.X);
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
		scale_f((((float)(*Position) / Nodes) * Width) + Pos.X - 6.0f),
		scale_f(Pos.Y - 6.0f),
		scale_f(12.0f),
		scale_f(12.0f)
	};
	if (Detect_Mouse_Collision(Node_Rectangle)) {
		UI_Link Link = { Set_Engagement, .Param.Integer = Engagement };
		Interface.UI_Query = Link;
		Set_Renderer_Color(Secondary);
	}
	SDL_RenderFillRect(Core.Renderer, &Node_Rectangle);
	Clear_Renderer();
	if (Text_Visible) {
		SDL_Texture* Caption_Texture = Render_Text(F_Subtext, Labels[*Position], Primary);
		SDL_FRect Caption_Rectangle = {
			scale_f((((float)(*Position) / Nodes) * Width) + Pos.X) - (Caption_Texture->w * 0.5f),
			scale_f(Pos.Y + 10.0f),
			(float)Caption_Texture->w,
			(float)Caption_Texture->h
		};
		Render_Texture(Caption_Texture, &Caption_Rectangle);
		free_texture(Caption_Texture);
	}
}