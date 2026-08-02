#include <prepping.h>

static bool Yield;

void Load_TXT(const char* Path, char* Input[], int Lines) {
	char Carrier[512];
	snprintf(Carrier, sizeof(Carrier), "assets/data/%s.txt", Path);
	FILE* File = fopen(Carrier, "r");
	if (File == NULL) {
		Yield = false;
	}
	char Buffer[512];
	size_t Length = 0;
	size_t Size;
	for (int C1 = 0; C1 < Lines; C1++) {
		fgets(Buffer, sizeof(Buffer), File);
		int Length = strlen(Buffer);
		if (Buffer[Length - 1] == '\n') {
			Length--;
		}
		Input[C1] = malloc(Length + 1);
		strncpy(Input[C1], Buffer, Length);
		Input[C1][Length] = '\0';
	}
	fclose(File);
}

void Load_Full(const char* Path, char** Input) {
	char Carrier[512];
	snprintf(Carrier, sizeof(Carrier), "assets/data/%s.txt", Path);
	FILE* File = fopen(Carrier, "r");
	if (File == NULL) {
		Yield = false;
		return;
	}
	fseek(File, 0L, SEEK_END);
	uint64_t Length = ftell(File);
	*Input = malloc(Length + 1);
	if (*Input == NULL) {
		Yield = false;
		fclose(File);
		return;
	}
	rewind(File);
	fread(*Input, 1, Length, File);
	(*Input)[Length] = '\0';
	fclose(File);
}

bool Load_Text() {
	Yield = true;
	int Index = SDL_GetDisplayForWindow(Core.Window);
	const SDL_DisplayMode* Display = SDL_GetDesktopDisplayMode(Index);
	snprintf(Metadata.Monitor_Size, sizeof(Metadata.Monitor_Size), "%dx%d", Display->w, Display->h);
	char Resolution_Names[ktn_supported_res][8] = { "nHD", "HD", "FHD", "QHD", "QHD+", "4K" };
	char Buffer[64];
	for (int C1 = 0; C1 < ktn_supported_res; C1++) {
		if (Display->w == Metadata.Supported_Resolutions[C1].X && Display->h == Metadata.Supported_Resolutions[C1].Y) {
			snprintf(Buffer, sizeof(Buffer), "%s (%s)", Metadata.Monitor_Size, Resolution_Names[C1]);
			break;
		}
	}
	snprintf(Metadata.Monitor_Size, sizeof(Metadata.Monitor_Size), "Detected Resolution: %s", Buffer);
	Load_TXT("buttons", Metadata.Buttons, ktn_buttons);
	Load_TXT("keybinds", Keybinds.Keybind_Texts, ktn_keybinds);
	Load_Full("changes", &Metadata.Logs[Changelog]);
	Load_Full("credits", &Metadata.Logs[Credits]);
	Load_Full("license", &Metadata.Logs[Legal]);
    return Yield;
}

void Free_Text() {
    for (int C1 = 0; C1 < ktn_buttons; C1++) {
		ktn_free(Metadata.Buttons[C1]);
	}
	for (int C1 = 0; C1 < ktn_logs; C1++) {
		ktn_free(Metadata.Logs[C1]);
	}
	for (int C1 = 0; C1 < ktn_keybinds; C1++) {
		ktn_free(Keybinds.Keybind_Texts[C1]);
	}
}