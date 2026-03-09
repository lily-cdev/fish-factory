#include <data.h>

void Get_Filesizes() {
	for (int C1 = 0; C1 < 4; C1++) {
		char Path[64];
		snprintf(Path, sizeof(Path), "Assets/Data/slot%i.pkg", C1 + 1);
		FILE* File = fopen(Path, "rb");
		if (File == NULL) {
			Core.Save_Filesizes[C1] = 0;
			continue;
		}
		fseek(File, 0L, SEEK_END);
		Core.Save_Filesizes[C1] = ftell(File);
		fclose(File);
	}
}

void Write_2D_Array(int Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], FILE* File) {
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			fwrite(&(int32_t){ Grid[X][Y] }, sizeof(int32_t), 1, File);
		}
	}
}

void Read_2D_Array(int Grid[LDE_GRIDSIZE][LDE_GRIDSIZE], FILE* File) {
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			fread(&Grid[X][Y], sizeof(int32_t), 1, File);
		}
	}
}

bool Save_Data(int Slot) {
	char Path[64];
	snprintf(Path, sizeof(Path), "Assets/Data/slot%i.pkg", Slot);
	FILE* File = fopen(Path, "wb");
	if (File == NULL) {
		return false;
	}
	fputc((uint8_t)Data.Version, File);
	fputc((uint8_t)Data.Day, File);
	fputc((uint8_t)Data.CMD_Placed, File);
	fwrite(&(uint16_t){ Data.Time }, sizeof(uint16_t), 1, File);
	fwrite(&(int64_t){ Data.Funds }, sizeof(uint64_t), 1, File);
	Write_2D_Array(Data.Visual_Grid, File);
	Write_2D_Array(Data.Behavior_Grid, File);
	Write_2D_Array(Data.Wiring_Grid, File);
	Write_2D_Array(Data.Plumbing_Grid, File);
	Write_2D_Array(Data.Items_Grid, File);
	Write_2D_Array(Data.Temperature_Grid, File);
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			for (int Z = 0; Z < 3; Z++) {
				fwrite(&(float){ Data.Animation_Grid[X][Y][Z] }, sizeof(float), 1, File);
			}
		}
	}
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			for (int Z = 0; Z < 7; Z++) {
				fwrite(&(float){ Data.Data_Grid[X][Y][Z] }, sizeof(float), 1, File);
			}
		}
	}
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			for (int Z = 0; Z < 16; Z++) {
				fwrite(&(float){ Data.Settings_Grid[X][Y][Z] }, sizeof(float), 1, File);
			}
		}
	}
	fclose(File);
	return true;
}

bool Load_Data(int Slot) {
	Reset_Statistics();
	char Path[64];
	snprintf(Path, sizeof(Path), "Assets/Data/slot%i.pkg", Slot);
	FILE* File = fopen(Path, "rb");
	if (File == NULL) {
		return false;
	}
	fseek(File, 0L, SEEK_END);
	if (ftell(File) > 0) {
		rewind(File);
		uint8_t Version = (uint8_t)fgetc(File);
		if (Version == 0) {
			Data.Day = (uint8_t)fgetc(File);
			Data.CMD_Placed = (bool)fgetc(File);
			fread(&Data.Time, sizeof(uint16_t), 1, File);
			fread(&Data.Funds, sizeof(int64_t), 1, File);
			Read_2D_Array(Data.Visual_Grid, File);
			Read_2D_Array(Data.Behavior_Grid, File);
			Read_2D_Array(Data.Wiring_Grid, File);
			Read_2D_Array(Data.Plumbing_Grid, File);
			Read_2D_Array(Data.Items_Grid, File);
			Read_2D_Array(Data.Temperature_Grid, File);
			for (int X = 0; X < LDE_GRIDSIZE; X++) {
				for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
					for (int Z = 0; Z < 3; Z++) {
						fread(&Data.Animation_Grid[X][Y][Z], sizeof(float), 1, File);
					}
				}
			}
			for (int X = 0; X < LDE_GRIDSIZE; X++) {
				for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
					for (int Z = 0; Z < 7; Z++) {
						fread(&Data.Data_Grid[X][Y][Z], sizeof(float), 1, File);
					}
				}
			}
			for (int X = 0; X < LDE_GRIDSIZE; X++) {
				for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
					for (int Z = 0; Z < 16; Z++) {
						fread(&Data.Settings_Grid[X][Y][Z], sizeof(float), 1, File);
					}
				}
			}
		}
	} else {
		Reset_Statistics();
		Save_Data(Slot);
	}
	fclose(File);
	Preclear_Temporaries();
	return true;
}

