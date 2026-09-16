#include <ui.h>

void Render_Victory(Point Pos) {
	Render_Box((Point){ 10, 10 }, 620, 340, Colors.Light_Grey, Colors.Dark_Grey);
	Render_Texture(Textures.Victory_Content, &Rects.Victory_Content);
}