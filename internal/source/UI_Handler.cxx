#include <Core.h>
#include <Preloader.h>
#include <Items.h>
#include <UI_Handler.h>
#include <Grid_Handler.h>
#include <Data_Handler.h>
#include <Terminal_Handler.h>

void Render_Blueprint(int Size_X, int Size_Y) {
	SDL_FRect Hitbox = { 0, 0, static_cast<float>(Size_X * 40) * Settings_Access.Screen_Size,
		static_cast<float>(Size_Y * 40) * Settings_Access.Screen_Size };
	SDL_FRect Invisible_Hitbox = { 0, 0, 40.0f * Settings_Access.Screen_Size, 40.0f * Settings_Access.Screen_Size };
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Hitbox.x = static_cast<int>((Column * 40) - UI_Access.Camera_X) * Settings_Access.Screen_Size;
		Invisible_Hitbox.x = static_cast<int>((Column * 40) - UI_Access.Camera_X) * Settings_Access.Screen_Size;
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Hitbox.y = static_cast<int>((Row * 40) - UI_Access.Camera_Y) * Settings_Access.Screen_Size;
			Invisible_Hitbox.y = static_cast<int>((Row * 40) - UI_Access.Camera_Y) * Settings_Access.Screen_Size;
			if (Detect_Mouse_Collision(Invisible_Hitbox)) {
				if ((Hitbox.x + Hitbox.w <= ((LDE_GRIDSIZE * 40) - UI_Access.Camera_X) * Settings_Access.Screen_Size &&
					Hitbox.y + Hitbox.h <= ((LDE_GRIDSIZE * 40) - UI_Access.Camera_Y) * Settings_Access.Screen_Size)
					|| (Size_X != 2 && Size_Y != 2)) {
					bool Placeable = Check_Clearance(Column, Row, Size_X, Size_Y);
					if ((UI_Access.Placing_Item == Command_Platform + 1 && Data_Access.CMD_Placed) ||
						(UI_Access.Placing_Item == Submarine_Dock + 1 && Row != 0)) {
						Placeable = false;
					}
					if (Placeable) {
						Render_Outline(Hitbox, Colors_Access.Pure_White);
					} else {
						SDL_SetTextureColorMod(Cache_Access.Blueprint_Cache, Colors_Access.Hostile_Red.r,
							Colors_Access.Hostile_Red.g, Colors_Access.Hostile_Red.b);
						Render_Outline(Hitbox, Colors_Access.Hostile_Red);
					}
					SDL_RenderTexture(Core_Access.Application_Renderer, Cache_Access.Blueprint_Cache,
						NULL, &Hitbox);
					SDL_SetTextureColorMod(Cache_Access.Blueprint_Cache, 255, 255, 255);
					return;
				}
			}
		}
	}
}

void Render_Sidebar(SDL_Texture* Texture, SDL_FRect Rectangle, int Selection) {
	if (Detect_Mouse_Collision(Rectangle)) {
		Rectangle.x = (640 * Settings_Access.Screen_Size) - Rectangle.w;
		UI_Access.UI_Selection = Selection;
	} else {
		Rectangle.x = (654 * Settings_Access.Screen_Size) - Rectangle.w;
	}
	SDL_RenderTexture(Core_Access.Application_Renderer, Texture, NULL, &Rectangle);
}

void Render_Game_UI() {
	if (UI_Access.Tool == LDE_INVALID && UI_Access.Prompt_Identifier == LDE_INVALID) {
		Render_Sidebar(Textures_Access.Help_Sidebutton, Rectangles_Access.Help, 1);
		Render_Sidebar(Textures_Access.Save_Sidebutton, Rectangles_Access.Save, 2);
		Render_Sidebar(Textures_Access.Recipe_Sidebutton, Rectangles_Access.Recipe, 3);
		Render_Sidebar(Textures_Access.Exit_Sidebutton, Rectangles_Access.Exit, 4);
	}
	std::vector<std::string> Queried_Data_Fragments = { };
	int Hour = Data_Access.Time / 60;
	int Minute =  Data_Access.Time % 60;
	bool Afternoon = false;
	if (Hour > 11) {
		Hour -= 12;
		Afternoon = true;
	}
	if (Hour == 0) {
		Hour = 12;
	}
	std::string Time;
	if (Hour < 10) {
		Time = "0" + std::to_string(Hour) + ":";
	} else {
		Time = std::to_string(Hour) + ":";
	}
	if (Minute < 10) {
		Time += "0" + std::to_string(Minute);
	} else {
		Time += std::to_string(Minute);
	}
	if (Afternoon) {
		Time += "PM";
	} else {
		Time += "AM";
	}
	Render_Dynamic_Text(Fonts_Access.Halftext_Font, Abbreviate_Number(Data_Access.Funds) + "LA", Colors_Access.Abyss_Black, 10, 30);
	Render_Dynamic_Text(Fonts_Access.Halftext_Font, Time + ", " + Metadata_Access.Days[Data_Access.Day] + "day",
		Colors_Access.Abyss_Black, 10, 50);
	if (UI_Access.Tool == 2) {
		std::vector<double> Content_Vector = Get_Grid_Data(Data_Access.Data_Grid);
		Item_Stack Returned_Item = Get_Item_Stack_Data();
		if (Returned_Item.Identifier != LDE_INVALID) {
			Queried_Data_Fragments.push_back("Item: " + Returned_Item.Display_Name);
			Queried_Data_Fragments.push_back(Truncate(Returned_Item.Temperature, 0) + "°F");
			double Pressure = Calculate_Pressure(Returned_Item.Temperature, Returned_Item.Boiling_Point,
				Returned_Item.Vaporisation_Enthalpy);
			int Multiplier = 1;
			if (Pressure == LDE_INVALID) {
				Queried_Data_Fragments.push_back("gas");
				Multiplier = 10;
			} else {
				if (Pressure < 1) {
					Pressure = 1;
				}
				Queried_Data_Fragments.push_back(Abbreviate_Number(Pressure) + " bar liquid");
			}
			if (Content_Vector[1] != 0) {
				Queried_Data_Fragments.push_back(Truncate(Content_Vector[0] * Multiplier, Get_Depth(Content_Vector[1] *
					Multiplier)) + " / " + Abbreviate_Number(Content_Vector[1] * Multiplier) + "L.");
			}
		} else {
			if (Content_Vector[1] != 0) {
				Queried_Data_Fragments.push_back(Truncate(0, 0) + " / " + Abbreviate_Number(Content_Vector[1]) + "L.");
			}
		}
		if (Content_Vector[3] != 0) {
			Queried_Data_Fragments.push_back(Truncate(Content_Vector[2], Get_Depth(Content_Vector[3])) + " / " +
				Abbreviate_Number(Content_Vector[3]) + "J.");
		}
		if (Queried_Data_Fragments.size() <= 0) {
			Queried_Data_Fragments.push_back("No data");
		}
		int Maximum_Width = 0;
		std::vector<SDL_Texture*> Fragment_Textures = { };
		std::vector<SDL_FRect> Fragment_Rectangles = { };
		for (int Counter = 0; Counter < Queried_Data_Fragments.size(); Counter++) {
			SDL_Surface* Fragment_Surface = TTF_RenderText_Blended(Fonts_Access.Subtext_Font,
				Queried_Data_Fragments[Counter].c_str(), Queried_Data_Fragments
				[Counter].size(), Colors_Access.Abyss_Black);
			if (Fragment_Surface->w > Maximum_Width) {
				Maximum_Width = Fragment_Surface->w;
			}
			SDL_Texture* Fragment_Texture = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Fragment_Surface);
			Fragment_Textures.push_back(Fragment_Texture);
			Fragment_Rectangles.push_back({ static_cast<float>(630 * Settings_Access.Screen_Size) -
				Fragment_Surface->w, static_cast<float>(10 + (Counter * 20)) *
				Settings_Access.Screen_Size, static_cast<float>(Fragment_Surface->w),
				static_cast<float>(Fragment_Surface->h) });
			SDL_DestroySurface(Fragment_Surface);
		}
		int Total_Height = Fragment_Rectangles[Fragment_Rectangles.size() - 1].y + Fragment_Rectangles[Fragment_Rectangles.size() - 1].h;
		Set_Renderer_Color(Colors_Access.Dark_Grey);
		SDL_FRect Background_Rectangle = { static_cast<float>(615 * Settings_Access.Screen_Size) -
			Maximum_Width, 0, Maximum_Width + static_cast<float>(25 * Settings_Access.Screen_Size),
			Total_Height + static_cast<float>(15 * Settings_Access.Screen_Size) };
		SDL_RenderFillRect(Core_Access.Application_Renderer, &Background_Rectangle);
		Set_Renderer_Color(Colors_Access.Light_Grey);
		Background_Rectangle = { static_cast<float>(620 * Settings_Access.Screen_Size) - Maximum_Width,
			0, Maximum_Width + static_cast<float>(20 * Settings_Access.Screen_Size), Total_Height +
			static_cast<float>(10 * Settings_Access.Screen_Size) };
		SDL_RenderFillRect(Core_Access.Application_Renderer, &Background_Rectangle);
		Clear_Renderer();
		for (int Counter = 0; Counter < Fragment_Textures.size(); Counter++) {
			SDL_RenderTexture(Core_Access.Application_Renderer, Fragment_Textures[Counter], NULL, &Fragment_Rectangles[Counter]);
			SDL_DestroyTexture(Fragment_Textures[Counter]);
		}
		Fragment_Textures.clear();
		Fragment_Rectangles.clear();
	}
	if (UI_Access.Save_Frames > 0) {
		SDL_Color Fading_Color = Colors_Access.Cherry_Blossom;
		Fading_Color.a = static_cast<Uint8>(ceil(((double) UI_Access.Save_Frames / (UI_Access.Frame_Rate * 2)) * 255));
		Render_Dynamic_Text(Fonts_Access.Subtext_Font, "Data saved!", Fading_Color, LDE_INVALID, 300);
		UI_Access.Save_Frames--;
	}
}

