#include <data.h>

bool Yield;

void Load_TXT(const char* Path, char* Input[], int Lines) {
	char Carrier[512];
	snprintf(Carrier, sizeof(Carrier), "Assets/Data/%s.txt", Path);
	FILE* File = fopen(Carrier, "r");
	if (File == NULL) {
		Yield = false;
	}
	char Buffer[512];
	size_t Length = 0;
	size_t Size;
	for (int Counter = 0; Counter < Lines; Counter++) {
		fgets(Buffer, sizeof(Buffer), File);
		int Length = strlen(Buffer);
		if (Buffer[Length - 1] == '\n') {
			Length--;
		}
		Input[Counter] = malloc(sizeof(char) * (Length + 1));
		strcpy(Input[Counter], Buffer);
		Input[Counter][Length] = '\0';
	}
	fclose(File);
}

void Load_Full(const char* Path, char** Input) {
	char Carrier[512];
	snprintf(Carrier, sizeof(Carrier), "Assets/Data/%s.txt", Path);
	FILE* File = fopen(Carrier, "r");
	if (File == NULL) {
		Yield = false;
		return;
	}
	fseek(File, 0L, SEEK_END);
	uint64_t Length = ftell(File);
	*Input = malloc(sizeof(char) * (Length + 1));
	if (*Input == NULL) {
		Yield = false;
		fclose(File);
		return;
	}
	rewind(File);
	fread(*Input, sizeof(char), Length, File);
	(*Input)[Length] = '\0';
	fclose(File);
}

bool Load_Text() {
	Yield = true;
	int Index = SDL_GetDisplayForWindow(Core.Window);
	const SDL_DisplayMode* Display = SDL_GetDesktopDisplayMode(Index);
	snprintf(Metadata.Monitor_Size, sizeof(Metadata.Monitor_Size), "%dx%d", Display->w, Display->h);
	char Resolution_Names[LDE_SUPPORTEDRESOLUTIONS][8] = { "nHD", "HD", "FHD", "QHD", "QHD+", "4K" };
	char Buffer[64];
	for (int Counter = 0; Counter < LDE_SUPPORTEDRESOLUTIONS; Counter++) {
		if (Display->w == Metadata.Supported_Resolutions[Counter].X &&
			Display->h == Metadata.Supported_Resolutions[Counter].Y) {
			snprintf(Buffer, sizeof(Buffer), "%s (%s)", Metadata.Monitor_Size, Resolution_Names[Counter]);
			break;
		}
	}
	snprintf(Metadata.Monitor_Size, sizeof(Metadata.Monitor_Size), "Detected Resolution: %s", Buffer);
	Metadata.Heating_Machines = malloc(sizeof(int) * 3);
	Metadata.Heating_Machines[0] = Incinerator;
	Metadata.Heating_Machines[1] = Geo_Well;
	Metadata.Heating_Machines[2] = LDE_TERMINATOR;
	Metadata.Irradiating_Machines = malloc(sizeof(int) * 2);
	Metadata.Irradiating_Machines[0] = RTG;
	Metadata.Irradiating_Machines[1] = LDE_TERMINATOR;
    Load_TXT("names", Metadata.Names, LDE_MACHINES);
	Load_TXT("descriptions", Metadata.Descriptions, LDE_MACHINES);
	Load_TXT("categories", Metadata.Categories, LDE_CATEGORIES);
	Load_TXT("subcategories", Metadata.Subcategories, LDE_SUBCATEGORIES);
	Load_TXT("buttons", Metadata.Buttons, LDE_BUTTONS);
	Load_TXT("keybinds", Keybinds.Keybind_Texts, LDE_KEYBINDS);
	Load_Full("changes", &Metadata.Logs[Changelog]);
	Load_Full("credits", &Metadata.Logs[Credits]);
	Load_Full("license", &Metadata.Logs[Legal]);
    return Yield;
}

void Free_Text() {
    for (int Counter = 0; Counter < LDE_MACHINES; Counter++) {
    	free_c(Metadata.Names[Counter]);//sus
        free_c(Metadata.Descriptions[Counter]);
    }
    for (int Counter = 0; Counter < LDE_CATEGORIES; Counter++) {
		free_c(Metadata.Categories[Counter]);
	}
    for (int Counter = 0; Counter < LDE_SUBCATEGORIES; Counter++) {
		free_c(Metadata.Subcategories[Counter]);
	}
    for (int Counter = 0; Counter < LDE_BUTTONS; Counter++) {
		free_c(Metadata.Buttons[Counter]);
	}
	for (int Counter = 0; Counter < LDE_LOGS; Counter++) {
		free_c(Metadata.Logs[Counter]);
	}
	for (int Counter = 0; Counter < LDE_KEYBINDS; Counter++) {
		free_c(Keybinds.Keybind_Texts[Counter]);
	}
	free_c(Metadata.Heating_Machines);
	free_c(Metadata.Irradiating_Machines);
	Clear_Rect2_Array(&Cache.Log_Rectangles);
}