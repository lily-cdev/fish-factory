#include <items.h>

Recipe* I_Recipes[LDE_MACHINES][8];
Recipe* O_Recipes[LDE_MACHINES][8];
Recipe* IO_Recipes[LDE_MACHINES][8];
Recipe* All_Recipes[LDE_RECIPETYPES][LDE_MACHINES][8];

void Prep_Items() {
    Fish_Catalog[0] = Preset_Fish.Milkfish;
    Fish_Catalog[1] = Preset_Fish.Mojarra;
    Fish_Catalog[2] = Preset_Fish.Menhaden;
    Item_Stack Item_Carrier[LDE_ITEMS] = {
        Preset_Items.Raw_Saltwater, Preset_Items.Saltwater, Preset_Items.Marine_Snow, Preset_Items.Waste,Preset_Items.Steam,
		Preset_Items.Desalinated_Water, Preset_Items.Salt, Preset_Items.Raw_Algae, Preset_Items.Biopaste,
		Preset_Items.Milkfish, Preset_Items.Mojarra, Preset_Items.Menhaden, Preset_Items.Drill_Mud, Preset_Items.J1,
        Preset_Items.J2, Preset_Items.Hydrogen, Preset_Items.Oxygen, Preset_Items.Chlorine, Preset_Items.Sodium_Hydroxide,
		Preset_Items.Hydrogen_Chloride, Preset_Items.Hydrochloric_Acid
	};
    memcpy(Preset_Items.Item_List, Item_Carrier, sizeof(Preset_Items.Item_List)); 
	Preset_O_Recipes.RP_Saltwater = (Recipe){ false, false, 1, 4, { }, { }, 0, { Preset_Items.Raw_Saltwater }, { 0.5 }, 1, 1 };
	Preset_O_Recipes.GB_Algae = (Recipe){ false, false, 2, 60, { }, { }, 0, { Preset_Items.Raw_Algae, Preset_Items.Raw_Algae },
		{ 2.5, 2.5 }, 2, 1 };
	Preset_IO_Recipes.FP_Saltwater = (Recipe){ true, false, 1, 70, { Preset_Items.Raw_Saltwater }, { 12 }, 1,
		{ Preset_Items.Saltwater, Preset_Items.Marine_Snow, Preset_Items.Waste }, { 8.5, 2, 1.5 }, 3, 1 };
	Preset_IO_Recipes.FP_Biopaste = (Recipe){ true, false, 1, 70, { Preset_Items.Raw_Algae }, { 4 }, 1,
		{ Preset_IO_Recipes.Blank_Item, Preset_Items.Biopaste, Preset_Items.Waste }, { 0, 2, 0.5 }, 3, 2 };
	Preset_IO_Recipes.FM_Drillmud_1 = (Recipe){ false, false, 1, 650, { Preset_Items.Saltwater, Preset_Items.Marine_Snow },
		{ 1, 5 }, 2, { Preset_Items.Drill_Mud }, { 6 }, 1, 1 };
	Preset_IO_Recipes.FM_Drillmud_2 = (Recipe){ false, false, 1, 650, { Preset_Items.Desalinated_Water,
		Preset_Items.Marine_Snow }, { 1, 5 }, 2, { Preset_Items.Drill_Mud }, { 6 }, 1, 2 };
	Preset_IO_Recipes.FM_Hydrogen_Chloride = (Recipe){ false, false, 1, 650, { Preset_Items.Hydrogen, Preset_Items.Chlorine },
		{ 3, 3 }, 2, { Preset_Items.Hydrogen_Chloride }, { 3 }, 1, 3 };
	Preset_IO_Recipes.FM_Hydrochloric_Acid = (Recipe){ false, false, 1, 650, { Preset_Items.Hydrogen_Chloride,
		Preset_Items.Desalinated_Water }, { 6, 1 }, 2, { Preset_Items.Hydrochloric_Acid }, { 1 }, 1, 4 };
	Preset_IO_Recipes.D_Water = (Recipe){ true, false, 5, 400, { Preset_Items.Saltwater }, { 4 }, 1, { Preset_Items.Salt,
		Preset_Items.Desalinated_Water }, { 1, 2.5 }, 2, 1 };
	Preset_IO_Recipes.EP_Water = (Recipe){ true, false, 10, 5000, { Preset_Items.Desalinated_Water }, { 12 }, 1,
		{ Preset_IO_Recipes.Blank_Item, Preset_Items.Hydrogen, Preset_Items.Oxygen }, { 0, 12, 12 }, 3, 1 };
	Preset_IO_Recipes.EP_Saltwater = (Recipe){ true, false, 10, 5000, { Preset_Items.Saltwater }, { 12 }, 1, {
		Preset_Items.Sodium_Hydroxide, Preset_Items.Hydrogen, Preset_Items.Chlorine }, { 12, 6, 6 }, 3, 2 };
	Preset_IO_Recipes.EP_Salt = (Recipe){ true, false, 10, 5000, { Preset_Items.Salt }, { 18 }, 1,
		{ Preset_Items.Hydrogen, Preset_Items.Sodium_Hydroxide, Preset_Items.Chlorine }, { 9, 18, 9 }, 3, 3 };
	Preset_Categories.Coolant = (Item_Category){
		.Identifier = 0,
		.Display_Name = "Heating Medium",
		.Contents = {
			Preset_Items.Saltwater,
			Preset_Items.Desalinated_Water
		},
		.Length = 2
	};
	Preset_Categories.Feedwater = (Item_Category){
		.Identifier = 0,
		.Display_Name = "Feedwater",
		.Contents = {
			Preset_Items.Desalinated_Water
		},
		.Length = 1
	};
	Preset_Categories.Biomass = (Item_Category){
		.Identifier = 1,
		.Display_Name = "Biomass",
		.Contents = {
			Preset_Items.Marine_Snow,
			Preset_Items.Raw_Algae,
			Preset_Items.Biopaste,
			Preset_Items.Milkfish,
			Preset_Items.Mojarra,
			Preset_Items.Menhaden
		},
		.Length = 6
	};
	Recipe Null_Carrier = NULLRECIPE;
	for (int Counter = 0; Counter < LDE_MACHINES; Counter++) {
		I_Recipes[Counter][0] = &Null_Carrier;
		O_Recipes[Counter][0] = &Null_Carrier;
		IO_Recipes[Counter][0] = &Null_Carrier;
	}
	O_Recipes[Ram_Pump][0] = &Preset_O_Recipes.RP_Saltwater;
	O_Recipes[Ram_Pump][1] = &Null_Carrier;
	IO_Recipes[Filtration_Plant][0] = &Preset_IO_Recipes.FP_Saltwater;
	IO_Recipes[Filtration_Plant][1] = &Preset_IO_Recipes.FP_Biopaste;
	IO_Recipes[Filtration_Plant][2] = &Null_Carrier;
	IO_Recipes[Fluid_Mixer][0] = &Preset_IO_Recipes.FM_Drillmud_1;
	IO_Recipes[Fluid_Mixer][1] = &Preset_IO_Recipes.FM_Drillmud_2;
	IO_Recipes[Fluid_Mixer][2] = &Preset_IO_Recipes.FM_Hydrogen_Chloride;
	IO_Recipes[Fluid_Mixer][3] = &Preset_IO_Recipes.FM_Hydrochloric_Acid;
	IO_Recipes[Fluid_Mixer][4] = &Null_Carrier;
	IO_Recipes[Distillery][0] = &Preset_IO_Recipes.D_Water;
	IO_Recipes[Distillery][1] = &Null_Carrier;
	IO_Recipes[Electrolytic_Cell][0] = &Preset_IO_Recipes.EP_Water;
	IO_Recipes[Electrolytic_Cell][1] = &Preset_IO_Recipes.EP_Saltwater;
	IO_Recipes[Electrolytic_Cell][2] = &Preset_IO_Recipes.EP_Salt;
	IO_Recipes[Electrolytic_Cell][3] = &Null_Carrier;
	memcpy(All_Recipes[0], I_Recipes, sizeof(All_Recipes[0]));
	memcpy(All_Recipes[1], O_Recipes, sizeof(All_Recipes[1]));
	memcpy(All_Recipes[2], IO_Recipes, sizeof(All_Recipes[2]));
}