void Render_Saveloader() {
	SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Saveloader,
		NULL, &Rectangles_Access.Saveloader);
	for (int Counter = 0; Counter < 4; Counter++) {
		if (Core_Access.Save_Filesizes[Counter] > 0) {
			Render_Button(Textures_Access.Load.Data[Counter],
				Rectangles_Access.Load.Data[Counter], 6 + Counter);
			Render_Button(Textures_Access.Clear.Data[Counter],
				Rectangles_Access.Clear.Data[Counter], 10 + Counter);
		} else {
			Render_Button(Textures_Access.New.Data[Counter],
				Rectangles_Access.New.Data[Counter], 2 + Counter);
		}
	}
	for (int Counter = 0; Counter < 4; Counter++) {
		std::string Text = "Factory " + std::to_string(Counter + 1) + " (" +
			Abbreviate_Number(Core_Access.Save_Filesizes[Counter]) + "b)";
		Render_Dynamic_Text(Fonts_Access.Subtext_Font, Text.c_str(),
			Colors_Access.Abyss_Black, 40, 160 + (40 * Counter));
	}
}

void Render_Prompts() {
	int X = UI_Access.Target_Tile.X;
	int Y = UI_Access.Target_Tile.Y;
	std::vector<std::vector<std::string>> Parameters;
	std::vector<int> Command_Types;
	int Index;
	switch (UI_Access.Prompt_Identifier) {
	case 0:
		Render_Box(10, 10, 620, 340, Colors_Access.Light_Grey, Colors_Access.Dark_Grey);
		for (int Counter = 0; Counter < 2; Counter++) {
			SDL_RenderTexture(Core_Access.Application_Renderer,
				Textures_Access.Help_Content.Data[Counter],
				NULL, &Rectangles_Access.Help_Content[Counter]);
		}
		Render_Slider(UI_Access.Slider_Texts[3], 1, 2, 1, UI_Access.Slider_Positions[3], 130,
			300, 380, Colors_Access.Abyss_Black, Colors_Access.Cherry_Blossom, true);
		switch (UI_Access.Slider_Positions[3]) {
		case 0:
			Render_Rich_Text(Fonts_Access.Subtext_Font, "[c]Welcome to Fish Factory! This game"
				" is in the alpha phase, so don't expect much.|More gameplay"
				" mechanics and customization options are planned for future updates."
				"| | | |Thank you for playing, and have fun!", 20, 60);
			break;
		case 1:
			Render_Rich_Text(Fonts_Access.Subtext_Font, "[c]Tutorials involve placing items. The space"
				" occupied by the selected tutorial will be marked by a bounding|box. For an optimal"
				" experience, please ensure that the indicated area is free of obstructions.", 20, 60);
			if (Temporary_Access.Tutorial_Step == LDE_INVALID) {
				if (Data_Access.CMD_Placed) {
					for (int Counter = 1; Counter < Textures_Access.Tutorials.Length; Counter++) {
						Rectangles_Access.Tutorial_Hitbox.Data = Rectangles_Access
							.Tutorials.Data[Counter].Data;
						Rectangles_Access.Tutorial_Hitbox.Data[0].y -= 40 * Settings_Access.Screen_Size;
						Rectangles_Access.Tutorial_Hitbox.Data[1].y -= 40 * Settings_Access.Screen_Size;
						Render_Button(Textures_Access.Tutorials.Data[Counter],
							Rectangles_Access.Tutorial_Hitbox, Counter + 3);
					}
				} else {
					Render_Dynamic_Text(Fonts_Access.Subtext_Font, "The Command Platform must be placed"
						" for full tutorial access!", Colors_Access.Abyss_Black, LDE_INVALID, 90);
					Render_Button(Textures_Access.Tutorials.Data[0], Rectangles_Access.Tutorials.Data[0], 3);
				}
			} else {
				Render_Button(Textures_Access.Clear_Tutorial, Rectangles_Access.Clear_Tutorial, 2);
			}
			break;
		case 2:
			Render_Rich_Text(Fonts_Access.Subtext_Font, "The following cheat items are intentionally unbalanced."
				"| |You can use them for troubleshooting, bug-hunting, or just playing around.", 20, 60);
			for (int Counter = 0; Counter < 2; Counter++) {
				Render_Button(Textures_Access.Cheats.Data[Counter],
					Rectangles_Access.Cheats.Data[Counter], Counter + 2);
			}
			break;
		default:
			break;
		}
		break;
	case 1:
		Render_Box(210, 10, 220, 340, Colors_Access.Light_Grey, Colors_Access.Dark_Grey);
		if (UI_Access.Subtab > 0) {
			if (UI_Access.Subtab < 9) {
				int Subcategories = Metadata_Access.Subcategory_Positions[UI_Access.Subtab - 1].size();
				for (int Counter = 0; Counter < Subcategories; Counter++) {
					Render_Button(Textures_Access.Subcategories.Data
						[UI_Access.Subtab - 1].Data[Counter], Rectangles_Access
						.Subcategories.Data[UI_Access.Subtab - 1].Data[Counter],
						Counter + 3);
				}
				for (int Counter = 0; Counter < Metadata_Access.Item_Labels[UI_Access.Subtab - 1].size(); Counter++) {
					Render_Button(Textures_Access.Item_Labels.Data[
						UI_Access.Subtab - 1].Data[Counter], Rectangles_Access
						.Item_Labels.Data[UI_Access.Subtab - 1].Data[Counter],
						Counter + Subcategories + 3);
				}
			} else {
				for (int Counter = 0; Counter < Metadata_Access.Subcontents[
					UI_Access.Subtab - 9].size(); Counter++) {
					Render_Button(Textures_Access.Subcontents.Data[
						UI_Access.Subtab - 9].Data[Counter], Rectangles_Access
						.Subcontents.Data[UI_Access.Subtab - 9].Data[Counter], Counter + 3);
				}
			}
			Render_Box(10, 10, 186, 340, Colors_Access.Light_Grey, Colors_Access.Dark_Grey);
			SDL_FRect Icon_Rectangle = Metadata_Access.Machine_Rectangles[UI_Access.Placing_Item - 1];
			double Multiplier = ((double)120 * Settings_Access.Screen_Size) / Icon_Rectangle.w;
			Icon_Rectangle.w = static_cast<int>(Icon_Rectangle.w * Multiplier);
			Icon_Rectangle.h = static_cast<int>(Icon_Rectangle.h * Multiplier);
			Icon_Rectangle.x = (103 * Settings_Access.Screen_Size) - (Icon_Rectangle.w / 2);
			Icon_Rectangle.y = (24 * Settings_Access.Screen_Size);
			int Offset = (Icon_Rectangle.y + Icon_Rectangle.h) / Settings_Access.Screen_Size;
			Render_Box((Icon_Rectangle.x / Settings_Access.Screen_Size) - 4,
				(Icon_Rectangle.y / Settings_Access.Screen_Size) - 4,
				(Icon_Rectangle.w / Settings_Access.Screen_Size) + 8,
				(Icon_Rectangle.h / Settings_Access.Screen_Size) + 8,
				Colors_Access.Light_Grey, Colors_Access.Dark_Grey);
			SDL_RenderTexture(Core_Access.Application_Renderer, Metadata_Access.Machine_Sprites[UI_Access.Placing_Item - 1],
				NULL, &Icon_Rectangle);
			std::vector<int> Quirk_Stack = { };
			for (int Counter = 0; Counter < 4; Counter++) {
				if (Metadata_Access.Machine_Quirks[UI_Access.Placing_Item - 1][Counter]) {
					Quirk_Stack.push_back(Counter);
				}
			}
			std::vector<SDL_FRect> Label_Rectangles = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
			float Start = static_cast<float>((103 * Settings_Access.Screen_Size) - (((20 * Quirk_Stack.size() *
				Settings_Access.Screen_Size) + (10 * (Quirk_Stack.size() - 1) * Settings_Access.Screen_Size)) / 2));
			for (int Counter = 0; Counter < Quirk_Stack.size(); Counter++) {
				SDL_FRect Quirk_Rectangle = { Start + (30 * Counter * Settings_Access.Screen_Size),
					static_cast<float>(16 + Offset) * Settings_Access.Screen_Size, 20.0f *
					Settings_Access.Screen_Size, 20.0f * Settings_Access.Screen_Size };
				SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
					.Quirk.Data[Quirk_Stack[Counter]], NULL, &Quirk_Rectangle);
				if (Detect_Mouse_Collision(Quirk_Rectangle)) {
					SDL_GetTextureSize(Textures_Access.Quirk_Label.Data[Quirk_Stack[Counter]],
						&Label_Rectangles[Counter].w, &Label_Rectangles[Counter].h);
					Label_Rectangles[Counter].x = Quirk_Rectangle.x + (10 * Settings_Access.Screen_Size) -
						(Label_Rectangles[Counter].w / 2);
					Label_Rectangles[Counter].y = Quirk_Rectangle.y + (24 * Settings_Access.Screen_Size);
				}
			}
			if (Quirk_Stack.size() > 0) {
				Offset += 32;
			}
			SDL_Surface* Name_Surface = TTF_RenderText_Blended(Fonts_Access.Halftext_Font, Metadata_Access.Machine_Names
				[UI_Access.Placing_Item - 1].c_str(), Metadata_Access.Machine_Names[UI_Access.Placing_Item - 1].size(),
				Colors_Access.Abyss_Black);
			SDL_Texture* Name_Texture = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Name_Surface);
			SDL_FRect Name_Rectangle = { static_cast<float>(103 * Settings_Access.Screen_Size) - (Name_Surface->w / 2),
				static_cast<float>(10 + Offset) * Settings_Access.Screen_Size, static_cast<float>(Name_Surface->w),
				static_cast<float>(Name_Surface->h) };
			SDL_RenderTexture(Core_Access.Application_Renderer, Name_Texture, NULL, &Name_Rectangle);
			SDL_DestroySurface(Name_Surface);
			SDL_DestroyTexture(Name_Texture);
			SDL_Surface* Carrying_Surface = TTF_RenderText_Blended_Wrapped(Fonts_Access.Subtext_Font,
				Metadata_Access.Machine_Descriptions[UI_Access.Placing_Item - 1].c_str(),
				Metadata_Access.Machine_Descriptions[UI_Access.Placing_Item - 1].size(),
				Colors_Access.Abyss_Black, 180 * Settings_Access.Screen_Size);
			SDL_FRect Description_Rectangle = { 16.0f * Settings_Access.Screen_Size,
				(40.0f + Offset) * Settings_Access.Screen_Size, static_cast<float>(
				Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
			SDL_Texture* Description_Texture = SDL_GenerateTextureFromSurface(
				Core_Access.Application_Renderer, Carrying_Surface);
			SDL_RenderTexture(Core_Access.Application_Renderer, Description_Texture,
				NULL, &Description_Rectangle);
			SDL_DestroySurface(Carrying_Surface);
			SDL_DestroyTexture(Description_Texture);
			std::string Content = "\"" + Metadata_Access.Machine_Comments[UI_Access.Placing_Item - 1] + "\"";
			Carrying_Surface = TTF_RenderText_Blended_Wrapped(Fonts_Access.Microtext_Font, Content.c_str(),
				Content.size(), Colors_Access.Clean_Grey, 180 * Settings_Access.Screen_Size);
			SDL_FRect Comment_Rectangle = { 16.0f * Settings_Access.Screen_Size, static_cast<float>(
				348 * Settings_Access.Screen_Size) - Carrying_Surface->h, static_cast<float>(Carrying_Surface->w),
				static_cast<float>(Carrying_Surface->h) };
			SDL_Texture* Comment_Texture = SDL_GenerateTextureFromSurface(
				Core_Access.Application_Renderer, Carrying_Surface);
			SDL_RenderTexture(Core_Access.Application_Renderer, Comment_Texture, NULL, &Comment_Rectangle);
			SDL_DestroySurface(Carrying_Surface);
			SDL_DestroyTexture(Comment_Texture);
			for (int Counter = 0; Counter < Quirk_Stack.size(); Counter++) {
				Set_Renderer_Color(Colors_Access.Light_Grey);
				SDL_FRect Temporary_Rectangle = Buffer_Rectangle(Label_Rectangles[Counter], 4, 1);
				SDL_RenderFillRect(Core_Access.Application_Renderer, &Temporary_Rectangle);
				Clear_Renderer();
				SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Quirk_Label
					.Data[Quirk_Stack[Counter]], NULL, &Label_Rectangles[Counter]);
			}
			Render_Box(444, 10, 186, 340, Colors_Access.Light_Grey, Colors_Access.Dark_Grey);
			Render_Dynamic_Text(Fonts_Access.Halftext_Font, "Price Sum:",
				Colors_Access.Abyss_Black, 446, 10);
			Render_Dynamic_Text(Fonts_Access.Subtext_Font, "Base: " +
				std::to_string(Metadata_Access.Machine_Prices
				[UI_Access.Placing_Item - 1]) + "LA", Colors_Access.Abyss_Black, 456, 30);
			Render_Dynamic_Text(Fonts_Access.Subtext_Font, "Tax: " +
				std::to_string(Metadata_Access.Machine_Prices
				[UI_Access.Placing_Item - 1] / 10) + "LA", Colors_Access.Abyss_Black, 456, 50);
			Render_Dynamic_Text(Fonts_Access.Subtext_Font, "Shipping Fee: " +
				std::to_string(Metadata_Access.Machine_Taxes
				[UI_Access.Placing_Item - 1]) + "LA", Colors_Access.Abyss_Black, 456, 70);
			Render_Dynamic_Text(Fonts_Access.Subtext_Font, "Processing Fee: 1LA",
				Colors_Access.Abyss_Black, 456, 90);
			Cache_Price();
			Render_Dynamic_Text(Fonts_Access.Subtext_Font, "Total: " +
				std::to_string(UI_Access.Queried_Price) + "LA",
				Colors_Access.Abyss_Black, 456, 110);
		} else {
			for (int Counter = 0; Counter < Metadata_Access.Categories.size(); Counter++) {
				Render_Button(Textures_Access.Categories.Data[Counter],
					Rectangles_Access.Categories.Data[Counter],	Counter + 3);
			}
		}
		break;
	case 2:
		Render_Box(40, 40, 560, 280, Colors_Access.Light_Grey, Colors_Access.Dark_Grey);
		Render_Dynamic_Text(Fonts_Access.Halftext_Font, Metadata_Access.Days[Data_Access.Day] +
			"day Report", Colors_Access.Abyss_Black, LDE_INVALID, 60);
		Render_Button(Textures_Access.Next_Day, Rectangles_Access.Next_Day, 1);
		break;
	case 3:
		Render_Backing();
		if (Data_Access.Settings_Grid[X][Y][3] > 3) {
			Render_Sidebuttons(Textures_Access.MSP_Buttons, Rectangles_Access.MSP_Buttons);
			Render_Slider(UI_Access.Slider_Texts[1], 1, 2, 9, UI_Access.Slider_Positions[1], 475, 210, 110,
				Colors_Access.Cherry_Blossom, Colors_Access.Pure_White, false);
			if (UI_Access.Engagement == 0) {
				Parameters = {
					{ "tank_info" },
					{ "fish_info" },
					{ "fill_pool" },
					{ "drain_pool" }
				};
				Command_Types = {
					Get_Data,
					Get_Data,
					Execute,
					Execute
				};
				Process_Commands(Command_Types, Parameters);
			} else {
				UI_Access.Terminal_Entry = Return_Command(Execute, { "set_fish", UI_Access.Slider_Texts[1]
					[UI_Access.Slider_Positions[1]] });
				Tick_Input(1, true);
			}
			Render_Necessities("modular_spawning_pool", "pool");
		} else if (Data_Access.Settings_Grid[X][Y][3] == -6) {
			Print_Fatal_Error(Too_Many_Inputs);
		} else if (Data_Access.Settings_Grid[X][Y][3] == -5) {
			Print_Fatal_Error(Missing_Input);
		} else if (Data_Access.Settings_Grid[X][Y][3] == -4) {
			Print_Fatal_Error(Too_Many_Outputs);
		} else if (Data_Access.Settings_Grid[X][Y][3] == -3) {
			Print_Fatal_Error(Missing_Output);
		} else if (Data_Access.Settings_Grid[X][Y][3] == -2) {
			Print_Fatal_Error(Too_Many_Controllers);
		} else if (Data_Access.Settings_Grid[X][Y][3] < 4) {
			Print_Fatal_Error(Missing_Pool);					
		}
		break;
	case 4:
		Render_Backing();
		Render_Sidebuttons(Textures_Access.TT_Buttons.Data[Temporary_Access.Dialogue_Position],
			Rectangles_Access.TT_Buttons.Data[Temporary_Access.Dialogue_Position]);
		Parameters = Metadata_Access.TT_Parameters[Temporary_Access.Dialogue_Position];
		Command_Types = Metadata_Access.TT_Types[Temporary_Access.Dialogue_Position];
		Process_Commands(Command_Types, Parameters);
		Render_Necessities("transmitter", "tower");
		break;
	case 5:
		Render_Backing();
		Render_Sidebuttons(Textures_Access.SD_Buttons, Rectangles_Access.SD_Buttons);
		Parameters = {
			{ "link" },
			{ "manifest" },
			{ "drain_silo", "1" },
			{ "drain_silo", "2" },
		};
		Command_Types = {
			Execute,
			Get_Data,
			Execute,
			Execute
		};
		Process_Commands(Command_Types, Parameters);
		Render_Necessities("submarine_dock", "dock");
		break;
	case 6:
		Render_Backing();
		Render_Sidebuttons(Textures_Access.HX_Buttons, Rectangles_Access.HX_Buttons);
		Render_Slider(UI_Access.Slider_Texts[13], 3, UI_Access.Valve300_Postions.size() - 1, 6,
			UI_Access.Slider_Positions[13], 475, 190, 110, Colors_Access.Cherry_Blossom,
			Colors_Access.Pure_White, false);
		Render_Slider(UI_Access.Slider_Texts[7], 2, UI_Access.Valve300_Postions.size() - 1, 7,
			UI_Access.Slider_Positions[7], 475, 150, 110, Colors_Access.Cherry_Blossom,
			Colors_Access.Pure_White, false);
		if (UI_Access.Engagement == 0) {
			Parameters = {
				{ "diagnostics" }
			};
			Command_Types = {
				Get_Data
			};
			Process_Commands(Command_Types, Parameters);
		} else if (UI_Access.Engagement == 2) {
			UI_Access.Terminal_Entry = Return_Command(Execute, { "set_primary_valve", std::to_string(
				static_cast<int>(UI_Access.Valve300_Postions[UI_Access.Slider_Positions[7]])) });
			Tick_Input(2, true);
		} else {
			UI_Access.Terminal_Entry = Return_Command(Execute, { "set_feedwater_valve", std::to_string(
				static_cast<int>(UI_Access.Valve300_Postions[UI_Access.Slider_Positions[13]])) });
			Tick_Input(3, true);
		}
		Render_Necessities("heat_exchanger", "exchanger");
		break;
	case 7:
		Render_Box(60, 60, 520, 240, Colors_Access.Light_Grey, Colors_Access.Dark_Grey);
		Render_Slider(UI_Access.Slider_Texts[8], 1, 10, 2, UI_Access.Slider_Positions[8],
			120, 80, 400, Colors_Access.Abyss_Black, Colors_Access.Cherry_Blossom, true);
		Render_Dynamic_Text(Fonts_Access.Halftext_Font, "Producing " + Abbreviate_Number(
			Data_Access.Settings_Grid[UI_Access.Target_Tile.X][UI_Access.Target_Tile.Y]
			[4]) + "LA/s", Colors_Access.Abyss_Black, -1, 120);
		for (int Counter = 0; Counter < 2; Counter++) {
			Render_Button(Textures_Access.Confirmation.Data[Counter],
				Rectangles_Access.Confirmation.Data[Counter], Counter + 3);
		}
		break;
	case 8:
		Render_Box(60, 60, 520, 240, Colors_Access.Light_Grey, Colors_Access.Dark_Grey);
		Render_Slider(UI_Access.Slider_Texts[9], 1, Preset_Items_Access.Item_List.size() -
			1, 2, UI_Access.Slider_Positions[9], 120, 80, 400, Colors_Access.Abyss_Black,
			Colors_Access.Cherry_Blossom, true);
		Render_Slider(UI_Access.Slider_Texts[10], 2, 240, 3, UI_Access.Slider_Positions[10],
			120, 120, 400, Colors_Access.Abyss_Black, Colors_Access.Cherry_Blossom, true);
		Render_Slider(UI_Access.Slider_Texts[11], 3, UI_Access.Valve300_Postions.size() - 1,
			4, UI_Access.Slider_Positions[11], 120, 160, 400, Colors_Access.Abyss_Black,
			Colors_Access.Cherry_Blossom, true);
		Render_Dynamic_Text(Fonts_Access.Halftext_Font, "Producing " + Abbreviate_Number(
			Data_Access.Settings_Grid[X][Y][5]) + "L/s of " + std::to_string(
			static_cast<int>(Data_Access.Settings_Grid[X][Y][4])) + " °F " +
			ID_To_Item(Data_Access.Settings_Grid[X][Y][3]).Display_Name,
			Colors_Access.Abyss_Black, -1, 200);
		for (int Counter = 0; Counter < 2; Counter++) {
			Render_Button(Textures_Access.Confirmation.Data[Counter],
				Rectangles_Access.Confirmation.Data[Counter], Counter + 5);
		}
		break;
	case 9:
		Render_Box(10, 10, 620, 340, Colors_Access.Light_Grey, Colors_Access.Dark_Grey);
		SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Recipe_Content,
			NULL, &Rectangles_Access.Recipe_Content);
		//render custom box with outside bound
		if (UI_Access.Subprompt_Identifier == LDE_INVALID) {
			Index = 0;
			for (int Counter = 0; Counter < Metadata_Access.Machine_Count; Counter++) {
				if (I_Recipes[Counter].empty() && O_Recipes[Counter].empty()
					&& IO_Recipes[Counter].empty()) {
					continue;
				}
				float Base_Subwidth = 44 * Settings_Access.Screen_Size;
				float Base_Padding = 7 * Settings_Access.Screen_Size;
				float Base_Subpadding = 2 * Settings_Access.Screen_Size;
				SDL_FRect Outer_Rectangle = {
					static_cast<float>((((Index % 10) * 58) + 30) *
						Settings_Access.Screen_Size) + Base_Padding,
					static_cast<float>(((std::floor(Index / 10) * 58) + 60) *
						Settings_Access.Screen_Size) + Base_Padding,
					Base_Subwidth,
					Base_Subwidth
				};
				if (Detect_Mouse_Collision(Outer_Rectangle) && UI_Access.UI_Selection == 0) {
					Set_Renderer_Color(Colors_Access.Cherry_Blossom);
					UI_Access.UI_Selection = Counter + 3;
				} else {
					Set_Renderer_Color(Colors_Access.Abyss_Black);
				}
				SDL_RenderFillRect(Core_Access.Application_Renderer, &Outer_Rectangle);
				SDL_FRect Inner_Rectangle = {
					Outer_Rectangle.x + Base_Subpadding,
					Outer_Rectangle.y + Base_Subpadding,
					Base_Subwidth - (Base_Subpadding * 2),
					Base_Subwidth - (Base_Subpadding * 2)
				};
				Set_Renderer_Color(Colors_Access.Pure_White);
				SDL_RenderFillRect(Core_Access.Application_Renderer, &Inner_Rectangle);
				Clear_Renderer();
				bool r=true;
				SDL_FRect Machine_Rectangle = {
					Inner_Rectangle.x + Base_Subpadding,
					Inner_Rectangle.y + Base_Subpadding,
					36.0f * Settings_Access.Screen_Size,
					36.0f * Settings_Access.Screen_Size
				};
				float XY_Ratio = Metadata_Access.Machine_Rectangles[Counter].w /
					Metadata_Access.Machine_Rectangles[Counter].h;
				if (XY_Ratio > 1) {
					Machine_Rectangle.h = Machine_Rectangle.w / XY_Ratio;
					Machine_Rectangle.y = Machine_Rectangle.y +	(18.0f *
						Settings_Access.Screen_Size) - (Machine_Rectangle.h * 0.5);
				} else if (XY_Ratio < 1) {
					Machine_Rectangle.w = Machine_Rectangle.h * XY_Ratio;
					Machine_Rectangle.x = Machine_Rectangle.x +	(18.0f *
						Settings_Access.Screen_Size) - (Machine_Rectangle.w * 0.5);
				}
				SDL_RenderTexture(Core_Access.Application_Renderer,
					Metadata_Access.Machine_Sprites[Counter], NULL,
					&Machine_Rectangle);
				Index++;
			}
		} else {
			int Offset = 120;
			//i recipes
			//o recipes
			int Index = UI_Access.Subprompt_Identifier;
			std::string Candidate;
			int Number = 1;
			for (int Counter1 = 0; Counter1 < 3; Counter1++) {
				std::vector<std::vector<Recipe*>> Table;
				Table = All_Recipes[Counter1];
				for (int Counter2 = 0; Counter2 < Table[Index].size(); Counter2++, Number++) {
					Candidate = "Recipe No. ";
					if (Number < 10) {
						Candidate += "0";
					}
					Candidate += std::to_string(Number) + " -> " + Abbreviate_Number(Table
						[Index][Counter2]->Power) + "J/s, " + std::to_string(Table
						[Index][Counter2]->Time) + "s";
					if (Table[Index][Counter2]->Voiding_Excess) {
						Candidate += ", cannot overflow";
					}
					Render_Dynamic_Text(Fonts_Access.Subtext_Font, Candidate,
						Colors_Access.Abyss_Black, 16, Offset);
					Offset += 20;
					Candidate = "Inputs -> ";
					for (int Counter3 = 0; Counter3 < Table[Index][Counter2]->Input_Items.size(); Counter3++) {
						Candidate += Abbreviate_Number(Table[Index][Counter2]->Input_Counts[Counter3] /
							Table[Index][Counter2]->Time) + "L/s " + Table[Index]
							[Counter2]->Input_Items[Counter3].Display_Name;
						if (Counter3 < Table[Index][Counter2]->Input_Items.size() - 1) {
							Candidate += ", ";
						}
					}
					Render_Dynamic_Text(Fonts_Access.Subtext_Font, Candidate,
						Colors_Access.Abyss_Black, 26, Offset);
					Offset += 20;
					Candidate = "Outputs -> ";
					for (int Counter3 = 0; Counter3 < Table[Index][Counter2]->Output_Items.size(); Counter3++) {
						Candidate += Abbreviate_Number(Table[Index][Counter2]->Output_Counts[Counter3] /
							Table[Index][Counter2]->Time) + "L/s " + Table[Index]
							[Counter2]->Output_Items[Counter3].Display_Name;
						if (Counter3 < Table[Index][Counter2]->Output_Items.size() - 1) {
							Candidate += ", ";
						}
					}
					Render_Dynamic_Text(Fonts_Access.Subtext_Font, Candidate,
						Colors_Access.Abyss_Black, 26, Offset);
					Offset += 20;
					//io recipes
				}
			}
			//recipe list
			break;
		}
		//recipe katalog, set selection, recipe list
		break;
	case 10:
		Render_Backing();
		Render_Sidebuttons(Textures_Access.MT_Buttons, Rectangles_Access.MT_Buttons);
		Parameters = {
			{ "diagnostics" }
		};
		Command_Types = {
			Get_Data
		};
		Process_Commands(Command_Types, Parameters);
		Render_Necessities("modular_turbine", "turbine");
		break;
	default:
		break;
	}
}

