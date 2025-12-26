#include <ui.h>

void Render_Daily_Report(int X, int Y) {
	Render_Box(40, 40, 560, 280, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Dynamic_Text(Fonts.Halftext_Font, Metadata.Days[Data.Day] +
		"day Report", Colors.Abyss_Black, LDE_INVALID, 60);
	Render_Button(Textures.Next_Day, Rects.Next_Day, 1);
}