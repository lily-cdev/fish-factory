#include <Legacy_Items.hpp>

int Get_Phase(int Fish, int Progress) {
	double Percentage = std::min(((double)Progress / Fish_Catalog[Fish].Maximum_Growth) * 100, 100.0);
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

std::string Get_Phase_Name(int Fish, int Progress, int Count) {
	double Percentage = std::min(((double)Progress / Fish_Catalog[Fish].Maximum_Growth) * 100, 100.0);
	std::string Attachment = " (" + std::to_string(static_cast<int>(std::floor(Percentage))) + "%)";
	if (Count == 1) {
		return Growth_Phases[Get_Phase(Fish, Progress)] + Attachment;
	}
	return Plural_Growth_Phases[Get_Phase(Fish, Progress)] + Attachment;
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

std::vector<Fish> Fish_Catalog = { Preset_Fish.Milkfish, Preset_Fish.Mojarra, Preset_Fish.Menhaden };
std::vector<std::string> Growth_Phases = { "Egg", "Larva", "Fry", "Fingerling", "Juvenile", "Near-Adult" };
std::vector<std::string> Plural_Growth_Phases = { "Eggs", "Larvae", "Fries", "Fingerlings", "Juveniles", "Near-Adults" };
std::vector<int> Growth_Weights = { 0, 5, 20, 35, 55, 100 };