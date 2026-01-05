#include <ui.h>

void Render_Daily_Report(int X, int Y) {
	Render_Box(40, 40, 560, 280, Colors.Light_Grey, Colors.Dark_Grey);
	char Buffer[64];
	snprintf(Buffer, sizeof(Buffer), "%sday Report", Metadata.Days[Data.Day]);
	Render_Dynamic_Text(Fonts.Halftext_Font, Buffer, Colors.Abyss_Black, LDE_INVALID, 60);
	Render_Button(Textures.Next_Day, Rects.Next_Day, 1, Colors.Cherry_Blossom);
}