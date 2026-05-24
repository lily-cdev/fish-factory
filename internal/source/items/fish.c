#include <items.h>

int Get_Phase(int Fish, int Progress) {
	float Percentage = min(((float)Progress / Fish_Catalog[Fish].Max_Growth) * 100, 100.0);
	int Phase = 0;
	for (int C1 = 0; C1 < 5; C1++) {
		if (Percentage > Growth_Weights[C1]) {
			Phase++;
		} else {
			break;
		}
	}
	return Phase;
}

void Get_Phase_Name(char* Buffer, int Length, int Fish, int Progress, int Count) {
	float Percentage = min(((float)Progress / Fish_Catalog[Fish].Max_Growth) * 100, 100.0);
	char Subbuffer[32];
	snprintf(Subbuffer, sizeof(Subbuffer), " (%i%%)", (int)(floorf(Percentage)));
	if (Count == 1) {
		snprintf(Buffer, Length, "%s%s", Growth_Phases[Get_Phase(Fish, Progress)], Subbuffer);
		return;
	}
	snprintf(Buffer, Length, "%s%s", Plural_Growth_Phases[Get_Phase(Fish, Progress)], Subbuffer);
	return;
}

Item_Ptr Get_Fish_Item(int Identifier) {
	switch (Identifier) {
	case 0:
		return Get_Item("milkfish");
		break;
	case 1:
		return Get_Item("mojarra");
		break;
	case 2:
		return Get_Item("menhaden");
		break;
	default:
		break;
	}
	return Get_Item("wet_waste");
}

Fish Fish_Catalog[ktn_fish] = { };
char Growth_Phases[ktn_fish_phases][32] = { "Egg", "Larva", "Fry", "Fingerling", "Juvenile", "Near-Adult" };
char Plural_Growth_Phases[ktn_fish_phases][32] = { "Eggs", "Larvae", "Fries", "Fingerlings", "Juveniles", "Near-Adults" };
int Growth_Weights[ktn_fish_phases] = { 0, 5, 20, 35, 55, 100 };