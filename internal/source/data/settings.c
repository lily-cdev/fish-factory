#include <data.h>
#define VERSION 0

bool Save_Settings() {
	char Path[] = "Assets/Data/settings.pkg";
	FILE* File = fopen(Path, "wb");
	if (File == NULL) {
		return false;
	}
	fputc((uint8_t)VERSION, File);
	fputc((uint8_t)Settings.Anti_Aliasing, File);
	fputc((uint8_t)Settings.VSync, File);
	fputc((uint8_t)Settings.Fullscreen, File);
	fputc((uint8_t)Settings.Screen_Size, File);
	fputc((uint8_t)Settings.Volume, File);
	fputc((uint8_t)Settings.Raw_FPS, File);
	for (int Counter = 0; Counter < LDE_KEYBINDS; Counter++) {
		fwrite(&(uint32_t){ Keybinds.Keybind_List[Counter] }, sizeof(uint32_t), 1, File);
	}
	fclose(File);
	return true;
}

void Load_Settings() {
	char Path[] = "Assets/Data/settings.pkg";
	FILE* File = fopen(Path, "rb");
	if (File != NULL) {
		fseek(File, 0L, SEEK_END);
		if (ftell(File) > 0) {
			rewind(File);
			int Version = (int)fgetc(File);
			if (Version == VERSION) {
				Settings.Anti_Aliasing = fgetc(File);
				Settings.VSync = fgetc(File);
				Settings.Fullscreen = fgetc(File);
				Settings.Screen_Size = fgetc(File);
				Settings.Volume = fgetc(File);
				Settings.Raw_FPS = fgetc(File);
				for (int Counter = 0; Counter < LDE_KEYBINDS; Counter++) {
					fread(&Keybinds.Keybind_List[Counter], sizeof(uint32_t), 1, File);
				}
				fclose(File);
				return;
			}
		}
		fclose(File);
	}
	Clear_File("settings.pkg");
	SDL_DisplayID Index = SDL_GetDisplayForWindow(Core.Window);
	const SDL_DisplayMode* Display = SDL_GetDesktopDisplayMode(Index);
	for (int Counter = 0; Counter < LDE_SUPPORTEDRESOLUTIONS; Counter++) {
		if (Display->w >= Metadata.Supported_Resolutions[Counter].X &&
			Display->h >= Metadata.Supported_Resolutions[Counter].Y) {
			Settings.Screen_Size++;
		} else {
			break;
		}
	}
	if (Settings.Screen_Size == 0) {
		Settings.Screen_Size = 1;
	}
	Save_Settings();
}

void Clear_Settings() {
	Interface.Slider_Positions[0] = Settings.Screen_Size - 1;
	Interface.Slider_Positions[4] = Settings.Raw_FPS;
	Interface.Slider_Positions[5] = Settings.Volume;
	Interface.Slider_Positions[6] = Settings.Fullscreen;
	Settings.AA_Temporary = (bool)(Settings.Anti_Aliasing);
	Settings.VS_Temporary = (bool)(Settings.VSync);
	for (int Counter = 0; Counter < LDE_KEYBINDS; Counter++) {
		Keybinds.Keybind_Settings[Counter] = Keybinds.Keybind_List[Counter];
	}
}

void Recalibrate_Settings() {
	Settings.Screen_Size = Interface.Slider_Positions[0] + 1;
	Settings.Raw_FPS = Interface.Slider_Positions[4];
	Settings.Volume = Interface.Slider_Positions[5];
	Settings.Fullscreen = Interface.Slider_Positions[6];
	Settings.Anti_Aliasing = (int)(Settings.AA_Temporary);
	Settings.VSync = (int)(Settings.VS_Temporary);
	for (int Counter = 0; Counter < LDE_KEYBINDS; Counter++) {
		Keybinds.Keybind_List[Counter] = Keybinds.Keybind_Settings[Counter];
	}
	Reload_All();
}