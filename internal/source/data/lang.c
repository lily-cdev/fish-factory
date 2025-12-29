#include <data.h>

bool Load_TXT(String1 Input[], int Lines, const char* Path) {
	char Carrier[512];
	snprintf(Carrier, sizeof(Carrier), "%s%s", Metadata.Data_Path.Data, Path);
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
		Input[Counter].Length = Length;
		Input[Counter].Data = malloc(sizeof(char) * Length);
		strcpy(Input[Counter].Data, Buffer);
		Input[Counter].Data[Length - 1] = '\0';
	}
	return true;
}

bool Load_Text() {
	Metadata.Image_Path.Data = "Assets/Core/Images/";
	Metadata.Image_Path.Length = 20;
	Metadata.Data_Path.Data = "Assets/Data/";
	Metadata.Data_Path.Length = 13;
    bool Yield = Load_TXT(Metadata.Names, LDE_MACHINES, "names.txt");
	Yield = Load_TXT(Metadata.Descriptions, LDE_MACHINES, "descriptions.txt");
	Yield = Load_TXT(Metadata.Categories, LDE_CATEGORIES, "categories.txt");
	Yield = Load_TXT(Metadata.Subcategories, LDE_SUBCATEGORIES, "subcategories.txt");
	Yield = Load_TXT(Metadata.Buttons, LDE_BUTTONS, "buttons.txt");
    return Yield;
}

void Free_Text() {
    for (int Counter = 0; Counter < LDE_MACHINES; Counter++) {
    	free_d(Metadata.Names[Counter]);
        free_d(Metadata.Descriptions[Counter]);
    }
    for (int Counter = 0; Counter < LDE_CATEGORIES; Counter++) {
		free_d(Metadata.Categories[Counter]);
	}
    for (int Counter = 0; Counter < LDE_SUBCATEGORIES; Counter++) {
		free_d(Metadata.Subcategories[Counter]);
	}
    for (int Counter = 0; Counter < LDE_BUTTONS; Counter++) {
		free_d(Metadata.Buttons[Counter]);
	}
	for (int Counter = 0; Counter < LDE_TTSLIDES; Counter++) {
		Free_String2(&Metadata.TT_Texts[Counter]);
		Free_String3(&Metadata.TT_Parameters[Counter]);
		free_c(Metadata.TT_Types[Counter]);
	}
}