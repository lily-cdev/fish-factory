#include <ui.h>

void Render_Genetics(Point Pos) {
	Render_Box((Point){ 10, 10 }, 620, 340, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Texture(Textures.Genetics_Content, &Rects.Genetics_Content);
}