#include <ui.h>

void Render_Daily_Report(Point Pos) {
	Render_Box((Point){ 40, 40 }, 560, 280, Colors.Light_Grey, Colors.Dark_Grey);
	char Buffer[64];
	snprintf(Buffer, sizeof(Buffer), "%sday Report", Metadata.Days[Data.Day]);
	Process_Supply(&Supplies.Report_Header, Buffer, F_Halftext, Colors.Abyss_Black, (Point){ LDE_INVALID, 60 });
	Render_Button(&Textures.Next_Day, &Rects.Next_Day, (UI_Link){ Forward_Day }, Colors.Cherry_Blossom);
}