#include <ui.h>

void Render_Changelog() {
	for (int C1 = 0; C1 < Cache.Log_Cache.Data[Changelog].Length; C1++) {
		SDL_FRect Log_Rectangle = Cache.Log_Rectangles.Data[Changelog].Data[C1];
		Log_Rectangle.y -= Interface.Log_Offset;
		Render_Texture(Cache.Log_Cache.Data[Changelog].Data[C1], &Log_Rectangle);
	}
	Render_Texture(Textures.Log_Background, &Rects.Log_Background);
	char Buffer[64];
	char Subbuffer[64];
	Truncate(Temporary.Scroll_Percent, 0, Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "changelog - %s%%", Subbuffer);
	Process_Supply(&Supplies.Changelog_Scroll, Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, (Point){ LDE_INVALID, 10 });
	Render_Button(&Textures.Return, &Rects.Return, (UI_Link){ Back }, Colors.Cherry_Blossom);
	Render_Button(&Textures.Sort.Data[(int)(!Temporary.Log_Inversions[Changelog])], &Rects.Sort.Data[(int)(
		!Temporary.Log_Inversions[Changelog])], (UI_Link){ Invert_Changelog }, Colors.Cherry_Blossom);
	bool Halfway = (Temporary.Scroll_Percent >= 50);
	Render_Button(&Textures.TBW_Texture.Data[(int)Halfway], &Rects.TBW_Rectangle.Data[(int)Halfway], (UI_Link){
		Jump_Changelog, .Param.Integer = (int)Halfway }, Colors.Cherry_Blossom);
}

void Render_Credits() {
	char Prefix[16] = "credits";
	switch (Interface.Slider_Positions[2]) {
	case 0:
		for (int C1 = 0; C1 < Cache.Log_Cache.Data[Credits].Length; C1++) {
			SDL_FRect Log_Rectangle = Cache.Log_Rectangles.Data[Credits].Data[C1];
			Log_Rectangle.y -= Interface.Log_Offset;
			Render_Texture(Cache.Log_Cache.Data[Credits].Data[C1], &Log_Rectangle);
		}
		break;
	case 1:
		for (int C1 = 0; C1 < Cache.Log_Cache.Data[Legal].Length; C1++) {
			SDL_FRect Log_Rectangle = Cache.Log_Rectangles.Data[Legal].Data[C1];
			Log_Rectangle.y -= Interface.Log_Offset;
			Render_Texture(Cache.Log_Cache.Data[Legal].Data[C1], &Log_Rectangle);
		}
		strncpy(Prefix, "legal", sizeof(Prefix));
		break;
	default:
		break;
	}
	Render_Texture(Textures.Log_Background, &Rects.Log_Background);
	char Buffer[64];
	char Subbuffer[64];
	Truncate(Temporary.Scroll_Percent, 0, Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "%s - %s%%", Prefix, Subbuffer);
	Process_Supply(&Supplies.Scroll_Percent, Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, (Point){ LDE_INVALID, 10 });
	Render_Button(&Textures.Return, &Rects.Return, (UI_Link){ Back }, Colors.Cherry_Blossom);
	Render_Slider(Interface.Slider_Texts[2], 1, 1, 2, &Interface.Slider_Positions[2], (Point){ 200, 340 }, 240,
		Colors.Abyss_Black, Colors.Cherry_Blossom, false);
}