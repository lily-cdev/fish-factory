#include <ui.h>

void Render_Catalog(int X, int Y) {
	int Index;
	Render_Box(10, 10, 620, 340, Colors.Light_Grey, Colors.Dark_Grey);
	SDL_RenderTexture(Core.Renderer, Textures.Recipe_Content, NULL, &Rects.Recipe_Content);
	//render custom box with outside bound
	if (Interface.Subprompt_Identifier == LDE_INVALID) {
		Index = 0;
		for (int Counter = 0; Counter < LDE_MACHINES; Counter++) {
			if (reclen((*I_Recipes)[Counter]) == 0 && reclen((*O_Recipes)[Counter]) == 0 &&
				reclen((*IO_Recipes)[Counter]) == 0) {
				continue;
			}
			float Base_Subwidth = Settings.Screen_Size * 44.0f;
			float Base_Padding = Settings.Screen_Size * 7.0f;
			float Base_Subpadding = Settings.Screen_Size * 2.0f;
			SDL_FRect Outer_Rectangle = {
				static_cast<float>((((Index % 10) * 58) + 30) *
					Settings.Screen_Size) + Base_Padding,
				static_cast<float>(((std::floor(Index / 10) * 58) + 60) *
					Settings.Screen_Size) + Base_Padding,
				Base_Subwidth,
				Base_Subwidth
			};
			if (Detect_Mouse_Collision(Outer_Rectangle) && Interface.UI_Selection == 0) {
				Set_Renderer_Color(Colors.Cherry_Blossom);
				Interface.UI_Selection = Counter + 3;
			} else {
				Set_Renderer_Color(Colors.Abyss_Black);
			}
			SDL_RenderFillRect(Core.Renderer, &Outer_Rectangle);
			SDL_FRect Inner_Rectangle = {
				Outer_Rectangle.x + Base_Subpadding,
				Outer_Rectangle.y + Base_Subpadding,
				Base_Subwidth - (Base_Subpadding * 2),
				Base_Subwidth - (Base_Subpadding * 2)
			};
			Set_Renderer_Color(Colors.Pure_White);
			SDL_RenderFillRect(Core.Renderer, &Inner_Rectangle);
			Clear_Renderer();
			SDL_FRect Machine_Rectangle = {
				Inner_Rectangle.x + Base_Subpadding,
				Inner_Rectangle.y + Base_Subpadding,
				36.0f * Settings.Screen_Size,
				36.0f * Settings.Screen_Size
			};
			float XY_Ratio = Metadata.Machine_Rectangles[Counter].w /
				Metadata.Machine_Rectangles[Counter].h;
			if (XY_Ratio > 1) {
				Machine_Rectangle.h = Machine_Rectangle.w / XY_Ratio;
				Machine_Rectangle.y = Machine_Rectangle.y +	(18.0f *
					Settings.Screen_Size) - (Machine_Rectangle.h * 0.5);
			} else if (XY_Ratio < 1) {
				Machine_Rectangle.w = Machine_Rectangle.h * XY_Ratio;
				Machine_Rectangle.x = Machine_Rectangle.x +	(18.0f *
					Settings.Screen_Size) - (Machine_Rectangle.w * 0.5);
			}
			SDL_RenderTexture(Core.Renderer, Metadata.Machine_Sprites[Counter], NULL,
				&Machine_Rectangle);
			Index++;
		}
	} else {
		int Offset = 120;
		//i recipes
		//o recipes
		int Index = Interface.Subprompt_Identifier;
		std::string Candidate;
		int Number = 1;
		for (int Counter1 = 0; Counter1 < 3; Counter1++) {
			for (int Counter2 = 0; Counter2 < reclen((*All_Recipes)[Counter1][Index]); Counter2++, Number++) {
				Candidate = "Recipe No. ";
				if (Number < 10) {
					Candidate += "0";
				}
				char Buffer[128];
				char Subbuffer[64];
				Abbreviate_Number(All_Recipes[Counter1][Index][Counter2]->Power, Subbuffer, sizeof(Subbuffer));
				snprintf(Buffer, sizeof(Buffer), "%i -> %sJ/s, %is", Number, Subbuffer,
					All_Recipes[Counter1][Index][Counter2]->Time);
				std::string tmp = Buffer;
				Candidate += tmp;
				if (All_Recipes[Counter1][Index][Counter2]->Voiding_Excess) {
					Candidate += ", cannot overflow";
				}
				Render_Dynamic_Text(Fonts.Subtext_Font, Candidate.c_str(),
					Colors.Abyss_Black, 16, Offset);
				Offset += 20;
				Candidate = "Inputs -> ";
				for (int Counter3 = 0; Counter3 < All_Recipes[Counter1][Index][Counter2]->Inputs; Counter3++) {
					memset(Buffer, 0, sizeof(Buffer));
					Abbreviate_Number(All_Recipes[Counter1][Index][Counter2]->Input_Counts[Counter3] /
						All_Recipes[Counter1][Index][Counter2]->Time, Buffer, sizeof(Buffer));
					std::string tmp = Buffer;
					Candidate += tmp + "L/s " + All_Recipes[Counter1][Index]
						[Counter2]->Input_Items[Counter3].Display_Name;
					if (Counter3 < All_Recipes[Counter1][Index][Counter2]->Inputs - 1) {
						Candidate += ", ";
					}
				}
				const char* tfmp = Candidate.c_str();
				memset(Buffer, 0, sizeof(Buffer));
				strcpy(Buffer, tfmp);
				Render_Dynamic_Text(Fonts.Subtext_Font, Buffer, Colors.Abyss_Black, 26, Offset);
				Offset += 20;
				Candidate = "Outputs -> ";
				for (int Counter3 = 0; Counter3 < All_Recipes[Counter1][Index][Counter2]->Outputs; Counter3++) {
					Abbreviate_Number(All_Recipes[Counter1][Index][Counter2]->Output_Counts[Counter3] /
						All_Recipes[Counter1][Index][Counter2]->Time, Buffer, sizeof(Buffer));
					std::string tmp = Buffer;
					Candidate += tmp + "L/s " + All_Recipes[Counter1][Index]
						[Counter2]->Output_Items[Counter3].Display_Name;
					if (Counter3 < All_Recipes[Counter1][Index][Counter2]->Outputs - 1) {
						Candidate += ", ";
					}
				}
				Render_Dynamic_Text(Fonts.Subtext_Font, Candidate.c_str(),
					Colors.Abyss_Black, 26, Offset);
				Offset += 20;
				//io recipes
			}
		}
		//recipe list
	}
	//recipe katalog, set selection, recipe list
}