void Render_Slider(std::vector<std::string> Labels, int Engagement, int Nodes, int Selection, int &Position,
	int X, int Y, int Width, SDL_Color Primary, SDL_Color Secondary, bool Text_Visible) {
	bool Active = false;
	SDL_FRect Background_Rectangle = { static_cast<float>(X * Settings_Access.Screen_Size),
		static_cast<float>(Y - 3) * Settings_Access.Screen_Size, static_cast<float>(Width *
		Settings_Access.Screen_Size), 6.0f * Settings_Access.Screen_Size };
	if (UI_Access.Engagement == Engagement) {
		Active = true;
		std::vector<int>Separators = { };
		for (int Counter = 0; Counter < Nodes; Counter++) {
			Separators.push_back(static_cast<int>(((((double)Counter / Nodes) * Width) + (Width / (Nodes * 2)) + X)) *
				Settings_Access.Screen_Size);
		}
		for (int Counter = 0; Counter < Nodes; Counter++) {
			if (Core_Access.Debug_Mode) {
				SDL_RenderLine(Core_Access.Application_Renderer, static_cast<float>(Separators[Counter]),
					0, static_cast<float>(Separators[Counter]), 360.0f * Settings_Access.Screen_Size);
			}
			if (UI_Access.X_Mouse_Position < Separators[0]) {
				Position = 0;
			} else if (UI_Access.X_Mouse_Position >= Separators[Nodes - 1]) {
				Position = Nodes;
			} else if (UI_Access.X_Mouse_Position >= Separators[Counter] && UI_Access.X_Mouse_Position < Separators[Counter + 1]) {
				Position = Counter + 1;
			}
		}
	}
	Set_Renderer_Color(Primary);
	SDL_RenderFillRect(Core_Access.Application_Renderer, &Background_Rectangle);
	if (Active) {
		Set_Renderer_Color(Secondary);
	}
	SDL_FRect Node_Rectangle = { static_cast<float>((((double) Position / Nodes) * Width) + X - 6) *
		Settings_Access.Screen_Size, static_cast<float>(Y - 6) * Settings_Access.Screen_Size,
		12.0f * Settings_Access.Screen_Size, 12.0f * Settings_Access.Screen_Size};
	if (Detect_Mouse_Collision(Node_Rectangle)) {
		UI_Access.UI_Selection = Selection;
		Set_Renderer_Color(Secondary);
	}
	SDL_RenderFillRect(Core_Access.Application_Renderer, &Node_Rectangle);
	Clear_Renderer();
	if (Text_Visible) {
		SDL_Surface* Caption_Surface = TTF_RenderText_Blended(Fonts_Access.Subtext_Font,
			Labels[Position].c_str(), Labels[Position].size(), Primary);
		SDL_FRect Caption_Rectangle = { static_cast<float>(((((double)Position / Nodes) * Width) + X) *
			Settings_Access.Screen_Size) - (Caption_Surface->w / 2), static_cast<float>(Y + 10) *
			Settings_Access.Screen_Size, static_cast<float>(Caption_Surface->w), static_cast<float>(Caption_Surface->h) };
		SDL_Texture* Caption_Texture = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Caption_Surface);
		SDL_RenderTexture(Core_Access.Application_Renderer, Caption_Texture, NULL, &Caption_Rectangle);
		SDL_DestroySurface(Caption_Surface);
		SDL_DestroyTexture(Caption_Texture);
	}
}

