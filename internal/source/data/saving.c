#include <data.h>

char* Get_Path_PKG(int Slot) {
	char* Yield = malloc(sizeof(char) * 23);
	strcpy(Yield, "Assets/Data/slot");
	Yield[16] = (char)Slot + '0';
	Yield[17] = '.';
	Yield[18] = 'p';
	Yield[19] = 'k';
	Yield[20] = 'g';
	Yield[21] = '\0';
	return Yield;
}

void Get_Filesizes() {
	for (int Counter = 0; Counter < 4; Counter++) {
		char* Path = Get_Path_PKG(Counter + 1);
		FILE* File = fopen(Path, "rb");
		fseek(File, 0L, SEEK_END);
		Core.Save_Filesizes[Counter] = ftell(File);
		fclose(File);
		free_c(Path);
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
	char* Path = Get_Path_PKG(Slot);
	FILE* File = fopen(Path, "wb");
	free_c(Path);
	if (File == NULL) {
		return false;
	}
	fputc((uint8_t)Data.Version, File);
	fputc((uint8_t)Data.Day, File);
	fputc((uint8_t)Data.CMD_Placed, File);
	fwrite(&(uint16_t){ Data.Time }, sizeof(uint16_t), 1, File);
	fwrite(&(uint64_t){ Data.Funds }, sizeof(uint64_t), 1, File);
	Write_2D_Array(Data.Visual_Grid, File);
	Write_2D_Array(Data.Connection_Grid, File);
	Write_2D_Array(Data.Behavior_Grid, File);
	Write_2D_Array(Data.Wiring_Grid, File);
	Write_2D_Array(Data.Plumbing_Grid, File);
	Write_2D_Array(Data.Items_Grid, File);
	Write_2D_Array(Data.Temperature_Grid, File);
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			for (int Z = 0; Z < 3; Z++) {
				fwrite(&(double){ Data.Animation_Grid[X][Y][Z] }, sizeof(double), 1, File);
			}
		}
	}
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			for (int Z = 0; Z < 7; Z++) {
				fwrite(&(double){ Data.Data_Grid[X][Y][Z] }, sizeof(double), 1, File);
			}
		}
	}
	for (int X = 0; X < LDE_GRIDSIZE; X++) {
		for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
			for (int Z = 0; Z < 16; Z++) {
				fwrite(&(double){ Data.Settings_Grid[X][Y][Z] }, sizeof(double), 1, File);
			}
		}
	}
	fclose(File);
	return true;
}

bool Load_Data(int Slot) {
	char* Path = Get_Path_PKG(Slot);
	FILE* File = fopen(Path, "rb");
	free_c(Path);
	if (File == NULL) {
		return false;
	}
	uint8_t Version = (uint8_t)fgetc(File);
	if (Version == 0) {
		Data.Day = (uint8_t)fgetc(File);
		Data.CMD_Placed = (bool)fgetc(File);
		fread(&Data.Time, sizeof(uint16_t), 1, File);
		fread(&Data.Funds, sizeof(uint64_t), 1, File);
		Read_2D_Array(Data.Visual_Grid, File);
		Read_2D_Array(Data.Connection_Grid, File);
		Read_2D_Array(Data.Behavior_Grid, File);
		Read_2D_Array(Data.Wiring_Grid, File);
		Read_2D_Array(Data.Plumbing_Grid, File);
		Read_2D_Array(Data.Items_Grid, File);
		Read_2D_Array(Data.Temperature_Grid, File);
		for (int X = 0; X < LDE_GRIDSIZE; X++) {
			for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
				for (int Z = 0; Z < 3; Z++) {
					fread(&Data.Animation_Grid[X][Y][Z], sizeof(double), 1, File);
				}
			}
		}
		for (int X = 0; X < LDE_GRIDSIZE; X++) {
			for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
				for (int Z = 0; Z < 7; Z++) {
					fread(&Data.Data_Grid[X][Y][Z], sizeof(double), 1, File);
				}
			}
		}
		for (int X = 0; X < LDE_GRIDSIZE; X++) {
			for (int Y = 0; Y < LDE_GRIDSIZE; Y++) {
				for (int Z = 0; Z < 16; Z++) {
					fread(&Data.Settings_Grid[X][Y][Z], sizeof(double), 1, File);
				}
			}
		}
	}
	fclose(File);
	Preclear_Temporaries();
	return true;
}