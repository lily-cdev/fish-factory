#include <ui.h>

void Render_Start_Game(Point Pos) {
	Render_Box((Point){ 10, 10 }, 620, 340, Colors.Light_Grey, Colors.Dark_Grey);
    char Toast[] = "[c]A year ago, you had this platform constructed; last week you moved in to start your factory. Your goal?|To make as much money as possible.";
    Render_Rich_Text(F_Subtext, Toast, (Point){ 20, 20 }, false, false);
	Render_Button(&Textures.Start_Game, &Rects.Start_Game, (UI_Link){ Start_Game }, Colors.Cherry_Blossom);
}