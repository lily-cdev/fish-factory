#include <ui.h>

void Render_Changelog() {
	for (int Counter = 0; Counter < Cache.Log_Cache.Data[Changelog].Length; Counter++) {
		SDL_FRect Log_Rectangle = Cache.Log_Rectangles.Data[Changelog].Data[Counter];
		Log_Rectangle.y -= Interface.Log_Offset;
		Render_Texture(Cache.Log_Cache.Data[Changelog].Data[Counter], &Log_Rectangle);
	}
	Render_Texture(Textures.Log_Background, &Rects.Log_Background);
	char Buffer[64];
	char Subbuffer[64];
	Truncate(Temporary.Scroll_Percent, 0, Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "Changelog - %s%%", Subbuffer);
	Process_Supply(&Supplies.Changelog_Scroll, Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, LDE_INVALID, 10);
	Render_Button(&Textures.Return, &Rects.Return, 1, Colors.Cherry_Blossom);
	if (Temporary.Log_Inversions[Changelog]) {
		Render_Button(&Textures.Sort.Data[0], &Rects.Sort.Data[0], 2, Colors.Cherry_Blossom);
	} else {
		Render_Button(&Textures.Sort.Data[1], &Rects.Sort.Data[1], 2, Colors.Cherry_Blossom);
	}
	if (Temporary.Scroll_Percent < 50) {
		Render_Button(&Textures.TBW_Texture.Data[0], &Rects.TBW_Rectangle.Data[0], 3, Colors.Cherry_Blossom);
	} else {
		Render_Button(&Textures.TBW_Texture.Data[1], &Rects.TBW_Rectangle.Data[1], 4, Colors.Cherry_Blossom);
	}
}

void Render_Credits() {
	char Prefix[16] = "Credits";
	switch (Interface.Slider_Positions[2]) {
	case 0:
		for (int Counter = 0; Counter < Cache.Log_Cache.Data[Credits].Length; Counter++) {
			SDL_FRect Log_Rectangle = Cache.Log_Rectangles.Data[Credits].Data[Counter];
			Log_Rectangle.y -= Interface.Log_Offset;
			Render_Texture(Cache.Log_Cache.Data[Credits].Data[Counter], &Log_Rectangle);
		}
		break;
	case 1:
		for (int Counter = 0; Counter < Cache.Log_Cache.Data[Legal].Length; Counter++) {
			SDL_FRect Log_Rectangle = Cache.Log_Rectangles.Data[Legal].Data[Counter];
			Log_Rectangle.y -= Interface.Log_Offset;
			Render_Texture(Cache.Log_Cache.Data[Legal].Data[Counter], &Log_Rectangle);
		}
		strcpy(Prefix, "Legal");
		break;
	default:
		break;
	}
	Render_Texture(Textures.Log_Background, &Rects.Log_Background);
	char Buffer[64];
	char Subbuffer[64];
	Truncate(Temporary.Scroll_Percent, 0, Subbuffer, sizeof(Subbuffer));
	snprintf(Buffer, sizeof(Buffer), "%s - %s%%", Prefix, Subbuffer);
	Process_Supply(&Supplies.Scroll_Percent, Buffer, Fonts.Subtext_Font, Colors.Abyss_Black, LDE_INVALID, 10);
	Render_Button(&Textures.Return, &Rects.Return, 1, Colors.Cherry_Blossom);
	Render_Slider(Interface.Slider_Texts[2], 1, 1, 2, &Interface.Slider_Positions[2], 200, 340, 240, Colors.Abyss_Black,
		Colors.Cherry_Blossom, false);
}