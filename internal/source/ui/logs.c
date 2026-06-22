#include <ui.h>

void Render_Changelog() {
	Render_Rich_Text(F_Halftext, Metadata.Logs[Changelog], (Point){ 52, 52 - Interface.Log_Offset }, Temporary.Log_Inversions[
		Changelog], false);
	Render_Texture(Textures.Log_Background, &Rects.Log_Background);
	char Buffer[64];
	char Subbuffer[64];
	Truncate(Temporary.Scroll_Percent, 0, Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "changelog - %s%%", Subbuffer);
	Process_Supply(&Supplies.Changelog_Scroll, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ ktn_invalid, 10 });
	Render_Button(&Textures.Return, &Rects.Return, (UI_Link){ Back }, Colors.Cherry_Blossom);
	Render_Button(&Textures.Sort.Data[(int)(!Temporary.Log_Inversions[Changelog])], &Rects.Sort.Data[(int)(
		!Temporary.Log_Inversions[Changelog])], (UI_Link){ Invert_Changelog }, Colors.Cherry_Blossom);
	bool Halfway = (Temporary.Scroll_Percent >= 50);
	Render_Button(&Textures.TBW_Texture.Data[(int)Halfway], &Rects.TBW_Rectangle.Data[(int)Halfway], (UI_Link){ Jump_Changelog,
		.Param.Integer = (int)Halfway }, Colors.Cherry_Blossom);
}

void Render_Credits() {
	char Prefix[16] = "credits";
	switch (Interface.Slider_Positions[2]) {
	case 0:
		Render_Rich_Text(F_Halftext, Metadata.Logs[Credits], (Point){ 52, 52 - Interface.Log_Offset }, Temporary.Log_Inversions[
			Credits], false);
		break;
	case 1:
		Render_Rich_Text(F_Halftext, Metadata.Logs[Legal], (Point){ 52, 52 - Interface.Log_Offset }, Temporary.Log_Inversions[
			Legal], false);
		strcpy(Prefix, "legal");
		break;
	default:
		break;
	}
	Render_Texture(Textures.Log_Background, &Rects.Log_Background);
	char Buffer[64];
	char Subbuffer[64];
	Truncate(Temporary.Scroll_Percent, 0, Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "%s - %s%%", Prefix, Subbuffer);
	Process_Supply(&Supplies.Scroll_Percent, Buffer, F_Subtext, Colors.Abyss_Black, (Point){ ktn_invalid, 10 });
	Render_Button(&Textures.Return, &Rects.Return, (UI_Link){ Back }, Colors.Cherry_Blossom);
	Render_Slider(2, 1, 1, (Point){ 200, 340 }, 240, Colors.Abyss_Black, Colors.Cherry_Blossom, false);
}