void Reset_Tile(Point Pos) {
	Data.Visual_Grid[Pos.X][Pos.Y] = 0;
	Data.Behavior_Grid[Pos.X][Pos.Y] = LDE_INVALID;
	Data.Wiring_Grid[Pos.X][Pos.Y] = LDE_INVALID;
	Data.Plumbing_Grid[Pos.X][Pos.Y]= LDE_INVALID;
	Data.Items_Grid[Pos.X][Pos.Y] = LDE_INVALID;
	Data.Temperature_Grid[Pos.X][Pos.Y] = LDE_ROOMTEMP;
	memset(Data.Data_Grid[Pos.X][Pos.Y], 0, sizeof(Data.Data_Grid[Pos.X][Pos.Y]));
	Data.Data_Grid[Pos.X][Pos.Y][4] = LDE_INVALID;
	for (int C1 = 0; C1 < sizeof(Data.Settings_Grid[Pos.X][Pos.Y]) / sizeof(Data.Settings_Grid[Pos.X][Pos.Y][0]); C1++) {
		Data.Settings_Grid[Pos.X][Pos.Y][C1] = LDE_INVALID;
	}
}

void Reset_Statistics() {
	Data.Funds = 750;
	Data.CMD_Placed = false;
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			Reset_Tile((Point){ X, Y });
		}
	}
	Clear_Bridges(&Wires);
	Clear_Bridges(&Pipes);
	Preclear_Temporaries();
	Save_Data(Core.Selected_Save);
}

void Reload_All() {
	uint64_t Start = SDL_GetTicks();
	Cleanup_Assets();
	Free_Sounds();
	SDL_SetWindowSize(Core.Window, Settings.Screen_Size * 640, Settings.Screen_Size * 360);
	Preload_Fonts();
	Load_Sounds();
	Render_Loadscreen();
	SDL_SetWindowPosition(Core.Window, 0, 0);
	for (int C1 = 0; C1 < LDE_ITEMS; C1++) {
		strncpy(Interface.Slider_Texts[9][C1], Preset_Items.Item_List[C1].Display_Name, sizeof(Interface.Slider_Texts[9][
			C1]));
	}
	strncpy(Interface.Slider_Texts[9][LDE_ITEMS], NULLSTRING, sizeof(Interface.Slider_Texts[9][LDE_ITEMS]));
	Adjust_Sound(Settings.Volume * 0.01f);
	Interface.Frame_Rate = (int)(pow(2, Settings.Raw_FPS) * 15);
	switch (Settings.Fullscreen) {
	case 0:
		SDL_SetWindowBordered(Core.Window, true);
		SDL_SetWindowFullscreen(Core.Window, false);
		break;
	case 1:
		SDL_SetWindowBordered(Core.Window, false);
		SDL_SetWindowFullscreen(Core.Window, false);
		break;
	case 2:
		SDL_SetWindowBordered(Core.Window, false);
		SDL_SetWindowFullscreen(Core.Window, true);
		break;
	default:
		break;
	}
	Scaling_Quality = (Settings.Anti_Aliasing == 0) ? SDL_SCALEMODE_NEAREST : SDL_SCALEMODE_LINEAR;
	(Settings.VSync == 0) ? SDL_SetRenderVSync(Core.Renderer, 0) : SDL_SetRenderVSync(Core.Renderer, 1);
	Preload_Assets();
	Preload_Noise();
	float Loading_Time = (SDL_GetTicks() - Start) / 1000.0;
	//do smth with loading time ig
}