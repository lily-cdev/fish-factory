#include <data.h>

bool Load_TXT(char* Input[], int Lines, const char* Path) {
	char Carrier[512];
	snprintf(Carrier, sizeof(Carrier), "%s%s", Metadata.Data_Path, Path);
	FILE* File = fopen(Carrier, "r");
	if (File == NULL) {
		return false;
	}
	char Buffer[512];
	size_t Length = 0;
	size_t Size;
	for (int Counter = 0; Counter < Lines; Counter++) {
		fgets(Buffer, sizeof(Buffer), File);
		int Length = strlen(Buffer);
		if (Counter == Lines - 1) {
			Length = strlen(Buffer) + 1;
		}
		Input[Counter] = malloc(sizeof(char) * Length);
		strcpy(Input[Counter], Buffer);
		Input[Counter][Length - 1] = '\0';
	}
	return true;
}

bool Load_Text() {
	Metadata.Image_Path = "Assets/Core/Images/";
	Metadata.Data_Path = "Assets/Data/";
    bool Yield = Load_TXT(Metadata.Names, LDE_MACHINES, "names.txt");
	Yield = Load_TXT(Metadata.Descriptions, LDE_MACHINES, "descriptions.txt");
	Yield = Load_TXT(Metadata.Categories, LDE_CATEGORIES, "categories.txt");
	Yield = Load_TXT(Metadata.Subcategories, LDE_SUBCATEGORIES, "subcategories.txt");
	Yield = Load_TXT(Metadata.Buttons, LDE_BUTTONS, "buttons.txt");
    return Yield;
}

void Free_Text() {
    for (int Counter = 0; Counter < LDE_MACHINES; Counter++) {
    	free_c(Metadata.Names[Counter]);
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
	for (int Counter = 0; Counter < LDE_TTSLIDES; Counter++) {
		Free_String2(&Metadata.TT_Texts[Counter]);
		Free_String3(&Metadata.TT_Parameters[Counter]);
		free_c(Metadata.TT_Types[Counter]);
	}
}