#include <ui.h>

void Render_Main() {
    Render_Texture(Textures.Emblem, &Rects.Emblem);
	Render_Texture(Textures.Logo, &Rects.Logo);
	Render_Button(&Textures.New_Game, &Rects.New_Game, (UI_Link){ Tab_Saveloader }, Colors.Cherry_Blossom);
	Render_Button(&Textures.Settings, &Rects.Settings, (UI_Link){ Switch_Tab, .Param.Integer = 3 },
		Colors.Cherry_Blossom);
	Render_Button(&Textures.Update_Logs, &Rects.Update_Logs, (UI_Link){ Switch_Tab, .Param.Integer = 4 },
		Colors.Cherry_Blossom);
	Render_Button(&Textures.Credits, &Rects.Credits, (UI_Link){ Switch_Tab, .Param.Integer = 5 }, Colors.Cherry_Blossom);
	Render_Button(&Textures.Quit_Game, &Rects.Quit_Game, (UI_Link){ Quit }, Colors.Cherry_Blossom);
}

void Render_Loader() {
	Render_Saveloader();
	Render_Button(&Textures.Return, &Rects.Return, (UI_Link){ Back }, Colors.Cherry_Blossom);
}