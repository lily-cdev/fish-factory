#include <ui.h>

void Render_Main() {
    Render_Texture(Textures.Emblem, &Rects.Emblem);
	Render_Texture(Textures.Logo1, &Rects.Logo1);
	Render_Texture(Textures.Logo2, &Rects.Logo2);
	Render_Button(&Textures.New_Game, &Rects.New_Game, 1, Colors.Cherry_Blossom);
	Render_Button(&Textures.Settings, &Rects.Settings, 2, Colors.Cherry_Blossom);
	Render_Button(&Textures.Update_Logs, &Rects.Update_Logs, 3, Colors.Cherry_Blossom);
	Render_Button(&Textures.Credits, &Rects.Credits, 4, Colors.Cherry_Blossom);
	Render_Button(&Textures.Quit_Game, &Rects.Quit_Game, 5, Colors.Cherry_Blossom);
}

void Render_Loader() {
	Render_Saveloader();
	Render_Button(&Textures.Return, &Rects.Return, 1, Colors.Cherry_Blossom);
}