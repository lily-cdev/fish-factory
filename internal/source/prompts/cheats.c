#include <ui.h>

void Render_M_Generator(Point Pos) {
	char Buffer[256];
	char Subbuffer[256];
	Render_Box((Point){ 60, 60 }, 520, 240, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Slider(Interface.Slider_Texts[8], 1, 10, &Interface.Slider_Positions[8], (Point){ 120, 80 }, 400,
		Colors.Abyss_Black, Colors.Cherry_Blossom, true);
	Abbreviate_Number(Data.Settings_Grid[pt(Pos)][4], Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "Producing %sLA/s", Subbuffer);
	Process_Supply(&Supplies.Money_Production, Buffer, F_Halftext, Colors.Abyss_Black, (Point){ ktn_invalid, 120 });
	Render_Button(&Textures.Confirmation.Data[0], &Rects.Confirmation.Data[0], (UI_Link){ Set_M_Cheat, .Param.Pos = Pos },
		Colors.Cherry_Blossom);
	Render_Button(&Textures.Confirmation.Data[1], &Rects.Confirmation.Data[1], (UI_Link){ Apply_M_Cheat, .Param.Pos = Pos },
		Colors.Cherry_Blossom);
}

void Render_F_Generator(Point Pos) {
	Render_Box((Point){ 60, 60 }, 520, 240, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Slider(Interface.Slider_Texts[9], 1, ktn_items - 1, &Interface.Slider_Positions[9], (Point){ 120, 80 }, 400,
		Colors.Abyss_Black, Colors.Cherry_Blossom, true);
	Render_Slider(Interface.Slider_Texts[10], 2, 240, &Interface.Slider_Positions[10], (Point){ 120, 120 }, 400,
		Colors.Abyss_Black, Colors.Cherry_Blossom, true);
	Render_Slider(Interface.Slider_Texts[11], 3, ktn_valve300_len - 1, &Interface.Slider_Positions[11],
		(Point){ 120, 160 }, 400, Colors.Abyss_Black, Colors.Cherry_Blossom, true);
	char Buffer[256];
	char Subbuffer[256];
	Abbreviate_Number(Data.Settings_Grid[pt(Pos)][5], Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "Producing %sL/s of %i °F ", Subbuffer, (int)Data.Settings_Grid[pt(Pos)][4]);
	strcat(Buffer, ID_To_Item(Data.Settings_Grid[pt(Pos)][3]).Display_Name);
	Process_Supply(&Supplies.Fluid_Production, Buffer, F_Halftext, Colors.Abyss_Black, (Point){ ktn_invalid, 200 });
	Render_Button(&Textures.Confirmation.Data[0], &Rects.Confirmation.Data[0], (UI_Link){ Set_F_Cheat, .Param.Pos = Pos },
		Colors.Cherry_Blossom);
	Render_Button(&Textures.Confirmation.Data[1], &Rects.Confirmation.Data[1], (UI_Link){ Apply_F_Cheat, .Param.Pos = Pos },
		Colors.Cherry_Blossom);
}

void Render_P_Generator(Point Pos) {
	char Buffer[256];
	char Subbuffer[256];
	Render_Box((Point){ 60, 60 }, 520, 240, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Slider(Interface.Slider_Texts[14], 1, 5, &Interface.Slider_Positions[14], (Point){ 120, 80 }, 400,
		Colors.Abyss_Black, Colors.Cherry_Blossom, true);
	Abbreviate_Number(Data.Settings_Grid[pt(Pos)][3], Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "Producing %sJ/s", Subbuffer);
	Process_Supply(&Supplies.Power_Production, Buffer, F_Halftext, Colors.Abyss_Black, (Point){ ktn_invalid, 120 });
	Render_Button(&Textures.Confirmation.Data[0], &Rects.Confirmation.Data[0], (UI_Link){ Set_P_Cheat, .Param.Pos = Pos },
		Colors.Cherry_Blossom);
	Render_Button(&Textures.Confirmation.Data[1], &Rects.Confirmation.Data[1], (UI_Link){ Apply_P_Cheat, .Param.Pos = Pos },
		Colors.Cherry_Blossom);
}