#include <prepping.h>

char* Get_File(char* Path) {
	char Carrier[128];
	snprintf(Carrier, sizeof(Carrier), "assets/%s.xml", Path);
	FILE* File = fopen(Carrier, "r");
	if (File == NULL) {
		char Subcarrier[128];
		snprintf(Subcarrier, sizeof(Subcarrier), "failed to open xml file \"%s\"", Carrier);
		jump(I_No_XML_File, Subcarrier);
	}
	fseek(File, 0L, SEEK_END);
	int Length = ftell(File);
	rewind(File);
	char* Yield = malloc(Length + 1);
	fread(Yield, 1, Length, File);
	fclose(File);
	Yield[Length] = '\0';
	int Index = 0;
	int Subindex = 0;
	while (Yield[Index] != '\0') {
		if (Yield[Index] != '\n' && Yield[Index] != '\t') {
			Yield[Subindex] = Yield[Index];
			Subindex++;
		}
		Index++;
	}
	Yield[Subindex] = '\0';
	return Yield;
}

int Get_Integer(char* Path, char* Text, char* Element) {
	char* Carrier = Find_Element(Path, Text, Element, NULL);
	bool Zero = false;
	int Yield = atoi(Carrier);
	if (Carrier[0] == '0') {
		Zero = true;
		Yield = 0;
	}
	free_c(Carrier);
	if (Yield == 0 && !Zero) {
		char Subcarrier[128];
		snprintf(Subcarrier, sizeof(Subcarrier), "xml parser failed to process integer \"%s\" at \"assets/%s.xml\"", Element,
			Path);
		jump(I_No_Integer, Subcarrier);
	}
	return Yield;
}

bool Get_Boolean(char* Text, char* Element) {
	char Elements[2][64] = { };
	snprintf(Elements[0], sizeof(Elements[0]), "<%s/>", Element);
	snprintf(Elements[1], sizeof(Elements[1]), "<%s />", Element);
	for (int C1 = 0; C1 < strlen(Text) - strlen(Elements[1]); C1++) {
		for (int C2 = 0; C2 < 2; C2++) {
			if (strncmp(Text + C1, Elements[C2], strlen(Elements[C2])) == 0) {
				return true;
			}
		}
	}
	return false;
}

void Load_XML() {
	char* Registrar = Get_File("registrar");
	Core.Machines = Get_Integer("registrar", Registrar, "Machine_Ct");
	Metadata.Machines = calloc(Core.Machines, sizeof(Machine_Data));
	Metadata.Descriptions = calloc(Core.Machines, sizeof(char*));
	char** Raw_Names = Find_Multiple("registrar", Registrar, "Machine", Core.Machines);
	free_c(Registrar);
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		#define Machine Metadata.Machines[C1]	
		char* Machine_File = Get_File(Raw_Names[C1]);
		Machine.Name = Find_Element(Raw_Names[C1], Machine_File, "Name", NULL);
		char* Texture_Type = Find_Element(Raw_Names[C1], Machine_File, "Texture_Type", NULL);
		if (strcmp(Texture_Type, "none") == 0) {
			Machine.Animation_Type = A_None;
		} else if (strcmp(Texture_Type, "static") == 0) {
			Machine.Animation_Type = A_Static;
		} else if (strcmp(Texture_Type, "rot") == 0) {
			Machine.Animation_Type = A_Rot;
		} else if (strcmp(Texture_Type, "modular") == 0) {
			Machine.Animation_Type = A_Modular;
			Machine.Mod_Data.Parts = Get_Integer(Raw_Names[C1], Machine_File, "Parts");
		} else {
			jump(I_No_Animtype, "xml parser failed to process \"Texture_Type\"");
		}
		free_c(Texture_Type);
		Machine.Path = Find_Element(Raw_Names[C1], Machine_File, "Path", NULL);
		Machine.Price = Get_Integer(Raw_Names[C1], Machine_File, "Price");
		Machine.Fee = Get_Integer(Raw_Names[C1], Machine_File, "Fee");
		char* Quirk_Texts[4] = { "Nonrotatable", "Modular", "Interactable", "Omnidirectional" };
		for (int C2 = 0; C2 < LDE_QUIRKS; C2++) {
			Machine.Quirks[C2] = Get_Boolean(Machine_File, Quirk_Texts[C2]);
		}
		Machine.Single_ID = Get_Boolean(Machine_File, "Single_ID");
		Machine.Size = (Point){
			Get_Integer(Raw_Names[C1], Machine_File, "Width"),
			Get_Integer(Raw_Names[C1], Machine_File, "Height")
		};
		Machine.Rect = (SDL_FRect){
			0,
			0,
			LDE_TILESIZE * Settings.Scalar * Machine.Size.X,
			LDE_TILESIZE * Settings.Scalar * Machine.Size.Y
		};
		if (Machine.Single_ID) {
			Machine.Visual_ID1 = Get_Integer(Raw_Names[C1], Machine_File, "Visual_ID");
		} else {
			//idk lol
		}
		free_c(Machine_File);
		free_c(Raw_Names[C1]);
		#undef Machine
	}
	free_c(Raw_Names);
}

char* Find_Element(const char* Path, const char* Text, const char* Element, int* End_Yield) {
	char Start_Target[64];
	snprintf(Start_Target, sizeof(Start_Target), "<%s>", Element);
	char End_Target[64];
	snprintf(End_Target, sizeof(End_Target), "</%s>", Element);
	bool Found_Start = false;
	bool Found_End = false;
	int Start = 0;
	int End = 0;
	int Stop = strlen(Text) - strlen(End_Target) + 1;
	while (Start < Stop) {
		if (strncmp(Text + Start, Start_Target, strlen(Start_Target)) == 0) {
			Found_Start = true;
			break;
		}
		Start++;
	}
	End = Start + strlen(Start_Target);
	while (End < Stop) {
		if (strncmp(Text + End, End_Target, strlen(End_Target)) == 0) {
			Found_End = true;
			break;
		}
		End++;
	}
	if (!Found_Start || !Found_End) {
		char Carrier[128];
		snprintf(Carrier, sizeof(Carrier), "xml parser failed to find element \"%s\" in xml file \"%s\"", Element, Path);
		jump(I_No_Element, Carrier);
	}
	int Length = End - Start - strlen(Start_Target);
	char* Yield = malloc(Length + 1);
	strncpy(Yield, Text + Start + strlen(Start_Target), Length);
	if (End_Yield) {
		*End_Yield = End + strlen(End_Target);
	}
	Yield[Length] = '\0';
	return Yield;
}

char** Find_Multiple(const char* Path, const char* Text, const char* Element, int Count) {
	char** Yield = malloc(sizeof(char*) * Count);
	int End = 0;
	for (int C1 = 0; C1 < Count; C1++) {
		int Carrier = 0;
		Yield[C1] = Find_Element(Path, Text + End, Element, &Carrier);
		if (Yield[C1] == NULL || Carrier <= 0) {
			free_c(Yield);
			return NULL;
		}
		End += Carrier;
	}
	return Yield;
}