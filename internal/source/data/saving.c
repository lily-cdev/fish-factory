#include <data.h>
#include <items.h>

void Get_Filesizes() {
	for (int C1 = 0; C1 < 4; C1++) {
		char Path[64];
		snprintf(Path, sizeof(Path), "assets/data/slot%i.pkg", C1);
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

void Write_2D_Array(int Grid[ktn_grid_size][ktn_grid_size], FILE* File) {
	for (int X = 0; X < ktn_grid_size; X++) {
		for (int Y = 0; Y < ktn_grid_size; Y++) {
			fwrite(&(int32_t){ Grid[X][Y] }, sizeof(int32_t), 1, File);
		}
	}
}

void Read_2D_Array(int Grid[ktn_grid_size][ktn_grid_size], FILE* File) {
	for (int X = 0; X < ktn_grid_size; X++) {
		for (int Y = 0; Y < ktn_grid_size; Y++) {
			fread(&Grid[X][Y], sizeof(int32_t), 1, File);
		}
	}
}

bool Save_Data(int Slot) {
	char Path[64];
	snprintf(Path, sizeof(Path), "assets/data/slot%i.pkg", Slot);
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
	for (int X = 0; X < ktn_grid_size; X++) {
		for (int Y = 0; Y < ktn_grid_size; Y++) {
			for (int Z = 0; Z < 3; Z++) {
				fwrite(&(float){ Data.Animation_Grid[X][Y][Z] }, sizeof(float), 1, File);
			}
		}
	}
	for (int X = 0; X < ktn_grid_size; X++) {
		for (int Y = 0; Y < ktn_grid_size; Y++) {
			for (int Z = 0; Z < 7; Z++) {
				fwrite(&(float){ Data.Data_Grid[X][Y][Z] }, sizeof(float), 1, File);
			}
		}
	}
	for (int X = 0; X < ktn_grid_size; X++) {
		for (int Y = 0; Y < ktn_grid_size; Y++) {
			for (int Z = 0; Z < 16; Z++) {
				fwrite(&(float){ Data.Settings_Grid[X][Y][Z] }, sizeof(float), 1, File);
			}
		}
	}
	fwrite(&Wires.Length, sizeof(int64_t), 1, File);
	fwrite(&Pipes.Length, sizeof(int64_t), 1, File);
	for (int C1 = 0; C1 < 2; C1++) {
		for (int C2 = 0; C2 < ((C1 == 0) ? Wires.Length : Pipes.Length); C2++) {
			Bridge Subbridge = ((C1 == 0) ? Wires.Data[C2] : Pipes.Data[C2]);
			fputc((char)Subbridge.Filled, File);
			fputc((char)Subbridge.X1, File);
			fputc((char)Subbridge.Y1, File);
			fputc((char)Subbridge.X2, File);
			fputc((char)Subbridge.Y2, File);
			fwrite(&(int16_t){ Subbridge.X_Offset }, sizeof(int16_t), 1, File);
			fwrite(&(int16_t){ Subbridge.Y_Offset }, sizeof(int16_t), 1, File);
			fputc((char)Subbridge.Orienation, File);
		}
	}
	fclose(File);
	return true;
}

bool Load_Data(int Slot) {
	char Path[64];
	snprintf(Path, sizeof(Path), "assets/data/slot%i.pkg", Slot);
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
			for (int X = 0; X < ktn_grid_size; X++) {
				for (int Y = 0; Y < ktn_grid_size; Y++) {
					for (int Z = 0; Z < 3; Z++) {
						fread(&Data.Animation_Grid[X][Y][Z], sizeof(float), 1, File);
					}
				}
			}
			for (int X = 0; X < ktn_grid_size; X++) {
				for (int Y = 0; Y < ktn_grid_size; Y++) {
					for (int Z = 0; Z < 7; Z++) {
						fread(&Data.Data_Grid[X][Y][Z], sizeof(float), 1, File);
					}
				}
			}
			for (int X = 0; X < ktn_grid_size; X++) {
				for (int Y = 0; Y < ktn_grid_size; Y++) {
					for (int Z = 0; Z < 16; Z++) {
						fread(&Data.Settings_Grid[X][Y][Z], sizeof(float), 1, File);
					}
				}
			}
			int64_t Limiters[2];
			fread(&Limiters[0], sizeof(int64_t), 1, File);
			fread(&Limiters[1], sizeof(int64_t), 1, File);
			Wires.Full_Size = 0;
			Pipes.Full_Size = 0;
			Wires.Length = 0;
			Pipes.Length = 0;
			for (int C1 = 0; C1 < 2; C1++) {
				for (int C2 = 0; C2 < Limiters[C1]; C2++) {
					Bridge Subbridge = { };
					Subbridge.Filled = (bool)fgetc(File);
					Subbridge.X1 = (int8_t)fgetc(File);
					Subbridge.Y1 = (int8_t)fgetc(File);
					Subbridge.X2 = (int8_t)fgetc(File);
					Subbridge.Y2 = (int8_t)fgetc(File);
					fread(&Subbridge.X_Offset, sizeof(int16_t), 1, File);
					fread(&Subbridge.Y_Offset, sizeof(int16_t), 1, File);
					Subbridge.Orienation = (int8_t)fgetc(File);
					Push_Bridge(((C1 == 0) ? &Wires : &Pipes), Subbridge);
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
	Data.Visual_Grid[pt(Pos)] = 0;
	Data.Behavior_Grid[pt(Pos)] = ktn_invalid;
	Data.Wiring_Grid[pt(Pos)] = ktn_invalid;
	Data.Plumbing_Grid[pt(Pos)] = ktn_invalid;
	Data.Items_Grid[pt(Pos)] = ktn_invalid;
	Data.Temperature_Grid[pt(Pos)] = ktn_room_temp;
	memset(Data.Data_Grid[pt(Pos)], 0, sizeof(Data.Data_Grid[pt(Pos)]));
	memset(Data.Animation_Grid[pt(Pos)], 0, sizeof(Data.Animation_Grid[pt(Pos)]));
	Data.Data_Grid[pt(Pos)][4] = ktn_invalid;
	for (int C1 = 0; C1 < sizeof(Data.Settings_Grid[pt(Pos)]) / sizeof(Data.Settings_Grid[pt(Pos)][0]); C1++) {
		Data.Settings_Grid[pt(Pos)][C1] = ktn_invalid;
	}
}

void Reset_Statistics() {
	Data.Funds = 750;
	Data.CMD_Placed = false;
	for (int X = 0; X < ktn_grid_size; X++) {
		for (int Y = 0; Y < ktn_grid_size; Y++) {
			Reset_Tile((Point){ X, Y });
		}
	}
	Clear_Bridges(&Wires);
	Clear_Bridges(&Pipes);
	Preclear_Temporaries();
	Save_Data(Core.Selected_Save);
}

void Reload_All(bool Initialized) {
	uint64_t Start = SDL_GetTicks();
	Core.Screensize = (Point_f){ ktn_fscale(640.0f), ktn_fscale(360.0f) };
	Core.Screenhalfsize = (Point_f){ ktn_fscale(320.0f), ktn_fscale(180.0f) };
	SDL_SetWindowSize(Core.Window, (int)Core.Screensize.X, (int)Core.Screensize.Y);
	SDL_SetWindowPosition(Core.Window, 0, 0);
	Preload_Fonts();
	Temporary.Spinner = Preload_Texture("core/images/ui/other/spinner");
	Temporary.Spinner_Rect = (SDL_FRect){
		Core.Screenhalfsize.X - ktn_fscale((Temporary.Spinner->w * 0.5f) / 6.0f),
		Core.Screenhalfsize.Y - ktn_fscale((Temporary.Spinner->h * 0.5f) / 6.0f),
		ktn_fscale(Temporary.Spinner->w / 6.0f),
		ktn_fscale(Temporary.Spinner->h / 6.0f)
	};
	Temporary.Load_Text = Render_Text(F_Logo, "loading assets", Colors.Abyss_Black);
	Temporary.Load_Text_Rect = (SDL_FRect){
		Core.Screenhalfsize.X - (Temporary.Load_Text->w * 0.5f),
		Core.Screenhalfsize.Y - (Temporary.Load_Text->h * 0.5f) - ktn_fscale((Temporary.Spinner->h * 1.5f) / 6.0f),
		(float)Temporary.Load_Text->w,
		(float)Temporary.Load_Text->h
	};
	if (Initialized) {
		Cleanup_Assets();
		Free_Sounds();
	}
	Load_XML();
	Prep_Items();
	Load_Text();
	Load_Sounds();
	for (int C1 = 0; C1 < Core.Items; C1++) {
		strncpy(Interface.Slider_Texts[9][C1], Metadata.Items[C1].Name, sizeof(Interface.Slider_Texts[9][C1]));
	}
	strncpy(Interface.Slider_Texts[9][Core.Items], ktn_null_string, sizeof(Interface.Slider_Texts[9][Core.Items]));
	Adjust_Sound(Settings.Volume * 0.01f);
	Interface.Frame_Rate = (int)(powf(2.0f, (float)Settings.Raw_FPS) * 15.0f);
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
	ktn_free_texture(Temporary.Spinner);
	ktn_free_texture(Temporary.Load_Text);
	float Loading_Time = (SDL_GetTicks() - Start) / 1000.0f;
	//do smth with loading time ig
}