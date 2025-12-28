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
        free(Path);
	}
}

bool Save_Data(int Slot) {
    char* Path = Get_Path_PKG(Slot);
    FILE* File = fopen(Path, "wb");
    free(Path);
    if (File == NULL) {
        return false;
    }
    fputc((uint8_t)Data.Version, File);
    fputc((uint8_t)Data.Day, File);
    fputc((uint8_t)Data.CMD_Placed, File);
    fwrite(&(uint16_t){ Data.Time }, sizeof(uint16_t), 1, File);
    fwrite(&(uint64_t){ Data.Funds }, sizeof(uint64_t), 1, File);
    fclose(File);
	return true;
}

bool Load_Data(int Slot) {
    char* Path = Get_Path_PKG(Slot);
    FILE* File = fopen(Path, "rb");
    free(Path);
    if (File == NULL) {
        return false;
    }
    uint8_t Version = (uint8_t)fgetc(File);
    if (Version == 0) {
        Data.Day = (uint8_t)fgetc(File);
        Data.CMD_Placed = (bool)fgetc(File);
        fread(&Data.Time, sizeof(uint16_t), 1, File);
        fread(&Data.Funds, sizeof(uint64_t), 1, File);
    }
    fclose(File);
	Preclear_Temporaries();
	return true;
}