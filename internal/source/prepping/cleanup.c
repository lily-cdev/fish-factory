#include <prepping.h>

void Clear_Texture_Array(Texture_Array* Target) {
	if ((*Target).Data != NULL) {
		for (int Counter = 0; Counter < (*Target).Length; Counter++) {
			SDL_DestroyTexture((*Target).Data[Counter]);
		}
		free((*Target).Data);
	}
}

void Clear_Texture2_Array(Texture2_Array* Target) {
	if ((*Target).Data != NULL) {
		for (int Counter = 0; Counter < (*Target).Length; Counter++) {
			Clear_Texture_Array(&((*Target).Data[Counter]));
		}
		free((*Target).Data);
	}
}

void Clear_Texture3_Array(Texture3_Array* Target) {
	if ((*Target).Data != NULL) {
		for (int Counter = 0; Counter < (*Target).Length; Counter++) {
			Clear_Texture2_Array(&((*Target).Data[Counter]));
		}
		free((*Target).Data);
	}
}

void Clear_Rect_Array(Rect_Array* Target) {
	if ((*Target).Data != NULL) {
		free((*Target).Data);
	}
}

void Clear_Rect2_Array(Rect2_Array* Target) {
	if ((*Target).Data != NULL) {
		for (int Counter = 0; Counter < (*Target).Length; Counter++) {
			Clear_Rect_Array(&(((*Target).Data)[Counter]));
		}
		free((*Target).Data);
	}
}

void Clear_Rect3_Array(Rect3_Array* Target) {
	if ((*Target).Data != NULL) {
		for (int Counter = 0; Counter < (*Target).Length; Counter++) {
			Clear_Rect2_Array(&((*Target).Data[Counter]));
		}
		free((*Target).Data);
	}
}

