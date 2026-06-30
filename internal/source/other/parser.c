#include <prepping.h>
#include <items.h>

char* Get_File(char* Path) {
	char Carrier[128];
	snprintf(Carrier, sizeof(Carrier), "assets/%s.xml", Path);
	FILE* File = fopen(Carrier, "r");
	if (File == NULL) {
		char Subcarrier[128];
		snprintf(Subcarrier, sizeof(Subcarrier), "failed to open xml file \"%s\"", Carrier);
		ktn_jump(I_No_XML_File, Subcarrier);
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

int Get_Integer(const char* Path, const char* Text, const char* Element) {
	char* Carrier = Find_Element(Path, Text, Element, NULL);
	bool Zero = false;
	int Yield = atoi(Carrier);
	if (Carrier[0] == '0') {
		Zero = true;
		Yield = 0;
	}
	ktn_free(Carrier);
	if (Yield == 0 && !Zero) {
		char Subcarrier[128];
		snprintf(Subcarrier, sizeof(Subcarrier), "xml parser failed to process integer \"%s\" at \"assets/%s.xml\"", Element,
			Path);
		ktn_jump(I_No_Integer, Subcarrier);
	}
	return Yield;
}

float Get_Float(const char* Path, const char* Text, const char* Element) {
	char* Carrier = Find_Element(Path, Text, Element, NULL);
	float Yield = atof(Carrier);
	ktn_free(Carrier);
	return Yield;
}

bool Get_Boolean(const char* Text, const char* Element) {
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


void Get_Node(const char* Path, const char* Data, const char* Label, int* Ct_Ptr, Node_Data** Node_Ptr, Flow_Type Flow) {
	char Carrier[64];
	snprintf(Carrier, sizeof(Carrier), "%s_Ct", Label);
	int Node_Ct = Get_Integer(Path, Data, Carrier);
	*Ct_Ptr = Node_Ct;
	*Node_Ptr = malloc(sizeof(Node_Data) * Node_Ct);
	char** Subnodes = Find_Multiple(Path, Data, Label, Node_Ct);
	for (int C1 = 0; C1 < Node_Ct; C1++) {
		(*Node_Ptr)[C1].Flow = Flow;
		(*Node_Ptr)[C1].Pos.X = Get_Integer(Path, Subnodes[C1], "X");
		(*Node_Ptr)[C1].Pos.Y = Get_Integer(Path, Subnodes[C1], "Y");
		(*Node_Ptr)[C1].Cap = Get_Integer(Path, Subnodes[C1], "Cap");
		char* Direction = Find_Element(Path, Subnodes[C1], "Dir", NULL);
		const char* Identifiers[5] = { "any", "left", "up", "right", "down" };
		const Dir Results[5] = { Any, Left, Up, Right, Down };
		for (int C2 = 0; C2 < 5; C2++) {
			if (!ktn_stricmp(Direction, Identifiers[C2])) {
				continue;
			}
			(*Node_Ptr)[C1].Connection = Results[C2];
			break;
		}
		ktn_free(Direction);
		ktn_free(Subnodes[C1]);
	}
	ktn_free(Subnodes);
}

~start;
void Load_XML() {
	char* Registrar = Get_File("registrar");
	Core.Machines = Get_Integer("registrar", Registrar, "Machine_Ct");
	Core.Items = Get_Integer("registrar", Registrar, "Item_Ct");
	Core.Recipes = Get_Integer("registrar", Registrar, "Recipe_Ct");
	Core.Fishes = Get_Integer("registrar", Registrar, "Fish_Ct");
	Metadata.Machines = calloc(Core.Machines, sizeof(Machine_Data));
	char** Raw_Names = Find_Multiple("registrar", Registrar, "Machine", Core.Machines);
	int ID_Record = 0;
	for (int C1 = 0; C1 < Core.Machines; C1++) {
		#define Machine Metadata.Machines[C1]
		#define get_str(Victim) (Find_Element(Raw_Names[C1], Machine_File, Victim, NULL))
		#define get_int(Victim) (Get_Integer(Raw_Names[C1], Machine_File, Victim))
		char* Machine_File = Get_File(Raw_Names[C1]);
		Machine.Name = get_str("Name");
		Machine.Desc = get_str("Desc");
		Machine.Index = get_str("Index");
		char* Texture_Type = get_str("Texture_Type");
		if (ktn_stricmp(Texture_Type, "none")) {
			Machine.Animation_Type = A_None;
		} else if (ktn_stricmp(Texture_Type, "static")) {
			Machine.Animation_Type = A_Static;
		} else if (ktn_stricmp(Texture_Type, "rot")) {
			Machine.Animation_Type = A_Rot;
		} else if (ktn_stricmp(Texture_Type, "modular")) {
			Machine.Animation_Type = A_Modular;
			Machine.Mod_Data.Parts = get_int("Parts");
		} else if (ktn_stricmp(Texture_Type, "spinner")) {
			Machine.Animation_Type = A_Spinner;
			Machine.Spin_Data.Speed = get_int("Speed");
		} else if (ktn_stricmp(Texture_Type, "gauged")) {
			Machine.Animation_Type = A_Gauged;
			Machine.Gauge_Data.Pos = (Point){ get_int("Gauge_X"), get_int("Gauge_Y") };
			Machine.Gauge_Data.Size = (Point){ get_int("Gauge_W"), get_int("Gauge_H") };
		} else {
			ktn_jump(I_No_Animtype, "xml parser failed to process \"Texture_Type\"");
		}
		ktn_free(Texture_Type);
		char* Power_Type = get_str("Power_Type");
		if (ktn_stricmp(Power_Type, "none")) {
			Machine.Power_Type = F_None;
		} else if (ktn_stricmp(Power_Type, "in")) {
			Machine.Power_Type = F_In;
		} else if (ktn_stricmp(Power_Type, "out")) {
			Machine.Power_Type = F_Out;
		} else if (ktn_stricmp(Power_Type, "any")) {
			Machine.Power_Type = F_Either;
		} else {
			ktn_jump(I_No_Powertype, "xml parser failed to process \"Power_Type\"");
		}
		if (Machine.Power_Type != F_None) {
			Machine.Power_Capacity = get_int("Power_Capacity");
			Machine.Anchor.X = get_int("Anchor_X");
			Machine.Anchor.Y = get_int("Anchor_Y");
		}
		ktn_free(Power_Type);
		Machine.Path = get_str("Path");
		Machine.Price = get_int("Price");
		Machine.Fee = get_int("Fee");
		char* Quirk_Texts[4] = { "Nonrotatable", "Modular", "Interactable", "Omnidirectional" };
		for (int C2 = 0; C2 < ktn_quirks; C2++) {
			Machine.Quirks[C2] = Get_Boolean(Machine_File, Quirk_Texts[C2]);
		}
		Machine.Size = (Point){
			get_int("Width"),
			get_int("Height")
		};
		Machine.Rect = (SDL_FRect){
			0.0f,
			0.0f,
			ktn_fscale(ktn_tile_size * Machine.Size.X),
			ktn_fscale(ktn_tile_size * Machine.Size.Y)
		};
		bool Single_ID = Get_Boolean(Machine_File, "Single_ID");
		bool Rot_ID = Get_Boolean(Machine_File, "Rot_ID");
		if (Single_ID) {
			Machine.Visual_Type = I_Single;
			Machine.Visual_ID1 = get_int("Visual_ID");
			ID_Record = max(ID_Record, Machine.Visual_ID1);
		} else if (Rot_ID) {
			Machine.Visual_Type = I_Rot;
			const char* Tags[4] = { "Visual_Left", "Visual_Up", "Visual_Right", "Visual_Down" };
			for (int C2 = 0; C2 < 4; C2++) {
				Machine.Visual_ID4[C2] = get_int(Tags[C2]);
				ID_Record = max(ID_Record, Machine.Visual_ID4[C2]);
			}
		} else {
			Machine.Visual_Type = I_None_Vis;
			//idk lol
		}
		Machine.Heating = Get_Boolean(Machine_File, "Heating");
		Machine.Irradiating = Get_Boolean(Machine_File, "Irradiating");
		Machine.Command = Get_Boolean(Machine_File, "Command");
		if (Get_Boolean(Machine_File, "Fluid_Processor")) {
			Get_Node(Raw_Names[C1], Machine_File, "Input", &Machine.Input_Ct, &Machine.Inputs, F_In);
			Get_Node(Raw_Names[C1], Machine_File, "Output", &Machine.Output_Ct, &Machine.Outputs, F_Out);
			Machine.Neutral_Ct = get_int("Neutral_Ct");
		}
		ktn_free(Machine_File);
		ktn_free(Raw_Names[C1]);
		#undef get_str
		#undef get_int
		#undef Machine
	}
	ktn_free(Raw_Names);
	Raw_Names = Find_Multiple("registrar", Registrar, "Item", Core.Items);
	Metadata.Items = calloc(Core.Items, sizeof(Item_Data));
	for (int C1 = 0; C1 < Core.Items; C1++) {
		#define Item Metadata.Items[C1]
		#define get_str(Victim) (Find_Element(Raw_Names[C1], Item_File, Victim, NULL))
		#define get_int(Victim) (Get_Integer(Raw_Names[C1], Item_File, Victim))
		char* Item_File = Get_File(Raw_Names[C1]);
		Item.Name = get_str("Name");
		Item.Index = get_str("Index");
		Item.Path = get_str("Path");
		Item.Coolant = Get_Boolean(Item_File, "Coolant");
		Item.ID = get_int("ID");
		Item.Price = get_int("Price");
		Item.Chem_Energy = get_int("Chem_Energy");
		Item.Nutrition = get_int("Nutrition") * 0.01f;
		if (ktn_stricmp(get_str("Boil_Pt"), "none")) {
			Item.Boil_Pt = -2;
		} else if (ktn_stricmp(get_str("Boil_Pt"), "gas")) {
			Item.Boil_Pt = ktn_invalid;
		} else {
			Item.Boil_Pt = get_int("Boil_Pt");
		}
		if (ktn_stricmp(get_str("V_Enthalpy"), "none")) {
			Item.V_Enthalpy = -2;
		} else if (ktn_stricmp(get_str("V_Enthalpy"), "gas")) {
			Item.V_Enthalpy = ktn_invalid;
		} else {
			Item.V_Enthalpy = get_int("V_Enthalpy");
		}
		char* Danger = get_str("Hazard");
		if (ktn_stricmp(Danger, "none")) {
			Item.Danger = Harmless;
		} else if (ktn_stricmp(Danger, "low")) {
			Item.Danger = Mild;
		} else if (ktn_stricmp(Danger, "mid")) {
			Item.Danger = Medium;
		} else if (ktn_stricmp(Danger, "high")) {
			Item.Danger = Severe;
		} else {
			ktn_jump(I_No_Hazard, "xml parser failed to process \"Hazard\"");
		}
		ktn_free(Danger);
		char* Value = get_str("Value");
		if (ktn_stricmp(Value, "none")) {
			Item.Worth = Worthless;
		} else if (ktn_stricmp(Value, "low")) {
			Item.Worth = Normal;
		} else if (ktn_stricmp(Value, "mid")) {
			Item.Worth = Expensive;
		} else if (ktn_stricmp(Value, "high")) {
			Item.Worth = Exotic;
		} else {
			char Carrier[128];
			snprintf(Carrier, sizeof(Carrier), "xml parser failed to process \"Value\" at \"%s\"", Raw_Names[C1]);
			ktn_jump(I_No_Value, Carrier);
		}
		ktn_free(Value);
		#undef get_str
		#undef get_int
		#undef Item
		ktn_free(Item_File);
		ktn_free(Raw_Names[C1]);
	}
	ktn_free(Raw_Names);
	Raw_Names = Find_Multiple("registrar", Registrar, "Recipe", Core.Recipes);
	Metadata.Recipes = calloc(Core.Recipes, sizeof(Recipe));
	for (int C1 = 0; C1 < Core.Recipes; C1++) {
		#define Recipe Metadata.Recipes[C1]
		#define get_str(Victim) (Find_Element(Raw_Names[C1], Recipe_File, Victim, NULL))
		#define get_int(Victim) (Get_Integer(Raw_Names[C1], Recipe_File, Victim))
		char* Recipe_File = Get_File(Raw_Names[C1]);
		char* Subtype = get_str("Type");
		if (ktn_stricmp(Subtype, "both")) {
			Recipe.Type = 0;
		} else if (ktn_stricmp(Subtype, "in")) {
			Recipe.Type = 1;
		} else if (ktn_stricmp(Subtype, "out")) {
			Recipe.Type = 2;
		} else {
			char Carrier[128];
			snprintf(Carrier, sizeof(Carrier), "xml parser failed to process \"Type\" at \"%s\"", Raw_Names[C1]);
			ktn_jump(I_No_Type, Carrier);
		}
		ktn_free(Subtype);
		Recipe.Shuffling_Barred = Get_Boolean(Recipe_File, "Shuffling_Barred");
		Recipe.Voiding_Excess = Get_Boolean(Recipe_File, "Voiding_Excess");
		Recipe.Time = get_int("Time");
		Recipe.Power = get_int("Power");
		Recipe.Machine = Get_Machine(get_str("Parent"));
		char** IO_Carrier = Find_Multiple(Raw_Names[C1], Recipe_File, "Input", Recipe.Machine->Input_Ct);
		for (int C2 = 0; C2 < Recipe.Machine->Input_Ct; C2++) {
			Recipe.Input_Items[C2] = Get_Item(Find_Element(Raw_Names[C1], IO_Carrier[C2], "Item", NULL));
			Recipe.Input_Counts[C2] = Get_Float(Raw_Names[C1], IO_Carrier[C2], "Volume");
			ktn_free(IO_Carrier[C2]);
		}
		ktn_free(IO_Carrier);
		IO_Carrier = Find_Multiple(Raw_Names[C1], Recipe_File, "Output", Recipe.Machine->Output_Ct);
		for (int C2 = 0; C2 < Recipe.Machine->Output_Ct; C2++) {
			Recipe.Output_Items[C2] = Get_Item(Find_Element(Raw_Names[C1], IO_Carrier[C2], "Item", NULL));
			Recipe.Output_Counts[C2] = Get_Float(Raw_Names[C1], IO_Carrier[C2], "Volume");
			ktn_free(IO_Carrier[C2]);
		}
		ktn_free(IO_Carrier);
		#undef get_str
		#undef get_int
		#undef Recipe
		ktn_free(Recipe_File);
		ktn_free(Raw_Names[C1]);
	}
	ktn_free(Raw_Names);
	Raw_Names = Find_Multiple("registrar", Registrar, "Fish", Core.Fishes);
	Metadata.Fish = calloc(Core.Fishes, sizeof(Fish_Data));
	for (int C1 = 0; C1 < Core.Fishes; C1++) {
		#define Fish Metadata.Fish[C1]
		#define get_str(Victim) (Find_Element(Raw_Names[C1], Fish_File, Victim, NULL))
		#define get_int(Victim) (Get_Integer(Raw_Names[C1], Fish_File, Victim))
		char* Fish_File = Get_File(Raw_Names[C1]);
		Fish.Name = get_str("Name");
		Fish.Identifier = get_int("ID");
		Fish.Item = Get_Item(get_str("Item"));
		Fish.Max_Growth = get_int("Max_Growth");
		Fish.Size = Get_Float(Raw_Names[C1], Fish_File, "Size");
		Fish.Food_Consumption = Get_Float(Raw_Names[C1], Fish_File, "Hunger");
		Fish.Fragility = Get_Float(Raw_Names[C1], Fish_File, "Fragility");
		#undef get_str
		#undef get_int
		#undef Fish
		ktn_free(Fish_File);
		ktn_free(Raw_Names[C1]);
	}
	ktn_free(Raw_Names);
	ktn_free(Registrar);
	printf("debug info:\nlowest unreg. visual id -> %i\n", ID_Record + 1);
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
		ktn_jump(I_No_Element, Carrier);
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
			ktn_free(Yield);
			return NULL;
		}
		End += Carrier;
	}
	return Yield;
}
~end;