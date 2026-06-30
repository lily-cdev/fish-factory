#include <items.h>

int Get_Phase(Fish_Ptr Fish, int Progress) {
	float Percentage = min(((float)Progress / Fish->Max_Growth) * 100, 100.0);
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

void Get_Phase_Name(char* Buffer, int Length, Fish_Ptr Fish, int Progress, int Count) {
	float Percentage = min(((float)Progress / Fish->Max_Growth) * 100, 100.0);
	char Subbuffer[32];
	snprintf(Subbuffer, sizeof(Subbuffer), " (%i%%)", (int)(floorf(Percentage)));
	if (Count == 1) {
		snprintf(Buffer, Length, "%s%s", Growth_Phases[Get_Phase(Fish, Progress)], Subbuffer);
		return;
	}
	snprintf(Buffer, Length, "%s%s", Plural_Growth_Phases[Get_Phase(Fish, Progress)], Subbuffer);
	return;
}

Fish_Ptr Get_Fish(int Identifier) {
	for (int C1 = 0; C1 < Core.Fishes; C1++) {
		if (Metadata.Fish[C1].Identifier == Identifier) {
			return &Metadata.Fish[C1];
		}
	}
	return NULL;
}

void Cycle_Fish(int ID) {

}

char Growth_Phases[ktn_fish_phases][32] = { "egg", "larva", "fry", "fingerling", "juvenile", "near-adult" };
char Plural_Growth_Phases[ktn_fish_phases][32] = { "eggs", "larvae", "fries", "fingerlings", "juveniles", "near-adults" };
int Growth_Weights[ktn_fish_phases] = { 0, 5, 20, 35, 55, 100 };
int Pool_Ct = 0;
struct Fishlink Fishlinks[16];