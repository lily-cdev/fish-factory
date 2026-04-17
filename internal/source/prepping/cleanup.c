#include <prepping.h>
#include <items.h>

void Free_String2(String2* Target) {
	for (int C1 = 0; C1 < (*Target).Length; C1++) {
		free_c((*Target).Data[C1]);
	}
	free_c((*Target).Data);
	(*Target).Length = 0;
}

void Clear_Texture_Array(Texture_Array* Target) {
	for (int C1 = 0; C1 < (*Target).Length; C1++) {
		free_texture((*Target).Data[C1]);
	}
	free_c((*Target).Data);
	(*Target).Length = 0;
}

void Clear_Texture2_Array(Texture2_Array* Target) {
	for (int C1 = 0; C1 < (*Target).Length; C1++) {
		Clear_Texture_Array(&((*Target).Data[C1]));
	}
	free_c((*Target).Data);
	(*Target).Length = 0;
}

void Clear_Texture3_Array(Texture3_Array* Target) {
	for (int C1 = 0; C1 < (*Target).Length; C1++) {
		Clear_Texture2_Array(&((*Target).Data[C1]));
	}
	free_c((*Target).Data);
	(*Target).Length = 0;
}

void Clear_Rect2_Array(Rect2_Array* Target) {
	for (int C1 = 0; C1 < (*Target).Length; C1++) {
		free_c((*Target).Data[C1].Data);
	}
	free_c((*Target).Data);
	(*Target).Length = 0;
}

void Clear_Rect3_Array(Rect3_Array* Target) {
	for (int C1 = 0; C1 < (*Target).Length; C1++) {
		Clear_Rect2_Array(&((*Target).Data[C1]));
	}
	free_c((*Target).Data);
	(*Target).Length = 0;
}

void Clear_File(const char* Path) {
	char Buffer[512];
	snprintf(Buffer, sizeof(Buffer), "Assets/Data/%s", Path);
	FILE* File = fopen(Path, "w");
	fclose(File);
}