void Drain_Query() {
	for (int Counter1 = 0; Counter1 < Temporary_Access.Query.size(); Counter1++) {
		if (Temporary_Access.ID_Query[Counter1] == 0) {
			Render_Outline(Temporary_Access.Query[Counter1], Temporary_Access.Color_Query[Counter1]);
		} else if (Temporary_Access.ID_Query[Counter1] == 1) {
			double Length = std::sqrt(std::pow(Temporary_Access.Query[Counter1].x -
				Temporary_Access.Query[Counter1].w, 2) + std::pow(Temporary_Access
				.Query[Counter1].y - Temporary_Access.Query[Counter1].h, 2));
			double Rotation = std::atan2(Temporary_Access.Query[Counter1].y -
				Temporary_Access.Query[Counter1].h, Temporary_Access.Query[Counter1].x -
				Temporary_Access.Query[Counter1].w) / (M_PI / 180);
			SDL_FPoint Centrepoint = { 5.0f * Settings_Access.Screen_Size,
				5.0f * Settings_Access.Screen_Size };
			for (int Counter2 = 0; Counter2 < std::floor(Length /
				(Settings_Access.Screen_Size * 10)); Counter2++) {
				SDL_FRect Tilebox = { 0.0f, 0.0f, Settings_Access.Screen_Size *
					10.0f, Settings_Access.Screen_Size * 10.0f };
				Tilebox.x = static_cast<float>(Temporary_Access.Query[Counter1].x -
					((Counter2 * Settings_Access.Screen_Size * 10) * cos(Rotation *
					(M_PI / 180))) - (5 * Settings_Access.Screen_Size));
				Tilebox.y = static_cast<float>(Temporary_Access.Query[Counter1].y -
					((Counter2 * Settings_Access.Screen_Size * 10) * sin(Rotation *
					(M_PI / 180))) - (5 * Settings_Access.Screen_Size));
				SDL_RenderTextureRotated(Core_Access.Application_Renderer,
					Textures_Access.Path_Arrow, NULL, &Tilebox,
					Rotation + 90, &Centrepoint, SDL_FLIP_NONE);
			}
		}
	}
	Temporary_Access.ID_Query.clear();
	Temporary_Access.Query.clear();
	Temporary_Access.Color_Query.clear();
}

