#include <items.h>

int Get_Phase(int Fish, int Progress) {
	double Percentage = min(((double)Progress / Fish_Catalog[Fish].Maximum_Growth) * 100, 100.0);
	int Phase = 0;
	for (int Counter = 0; Counter < 5; Counter++) {
		if (Percentage > Growth_Weights[Counter]) {
			Phase++;
		} else {
			break;
		}
	}
	return Phase;
}

void Get_Phase_Name(char* Buffer, int Length, int Fish, int Progress, int Count) {
	double Percentage = min(((double)Progress / Fish_Catalog[Fish].Maximum_Growth) * 100, 100.0);
	char Subbuffer[32];
	snprintf(Subbuffer, sizeof(Subbuffer), " (%i%%)", (int)(floor(Percentage)));
	if (Count == 1) {
		snprintf(Buffer, Length, "%s%s", Growth_Phases[Get_Phase(Fish, Progress)], Subbuffer);
		return;
	}
	snprintf(Buffer, Length, "%s%s", Plural_Growth_Phases[Get_Phase(Fish, Progress)], Subbuffer);
	return;
}

Item_Stack Get_Fish_Item(int Identifier) {
	switch (Identifier) {
	case 0:
		return Preset_Items.Milkfish;
		break;
	case 1:
		return Preset_Items.Mojarra;
		break;
	case 2:
		return Preset_Items.Menhaden;
		break;
	default:
		break;
	}
	return Preset_Items.Waste;
}

Fish Fish_Catalog[LDE_FISH] = { };
char Growth_Phases[LDE_FISHPHASES][32] = { "Egg", "Larva", "Fry", "Fingerling", "Juvenile", "Near-Adult" };
char Plural_Growth_Phases[LDE_FISHPHASES][32] = { "Eggs", "Larvae", "Fries", "Fingerlings", "Juveniles", "Near-Adults" };
int Growth_Weights[LDE_FISHPHASES] = { 0, 5, 20, 35, 55, 100 };