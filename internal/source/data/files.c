#include <data.h>

char* Get_Path(int Slot) {
    char* Yield = malloc(sizeof(char) * 23);
    strcpy(Yield, "Assets/Data/Slot");
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
		char* Path = Get_Path(Counter + 1);
        printf("%s\n", Path);
        FILE* File = fopen(Path, "rb");
        fseek(File, 0L, SEEK_END);
		Core.Save_Filesizes[Counter] = ftell(File);
		fclose(File);
        free(Path);
	}
}

bool Save_Data(int Slot) {
    char* Path = Get_Path(Slot);
	Package0 Package = {
        .Funds = (uint64_t)Data.Funds,
        .Time = (uint16_t)Data.Time,
        .Day = (uint8_t)Data.Day,
        .CMD_Placed = (uint8_t)Data.CMD_Placed
    };
    FILE* File = fopen(Path, "wb");
    free(Path);
    uint8_t Subversion = (uint8_t)Data.Version;
    fwrite(&Subversion, sizeof(uint8_t), 1, File);
    fwrite(&Package, sizeof(Package), 1, File);
    if (File == NULL) {
        return false;
    }
    fclose(File);
	return true;
}

bool Load_Data(int Slot) {
    char* Path = Get_Path(Slot);
    printf("%s", Path);
    FILE* File = fopen(Path, "rb");
    free(Path);
    if (File == NULL) {
        return false;
    }
    uint8_t Version = 0;
    fread(&Version, sizeof(Version), 1, File);
    if (Version == 0) {
        Package0 Package;
        fread(&Package, sizeof(Package), 1, File);
        Data.Funds = Package.Funds;
        Data.Time = Package.Time;
        Data.Day = Package.Day;
        Data.CMD_Placed = (bool)Package.CMD_Placed;
    }
    fclose(File);
	Preclear_Temporaries();
	return true;
}