void Render_Toolbar() {
	if (UI_Access.Tool > LDE_INVALID) {
		Set_Renderer_Color(Colors_Access.Dark_Grey);
		SDL_FRect Backing_Rectangle = Rectangles_Access.Tool[UI_Access.Tool];
		Backing_Rectangle.x = Backing_Rectangle.x - (2 * Settings_Access.Screen_Size);
		Backing_Rectangle.w = Backing_Rectangle.w + (4 * Settings_Access.Screen_Size);
		Backing_Rectangle.y = 330 * Settings_Access.Screen_Size;
		Backing_Rectangle.h = 38 * Settings_Access.Screen_Size;
		SDL_RenderFillRect(Core_Access.Application_Renderer, &Backing_Rectangle);
		Backing_Rectangle.y = 334 * Settings_Access.Screen_Size;
		Backing_Rectangle.h = 34 * Settings_Access.Screen_Size;
		Set_Renderer_Color(Colors_Access.Light_Grey);
		SDL_RenderFillRect(Core_Access.Application_Renderer, &Backing_Rectangle);
		Clear_Renderer();
		Rectangles_Access.Cap.x = Backing_Rectangle.x + Backing_Rectangle.w;
		Rectangles_Access.Cap_Button.x = Rectangles_Access.Cap.x + Rectangles_Access.Cap.w + 12;
		Rectangles_Access.Cap_Hitbox.Data[0] = Rectangles_Access.Cap_Button;
		Rectangles_Access.Cap_Hitbox.Data[1] = Rectangles_Access.Cap_Button;
		Render_Button(Textures_Access.Cap_Button.Data[0], Rectangles_Access.Cap_Hitbox, 4);
		SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access
			.Cap.Data[0], NULL, &Rectangles_Access.Cap);
		Rectangles_Access.Cap.x = Backing_Rectangle.x - Rectangles_Access.Cap.w;
		Rectangles_Access.Cap_Button.x = Rectangles_Access.Cap.x -
			Rectangles_Access.Cap_Button.w - 12;
		Rectangles_Access.Cap_Hitbox.Data[0] = Rectangles_Access.Cap_Button;
		Rectangles_Access.Cap_Hitbox.Data[1] = Rectangles_Access.Cap_Button;
		Render_Button(Textures_Access.Cap_Button.Data[1], Rectangles_Access.Cap_Hitbox, 5);
		SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Cap
			.Data[1], NULL, &Rectangles_Access.Cap);
		SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Tool
			.Data[UI_Access.Tool], NULL, &Rectangles_Access.Tool[UI_Access.Tool]);
	}
	if (UI_Access.Tool == 0) {
		std::string Machine_Text = Metadata_Access.Machine_Names[UI_Access.Placing_Item - 1] + " | " +
			Abbreviate_Number(UI_Access.Queried_Price) + "LA";
		SDL_Surface* Machine_Surface = TTF_RenderText_Blended(Fonts_Access.Subtext_Font, Machine_Text.c_str(),
			Machine_Text.size(), Colors_Access.Abyss_Black);
		SDL_FRect Machine_Rectangle = { static_cast<float>(312 * Settings_Access.Screen_Size) -
			(Machine_Surface->w / 2), 290.0f * Settings_Access.Screen_Size, Machine_Surface->w +
			static_cast<float>(16 * Settings_Access.Screen_Size), TTF_GetFontHeight(
			Fonts_Access.Subtext_Font) + static_cast<float>(18 * Settings_Access.Screen_Size) };
		Set_Renderer_Color(Colors_Access.Dark_Grey);
		SDL_RenderFillRect(Core_Access.Application_Renderer, &Machine_Rectangle);
		Machine_Rectangle.x = Machine_Rectangle.x + (4 * Settings_Access.Screen_Size);
		Machine_Rectangle.y = Machine_Rectangle.y + (4 * Settings_Access.Screen_Size);
		Machine_Rectangle.w = Machine_Rectangle.w - (8 * Settings_Access.Screen_Size);
		Machine_Rectangle.h = Machine_Rectangle.h - (8 * Settings_Access.Screen_Size);
		Set_Renderer_Color(Colors_Access.Light_Grey);
		SDL_RenderFillRect(Core_Access.Application_Renderer, &Machine_Rectangle);
		Clear_Renderer();
		Machine_Rectangle.x = Machine_Rectangle.x + (4 * Settings_Access.Screen_Size);
		Machine_Rectangle.y = Machine_Rectangle.y + (4 * Settings_Access.Screen_Size);
		Machine_Rectangle.w = Machine_Surface->w;
		Machine_Rectangle.h = Machine_Surface->h;
		SDL_Texture* Machine_Texture = SDL_GenerateTextureFromSurface(Core_Access.Application_Renderer, Machine_Surface);
		SDL_RenderTexture(Core_Access.Application_Renderer, Machine_Texture, NULL, &Machine_Rectangle);
		SDL_DestroySurface(Machine_Surface);
		SDL_DestroyTexture(Machine_Texture);
	}
}

