#include <prepping.h>

bool Detect_Mouse_Collision(const SDL_FRect Target) {
	return (Core.Mouse.X >= Target.x && Core.Mouse.X <= Target.x + Target.w &&
		Core.Mouse.Y >= Target.y && Core.Mouse.Y <= Target.y + Target.h);
}

void Render_Button(const Texture_Array Button, const Rect_Array Hitbox,
	int Selection, SDL_Color Underline_Color) {
	if (Detect_Mouse_Collision(Hitbox.Data[0])) {
		Interface.UI_Selection = Selection;
		SDL_FRect Underline_Rectangle = { Hitbox.Data[0].x, Hitbox.Data[0].y +
			Hitbox.Data[0].h + 2, Hitbox.Data[0].w, Hitbox.Data[0].h / 10 };
		SDL_SetRenderDrawColor(Core.Renderer, Underline_Color.r, Underline_Color.g,
			Underline_Color.b, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(Core.Renderer, &Underline_Rectangle);
		Clear_Renderer();
		SDL_RenderTexture(Core.Renderer, Button.Data[1], NULL, &Hitbox.Data[1]);
	} else {
		SDL_RenderTexture(Core.Renderer, Button.Data[0], NULL, &Hitbox.Data[0]);
	}
}