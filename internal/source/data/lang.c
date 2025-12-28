#include <data.h>

void Load_Names(bool* Error) {
	FILE* File = fopen("Assets/Data/names.txt", "r");
	if (File == NULL) {
		*Error = false;
		return;
	}
	char Buffer[1024];
	size_t Length = 0;
	size_t Size;
	for (int Counter = 0; Counter < LDE_MACHINES; Counter++) {
		fgets(Buffer, sizeof(Buffer), File);
		int Length = strlen(Buffer) + 1;
		Metadata.Names[Counter].Length = Length - 1;
		Metadata.Names[Counter].Content = malloc(sizeof(char) * Length);
		Metadata.Names[Counter].Content[Length - 1] = '\0';
		strcpy(Metadata.Names[Counter].Content, Buffer);
	}
}

void Load_Descriptions(bool* Error) {
	FILE* File = fopen("Assets/Data/descriptions.txt", "r");
	if (File == NULL) {
		*Error = false;
		return;
	}
	char Buffer[1024];
	size_t Length = 0;
	size_t Size;
	for (int Counter = 0; Counter < LDE_MACHINES; Counter++) {
		fgets(Buffer, sizeof(Buffer), File);
		int Length = strlen(Buffer) + 1;
		Metadata.Descriptions[Counter].Length = Length - 1;
		Metadata.Descriptions[Counter].Content = malloc(sizeof(char) * Length);
		Metadata.Descriptions[Counter].Content[Length - 1] = '\0';
		strcpy(Metadata.Descriptions[Counter].Content, Buffer);
	}
}

bool Load_Text() {
    bool Yield = true;
    Load_Names(&Yield);
    Load_Descriptions(&Yield);
    return Yield;
}

void Free_Text() {
    for (int Counter = 0; Counter < LDE_MACHINES; Counter++) {
        if (Metadata.Names[Counter].Content != NULL) {
            free(Metadata.Names[Counter].Content);
        }
        if (Metadata.Descriptions[Counter].Content != NULL) {
            free(Metadata.Descriptions[Counter].Content);
        }
    }
}