void Cleanup_Assets() {
	SDL_DestroyTexture(Core.Game_Texture);
	Free_Sound(&Audio.Primary_Ambience);
	Free_Sound(&Audio.Filtration_Loop);
	Free_Sound(&Audio.Ram_Loop);
	Free_Sound(&Audio.Click);
	TTF_CloseFont(Fonts.Logo_Font);
	TTF_CloseFont(Fonts.Large_Font);
	TTF_CloseFont(Fonts.Text_Font);
	TTF_CloseFont(Fonts.Halftext_Font);
	TTF_CloseFont(Fonts.Subtext_Font);
	TTF_CloseFont(Fonts.Microtext_Font);
	TTF_CloseFont(Fonts.Terminal_Font);
	Clear_Texture_Array(&Textures.Tool);
	Clear_Texture_Array(&Textures.Help_Content);
	Clear_Texture_Array(&Textures.Door);
	SDL_DestroyTexture(Textures.Recipe_Content);
	Clear_Texture3_Array(&Textures.Item_Labels);
	Clear_Rect3_Array(&Rects.Item_Labels);
	Clear_Texture3_Array(&Textures.Subcategories);
	Clear_Rect3_Array(&Rects.Subcategories);
	Clear_Texture3_Array(&Textures.Subcontents);
	Clear_Rect3_Array(&Rects.Subcontents);
	Clear_Texture2_Array(&Textures.Tutorials);
	Clear_Rect2_Array(&Rects.Tutorials);
	Clear_Rect_Array(&Rects.Tutorial_Hitbox);
	Clear_Texture2_Array(&Textures.Cheats);
	Clear_Rect2_Array(&Rects.Cheats);
	Clear_Texture2_Array(&Textures.Cap_Button);
	Clear_Rect_Array(&Rects.Cap_Hitbox);
	Clear_Texture2_Array(&Textures.New);
	Clear_Rect2_Array(&Rects.New);
	Clear_Texture2_Array(&Textures.Load);
	Clear_Rect2_Array(&Rects.Load);
	Clear_Texture2_Array(&Textures.Clear);
	Clear_Rect2_Array(&Rects.Clear);
	Clear_Texture2_Array(&Textures.Categories);
	Clear_Rect2_Array(&Rects.Categories);
	Clear_Texture_Array(&Textures.Error_Exit);
	Clear_Rect_Array(&Rects.Error_Exit);
	Clear_Texture2_Array(&Textures.MSP_Buttons);
	Clear_Rect2_Array(&Rects.MSP_Buttons);
	Clear_Texture2_Array(&Textures.SD_Buttons);
	Clear_Rect2_Array(&Rects.SD_Buttons);
	Clear_Texture2_Array(&Textures.HX_Buttons);
	Clear_Rect2_Array(&Rects.HX_Buttons);
	Clear_Texture3_Array(&Textures.TT_Buttons);
	Clear_Rect3_Array(&Rects.TT_Buttons);
	Clear_Texture2_Array(&Textures.MT_Buttons);
	Clear_Rect2_Array(&Rects.MT_Buttons);
	Clear_Texture2_Array(&Textures.Anti_Aliasing);
	Clear_Rect2_Array(&Rects.Anti_Aliasing);
	Clear_Texture2_Array(&Textures.V_Sync);
	Clear_Rect2_Array(&Rects.V_Sync);
	Clear_Texture2_Array(&Textures.Sort);
	Clear_Rect2_Array(&Rects.Sort);
	Clear_Texture2_Array(&Textures.TBW_Texture);
	Clear_Rect2_Array(&Rects.TBW_Rectangle);
	Clear_Texture_Array(&Textures.Clear_Tutorial);
	Clear_Rect_Array(&Rects.Clear_Tutorial);
	Clear_Texture_Array(&Textures.Settings_Label);
	Clear_Rect_Array(&Rects.Settings_Label);
	Clear_Texture_Array(&Textures.Save_Settings);
	Clear_Rect_Array(&Rects.Save_Settings);
	Clear_Texture_Array(&Textures.Cap);
	Clear_Texture_Array(&Textures.R_Pipe);
	Clear_Texture_Array(&Textures.L_Pipe);
	Clear_Texture_Array(&Textures.MS_Pool);
	Clear_Texture_Array(&Textures.Arrow);
	Clear_Texture_Array(&Textures.S_Dock);
	Clear_Texture_Array(&Textures.Tunnel);
	Clear_Rect_Array(&Rects.Tunnel);
	Clear_Texture_Array(&Textures.Return);
	Clear_Rect_Array(&Rects.Return);
	Clear_Texture_Array(&Textures.New_Game);
	Clear_Rect_Array(&Rects.New_Game);
	Clear_Texture_Array(&Textures.Settings);
	Clear_Rect_Array(&Rects.Settings);
	Clear_Texture_Array(&Textures.Update_Logs);
	Clear_Rect_Array(&Rects.Update_Logs);
	Clear_Texture_Array(&Textures.Credits);
	Clear_Rect_Array(&Rects.Credits);
	Clear_Texture_Array(&Textures.Quit_Game);
	Clear_Rect_Array(&Rects.Quit_Game);
	Clear_Texture_Array(&Textures.Apply);
	Clear_Rect_Array(&Rects.Apply);
	Clear_Texture_Array(&Textures.Cancel);
	Clear_Rect_Array(&Rects.Cancel);
	Clear_Texture_Array(&Textures.Next_Day);
	Clear_Rect_Array(&Rects.Next_Day);
	Clear_Texture_Array(&Textures.Quirk);
	Clear_Texture_Array(&Textures.Quirk_Label);
	SDL_DestroyTexture(Textures.Logo);
	SDL_DestroyTexture(Textures.Crosshair);
	SDL_DestroyTexture(Textures.Cursor_Core);
	SDL_DestroyTexture(Textures.Sapling);
	SDL_DestroyTexture(Textures.Node);
	SDL_DestroyTexture(Textures.Log_Background);
	SDL_DestroyTexture(Textures.Saveloader);
	SDL_DestroyTexture(Textures.Help_Sidebutton);
	SDL_DestroyTexture(Textures.Save_Sidebutton);
	SDL_DestroyTexture(Textures.Recipe_Sidebutton);
	SDL_DestroyTexture(Textures.Exit_Sidebutton);
	SDL_DestroyTexture(Textures.R_Flash);
	SDL_DestroyTexture(Textures.Bubble);
	SDL_DestroyTexture(Textures.Floor_Texture);
	SDL_DestroyTexture(Textures.Frame_Texture);
	SDL_DestroyTexture(Textures.Tile_Texture);
	Clear_Texture_Array(&Textures.R_Pump);
	Clear_Texture2_Array(&Textures.Incinerator);
	SDL_DestroyTexture(Textures.P_Generator);
	Clear_Texture_Array(&Textures.F_Plant);
	Clear_Texture2_Array(&Textures.B_Generator);
	Clear_Texture2_Array(&Textures.Distillery);
	Clear_Texture2_Array(&Textures.G_Bed);
	Clear_Texture_Array(&Textures.C_Platform);
	Clear_Texture_Array(&Textures.B_Scrubber);
	SDL_DestroyTexture(Textures.MS_Controller);
	SDL_DestroyTexture(Textures.MS_Output);
	SDL_DestroyTexture(Textures.MS_Input);
	Clear_Texture_Array(&Textures.E_Plant);
	Clear_Texture2_Array(&Textures.F_Mixer);
	Clear_Texture_Array(&Textures.T_Tower);
	SDL_DestroyTexture(Textures.Flowerpot);
	Clear_Texture_Array(&Textures.A_Shelf);
	Clear_Texture_Array(&Textures.Submarine);
	SDL_DestroyTexture(Textures.C_Node);
	Clear_Texture_Array(&Textures.G_Well);
	Clear_Texture_Array(&Textures.H_Exchanger);
	SDL_DestroyTexture(Textures.P_Wood);
	SDL_DestroyTexture(Textures.B_Tile);
	SDL_DestroyTexture(Textures.S_Carpet);
	SDL_DestroyTexture(Textures.H_Strip);
	SDL_DestroyTexture(Textures.M_Generator);
	SDL_DestroyTexture(Textures.F_Generator);
	Clear_Texture_Array(&Textures.R_Intersection);
	Clear_Texture_Array(&Textures.L_Intersection);
	Clear_Texture_Array(&Textures.SC_Input);
	Clear_Texture_Array(&Textures.SCH_Sink);
	Clear_Texture_Array(&Textures.SC_Transferor);
	Clear_Texture_Array(&Textures.SC_Output);
	Clear_Texture_Array(&Textures.ST_Input);
	Clear_Texture2_Array(&Textures.STIT_Block);
	Clear_Texture2_Array(&Textures.ST_Output);
	SDL_DestroyTexture(Textures.Scrap);
	Clear_Texture2_Array(&Textures.Confirmation);
	Clear_Rect2_Array(&Rects.Confirmation);
	Clear_Texture_Array(&Textures.Pyramid);
	SDL_DestroyTexture(Textures.Mesh);
	Clear_Texture_Array(&Textures.Fire);
	Clear_Texture_Array(&Textures.None);
	Clear_Texture_Array(&Cache.Wire_Cache);
	SDL_DestroyTexture(Cache.Blueprint_Cache);
	Clear_Texture2_Array(&Cache.Log_Cache);
}