void Cleanup_Assets() {
	free_texture(Core.Game_Texture);
	for (int C1 = 0; C1 < LDE_FONTS; C1++) {
		TTF_CloseFont(Fonts.Faces[C1]);
	}
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		switch (Metadata.Machines[C1].Depth) {
		case 1:
			free_texture(Metadata.Machines[C1].Texture1);
			break;
		case 2:
			Clear_Texture_Array(&Metadata.Machines[C1].Texture2);
			break;
		case 3:
			Clear_Texture2_Array(&Metadata.Machines[C1].Texture3);
			break;
		}
		free_c(Metadata.Machines[C1].Name);
		free_c(Metadata.Machines[C1].Path);
	}
	free_c(Cache.FPS_Cache);
	free_texture(Textures.Logo1);
	free_texture(Textures.Logo2);
	free_texture(Textures.CMD_Warning1);
	free_texture(Textures.CMD_Warning2);
	free_texture(Textures.Terminal_Prompt);
	free_texture(Textures.Price_Header);
	free_texture(Textures.CMD_Warning1);
	free_texture(Textures.CMD_Warning2);
	Clear_Texture_Array(&Textures.Tool);
	Clear_Texture_Array(&Textures.Help_Content);
	Clear_Texture_Array(&Textures.Door);
	free_texture(Textures.Recipe_Content);
	Clear_Texture3_Array(&Textures.Item_Labels);
	Clear_Rect3_Array(&Rects.Item_Labels);
	Clear_Texture3_Array(&Textures.Subcategories);
	Clear_Rect3_Array(&Rects.Subcategories);
	Clear_Texture3_Array(&Textures.Subcontents);
	Clear_Rect3_Array(&Rects.Subcontents);
	Clear_Texture2_Array(&Textures.Tutorials);
	Clear_Rect2_Array(&Rects.Tutorials);
	Clear_Texture2_Array(&Textures.Cheats);
	Clear_Rect2_Array(&Rects.Cheats);
	Clear_Texture2_Array(&Textures.New);
	Clear_Rect2_Array(&Rects.New);
	Clear_Texture2_Array(&Textures.Load);
	Clear_Rect2_Array(&Rects.Load);
	Clear_Texture2_Array(&Textures.Clear);
	Clear_Rect2_Array(&Rects.Clear);
	Clear_Texture2_Array(&Textures.Categories);
	Clear_Rect2_Array(&Rects.Categories);
	Clear_Texture_Array(&Textures.Error_Exit);
	free_c(Rects.Error_Exit.Data);
	Clear_Texture2_Array(&Textures.MSP_Buttons);
	Clear_Rect2_Array(&Rects.MSP_Buttons);
	Clear_Texture2_Array(&Textures.SD_Buttons);
	Clear_Rect2_Array(&Rects.SD_Buttons);
	Clear_Texture2_Array(&Textures.HX_Buttons);
	Clear_Rect2_Array(&Rects.HX_Buttons);
	Clear_Texture2_Array(&Textures.TT_Buttons);
	Clear_Rect2_Array(&Rects.TT_Buttons);
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
	free_c(Rects.Clear_Tutorial.Data);
	Clear_Texture_Array(&Textures.Settings_Label);
	free_c(Rects.Settings_Label.Data);
	Clear_Texture_Array(&Textures.Save_Settings);
	free_c(Rects.Save_Settings.Data);
	Clear_Texture_Array(&Textures.Arrow);
	Clear_Texture_Array(&Textures.S_Dock);
	Clear_Texture_Array(&Textures.Tunnel);
	free_c(Rects.Tunnel.Data);
	Clear_Texture_Array(&Textures.Return);
	free_c(Rects.Return.Data);
	Clear_Texture_Array(&Textures.New_Game);
	free_c(Rects.New_Game.Data);
	Clear_Texture_Array(&Textures.Settings);
	free_c(Rects.Settings.Data);
	Clear_Texture_Array(&Textures.Update_Logs);
	free_c(Rects.Update_Logs.Data);
	Clear_Texture_Array(&Textures.Credits);
	free_c(Rects.Credits.Data);
	Clear_Texture_Array(&Textures.Quit_Game);
	free_c(Rects.Quit_Game.Data);
	Clear_Texture_Array(&Textures.Apply);
	free_c(Rects.Apply.Data);
	Clear_Texture_Array(&Textures.Cancel);
	free_c(Rects.Cancel.Data);
	Clear_Texture_Array(&Textures.Next_Day);
	free_c(Rects.Next_Day.Data);
	Clear_Texture_Array(&Textures.Quirk);
	Clear_Texture_Array(&Textures.Quirk_Label);
	free_texture(Textures.Emblem);
	free_texture(Textures.Crosshair);
	free_texture(Textures.Cursor_Core);
	free_texture(Textures.Sapling);
	free_texture(Textures.Node);
	free_texture(Textures.Log_Background);
	free_texture(Textures.Saveloader);
	free_texture(Textures.Help_Sidebutton);
	free_texture(Textures.Save_Sidebutton);
	free_texture(Textures.Recipe_Sidebutton);
	free_texture(Textures.Exit_Sidebutton);
	free_texture(Textures.R_Flash);
	Clear_Texture_Array(&Textures.A_Bubble);
	free_texture(Textures.Floor_Texture);
	free_texture(Textures.Frame_Texture);
	free_texture(Textures.Tile_Texture);
	Clear_Texture_Array(&Textures.Submarine);
	free_texture(Textures.Scrap);
	Clear_Texture2_Array(&Textures.Confirmation);
	Clear_Rect2_Array(&Rects.Confirmation);
	Clear_Texture_Array(&Textures.Pyramid);
	free_texture(Textures.Mesh);
	Clear_Texture_Array(&Textures.Items);
	free_texture(Textures.None_Item);
	Clear_Texture_Array(&Textures.Fire);
	Clear_Texture_Array(&Textures.None);
	Clear_Texture_Array(&Cache.Wire_Cache);
	free_texture(Cache.Blueprint_Cache);
	Clear_Texture2_Array(&Cache.Log_Cache);
	Clear_Rect2_Array(&Cache.Log_Rectangles);
	free_c(Metadata.Machines);
	Free_Items();
	Free_Text();
}