void Verify_Settings() {
	bool Keybinds_Altered = false;
	for (int Counter = 0; Counter < Keybinds_Access.Keybind_Settings.size(); Counter++) {
		if (Keybinds_Access.Keybind_Settings[Counter] != Keybinds_Access.Keybind_List[Counter]) {
			Keybinds_Altered = true;
			break;
		}
	}
	if (Settings_Access.Screen_Size != UI_Access.Slider_Positions[0] + 1 || Keybinds_Altered ||
		static_cast<int>(Settings_Access.AA_Temporary) != Settings_Access.Anti_Aliasing ||
		static_cast<int>(Settings_Access.VS_Temporary) != Settings_Access.VSync || Settings_Access.Raw_FPS !=
		UI_Access.Slider_Positions[4] || Settings_Access.Volume != UI_Access.Slider_Positions[5] ||
		UI_Access.Slider_Positions[6] != Settings_Access.Fullscreen) {
		Render_Button(Textures_Access.Apply, Rectangles_Access.Apply, 2);
		Render_Button(Textures_Access.Cancel, Rectangles_Access.Cancel, 3);
	}
}

void Render_Tile_Prompts() {
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rectangles_Access.Tile_1x1.x = static_cast<int>(((Column * 40) -
			UI_Access.Camera_X) * Settings_Access.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rectangles_Access.Tile_1x1.y = static_cast<int>(((Row * 40) -
				UI_Access.Camera_Y) * Settings_Access.Screen_Size);
			if (Detect_Mouse_Collision(Rectangles_Access.Tile_1x1)) {
				for (int Counter = 0; Counter < Metadata_Access.Quirk_Positions[2].size(); Counter++) {
						if (Visual_To_ID(Data_Access.Visual_Grid[Column][Row]) ==
							Metadata_Access.Quirk_Positions[2][Counter]) {
						std::string Core = SDL_GetKeyName(Keybinds_Access.Keybind_List[10]);
						for (int Counter = 0; Counter < Core.size(); Counter++) {
							Core[Counter] = static_cast<char>(std::tolower(Core[Counter]));
						}
						Core = "interact - (\"" + Core + "\")";
						SDL_Surface* Carrying_Surface = TTF_RenderText_Blended(Fonts_Access.Halftext_Font, Core.c_str(),
							Core.size(), Colors_Access.Cherry_Blossom);
						SDL_FRect Carrying_Rectangle = { static_cast<float>(320 * Settings_Access.Screen_Size) -
							(Carrying_Surface->w / 2), 320.0f *	Settings_Access.Screen_Size, static_cast<float>(
							Carrying_Surface->w), static_cast<float>(Carrying_Surface->h) };
						SDL_Texture* Carrying_Texture = SDL_GenerateTextureFromSurface(
							Core_Access.Application_Renderer, Carrying_Surface);
						Render_Box((Carrying_Rectangle.x / Settings_Access.Screen_Size) - 4,
							(Carrying_Rectangle.y / Settings_Access.Screen_Size) - 4,
							(Carrying_Rectangle.w / Settings_Access.Screen_Size) + 8,
							(Carrying_Rectangle.h / Settings_Access.Screen_Size) + 8,
							Colors_Access.Light_Grey, Colors_Access.Dark_Grey);
						SDL_RenderTexture(Core_Access.Application_Renderer, Carrying_Texture, NULL, &Carrying_Rectangle);
						SDL_DestroySurface(Carrying_Surface);
						SDL_DestroyTexture(Carrying_Texture);
					}
				}
			}
		}
	}
}

