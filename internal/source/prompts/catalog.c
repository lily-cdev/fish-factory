#include <ui.h>

void Render_Catalog(Point Pos) {
	int Index;
	Render_Box((Point){ 10, 10 }, 620, 340, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Texture(Textures.Recipe_Content, &Rects.Recipe_Content);
	//render custom box with outside bound
	if (Interface.Subprompt_Identifier == ktn_invalid) {
		Index = 0;
		for (int C1 = 0; C1 < Core.Machines; C1++) {
			bool Found = false;
			for (int C2 = 0; C2 < Core.Recipes; C2++) {
				if (ktn_stricmp(Metadata.Recipes[C2].Machine->Index, Metadata.Machines[C1].Index)) {
					Found = true;
					break;
				}
			}
			if (!Found) {
				continue;
			}
			float Base_Subwidth = ktn_fscale(44.0f);
			float Base_Padding = ktn_fscale(7.0f);
			float Base_Subpadding = ktn_fscale(2.0f);
			SDL_FRect Outer_Rectangle = {
				ktn_fscale(((Index % 10) * 58.0f) + 30.0f) + Base_Padding,
				ktn_fscale((floorf(Index * 0.1f) * 58.0f) + 60.0f) + Base_Padding,
				Base_Subwidth,
				Base_Subwidth
			};
			if (Detect_Mouse_Collision(Outer_Rectangle) && Interface.UI_Selection == 0) {
				Set_Renderer_Color(Colors.Cherry_Blossom);
				Interface.UI_Selection = C1 + 3;
			} else {
				Set_Renderer_Color(Colors.Abyss_Black);
			}
			SDL_RenderFillRect(Core.Renderer, &Outer_Rectangle);
			SDL_FRect Inner_Rectangle = {
				Outer_Rectangle.x + Base_Subpadding,
				Outer_Rectangle.y + Base_Subpadding,
				Base_Subwidth - (Base_Subpadding * 2.0f),
				Base_Subwidth - (Base_Subpadding * 2.0f)
			};
			Set_Renderer_Color(Colors.Pure_White);
			SDL_RenderFillRect(Core.Renderer, &Inner_Rectangle);
			Clear_Renderer();
			SDL_FRect Machine_Rectangle = {
				Inner_Rectangle.x + Base_Subpadding,
				Inner_Rectangle.y + Base_Subpadding,
				ktn_fscale(36.0f),
				ktn_fscale(36.0f)
			};
			float XY_Ratio = Metadata.Machines[C1].Rect.w / Metadata.Machines[C1].Rect.h;
			if (XY_Ratio > 1) {
				Machine_Rectangle.h = Machine_Rectangle.w / XY_Ratio;
				Machine_Rectangle.y = Machine_Rectangle.y +	ktn_fscale(18.0f) - (Machine_Rectangle.h * 0.5f);
			} else if (XY_Ratio < 1) {
				Machine_Rectangle.w = Machine_Rectangle.h * XY_Ratio;
				Machine_Rectangle.x = Machine_Rectangle.x +	ktn_fscale(18.0f) - (Machine_Rectangle.w * 0.5f);
			}
			Render_Texture(Metadata.Machines[C1].Icon, &Machine_Rectangle);
			Index++;
		}
	} else {
		int Offset = 120;
		int Index = Interface.Subprompt_Identifier;
		char Candidate[256];
		int Number = 1;
		for (int C1 = 0; C1 < Core.Recipes; C1++) {
			if (!ktn_stricmp(Metadata.Machines[Index].Index, Metadata.Recipes[C1].Machine->Index)) {
				continue;
			}
			strncpy(Candidate, "Recipe No. ", sizeof(Candidate));
			if (Number < 10) {
				ktn_charcat(Candidate, '0', sizeof(Candidate));
			}
			char Buffer[128];
			char Subbuffer[64];
			Abbreviate_Number(Metadata.Recipes[C1].Power, Subbuffer, sizeof(Subbuffer));
			snprintf(Buffer, sizeof(Buffer), "%i -> %sJ/s, %is", Number, Subbuffer, Metadata.Recipes[C1].Time);
			strcat(Candidate, Buffer);
			if (Metadata.Recipes[C1].Voiding_Excess) {
				strcat(Candidate, ", cannot overflow");
			}
			Process_Supply(&Supplies.Catalog1[C1], Candidate, F_Subtext, Colors.Abyss_Black, (Point){ 16, Offset });
			Offset += 20;
			if (Metadata.Recipes[C1].Machine->Input_Ct > 0) {
				strncpy(Candidate, "Inputs -> ", sizeof(Candidate));
				Process_Supply(&Supplies.Catalog1[C1], Candidate, F_Subtext, Colors.Abyss_Black, (Point){ 26, Offset });
				Offset += 20;
			}
			for (int C3 = 0; C3 < Metadata.Recipes[C1].Machine->Input_Ct; C3++) {
				Abbreviate_Number(Metadata.Recipes[C1].Input_Counts[C3] / Metadata.Recipes[C1].Time, Buffer, sizeof(Buffer));
				snprintf(Candidate, sizeof(Candidate), "%suFI/s %s", Buffer, Metadata.Recipes[C1].Input_Items[C3]->Name);
				if (C3 < Metadata.Recipes[C1].Machine->Input_Ct - 1) {
					strcat(Candidate, ", ");
				}
				Process_Supply(&Supplies.Catalog2[C1], Candidate, F_Subtext, Colors.Abyss_Black, (Point){ 36, Offset });
				Offset += 20;
			}
			if (Metadata.Recipes[C1].Machine->Output_Ct > 0) {
				strncpy(Candidate, "Outputs -> ", sizeof(Candidate));
				Process_Supply(&Supplies.Catalog1[C1], Candidate, F_Subtext, Colors.Abyss_Black, (Point){ 26, Offset });
				Offset += 20;
			}
			for (int C3 = 0; C3 < Metadata.Recipes[C1].Machine->Output_Ct; C3++) {
				if (ktn_stricmp(Metadata.Recipes[C1].Output_Items[C3]->Name, "none")) {
					continue;
				}
				Abbreviate_Number(Metadata.Recipes[C1].Output_Counts[C3] / Metadata.Recipes[C1].Time, Buffer,
					sizeof(Buffer));
				snprintf(Candidate, sizeof(Candidate), "%suFI/s %s", Buffer, Metadata.Recipes[C1].Output_Items[C3]->Name);
				if (C3 < Metadata.Recipes[C1].Machine->Output_Ct - 1) {
					strcat(Candidate, ", ");
				}
				Process_Supply(&Supplies.Catalog3[C1], Candidate, F_Subtext, Colors.Abyss_Black, (Point){ 36, Offset });
				Offset += 20;
			}
			Number++;
		}
	}
}