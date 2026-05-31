#include <items.h>

void Prep_Items() {
    Fish_Catalog[0] = Preset_Fish.Milkfish;
    Fish_Catalog[1] = Preset_Fish.Mojarra;
    Fish_Catalog[2] = Preset_Fish.Menhaden;
}

void Free_Items() {
	ktn_free(Metadata.Recipes);
}