void Render_Interaction() {
	int Indexes[7] = { 4, 3, 5, 6, 7, 8, 10 };
	for (int Column = 0; Column < LDE_GRIDSIZE; Column++) {
		Rectangles_Access.Tile_1x1.x = static_cast<int>(((Column * 40) -
			UI_Access.Camera_X) * Settings_Access.Screen_Size);
		for (int Row = 0; Row < LDE_GRIDSIZE; Row++) {
			Rectangles_Access.Tile_1x1.y = static_cast<int>(((Row * 40) -
				UI_Access.Camera_Y) * Settings_Access.Screen_Size);
			if (Detect_Mouse_Collision(Rectangles_Access.Tile_1x1)) {
				for (int Counter = 0; Counter < Metadata_Access.Quirk_Positions[2].size(); Counter++) {
					if (Visual_To_ID(Data_Access.Visual_Grid[Column][Row]) ==
						Metadata_Access.Quirk_Positions[2][Counter]) {
						UI_Access.Prompt_Identifier = Indexes[Counter];
						UI_Access.Building = false;
						UI_Access.Target_Tile.X = Column;
						UI_Access.Target_Tile.Y = Row;
						switch (Visual_To_ID(Data_Access.Visual_Grid[Column][Row])) {
						case Money_Generator:
							UI_Access.Slider_Positions[8] = Data_Access.Settings_Grid
								[UI_Access.Target_Tile.X][UI_Access.Target_Tile.Y][3];
							break;
						case Fluid_Generator:
							UI_Access.Slider_Positions[9] = Data_Access.Settings_Grid
								[UI_Access.Target_Tile.X][UI_Access.Target_Tile.Y][3];
							UI_Access.Slider_Positions[10] = Data_Access.Settings_Grid
								[UI_Access.Target_Tile.X][UI_Access.Target_Tile.Y][4] / 5;
							for (int Counter = 0; Counter < UI_Access.Valve300_Postions.size(); Counter++) {
								if (Data_Access.Settings_Grid[UI_Access.Target_Tile.X]
									[UI_Access.Target_Tile.Y][5] == UI_Access.Valve300_Postions[Counter]) {
									UI_Access.Slider_Positions[11] = Counter;
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
	if (UI_Access.Effects[Heat] > 0) {
		//std::cout << "boilin'" << " ";
	}
}

void Find_Effect() {
	UI_Access.Effects[Heat] = 0;
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			for (int Counter = 0; Counter < Metadata_Access.Heating_Machines.size(); Counter++) {
				if (Visual_To_ID(Data_Access.Visual_Grid[X][Y]) == Metadata_Access.Heating_Machines[Counter] &&
					X * 40 > UI_Access.Camera_X && Y * 40 > UI_Access.Camera_Y && X * 40 <
					UI_Access.Camera_X + 640 && Y * 40 < UI_Access.Camera_Y + 360) {
					UI_Access.Effects[Heat] += 0.1;
				}
			}
		}
	}
}

void Cache_Blueprint() {
	int Width;
	int Height;
	ID_To_Size(UI_Access.Placing_Item - 1, UI_Access.Placing_Rotation, Width, Height);
	int Maximum = (Width > Height ? Width : Height) * Settings_Access.Screen_Size * 40;
	SDL_DestroyTexture(Cache_Access.Blueprint_Cache);
	Cache_Access.Blueprint_Cache = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Maximum, Maximum);
	SDL_SetTextureBlendMode(Cache_Access.Blueprint_Cache, SDL_BLENDMODE_BLEND);
	SDL_Texture* Backing = SDL_GenerateTexture(Core_Access.Application_Renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Width *
		Settings_Access.Screen_Size * 40, Height * Settings_Access.Screen_Size * 40);
	SDL_SetTextureBlendMode(Backing, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Backing);
	for (int X = 0; X < Width; X++) {
		for (int Y = 0; Y < Height; Y++) {
			SDL_FRect Pasting_Rectangle = Rectangles_Access.Tile_1x1;
			Pasting_Rectangle.x = X * Settings_Access.Screen_Size * 40;
			Pasting_Rectangle.y = Y * Settings_Access.Screen_Size * 40;
			SDL_RenderTexture(Core_Access.Application_Renderer, Textures_Access.Tile_Texture,
				NULL, &Pasting_Rectangle);
		}
	}
	SDL_SetRenderTarget(Core_Access.Application_Renderer, Cache_Access.Blueprint_Cache);
	SDL_RenderTexture(Core_Access.Application_Renderer, Backing, NULL, NULL);
	SDL_DestroyTexture(Backing);
	int Rotation = UI_Access.Placing_Rotation * 90;
	for (int Counter = 0; Counter < Metadata_Access.Quirk_Positions[0].size(); Counter++) {
		if (Metadata_Access.Quirk_Positions[0][Counter] == UI_Access.Placing_Item - 1) {
			Rotation = 0;
		}
	}
	SDL_FPoint Centerpoint = { Maximum * 0.5f, Maximum * 0.5f };
	SDL_RenderTextureRotated(Core_Access.Application_Renderer, Metadata_Access.Machine_Sprites
		[UI_Access.Placing_Item - 1], NULL, NULL, Rotation, &Centerpoint, SDL_FLIP_NONE);
	SDL_SetRenderTarget(Core_Access.Application_Renderer, NULL);
	SDL_SetTextureAlphaMod(Cache_Access.Blueprint_Cache, 190);
}

void Cache_Price() {
	UI_Access.Queried_Price = static_cast<int>((Metadata_Access.Machine_Prices[UI_Access.Placing_Item - 1] *
		1.1)) +	Metadata_Access.Machine_Taxes[UI_Access.Placing_Item - 1] + 1;
}