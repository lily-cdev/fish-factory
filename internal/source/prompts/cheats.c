#include <ui.h>

void Render_M_Generator(int X, int Y) {
	char Buffer[256];
	char Subbuffer[256];
	Render_Box(60, 60, 520, 240, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Slider(Interface.Slider_Texts[8], 1, 10, 2, &Interface.Slider_Positions[8], 120, 80, 400,
		Colors.Abyss_Black, Colors.Cherry_Blossom, true);
	Abbreviate_Number(Data.Settings_Grid[Interface.Tile.X][Interface.Tile.Y][4], Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "Producing %sLA/s", Subbuffer);
	Process_Supply(&Supplies.Money_Production, Buffer, Fonts.Halftext_Font, Colors.Abyss_Black, LDE_INVALID, 120);
	for (int C1 = 0; C1 < 2; C1++) {
		Render_Button(&Textures.Confirmation.Data[C1], &Rects.Confirmation.Data[C1], C1 + 3,
			Colors.Cherry_Blossom);
	}
}

void Render_F_Generator(int X, int Y) {
	Render_Box(60, 60, 520, 240, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Slider(Interface.Slider_Texts[9], 1, LDE_ITEMS - 1, 2, &Interface.Slider_Positions[9],
		120, 80, 400, Colors.Abyss_Black, Colors.Cherry_Blossom, true);
	Render_Slider(Interface.Slider_Texts[10], 2, 240, 3, &Interface.Slider_Positions[10],
		120, 120, 400, Colors.Abyss_Black, Colors.Cherry_Blossom, true);
	Render_Slider(Interface.Slider_Texts[11], 3, LDE_VALVE300LENGTH - 1, 4, &Interface.Slider_Positions[11],
		120, 160, 400, Colors.Abyss_Black, Colors.Cherry_Blossom, true);
	char Buffer[256];
	char Subbuffer[256];
	Abbreviate_Number(Data.Settings_Grid[X][Y][5], Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "Producing %sL/s of %i °F ", Subbuffer, (int)Data.Settings_Grid[X][Y][4]);
	strcat(Buffer, ID_To_Item(Data.Settings_Grid[X][Y][3]).Display_Name);
	Process_Supply(&Supplies.Fluid_Production, Buffer, Fonts.Halftext_Font, Colors.Abyss_Black, LDE_INVALID, 200);
	for (int C1 = 0; C1 < 2; C1++) {
		Render_Button(&Textures.Confirmation.Data[C1], &Rects.Confirmation.Data[C1], C1 + 5, Colors.Cherry_Blossom);
	}
}